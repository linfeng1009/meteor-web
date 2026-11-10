import { NATIVE_MOVE_CATALOG } from './native-move-catalog.js';
import { selectNativeMove } from './native-input.js';

const PERCENT = Math.fround(.01), THINK_MINIMUM = Math.fround(.1);
const directions = { f: 'up', b: 'down', l: 'left', r: 'right' };
const defaults = { Think: 100, Guard: 20, Attack1: 25, Attack2: 25, Attack3: 25 };
const short = (config, key) => Number.isFinite(Number(config?.[key])) ? Math.trunc(Number(config[key])) << 16 >> 16 : defaults[key];
export const NATIVE_NPC_COMBAT_PROVENANCE = Object.freeze({
  clock: '004fb770: base delay divided by max(signed Think×float32(.01),float32(.1)); one due decision then elapsed=0. 00503e00 combat basefloat32(.2),00503970 waitfloat32(.4).',
  initial: '004fda00: (rand()%1000)×float32(.0005).',
  weights: '005043d7..00504543: first rand()%100 selects Guard or gates attack by Guard+Attack1+Attack2+Attack3; a separate rand()%100 selects Attack1/2/3. Guard decisions set basefloat32(.4). No probability normalization.',
  commands: '004ff200 twelve original weapon tables;00500c90 uses one of17 air commands in controllerstate0, otherwise50% previous category/index reuse or random entry in requested category.',
  distance: '004fc9f0 uses strict distance²<maximumDistance², with ×3 for a non-ranged actor outside grounded states1/11.004fcb00→004fced0 checks the weapon angle tolerance before choosing a program. Native units×.08.',
  adapters: 'Web random samples produce15-bit draws; original PRNG sequence and exact OS clocks are not reproduced. Full AI evasion, jumping, looking, range switching and tactical states remain incomplete. Guard currently holds browser defense; the20% alternate005012a0 flag branch remains pending. Direction programs use the existing Web recognizer and original POS/ACT gates.'
});

export function nativeNpcInterval(baseDelay, config) {
  return baseDelay / Math.max(short(config, 'Think') * PERCENT, THINK_MINIMUM);
}

export function nativeNpcChoice(config, actionRoll, categoryRoll) {
  const guard = short(config, 'Guard');
  if (actionRoll < guard) return { kind: 'guard' };
  const first = short(config, 'Attack1'), second = short(config, 'Attack2');
  if (actionRoll >= guard + first + second + short(config, 'Attack3')) return { kind: 'wait' };
  return { kind: 'attack', category: categoryRoll < first ? 0 : categoryRoll < first + second ? 1 : 2 };
}

export function nativeNpcMove(actor, program, time = 0) {
  if (!/^[fblr]*$/.test(program)) return null;
  const air = !actor.grounded;
  const buffer = [...program].map((key, index) => ({ direction: directions[key], air,
    time: time - (program.length - index) * .01 }));
  return selectNativeMove(NATIVE_MOVE_CATALOG, { weapon: actor.weapon, weaponMode: actor.combat.weaponMode, air, buffer, time,
    poseId: actor.combat.timeline?.pose.id, movePoseId: actor.combat.currentMove?.poseId, busy: actor.combat.busy });
}

export function nativeNpcInRange(actor, target, profile) {
  if (!profile || !target) return false;
  const a = actor.root.position, b = target.root.position;
  const groundedState = actor.grounded && !actor.combat.busy;
  const radius = profile.maximumDistance * .08;
  if (!profile.ranged && groundedState && Math.abs(a.y - b.y) > 400 * .08) return false;
  return (a.x - b.x) ** 2 + (a.y - b.y) ** 2 + (a.z - b.z) ** 2 < radius ** 2 * (!profile.ranged && !groundedState ? 3 : 1);
}

export function nativeNpcFacing(actor, target, profile) {
  if (!profile || !target) return false;
  const a = actor.root.position, b = target.root.position;
  const desired = Math.atan2(b.x - a.x, b.z - a.z), delta = desired - actor.root.rotation.y;
  return Math.abs(Math.atan2(Math.sin(delta), Math.cos(delta))) <= profile.angleTolerance * Math.PI / 180;
}

export class NativeNpcCombat {
  constructor(data, { random = Math.random } = {}) {
    this.data = data; this.random = random; this.category = 0; this.index = 0; this.reset();
  }
  draw() { return Math.min(32767, Math.max(0, Math.floor(this.random() * 32768))); }
  reset() {
    this.elapsed = 0; this.baseDelay = Math.fround((this.draw() % 1000) * Math.fround(.0005));
    this.guard = false; this.engaged = false;
  }
  advance(dt, config, { hasTarget = false, paused = false } = {}) {
    if (paused || !Number.isFinite(dt) || dt <= 0) return false;
    const elapsed = this.elapsed + Math.fround(dt);
    this.elapsed = Math.fround(elapsed);
    if (elapsed < nativeNpcInterval(this.baseDelay, config)) return false;
    this.elapsed = 0;
    // 00503970→004fdf00 pushes00503e00 after discovery; that wait
    // invocation retains its .4 base and does not attack in the same step.
    const entering = hasTarget && !this.engaged;
    this.baseDelay = Math.fround(hasTarget && !entering ? .2 : .4);
    this.engaged = hasTarget;
    if (!hasTarget) this.guard = false;
    return hasTarget && !entering;
  }
  command(weapon, category, air = false) {
    if (air) return this.data.airCommands[this.draw() % this.data.airCommands.length];
    const profile = this.data.profiles[weapon]; if (!profile) return null;
    let index;
    if (this.draw() % 2 === 0) {
      category = this.category; index = Math.min(this.index, profile.commands[category].length - 1);
    } else index = this.draw() % profile.commands[category].length;
    this.category = category; this.index = index;
    return profile.commands[category][index];
  }
  choose(actor, { canAttack = () => true } = {}) {
    const actionRoll = this.draw() % 100;
    const gate = nativeNpcChoice(actor.scriptConfig, actionRoll, 0);
    const choice = gate.kind === 'attack' ? canAttack() ? nativeNpcChoice(actor.scriptConfig, actionRoll, this.draw() % 100) : { kind: 'wait' } : gate;
    this.guard = choice.kind === 'guard';
    if (this.guard) this.baseDelay = Math.fround(.4);
    return choice.kind === 'attack' ? { ...choice, program: this.command(actor.weapon, choice.category, !actor.grounded) } : choice;
  }
}
