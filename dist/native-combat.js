// Native Meteor Blade POS/ACT playback. These parsers read the original files;
// no attack frame ranges, hit intervals, animation speeds or links are synthesized.
// Evidence: work/meteor-original/evidence/E-native-combat.md.
const BLOCK_TYPES = new Set(['pose', 'blend', 'action', 'attack', 'drag', 'nextpose']);
import { NATIVE_MOVE_CATALOG } from './native-move-catalog.js';
const scalar = value => /^[-+]?\d+(?:\.\d*)?(?:e[-+]?\d+)?$/i.test(value) ? Number(value) : value;
const values = text => [...text.matchAll(/"([^"]*)"|([-+]?\d+(?:\.\d*)?(?:e[-+]?\d+)?|[^\s,=]+)/gi)].map(m => m[1] ?? scalar(m[2]));
const includes = (block, frame) => frame >= block.start && frame < block.end + 1;
const windowData = node => ({ ...node.fields, bones: Array.isArray(node.fields.bone) ? node.fields.bone : node.fields.bone ? [node.fields.bone] : [], line: node.line });
// 00575180 initializes pose+50 to float32(0.12); NextPose.Time overwrites it.
export const NATIVE_DEFAULT_BLEND_TIME = Math.fround(.12);
// 004dd070: a destination in the current weapon's guard-hit list uses .01s.
export const NATIVE_GUARD_BLEND_TIME = Math.fround(.01);
const phaseAt = (pose, frame) => [...pose.phases].reverse().find(p => p.type === 'action' && includes(p, frame)) || [...pose.phases].reverse().find(p => p.type === 'blend' && includes(p, frame));

export function decodeNativeText(buffer) {
  // The supplied 2002 POS/ACT files contain Traditional Chinese Big5 comments.
  return new TextDecoder('big5').decode(buffer instanceof ArrayBuffer ? new Uint8Array(buffer) : buffer);
}

export function parsePos(text, { file = 'P0.POS' } = {}) {
  const poses = new Map(), stack = [], lines = text.replace(/^\uFEFF/, '').split(/\r?\n/);
  let pending = null, lastField = null;
  for (let i = 0; i < lines.length; i++) {
    const raw = lines[i], commentAt = raw.indexOf('#');
    const comment = commentAt < 0 ? '' : raw.slice(commentAt + 1).trim();
    const clean = (commentAt < 0 ? raw : raw.slice(0, commentAt)).trim();
    if (!clean) continue;
    const fragments = clean.split(/([{}])/).map(s => s.trim()).filter(Boolean);
    for (const line of fragments) {
      if (line === '{') {
        if (!pending) throw new Error(`${file}:${i + 1}: Block without a name`);
        const node = { ...pending, fields: {}, blocks: [] }; pending = null;
        if (stack.length) stack[stack.length - 1].blocks.push(node);
        stack.push(node); lastField = null; continue;
      }
      if (line === '}') {
        const node = stack.pop(); if (!node) throw new Error(`${file}:${i + 1}: Unmatched closing brace`);
        node.endLine = i + 1;
        if (node.type === 'pose') {
          const f = node.fields, phases = node.blocks.filter(b => b.type === 'blend' || b.type === 'action').map(b => ({ type: b.type, ...b.fields, line: b.line }));
          const pose = { id: node.id, label: node.label, source: f.source ?? 0, start: f.start, end: f.end, loopStart: f.loopstart, loopEnd: f.loopend, link: f.link, phases, attacks: node.blocks.filter(b => b.type === 'attack').map(windowData), drags: node.blocks.filter(b => b.type === 'drag').map(windowData), cancels: node.blocks.filter(b => b.type === 'nextpose').map(windowData), raw: node, evidence: { file, line: node.line, endLine: node.endLine } };
          pose.valid = Number.isFinite(pose.start) && Number.isFinite(pose.end) && pose.end >= pose.start;
          // 0057bef0: first Action.Start; if absent (or exactly End), Start.
          const actionStart = Math.min(pose.end, ...phases.filter(p => p.type === 'action').map(p => p.start));
          pose.entryFrame = actionStart === pose.end ? pose.start : actionStart;
          pose.blendTime = pose.cancels.at(-1)?.time ?? NATIVE_DEFAULT_BLEND_TIME;
          if (poses.has(pose.id)) throw new Error(`${file}:${node.line}: Duplicate pose ${pose.id}`);
          poses.set(pose.id, pose);
        }
        lastField = null; continue;
      }
      const poseHeader = line.match(/^Pose\s+(\d+)\s*$/i);
      if (poseHeader) { pending = { type: 'pose', id: Number(poseHeader[1]), label: comment, line: i + 1 }; continue; }
      if (/^\w+$/.test(line) && (BLOCK_TYPES.has(line.toLowerCase()) || lines.slice(i + 1).find(l => l.trim())?.trim().startsWith('{'))) {
        pending = { type: line.toLowerCase(), line: i + 1 }; continue;
      }
      const node = stack[stack.length - 1];
      if (!node) throw new Error(`${file}:${i + 1}: Statement outside a pose`);
      if (line.startsWith('"') && lastField) {
        const current = node.fields[lastField]; node.fields[lastField] = [...(Array.isArray(current) ? current : [current]), ...values(line)]; continue;
      }
      const match = line.match(/^(\w+)\s*(?:=\s*)?(.*)$/);
      if (!match) throw new Error(`${file}:${i + 1}: Invalid field`);
      lastField = match[1].toLowerCase(); const parsed = values(match[2]);
      node.fields[lastField] = parsed.length === 1 ? parsed[0] : parsed;
    }
  }
  if (stack.length || pending) throw new Error(`${file}: Truncated pose block`);
  return poses;
}

// The EXE compiles every pose into shared per-source frame flags. For each
// pose it writes all Blend ranges, then all Action ranges (0055c580), so an
// Action overrides an overlapping Blend regardless of text block order.
const compiledFrames = new WeakMap();
export function compileNativeFrameTable(poses) {
  if (compiledFrames.has(poses)) return compiledFrames.get(poses);
  const table = new Map();
  for (const pose of poses.values()) if (pose.valid) {
    const size = Math.max(table.get(pose.source)?.size || 0, pose.end + 1);
    if (size > 200000) throw new Error('Native pose frame range is excessive');
    table.set(pose.source, { size });
  }
  for (const [source, { size }] of table) table.set(source, { speed: new Float32Array(size).fill(1), blend: new Uint8Array(size).fill(1) });
  for (const pose of poses.values()) if (pose.valid) for (const type of ['blend', 'action']) for (const p of pose.phases) if (p.type === type) {
    const data = table.get(pose.source);
    for (let frame = Math.max(pose.start, p.start); frame <= Math.min(pose.end, p.end); frame++) {
      data.speed[frame] = p.speed ?? 1; data.blend[frame] = Number(type === 'blend');
    }
  }
  compiledFrames.set(poses, table); return table;
}

export function parseAct(text, { file = 'character.act' } = {}) {
  const clean = text.replace(/#[^\r\n]*/g, ''), groups = [], links = new Map(), groupIds = new Map();
  for (const match of clean.matchAll(/\bgroup\s*\(\s*(\d+)(?:\s*-\s*(\d+))?\s*\)/gi)) {
    const start = Number(match[1]), end = Number(match[2] || start);
    if (end < start || end - start > 10000) throw new Error(`${file}: Invalid group range`);
    groups.push(Array.from({ length: end - start + 1 }, (_, index) => start + index));
  }
  for (const [groupId, members] of groups.entries()) for (const id of members) groupIds.set(id, groupId);
  for (const match of clean.matchAll(/(?:^|\n)\s*(\d+)\s*\(\s*([\d,\s]+)\)/g)) {
    const id = Number(match[1]), targets = [...match[2].matchAll(/\d+/g)].map(m => Number(m[0]));
    if (links.has(id)) throw new Error(`${file}: Duplicate links for pose ${id}`);
    links.set(id, new Set(targets));
  }
  return { groups, links, groupIds, canLink: (from, to) => links.get(from)?.has(to) || false,
    // 0055d020/0055d130 receive a group id, then scan the current pose's
    // allowed destinations in source order. The first destination whose
    // pose+68 group matches becomes the actual queued pose (+624).
    // This does not make arbitrary members of a group mutually linkable.
    resolveTransition(from, requested) {
      const groupId = groupIds.get(requested); if (groupId == null) return null;
      for (const target of links.get(from) || []) if (groupIds.get(target) === groupId) return target;
      return null;
    }
  };
}

// These weapon groups are explicitly named in P0.POS and character.act.
// Stance IDs are cross-checked against lxres.com/LiuXingBiJi/1758.html; they are
// not claimed to have been recovered from the Windows executable.
export const NATIVE_WEAPONS = Object.freeze({
  dart: { weaponId: 1, model: 'w3_0', stance: 1, guard: 11, basic: [200], air: [202], special: [203, 551], family: [200, 205] },
  musket: { weaponId: 3, model: 'w2_0', stance: 2, guard: 12, basic: [206], air: [], special: [208, 215, 216, 217], family: [206, 208] },
  wheel: { weaponId: 2, model: 'w6_0', stance: 3, guard: 13, basic: [218], air: [], special: [224, 552, 554], family: [218, 225] },
  dual: { weaponId: 4, model: 'w8_0r', stance: 4, guard: 14, basic: [230, 231, 232], air: [226, 227], special: [244, 556, 557], family: [226, 244] },
  dagger: { weaponId: 5, model: 'w1_0', stance: 5, guard: 15, basic: [248, 249], air: [245, 246, 247], special: [558, 559], family: [245, 259] },
  sword: { weaponId: 6, model: 'w0_0', stance: 6, guard: 16, basic: [262, 263, 264], air: [260, 261], special: [560, 561], family: [260, 278] },
  spear: { weaponId: 7, model: 'w7_0', stance: 7, guard: 17, basic: [279, 280, 281], air: [338], special: [562, 563, 571], family: [279, 294] },
  blade: { weaponId: 8, model: 'w5_0', stance: 8, guard: 18, basic: [295, 296, 297], air: [338], special: [565, 572, 573], family: [295, 314] },
  hammer: { weaponId: 9, model: 'w4_0', stance: 9, guard: 19, basic: [315], air: [338], special: [325, 566, 567], family: [315, 328] },
  knuckle: { weaponId: 51, model: 'w10_0r', stance: 400, guard: 480, basic: [407, 408, 409], air: [405, 406], special: [416, 421, 489], family: [405, 426] },
  qiankun: { weaponId: 47, model: 'w9_0r', stance: 401, guard: 481, basic: [432, 433, 434], air: [458], special: [451, 568, 570], family: [430, 456],
    modes: { blade: { stance: 401, basic: [432, 433, 434] }, spear: { stance: 402, basic: [442] }, sheath: { stance: 403, basic: [520, 521] } } },
  ninja: { weaponId: 55, model: 'w11_0', stance: 404, guard: 482, basic: [461, 462], air: [478, 479], special: [468, 473, 474, 535, 540], family: [461, 479] }
});
export const NATIVE_LOCOMOTION = Object.freeze({ idle: 0, walk: 140, run: 144, jumpStart: 151, jumpAir: 152, fall: 180, hit: 90, dead: 117 });
// Original weapon-state initializers, matched by their guard stance (+18).
// 004dce50 maps a CRT15-bit draw through4/32767 for direction0: usually
// slots0..3, with slot4 at32767. Directions1/2/3 use slots4/5/6.
// Draws use Web RNG; the native CRT seed/sequence is not reproduced here.
export const NATIVE_GUARD_REACTIONS = Object.freeze(Object.fromEntries(Object.entries({
  dart: [40, 41, 42, 43, 77, 78, 79], musket: [44, 45, 46, 47, 77, 78, 79], wheel: [48, 49, 50, 51, 77, 78, 79], dual: [52, 53, 54, 55, 77, 78, 79],
  dagger: [56, 57, 58, 59, 83, 84, 85], sword: [60, 61, 62, 63, 80, 81, 82],
  spear: [64, 65, 66, 67, 86, 87, 88], blade: [68, 69, 70, 71, 80, 81, 82],
  hammer: [72, 73, 74, 75, 77, 78, 79], knuckle: [490, 491, 492, 493, 513, 514, 515],
  qiankun: [494, 495, 496, 497, 498, 499, 500], ninja: [516, 517, 518, 519, 475, 476, 477]
}).map(([weapon, poses]) => [weapon, Object.freeze(poses)])));

// 004dc060 returns minus native matrix row1 as facing. In Web x/z space
// native x/y is (x,-z), so positive signed angles point to the actor's right.
// POS names describe the selected reaction, not the attacker's side.
export function nativeHitAngle(attackerPosition, targetPosition, targetYaw = 0) {
  const dx = attackerPosition.x - targetPosition.x, dz = attackerPosition.z - targetPosition.z;
  const length = Math.hypot(dx, dz); if (length < 1e-6) return 0;
  const x = Math.sin(targetYaw), z = Math.cos(targetYaw);
  const angle = Math.acos(Math.max(-1, Math.min(1, (x * dx + z * dz) / length)));
  return z * dx - x * dz < 0 ? -angle : angle;
}
export function nativeHitSelection(attack, angle = 0) {
  // Actual PE doubles at005ab628/638 and005ab620/630, rather than PI/4.
  const low = .7853975, high = 2.3561924999999997;
  const direction = angle > -low && angle < low ? 0 : angle > -high && angle <= -low ? 1 : angle >= low && angle < high ? 2 : 3;
  const field = ['targetposefront', 'targetposeright', 'targetposeleft', 'targetposeback'][direction];
  // 005754d0 replaces unset(-1) directional fields with TargetPose.
  const value = attack[field];
  return { poseId: Number(value == null || value === -1 ? attack.targetpose ?? -1 : value) & 0xfff, direction, field, angle };
}
export function nativeGuardPose(weapon, direction, random = Math.random) {
  const poses = NATIVE_GUARD_REACTIONS[weapon]; if (!poses) return null;
  const draw = direction === 0 ? Math.min(32767, Math.max(0, Math.trunc(random() * 32768))) : 0;
  const index = direction === 0 ? Math.trunc(draw * (4 / 32767)) : direction + 3;
  return poses[index] ?? null;
}
// POS authors fall -> prone links; EXE 004d01f0 maps 113 -> 120 and other
// prone states -> 119. Only the waiting time is a provisional Web adapter.
export const NATIVE_REACTION_ADAPTER = Object.freeze({ downHold: .65, recover: Object.freeze({ 112: 119, 113: 120 }) });
// External action-table corroboration, recorded separately from local PE evidence.
// Compatibility view for inspectors. Runtime selection also checks stance,
// predecessor, rage and pending-effect conditions in the full catalog.
export const NATIVE_DIRECTIONAL = Object.freeze(Object.fromEntries(Object.keys(NATIVE_WEAPONS).map(weapon => [weapon,
  Object.freeze(Object.fromEntries(NATIVE_MOVE_CATALOG.filter(move => move.weapon === weapon && move.stance === 'ground' && move.input.length > 1 && !move.continuationOf)
    .map(move => [move.input.slice(0, -1).join(','), move.poseId])))
])));

export function summarizeNativeMove(pose, { fps = 30, actions = null } = {}) {
  const boundaries = new Set([pose.start, pose.end]);
  for (const phase of pose.phases) { if (phase.start > pose.start && phase.start <= pose.end) boundaries.add(phase.start); if (phase.end + 1 > pose.start && phase.end < pose.end) boundaries.add(phase.end + 1); }
  const sorted = [...boundaries].sort((a, b) => a - b); let duration = 0;
  for (let i = 0; i < sorted.length - 1; i++) {
    const phase = [...pose.phases].reverse().find(p => includes(p, sorted[i]));
    duration += (sorted[i + 1] - sorted[i]) / (fps * (phase?.speed ?? 1));
  }
  return { id: pose.id, name: pose.label, source: pose.source, start: pose.start, end: pose.end, frameCount: pose.end - pose.start + 1, fps, duration, attacks: pose.attacks, phases: pose.phases, cancel: pose.cancels, links: actions ? [...(actions.links.get(pose.id) || [])] : [], evidence: pose.evidence };
}

// Arithmetic recovered from original x86, not an estimated gameplay formula.
// 004d5e30: effective stat; 004d61c0: pose modifiers; 004d6190/004d5f70:
// defense and team factor; 004af630: victim rage; 004d4d30: clamping.
export const NATIVE_PERCENT = Math.fround(.01);
// 004f3380 packs each float as uint16(trunc(float32(value)*100+.5));
// 004af630 selects the target or defense half, and 004f3f50/004f4010
// multiply its unsigned integer by float32(.01), storing another float32.
export function nativeReactionParameters(attack, { guarded = false } = {}) {
  const wireFloat = value => Math.fround((Math.trunc(Math.fround(value) * 100 + .5) & 0xffff) * NATIVE_PERCENT);
  return { motionScale: wireFloat((guarded ? attack.defensemove : attack.targetmove) ?? 1),
    duration: wireFloat((guarded ? attack.defensevalue : attack.targetvalue) ?? 0) };
}
const modifierApplies = (effect, statId) => effect.words[2] === statId && effect.words[4] === -1 && (effect.words[0] & 2) !== 0 && effect.words[1] === 0;
function modifierDelta(effect, basis) { return effect.mode === 0 ? effect.value : effect.mode === 1 ? Math.trunc((effect.value * NATIVE_PERCENT - 1) * basis) : 0; }
export function nativeEffectiveStat(statId, underlying, records = []) {
  let delta = 0; for (const record of records) for (const effect of record?.effects || []) if (modifierApplies(effect, statId)) delta += modifierDelta(effect, underlying);
  return Math.max(0, underlying + delta);
}
export function nativePoseAttack(effectiveAttack, moveRecord) {
  let delta = 0; for (const effect of moveRecord?.effects || []) if (modifierApplies(effect, 3)) delta += modifierDelta(effect, effectiveAttack);
  return effectiveAttack + delta;
}
export function calculateNativeDamage({ attack, defense, moveRecord, factor = 1, guarded = false, sameTeam = false }) {
  const poseAttack = nativePoseAttack(attack, moveRecord), beforeScale = poseAttack - defense;
  const damage = guarded ? 0 : Math.max(0, Math.trunc(beforeScale * Math.fround(factor)));
  return { poseAttack, defense, beforeScale, factor, damage, victimRage: guarded ? !sameTeam && beforeScale > 0 ? Math.trunc(14 * beforeScale / 500) : 0 : Math.floor(14 * damage / 100), guarded };
}
export function createNativeDamageResolver(data) {
  return context => {
    const { attacker, target, poseId, guarded = false } = context, moveRecord = data.moveRecords.get(poseId); if (!moveRecord) return null;
    const weapon = actor => actor.weaponRecord || data.weaponRecords.get(NATIVE_WEAPONS[actor.weapon]?.model);
    const attack = nativeEffectiveStat(3, attacker.nativeStats?.[3] ?? 0, [weapon(attacker), ...(attacker.activeItems || [])]);
    const defense = nativeEffectiveStat(4, target.nativeStats?.[4] ?? 0, [weapon(target), ...(target.activeItems || [])]);
    const sameTeam = ((attacker.teamMask ?? (attacker.hero ? 1 : 2)) & (target.teamMask ?? (target.hero ? 1 : 2))) !== 0;
    context.nativeResult = calculateNativeDamage({ attack, defense, moveRecord, factor: sameTeam ? .2 : 1, guarded, sameTeam });
    return context.nativeResult.damage;
  };
}

// Scene OnAttack receives the attacker's pose attack directly. The original
// 004af570 -> 005643f0 -> 00560500 path applies no victim defense/team factor.
// Evidence: work/meteor-original/evidence/E-native-machine-damage.json.
export function createNativeSceneDamageResolver(data) {
  return context => {
    const { attacker } = context, moveRecord = data.moveRecords.get(context.state?.poseId ?? context.poseId);
    if (!moveRecord) return null;
    const weapon = attacker.weaponRecord || data.weaponRecords.get(NATIVE_WEAPONS[attacker.weapon]?.model);
    const attack = nativeEffectiveStat(3, attacker.nativeStats?.[3] ?? 0, [weapon, ...(attacker.activeItems || [])]);
    return nativePoseAttack(attack, moveRecord);
  };
}

export class NativePoseTimeline {
  constructor(pose, { fps = 30, loop = false, sampleRoot = null, scale = .08, frameTable = null } = {}) {
    if (!pose?.valid) throw new Error(`Pose ${pose?.id ?? '?'} has no animation frames`);
    this.pose = pose; this.fps = fps; this.loop = loop; this.sampleRoot = sampleRoot; this.scale = scale;
    this.frame = pose.start; this.finished = false; this.elapsed = 0;
    this.frameTable = frameTable;
  }
  speedAt(frame = this.frame) {
    return Math.max(.01, this.frameTable?.get(this.pose.source)?.speed[Math.floor(frame)] ?? phaseAt(this.pose, frame)?.speed ?? 1);
  }
  isBlendFrame(frame = this.frame) { return this.frameTable?.get(this.pose.source)?.blend[Math.floor(frame)] === 1 || !this.frameTable && phaseAt(this.pose, frame)?.type !== 'action'; }
  advance(dt, { stopAtFrame = Infinity } = {}) {
    const previous = this.frame, pose = this.pose, wasFinished = this.finished;
    let remaining = Math.max(0, dt), loops = 0; const traversed = [];
    const sampleBefore = this.sampleRoot?.(pose.source, previous);
    while (remaining > 1e-7 && !this.finished && loops++ < 10000) {
      const looping = this.loop && Number.isFinite(pose.loopStart) && Number.isFinite(pose.loopEnd);
      const terminal = looping ? pose.loopEnd : pose.end;
      // 0055d560 mode0 resets to LoopStart when it passes LoopEnd;
      // mode1 finishes at End. Never interpolate into the next pose's frame.
      // A one-frame loop holds one transform and consumes time, rather than
      // producing a false up/down velocity that can suspend an actor forever.
      if (looping && this.frame >= terminal - 1e-7) {
        traversed.push({ from:this.frame, to:this.frame, timeFrom:Math.max(0, dt) - remaining, timeTo:Math.max(0, dt) }); this.frame = pose.loopStart; remaining = 0; break;
      }
      let boundary = Math.min(terminal, stopAtFrame);
      if (this.frameTable) boundary = Math.min(boundary, Math.floor(this.frame + 1e-6) + 1);
      for (const p of pose.phases) {
        if (p.start > this.frame + 1e-6) boundary = Math.min(boundary, p.start);
        if (p.end + 1 > this.frame + 1e-6) boundary = Math.min(boundary, p.end + 1);
      }
      const before = this.frame, timeFrom = Math.max(0, dt) - remaining, speed = this.speedAt(), seconds = (boundary - this.frame) / (this.fps * speed);
      if (remaining < seconds - 1e-8) { this.frame += remaining * this.fps * speed; remaining = 0; }
      else { this.frame = boundary; remaining -= Math.max(0, seconds); }
      traversed.push({ from: before, to: this.frame, timeFrom, timeTo: Math.max(0, dt) - remaining });
      if (this.frame >= terminal - 1e-6) {
        if (looping) {
          if (remaining > 1e-7) { this.frame = pose.loopStart; remaining = 0; }
        }
        else { this.frame = pose.end; this.finished = true; }
      }
      if (!this.finished && this.frame >= stopAtFrame - 1e-6) break;
    }
    this.elapsed += Math.max(0, dt) - remaining;
    const sampleAfter = this.sampleRoot?.(pose.source, this.frame);
    const rootDelta = sampleBefore && sampleAfter ? { x: (sampleAfter.x - sampleBefore.x) * this.scale, y: (sampleAfter.y - sampleBefore.y) * this.scale, z: (sampleAfter.z - sampleBefore.z) * this.scale } : { x: 0, y: 0, z: 0 };
    if (!traversed.length && !wasFinished) traversed.push({ from: previous, to: previous, timeFrom: 0, timeTo: Math.max(0, dt) - remaining });
    const crossed = block => traversed.some(range => range.from < block.end + 1 && range.to >= block.start);
    return { poseId: pose.id, source: pose.source, previousFrame: previous, frame: this.frame, frameIntervals: traversed, finished: this.finished, attacks: pose.attacks.map((attack, index) => ({ ...attack, index })).filter(crossed), drags: pose.drags.filter(crossed), cancel: pose.cancels.some(w => includes(w, this.frame)), rootDelta, consumed: Math.max(0, dt) - remaining, remaining };
  }
  get canCancel() { return this.pose.cancels.some(w => includes(w, this.frame)); }
}

export class NativeCombatController {
  constructor(data, { weapon = 'sword', fps = 30, sampleRoot = null, scale = .08 } = {}) {
    this.data = data; this.weapon = weapon; this.fps = fps; this.sampleRoot = sampleRoot; this.scale = scale;
    this.timeline = null; this.queued = null; this.serial = 0; this.combo = 0;
    this._queuedRequest = null; this._activeMove = null; this._attackChain = false; this._motionChain = false; this._inputPose = null;
    this._reaction = null;
    this._effectElapsed = 0;
    this.weaponMode = 'blade';
    this.frameTable = compileNativeFrameTable(data.poses); this._transition = null;
  }
  setWeapon(name) {
    if (!NATIVE_WEAPONS[name]) throw new Error(`Unknown native weapon ${name}`);
    this.weapon = name; this.timeline = null; this.queued = null; this.combo = 0;
    this.weaponMode = 'blade';
    this._queuedRequest = null; this._activeMove = null; this._attackChain = false; this._motionChain = false; this._inputPose = null;
    this._reaction = null;
    this._transition = null;
  }
  _hasAttack(id, visited = new Set()) {
    if (visited.has(id)) return false; visited.add(id);
    const pose = this.data.poses.get(id);
    return !!pose?.attacks.length || (pose?.link != null && this._hasAttack(pose.link, visited));
  }
  _queueFrame() {
    const { pose, frame } = this.timeline;
    // 0055d130 accepts the command in NextPose's interval; state2 in
    // 0055d560 keeps the old animation until a compiled Blend frame (or End).
    const armed = this.timeline.canCancel ? frame : pose.cancels.find(w => w.start > frame)?.start;
    if (armed == null) return pose.end;
    for (let candidate = Math.ceil(armed - 1e-6); candidate < pose.end; candidate++) if (this.timeline.isBlendFrame(candidate)) return candidate;
    return pose.end;
  }
  _canCancelFor(request) { return !this._transition && this.timeline.frame >= request.transitionFrame - 1e-6; }
  _start(request, { linked = false } = {}) {
    const pose = this.data.poses.get(request.id); if (!pose?.valid) return false;
    // Queued requests reserve no resource. Re-check and pay only when the
    // requested pose actually starts; automatic POS links pay no second cost.
    if (!linked && (request.canStart?.(request.context) === false || request.onStart?.(request.context) === false)) return false;
    this.timeline = new NativePoseTimeline(pose, { fps: this.fps, loop: request.loop, sampleRoot: this.sampleRoot, scale: this.scale, frameTable: this.frameTable });
    this._effectElapsed = 0;
    this._transition = null;
    this.serial++; this.queued = null; this._queuedRequest = null;
    if (!linked) {
      this._reaction = null;
      this._activeMove = request.context ?? null;
      this._attackChain = request.attack || this._hasAttack(request.id);
      this._inputPose = this._attackChain ? request.id : null; this._motionChain = request.motion === true;
      if (NATIVE_WEAPONS[this.weapon].modes?.[request.context?.changesMode]) this.weaponMode = request.context.changesMode;
    }
    const index = NATIVE_WEAPONS[this.weapon].basic.indexOf(request.id); this.combo = index >= 0 ? index + 1 : 0;
    return true;
  }
  _startTransition(request, { linked = false } = {}) {
    const old = this.timeline, from = old && { source: old.pose.source, frame: old.frame, poseId: old.pose.id };
    const duration = Math.max(0, old?.pose.blendTime ?? NATIVE_DEFAULT_BLEND_TIME);
    if (!this._start(request, { linked })) return false;
    // Native queued combos blend to first Action (0055d450); automatic POS
    // links blend to Start (0055d260). No attack time elapses while blending.
    this.timeline.frame = linked ? this.timeline.pose.start : this.timeline.pose.entryFrame;
    if (from && duration > 0) this._transition = { from, to: { source: this.timeline.pose.source, frame: this.timeline.frame, poseId: request.id }, duration, elapsed: 0 };
    return true;
  }
  play(id, { loop = false, force = false, context = null, canStart = null, onStart = null, attack = false, motion = false } = {}) {
    const pose = this.data.poses.get(id); if (!pose?.valid) return false;
    if (!force && this.reacting) return false;
    const request = { id, loop, context, canStart, onStart, attack, motion };
    // 004cbf10 enters controller state6;004cff40 explicitly accepts attacks
    // from state6. This is a locomotion interrupt, not an invented ACT link.
    if(!force&&attack&&this._motionChain&&this._activeMove?.kind==='dash')return this._start(request);
    if (!force && this.busy) {
      const current = this.timeline.pose;
      // Air recovery poses retain the input pose's ACT links (e.g. 260 ->
      // 340 can still receive the second air strike 261). No link is invented.
      const recovery = !current.attacks.length && Number.isFinite(current.loopStart);
      const from = recovery && !this.data.actions.links.has(current.id) ? this._inputPose : current.id;
      const resolved = this.data.actions.resolveTransition ? this.data.actions.resolveTransition(from, id) : this.data.actions.canLink(from, id) ? id : null;
      if (resolved == null) return false;
      request.id = resolved;
      request.transitionFrame = recovery ? this.timeline.frame : this._queueFrame();
      if (!this._canCancelFor(request)) { this.queued = request.id; this._queuedRequest = request; return true; }
      return this._startTransition(request);
    }
    return this._start(request);
  }
  react(id, { motionScale = 1, duration = 0, guarded = false, fromPose = null } = {}) {
    // A light hit must not snap an already prone character back upright.
    if (this._reaction?.phase === 'down' || this._reaction?.phase === 'recover') return false;
    const pose = this.data.poses.get(id), old = this.timeline;
    const from = fromPose || old && { source: old.pose.source, frame: old.frame, poseId: old.pose.id };
    if (!pose?.valid || !this.play(id, { force: true })) return false;
    this._attackChain = false; this._inputPose = null;
    // 004f3380 packs native Move/Value*100; 004af630/004f3f50
    // unpack them. 004d03f0 stores Move at+37c for 004ce850's
    // d_base velocity multiplier; Value reaches animation+608 duration.
    this._reaction = { poseId: id, phase: guarded ? 'guard' : 'hit', holdRemaining: NATIVE_REACTION_ADAPTER.downHold,
      motionScale: Math.max(0, Number(motionScale) || 0), remainingDuration: Math.max(0, Number(duration) || 0) };
    const blendTime = NATIVE_GUARD_REACTIONS[this.weapon]?.includes(id) ? NATIVE_GUARD_BLEND_TIME : NATIVE_DEFAULT_BLEND_TIME;
    if (from) this._transition = { from, to: { source: pose.source, frame: pose.start, poseId: id }, duration: blendTime, elapsed: 0 };
    return true;
  }
  attack({ air = false, poseId = null, context = null, canStart = null, onStart = null } = {}) {
    const options = { attack: true, context, canStart, onStart };
    if (poseId != null) return this.play(poseId, options);
    const profile = NATIVE_WEAPONS[this.weapon];
    const sequence = air ? profile.air : profile.modes?.[this.weaponMode]?.basic || profile.basic;
    const current = this.busy ? this._inputPose : null, index = sequence.indexOf(current), next = index >= 0 && index < sequence.length - 1 ? sequence[index + 1] : sequence[0];
    // A third light hit cannot silently cancel back into the first if ACT forbids it.
    if (this.timeline && !this.timeline.finished && index === sequence.length - 1 && !this.data.actions.canLink(current, next)) return false;
    return this.play(next, options);
  }
  update(dt, { grounded, projectileReady = true } = {}) {
    if (!this.timeline) return null;
    let remaining = Math.max(0, dt), state = null; const segments = [];
    for (let transitions = 0; transitions < 128; transitions++) {
      const timeline = this.timeline, pose = timeline.pose;
      if (this._transition) {
        const blend = this._transition, consumed = Math.min(remaining, Math.max(0, blend.duration - blend.elapsed));
        blend.elapsed += consumed; remaining -= consumed;
        state = { poseId: pose.id, pose, source: pose.source, previousFrame: timeline.frame, frame: timeline.frame,
          serial: this.serial, combo: this.combo, context: this._activeMove, attacks: [], drags: [], cancel: false, finished: false,
          rootDelta: { x: 0, y: 0, z: 0 }, consumed, remaining,
          blend: { from: blend.from, to: blend.to, weight: Math.min(1, blend.elapsed / blend.duration), duration: blend.duration } };
        this._stampEffectTime(state); segments.push(state);
        if (blend.elapsed < blend.duration - 1e-7) break;
        this._transition = null;
        if (remaining <= 1e-7) break;
      }
      if (this._reaction && Object.hasOwn(NATIVE_REACTION_ADAPTER.recover, pose.id)) {
        this._reaction.phase = 'down'; timeline.loop = true;
        // Freeze the authored prone frame while airborne; recovery starts
        // after contact with a floor, never while falling through the scene.
        const waiting = grounded === false ? 0 : Math.min(remaining, Math.max(0, this._reaction.holdRemaining));
        this._reaction.holdRemaining -= waiting;
        if (this._reaction.holdRemaining <= 1e-7) {
          if (waiting > 0) {
            state = { ...timeline.advance(waiting), serial: this.serial, combo: this.combo, pose, context: this._activeMove, authoredMotionScale: 1 };
            this._stampEffectTime(state); segments.push(state); remaining -= waiting;
          }
          this._reaction.phase = 'recover';
          if (this._start({ id: NATIVE_REACTION_ADAPTER.recover[pose.id], loop: false }, { linked: true })) continue;
        }
      }
      // Ground contact is a Web-host adapter. The held frame ranges themselves
      // are read from POS; they are not guessed physics constants. Undefined
      // grounded keeps the standalone timeline's previous non-holding behavior.
      if (this._attackChain && Number.isFinite(pose.loopStart) && Number.isFinite(pose.loopEnd)) timeline.loop = grounded === false;
      // A POS link can enter falling within this same update. Apply its
      // authored hold before consuming leftover time, not one host tick later.
      if (pose.id === NATIVE_LOCOMOTION.fall && grounded !== undefined) timeline.loop = grounded === false;
      if (this.weapon === 'wheel' && pose.id === 219) timeline.loop = !projectileReady;
      const timedReaction = ['hit', 'guard'].includes(this._reaction?.phase) && Number.isFinite(pose.loopStart) && Number.isFinite(pose.loopEnd);
      if (timedReaction) timeline.loop = this._reaction.remainingDuration > 1e-7;
      if (this._queuedRequest && (this._canCancelFor(this._queuedRequest) || timeline.finished)) {
        const request = this._queuedRequest; this._queuedRequest = null; this.queued = null;
        if (this._startTransition(request)) continue;
      }
      let stopAtFrame = Infinity;
      if (this._queuedRequest && this._queuedRequest.transitionFrame > timeline.frame) stopAtFrame = this._queuedRequest.transitionFrame;
      const step = timedReaction && this._reaction.remainingDuration > 1e-7 ? Math.min(remaining, this._reaction.remainingDuration) : remaining;
      state = { ...timeline.advance(step, { stopAtFrame }), serial: this.serial, combo: this.combo, pose, context: this._activeMove,
        authoredMotionScale: this._reaction ? ['hit', 'guard'].includes(this._reaction.phase) ? this._reaction.motionScale : 1 : (this._attackChain || this._motionChain) ? 1 : null };
      remaining -= state.consumed;
      if (timedReaction) this._reaction.remainingDuration = Math.max(0, this._reaction.remainingDuration - state.consumed);
      this._stampEffectTime(state); segments.push(state);
      if (this._queuedRequest && (this._canCancelFor(this._queuedRequest) || timeline.finished)) {
        const request = this._queuedRequest; this._queuedRequest = null; this.queued = null;
        if (this._startTransition(request)) continue;
      }
      if (timeline.finished && pose.link != null) {
        if (this._startTransition({ id: pose.link, loop: pose.link === NATIVE_LOCOMOTION.fall && grounded === false }, { linked: true })) continue;
      }
      if (timedReaction && remaining > 1e-7 && this._reaction.remainingDuration <= 1e-7 && !timeline.finished) continue;
      break;
    }
    // Every old-pose attack segment survives an ACT transition or automatic
    // link. The host can sample its source/frame and resolve each original
    // attack index once before displaying the final segment.
    return state ? { ...state, segments } : null;
  }
  _stampEffectTime(state) {
    state.previousEffectTime = this._effectElapsed;
    this._effectElapsed += Math.max(0, state.consumed || 0);
    state.effectTime = this._effectElapsed;
  }
  get attacking() { return !!this.timeline && !this.timeline.finished && this.timeline.pose.attacks.length > 0; }
  get stance() { const profile = NATIVE_WEAPONS[this.weapon]; return profile.modes?.[this.weaponMode]?.stance ?? profile.stance; }
  get reacting() { return !!this._reaction && !!this.timeline && !this.timeline.finished; }
  get reactionPhase() { return this.reacting ? this._reaction.phase : null; }
  get busy() { return !!this.timeline && !this.timeline.finished && (this._attackChain || this._motionChain || !!this._reaction); }
  get currentMove() { return this._activeMove; }
  get queuedMove() { return this._queuedRequest?.context ?? null; }
  get poseBlend() { const blend = this._transition; return blend ? { from: blend.from, to: blend.to, weight: Math.min(1, blend.elapsed / blend.duration), duration: blend.duration } : null; }
}

async function fetchNativeCombat(base) {
  const files = await Promise.all(['P0.POS', 'character.act'].map(async name => { const response = await fetch(base + name); if (!response.ok) throw new Error(`Native combat asset ${name}: ${response.status}`); return decodeNativeText(await response.arrayBuffer()); }));
  const poses = parsePos(files[0], { file: 'pmodel/P0.POS' }), actions = parseAct(files[1], { file: 'Common/character.act' });
  const resourceResponse = await fetch(new URL('./assets/original/characters/meteor-res-data.json', import.meta.url));
  if (!resourceResponse.ok) throw new Error('Original Meteor.res record extraction unavailable');
  const resourceData = await resourceResponse.json();
  const npcResponse = await fetch(new URL('./assets/original/npc-ai/manifest.json', import.meta.url));
  if (!npcResponse.ok) throw new Error('Original NPC command extraction unavailable');
  const npcAi = await npcResponse.json();
  if (npcAi.version !== 1 || Object.keys(npcAi.profiles || {}).length !== 12 || npcAi.airCommands?.length !== 17) throw new Error('Invalid original NPC command tables');
  const moveRecords = new Map(resourceData.allRecords.filter(r => r.type === 3).map(r => [r.id, r]));
  const weaponRecords = new Map(resourceData.allRecords.filter(r => r.type === 1).map(r => [r.model.toLowerCase(), r]));
  const itemRecords = new Map(resourceData.allRecords.filter(r => r.type === 2).map(r => [r.id, r]));
  for (const pose of poses.values()) pose.resource = moveRecords.get(pose.id) || null;
  for (const profile of Object.values(NATIVE_WEAPONS)) for (const id of profile.basic) if (!poses.get(id)?.valid) throw new Error(`Required original pose ${id} is missing`);
  const moves = Object.fromEntries(Object.entries(NATIVE_WEAPONS).map(([weapon, profile]) => [weapon, profile.basic.map(id => ({ ...summarizeNativeMove(poses.get(id), { actions }), resource: moveRecords.get(id) }))]));
  return { poses, actions, moves, moveRecords, weaponRecords, itemRecords, npcAi, getPose: id => poses.get(Number(id)), fps: 30, provenance: { frameRate: 'BANIM headers: 30 FPS', poseWindows: 'Original pmodel/P0.POS', cancelGraph: 'Original Common/character.act', moveStats: 'Original Meteor.res type-3 records, byte offsets retained', damageFormula: 'Original Meteor.exe 004d5e30/004d61c0/004d6190/004d5f70, disassembly checked; E-exe-combat-formulas.json', directionalInputMap: 'external lxres action-table corroboration; not present in POS/ACT, executable verification pending' } };
}
const combatCache = new Map();
export function loadNativeCombat(base = './assets/native/combat/') {
  if (!combatCache.has(base)) combatCache.set(base, fetchNativeCombat(base).catch(error => { combatCache.delete(base); throw error; }));
  return combatCache.get(base);
}
