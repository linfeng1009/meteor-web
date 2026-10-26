// A bounded original-item adapter. Item identity and healing come from the
// preserved Meteor.res type-2 record, never from the rendered mesh's name.
export const NATIVE_ITEM_PICKUP_PROFILE = Object.freeze({
  radius: 1.8, verticalTolerance: 2,
  provenance: Object.freeze({
    effect: 'Meteor.res type2/id1 Item01 肉包: stat2 mode0 value300, valueOffset53204; 004d4d30 clamps current HP to 0..effective maxHP.',
    interaction: 'Browser adapter: explicit pickup input, horizontal radius1.8 world units, vertical tolerance2; exact EXE pickup trigger/range remains unverified.',
    fullHp: 'Browser adapter: keep the item when HP is full; original full-HP consumption and item respawn timing remain unverified.',
    scope: 'Only the original Item01 meatbun immediate HP effect; no timed buffs, weapon pickup, respawn, or other item effects.'
  })
});

const normalizedModel = value => String(value ?? '').replace(/^"|"$/g, '').toLowerCase();
const disabled = value => value === false || value === 0 || /^(0|false)$/i.test(String(value));
const records = value => value instanceof Map ? value.values() : value || [];

export function nativeMeatbunEffect(record) {
  if (record?.type !== 2 || record.id !== 1 || normalizedModel(record.model) !== 'item01' || record.effects?.length !== 1) return null;
  const effect = record.effects[0];
  if (effect.statKey !== 2 || effect.mode !== 0 || effect.words?.[4] !== 0 || !Number.isInteger(effect.value) || effect.value <= 0) return null;
  return { itemId: record.id, name: record.name, model: normalizedModel(record.model), heal: effect.value, recordOffset: record.offset, valueOffset: effect.valueOffset };
}

export class NativeItemSystem {
  constructor({ itemRecords, getInstances = () => [], canReach = () => true, onPickup = () => {}, profile = NATIVE_ITEM_PICKUP_PROFILE } = {}) {
    this.getInstances = getInstances; this.canReach = canReach; this.onPickup = onPickup; this.profile = profile;
    this.itemsByModel = new Map(); this.consumed = new WeakSet(); this.disposed = false;
    for (const record of records(itemRecords)) {
      const effect = nativeMeatbunEffect(record); if (effect) this.itemsByModel.set(effect.model, effect);
    }
  }
  peek(actor) {
    if (this.disposed || !actor?.root?.position || actor.dead || actor.disposed || actor.scriptRemoved || !Number.isFinite(actor.hp) || actor.hp <= 0 || !Number.isFinite(actor.maxHp) || actor.maxHp <= 0) return null;
    const origin = actor.root.position, candidates = [];
    for (const instance of this.getInstances() || []) {
      if (!instance?.root?.position || this.consumed.has(instance) || disabled(instance.attributes?.active) || disabled(instance.attributes?.interactive)) continue;
      const effect = this.itemsByModel.get(normalizedModel(instance.source?.properties?.model)); if (!effect) continue;
      const point = instance.root.position, distance = Math.hypot(point.x - origin.x, point.z - origin.z);
      if (distance > this.profile.radius || Math.abs(point.y - origin.y) > this.profile.verticalTolerance) continue;
      candidates.push({ ...effect, instance, objectName: instance.name, distance, full: actor.hp >= actor.maxHp, provenance: this.profile.provenance });
    }
    candidates.sort((a, b) => a.distance - b.distance || a.objectName.localeCompare(b.objectName));
    return candidates.find(candidate => this.canReach(actor, candidate.instance)) || null;
  }
  tryPickup(actor) {
    const candidate = this.peek(actor);
    if (!candidate) return { ok: false, reason: 'no-item', healed: 0 };
    if (candidate.full) return { ok: false, reason: 'full-hp', healed: 0, candidate };
    // Native stat2/current HP is clamped by stat1/max HP (004d4d30).
    const before = actor.hp, after = Math.max(0, Math.min(actor.maxHp, before + candidate.heal));
    const instance = candidate.instance;
    this.consumed.add(instance); actor.hp = after;
    instance.attributes ||= {}; instance.attributes.active = 0; instance.attributes.interactive = 0; instance.attributes.collision = 0;
    if (instance.setActive) instance.setActive(false); else instance.root.visible = false;
    instance.setCollision?.(false);
    const result = { ok: true, reason: 'picked-up', itemId: candidate.itemId, name: candidate.name, objectName: candidate.objectName,
      healed: after - before, hpBefore: before, hpAfter: after, maxHp: actor.maxHp, effectValue: candidate.heal,
      recordOffset: candidate.recordOffset, valueOffset: candidate.valueOffset, instance, provenance: this.profile.provenance };
    this.onPickup(result); return result;
  }
  reset() { this.consumed = new WeakSet(); }
  dispose() { this.reset(); this.disposed = true; }
}
