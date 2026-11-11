// A bounded original-item adapter. Identity and effects come from preserved
// Meteor.res type-2 records, never from the rendered mesh's display name.
import { nativeEffectiveStat } from './native-combat.js';

export const NATIVE_ITEM_PICKUP_PROFILE = Object.freeze({
  radius: 1.8, verticalTolerance: 2,
  provenance: Object.freeze({
    effect: 'Meteor.res type2/id1 Item01 肉包: stat2 mode0 value300, valueOffset53204; 004d4d30 clamps current HP to 0..effective maxHP.',
    interaction: 'Browser adapter: grounded automatic proximity pickup plus optional manual assist, horizontal radius1.8 world units, vertical tolerance2; exact EXE range/state gates remain unverified.',
    fullHp: 'Browser adapter: keep positive immediate HP/rage items when that resource is full; original full-HP consumption and item respawn timing remain unverified.',
    scope: 'Verified world RES records1/2/3/4/5/8/16/17/18/27/28/29/30/31 and available original weapon-manifest records. Unsupported effects remain unconsumed; no automatic respawn.'
  })
});

const normalizedModel = value => String(value ?? '').replace(/^"|"$/g, '').toLowerCase();
const disabled = value => value === false || value === 0 || /^(0|false)$/i.test(String(value));
const records = value => value instanceof Map ? value.values() : value || [];

// Bounded Perform("use") bridge for original story missions. The
// source parameters2/8 give lifetime/rate; effect words3/4 give period/type.
// 004d59d0 refreshes an existing type2 item instead of stacking it,
// 004d5020 expires it, 004d4e30 applies periodic HP changes. The server
// 004b1e16 and client0048af49 pass float32(.2) to this dedicated update.
// Web frames bridge to those steps; complete EF presentation is pending.
export const NATIVE_ITEM_UPDATE_SECONDS = .2;
const nativeItemStep = Math.fround(NATIVE_ITEM_UPDATE_SECONDS);
const itemClocks = new WeakMap();
export const NATIVE_SCRIPT_ITEM_PROVENANCE = Object.freeze({
  values: 'Original Meteor.res type2/id4 attack+25 for600/10 seconds; id11 HP-10 every3 seconds for150/10 seconds; id12 HP-10 every2 seconds for600/10 seconds; id14 HP-10 every5 seconds for99999/10 seconds; id15 immediate HP+5000; id19 attack+150 and id20 maxHP+6999 for99999/10 seconds; id22 immediate rage-20.',
  native: 'Meteor.exe 004d59d0 duplicate refresh, 004d5020 duration/rate, 004d4e30 period*10 with float10 at005a84ac; 004d4d30 clamps HP/stat2 to maxHP/stat1 and rage/stat6 to maxRage/stat7. 004d4a70 initializes stat7 to100.',
  attack: '004af630 applies type3 parameter16 only after HP damage and victim rage gain, on an unguarded surviving target; 004d5fc0 resolves the type2 record, server004afcf0 applies it through004d59d0.',
  self: '004cff40 saves type3 parameter18 at controller+524;004ce3d0/004f1920 gates its deferred004f0c10 message2a. Web adapter applies it once on the completed source casting pose; the native manager+210 trigger phase is not reproduced.',
  rageSkills: 'Original type2/id34 attack+40 for900/10 seconds; id40 defense+20 for1200/10 seconds; id37 immediate rage-5; id13 stat5 mode1 value30 for600/10 seconds. Stat5 scales Web movement using a100-point basis; exact native movement/network consumer remains unverified.',
  timing: '004b1e16 server and0048af49 client pass float32(.2). Each step expires before applying periodic effects;004d4e30 tests the old integer counter before adding trunc(counter+10*dt), applies at most once and resets to0. Web elapsed frames bridge to this source cadence; original wall-clock phase/network scheduling remain unverified.',
  maxHp: '004d5e30 stat1 adds the active modifier; removal restores maxHP without an invented immediate current-HP adjustment. 004d4d30 clamps the next HP adjustment.',
  pending: 'id7 stat10+1 for600/10 seconds is not implemented until its native consumer is recovered; none of ids4/7/14/15/19/20 is an immediate rage effect. Poison removal is not inferred from item names.',
  visuals: 'Original item EF presentation is pending; HUD status identifies the applied gameplay effect.'
});

const scriptItemSpecs = new Map([
  [2, { statKey:1,value:500,lifetime:6000,rate:10,effectType:-1,period:0,kind:'modifier' }],
  [3, { statKey:4,value:20,lifetime:900,rate:10,effectType:-1,period:0,kind:'modifier' }],
  [5, { statKey:5,mode:1,value:150,lifetime:600,rate:10,effectType:-1,period:0,kind:'modifier' }],
  [8, { statKey:6,value:100,lifetime:0,rate:0,effectType:0,period:0,kind:'immediate' }],
  [16, { statKey:2,value:500,lifetime:0,rate:0,effectType:0,period:0,kind:'immediate' }],
  [17, { statKey:2,value:100,lifetime:0,rate:0,effectType:0,period:0,kind:'immediate' }],
  [18, { statKey:2,value:-10,lifetime:300,rate:10,effectType:1,period:5,kind:'periodic' }],
  [27, { statKey:1,value:6999,lifetime:600,rate:10,effectType:-1,period:0,kind:'modifier' }],
  [28, { statKey:6,value:25,lifetime:0,rate:0,effectType:0,period:0,kind:'immediate' }],
  [29, { statKey:4,value:100,lifetime:99999,rate:10,effectType:-1,period:0,kind:'modifier' }],
  [30, { statKey:3,value:125,lifetime:99999,rate:10,effectType:-1,period:0,kind:'modifier' }],
  [31, { statKey:5,mode:1,value:150,lifetime:99999,rate:10,effectType:-1,period:0,kind:'modifier' }],
  [4, { statKey: 3, value: 25, lifetime: 600, rate: 10, effectType: -1, period: 0, kind: 'modifier' }],
  [11, { statKey: 2, value: -10, lifetime: 150, rate: 10, effectType: 1, period: 3, kind: 'periodic' }],
  [12, { statKey: 2, value: -10, lifetime: 600, rate: 10, effectType: 1, period: 2, kind: 'periodic' }],
  [13, { statKey: 5, mode: 1, value: 30, lifetime: 600, rate: 10, effectType: -1, period: 0, kind: 'modifier' }],
  [14, { statKey: 2, value: -10, lifetime: 99999, rate: 10, effectType: 1, period: 5, kind: 'periodic' }],
  [15, { statKey: 2, value: 5000, lifetime: 0, rate: 0, effectType: 0, period: 0, kind: 'immediate' }],
  [19, { statKey: 3, value: 150, lifetime: 99999, rate: 10, effectType: -1, period: 0, kind: 'modifier' }],
  [20, { statKey: 1, value: 6999, lifetime: 99999, rate: 10, effectType: -1, period: 0, kind: 'modifier' }],
  [22, { statKey: 6, value: -20, lifetime: 0, rate: 0, effectType: 0, period: 0, kind: 'immediate' }],
  [34, { statKey: 3, value: 40, lifetime: 900, rate: 10, effectType: -1, period: 0, kind: 'modifier' }],
  [37, { statKey: 6, value: -5, lifetime: 0, rate: 0, effectType: 0, period: 0, kind: 'immediate' }],
  [40, { statKey: 4, value: 20, lifetime: 1200, rate: 10, effectType: -1, period: 0, kind: 'modifier' }]
]);
const maxHpBeforeScriptItems = new WeakMap();

export function nativeScriptItemEffect(record) {
  const spec = scriptItemSpecs.get(record?.id);
  if (record?.type !== 2 || !spec || record.effects?.length !== 1) return null;
  const effect = record.effects[0], parameter = key => record.parameters?.find(p => p.words[0] === key)?.words[1];
  if (parameter(1) !== spec.lifetime || parameter(2) !== spec.lifetime || parameter(8) !== spec.rate ||
      effect.words?.[0] !== 2 || effect.words[1] !== 0 || effect.statKey !== spec.statKey || effect.words[2] !== spec.statKey ||
      effect.words[3] !== spec.period || effect.words[4] !== spec.effectType || effect.mode !== (spec.mode ?? 0) || effect.words[5] !== (spec.mode ?? 0) ||
      effect.value !== spec.value || effect.words[6] !== spec.value || effect.words[7] !== Number(spec.kind === 'modifier')) return null;
  return { id: record.id, name: record.name, record, kind: spec.kind, statKey: spec.statKey,
    duration: spec.rate ? spec.lifetime / spec.rate : 0, lifetime: spec.lifetime, rate: spec.rate, period: spec.period || null, value: effect.value };
}

export function nativeRageMaximum(actor) {
  return nativeEffectiveStat(7, actor.nativeStats?.[7] ?? 100, [actor.weaponRecord, ...(actor.activeItems || [])]);
}

// The host's walking speed is a Web physics value. Apply recovered percent
// active item modifiers on a normalized basis, preserving native integer stat
// arithmetic. Weapon speed is not reapplied to the host's existing base speed.
export function nativeMovementScale(actor) {
  const basis = actor.nativeStats?.[5] ?? 100;
  return basis > 0 ? nativeEffectiveStat(5, basis, actor.activeItems || []) / basis : 1;
}

function syncScriptMaxHp(actor) {
  if (!maxHpBeforeScriptItems.has(actor)) return;
  actor.maxHp = Math.max(0, maxHpBeforeScriptItems.get(actor) + (actor.scriptItems || [])
    .filter(item => item.statKey === 1 && item.kind === 'modifier').reduce((sum, item) => sum + item.value, 0));
  if (!(actor.scriptItems || []).some(item => item.statKey === 1 && item.kind === 'modifier')) maxHpBeforeScriptItems.delete(actor);
}

export function useNativeScriptItem(actor, record) {
  const effect = nativeScriptItemEffect(record);
  if (!effect || !actor || actor.dead || actor.disposed || actor.scriptRemoved || !(actor.hp > 0)) return null;
  if (effect.kind === 'immediate') {
    if (effect.statKey === 6) {
      const before = actor.rage || 0;
      actor.rage = Math.max(0, Math.min(nativeRageMaximum(actor), before + effect.value));
      return { ...effect, refreshed: false, rageBefore: before, rageAfter: actor.rage, drained: before - actor.rage };
    }
    if (!Number.isFinite(actor.maxHp) || actor.maxHp <= 0) return null;
    const before = actor.hp; actor.hp = Math.max(0, Math.min(actor.maxHp, before + effect.value));
    return { ...effect, refreshed: false, hpBefore: before, hpAfter: actor.hp, healed: actor.hp - before };
  }
  if (effect.statKey === 1 && !maxHpBeforeScriptItems.has(actor)) {
    if (!Number.isFinite(actor.maxHp) || actor.maxHp <= 0) return null;
    maxHpBeforeScriptItems.set(actor, actor.maxHp);
  }
  actor.scriptItems ||= []; actor.activeItems ||= [];
  const existing = actor.scriptItems.find(item => item.id === effect.id);
  if (existing) { existing.remainingTicks = effect.lifetime; existing.remaining = effect.duration; return { ...effect, refreshed: true }; }
  actor.scriptItems.push({ ...effect, remaining: effect.duration, remainingTicks: effect.lifetime, counter: 0, accumulator: 0 });
  actor.activeItems.push(record); syncScriptMaxHp(actor); return { ...effect, refreshed: false };
}

// The caller preserves the source guard/alive gates and damage→rage→item
// order. Only items whose stat consumers are implemented above can apply.
export function useNativeAttackItem(actor, moveRecord, itemRecords) {
  if (moveRecord?.type !== 3) return null;
  const itemId = moveRecord.parameters?.find(parameter => parameter.words?.[0] === 16)?.words[1];
  return useNativeScriptItem(actor, itemRecords?.get(itemId));
}

export function useNativeSelfItem(actor, moveRecord, itemRecords) {
  if (moveRecord?.type !== 3) return null;
  const itemId = moveRecord.parameters?.find(parameter => parameter.words?.[0] === 18)?.words[1];
  return useNativeScriptItem(actor, itemRecords?.get(itemId));
}

export function updateNativeScriptItems(actor, dt, onTick = () => {}, { time } = {}) {
  if (!actor || actor.dead || actor.disposed || actor.scriptRemoved || !Number.isFinite(dt) || !(dt > 0)) return;
  // Shared game time keeps actors on the same item phase. Standalone users
  // retain elapsed time between calls even when no item is currently active.
  const elapsed = itemClocks.get(actor) || 0, end = Number.isFinite(time) ? time : elapsed + dt;
  const begin = Number.isFinite(time) ? time - dt : elapsed;
  itemClocks.set(actor, end);
  const stepIndex = seconds => Math.floor((seconds + 1e-9) / NATIVE_ITEM_UPDATE_SECONDS);
  const steps = Math.max(0, stepIndex(end) - stepIndex(begin));
  for (let step = 0; step < steps && actor.hp > 0 && actor.scriptItems?.length; step++) {
    for (const item of [...actor.scriptItems]) {
      const lifetimeDelta = item.rate * nativeItemStep;
      // 004d50b1..c3: finite less-or-equal expires before the stat update.
      if (item.remainingTicks <= lifetimeDelta) {
        actor.scriptItems = actor.scriptItems.filter(active => active !== item);
        actor.activeItems = (actor.activeItems || []).filter(record => record !== item.record);
        continue;
      }
      item.remainingTicks -= Math.trunc(lifetimeDelta); item.remaining = item.remainingTicks / item.rate;
      if (item.period) {
        if (item.counter < item.period * 10) item.counter = Math.trunc(item.counter + 10 * nativeItemStep);
        else {
          item.counter = 0;
          const before = actor.hp; actor.hp = Math.max(0, Math.min(actor.maxHp, before + item.value));
          onTick({ itemId: item.id, name: item.name, hpBefore: before, hpAfter: actor.hp, amount: before - actor.hp });
        }
        item.accumulator = item.counter / 10;
      }
      if (actor.hp <= 0) break;
    }
    syncScriptMaxHp(actor);
  }
}

export function clearNativeScriptItems(actor) {
  const applied = new Set((actor.scriptItems || []).map(item => item.record));
  actor.activeItems = (actor.activeItems || []).filter(record => !applied.has(record)); actor.scriptItems = []; itemClocks.delete(actor); syncScriptMaxHp(actor);
}

export function nativeMeatbunEffect(record) {
  if (record?.type !== 2 || record.id !== 1 || normalizedModel(record.model) !== 'item01' || record.effects?.length !== 1) return null;
  const effect = record.effects[0];
  if (effect.statKey !== 2 || effect.mode !== 0 || effect.words?.[4] !== 0 || !Number.isInteger(effect.value) || effect.value <= 0) return null;
  return { itemId: record.id, name: record.name, model: normalizedModel(record.model), heal: effect.value, recordOffset: record.offset, valueOffset: effect.valueOffset };
}

const worldItemIds=new Set([2,3,4,5,8,16,17,18,27,28,29,30,31]);
export function nativeWorldItemEffect(record){
  const bun=nativeMeatbunEffect(record);
  if(bun)return {...bun,record,kind:'immediate',statKey:2,value:bun.heal,duration:0,description:`气血 +${bun.heal}`};
  if(!worldItemIds.has(record?.id)||!/^item\d+$/i.test(normalizedModel(record.model)))return null;
  const effect=nativeScriptItemEffect(record);if(!effect)return null;
  const heal=effect.kind==='immediate'&&effect.statKey===2&&effect.value>0?effect.value:0;
  const stat={1:'气血上限',2:'气血',3:'攻击',4:'防御',5:'移速',6:'怒气'}[effect.statKey];
  const value=effect.statKey===5?`${effect.value}%`:`${effect.value>0?'+':''}${effect.value}`;
  const description=effect.period?`每${effect.period}秒${stat} ${value} · ${effect.duration}秒`:`${stat} ${value}${effect.duration?` · ${effect.duration}秒`:''}`;
  return {...effect,itemId:record.id,model:normalizedModel(record.model),heal,recordOffset:record.offset,valueOffset:record.effects[0].valueOffset,description};
}

export class NativeItemSystem {
  constructor({ itemRecords, weaponItems = [], getInstances = () => [], canReach = () => true, onPickup = () => {}, profile = NATIVE_ITEM_PICKUP_PROFILE } = {}) {
    this.getInstances = getInstances; this.canReach = canReach; this.onPickup = onPickup; this.profile = profile;
    this.itemsByModel = new Map(); this.consumed = new WeakSet(); this.disposed = false;
    this.consumedNames=new Set();this.visuals=new Map();
    for (const record of records(itemRecords)) {
      const effect = nativeWorldItemEffect(record); if (effect) this.itemsByModel.set(effect.model, effect);
    }
    for(const item of records(weaponItems))if(item.available)this.itemsByModel.set(normalizedModel(item.modelId),{kind:'weapon',itemId:Number(item.itemId),name:item.name,description:'收为副兵器',record:item});
  }
  peek(actor) {
    if (this.disposed || !actor?.root?.position || actor.dead || actor.disposed || actor.scriptRemoved || actor.scriptInputBlocked || actor.switchingWeapon || !Number.isFinite(actor.hp) || actor.hp <= 0 || !Number.isFinite(actor.maxHp) || actor.maxHp <= 0) return null;
    const origin = actor.root.position, candidates = [];
    for (const instance of this.getInstances() || []) {
      if (!instance?.root?.position || this.consumed.has(instance) || disabled(instance.attributes?.active) || disabled(instance.attributes?.interactive)) continue;
      const effect = this.itemsByModel.get(normalizedModel(instance.source?.properties?.model)); if (!effect) continue;
      const point = instance.root.position, distance = Math.hypot(point.x - origin.x, point.z - origin.z);
      if(instance.dropOwner===actor){if(distance<=this.profile.radius+.1)continue;instance.dropOwner=null;}
      if (distance > this.profile.radius || Math.abs(point.y - origin.y) > this.profile.verticalTolerance) continue;
      const fullHp=effect.heal>0&&actor.hp>=actor.maxHp;
      const fullRage=effect.kind==='immediate'&&effect.statKey===6&&(actor.rage||0)>=nativeRageMaximum(actor);
      const fullWeapons=effect.kind==='weapon'&&Number.isInteger(actor.weapon2Id)&&actor.weapon2Id>0;
      candidates.push({ ...effect, instance, objectName: instance.name, distance, full:fullHp||fullRage||fullWeapons,fullReason:fullWeapons?'full-weapons':fullRage?'full-rage':'full-hp', provenance: this.profile.provenance });
    }
    candidates.sort((a, b) => a.distance - b.distance || a.objectName.localeCompare(b.objectName));
    const reachable=candidates.filter(candidate=>this.canReach(actor,candidate.instance));
    return reachable.find(candidate=>!candidate.full)||reachable[0]||null;
  }
  tryPickup(actor) {
    const candidate = this.peek(actor);
    if (!candidate) return { ok: false, reason: 'no-item', healed: 0 };
    if (candidate.full) return { ok: false, reason: candidate.fullReason, healed: 0, candidate };
    // Native stat2/current HP is clamped by stat1/max HP (004d4d30).
    const before=actor.hp,rageBefore=actor.rage||0;
    let applied;
    if(candidate.kind==='weapon'){actor.weapon2Id=candidate.itemId;applied={refreshed:false};}
    else if(candidate.itemId===1){actor.hp=Math.max(0,Math.min(actor.maxHp,before+candidate.heal));applied={refreshed:false};}
    else applied=useNativeScriptItem(actor,candidate.record);
    if(!applied)return {ok:false,reason:'unsupported-effect',healed:0};
    const after=actor.hp;
    const instance = candidate.instance;
    this.consumed.add(instance);
    if(!instance.weaponId)this.consumedNames.add(instance.name);
    instance.attributes ||= {}; instance.attributes.active = 0; instance.attributes.interactive = 0; instance.attributes.collision = 0;
    if (instance.setActive) instance.setActive(false); else instance.root.visible = false;
    instance.setCollision?.(false);
    const result = { ok: true, reason: 'picked-up', itemId: candidate.itemId, name: candidate.name, objectName: candidate.objectName,
      healed: after - before, hpBefore: before, hpAfter: after, maxHp: actor.maxHp, effectValue: candidate.value,
      description:candidate.description,kind:candidate.kind,statKey:candidate.statKey,duration:candidate.duration,refreshed:applied.refreshed,rageGained:(actor.rage||0)-rageBefore,actor,
      recordOffset: candidate.recordOffset, valueOffset: candidate.valueOffset, instance, provenance: this.profile.provenance };
    this.onPickup(result); return result;
  }
  prepareWorld(){for(const instance of this.getInstances()||[])if(this.itemsByModel.has(normalizedModel(instance.source?.properties?.model)))instance.setCollision?.(false);}
  updateVisuals(time){
    for(const instance of this.getInstances()||[]){
      if(!this.itemsByModel.has(normalizedModel(instance.source?.properties?.model)))continue;
      const model=instance.model;if(!model||instance.asset?.animation||disabled(instance.attributes?.active))continue;
      if(!this.visuals.has(instance))this.visuals.set(instance,{model,position:model.position.clone(),quaternion:model.quaternion.clone()});
      const base=this.visuals.get(instance);model.position.copy(base.position);model.position.y+=Math.sin(time*2)*.12/(instance.root.scale.y||1);
      model.quaternion.copy(base.quaternion);model.rotateY(time);model.updateMatrixWorld(true);
    }
  }
  reset() { this.consumed = new WeakSet();this.consumedNames.clear();for(const base of this.visuals.values()){base.model.position.copy(base.position);base.model.quaternion.copy(base.quaternion);}this.visuals.clear(); }
  dispose() { this.reset(); this.disposed = true; }
}
