import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import * as T from '../dist/vendor/three.module.js';
import {NativePoisonFeedback,hasNativePoison,POISON_ADAPTER} from '../dist/native-poison-feedback.js';
import {useNativeScriptItem,updateNativeScriptItems,clearNativeScriptItems} from '../dist/native-items.js';
const manifest=JSON.parse(await readFile(new URL('../dist/assets/original/poison-vfx.json',import.meta.url)));
const records=JSON.parse(await readFile(new URL('../dist/assets/original/characters/meteor-res-data.json',import.meta.url))).allRecords;
const actor=()=>({root:new T.Group(),hp:1000,maxHp:1000,scriptItems:[],activeItems:[]});
const fixture=()=>new NativePoisonFeedback(new T.Scene(),manifest.effects.attrpois,new T.Texture());
const poison=a=>useNativeScriptItem(a,records.find(r=>r.type===2&&r.id===12));
test('中毒表现保留原AttrPOIS三组绿色粒子与源哈希',async()=>{
 const raw=await readFile(new URL('../dist/assets/original/sounds/definitions/AttrPOIS.ef',import.meta.url));assert.equal(createHash('sha256').update(raw).digest('hex'),manifest.effects.attrpois.sha256);
 assert.equal(manifest.effects.attrpois.nodes.length,3);
 for(const n of manifest.effects.attrpois.nodes){assert.equal(n.type,'PARTICLE');assert.equal(n.texture,'zs2.tga');assert.deepEqual(n.keys[0].slice(11,14),[0,.250980406999588,0]);}
});
test('真实施毒、刷新、扣血与到期驱动持续特效而不重复创建绘制对象',()=>{
 const a=actor(),v=fixture();poison(a);v.update(.4,[a]);const geometry=v.mesh.geometry,material=v.mesh.material,age=v.actors.get(a).age;
 assert.equal(v.mesh.geometry.drawRange.count,24);updateNativeScriptItems(a,1.5);poison(a);v.update(.1,[a]);assert.ok(v.actors.get(a).age>age);assert.equal(v.actors.size,1);assert.equal(v.mesh.geometry,geometry);assert.equal(v.mesh.material,material);
 const positions=Array.from(v.positions);v.update(0,[a]);assert.deepEqual(Array.from(v.positions),positions);
 a.root.position.set(3,2,5);v.update(0,[a]);assert.ok(Math.abs(v.positions[0]-positions[0]-3)<1e-5);assert.ok(Math.abs(v.positions[1]-positions[1]-2)<1e-5);
 updateNativeScriptItems(a,61);v.update(.1,[a]);assert.equal(v.actors.size,0);assert.equal(v.mesh.visible,false);v.dispose();
});
test('客人只按权威状态显示，空快照、死亡、移除和重生清除特效',()=>{
 const a=actor(),v=fixture();poison(a);a.networkItemStatuses=[];assert.equal(hasNativePoison(a),false);
 a.networkItemStatuses=a.scriptItems.map(x=>({...x}));v.update(.1,[a]);assert.equal(v.actors.size,1);
 for(const field of ['dead','disposed','scriptRemoved']){a[field]=true;v.update(.1,[a]);assert.equal(v.mesh.visible,false);a[field]=false;v.update(.1,[a]);assert.equal(v.actors.size,1);}
 a.networkItemStatuses=[];v.update(.1,[a]);assert.equal(v.mesh.visible,false);delete a.networkItemStatuses;clearNativeScriptItems(a);v.update(.1,[a]);assert.equal(v.actors.size,0);v.dispose();v.dispose();
});
test('长时间循环与多人中毒有界，普通增益不冒毒气，清场释放一次',()=>{
 const v=fixture(),actors=Array.from({length:100},()=>{const a=actor();poison(a);return a;});v.update(3600,actors);assert.equal(v.actors.size,POISON_ADAPTER.maxActors);assert.equal(v.mesh.geometry.drawRange.count,768);assert.ok(v.positions.every(Number.isFinite));
 let disposed=0;v.mesh.geometry.addEventListener('dispose',()=>disposed++);v.clear();assert.equal(v.actors.size,0);v.dispose();v.dispose();assert.equal(disposed,1);
 const a=actor();a.scriptItems=[{id:3,statKey:4,value:20,period:0,remaining:30}];assert.equal(hasNativePoison(a),false);
});
