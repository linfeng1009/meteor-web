import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import { loadNativeCombat, NativeCombatController } from '../../dist/native-combat.js';
import { NATIVE_MOVE_CATALOG } from '../../dist/native-move-catalog.js';
const dist = new URL('../../dist/', import.meta.url);
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
const data = await loadNativeCombat(), bytes = await readFile(new URL('assets/original/rage-vfx/manifest.json', dist));
const manifest = JSON.parse(bytes), formats = new Set(['PLANE', 'BILLBOARD', 'CYLINDER', 'SPHERE', 'BOX']), kinds = {}, effects = new Map(), moves = [];
for (const effect of Object.values(manifest.effects)) for (const node of effect.nodes) kinds[node.type] = (kinds[node.type] || 0) + 1;
for (const move of NATIVE_MOVE_CATALOG.filter(m => m.rage > 0 && !m.pending)) {
  const combat = new NativeCombatController(data, { weapon: move.weapon }); combat.weaponMode = move.weaponMode || 'blade';
  if (!combat.attack({ poseId: move.poseId, context: move })) throw new Error(`Cannot audit ${move.id}`);
  const seen = new Set(); let ended = false;
  for (let i = 0; i < 1800; i++) {
    const state = combat.update(1 / 60, { grounded: true });
    for (const s of state?.segments || []) {
      const id = String(s.pose?.raw?.fields.effectid || '').toLowerCase(), definition = manifest.effects[id];
      if (!definition || !(s.context?.rage > 0)) continue;
      seen.add(id);
      if (!effects.has(id)) {
        const shapes = definition.nodes.filter(n => formats.has(n.type) && n.texture);
        effects.set(id, { id, pose: s.pose.id, hostLastSample: 0, visualEnd: Math.max(0, ...shapes.map(n => n.keys.at(-1)[0])), shapes: shapes.map(n => ({ name: n.name, type: n.type, start: n.keys[0][0], end: n.keys.at(-1)[0] })) });
      }
      effects.get(id).hostLastSample = Math.max(effects.get(id).hostLastSample, s.effectTime);
    }
    if (!combat.busy) { ended = true; break; }
  }
  moves.push({ id: move.id, name: move.name, weapon: move.weapon, rage: move.rage, effects: [...seen], ended });
}
const records = [...effects.values()].map(e => ({ ...e, clippedByOldTail: e.visualEnd > e.hostLastSample + .18 + 1e-6, entirelyMissingShapesWithOldTail: e.shapes.filter(n => n.start > e.hostLastSample + .18).map(n => n.name) }));
const result = {
  scope: 'Offline source-controller presentation audit; source timeline uses grounded=true to finish holds. Not a native EXE run or manual combat completion.',
  manifestSha256: createHash('sha256').update(bytes).digest('hex'), definitions: Object.keys(manifest.effects).length, nodeTypes: kinds,
  texturedSupportedShapes: Object.values(manifest.effects).flatMap(e => e.nodes).filter(n => formats.has(n.type) && n.texture).length,
  textureRecords: Object.keys(manifest.textures).length, sourceDragPoses: [...data.poses.values()].filter(p => p.drags.length).length,
  sourceDragWindows: [...data.poses.values()].reduce((sum, p) => sum + p.drags.length, 0), supportedWeaponSocketModels: Object.keys(manifest.weaponAttachments).length,
  oldBrightness: .65, brightness: 1, colorGain: 1.15, oldTailSeconds: .18, detachedAnchorPolicy: 'last source skeleton sample frozen; internal keyed nodes continue',
  controllerMoves: moves, observedEffects: records, truncatedEffects: records.filter(e => e.clippedByOldTail).map(e => e.id),
  unportedTypes: Object.keys(kinds).filter(type => !formats.has(type) && !['AUDIO'].includes(type)),
  originalAssetsChanged: false, originalExecutableExecuted: false, gameplayRulesChanged: false
};
await writeFile(new URL('coverage-audit.json', import.meta.url), JSON.stringify(result, null, 2) + '\n');
console.log(JSON.stringify({ moves: moves.length, effects: records.length, truncatedEffects: result.truncatedEffects, dragPoses: result.sourceDragPoses, dragWindows: result.sourceDragWindows, supportedTexturedShapes: result.texturedSupportedShapes }));
