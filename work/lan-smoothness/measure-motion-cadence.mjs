import {execFileSync} from 'node:child_process';
import * as T from '../../dist/vendor/three.module.js';
import {NetworkFrameBuffer} from '../../dist/network-frame-buffer.js';
import {NetworkReplicaMotion} from '../../dist/network-game.js';
const base='390e0b9',show=path=>execFileSync('git',['show',`${base}:${path}`],{encoding:'utf8'});
const game=show('dist/network-game.js'),source=game.slice(game.indexOf('export class NetworkReplicaMotion'),game.indexOf('export class NetworkGame'));
const load=code=>import('data:text/javascript;base64,'+Buffer.from(code).toString('base64'));
const OldMotion=(await load(source)).NetworkReplicaMotion,OldBuffer=(await load(show('dist/network-frame-buffer.js'))).NetworkFrameBuffer;
function run(hz,renderHz,updated){
 const actor={root:new T.Group(),character:{source:0,frame:0,setPoseFrame(source,frame){this.source=source;this.frame=frame;}},combat:{timeline:{pose:{start:0,end:1000}}}},motion=new (updated?NetworkReplicaMotion:OldMotion)();let previous=0;
 const buffer=new (updated?NetworkFrameBuffer:OldBuffer)(f=>{motion.receive(actor,f.players[0],f.time-previous);previous=f.time;},{delay:updated?.055:1/60});
 const packets=Array.from({length:hz*3},(_,i)=>({at:i/hz+[0,.012,.002,.009][i%4],frame:{sequence:i+1,time:i/hz,players:[{position:[8*i/hz,0,0],angle:i/hz,source:0,frame:30*i/hz,pose:144,serial:1,dead:false}]}}));
 let index=0,last=0;const steps=[],lags=[];
 for(let render=0;render<3*renderHz;render++){const time=render/renderHz;while(index<packets.length&&packets[index].at<=time+1e-9)buffer.receive(packets[index++].frame);buffer.update(1/renderHz);
  if(updated){const sample=buffer.sample;motion.present(actor,sample.from.players[0],sample.to.players[0],sample.weight);}else motion.update(actor,1/renderHz);
  const x=actor.root.position.x;if(time>.5&&time<2.9){steps.push(x-last);lags.push((8*time-x)/8*1000);}last=x;
 }
 const mean=steps.reduce((a,b)=>a+b,0)/steps.length,sd=Math.sqrt(steps.reduce((a,b)=>a+(b-mean)**2,0)/steps.length);
 return {freezeFrames:steps.filter(d=>d<1e-6).length,stepCV:+(sd/mean).toFixed(4),meanPresentationLagMs:+(lags.reduce((a,b)=>a+b,0)/lags.length).toFixed(2)};
}
console.log(JSON.stringify({baseline:base,scope:'Deterministic presentation, not GPU FPS or physical LAN measurement',cases:[30,60].flatMap(hz=>[60,144].map(renderHz=>({snapshotHz:hz,renderHz,before:run(hz,renderHz,false),after:run(hz,renderHz,true)})))},null,2));
