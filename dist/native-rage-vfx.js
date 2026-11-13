import * as THREE from './vendor/three.module.js';
import { loadNativeEffectManifest, createEffectTransforms, setEffectTime, effectNodeMatrix, snapshotEffectAnchors } from './native-effect-transforms.js';
import { NativeWeaponTrails } from './native-weapon-trails.js';
export { sampleEffectKeys } from './native-effect-transforms.js';

// Original PonEF keys/textures drive presentation only. No visual shape becomes
// an attack collider. The independent contact system reads native attack-node
// bounds; particle-emitter physics remains pending.
const ROOT = new URL('./assets/original/rage-vfx/', import.meta.url);
const FORMATS = new Set(['PLANE', 'BILLBOARD', 'CYLINDER', 'SPHERE', 'BOX']);
export const RAGE_VFX_ADAPTER = Object.freeze({ brightness: 1, colorGain: 1.15, tail: .18, maxActive: 12, scale: .08 });

function effectGeometry(node) {
  const d = node.dimensions;
  if (!d?.every(Number.isFinite)) return null;
  if (node.type === 'PLANE' || node.type === 'BILLBOARD') return new THREE.PlaneGeometry(Math.abs(d[0]), Math.abs(d[1]));
  if (node.type === 'BOX') return new THREE.BoxGeometry(...d.map(Math.abs)).translate(0, 0, node.flags[0] === 1 ? d[1] / 2 : 0);
  if (node.type === 'CYLINDER') {
    const start = THREE.MathUtils.degToRad(d[3]), arc = THREE.MathUtils.degToRad(THREE.MathUtils.clamp(d[4] - d[3], 1, 360));
    // 0047cdb0 emits (cos(angle)*radius, sin(angle)*radius, +/-height/2).
    // Three's Y-axis cylinder needs the additional quarter turn to keep the
    // original sector and texture seam; 00588ed0 then applies the base offset.
    return new THREE.CylinderGeometry(Math.abs(d[0]), Math.abs(d[1]), Math.abs(d[2]), 24, 1, true, start, arc).rotateX(Math.PI / 2).rotateZ(Math.PI / 2)
      .translate(0, 0, node.flags[0] === 1 ? d[2] / 2 : 0);
  }
  if (node.type === 'SPHERE') {
    // 00584e50/00585130 draw a shared full unit sphere scaled by radius;
    // the authored angle limits belong to 00584f70 particle point sampling.
    // 0047d2c0/0047d000 map U to longitude90..450 and V to latitude-90..90.
    return new THREE.SphereGeometry(Math.abs(d[0]), 24, 12).rotateX(Math.PI / 2).rotateZ(-Math.PI / 2);
  }
  return null;
}

export async function loadNativeRageVfx(scene) {
  const base=await loadNativeEffectManifest();
  const itemEffects=await fetch(new URL('./assets/original/item-vfx.json',import.meta.url)).then(r=>r.ok?r.json():{effects:{}}).catch(()=>({effects:{}}));
  const combatEffects=await fetch(new URL('./assets/original/combat-vfx.json',import.meta.url)).then(r=>r.ok?r.json():{effects:{}}).catch(()=>({effects:{}}));
  const manifest={...base,effects:{...combatEffects.effects,...base.effects,...itemEffects.effects}}, textures = new Map(), loader = new THREE.TextureLoader();
  // A contact definition can share the exact EF with an ordinary visual.
  // Preserve its bounded particle presentation when promoting it to the
  // contact manifest; never transfer adapters between different source files.
  for (const [id, visual] of Object.entries(combatEffects.effects || {})) {
    if (visual.particleAdapter && manifest.effects[id]?.sha256 === visual.sha256)
      manifest.effects[id] = {...manifest.effects[id], particleAdapter:true};
  }
  try {
    await Promise.all(Object.entries(manifest.textures).filter(([, record]) => record.url).map(async ([name, record]) => {
      // Loading failures keep that visual hidden rather than drawing an opaque
      // untextured sphere over the actor. Other native shapes can still play.
      const texture = await new Promise(resolve => loader.load(new URL(record.url, ROOT).href, resolve, undefined, () => resolve(null)));
      if (!texture) { console.warn('技能特效贴图未能载入：', name); return; }
      texture.colorSpace = THREE.SRGBColorSpace; texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
      textures.set(name, texture);
    }));
    return new NativeRageVfx({ scene, manifest, textures });
  } catch (error) { for (const texture of textures.values()) texture.dispose(); throw error; }
}

export class NativeRageVfx {
  constructor({ scene, manifest, textures = new Map() }) {
    this.scene = scene; this.manifest = manifest; this.textures = textures;
    this.active = []; this.actors = new Map(); this.deathCasts=new WeakMap();this.disposed = false;
    this.time = 0; this.trails = new NativeWeaponTrails(scene, manifest);
    this.group = new THREE.Group(); this.group.name = '原版怒气技能特效'; scene.add(this.group);
  }
  sample(actor, state, fps = 30) {
    if (this.disposed || !actor || !state) return null;
    if(actor.disposed||actor.scriptRemoved){this.clearActor(actor);return null;}
    if(actor.dead){
      const context=state.context;
      if(state.pose?.id===469&&context?.poseId===468&&Number.isFinite(context.deathEffectTime)&&this.deathCasts.get(actor)!==state.serial){
        this.deathCasts.set(actor,state.serial);
        let effect=this.actors.get(actor);
        if(effect?.id!=='pos468'){if(effect)this._remove(effect);effect=this.manifest.effects.pos468?this._create(actor,state,'pos468'):null;}
        if(effect){effect.time=Math.max(0,context.deathEffectTime+(state.deathEffectAge||0));effect.persistAfterDeath=true;effect.anchorSnapshot=snapshotEffectAnchors(effect);this._retire(effect);}
      }
      for(const effect of [...this.active])if(effect.actor===actor&&!effect.persistAfterDeath)this._remove(effect);
      this.trails.clearActor(actor);return null;
    }
    if (actor.combat?.reacting || actor.networkReactionPhase) {
      const live = this.actors.get(actor); if (live) this._remove(live);
      this.trails.clearActor(actor); return null;
    }
    const segments = state.segments?.length ? state.segments : [state], character = actor.character;
    const hasEffect = this.actors.has(actor) || segments.some(s => this.manifest.effects[String(s.pose?.raw?.fields.effectid || '').toLowerCase()]);
    const hasDrag = segments.some(s => !s.blend && s.pose?.drags?.some(d => s.frameIntervals?.some(r => r.to >= d.start && r.from < d.end + 1)));
    if (!hasEffect && !hasDrag) return null;
    const saved = { source: character.source, frame: character.frame, facing: actor.root.rotation.y }; let offset = 0, result = null;
    try {
      for (const segment of segments) {
        if (Number.isFinite(segment.facing)) actor.root.rotation.y = segment.facing;
        // A single update can traverse several automatic POS links. Capture
        // every stage on its own skeleton, including native dummy reparenting.
        if (segment.blend && character.setPoseBlend) character.setPoseBlend(segment.blend.from, segment.blend.to, segment.blend.weight);
        else character.setPoseFrame?.(segment.source ?? segment.pose?.source, segment.frame);
        result = this._sampleSegment(actor, segment, fps, this.time + offset + (segment.consumed || 0));
        this.trails.sample(actor, segment, offset);
        offset += Math.max(0, segment.consumed || 0);
      }
    } finally {
      actor.root.rotation.y = saved.facing;
      if (state.blend && character.setPoseBlend) character.setPoseBlend(state.blend.from, state.blend.to, state.blend.weight);
      else if (saved.source != null && saved.frame != null) character.setPoseFrame?.(saved.source, saved.frame);
      else character.setPoseFrame?.(state.source ?? state.pose?.source, state.frame);
    }
    return result;
  }
  playItem(actor,id='getitem'){
    if(this.disposed||!actor||actor.dead||actor.disposed||!this.manifest.effects[id])return null;
    const live=this.actors.get(actor),effect=this._create(actor,{serial:-1},id);
    if(live&&this.active.includes(live))this.actors.set(actor,live);else this.actors.delete(actor);
    effect.live=false;effect.time=0;effect.tail=Math.max(RAGE_VFX_ADAPTER.tail,effect.visualEnd);effect.updatedAt=this.time;
    return effect;
  }
  detachOnDeath(actor,state,fps=30){
    this.sample(actor,state,fps);
    const effect=this.actors.get(actor);if(!effect)return;
    effect.persistAfterDeath=true;this._retire(effect);this.trails.clearActor(actor);
  }
  _sampleSegment(actor, state, fps, at) {
    const current = this.actors.get(actor), context = state.context;
    if(state.blend){
      if(current){current.time+=Math.max(0,state.consumed||0);current.anchorSnapshot=snapshotEffectAnchors(current);}
      return current||null;
    }
    const id = String(state.pose?.raw?.fields.effectid || '').toLowerCase();
    if (!this.manifest.effects[id]) {
      if(current&&Number.isInteger(context?.poseId)&&current.castPoseId===context.poseId&&state.pose?.raw?.fields.effectid===0){
        current.time+=Math.max(0,state.consumed||0);current.anchorSnapshot=snapshotEffectAnchors(current);return current;
      }
      if (current) this._retire(current, at - (state.consumed || 0));
      return null;
    }
    let effect = current;
    if (!effect || effect.serial !== state.serial || effect.id !== id) {
      if (effect) this._retire(effect, at - (state.consumed || 0));
      effect = this._create(actor, state, id);
    }
    // 005663e0 advances the EF clock in seconds, independently of POS speed.
    effect.time = Math.max(0, state.effectTime ?? (state.frame - state.pose.start) / fps);
    effect.anchorSnapshot = snapshotEffectAnchors(effect);
    return effect;
  }
  _create(actor, state, id) {
    while (this.active.length >= RAGE_VFX_ADAPTER.maxActive) this._remove(this.active[0]);
    const definition = this.manifest.effects[id], group = new THREE.Group(); group.name = `${id} · 怒气技`;
    this.group.add(group);
    const effect = { ...createEffectTransforms(actor, definition, this.manifest), id, serial: state.serial, castPoseId:state.context?.poseId, group, live: true, tail: 0, visualEnd: 0 };
    for (const node of effect.nodes) {
      const { source } = node; node.mesh = null;
      // The native +dc display gate must not remove the graph node: hidden
      // helper shapes still parent other effects and can provide attack bounds.
      if (source.hidden) continue;
      const particle=definition.particleAdapter && source.type==='PARTICLE';
      if ((!FORMATS.has(source.type) && !particle) || !source.texture) continue;
      const geometry = particle ? new THREE.BufferGeometry().setAttribute('position',new THREE.BufferAttribute(new Float32Array(24),3)) : effectGeometry(source); if (!geometry) continue;
      const material = particle ? new THREE.PointsMaterial({size:.10,transparent:true,opacity:0,blending:THREE.AdditiveBlending,depthWrite:false,depthTest:true,toneMapped:false}) : new THREE.MeshBasicMaterial({ transparent: true, opacity: 0, blending: THREE.AdditiveBlending,
        depthWrite: false, depthTest: true, side: THREE.DoubleSide, toneMapped: false });
      const mesh = node.mesh = particle ? new THREE.Points(geometry,material) : new THREE.Mesh(geometry, material); mesh.name = source.name;
      if (!particle && source.uvSpeed?.some(value => value !== 0)) {
        node.uvOffset = new THREE.Vector2();
        // Per-material uniform: keep shared textures/IFL frames immutable and
        // avoid per-frame vertex-buffer uploads or duplicate GPU textures.
        material.customProgramCacheKey = () => 'native-effect-uv-scroll-v1';
        material.onBeforeCompile = shader => {
          shader.uniforms.nativeUvOffset = { value: node.uvOffset };
          shader.vertexShader = 'uniform vec2 nativeUvOffset;\n' + shader.vertexShader.replace('#include <uv_vertex>',
            '#include <uv_vertex>\n#ifdef USE_MAP\n vMapUv += nativeUvOffset;\n#endif');
        };
      }
      effect.visualEnd = Math.max(effect.visualEnd, source.keys.at(-1)?.[0] || 0);
      mesh.matrixAutoUpdate = false; mesh.frustumCulled = false; mesh.visible = false; group.add(mesh);
    }
    this.active.push(effect); this.actors.set(actor, effect); return effect;
  }
  _retire(effect, at = this.time) {
    effect.live = false; effect.tail = Math.max(RAGE_VFX_ADAPTER.tail, effect.visualEnd - effect.time);
    effect.updatedAt = at;
    effect.frozenAnchors = effect.anchorSnapshot || snapshotEffectAnchors(effect);
    if (this.actors.get(effect.actor) === effect) this.actors.delete(effect.actor);
  }
  _texture(reference, time) {
    const sequence = this.manifest.textures[reference];
    if (sequence?.frames?.length) reference = sequence.frames[Math.floor(Math.max(0, time) * sequence.fpsAdapter) % sequence.frames.length];
    return this.textures.get(reference) || null;
  }
  update(dt, camera = null) {
    if (this.disposed) return;
    const step = Number.isFinite(dt) ? Math.max(0, dt) : 0;
    this.time += step; this.trails.update(step);
    for (const effect of [...this.active]) {
      if (effect.actor.dead&&!effect.persistAfterDeath || effect.actor.disposed || effect.actor.scriptRemoved || effect.live && effect.actor.combat?.reacting) { this._remove(effect); continue; }
      if (!effect.live) {
        const elapsed = Math.max(0, this.time - effect.updatedAt); effect.updatedAt = this.time;
        effect.time += elapsed; effect.tail -= elapsed;
        if (effect.tail <= 0) { this._remove(effect); continue; }
      }
      setEffectTime(effect, effect.time);
      for (const node of effect.nodes) {
        if (!node.mesh) continue;
        const { source, mesh } = node, keys = source.keys;
        mesh.visible = false;
        if (effect.time < keys[0][0] || effect.time > keys.at(-1)[0]) continue;
        const matrix = effectNodeMatrix(effect, node); if (!matrix) continue;
        const texture = this._texture(source.texture, effect.time); if (!texture) continue;
        mesh.matrix.copy(matrix);
        if(mesh.isPoints){
          // Presentation adapter only: original keys/anchors/texture, bounded deterministic spread.
          const positions=mesh.geometry.attributes.position,age=Math.max(0,effect.time-keys[0][0]);
          for(let i=0;i<8;i++){const phase=(age*2+i/8)%1,a=i*2.399963;positions.setXYZ(i,Math.cos(a)*phase*5,Math.sin(a)*phase*5,phase*2);}
          positions.needsUpdate=true;
        }
        if (source.type === 'BILLBOARD' && camera) {
          const p = new THREE.Vector3(), q = new THREE.Quaternion(), s = new THREE.Vector3(); matrix.decompose(p, q, s);
          mesh.matrix.compose(p, camera.quaternion, s);
        }
        mesh.material.map = texture;
        if (node.uvOffset) {
          // 00582460 accumulates UV only while the node is active. The Web
          // adapter integrates that interval continuously; 00585130 instead
          // applies sphere U at float32(.4)*effect age, V at effect age.
          const age = source.type === 'SPHERE' ? effect.time : Math.max(0, effect.time - keys[0][0]);
          const uGain = source.type === 'SPHERE' ? Math.fround(.4) : 1;
          node.uvOffset.set((source.uvSpeed[0] * age * uGain) % 1, (source.uvSpeed[1] * age) % 1);
        }
        mesh.material.color.setRGB(...node.key.slice(11, 14).map(v => THREE.MathUtils.clamp(v, 0, 1) * RAGE_VFX_ADAPTER.colorGain));
        mesh.material.opacity = THREE.MathUtils.clamp(node.key[24], 0, 1) * RAGE_VFX_ADAPTER.brightness;
        mesh.visible = mesh.material.opacity > .001;
      }
    }
  }
  _remove(effect) {
    if (this.actors.get(effect.actor) === effect) this.actors.delete(effect.actor);
    const index = this.active.indexOf(effect); if (index >= 0) this.active.splice(index, 1);
    effect.group.removeFromParent();
    for (const node of effect.nodes) if (node.mesh) { node.mesh.geometry.dispose(); node.mesh.material.dispose(); }
  }
  clearActor(actor) { for (const effect of [...this.active]) if (effect.actor === actor) this._remove(effect); this.trails.clearActor(actor);this.deathCasts.delete(actor); }
  clear() { for (const effect of [...this.active]) this._remove(effect); this.trails.clear();this.deathCasts=new WeakMap(); }
  dispose() {
    if (this.disposed) return; this.clear(); this.group.removeFromParent(); this.trails.dispose();
    for (const texture of new Set(this.textures.values())) texture.dispose(); this.textures.clear(); this.disposed = true;
  }
}
