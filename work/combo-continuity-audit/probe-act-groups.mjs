import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import { decodeNativeText, parseAct, parsePos, NativeCombatController } from '../../dist/native-combat.js';
const posBytes = await readFile(new URL('../../dist/assets/native/combat/P0.POS', import.meta.url));
const actBytes = await readFile(new URL('../../dist/assets/native/combat/character.act', import.meta.url));
const data = { poses: parsePos(decodeNativeText(posBytes)), actions: parseAct(decodeNativeText(actBytes)) };
const cases = [];
for (const [weapon, from, requested, nativeExpected] of [['sword', 264, 368, 369], ['spear', 281, 293, 294], ['blade', 299, 310, 313]]) {
  const controller = new NativeCombatController(data, { weapon }); controller.attack({ poseId: from });
  const accepted = controller.attack({ poseId: requested, context: { name: 'source group command', poseId: requested, rage: 100 } });
  for (let i = 0; i < 1000 && controller.timeline.pose.id === from; i++) controller.update(1 / 120, { grounded: true });
  cases.push({ weapon, from, requested, nativeExpected, group: data.actions.groups.find(group => group.includes(requested)),
    literalAllowed: data.actions.canLink(from, requested), allowedTargets: [...data.actions.links.get(from)], accepted, actualPose: controller.timeline.pose.id });
}
const evidence = { method: 'Original POS/ACT plus production controller, no browser/native execution.',
  sourceHashes: { pos: createHash('sha256').update(posBytes).digest('hex'), act: createHash('sha256').update(actBytes).digest('hex') }, cases };
const target = process.argv[2]; if (target) await writeFile(target, JSON.stringify(evidence, null, 2) + '\n');
console.log(JSON.stringify(evidence, null, 2));
