import * as THREE from './vendor/three.module.js';

// POS Drag windows/colors/time and DES blade endpoints are original data.
// Ribbon tessellation, fade and these resource limits are Web presentation.
export const WEAPON_TRAIL_ADAPTER = Object.freeze({ maxPoints: 40, maxStrips: 24, sampleHz: 60, maxSteps: 4, lifetimeGain: 1.35, gain: 1.3 });
const NATIVE_TO_MODEL = new THREE.Matrix4().makeRotationX(-Math.PI / 2);

export class NativeWeaponTrails {
  constructor(scene, manifest) {
    this.manifest = manifest; this.time = 0; this.strips = [];
    this.group = new THREE.Group(); this.group.name = '原POS武器拖尾'; scene.add(this.group);
  }
  sample(actor, state, offset = 0) {
    if (state.blend || !state.pose?.drags?.length) return;
    const models = actor.weaponModels || (actor.weaponModel ? [actor.weaponModel] : []);
    for (const [index, drag] of state.pose.drags.entries()) {
      if (!(drag.time > 0) || !drag.color?.length) continue;
      const ranges = (state.frameIntervals || []).filter(r => r.to >= drag.start && r.from < drag.end + 1);
      if (!ranges.length) continue;
      for (const model of models) {
        if (!model.visible) continue;
        const sockets = this.manifest.weaponAttachments?.[model.name.toLowerCase()];
        const start = sockets?.d_wpnrs || sockets?.d_wpnls, end = sockets?.d_wpnre || sockets?.d_wpnle;
        if (!start || !end) continue;
        let strip = this.strips.find(s => s.actor === actor && s.model === model);
        if (!strip) strip = this._create(actor, model);
        const key = `${state.serial}:${index}`, life = Math.min(.4, Math.max(.06, drag.time * WEAPON_TRAIL_ADAPTER.lifetimeGain));
        for (const range of ranges) {
          const from = Math.max(range.from, drag.start), to = Math.min(range.to, drag.end + 1);
          if (to <= from) continue;
          const fraction = f => (f - range.from) / Math.max(1e-9, range.to - range.from);
          const at = f => THREE.MathUtils.lerp(range.timeFrom, range.timeTo, fraction(f));
          const steps = Math.min(WEAPON_TRAIL_ADAPTER.maxSteps, Math.max(1, Math.ceil((at(to) - at(from)) * WEAPON_TRAIL_ADAPTER.sampleHz)));
          for (let i = 0; i <= steps; i++) {
            const frame = THREE.MathUtils.lerp(from, to, i / steps);
            actor.character.setPoseFrame?.(state.source ?? state.pose.source, frame);
            model.updateWorldMatrix(true, false);
            const a = new THREE.Vector3(...start.position).applyMatrix4(NATIVE_TO_MODEL).applyMatrix4(model.matrixWorld);
            const b = new THREE.Vector3(...end.position).applyMatrix4(NATIVE_TO_MODEL).applyMatrix4(model.matrixWorld);
            if (![...a, ...b].every(Number.isFinite)) continue;
            const last = strip.points.at(-1), time = this.time + offset + at(frame);
            if (last?.key === key && last.a.distanceToSquared(a) + last.b.distanceToSquared(b) < 1e-9) continue;
            strip.points.push({ a, b, time, life, key, color: drag.color.slice(0, 3).map(v => v / 255) });
            if (strip.points.length > WEAPON_TRAIL_ADAPTER.maxPoints) strip.points.shift();
          }
        }
      }
    }
  }
  _create(actor, model) {
    while (this.strips.length >= WEAPON_TRAIL_ADAPTER.maxStrips) this._remove(this.strips[0]);
    const count = WEAPON_TRAIL_ADAPTER.maxPoints * 2, geometry = new THREE.BufferGeometry();
    geometry.setAttribute('position', new THREE.BufferAttribute(new Float32Array(count * 3), 3).setUsage(THREE.DynamicDrawUsage));
    geometry.setAttribute('color', new THREE.BufferAttribute(new Float32Array(count * 3), 3).setUsage(THREE.DynamicDrawUsage));
    geometry.setAttribute('uv', new THREE.BufferAttribute(new Float32Array(count * 2), 2));
    for (let i = 0; i < count; i++) geometry.attributes.uv.setXY(i, i % 2, 0);
    geometry.setIndex(new THREE.BufferAttribute(new Uint16Array((WEAPON_TRAIL_ADAPTER.maxPoints - 1) * 6), 1).setUsage(THREE.DynamicDrawUsage));
    geometry.setDrawRange(0, 0);
    const material = new THREE.ShaderMaterial({ vertexColors: true, transparent: true, blending: THREE.AdditiveBlending,
      depthWrite: false, depthTest: true, side: THREE.DoubleSide, toneMapped: false,
      vertexShader: `varying vec3 trailColor; varying float bladeU;
        void main() { trailColor = color; bladeU = uv.x;
          gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0); }`,
      fragmentShader: `varying vec3 trailColor; varying float bladeU;
        void main() { float softEdge = pow(max(0.0, sin(3.14159265 * bladeU)), 1.25);
          gl_FragColor = vec4(trailColor, softEdge * 0.6);
          #include <colorspace_fragment>
        }` });
    const mesh = new THREE.Mesh(geometry, material); mesh.name = `${model.name} · 原Drag`; mesh.frustumCulled = false; this.group.add(mesh);
    const strip = { actor, model, mesh, points: [] }; this.strips.push(strip); return strip;
  }
  update(dt) {
    this.time += Math.max(0, Number(dt) || 0);
    for (const strip of [...this.strips]) {
      const { actor, mesh } = strip;
      if (actor.dead || actor.disposed || actor.scriptRemoved || actor.combat?.reacting) { this._remove(strip); continue; }
      strip.points = strip.points.filter(p => this.time - p.time < p.life);
      if (!strip.points.length) { this._remove(strip); continue; }
      const { position, color } = mesh.geometry.attributes, indices = mesh.geometry.index; let count = 0;
      for (const [i, point] of strip.points.entries()) {
        const fade = Math.pow(THREE.MathUtils.clamp(1 - (this.time - point.time) / point.life, 0, 1), .7) * WEAPON_TRAIL_ADAPTER.gain;
        position.setXYZ(i * 2, ...point.a); position.setXYZ(i * 2 + 1, ...point.b);
        for (let j = 0; j < 2; j++) color.setXYZ(i * 2 + j, ...point.color.map(c => c * fade));
        const previous = strip.points[i - 1];
        // Never bridge separate windows/casts or a teleported weapon.
        if (previous?.key !== point.key || point.time - previous.time > .08 || point.a.distanceToSquared(previous.a) > 36) continue;
        const a = (i - 1) * 2, b = i * 2;
        for (const vertex of [a, a + 1, b, b, a + 1, b + 1]) indices.setX(count++, vertex);
      }
      position.needsUpdate = color.needsUpdate = indices.needsUpdate = true;
      mesh.geometry.setDrawRange(0, count); mesh.visible = count > 0;
    }
  }
  _remove(strip) {
    const index = this.strips.indexOf(strip); if (index < 0) return;
    this.strips.splice(index, 1); strip.mesh.removeFromParent(); strip.mesh.geometry.dispose(); strip.mesh.material.dispose();
  }
  clearActor(actor) { for (const strip of [...this.strips]) if (strip.actor === actor) this._remove(strip); }
  clear() { for (const strip of [...this.strips]) this._remove(strip); }
  dispose() { this.clear(); this.group.removeFromParent(); }
}
