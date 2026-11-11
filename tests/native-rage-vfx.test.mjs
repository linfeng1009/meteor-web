import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import { NativeRageVfx, sampleEffectKeys, RAGE_VFX_ADAPTER } from '../dist/native-rage-vfx.js';
import { NATIVE_MOVE_CATALOG } from '../dist/native-move-catalog.js';
import { NativeCombatController, decodeNativeText, parsePos, parseAct } from '../dist/native-combat.js';
import { WEAPON_TRAIL_ADAPTER } from '../dist/native-weapon-trails.js';

const packRoot = new URL('../dist/assets/original/rage-vfx/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', packRoot), 'utf8'));
const combatRoot = new URL('../dist/assets/native/combat/', import.meta.url);
const data = { poses: parsePos(decodeNativeText(await readFile(new URL('P0.POS', combatRoot)))), actions: parseAct(decodeNativeText(await readFile(new URL('character.act', combatRoot)))) };

function fixture(weapon = 'spear') {
  const scene = new THREE.Scene(), root = new THREE.Group(), nativeSpace = new THREE.Group();
  nativeSpace.rotation.x = -Math.PI / 2; nativeSpace.scale.setScalar(.08); root.add(nativeSpace); scene.add(root);
  const weaponModel = new THREE.Group(); weaponModel.name = 'w7_0'; weaponModel.rotation.x = Math.PI / 2; nativeSpace.add(weaponModel);
  const spine = new THREE.Group(); spine.position.z = 20; nativeSpace.add(spine);
  const actor = { root, weaponModel, weaponModels: [weaponModel], rage: 100, hp: 1000,
    combat: new NativeCombatController(data, { weapon }), character: { nativeSpace, getAttachment: name => ['d_base', 'bau_Spine'].includes(name) ? spine : null } };
  const textures = new Map(Object.entries(manifest.textures).filter(([, t]) => t.url).map(([id]) => [id, new THREE.Texture()]));
  const vfx = new NativeRageVfx({ scene, manifest, textures });
  return { scene, actor, vfx, textures };
}
function state(id, time, context = { rage: 60 }, serial = 1) {
  const pose = data.poses.get(id); return { pose, context, serial, frame: pose.start + time * 30 };
}

test('ordinary native EF definitions keep source hashes and render without a rage context',async()=>{
  const extra=JSON.parse(await readFile(new URL('../dist/assets/original/combat-vfx.json',import.meta.url),'utf8'));
  assert.ok(Object.keys(extra.effects).length>=66);
  assert.ok(extra.effects.pos262.particleAdapter);
  assert.ok(extra.effects.pos262.nodes.some(n=>n.type==='PARTICLE'));
  for(const effect of Object.values(extra.effects)){const bytes=await readFile(new URL('../dist/assets/original/'+effect.source,import.meta.url));assert.equal(createHash('sha256').update(bytes).digest('hex'),effect.sha256);}
  const f=fixture('musket');try{f.vfx.manifest={...manifest,effects:{...extra.effects,...manifest.effects}};
    const before={hp:f.actor.hp,rage:f.actor.rage};let visible=false;
    for(let i=0;i<30;i++){const effect=f.vfx.sample(f.actor,state(206,i/30,null));f.vfx.update(0);visible ||= effect?.nodes.some(n=>n.mesh?.visible);}
    assert.equal(visible,true);
    f.vfx.clear();const slash=f.vfx.sample(f.actor,state(262,.3,null,2));f.vfx.update(0);
    assert.ok(slash.nodes.some(n=>n.mesh?.isPoints&&n.mesh.visible));
    assert.ok(slash.nodes.filter(n=>n.mesh?.isPoints).every(n=>n.mesh.geometry.attributes.position.count===8));
    assert.equal(f.actor.hp,before.hp);assert.equal(f.actor.rage,before.rage);
  }finally{f.vfx.dispose();}
});

test('enhanced weapon skins keep their original POS blade trail instead of hiding it with the original mesh',()=>{
  const f=fixture(),pose=data.poses.get(279),drag=pose.drags[0];try{
    f.actor.weaponModel.visible=false;f.actor.butterflySword={visible:true};f.actor.character.setPoseFrame=(_,frame)=>{f.actor.weaponModel.rotation.z=(frame-drag.start)*.4;};
    f.vfx.sample(f.actor,{pose,source:pose.source,frame:drag.start+2,serial:2,context:null,consumed:1/30,frameIntervals:[{from:drag.start,to:drag.start+2,timeFrom:0,timeTo:1/30}]});f.vfx.update(1/30);
    assert.equal(f.vfx.trails.strips.length,1);assert.ok(f.vfx.trails.strips[0].mesh.geometry.drawRange.count>0);
  }finally{f.vfx.dispose();}
});

test('pickup uses preserved GetItem shapes and textures without replacing a live skill effect',async()=>{
  const extra=JSON.parse(await readFile(new URL('../dist/assets/original/item-vfx.json',import.meta.url),'utf8'));
  const bytes=await readFile(new URL('../dist/assets/original/sounds/definitions/getitem.ef',import.meta.url));
  assert.equal(createHash('sha256').update(bytes).digest('hex'),extra.effects.getitem.sha256);assert.equal(extra.effects.getitem.nodes.length,bytes.readUInt32LE(11));
  const f=fixture();try{
    f.vfx.manifest={...manifest,effects:{...manifest.effects,...extra.effects}};
    f.vfx.sample(f.actor,state(293,.1));const live=f.vfx.actors.get(f.actor),pickup=f.vfx.playItem(f.actor);
    assert.equal(f.vfx.actors.get(f.actor),live);assert.ok(pickup.nodes.filter(x=>x.mesh).length===2,'render the original plane/cylinder, not fabricated particles');
    let visible=false;for(let i=0;i<30;i++){f.vfx.update(1/60);visible ||= pickup.nodes.some(n=>n.mesh?.visible);}assert.equal(visible,true);
    for(let i=0;i<180;i++)f.vfx.update(1/60);assert.equal(f.vfx.active.includes(pickup),false);
    f.vfx.playItem(f.actor);f.vfx.clearActor(f.actor);assert.equal(f.vfx.active.length,0);
  }finally{f.vfx.dispose();}
});

test('all enabled rage moves and automatic pose links have source-backed effect definitions and PNG textures', async () => {
  const checked = new Set();
  for (const move of NATIVE_MOVE_CATALOG.filter(move => move.rage > 0 && !move.pending)) {
    let id = move.poseId; const seen = new Set();
    while (!seen.has(id) && data.poses.has(id)) {
      seen.add(id); const pose = data.poses.get(id), name = String(pose.raw.fields.effectid).toLowerCase();
      if (!pose.raw.fields.effectid) { id = pose.link; continue; }
      const effect = manifest.effects[name]; assert.ok(effect, `${move.name}: ${name}`);
      if (!checked.has(name)) {
        checked.add(name); const bytes = await readFile(new URL(`../${effect.source}`, packRoot));
        assert.equal(createHash('sha256').update(bytes).digest('hex'), effect.sha256);
        assert.equal(effect.nodes.length, bytes.readUInt32LE(11));
        assert.ok(effect.nodes.every(node => node.keys.every(key => key.length === 28 && key.every(Number.isFinite))));
      }
      id = pose.link;
    }
  }
  assert.ok(checked.size >= 38);
  for (const texture of Object.values(manifest.textures)) {
    if (texture.frames) assert.ok(texture.frames.every(name => manifest.textures[name]?.url));
    if (texture.url) {
      const bytes = await readFile(new URL(texture.url, packRoot));
      assert.equal(bytes.readUInt32BE(16), texture.width); assert.equal(bytes.readUInt32BE(20), texture.height);
    }
  }
});

test('rage visuals follow authored frames, stay absent for ordinary attacks and cannot change combat values', () => {
  const { actor, vfx } = fixture(), before = { hp: actor.hp, rage: actor.rage, serial: actor.combat.serial };
  vfx.sample(actor, state(279, .3, null)); vfx.update(.5); assert.equal(vfx.active.length, 0);
  const effect = vfx.sample(actor, state(571, .05)); vfx.update(1);
  assert.ok(Math.abs(effect.time - .05) < 1e-8, 'wall-clock updates cannot advance live animation channels');
  assert.ok(effect.nodes.every(node => !node.mesh?.visible));
  vfx.sample(actor, state(571, .4)); vfx.update(0);
  assert.ok(effect.nodes.some(node => node.mesh?.visible && node.source.name === 'Board_15'));
  assert.ok(effect.nodes.filter(node => node.mesh).every(node => node.mesh.material.opacity <= RAGE_VFX_ADAPTER.brightness));
  assert.equal(actor.hp, before.hp); assert.equal(actor.rage, before.rage); assert.equal(actor.combat.serial, before.serial);
  vfx.dispose();
});

test('original weapon DES dummies bind light to native W7_0 coordinates even when that model is hidden by a skin', () => {
  const { actor, vfx } = fixture(); actor.weaponModel.visible = false;
  const effect = vfx.sample(actor, state(571, .4)); vfx.update(0);
  const node = effect.nodes.find(node => node.source.name === 'Board_15'); assert.equal(node.mesh.visible, true);
  const position = new THREE.Vector3().setFromMatrixPosition(node.mesh.matrix);
  assert.ok(Math.abs(position.x - (-.003 * .08)) < 1e-5);
  assert.ok(Math.abs(position.z - (20.317 * .08)) < 1e-5);
  vfx.dispose();
});

test('automatic rage links play their own EF timeline and pay no second cost', () => {
  const { actor, vfx } = fixture(); let payments = 0;
  const move = NATIVE_MOVE_CATALOG.find(move => move.poseId === 562), seen = new Set();
  actor.combat.attack({ poseId: 562, context: move, onStart: command => { actor.rage -= command.rage; payments++; } });
  for (let i = 0; i < 220; i++) {
    const sample = actor.combat.update(1 / 60, { grounded: true });
    vfx.sample(actor, sample); vfx.update(1 / 60);
    for (const effect of vfx.active) seen.add(effect.id);
  }
  assert.ok(seen.has('pos562') && seen.has('pos563'));
  assert.equal(payments, 1); assert.equal(actor.rage, 40);
  assert.ok(vfx.active.length <= 2); vfx.dispose();
});

test('hit interruption, weapon changes and clear remove visuals and dispose each owned mesh once', () => {
  const { actor, vfx, textures } = fixture(); vfx.sample(actor, state(571, .4)); vfx.update(0);
  let geometryDisposals = 0, materialDisposals = 0, textureDisposals = 0;
  const meshes = vfx.active.flatMap(effect => effect.nodes.map(node => node.mesh).filter(Boolean));
  for (const mesh of meshes) { mesh.geometry.addEventListener('dispose', () => geometryDisposals++); mesh.material.addEventListener('dispose', () => materialDisposals++); }
  for (const texture of textures.values()) texture.addEventListener('dispose', () => textureDisposals++);
  actor.dead = true; vfx.update(.01);
  assert.equal(vfx.active.length, 0); assert.equal(vfx.group.children.length, 0);
  assert.equal(geometryDisposals, meshes.length); assert.equal(materialDisposals, meshes.length); assert.equal(textureDisposals, 0);
  actor.dead = false; vfx.sample(actor, state(571, .4, { rage: 60 }, 2)); vfx.clearActor(actor); assert.equal(vfx.active.length, 0);
  vfx.sample(actor, state(571, .4, { rage: 60 }, 3)); vfx.clear(); assert.equal(vfx.active.length, 0);
  const count = textures.size; vfx.dispose(); vfx.dispose(); assert.equal(textureDisposals, count);
});

test('invalid native parent bindings remain hidden instead of emitting at the world origin', () => {
  const pack = structuredClone(manifest), node = pack.effects.pos571.nodes.find(node => node.name === 'Board_15');
  node.bindings = ['not-a-native-bone', 'not-a-native-bone'];
  const { actor, vfx } = fixture(); vfx.manifest = pack;
  const effect = vfx.sample(actor, state(571, .4)); vfx.update(0);
  assert.equal(effect.nodes.find(node => node.source.name === 'Board_15').mesh.visible, false);
  assert.ok(effect.nodes.filter(node => node.mesh).every(node => node.mesh.matrix.elements.every(Number.isFinite)));
  vfx.dispose();
});

test('key interpolation retains native endpoints and a normalized quaternion', () => {
  const keys = manifest.effects.pos571.nodes.find(node => node.name === 'AttackWave01').keys;
  const time = (keys[0][0] + keys[1][0]) / 2, sample = sampleEffectKeys(keys, time);
  assert.equal(sample[0], time);
  assert.ok(Math.abs(Math.hypot(...sample.slice(4, 8)) - 1) < 1e-8);
  assert.ok(sampleEffectKeys(keys, keys[0][0]).every((value, i) => Math.abs(value - keys[0][i]) < 1e-7));
  assert.equal(sampleEffectKeys([], 0), null); assert.equal(sampleEffectKeys(keys, NaN), null);
});

test('completed qiankun finale plays all twelve authored slash shapes, independent of the recovering or struck caster', () => {
  const { actor, vfx } = fixture('qiankun');
  actor.character.getAttachment = () => actor.character.nativeSpace;
  const effect = vfx.sample(actor, state(456, 1.3444444444444648));
  vfx.update(0);
  vfx.sample(actor, state(487, 0, { rage: 100 }, 2));
  const seen = new Set();
  for (let frame = 0; frame < 100; frame++) {
    if (frame === 20) { actor.root.position.x = 30; actor.combat = { reacting: true }; }
    vfx.update(1 / 60);
    for (const node of effect.nodes.filter(n => /^SLASH/.test(n.source.name) && n.mesh?.visible)) {
      seen.add(node.source.name);
      const position = new THREE.Vector3().setFromMatrixPosition(node.mesh.matrix);
      assert.ok(Math.abs(position.x) < 20, 'a detached slash cannot follow a caster who has left the cast location');
    }
  }
  assert.equal(seen.size, 12); assert.ok(seen.has('SLASH06') && seen.has('SLASH_L06'));
  assert.equal(vfx.active.length, 0); assert.equal(actor.hp, 1000); assert.equal(actor.rage, 100);
  vfx.dispose();
});

test('one large update preserves intermediate EF stages and cancels only the active stage on a hit', () => {
  const { actor, vfx } = fixture('qiankun'); actor.character.getAttachment = () => actor.character.nativeSpace;
  const a = { ...state(452, .25, { rage: 100 }, 1), consumed: .01 }, b = { ...state(453, .25, { rage: 100 }, 2), consumed: .02 };
  const end = { ...state(454, .05, { rage: 100 }, 3), consumed: .05 };
  vfx.sample(actor, { ...end, segments: [a, b, end] }); vfx.update(.08);
  assert.deepEqual(vfx.active.map(e => e.id), ['pos452', 'pos453', 'pos454']);
  assert.equal(vfx.active[0].live, false); assert.equal(vfx.active[2].live, true);
  const detached = vfx.active[0];
  assert.ok(detached.nodes.filter(n => n.mesh?.visible).length, 'an intermediate retired stage still draws its authored shapes');
  actor.combat = { reacting: true };
  vfx.sample(actor, state(100, 0, null, 4));
  assert.ok(vfx.active.every(e => !e.live), 'being struck cancels the currently casting stage');
  assert.ok(vfx.active.includes(detached), 'previously completed stages retain their visual tails');
  vfx.dispose();
});

test('retired dart effects keep animated internal parents while freezing external cast anchors', () => {
  const { actor, vfx } = fixture('dart'); actor.character.getAttachment = () => actor.character.nativeSpace;
  const effect = vfx.sample(actor, state(201, .4));
  vfx.sample(actor, state(5, 0, null, 2)); actor.root.position.x = 50; vfx.update(.05);
  const children = effect.nodes.filter(n => /^Attack[12]/.test(n.source.name) && n.mesh?.visible);
  assert.ok(children.length >= 6); assert.ok(children.every(n => Math.abs(n.mesh.matrix.elements[12]) < 20));
  vfx.dispose();
});

test('weapon Drag windows draw bounded ribbons from original DES endpoints and restore the final skeleton pose', () => {
  const { actor, vfx } = fixture(); const pose = data.poses.get(279), drag = pose.drags[0];
  const character = actor.character; character.source = pose.source; character.frame = drag.start + 2;
  character.setPoseFrame = (source, frame) => { character.source = source; character.frame = frame; actor.weaponModel.rotation.z = (frame - drag.start) * .4; };
  const packet = { pose, source: pose.source, frame: drag.start + 2, serial: 7, context: null,
    frameIntervals: [{ from: drag.start, to: drag.start + 2, timeFrom: 0, timeTo: 1 / 30 }], consumed: 1 / 30 };
  vfx.sample(actor, packet); vfx.update(1 / 30);
  assert.equal(vfx.active.length, 0, 'ordinary attacks do not require rage effects');
  assert.equal(vfx.trails.strips.length, 1); const strip = vfx.trails.strips[0];
  assert.ok(strip.mesh.geometry.drawRange.count > 0); assert.equal(character.frame, packet.frame);
  assert.equal(actor.hp, 1000); assert.equal(actor.rage, 100);
  const socket = manifest.weaponAttachments.w7_0.d_wpnrs;
  actor.weaponModel.updateWorldMatrix(true, false);
  const expected = new THREE.Vector3(...socket.position).applyAxisAngle(new THREE.Vector3(1, 0, 0), -Math.PI / 2).applyMatrix4(actor.weaponModel.matrixWorld);
  assert.ok(strip.points.at(-1).a.distanceTo(expected) < 1e-7);
  let disposed = 0; strip.mesh.geometry.addEventListener('dispose', () => disposed++);
  vfx.update(.5); assert.equal(vfx.trails.strips.length, 0); assert.equal(disposed, 1);
  vfx.sample(actor, { ...packet, frameIntervals: [{ from: drag.end + 2, to: drag.end + 3, timeFrom: 0, timeTo: .02 }] });
  assert.equal(vfx.trails.strips.length, 0, 'no fabricated trail outside the original Drag window');
  vfx.sample(actor, packet); actor.dead = true; vfx.update(0); assert.equal(vfx.trails.strips.length, 0);
  vfx.dispose();
});

test('rapid casts never join separate trail windows, preserve pose blends and keep a bounded geometry history', () => {
  const { actor, vfx } = fixture('qiankun'), pose = data.poses.get(456), drag = pose.drags[0];
  const character = actor.character; character.source = pose.source; character.frame = drag.start + 1;
  character.setPoseFrame = (source, frame) => { character.source = source; character.frame = frame; actor.weaponModel.rotation.z = frame * .3; };
  for (let serial = 1; serial <= 70; serial++) {
    vfx.sample(actor, { pose, source: pose.source, frame: drag.start + 1, serial, context: null, consumed: .001,
      frameIntervals: [{ from: drag.start, to: drag.start + 1, timeFrom: 0, timeTo: .001 }] });
    vfx.update(.001);
  }
  const strip = vfx.trails.strips[0]; assert.ok(strip.mesh.visible);
  assert.equal(strip.points.length, WEAPON_TRAIL_ADAPTER.maxPoints);
  const indices = strip.mesh.geometry.index;
  for (let i = 0; i < strip.mesh.geometry.drawRange.count; i += 3) {
    const keys = [0, 1, 2].map(j => strip.points[Math.floor(indices.getX(i + j) / 2)].key);
    assert.equal(new Set(keys).size, 1, 'each triangle must belong to one cast and Drag window');
  }
  character.setPoseBlend = (from, to, weight) => { character.source = to.source; character.frame = to.frame; character.weight = weight; };
  const blend = { from: { source: 0, frame: 1 }, to: { source: 0, frame: pose.start }, weight: .6 };
  vfx.sample(actor, { ...state(456, .1, { rage: 100 }, 71), source: 0, blend });
  assert.equal(character.weight, .6); assert.equal(character.frame, pose.start);
  actor.weaponModel.visible = false; vfx.clear();
  vfx.sample(actor, { pose, source: 0, frame: drag.start + 1, serial: 72, frameIntervals: [{ from: drag.start, to: drag.start + 1, timeFrom: 0, timeTo: .01 }] });
  assert.equal(vfx.trails.strips.length, 0, 'skins hiding native geometry retain their own weapon VFX');
  vfx.dispose();
});
