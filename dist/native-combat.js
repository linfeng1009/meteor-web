// Native Meteor Blade POS/ACT playback. These parsers read the original files;
// no attack frame ranges, hit intervals, animation speeds or links are synthesized.
// Evidence: work/meteor-original/evidence/E-native-combat.md.
const BLOCK_TYPES = new Set(['pose', 'blend', 'action', 'attack', 'drag', 'nextpose']);
const scalar = value => /^[-+]?\d+(?:\.\d*)?(?:e[-+]?\d+)?$/i.test(value) ? Number(value) : value;
const values = text => [...text.matchAll(/"([^"]*)"|([-+]?\d+(?:\.\d*)?(?:e[-+]?\d+)?|[^\s,=]+)/gi)].map(m => m[1] ?? scalar(m[2]));
const includes = (block, frame) => frame >= block.start && frame < block.end + 1;
const windowData = node => ({ ...node.fields, bones: Array.isArray(node.fields.bone) ? node.fields.bone : node.fields.bone ? [node.fields.bone] : [], line: node.line });

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

export function parseAct(text, { file = 'character.act' } = {}) {
  const clean = text.replace(/#[^\r\n]*/g, ''), groups = [], links = new Map();
  for (const match of clean.matchAll(/\bgroup\s*\(\s*(\d+)(?:\s*-\s*(\d+))?\s*\)/gi)) {
    const start = Number(match[1]), end = Number(match[2] || start);
    if (end < start || end - start > 10000) throw new Error(`${file}: Invalid group range`);
    groups.push(Array.from({ length: end - start + 1 }, (_, index) => start + index));
  }
  for (const match of clean.matchAll(/(?:^|\n)\s*(\d+)\s*\(\s*([\d,\s]+)\)/g)) {
    const id = Number(match[1]), targets = [...match[2].matchAll(/\d+/g)].map(m => Number(m[0]));
    if (links.has(id)) throw new Error(`${file}: Duplicate links for pose ${id}`);
    links.set(id, new Set(targets));
  }
  return { groups, links, canLink: (from, to) => links.get(from)?.has(to) || false };
}

// These three groups are explicitly named in P0.POS and listed in character.act.
// Stance IDs are cross-checked against lxres.com/LiuXingBiJi/1758.html; they are
// not claimed to have been recovered from the Windows executable.
export const NATIVE_WEAPONS = Object.freeze({
  dart: { weaponId: 1, model: 'w3_0', stance: 1, guard: 11, basic: [200], air: [202], special: [203, 551], family: [200, 205] },
  dagger: { weaponId: 5, model: 'w1_0', stance: 5, guard: 15, basic: [248, 249, 250, 251], air: [245, 246, 247], special: [558, 559], family: [245, 259] },
  sword: { weaponId: 6, model: 'w0_0', stance: 6, guard: 16, basic: [262, 263, 264], air: [260, 261], special: [560, 561], family: [260, 278] },
  spear: { weaponId: 7, model: 'w7_0', stance: 7, guard: 17, basic: [279, 280, 281], air: [282, 283], special: [562, 563, 571], family: [279, 294] },
  blade: { weaponId: 8, model: 'w5_0', stance: 8, guard: 18, basic: [295, 296, 297], air: [298], special: [565, 572, 573], family: [295, 314] }
});
export const NATIVE_LOCOMOTION = Object.freeze({ idle: 0, walk: 140, run: 144, jumpStart: 151, jumpAir: 152, hit: 90, dead: 117 });
// External action-table corroboration, recorded separately from local PE evidence.
export const NATIVE_DIRECTIONAL = Object.freeze({ sword: { up: 266, down: 267, left: 269, right: 270, 'down,down': 271, 'down,up': 272, 'up,down': 274, 'up,up': 275 }, spear: { up: 285, down: 284, 'down,down': 287, 'down,up': 288, 'up,up': 289 }, blade: { up: 299, down: 300, left: 301, right: 302, 'up,up': 303, 'down,up': 305, 'down,down': 306 } });

export function summarizeNativeMove(pose, { fps = 30, actions = null } = {}) {
  const boundaries = new Set([pose.start, pose.end + 1]);
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
  constructor(pose, { fps = 30, loop = false, sampleRoot = null, scale = .08 } = {}) {
    if (!pose?.valid) throw new Error(`Pose ${pose?.id ?? '?'} has no animation frames`);
    this.pose = pose; this.fps = fps; this.loop = loop; this.sampleRoot = sampleRoot; this.scale = scale;
    this.frame = pose.start; this.finished = false; this.elapsed = 0;
  }
  speedAt(frame = this.frame) {
    // Later ranges override earlier ranges where files deliberately overlap.
    for (let i = this.pose.phases.length - 1; i >= 0; i--) { const p = this.pose.phases[i]; if (includes(p, frame)) return Math.max(.01, p.speed ?? 1); }
    return 1;
  }
  advance(dt) {
    const previous = this.frame, pose = this.pose; let remaining = Math.max(0, dt), loops = 0;
    const sampleBefore = this.sampleRoot?.(pose.source, previous);
    while (remaining > 1e-7 && !this.finished && loops++ < 128) {
      const terminal = this.loop && Number.isFinite(pose.loopEnd) ? pose.loopEnd + 1 : pose.end + 1;
      let boundary = terminal;
      for (const p of pose.phases) {
        if (p.start > this.frame + 1e-6) boundary = Math.min(boundary, p.start);
        if (p.end + 1 > this.frame + 1e-6) boundary = Math.min(boundary, p.end + 1);
      }
      const speed = this.speedAt(), seconds = (boundary - this.frame) / (this.fps * speed);
      if (remaining < seconds - 1e-8) { this.frame += remaining * this.fps * speed; remaining = 0; }
      else { this.frame = boundary; remaining -= Math.max(0, seconds); }
      if (this.frame >= terminal - 1e-6) {
        if (this.loop && Number.isFinite(pose.loopStart)) this.frame = pose.loopStart;
        else { this.frame = pose.end; this.finished = true; }
      }
    }
    this.elapsed += Math.max(0, dt) - remaining;
    const sampleAfter = this.sampleRoot?.(pose.source, this.frame);
    const rootDelta = sampleBefore && sampleAfter ? { x: (sampleAfter.x - sampleBefore.x) * this.scale, y: (sampleAfter.y - sampleBefore.y) * this.scale, z: (sampleAfter.z - sampleBefore.z) * this.scale } : { x: 0, y: 0, z: 0 };
    const crossed = block => !this.finished || previous < pose.end ? previous < block.end + 1 && this.frame >= block.start : false;
    return { poseId: pose.id, source: pose.source, previousFrame: previous, frame: this.frame, finished: this.finished, attacks: pose.attacks.map((attack, index) => ({ ...attack, index })).filter(crossed), drags: pose.drags.filter(crossed), cancel: pose.cancels.some(w => includes(w, this.frame)), rootDelta };
  }
  get canCancel() { return this.pose.cancels.some(w => includes(w, this.frame)); }
}

export class NativeCombatController {
  constructor(data, { weapon = 'sword', fps = 30, sampleRoot = null, scale = .08 } = {}) {
    this.data = data; this.weapon = weapon; this.fps = fps; this.sampleRoot = sampleRoot; this.scale = scale;
    this.timeline = null; this.queued = null; this.serial = 0; this.combo = 0;
  }
  setWeapon(name) { if (!NATIVE_WEAPONS[name]) throw new Error(`Unknown native weapon ${name}`); this.weapon = name; this.timeline = null; this.queued = null; this.combo = 0; }
  play(id, { loop = false, force = false } = {}) {
    const pose = this.data.poses.get(id); if (!pose?.valid) return false;
    if (!force && this.timeline && !this.timeline.finished && this.timeline.pose.attacks.length) {
      const current = this.timeline.pose;
      if (!this.data.actions.canLink(current.id, id)) return false;
      if (!this.timeline.canCancel) { this.queued = id; return true; }
    }
    this.timeline = new NativePoseTimeline(pose, { fps: this.fps, loop, sampleRoot: this.sampleRoot, scale: this.scale }); this.serial++; this.queued = null;
    const index = NATIVE_WEAPONS[this.weapon].basic.indexOf(id); this.combo = index >= 0 ? index + 1 : 0; return true;
  }
  attack({ air = false, poseId = null } = {}) {
    if (poseId != null) return this.play(poseId);
    const sequence = air ? NATIVE_WEAPONS[this.weapon].air : NATIVE_WEAPONS[this.weapon].basic;
    const current = this.timeline?.pose.id, index = sequence.indexOf(current), next = index >= 0 && index < sequence.length - 1 ? sequence[index + 1] : sequence[0];
    // A third light hit cannot silently cancel back into the first if ACT forbids it.
    if (this.timeline && !this.timeline.finished && index === sequence.length - 1 && !this.data.actions.canLink(current, next)) return false;
    return this.play(next);
  }
  update(dt) {
    if (!this.timeline) return null;
    let state = this.timeline.advance(dt);
    if (this.queued != null && (this.timeline.canCancel || this.timeline.finished)) {
      const next = this.queued; this.play(next, { force: true }); state = this.timeline.advance(0);
    } else if (state.finished && this.timeline.pose.link != null) {
      this.play(this.timeline.pose.link, { force: true }); state = this.timeline.advance(0);
    }
    return { ...state, serial: this.serial, combo: this.combo, pose: this.timeline.pose };
  }
  get attacking() { return !!this.timeline && !this.timeline.finished && this.timeline.pose.attacks.length > 0; }
}

async function fetchNativeCombat(base) {
  const files = await Promise.all(['P0.POS', 'character.act'].map(async name => { const response = await fetch(base + name); if (!response.ok) throw new Error(`Native combat asset ${name}: ${response.status}`); return decodeNativeText(await response.arrayBuffer()); }));
  const poses = parsePos(files[0], { file: 'pmodel/P0.POS' }), actions = parseAct(files[1], { file: 'Common/character.act' });
  const resourceResponse = await fetch(new URL('./assets/original/characters/meteor-res-data.json', import.meta.url));
  if (!resourceResponse.ok) throw new Error('Original Meteor.res record extraction unavailable');
  const resourceData = await resourceResponse.json();
  const moveRecords = new Map(resourceData.allRecords.filter(r => r.type === 3).map(r => [r.id, r]));
  const weaponRecords = new Map(resourceData.allRecords.filter(r => r.type === 1).map(r => [r.model.toLowerCase(), r]));
  const itemRecords = new Map(resourceData.allRecords.filter(r => r.type === 2).map(r => [r.id, r]));
  for (const pose of poses.values()) pose.resource = moveRecords.get(pose.id) || null;
  for (const profile of Object.values(NATIVE_WEAPONS)) for (const id of profile.basic) if (!poses.get(id)?.valid) throw new Error(`Required original pose ${id} is missing`);
  const moves = Object.fromEntries(Object.entries(NATIVE_WEAPONS).map(([weapon, profile]) => [weapon, profile.basic.map(id => ({ ...summarizeNativeMove(poses.get(id), { actions }), resource: moveRecords.get(id) }))]));
  return { poses, actions, moves, moveRecords, weaponRecords, itemRecords, getPose: id => poses.get(Number(id)), fps: 30, provenance: { frameRate: 'BANIM headers: 30 FPS', poseWindows: 'Original pmodel/P0.POS', cancelGraph: 'Original Common/character.act', moveStats: 'Original Meteor.res type-3 records, byte offsets retained', damageFormula: 'Original Meteor.exe 004d5e30/004d61c0/004d6190/004d5f70, disassembly checked; E-exe-combat-formulas.json', directionalInputMap: 'external lxres action-table corroboration; not present in POS/ACT, executable verification pending' } };
}
const combatCache = new Map();
export function loadNativeCombat(base = './assets/native/combat/') {
  if (!combatCache.has(base)) combatCache.set(base, fetchNativeCombat(base).catch(error => { combatCache.delete(base); throw error; }));
  return combatCache.get(base);
}
