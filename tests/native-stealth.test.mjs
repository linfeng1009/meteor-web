import test from 'node:test';import assert from 'node:assert/strict';import {readFile}from'node:fs/promises';
import * as T from '../dist/vendor/three.module.js';
import {NativeStealthFeedback}from'../dist/native-stealth-feedback.js';
import {nativeIsInvisible,useNativeScriptItem,updateNativeScriptItems,clearNativeScriptItems}from'../dist/native-items.js';
import {nativeCanDiscover,findNativeEnemy}from'../dist/native-awareness.js';
import {acquireCombatTarget,validCombatTarget}from'../dist/combat-targeting.js';
const records=JSON.parse(await readFile(new URL('../dist/assets/original/characters/meteor-res-data.json',import.meta.url),'utf8')).allRecords;
const item=id=>records.find(r=>r.type===2&&r.id===id);
const actor=team=>({root:new T.Group(),hp:1000,team,activeItems:[],scriptItems:[],character:{},nameplate:{visible:true}});
test('原风水与隐忍使用同一隐身属性，各自寿命与刷新保留，镜像以权威状态为准',()=>{
 for(const[id,duration]of[[7,60],[36,120]]){const a=actor(1);assert.equal(nativeIsInvisible(a),false);useNativeScriptItem(a,item(id));assert.equal(nativeIsInvisible(a),true);assert.equal(a.scriptItems[0].remaining,duration);assert.equal(useNativeScriptItem(a,item(id)).refreshed,true);assert.equal(a.scriptItems.length,1);updateNativeScriptItems(a,duration+.2);assert.equal(nativeIsInvisible(a),false);}
 const guest=actor(1);guest.networkItemStatuses=[{statKey:10,value:1,remaining:40}];assert.equal(nativeIsInvisible(guest),true);guest.networkItemStatuses=[];assert.equal(nativeIsInvisible(guest),false);
});
test('隐身阻止新发现，保留原短距离追击记忆，也不授予攻击免疫',()=>{
 const observer=actor(1),target=actor(2);target.root.position.z=5;
 assert.equal(findNativeEnemy(observer,[target],()=>true),target);useNativeScriptItem(target,item(36));
 assert.equal(nativeCanDiscover(observer,target,()=>true),false);assert.equal(findNativeEnemy(observer,[target],()=>true),target);
 observer.awarenessTarget=null;assert.equal(findNativeEnemy(observer,[target],()=>true),null);
 assert.equal(acquireCombatTarget(observer,[target]),null);assert.equal(validCombatTarget(observer,target),true,'hit eligibility remains separate from new acquisition');
 clearNativeScriptItems(target);assert.equal(nativeCanDiscover(observer,target,()=>true),true);
});
test('隐身隔离共享材质，保留透明材质比例，不污染同模型同伴，到期恢复并释放克隆',()=>{
 const a=actor(2),b=actor(1),material=new T.MeshBasicMaterial({opacity:.8}),mesh=new T.Mesh(new T.BoxGeometry(),material),other=new T.Mesh(mesh.geometry,material);a.root.add(mesh);b.root.add(other);a.character.mesh=mesh;b.character.mesh=other;
 const vfx=new NativeStealthFeedback();let released=0;try{
  useNativeScriptItem(a,item(36));vfx.update([a,b],b);const copy=mesh.material;copy.addEventListener('dispose',()=>released++);
  assert.notEqual(copy,material);assert.ok(Math.abs(copy.opacity-.08)<1e-10);assert.equal(copy.transparent,true);assert.equal(other.material,material);assert.equal(material.opacity,.8);assert.equal(a.nameplate.visible,false);
  vfx.update([a,b],b);assert.equal(mesh.material,copy,'steady frames must reuse cloned materials');
  clearNativeScriptItems(a);vfx.update([a,b],b);assert.equal(mesh.material,material);assert.equal(a.nameplate.visible,true);assert.equal(released,1);assert.equal(vfx.actors.size,0);
 }finally{vfx.dispose();material.dispose();mesh.geometry.dispose();}
});
test('隐身中更换武器及外观会重建隔离，死亡和移出场景都清理',()=>{
 const a=actor(1),body=new T.Mesh(new T.BoxGeometry(),new T.MeshBasicMaterial()),vfx=new NativeStealthFeedback();a.root.add(body);a.character.mesh=body;useNativeScriptItem(a,item(36));
 try{vfx.update([a]);const first=body.material;let disposed=0;first.addEventListener('dispose',()=>disposed++);
  const weapon=new T.Mesh(body.geometry,new T.MeshBasicMaterial());const weaponMaterial=weapon.material;a.root.add(weapon);a.weaponModel=weapon;
  vfx.update([a]);assert.equal(disposed,1);assert.notEqual(weapon.material,weaponMaterial);
  a.dead=true;vfx.update([a]);assert.equal(weapon.material,weaponMaterial);assert.equal(vfx.actors.size,0);
  a.dead=false;vfx.update([a]);assert.equal(vfx.actors.size,1);vfx.update([]);assert.equal(vfx.actors.size,0);weaponMaterial.dispose();
 }finally{vfx.dispose();body.material.dispose();body.geometry.dispose();}
});
