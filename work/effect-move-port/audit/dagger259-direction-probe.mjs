// Read-only original-data / current-host contact query. No public input,
// original executable, rendering, live AI, damage or world movement is tested.
import { readFile, writeFile } from 'node:fs/promises';
import * as THREE from '../../../dist/vendor/three.module.js';
import { loadNativeCombat, NativeCombatController } from '../../../dist/native-combat.js';
import { loadNativeCharacter } from '../../../dist/native-character.js';
import { NativeEffectContacts } from '../../../dist/native-effect-contacts.js';
const dist = new URL('../../../dist/', import.meta.url), here = new URL('./', import.meta.url);
const fetchBefore = globalThis.fetch, textureBefore = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function (_url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const source = JSON.parse(await readFile(new URL('pos259-read-only-graph.json', here)));
const data = await loadNativeCombat(), character = await loadNativeCharacter(0, { scale: .08, inPlace: true, appearance: 'original' });
const actor = { character, root: character.group, combat: new NativeCombatController({ ...data, poses: character.combatPoses }, { weapon: 'dagger' }) };
actor.root.position.y = .015;
const contacts = new NativeEffectContacts({ manifest: { effects: { pos259: source }, weaponAttachments: {} } });
const allVolumes = [], windowSamples = [], matrices = [];
actor.combat.attack({ poseId: 259 });
for (let i = 0; i < 2000 && actor.combat.busy; i++) {
  const update = actor.combat.update(1 / 600, { grounded: true });
  for (const state of update.segments) {
    if (state.poseId !== 259 || state.blend) continue;
    character.setPoseFrame(state.source, state.frame);
    for (const attack of state.attacks) {
      const volumes = contacts.sample(actor, state, attack); allVolumes.push(...volumes);
      windowSamples.push({ frame: state.frame, previousFrame: state.previousFrame, previousEffectTime: state.previousEffectTime, effectTime: state.effectTime });
      if (volumes.length && (matrices.length === 0 || state.effectTime - matrices.at(-1).time > .02)) {
        const v = volumes.at(-1); matrices.push({ frame: state.frame, time: v.time, center: v.center.toArray(), halfLengths: v.edges.map(edge => edge.length()) });
      }
    }
  }
}
const hit = (x, z, y = .015) => contacts.contact(allVolumes, { root: { position: new THREE.Vector3(x, y, z) } });
const examples = [[0,1],[0,1.5],[0,2],[0,0],[0,-1],[0,-1.5],[.5,1],[.7,1],[1,1],[-.5,-1],[-.7,-1]].map(([x,z]) => {
  const contact = hit(x,z); return { position: [x,.015,z], hit: !!contact, firstHitTime: contact?.effectTime ?? null, node: contact?.effectNode ?? null };
});
const gridHits = [];
for (let xi=-10;xi<=10;xi++) for (let zi=-30;zi<=30;zi++) if (hit(xi / 10, zi / 10)) gridHits.push([xi / 10, zi / 10]);
const result = { scope: 'Original p0 assets and current NativeEffectContacts; static actor origin/yaw0 and host target box; no damage, public input or native world physics.',
  posAttackWindow: [9551,9553], firstCrossedInterval: windowSamples[0], lastCrossedInterval: windowSamples.at(-1), sampledBounds: matrices,
  hostGridContactEnvelope: { x: [Math.min(...gridHits.map(p=>p[0])), Math.max(...gridHits.map(p=>p[0]))], z: [Math.min(...gridHits.map(p=>p[1])), Math.max(...gridHits.map(p=>p[1]))] }, examples };
await writeFile(new URL('dagger259-direction-probe.json',here),JSON.stringify(result,null,2)+'\n');
console.log(JSON.stringify(result,null,2));
contacts.dispose();character.dispose();globalThis.fetch=fetchBefore;THREE.TextureLoader.prototype.load=textureBefore;
