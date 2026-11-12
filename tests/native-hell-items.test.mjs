import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { useNativeScriptItem, updateNativeScriptItems, clearNativeScriptItems, nativeScriptItemEffect } from '../dist/native-items.js';
import { nativeEffectiveStat } from '../dist/native-combat.js';
const data=JSON.parse(await readFile(new URL('../dist/assets/original/characters/meteor-res-data.json',import.meta.url),'utf8'));
const item=id=>data.allRecords.find(r=>r.type===2&&r.id===id);
const actor=()=>({hp:500,maxHp:3000,activeItems:[],scriptItems:[]});
test('original instant healing clamps to current effective maxHP and never installs a timed modifier',()=>{
  const target=actor(),result=useNativeScriptItem(target,item(15));assert.equal(target.hp,3000);assert.equal(result.healed,2500);assert.equal(result.duration,0);assert.equal(target.activeItems.length,0);
  assert.equal(useNativeScriptItem(target,item(15)).healed,0);assert.equal(target.hp,3000);
});
test('original attack boost19 applies150, refreshes without stacking and expires from the effective stat calculation',()=>{
  const target=actor();useNativeScriptItem(target,item(19));assert.equal(nativeEffectiveStat(3,100,target.activeItems),250);
  updateNativeScriptItems(target,20);useNativeScriptItem(target,item(19));assert.equal(target.scriptItems.length,1);assert.equal(target.scriptItems[0].remaining,9999.9);
  updateNativeScriptItems(target,10000);assert.equal(nativeEffectiveStat(3,100,target.activeItems),100);assert.equal(target.hp,500);
});
test('original maxHP boost20 changes the clamp used by subsequent healing; clear restores the base limit without inventing immediate damage',()=>{
  const target=actor();useNativeScriptItem(target,item(20));assert.equal(target.maxHp,9999);assert.equal(target.hp,500);
  useNativeScriptItem(target,item(15));useNativeScriptItem(target,item(15));assert.equal(target.hp,9999);
  useNativeScriptItem(target,item(20));assert.equal(target.maxHp,9999);assert.equal(target.activeItems.length,1);
  clearNativeScriptItems(target);assert.equal(target.maxHp,3000);assert.equal(target.hp,9999);assert.equal(target.activeItems.length,0);
  useNativeScriptItem(target,item(15));assert.equal(target.hp,3000,'native HP adjustment clamps to the restored effective maximum');
  assert.equal(nativeScriptItemEffect(item(7)).statKey,10,'recovered stat10 is invisibility, not invulnerability or rage');
  assert.equal(nativeScriptItemEffect(item(7)).duration,60);
});
