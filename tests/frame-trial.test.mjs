import test from 'node:test';
import assert from 'node:assert/strict';
import {summarizeFrameTrial,assessFrameTrial} from '../dist/frame-trial.js';

test('finite frame trial retains real long frames in FPS, tail counts and percentiles',()=>{
  const frames=[...Array(99).fill(16),300],original=[...frames];
  const report=summarizeFrameTrial(frames,[{cpu:2,world:1,camera:.2,render:.8},{cpu:4,world:2,camera:.4,render:1.6}]);
  assert.equal(report.fps,100000/1884);assert.equal(report.p95Ms,16);assert.equal(report.p99Ms,16);assert.equal(report.maxMs,300);
  assert.equal(report.over25Ms,1);assert.equal(report.over50Ms,1);assert.equal(report.cpuMs,3);assert.equal(report.worldMs,1.5);
  assert.deepEqual(frames,original,'measurement must not reorder the input trace');
});

test('finite trial distinguishes consistent 30/60/144Hz and rejects missing/invalid data',()=>{
  for(const hz of [30,60,144]){
    const report=summarizeFrameTrial(Array(hz*10).fill(1000/hz),[]);
    assert.ok(Math.abs(report.fps-hz)<1e-8);assert.ok(Math.abs(report.durationMs-10000)<1e-7);
  }
  for(const frames of [[],[0],[Infinity],[NaN],[-1]])assert.throws(()=>summarizeFrameTrial(frames,[]));
});

test('manual trial requires lock events and actual turn; hidden, resized and stalled traces require review',()=>{
  const base={mode:'manual',hidden:false,resized:false,maxMs:20,lockedEvents:40,angleChange:1.2,angleTravel:1.2,displacement:0};
  assert.equal(assessFrameTrial(base).validForComparison,true);
  for(const change of [{lockedEvents:0},{angleChange:0,angleTravel:0},{hidden:true},{resized:true},{maxMs:1000},{angleChange:null},{displacement:NaN},{angleTravel:Infinity},{invalidState:true}])assert.equal(assessFrameTrial({...base,...change}).validForComparison,false);
  assert.equal(assessFrameTrial({...base,mode:'orbit',lockedEvents:0}).validForComparison,true);
  assert.equal(assessFrameTrial({...base,maxMs:300}).validForComparison,true,'real short stalls must remain measurable, not be filtered away');
  assert.equal(assessFrameTrial({...base,angleChange:0,angleTravel:2.4}).validForComparison,true,'back-and-forth mouse turns must not fail because net rotation is zero');
});
