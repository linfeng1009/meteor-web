import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { decodeNativeText, parsePos, parseAct, NativeCombatController } from '../dist/native-combat.js';

const root = new URL('../dist/assets/native/combat/', import.meta.url);
const data = { poses: parsePos(decodeNativeText(await readFile(new URL('P0.POS', root)))),
  actions: parseAct(decodeNativeText(await readFile(new URL('character.act', root)))) };
const { poses, actions } = data;

test('original ACT resolves a requested command group through the current allowed list to its actual destination', () => {
  for (const [from, requested, actual] of [[264, 368, 369], [281, 293, 294], [299, 310, 313], [301, 310, 312], [231, 233, 234]]) {
    assert.equal(actions.canLink(from, requested), false, 'these are actual missing root-pose links');
    assert.equal(actions.resolveTransition(from, requested), actual);
    assert.ok(actions.links.get(from).has(actual));
    assert.equal(actions.groupIds.get(actual), actions.groupIds.get(requested));
  }
});

test('group resolution preserves original destination order, not exact requested membership or numeric order', () => {
  // Native 0055d130 scans the source +70 array first-to-last. Requesting the
  // second member is not permission to skip a source earlier destination.
  assert.equal(actions.resolveTransition(262, 264), 263);
  assert.equal(actions.resolveTransition(279, 281), 280);
  assert.equal(actions.resolveTransition(297, 314), 310);
  assert.equal(actions.resolveTransition(299, 310), 313);
});

test('a group does not grant a connection when the current ACT list has no member of that group', () => {
  for (const [from, requested] of [[262, 368], [279, 293], [295, 310], [260, 277]]) assert.equal(actions.resolveTransition(from, requested), null);
  assert.equal(actions.resolveTransition(368, 369), null, 'automatic POS links are not additional ACT permission');
  assert.equal(actions.resolveTransition(262, 987654), null);
});

test('queued sword, spear and blade rage group members preserve predecessor strikes and pay their command once', () => {
  for (const [weapon, from, requested, actual] of [['sword', 264, 368, 369], ['spear', 281, 293, 294], ['blade', 299, 310, 313]]) {
    const combat = new NativeCombatController(data, { weapon }), context = { id: `${weapon}-group`, poseId: requested, rage: 100 };
    let rage = 100, payments = 0;
    assert.equal(combat.attack({ poseId: from }), true);
    assert.equal(combat.attack({ poseId: requested, context, canStart: command => rage >= command.rage,
      onStart: command => { payments++; rage -= command.rage; } }), true);
    assert.equal(combat.queued, actual); assert.equal(combat.queuedMove, context); assert.equal(rage, 100);
    const seen = new Set(); let oldContact = false;
    for (let frame = 0; frame < 1200 && combat.busy; frame++) for (const state of combat.update(1 / 120, { grounded: true }).segments) {
      if (state.poseId === from && state.attacks.length) oldContact = true;
      if (!state.blend) seen.add(state.poseId);
    }
    assert.equal(oldContact, true, `${weapon}: preserve predecessor native contact window`);
    assert.ok(seen.has(actual), `${weapon}: actual allowed member must play`);
    assert.ok(combat.serial > 1); assert.equal(payments, 1); assert.equal(rage, 0);
    assert.equal(combat.currentMove, context, 'root command context survives its actual member and POS recovery');
  }
});

test('a grouped queued cost remains subject to start-time resource and hit interruption checks', () => {
  for (const action of ['spend', 'hit']) {
    const combat = new NativeCombatController(data, { weapon: 'spear' }); let rage = 100, payments = 0;
    combat.attack({ poseId: 281 });
    combat.attack({ poseId: 293, context: { rage: 100 }, canStart: c => rage >= c.rage, onStart: c => { payments++; rage -= c.rage; } });
    if (action === 'spend') rage = 0; else combat.react(93);
    combat.update(10, { grounded: true });
    assert.equal(payments, 0); assert.equal(combat.queued, null); assert.notEqual(combat.timeline.pose.id, 294);
  }
});

test('an idle group command starts at its original root rather than a combo-only member', () => {
  for (const [weapon, id] of [['sword', 368], ['spear', 293], ['blade', 310]]) {
    const combat = new NativeCombatController(data, { weapon });
    combat.attack({ poseId: id, context: { poseId: id } });
    assert.equal(combat.timeline.pose.id, id);
    assert.equal(actions.groups[actions.groupIds.get(id)][0], id);
  }
});

test('original direct A chains and held air recovery links survive group resolution without new ground links', () => {
  const combat = new NativeCombatController(data, { weapon: 'sword' });
  combat.attack({ poseId: 262 }); assert.equal(combat.attack({ poseId: 263 }), true);
  for (let i = 0; i < 180 && combat.timeline.pose.id === 262; i++) combat.update(1 / 60, { grounded: true });
  assert.equal(combat.timeline.pose.id, 263); assert.equal(combat.attack({ poseId: 264 }), true);
  for (let i = 0; i < 180 && combat.timeline.pose.id === 263; i++) combat.update(1 / 60, { grounded: true });
  assert.equal(combat.timeline.pose.id, 264);
  const air = new NativeCombatController(data, { weapon: 'sword' });
  air.attack({ air: true, poseId: 260 }); air.update(.7, { grounded: false });
  assert.equal(air.timeline.pose.id, 340); assert.equal(air.attack({ poseId: 277 }), false);
  assert.equal(air.attack({ air: true, poseId: 261 }), true); assert.equal(air.timeline.pose.id, 261);
  // The already accepted transition still uses the original connection after
  // host landing, matching the existing browser policy, not canceling it.
  for (let i = 0; i < 180 && air.timeline.pose.id === 261; i++) air.update(1 / 60, { grounded: true });
  assert.equal(air.timeline.pose.id, 341);
  assert.equal(poses.get(261).link, 341);
});
