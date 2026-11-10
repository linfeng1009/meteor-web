import test from 'node:test';
import assert from 'node:assert/strict';
import {traversalTap,NATIVE_ROLL_POSES} from '../dist/native-traversal.js';

test('crouched released double taps map each direction to its original native roll pose',()=>{
  for(const [direction,poseId] of Object.entries(NATIVE_ROLL_POSES)){
    const first=traversalTap(null,{direction,time:10,crouched:true,allowed:true});assert.equal(first.poseId,null);
    const second=traversalTap(first.tap,{direction,time:10.2,crouched:true,allowed:true});assert.equal(second.poseId,poseId);assert.equal(second.tap,null);
  }
});
test('slow, standing, opposite, interrupted and backwards-time taps cannot roll',()=>{
  const previous={direction:'forward',time:10,crouched:true};
  for(const options of [{time:10.5},{crouched:false},{direction:'back'},{allowed:false},{time:9},{time:10}]){
    assert.equal(traversalTap(previous,{direction:'forward',time:10.1,crouched:true,allowed:true,...options}).poseId,null);
  }
  assert.equal(traversalTap({...previous,crouched:false},{direction:'forward',time:10.1,crouched:true,allowed:true}).poseId,null);
});
