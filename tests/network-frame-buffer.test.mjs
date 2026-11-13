import test from 'node:test';
import assert from 'node:assert/strict';
import {NetworkFrameBuffer} from '../dist/network-frame-buffer.js';
const frame=(sequence,time=sequence/30)=>({sequence,time});

test('快照缓冲吸收十余毫秒抖动，保持30Hz播放且不预测权威状态',()=>{
  let now=0;const shown=[],buffer=new NetworkFrameBuffer(f=>shown.push({sequence:f.sequence,at:now}));
  const arrivals=Array.from({length:30},(_,i)=>({at:i/30+[0,.012,.002,.009][i%4],frame:frame(i+1,i/30)}));
  let index=0;const step=1/600;
  for(now=0;now<1.1;now+=step){while(index<arrivals.length&&arrivals[index].at<=now+1e-9)buffer.receive(arrivals[index++].frame);buffer.update(step);}
  assert.equal(shown.length,30);assert.deepEqual(shown.map(f=>f.sequence),arrivals.map(f=>f.frame.sequence));
  const gaps=shown.slice(2).map((f,i)=>f.at-shown[i+1].at);
  assert.ok(gaps.every(gap=>Math.abs(gap-1/30)<.002));
  for(let i=0;i<600;i++)buffer.update(step);assert.equal(shown.length,30,'网络停止后不自行产生状态');
});
test('旧序号和时间倒退不打断播放，长断流恢复不慢放数秒积压',()=>{
  const seen=[],buffer=new NetworkFrameBuffer(f=>seen.push(f.sequence));
  buffer.receive(frame(1));buffer.receive(frame(2));buffer.receive(frame(1));buffer.receive(frame(3,0));buffer.update(.1);
  assert.deepEqual(seen,[1,2]);buffer.update(10);buffer.receive(frame(4,8));buffer.update(.04);assert.deepEqual(seen,[1,2,4]);
});
test('缓冲有数量上限，结算直接显示并清除旧状态，退出释放全部快照',()=>{
  const shown=[],buffer=new NetworkFrameBuffer(f=>shown.push(f.sequence));buffer.receive(frame(1));
  for(let i=2;i<=30;i++)buffer.receive(frame(i));assert.ok(buffer.frames.length<=8);
  buffer.receive({...frame(31),result:{reason:'score'}});assert.equal(shown.at(-1),31);assert.equal(buffer.frames.length,0);
  buffer.update(1);assert.equal(shown.at(-1),31);buffer.clear();assert.equal(buffer.clock,null);assert.equal(buffer.latestSequence,0);
});

test('同一服务器时刻只保留最新快照，减少推送与轮询交错带来的重复呈现',()=>{
  const seen=[],buffer=new NetworkFrameBuffer(f=>seen.push(f.sequence));buffer.receive(frame(1,0));
  buffer.receive(frame(2,.03));buffer.receive(frame(3,.03));buffer.receive(frame(4,.03));
  assert.equal(buffer.frames.length,1);buffer.update(.1);assert.deepEqual(seen,[1,4]);
});
