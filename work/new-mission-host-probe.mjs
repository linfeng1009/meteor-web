// Read original imported PST/metadata through the production VM/host. This
// deliberately uses mock actors/scene pose completion: no combat, rendering,
// physical navigation or original executable execution is asserted.
import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import { NativeMissionHost } from '../dist/native-mission-host.js';

const root = new URL('../dist/assets/original/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));
const weapons = JSON.parse(await readFile(new URL('weapon-models/manifest.json', root), 'utf8'));
const sources = new Map();
for (const record of manifest.scripts) sources.set(record.source.path.toLowerCase(), await readFile(new URL(record.utf8, root), 'utf8'));
const nativePosition = p => new THREE.Vector3(p[0] * .08, p[2] * .08, -p[1] * .08);
const sourceHash = createHash('sha256').update(await readFile(new URL('../dist/native-mission-host.js', import.meta.url))).digest('hex');
const results = [];
for (const mapId of ['sn03', 'sn04', 'sn09', 'sn13', 'sn15']) {
  const metadata = JSON.parse(await readFile(new URL(`maps/${mapId}/metadata.json`, root), 'utf8'));
  const sceneObjects = new Map(metadata.files.find(f => f.parsed?.format === 'DES').parsed.objects.map(object => [object.name.toLowerCase(), {
    name: object.name, pose: 0, state: 3, attributes: { active: 1, collision: 1, interactive: 1 }
  }]));
  const events = [], configurations = [], endings = [];
  const hero = { id: 500, name: '孟星魂', root: new THREE.Group(), hp: 1000, maxHp: 1000, dead: false, team: 1 };
  const game = { manifest, hero, enemies: [], paused: false,
    currentMap: { id: mapId, metadata, colliders: [], sceneObjects,
      points: metadata.waypoints.points.map(p => ({ ...p, native: p.position, position: nativePosition(p.position) })) },
    onEvent: event => events.push(event),
    getSceneObject: name => sceneObjects.get(String(name).toLowerCase()),
    playScenePose: (name, pose) => { const item = sceneObjects.get(name.toLowerCase()); if (item) { item.pose = pose; item.state = 3; } },
    setSceneActive: (name, active) => { sceneObjects.get(name.toLowerCase()).attributes.active = Number(active); },
    setSceneCollision: (name, active) => { sceneObjects.get(name.toLowerCase()).attributes.collision = Number(active); },
    hasScriptLineOfSight: () => true,
    placeScriptPlayer: config => { hero.root.position.copy(config.spawn.position); },
    createScriptActor: async config => {
      const weapon = weapons.items.find(item => item.itemId === config.weaponId);
      configurations.push({ name: config.name, model: config.modelId, weapon: config.weaponId, weaponModel: weapon?.modelId,
        weaponSupported: /^(w[01357]_)/.test(weapon?.modelId || ''), team: config.team, hp: config.hp, spawn: config.spawn.id });
      const actor = { id: 500 + config.scriptId, root: new THREE.Group(), hp: config.hp, maxHp: config.hp,
        team: config.team, dead: false, character: { dispose() {} } };
      actor.root.position.copy(config.spawn.position); game.enemies.push(actor); return actor;
    },
    _face() {}, _soundDefinition() {}, finishStory: result => endings.push(result)
  };
  let host, startError = null;
  try { host = await NativeMissionHost.create(game, { sources }); await host.start(); }
  catch (error) { startError = { message: error.message, code: error.code }; }
  if (host?.started && !startError) for (let step = 0; step < 1000 && !host.completed; step++) host.update(.1);
  const after100 = { elapsed: host?.clock, completed: host?.completed || null, globals: host?.levelVm.snapshot(),
    dialogues: host?.dialogues.length, disabledCallbacks: [...(host?.disabledCallbacks || [])] };
  let failureProbe = null;
  if (host?.started && !startError && !host.completed) {
    hero.hp = 0; host.update(.1);
    failureProbe = { assignedHP: true, completed: host.completed || null, sourceGameover: host.levelVm.snapshot().gameover };
  }
  results.push({ mapId, rule: host?.rule, roundTime: host?.roundTime, startError, configurations, after100, failureProbe,
    diagnostics: host?.diagnostics || [], endings, unsupportedPerform: events.filter(e => e.code === 'UNSUPPORTED_PERFORM') });
  host?.dispose();
}
const output = { observedAt: '2026-11-04', method: 'Production PST VM/host with original imported text and metadata, mocked actor/scene bridges; no native binary execution.',
  moduleSha256: sourceHash, elapsed: '100 simulated seconds, 0.1sec updates, no actor movement or retaliation.', results,
  limits: ['Unsupported primary weapons are recorded but deliberately accepted by this mock; this is not successful gameplay initialization.',
    'Scene poses complete immediately in mock objects; no physical mechanism completion proved.',
    'Failure probe directly assigns hero HP0 only to inspect completion priority; not natural death acceptance.'] };
const target = new URL('meteor-original/evidence/E-new-mission-host-current-2026-11-04.json', import.meta.url);
await writeFile(target, JSON.stringify(output, null, 2) + '\n');
console.log(JSON.stringify(results.map(r => ({ mapId: r.mapId, startError: r.startError, npcCount: r.configurations.length,
  diagnostics: r.diagnostics.map(d => ({ code: d.code, api: d.api, callback: d.callback })),
  failure: r.failureProbe?.completed, unsupportedWeapons: r.configurations.filter(c => !c.weaponSupported).map(c => c.weaponModel) })), null, 2));
