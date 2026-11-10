// Direction recognition is a Web host adapter. Pose IDs, attack windows and
// legal transitions are validated separately against the original POS / ACT.
export const NATIVE_INPUT_TIMING = Object.freeze({ sequence: 1.2, step: .45, attack: .45, capacity: 8 });
// The native controller expires key-token queues after .3s (004cc130,
// double005aa8b8). This single post-hit command slot is a bounded Web adapter,
// not a claim that the complete original recognizer has been recovered.
export const NATIVE_RECOVERY_INPUT_WINDOW = .3;
const directions = new Set(['up', 'down', 'left', 'right']);

export function recordNativeDirection(buffer, direction, time, air = false) {
  if (!directions.has(direction) || !Number.isFinite(time)) return buffer;
  return [...buffer.filter(event => time - event.time <= NATIVE_INPUT_TIMING.sequence), { direction, time, air }].slice(-NATIVE_INPUT_TIMING.capacity);
}

// Match the longest contiguous suffix before considering a held direction or
// plain A. A recognised but unavailable move must be rejected by its caller,
// never silently replaced with a shorter command or a normal attack.
export function selectNativeMove(catalog, { weapon, weaponMode = 'blade', includeOtherModes = false, air = false, buffer = [], held = [], time = 0, poseId = null, movePoseId = null, busy = false } = {}) {
  const stance = air ? 'air' : 'ground';
  const candidates = catalog.filter(move => move.weapon === weapon && move.stance === stance &&
    (includeOtherModes || !move.weaponMode || move.weaponMode === weaponMode) &&
    (!move.continuationOf?.length || busy && move.continuationOf.some(id => id === poseId || id === movePoseId)));
  let recent = buffer.filter(event => Number.isFinite(event.time) && time >= event.time && time - event.time <= NATIVE_INPUT_TIMING.sequence);
  let start = recent.length;
  for (let i = recent.length - 1; i >= 0; i--) {
    if (recent[i].air != null && recent[i].air !== air) break;
    if (i < recent.length - 1 && recent[i + 1].time - recent[i].time > NATIVE_INPUT_TIMING.step) break;
    start = i;
  }
  recent = recent.slice(start);
  if (!recent.length || time - recent.at(-1).time > NATIVE_INPUT_TIMING.attack) recent = [];
  const ordered = candidates.flatMap(move => [move.input, ...(move.alternateInputs || [])].map(input => ({ move, input })))
    .sort((a, b) => b.input.length - a.input.length ||
      Number(!b.move.weaponMode || b.move.weaponMode === weaponMode) - Number(!a.move.weaponMode || a.move.weaponMode === weaponMode) ||
      Number(!!b.move.continuationOf?.length) - Number(!!a.move.continuationOf?.length));
  for (const { move, input } of ordered) {
    const command = input.slice(0, -1);
    if (!command.length || input.at(-1) !== 'attack' || command.length > recent.length) continue;
    if (command.every((direction, i) => direction === recent[recent.length - command.length + i].direction)) return move;
  }
  // A long-running movement key still allows ↑A / ↓A after its tap expires.
  // Require one unambiguous held direction; opposite/diagonal chords are not
  // fabricated into a sequence by object iteration order.
  const heldDirections = [...new Set(held)].filter(direction => directions.has(direction));
  if (heldDirections.length === 1) {
    const match = ordered.find(({ input }) => input.length === 2 && input[0] === heldDirections[0]);
    if (match) return match.move;
  }
  return ordered.find(({ input }) => input.length === 1 && input[0] === 'attack')?.move || null;
}
