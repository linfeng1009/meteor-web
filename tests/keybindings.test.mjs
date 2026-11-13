import test from 'node:test';
import assert from 'node:assert/strict';
import { defaultBindings, validateBindings, loadBindings, saveBindings, KEY_BINDINGS_STORAGE, bindKeyboard } from '../dist/keybindings.js';

test('跳跃键真实松开与失焦取消分开，取消先于松键回调',()=>{
  const target=new EventTarget(),events=[],bindings=defaultBindings();bindings.jump=['KeyL'];
  const controller=bindKeyboard(target,{bindings,enabled:()=>true,action:(...args)=>events.push(args),onReset:()=>events.push(['clear',false])});
  const emit=type=>{const event=new Event(type,{cancelable:true});if(type!=='blur')Object.assign(event,{code:'KeyL'});target.dispatchEvent(event);};
  try{
    emit('keydown');emit('keyup');assert.deepEqual(events,[['jump',true],['jump',false]]);
    events.length=0;emit('keydown');emit('blur');assert.deepEqual(events,[['jump',true],['clear',false],['jump',false]]);
  }finally{controller.dispose();}
});

test('original PC defaults use mouse attack/jump, Space guard, Ctrl crouch and Q camera lock',()=>{
  const b=defaultBindings();assert.deepEqual(b.attack,['Mouse0']);assert.deepEqual(b.jump,['Mouse2']);assert.deepEqual(b.guard,['Space']);assert.deepEqual(b.crouch,['ControlLeft','ControlRight']);assert.deepEqual(b.lock,['KeyQ']);assert.equal(validateBindings(b),true);
});
test('holding Ctrl crouches and still allows movement, then releasing stops both actions',()=>{
  const h=harness();h.emit('keydown','ControlLeft',{ctrlKey:true});const move=h.emit('keydown','KeyW',{ctrlKey:true});
  assert.equal(move.defaultPrevented,true);assert.deepEqual(h.events,[['crouch',true],['forward',true]]);
  h.emit('keyup','KeyW',{ctrlKey:true});h.emit('keyup','ControlLeft');assert.deepEqual(h.events.slice(-2),[['forward',false],['crouch',false]]);h.controller.dispose();
});

test('saved bindings survive reload, and restoring defaults persists',()=>{
  const data=new Map(),storage={getItem:key=>data.get(key),setItem:(key,value)=>data.set(key,value)};
  const custom=defaultBindings();custom.attack=['KeyH'];saveBindings(storage,custom);
  assert.deepEqual(loadBindings(storage).attack,['KeyH']);
  saveBindings(storage,defaultBindings());assert.deepEqual(loadBindings(storage),defaultBindings());
  data.set(KEY_BINDINGS_STORAGE,'invalid json');assert.deepEqual(loadBindings(storage),defaultBindings());
});
test('corrupt, duplicate, missing and reserved bindings cannot break controls',()=>{
  for(const mutate of [b=>b.attack=['Escape'],b=>b.attack=['KeyW'],b=>b.attack=[],b=>delete b.guard,b=>b.attack=['<script>'],b=>b.attack=['KeyH','KeyH']]){
    const bindings=defaultBindings();mutate(bindings);assert.equal(validateBindings(bindings),false);
    assert.deepEqual(loadBindings({getItem:()=>JSON.stringify(bindings)}),defaultBindings());
  }
  assert.deepEqual(loadBindings({getItem(){throw Error('denied');}}),defaultBindings());
  assert.throws(()=>saveBindings({setItem(){throw Error('quota');}},defaultBindings()),/quota/);
});
function harness(bindings=defaultBindings()){
  const target=new EventTarget(),events=[];let enabled=true;
  const controller=bindKeyboard(target,{bindings,enabled:()=>enabled,action:(...args)=>events.push(args)});
  const emit=(type,code,extra={})=>{const event=new Event(type,{cancelable:true});Object.assign(event,{code,...extra});target.dispatchEvent(event);return event;};
  return {events,controller,emit,setEnabled:value=>enabled=value};
}
test('custom input replaces old keys, keeps aliases held and ignores attack repeat',()=>{
  const bindings=defaultBindings();bindings.attack=['KeyH'];bindings.guard=['KeyK','Space'];const h=harness(bindings);
  h.emit('keydown','KeyJ');assert.equal(h.events.length,0);
  h.emit('keydown','KeyH');h.emit('keydown','KeyH',{repeat:true});h.emit('keyup','KeyH');
  assert.deepEqual(h.events,[['attack',true],['attack',false]]);h.events.length=0;
  h.emit('keydown','KeyK');h.emit('keydown','Space');h.emit('keyup','KeyK');
  assert.deepEqual(h.events,[['guard',true],['guard',true]]);
  h.emit('keyup','Space');assert.deepEqual(h.events.at(-1),['guard',false]);h.controller.dispose();
});
test('pause, focus loss and changing bindings release held actions safely',()=>{
  const h=harness();h.emit('keydown','KeyW');h.controller.reset();assert.deepEqual(h.events.at(-1),['forward',false]);
  h.setEnabled(false);h.emit('keydown','KeyJ');assert.equal(h.events.length,2);
  h.setEnabled(true);h.emit('keydown','Space');h.emit('blur');assert.deepEqual(h.events.at(-1),['guard',false]);
  h.emit('keydown','KeyW');const next=defaultBindings();next.forward=['KeyI'];h.controller.setBindings(next);assert.deepEqual(h.events.at(-1),['forward',false]);
  h.events.length=0;h.emit('keydown','KeyW');h.emit('keydown','KeyI');assert.deepEqual(h.events,[['forward',true]]);
  h.controller.dispose();h.events.length=0;h.emit('keydown','KeyI');assert.equal(h.events.length,0);
});
test('browser shortcuts and disabled controls do not invoke gameplay',()=>{
  const bindings=defaultBindings();bindings.crouch=['KeyC'];const h=harness(bindings);for(const modifier of ['ctrlKey','altKey','metaKey'])h.emit('keydown','KeyW',{[modifier]:true});
  assert.deepEqual(h.events,[]);h.controller.dispose();
});

test('untouched previous Web defaults upgrade, while customized layouts are retained',()=>{
  const old={forward:['KeyW','ArrowUp'],back:['KeyS','ArrowDown'],left:['KeyA','ArrowLeft'],right:['KeyD','ArrowRight'],attack:['KeyJ'],guard:['KeyK','Space'],jump:['KeyL'],crouch:['KeyC'],lock:['KeyQ'],switch:['KeyE'],pickup:['KeyF'],weapon1:['Digit1'],weapon2:['Digit2'],weapon3:['Digit3'],weapon4:['Digit4'],weapon5:['Digit5']};
  assert.deepEqual(loadBindings({getItem:()=>JSON.stringify(old)}),defaultBindings());old.attack=['KeyH'];assert.deepEqual(loadBindings({getItem:()=>JSON.stringify(old)}).attack,['KeyH']);
});


test('obsolete catalogue and explicit pickup shortcuts are removed while customized combat bindings survive migration',()=>{
 const prior={...defaultBindings(),attack:['KeyH'],pickup:['KeyF'],weapon1:['Digit1'],weapon2:['Digit2'],weapon3:['Digit3'],weapon4:['Digit4'],weapon5:['Digit5']};
 const loaded=loadBindings({getItem:()=>JSON.stringify(prior)});assert.deepEqual(loaded.attack,['KeyH']);assert.ok(!('pickup' in loaded));assert.ok(!('weapon1' in loaded));
 const h=harness(loaded);for(const code of ['KeyF','Digit1','Digit2','Digit3','Digit4','Digit5'])h.emit('keydown',code);assert.deepEqual(h.events,[]);h.controller.dispose();
});
