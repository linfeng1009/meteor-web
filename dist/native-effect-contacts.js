import * as THREE from './vendor/three.module.js';
import { createEffectTransforms, setEffectTime, effectNodeMatrix } from './native-effect-transforms.js';

// 00556910: POS "effect" =0x1001; 0055da50 ->0056f1d0 checks EF
// nodes whose first name byte is A/a, excluding AUDIO/PATH. It queries
// oriented bounds (005818f0/0055d950/00570630), not rendered triangles,
// opacity or texture presence. SPHERE/BOX/CYLINDER/PLANE/DONUT bounds are recovered here.
// MODEL/PATH and the other primitive families still require their own rules.
export const NATIVE_EFFECT_CONTACT_ADAPTER = Object.freeze({
  sampleStep: 1 / 120, maxSamplesPerInterval: 256, bodyRadius: .4, bodyHalfHeight: 1.3,
  provenance: 'Source EF bound dimensions, keys, A/a name filter and POS effect windows; Web transform interpolation, temporal sampling and actor body box.'
});
const WORLD_AXES = [new THREE.Vector3(1, 0, 0), new THREE.Vector3(0, 1, 0), new THREE.Vector3(0, 0, 1)];
const EFFECT_STEP=Symbol('native-effect-contact-step');

export function nativeEffectBounds(source) {
  const d = source.dimensions;
  if (!d?.length || !d.every(Number.isFinite)) return null;
  const center = new THREE.Vector3(), half = new THREE.Vector3();
  if (source.type === 'SPHERE' && d.length === 5) half.setScalar(Math.abs(d[0]));
  else if (source.type === 'CYLINDER' && d.length === 5) {
    const radius = Math.max(Math.abs(d[0]), Math.abs(d[1])); half.set(radius, radius, Math.abs(d[2]) / 2);
    if (source.flags?.[0] === 1) center.z = d[2] / 2;
  } else if (source.type === 'BOX' && d.length === 3) {
    half.set(...d.map(value => Math.abs(value) / 2));
    // 00589a40 keeps the original second dimension as the base offset.
    if (source.flags?.[0] === 1) center.z = d[1] / 2;
  }
  else if (source.type === 'PLANE' && d.length === 2) {
    // 00585400: authored width/height halves and fixed native Z half-size3.
    half.set(Math.abs(d[0])/2,Math.abs(d[1])/2,3);
    if(source.flags?.[0]===1)center.z=d[1]/2;
  }
  else if (source.type === 'DONUT' && d.length === 6) {
    // 005881a0: the native attack uses its OBB, including the visual hole.
    half.set(Math.abs(d[1]),Math.abs(d[1]),Math.abs(d[1]-d[0])/2);
    if(source.flags?.[0]===1)center.z=(d[1]-d[0])/2;
  }
  else return null;
  return { center, half };
}
function worldBounds(local, matrix) {
  const e = matrix.elements, center = local.center.clone().applyMatrix4(matrix);
  const edges = [new THREE.Vector3(e[0], e[1], e[2]).multiplyScalar(local.half.x),
    new THREE.Vector3(e[4], e[5], e[6]).multiplyScalar(local.half.y), new THREE.Vector3(e[8], e[9], e[10]).multiplyScalar(local.half.z)];
  if (edges.some(edge => edge.lengthSq() < 1e-14)) return null;
  return { center, edges };
}

// Separating-axis test for an affine EF box and an axis-aligned host body.
// Face normals and edge crosses also handle nonuniform inherited scales.
export function intersectsEffectBody(volume, position, radius = .4, halfHeight = 1.3) {
  const body = position.clone().add(new THREE.Vector3(0, halfHeight, 0)), delta = body.clone().sub(volume.center);
  const [a, b, c] = volume.edges, axes = [...WORLD_AXES, b.clone().cross(c), c.clone().cross(a), a.clone().cross(b)];
  for (const edge of volume.edges) for (const axis of WORLD_AXES) axes.push(edge.clone().cross(axis));
  for (const axis of axes) {
    if (axis.lengthSq() < 1e-16) continue;
    const reach = volume.edges.reduce((sum, edge) => sum + Math.abs(edge.dot(axis)), 0)
      + radius * (Math.abs(axis.x) + Math.abs(axis.z)) + halfHeight * Math.abs(axis.y);
    if (Math.abs(delta.dot(axis)) > reach + 1e-8 * axis.length()) return false;
  }
  return true;
}

function activeIntervals(state, attack, fps) {
  const offset = state.previousEffectTime ?? Math.max(0, ((state.previousFrame ?? state.frame) - state.pose.start) / fps);
  const intervals = state.frameIntervals || [{ from: state.previousFrame ?? state.frame, to: state.frame,
    timeFrom: 0, timeTo: Math.max(0, (state.effectTime ?? (state.frame - state.pose.start) / fps) - offset) }];
  const result = [];
  for (const range of intervals) {
    const from = Math.max(range.from, attack.start), to = Math.min(range.to, attack.end + 1 - 1e-7);
    if (to < from || range.from >= attack.end + 1) continue;
    const timeAt = frame => offset + (range.to > range.from ? THREE.MathUtils.lerp(range.timeFrom, range.timeTo, (frame - range.from) / (range.to - range.from)) : range.timeTo);
    result.push({ from, to, start: timeAt(from), end: timeAt(to) });
  }
  return result;
}

export class NativeEffectContacts {
  constructor({ manifest, bodyRadius = .4 } = {}) {
    this.manifest = manifest; this.bodyRadius = bodyRadius; this.actors = new Map(); this.timelines=new Map(); this.disposed = false;
  }
  _graph(actor,id,serial){
    const graph={...createEffectTransforms(actor,this.manifest.effects[id],this.manifest),id,serial};
    graph.attackNodes=graph.nodes.filter(node=>/^[aA]/.test(node.source.name)&&nativeEffectBounds(node.source));
    this.actors.set(actor,graph);return graph;
  }
  beginStep(actor,state){
    if(this.disposed||!actor||!state)return;
    if(actor.dead||actor.disposed||actor.scriptRemoved){this.clearActor(actor);return;}
    let record=this.timelines.get(actor);
    if(!record){record={clock:0,serial:null,effects:[]};this.timelines.set(actor,record);}
    for(const segment of state.segments||[state]){
      const start=record.clock,id=String(segment.pose?.raw?.fields.effectid||'').toLowerCase(),definition=this.manifest.effects[id];
      if(!segment.blend&&record.serial!==segment.serial){
        record.serial=segment.serial;
        if(definition?.nodes.some(node=>/^[aA]/.test(node.name)&&nativeEffectBounds(node))){
          const graph=this._graph(actor,id,segment.serial),born=start-(segment.previousEffectTime||0);
          const end=born+Math.max(...graph.attackNodes.map(node=>node.source.keys.at(-1)[0]));
          record.effects.push({graph,born,end});
          if(record.effects.length>16)record.effects.shift();
        }
      }
      // 0055da50 queries all living owner effects, not only the current POS
      // effect ID. An automatic phase with EffectID0 does not erase its caster.
      segment[EFFECT_STEP]=record.effects.filter(effect=>effect.end>=start-1e-7).map(effect=>({graph:effect.graph,offset:start-effect.born}));
      record.clock+=Math.max(0,segment.consumed||0);
      record.effects=record.effects.filter(effect=>effect.end>=record.clock-1e-7);
    }
  }
  sample(actor, state, attack, fps = 30) {
    if (this.disposed || !actor || actor.dead || actor.disposed || actor.scriptRemoved || actor.combat?.reacting || state.blend || !attack.bones?.includes('effect')) return [];
    if(state[EFFECT_STEP])return state[EFFECT_STEP].flatMap(({graph,offset})=>this._sampleGraph(actor,{...state,previousEffectTime:offset,effectTime:offset+(state.consumed||0)},attack,fps,graph));
    const id = String(state.pose?.raw?.fields.effectid || '').toLowerCase(), definition = this.manifest.effects[id];
    if (!definition) return [];
    let graph = this.actors.get(actor);
    if (!graph || graph.serial !== state.serial || graph.id !== id) {
      graph = this._graph(actor,id,state.serial);
    }
    return this._sampleGraph(actor,state,attack,fps,graph);
  }
  _sampleGraph(actor,state,attack,fps,graph){
    const id=graph.id;
    if (!graph.attackNodes.length) return [];
    const volumes = [], savedFrame = actor.character.frame, savedSource = actor.character.source;
    try {
      for (const range of activeIntervals(state, attack, fps)) {
        const count = Math.min(NATIVE_EFFECT_CONTACT_ADAPTER.maxSamplesPerInterval, Math.max(1, Math.ceil((range.end - range.start) / NATIVE_EFFECT_CONTACT_ADAPTER.sampleStep)));
        const times = new Set(Array.from({ length: count + 1 }, (_, i) => THREE.MathUtils.lerp(range.start, range.end, i / count)));
        // Include authored discontinuities as well as regular host samples.
        for (const node of graph.attackNodes) for (const key of node.source.keys) if (key[0] >= range.start && key[0] <= range.end) times.add(key[0]);
        for (const time of [...times].sort((a, b) => a - b)) {
          const weight = range.end > range.start ? (time - range.start) / (range.end - range.start) : 1;
          actor.character.setPoseFrame?.(state.source ?? state.pose.source, THREE.MathUtils.lerp(range.from, range.to, weight));
          setEffectTime(graph, time);
          for (const node of graph.attackNodes) {
            const { source } = node;
            if (time < source.keys[0][0] || time > source.keys.at(-1)[0]) continue;
            const matrix = effectNodeMatrix(graph, node); if (!matrix) continue;
            const box = worldBounds(nativeEffectBounds(source), matrix); if (!box) continue;
            volumes.push({ ...box, effectId: id, nodeName: source.name, time });
          }
        }
      }
    } finally {
      if (Number.isFinite(savedFrame) && savedSource != null) actor.character.setPoseFrame?.(savedSource, savedFrame);
    }
    return volumes;
  }
  contact(volumes, target) {
    if (this.disposed || !target || target.dead || target.disposed || target.scriptRemoved) return null;
    for (const volume of volumes) if (intersectsEffectBody(volume, target.root.position, this.bodyRadius, NATIVE_EFFECT_CONTACT_ADAPTER.bodyHalfHeight)) {
      return { point: target.root.position.clone().add(new THREE.Vector3(0, NATIVE_EFFECT_CONTACT_ADAPTER.bodyHalfHeight, 0)),
        effectId: volume.effectId, effectNode: volume.nodeName, effectTime: volume.time, contactSource: 'effect' };
    }
    return null;
  }
  clearActor(actor) { this.actors.delete(actor); this.timelines.delete(actor); }
  clear() { this.actors.clear(); this.timelines.clear(); }
  dispose() { this.clear(); this.disposed = true; }
}
