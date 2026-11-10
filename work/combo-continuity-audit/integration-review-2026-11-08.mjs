// Read-only CPU review of original assets and production controller. No browser,
// native execution, or runtime mutations. Run from the meteor-web directory.
import { readFile, writeFile } from 'node:fs/promises';
import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { decodeNativeText, parseAct, parsePos, NativeCombatController } from '../../dist/native-combat.js';
import { NATIVE_MOVE_CATALOG as catalog } from '../../dist/native-move-catalog.js';

const root = new URL('../../', import.meta.url);
const posBytes = await readFile(new URL('dist/assets/native/combat/P0.POS', root));
const actBytes = await readFile(new URL('dist/assets/native/combat/character.act', root));
const source = decodeNativeText(actBytes).replace(/#[^\r\n]*/g, '');
const poses = parsePos(decodeNativeText(posBytes)), actions = parseAct(source), data = { poses, actions };
// Independent source oracle deliberately does not call resolveTransition or
// groupIds; numeric ranges and destination order are read from original text.
const groups = [...source.matchAll(/\bgroup\s*\(\s*(\d+)(?:\s*-\s*(\d+))?\s*\)/gi)].map(m =>
  Array.from({ length: Number(m[2] || m[1]) - Number(m[1]) + 1 }, (_, i) => Number(m[1]) + i));
const sourceLinks = [...source.matchAll(/(?:^|\n)\s*(\d+)\s*\(\s*([\d,\s]+)\)/g)].map(m =>
  [Number(m[1]), [...m[2].matchAll(/\d+/g)].map(t => Number(t[0]))]);
const seen = new Set(), duplicates = [], missingTargets = [], missingGroups = [];
for (const group of groups) for (const id of group) { if (seen.has(id)) duplicates.push(id); seen.add(id); }
for (const [from, targets] of sourceLinks) for (const id of targets) {
  if (!poses.get(id)?.valid) missingTargets.push([from, id]);
  if (!seen.has(id)) missingGroups.push([from, id]);
}
assert.deepEqual(duplicates, []); assert.deepEqual(missingTargets, []); assert.deepEqual(missingGroups, []);
let groupComparisons = 0;
for (const [from, targets] of sourceLinks) for (const members of groups) for (const requested of members) {
  assert.equal(actions.resolveTransition(from, requested), targets.find(id => members.includes(id)) ?? null);
  groupComparisons++;
}
const ungroupedCatalog = catalog.filter(c => !seen.has(c.poseId)).map(c => c.poseId);
const nonfirstIdleRoots = catalog.filter(c => !c.continuationOf && groups.find(g => g.includes(c.poseId))?.[0] !== c.poseId).map(c => c.poseId);
assert.deepEqual(ungroupedCatalog, []); assert.deepEqual(nonfirstIdleRoots, []);

let idleRoots = 0, legalCatalogTransitions = 0, queuedTransitions = 0, alternateMembers = 0;
const failures = [];
for (const command of catalog.filter(c => !c.continuationOf && !c.pending)) {
  const combat = new NativeCombatController(data, { weapon: command.weapon });
  assert.ok(combat.attack({ poseId: command.poseId, context: command }));
  assert.equal(combat.timeline.pose.id, command.poseId); idleRoots++;
}
for (const prior of catalog.filter(c => !c.pending)) for (const command of catalog.filter(c => c.weapon === prior.weapon && !c.pending)) {
  if (command.continuationOf?.length && !command.continuationOf.includes(prior.poseId)) continue;
  const expected = actions.resolveTransition(prior.poseId, command.poseId); if (expected == null) continue;
  const combat = new NativeCombatController(data, { weapon: command.weapon });
  combat.attack({ poseId: prior.poseId, context: prior });
  let rage = 100, payments = 0, wrongContext = false;
  const started = combat.attack({ poseId: command.poseId, context: command,
    canStart: context => { wrongContext ||= context !== command; return rage >= context.rage; },
    onStart: context => { wrongContext ||= context !== command; rage -= context.rage; payments++; } });
  assert.equal(started, true); legalCatalogTransitions++;
  if (combat.queued != null) { queuedTransitions++; assert.equal(combat.queued, expected); assert.equal(combat.queuedMove, command); }
  for (let i = 0; i < 2400 && !payments; i++) combat.update(1 / 120, { grounded: command.stance !== 'air' });
  if (payments !== 1 || combat.timeline.pose.id !== expected || combat.currentMove !== command || wrongContext)
    failures.push({ from: prior.poseId, root: command.poseId, expected, actual: combat.timeline.pose.id, payments, wrongContext });
  assert.equal(payments, 1); assert.equal(combat.timeline.pose.id, expected); assert.equal(combat.currentMove, command); assert.equal(wrongContext, false);
  for (let i = 0; i < 240 && combat.busy; i++) combat.update(1 / 60, { grounded: true });
  assert.equal(payments, 1); assert.equal(rage, 100 - command.rage);
  if (expected !== command.poseId) alternateMembers++;
}
const result = {
  method: 'Original POS/ACT and production JS controller; no browser or native execution. Every group member is compared against an independent raw-source allowed-list oracle.',
  groupCount: groups.length, sourceCount: sourceLinks.length, groupComparisons, duplicates, missingTargets, missingGroups,
  ungroupedCatalog, nonfirstIdleRoots, idleRoots, legalCatalogTransitions, queuedTransitions, alternateMembers, failures,
  limitation: 'The controller matrix checks valid same-weapon catalog predecessors and queued resource/context behavior, not scene collision or the native directional recognizer.',
  sha256: { pos: createHash('sha256').update(posBytes).digest('hex'), act: createHash('sha256').update(actBytes).digest('hex') }
};
await writeFile(new URL('integration-review-2026-11-08.json', import.meta.url), JSON.stringify(result, null, 2) + '\n');
console.log(JSON.stringify(result, null, 2));
