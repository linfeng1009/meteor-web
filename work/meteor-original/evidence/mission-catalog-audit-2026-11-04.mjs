// Offline catalogue audit. Reads imported, byte-preserved original PSTs only;
// it does not execute Meteor.exe or claim a mission is playable.
import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import { parsePst, NativeScriptVM, normalizePstPath } from '../../../dist/native-script.js';

const project = new URL('../../../', import.meta.url), original = new URL('dist/assets/original/', project);
const manifest = JSON.parse(await readFile(new URL('manifest.json', original), 'utf8'));
const weaponManifest = JSON.parse(await readFile(new URL('weapon-models/manifest.json', original), 'utf8'));
const index = new Map(manifest.scripts.map(record => [normalizePstPath(record.source.path), record]));
const items = new Map(weaponManifest.items.map(item => [Number(item.itemId), item]));
const sourceCache = new Map(), sourceRecords = new Map();
// Frozen pre-extension host capabilities observed at the start of this work.
const baselineNatives = new Set(['AddNPC','GetChar','GetAnyChar','GetSelf','GetHP','GetMaxHP','GetTeam','GetEnemy','GetGameTime','ChangeBehavior','Perform','PlayerPerform','Say','IsPerforming','StopPerform','SetTarget','Distance','MakeString','GetSceneItem','SetSceneItem','CreateEffect','NetEvent','Output','Print','GameOver','UpdateAIAttrib','RemoveNPC','Perofrm','Distanve','InitBBoxs']);
const baselineBehaviors = new Set(['wait','patrol','follow','attacktarget','aggress','run','kill']);
const baselinePerform = new Set(['say','faceto','pause','guard','aggress','attack','block']);
const supportedPrefixes = new Set(['w0','w1','w3','w5','w7']);
const hash = bytes => createHash('sha256').update(bytes).digest('hex');
const visit = (node, callback) => {
  if (!node || typeof node !== 'object') return;
  callback(node);
  for (const value of Object.values(node)) if (Array.isArray(value)) value.forEach(child => visit(child, callback)); else if (value && typeof value === 'object') visit(value, callback);
};
const literals = node => node.arguments.map(arg => arg.type === 'Literal' ? arg.value : arg.type === 'Identifier' ? { variable: arg.name } : { expression: arg.type });
async function source(file) {
  file = normalizePstPath(file); if (sourceCache.has(file)) return sourceCache.get(file);
  const record = index.get(file); if (!record) throw new Error(`Missing imported source ${file}`);
  const raw = await readFile(new URL(record.raw, original));
  if (hash(raw) !== record.source.sha256) throw new Error(`Original byte-copy hash mismatch ${file}`);
  const text = await readFile(new URL(record.utf8, original), 'utf8'), ast = parsePst(text, { file });
  const result = { text, ast, globals: file.startsWith('level/') ? new NativeScriptVM().load(ast, { file }).snapshot() : {} };
  sourceCache.set(file, result); sourceRecords.set(file, { file, raw: record.raw, utf8: record.utf8, sha256: record.source.sha256, utf8Sha256: hash(text) });
  return result;
}
async function closure(file, known = new Map()) {
  file = normalizePstPath(file); if (known.has(file)) return known;
  const entry = await source(file); known.set(file, entry);
  for (const include of entry.ast.body.filter(node => node.type === 'Include')) await closure(normalizePstPath(include.name, file), known);
  return known;
}
function weapon(id) {
  if (!id) return { id: Number(id || 0), none: true, supportedAtBaseline: true };
  const item = items.get(Number(id));
  return { id: Number(id), name: item?.name, model: item?.modelId, available: !!item?.available,
    supportedAtBaseline: !!item && supportedPrefixes.has(item.modelId.toLowerCase().split('_')[0]) };
}
function callsIn(ast) {
  const calls = [];
  visit(ast, node => { if (node.type === 'Call') calls.push({ name: node.name, args: literals(node), line: node.location?.line }); });
  return calls;
}
function analyzeBundle(bundle) {
  const functions = new Set([...bundle.values()].flatMap(entry => entry.ast.body.filter(node => node.type === 'Function').map(node => node.name)));
  const calls = [...bundle].flatMap(([file, entry]) => callsIn(entry.ast).map(call => ({ file, ...call })));
  const unsupportedNativeCalls = calls.filter(call => !functions.has(call.name) && !baselineNatives.has(call.name));
  const behaviorCalls = calls.filter(call => call.name === 'ChangeBehavior');
  const performCalls = calls.filter(call => ['Perform','Perofrm','PlayerPerform'].includes(call.name));
  const unknownBehaviors = behaviorCalls.filter(call => typeof call.args[1] === 'string' && !baselineBehaviors.has(call.args[1]));
  const unknownPerform = performCalls.filter(call => {
    const action = call.args[call.name === 'PlayerPerform' ? 0 : 1];
    return typeof action === 'string' && !baselinePerform.has(action.trim());
  });
  return { functionCount: functions.size, callbacks: [...functions].filter(name => /^On|^Scene_|_On/.test(name)),
    apiCalls: [...new Set(calls.map(call => call.name))].sort(), unsupportedNativeCalls,
    unknownBehaviors, unknownPerform, symbolicActors: calls.filter(call => ['GetChar','GetAnyChar'].includes(call.name) && ['flag','vip'].includes(call.args[0])),
    gameOverCalls: calls.filter(call => ['GameOver','GameCallBack'].includes(call.name)) };
}

const missions = [];
for (const map of manifest.maps.filter(map => /^sn\d\d$/.test(map.id) && Number(map.id.slice(2)) <= 20)) {
  const levelFile = `level/${map.id}_.pst`, level = await source(levelFile), levelCalls = callsIn(level.ast);
  const npcFiles = [...new Set(levelCalls.filter(call => call.name === 'AddNPC' && typeof call.args[0] === 'string').map(call => `level/${call.args[0].toLowerCase()}.pst`))];
  const onStart = level.ast.body.find(node => node.type === 'Function' && node.name === 'OnStart');
  const startNpcNames = onStart ? callsIn(onStart).filter(call => call.name === 'AddNPC').map(call => call.args[0]) : [];
  const bundle = await closure(levelFile);
  const metadata = JSON.parse(await readFile(new URL(map.metadata, original), 'utf8'));
  const waypointIds = new Set((metadata.waypoints?.points || []).map(point => point.id));
  const npcs = [];
  for (const file of npcFiles) {
    const entry = await source(file), globals = entry.globals;
    await closure(file, bundle);
    npcs.push({ file, name: globals.Name, model: globals.Model, team: globals.Team, spawn: globals.Spawn,
      spawnExists: waypointIds.has(globals.Spawn), hp: globals.HP, view: globals.View, think: globals.Think,
      primary: weapon(globals.Weapon), secondary: weapon(globals.Weapon2), initiallyAdded: startNpcNames.includes(file.slice(6, -4)) });
  }
  await closure(`${map.id}/${map.id}.pst`, bundle);
  const analysis = analyzeBundle(bundle), globals = level.globals;
  missions.push({ id: map.id, name: map.name, sourceComment: level.text.split(/\r?\n/).find(line => line.startsWith('//')),
    kind: npcFiles.length && onStart ? 'source-story' : 'arena-config-only', availableMap: map.available !== false,
    levelFile, rule: globals.Rule, roundTime: globals.RoundTime,
    player: { hp: globals.PlayerHP ?? null, spawn: globals.PlayerSpawn, spawnExists: waypointIds.has(globals.PlayerSpawn), direction: globals.PlayerSpawnDir,
      primary: weapon(globals.PlayerWeapon), secondary: weapon(globals.PlayerWeapon2) },
    npcCount: npcs.length, initialNpcCount: startNpcNames.length, npcs, ...analysis,
    explicitPositiveAssignment: [...level.text.matchAll(/\bgameover\s*=\s*1\s*;/g)].map(match => level.text.slice(0,match.index).split('\n').length),
    includes: [...bundle.keys()], missingModelsOrWeapons: npcs.filter(npc => !npc.spawnExists || !npc.primary.available || !npc.secondary.none && !npc.secondary.available).map(npc => npc.file),
    unsupportedWeaponModelsAtBaseline: [...new Set([weapon(globals.PlayerWeapon), weapon(globals.PlayerWeapon2), ...npcs.flatMap(npc => [npc.primary,npc.secondary])].filter(w => !w.supportedAtBaseline).map(w => w.model))] });
}
const result = { id: 'E-mission-catalog-audit-2026-11-04', observedAt: '2026-11-04', scope: 'meteor-original/scope.md, granted offline resource parsing; Meteor.exe not executed',
  method: 'Parse original imported PST AST, resolve includes, read globals without running callbacks, verify each raw source hash, compare with frozen v0.5.1 host capabilities.',
  note: 'Capability gaps are the baseline before this continuation. They are not claims about the final updated runtime. Map numbers are identifiers, not an inferred campaign order.',
  supportedWeaponPrefixesAtBaseline: [...supportedPrefixes], missions, sources: [...sourceRecords.values()].sort((a,b)=>a.file.localeCompare(b.file)) };
await writeFile(new URL('mission-catalog-audit-2026-11-04.json', import.meta.url), JSON.stringify(result,null,2)+'\n');
console.log(JSON.stringify({ storyMissions: missions.filter(m=>m.kind==='source-story').map(m=>({ id:m.id,name:m.name,rule:m.rule,npcs:m.npcCount,initial:m.initialNpcCount,positiveGameOver:m.explicitPositiveAssignment.length,weaponGaps:m.unsupportedWeaponModelsAtBaseline,apiGaps:[...new Set(m.unsupportedNativeCalls.map(c=>c.name))],behaviorGaps:[...new Set(m.unknownBehaviors.map(c=>c.args[1]))],performGaps:[...new Set(m.unknownPerform.map(c=>c.args[c.name==='PlayerPerform'?0:1]))] })), sourceFiles: result.sources.length },null,2));
