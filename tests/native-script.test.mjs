import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { posix } from 'node:path';
import { NativeScriptVM, NativeScriptError, parsePst } from '../dist/native-script.js';

const root = new URL('../dist/assets/original/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));
const sources = new Map();
for (const script of manifest.scripts.filter(s => /\.(pst|h)$/i.test(s.source.path))) {
  sources.set(script.source.path.toLowerCase(), await readFile(new URL(script.utf8, root), 'utf8'));
}
for (const entry of manifest.maps) {
  const metadata = JSON.parse(await readFile(new URL(entry.metadata, root), 'utf8'));
  const info = metadata.files.find(f => f.path.endsWith('.pst'));
  const bytes = await readFile(new URL(entry.sceneScript, root));
  sources.set(info.path.toLowerCase(), new TextDecoder(info.parsed.encoding).decode(bytes));
}
const include = (name, from) => {
  const file = posix.normalize(posix.join(posix.dirname(from.replaceAll('\\', '/')), name.replaceAll('\\', '/'))).toLowerCase();
  const source = sources.get(file);
  assert.ok(source != null, `actual include ${file} must be imported`);
  return { source, file };
};
const load = (file, options = {}) => new NativeScriptVM(options).load(sources.get(file.toLowerCase()), { file, resolveInclude: include });

test('all preserved PST/header files parse and load their actual include dependencies', () => {
  assert.ok(sources.size >= 110);
  for (const [file, source] of sources) {
    assert.equal(parsePst(source, { file }).type, 'Program', file);
    new NativeScriptVM().load(source, { file, resolveInclude: include });
  }
});

test('the original Stalactite Cave mission starts its three declared NPC scripts', () => {
  const calls = [];
  const vm = load('level/sn01_.pst', { natives: { AddNPC: name => calls.push(name), GetChar: () => -1 } });
  assert.equal(vm.getGlobal('PlayerHP'), 1500);
  assert.equal(vm.getGlobal('Rule'), 10);
  vm.call('OnStart');
  assert.deepEqual(calls, ['npc01_01', 'npc01_02', 'npc01_03']);
  assert.equal(vm.call('OnUpdate'), 0, 'the real script returns early while the player is absent');
});

test('the original first cave NPC binds its runtime address and enters its scripted wait behavior', () => {
  const calls = [];
  const vm = load('level/npc01_01.pst', { natives: {
    GetSelf: address => { assert.equal(address, 17); return 101; },
    ChangeBehavior: (...args) => calls.push(args)
  } });
  vm.call('OnInit', [17]);
  vm.call('OnStart');
  assert.equal(vm.getGlobal('g_selfAddr'), 17);
  assert.equal(vm.getGlobal('g_self'), 101);
  assert.equal(vm.getGlobal('HP'), 1000);
  assert.deepEqual(calls, [[101, 'wait']]);
});

function sceneHost() {
  const items = new Map(), calls = [], indices = new Map();
  const id = value => {
    if (typeof value === 'number') return value;
    const key = value.toLowerCase(); if (!indices.has(key)) indices.set(key, indices.size + 1);
    return indices.get(key);
  };
  const props = value => { const index = id(value); if (!items.has(index)) items.set(index, new Map()); return items.get(index); };
  const natives = {
    MakeString: function (unused, prefix, number) { this.setArg(0, prefix + String(number).padStart(2, '0')); },
    SetSceneItem: (name, ...args) => { calls.push(['SetSceneItem', name, ...args]); props(name).set(args.slice(0, -1).join('/'), args.at(-1)); },
    GetSceneItem: (name, ...args) => args[0] === 'index' ? id(name) : props(name).get(args.join('/')) ?? 0,
    Output: (...args) => calls.push(['Output', ...args]),
    NetEvent: (...args) => calls.push(['NetEvent', ...args]),
    CreateEffect: (...args) => calls.push(['CreateEffect', ...args])
  };
  return { items, calls, natives, props, id };
}

test('the original cave scene loads all included libraries and initializes its real stone state', () => {
  const host = sceneHost(), vm = load('sn01/sn01.pst', { natives: host.natives });
  vm.call('Scene_OnLoad');
  vm.call('Scene_OnInit');
  assert.equal(vm.getGlobal('g_iStoneMaxHP'), 500);
  assert.equal(vm.getGlobal('g_iStoneHP').length, 32);
  assert.ok(vm.getGlobal('g_iStoneHP').every(hp => hp === 500));
  assert.ok(vm.getGlobal('g_bStoneAlive').every(alive => alive === 1));
  assert.equal(host.props('D_St01').get('attribute/collision'), 1);
  assert.equal(host.props('D_St32').get('attribute/damagevalue'), 50);
  assert.equal(host.props('D_itSt01').get('attribute/active'), 0);
  assert.ok(vm.hasFunction('D_BBox01_OnAttack'));
  assert.ok(vm.hasFunction('D_St32_OnAttack'));
});

test('an actual cave stone callback removes collision and activates its original item after damage', () => {
  const host = sceneHost(), vm = load('sn01/sn01.pst', { natives: host.natives });
  vm.call('Scene_OnLoad'); vm.call('Scene_OnInit');
  vm.call('D_St01_OnAttack', [host.id('D_St01'), 101, 500]);
  assert.equal(vm.getGlobal('g_iStoneHP')[0], 0);
  assert.equal(host.props('D_St01').get('attribute/collision'), 0);
  assert.equal(host.props('D_itSt01').get('attribute/active'), 1);
  assert.ok(host.calls.some(c => c[0] === 'CreateEffect' && c[1] === 'D_St01' && c[2] === 'StoneBRK'));
  host.props('D_St01').set('state', 3);
  // The host represents pose as a single getter value; the source setter also takes a blend argument.
  host.props('D_St01').set('pose', 1);
  vm.call('D_St01_OnIdle', [host.id('D_St01')]);
  assert.equal(vm.getGlobal('g_bStoneAlive')[0], 0);
  assert.equal(host.props('D_St01').get('attribute/active'), 0);
});

test('the real misspelled Perofrm API is exposed instead of silently corrected or skipped', () => {
  const events = [];
  const vm = load('level/sn01_.pst', { onEvent: event => events.push(event), natives: {
    GetChar: name => name === 'player' ? 0 : 1, Perform() {}, ChangeBehavior() {}, GetEnemy: () => -1,
    GetHP: () => 1000, GetMaxHP: () => 1000
  } });
  assert.throws(() => vm.call('OnUpdate'), error => error.code === 'UNKNOWN_NATIVE' && /Perofrm/.test(error.message));
  assert.ok(events.some(event => event.type === 'unknown-native' && event.name === 'Perofrm'));
  assert.equal(vm.getGlobal('trg0'), 0, 'execution must stop at the unsupported call');
});

test('native API requirements include exact names and source locations from included files', () => {
  const vm = load('sn01/sn01.pst');
  const requirements = vm.getNativeRequirements();
  assert.ok(requirements.find(r => r.name === 'MakeString' && r.locations.length > 0));
  assert.ok(requirements.find(r => r.name === 'SetSceneItem'));
  assert.equal(requirements.some(r => r.name === 'StoneOnAttack'), false, 'script functions are not host API requirements');
});

test('for/while loops, lexical locals, integer division and short circuit operators execute without JavaScript evaluation', () => {
  const vm = new NativeScriptVM().load(`
    int sum=0; int counters[5];
    Main() {
      for(int i=0; i<5; i++) { counters[i]=i; if(i==2) continue; sum+=i; }
      int j=0; while(j<10) { j++; if(j==3) break; }
      if(0 && MissingAPI()) sum=999;
      if(1 || MissingAPI()) sum+=j;
      return sum + 5/2;
    }`);
  assert.equal(vm.call('Main'), 13);
  assert.deepEqual(vm.getGlobal('counters'), [0, 1, 2, 3, 4]);
});

test('a native output reference evaluates an array index once', () => {
  const vm = new NativeScriptVM({ natives: { MakeString: function (old, prefix) { this.setArg(0, prefix); } } }).load(`
    string names[2]; int i=0;
    Main(){ MakeString(names[i++], "original"); return i; }
  `);
  assert.equal(vm.call('Main'), 1);
  assert.deepEqual(vm.getGlobal('names'), ['original', '']);
});

test('unknown native APIs, infinite loops, bounds violations and arbitrary property access fail explicitly', () => {
  assert.throws(() => new NativeScriptVM().load('Main(){ Unknown(1); }').call('Main'), error => error.code === 'UNKNOWN_NATIVE');
  assert.throws(() => new NativeScriptVM({ maxSteps: 100 }).load('Main(){ while(1){} }').call('Main'), error => error.code === 'STEP_LIMIT');
  assert.throws(() => new NativeScriptVM().load('int a[2]; Main(){ a[2]=1; }').call('Main'), error => error.code === 'ARRAY_BOUNDS');
  assert.throws(() => parsePst('Main(){ constructor.constructor("return process")(); }'), NativeScriptError);
});
