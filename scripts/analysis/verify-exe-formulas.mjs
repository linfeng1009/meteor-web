// Validate the shipped JS arithmetic against the nine independent x86/RES examples.
import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import { calculateNativeDamage, nativeEffectiveStat, NATIVE_WEAPONS } from '../../dist/native-combat.js';
const root = new URL('../../', import.meta.url), evidenceURL = new URL('work/meteor-original/evidence/', root);
const load = async path => JSON.parse(await readFile(new URL(path, root), 'utf8'));
const proof = await load('work/meteor-original/evidence/E-exe-combat-formulas.json');
const resources = await load('dist/assets/original/characters/meteor-res-data.json');
const rows = proof.examples.map(sample => {
  const moveRecord = resources.allRecords.find(r => r.type === 3 && r.id === sample.pose);
  const actual = calculateNativeDamage({ attack: sample.attack, defense: sample.defense, moveRecord });
  const pass = actual.poseAttack === sample.poseAttack && actual.damage === sample.rawHPDamage && actual.victimRage === sample.rageGainedByVictim;
  return { pose: sample.pose, expected: { poseAttack: sample.poseAttack, damage: sample.rawHPDamage, rage: sample.rageGainedByVictim }, actual, pass };
});
const weaponRows = ['w0_0', 'w7_0', 'w5_0'].map(model => {
  const r = resources.allRecords.find(r => r.type === 1 && r.model.toLowerCase() === model);
  return { model, attack: nativeEffectiveStat(3, 0, [r]), defense: nativeEffectiveStat(4, 0, [r]) };
});
const js = await readFile(new URL('dist/native-combat.js', root));
const result = { observedAt: new Date().toISOString(), method: 'Owned browser module executed in Node; expected values independently derived from original x86 and RES offsets in E-exe-combat-formulas.json; not original EXE dynamic execution.', module: 'dist/native-combat.js', moduleSha256: createHash('sha256').update(js).digest('hex'), examples: rows, normalWeaponStats: weaponRows, allPassed: rows.every(r => r.pass), actionFamiliesInCurrentModule: Object.keys(NATIVE_WEAPONS), limits: ['This check validates recovered arithmetic and the shipped module values, not input-selector, rage-cast-cost, physics, mission VM or browser rendering behavior.'] };
await writeFile(new URL('E-formula-runtime-verification.json', evidenceURL), JSON.stringify(result, null, 2) + '\n');
console.log(JSON.stringify({ allPassed: result.allPassed, samples: rows.length, normalWeaponStats: weaponRows, actionFamiliesInCurrentModule: result.actionFamiliesInCurrentModule }));
if (!result.allPassed) process.exitCode = 1;
