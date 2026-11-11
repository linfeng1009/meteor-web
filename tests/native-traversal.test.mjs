import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {traversalTap,NATIVE_ROLL_POSES,NATIVE_DASH_POSES,nativeDashPose} from '../dist/native-traversal.js';

test('crouched released double taps map each direction to its original native roll pose',()=>{
  for(const [direction,poseId] of Object.entries(NATIVE_ROLL_POSES)){
    const first=traversalTap(null,{direction,time:10,crouched:true,allowed:true});assert.equal(first.poseId,null);
    const second=traversalTap(first.tap,{direction,time:10.2,crouched:true,allowed:true});assert.equal(second.poseId,poseId);assert.equal(second.tap,null);
  }
});
test('standing released double taps use verified weapon remaps and never guess unsupported families',()=>{
  for(const [weapon,mapping] of Object.entries(NATIVE_DASH_POSES))for(const [direction,poseId] of Object.entries(mapping)){
    const first=traversalTap(null,{direction,time:10,crouched:false,allowed:true,weapon});
    assert.equal(traversalTap(first.tap,{direction,time:10.2,crouched:false,allowed:true,weapon}).poseId,poseId);
    assert.equal(traversalTap(first.tap,{direction,time:10.2,crouched:true,allowed:true,weapon}).poseId,null);
  }
  for(const weapon of ['dagger','dual','hammer','ninja'])assert.equal(nativeDashPose(weapon,'forward'),null);
  const previous={direction:'forward',time:10,crouched:false,weapon:'sword'};
  assert.equal(traversalTap(previous,{direction:'forward',time:10.2,crouched:false,allowed:true,weapon:'spear'}).poseId,null);
});
test('standing pose mappings agree with preserved original weapon remappers',async()=>{
  const base='work/native-ai-combat-2026-11-08/dodge-pose-scan/';
  for(const [weapon,file] of Object.entries({sword:base+'004dd790_FUN_004dd790.c',spear:base+'004ddef0_FUN_004ddef0.c',blade:base+'004de640_FUN_004de640.c',dart:base+'004df600_FUN_004df600.c',wheel:base+'004dfd50_FUN_004dfd50.c',musket:'work/musket-mission-audit/native-state/004dee40_FUN_004dee40.c',qiankun:'work/all-weapons-audit/native-modes/004e2860_FUN_004e2860.c',knuckle:'work/knuckle-audit/native-callbacks/004e3c00_FUN_004e3c00.c'})){
    const source=await readFile(new URL('../'+file,import.meta.url),'utf8');
    for(const [direction,input] of Object.entries({forward:164,right:167,left:170,back:173})){
      const match=source.match(new RegExp(`case 0x${input.toString(16)}:\\s*(?:return|param_2 =)\\s*(0x[0-9a-f]+|[0-9]+)`));
      assert.ok(match,`${weapon}/${direction}`);assert.equal(nativeDashPose(weapon,direction),Number(match[1]));
    }
  }
});
test('slow, standing, opposite, interrupted and backwards-time taps cannot roll',()=>{
  const previous={direction:'forward',time:10,crouched:true};
  for(const options of [{time:10.5},{crouched:false},{direction:'back'},{allowed:false},{time:9},{time:10}]){
    assert.equal(traversalTap(previous,{direction:'forward',time:10.1,crouched:true,allowed:true,...options}).poseId,null);
  }
  assert.equal(traversalTap({...previous,crouched:false},{direction:'forward',time:10.1,crouched:true,allowed:true}).poseId,null);
});
