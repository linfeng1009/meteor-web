import test from 'node:test';
import assert from 'node:assert/strict';
import * as T from '../dist/vendor/three.module.js';
import {NetworkGame,NetworkReplicaMotion} from '../dist/network-game.js';

function fixture(count=16){
  const pose={id:144,start:0,end:1000,attacks:[]},attack={id:262,start:0,end:30,attacks:[{}]};
  const actors=Array.from({length:count},(_,i)=>({networkId:String(i),root:new T.Group(),hp:1000,
    combat:{data:{poses:new Map([[144,pose],[262,attack]])},timeline:{pose},play(id){this.timeline.pose=this.data.poses.get(id);}},
    character:{source:0,frame:0,setPoseFrame(source,frame){this.source=source;this.frame=frame;}}}));
  const game={hero:actors[0],enemies:actors.slice(1),scene:new T.Scene(),pause(){},_hud(){},_updatePresentation(){}};
  const session=new NetworkGame(game,{host:false,streamActive:true,playerId:'0',send(){}},{players:actors.map(a=>({id:a.networkId}))});session.play();
  return {game,session,actors};
}

for(const hz of [30,60])for(const renderHz of [60,144])test(`${hz}Hz快照/${renderHz}Hz呈现：16人持续移动与转身在抖动下保持均匀步长`,()=>{
  const {game,session,actors}=fixture(),duration=3,speed=8;
  const packets=Array.from({length:hz*duration},(_,i)=>({at:i/hz+[0,.012,.002,.009][i%4],frame:{sequence:i+1,time:i/hz,
    players:actors.map((a,index)=>({id:a.networkId,position:[index*3+speed*i/hz,0,0],angle:3+i/hz,hp:1000,maxHp:1000,rage:0,pose:144,source:0,frame:30*i/hz,serial:1,effectTime:0}))}}));
  const previous=actors.map(()=>0),steps=[],lags=[];let index=0;
  try{
    for(let render=0;render<duration*renderHz;render++){
      const time=render/renderHz;while(index<packets.length&&packets[index].at<=time+1e-9)session.receive(packets[index++].frame);
      game._updatePresentation(1/renderHz);
      for(let i=0;i<actors.length;i++){const x=actors[i].root.position.x;if(time>.5&&time<duration-.1){steps.push(x-previous[i]);lags.push((i*3+speed*time-x)/speed);assert.equal(actors[i].hp,1000);}previous[i]=x;}
    }
    assert.ok(steps.every(step=>Math.abs(step-speed/renderHz)<1e-6),'网络到达抖动不能变成移动停顿或忽快忽慢');
    assert.ok(Math.max(...lags)<.07,'呈现保持有界延迟，不累积快照积压');
    for(let i=0;i<renderHz;i++)game._updatePresentation(1/renderHz);
    for(let i=0;i<actors.length;i++)assert.equal(actors[i].root.position.x,packets[index-1].frame.players[i].position[0],'断流不外推位置');
  }finally{session.dispose();}
});

test('攻击动作与生命变化按服务器时刻发生，不提前显示未来攻击或跨动作混帧',()=>{
  const {game,session,actors}=fixture(2),state=(pose,serial,frame,hp)=>({id:'0',position:[0,0,0],angle:0,pose,serial,frame,hp,maxHp:1000,rage:0,source:0,effectTime:0});
  try{
    session.receive({sequence:1,time:1,players:[state(144,1,10,1000)]});
    session.receive({sequence:2,time:1.1,players:[state(262,2,3,900)]});
    game._updatePresentation(.075);assert.equal(actors[0].hp,1000);assert.equal(actors[0].combat.timeline.pose.id,144);assert.equal(actors[0].character.frame,10);
    game._updatePresentation(.08);assert.equal(actors[0].hp,900);assert.equal(actors[0].combat.timeline.pose.id,262);assert.equal(actors[0].character.frame,3);
  }finally{session.dispose();}
});

test('循环走路动画按循环端点衔接，死亡与瞬移不被插值成滑行',()=>{
  const {actors,session}=fixture(1),actor=actors[0],motion=new NetworkReplicaMotion();
  Object.assign(actor.combat.timeline.pose,{loopStart:10,loopEnd:20});
  const a={pose:144,serial:1,source:0,frame:19,position:[0,0,0],angle:Math.PI-.1,dead:false};
  const b={...a,frame:11,position:[2,0,0],angle:-Math.PI+.1};
  try{motion.present(actor,a,b,.75);assert.equal(actor.character.frame,10.5);assert.equal(actor.root.position.x,1.5);assert.ok(Math.abs(actor.root.rotation.y-(Math.PI+.05))<1e-9);
    motion.present(actor,a,{...b,dead:true},.75);assert.equal(actor.root.position.x,0);
    motion.present(actor,a,{...b,position:[20,0,0]},.75);assert.equal(actor.root.position.x,0);
  }finally{session.dispose();}
});

test('权威混合在同一呈现时钟上连续推进，动作切换不补播旧混合',()=>{
  const {game,session,actors}=fixture(1),actor=actors[0],calls=[];
  actor.character.setPoseBlend=function(from,to,weight){this.source=to.source;this.frame=to.frame;calls.push({from,to,weight});};
  const state=(frame,weight)=>({id:'0',position:[0,0,0],angle:0,pose:144,serial:1,source:0,frame,hp:1000,maxHp:1000,rage:0,effectTime:0,
    blend:{from:{source:0,frame:0},to:{source:0,frame},weight,duration:.2}});
  try{session.receive({sequence:1,time:0,players:[state(10,.2)]});session.receive({sequence:2,time:.1,players:[state(20,.8)]});
    game._updatePresentation(.1);assert.ok(Math.abs(calls.at(-1).weight-.47)<1e-8);const first=calls.at(-1).from;
    game._updatePresentation(.055);assert.equal(calls.at(-1).weight,.8);assert.equal(calls.at(-1).from,first);
    session.receive({sequence:3,time:.2,players:[{...state(3,0),pose:262,serial:2,blend:null}]});game._updatePresentation(.1);
    assert.equal(actor.combat.timeline.pose.id,262);assert.equal(actor.character.frame,3);assert.equal(session.presentation.samples.get(actor).blend,undefined);
  }finally{session.dispose();}
});
