import test from 'node:test';
import assert from 'node:assert/strict';
import { createMouseLook, turnMouseCamera } from '../dist/mouse-look.js';
import { defaultBindings } from '../dist/keybindings.js';

function fixture(){
  const doc=new EventTarget(),moves=[],actions=[],events=[];let active=true,requests=0;
  const canvas={ownerDocument:doc,requestPointerLock(){requests++;doc.pointerLockElement=canvas;doc.dispatchEvent(new Event('pointerlockchange'));}};
  doc.exitPointerLock=()=>{doc.pointerLockElement=null;doc.dispatchEvent(new Event('pointerlockchange'));};
  const control=createMouseLook(canvas,{active:()=>active,move:(...args)=>moves.push(args),action:name=>actions.push(name),onUnlock:()=>events.push('unlock'),onError:()=>events.push('error')});
  const mouse=(button=0,pointerType='mouse')=>({button,pointerType,preventDefault(){}});
  const move=(x,y)=>{const e=new Event('mousemove');Object.assign(e,{movementX:x,movementY:y});doc.dispatchEvent(e);};
  return {doc,canvas,control,moves,actions,events,mouse,move,setActive:v=>active=v,get requests(){return requests;}};
}
test('entry click only locks; subsequent clicks attack and mouse motion rotates freely',()=>{
  const h=fixture();h.move(10,4);assert.deepEqual(h.moves,[]);
  assert.equal(h.control.pointerDown(h.mouse()),true);assert.equal(h.control.locked,true);assert.deepEqual(h.actions,[]);
  h.move(15,-8);assert.deepEqual(h.moves,[[15,-8]]);
  h.control.pointerDown(h.mouse(0));h.control.pointerDown(h.mouse(2));assert.deepEqual(h.actions,['attack','jump']);h.control.dispose();
});
test('explicit pause releases without triggering another pause; browser unlock notifies once',()=>{
  const h=fixture();h.control.request();h.control.release();assert.equal(h.control.locked,false);assert.deepEqual(h.events,[]);
  h.control.request();h.doc.exitPointerLock();assert.deepEqual(h.events,['unlock']);
  h.doc.dispatchEvent(new Event('pointerlockchange'));assert.deepEqual(h.events,['unlock']);h.control.dispose();
});
test('paused input does nothing and touch retains its original controls',()=>{
  const h=fixture();assert.equal(h.control.pointerDown(h.mouse(0,'touch')),false);
  h.control.request();h.setActive(false);h.move(20,8);h.control.pointerDown(h.mouse());assert.deepEqual(h.moves,[]);assert.deepEqual(h.actions,[]);
  h.control.dispose();h.move(20,8);assert.deepEqual(h.moves,[]);
});
test('rejected and legacy pointer lock requests are handled without uncaught errors',async()=>{
  const h=fixture();h.canvas.requestPointerLock=()=>Promise.reject(Error('denied'));h.control.request();await Promise.resolve();assert.deepEqual(h.events,['error']);
  h.doc.dispatchEvent(new Event('pointerlockerror'));assert.deepEqual(h.events,['error']);
  h.canvas.requestPointerLock=()=>{throw Error('denied');};h.control.request();assert.deepEqual(h.events,['error','error']);
  delete h.canvas.requestPointerLock;assert.equal(h.control.request(),false);assert.equal(h.control.pointerDown(h.mouse()),false);h.control.dispose();
});
test('late lock after pause is immediately released',()=>{
  const h=fixture();h.canvas.requestPointerLock=()=>undefined;h.control.request();h.control.release();h.doc.pointerLockElement=h.canvas;h.doc.dispatchEvent(new Event('pointerlockchange'));assert.equal(h.control.locked,false);assert.deepEqual(h.events,[]);h.control.dispose();
});

test('mouse bindings can be swapped and held defense releases on button up or unlock',()=>{
  const h=fixture(),bindings=defaultBindings();bindings.attack=['Mouse2'];bindings.jump=['Mouse0'];h.control.setBindings(bindings);h.control.request();
  h.control.pointerDown(h.mouse(0));h.control.pointerUp(h.mouse(0));h.control.pointerDown(h.mouse(2));assert.deepEqual(h.actions.slice(0,3),['jump','jump','attack']);
  h.control.pointerUp(h.mouse(2));bindings.attack=['Space'];bindings.guard=['Mouse2'];h.control.setBindings(bindings);h.actions.length=0;
  h.control.pointerDown(h.mouse(2));h.control.release();assert.deepEqual(h.actions,['guard','guard']);h.control.dispose();
});
test('free camera rotates but combat lock rejects mouse override, including vertical movement',()=>{
  const game={elapsed:10,cameraAngle:0,cameraPitch:.4,locked:null};assert.equal(turnMouseCamera(game,20,-10),true);assert.equal(game.cameraAngle,-.1);
  const angle=game.cameraAngle,pitch=game.cameraPitch;game.locked={dead:false,disposed:false};assert.equal(turnMouseCamera(game,100,100),false);assert.equal(game.cameraAngle,angle);assert.equal(game.cameraPitch,pitch);
  game.locked.dead=true;assert.equal(turnMouseCamera(game,20,0),true);
});
