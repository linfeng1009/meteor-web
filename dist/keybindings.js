export const KEY_BINDINGS_STORAGE = 'meteor-web-keybindings-v1';
export const ACTION_LABELS = Object.freeze({ forward:'前进', back:'后退', left:'左移', right:'右移', attack:'攻击', guard:'防御', jump:'跳跃', crouch:'蹲下', lock:'锁定 / 解除', switch:'切换兵器', pickup:'拾取（辅助）', drop:'丢弃副兵器', weapon1:'切换长剑（演武扩展）', weapon2:'切换大刀（演武扩展）', weapon3:'切换长枪（演武扩展）', weapon4:'切换匕首（演武扩展）', weapon5:'切换飞镖（演武扩展）' });
export const DEFAULT_BINDINGS = Object.freeze(Object.fromEntries(Object.entries({forward:['KeyW'],back:['KeyS'],left:['KeyA'],right:['KeyD'],attack:['Mouse0'],guard:['Space'],jump:['Mouse2'],crouch:['ControlLeft','ControlRight'],lock:['KeyQ'],switch:['KeyE'],drop:['KeyG'],pickup:['KeyF'],weapon1:['Digit1'],weapon2:['Digit2'],weapon3:['Digit3'],weapon4:['Digit4'],weapon5:['Digit5']}).map(([action,codes])=>[action,Object.freeze(codes)])));
export const defaultBindings = () => Object.fromEntries(Object.entries(DEFAULT_BINDINGS).map(([action,codes])=>[action,[...codes]]));
export function keyLabel(code) {
  return ({Mouse0:'鼠标左键',Mouse1:'鼠标中键',Mouse2:'鼠标右键',ControlLeft:'左 Ctrl',ControlRight:'右 Ctrl',Space:'空格',ArrowUp:'↑',ArrowDown:'↓',ArrowLeft:'←',ArrowRight:'→',ShiftLeft:'左 Shift',ShiftRight:'右 Shift',Enter:'Enter',Tab:'Tab',Backspace:'Backspace',Delete:'Delete',Insert:'Insert',Home:'Home',End:'End',PageUp:'PageUp',PageDown:'PageDown',Minus:'-',Equal:'=',BracketLeft:'[',BracketRight:']',Backslash:'\\',Semicolon:';',Quote:"'",Comma:',',Period:'.',Slash:'/',Backquote:'`'})[code] || code.replace(/^Key|^Digit/,'').replace(/^Numpad/,'数字键盘 ');
}
export function allowedCode(code) {
  return typeof code==='string' && /^(Mouse[012]|Control(Left|Right)|Key[A-Z]|Digit[0-9]|Arrow(Up|Down|Left|Right)|Space|Shift(Left|Right)|Enter|Tab|Backspace|Delete|Insert|Home|End|PageUp|PageDown|Minus|Equal|BracketLeft|BracketRight|Backslash|Semicolon|Quote|Comma|Period|Slash|Backquote|Numpad([0-9]|Add|Subtract|Multiply|Divide|Decimal|Enter))$/.test(code);
}
export function validateBindings(bindings) {
  const seen=new Set();
  if(!bindings || typeof bindings!=='object' || Array.isArray(bindings))return false;
  for(const action of Object.keys(DEFAULT_BINDINGS)) {
    const codes=bindings[action];
    if(!Array.isArray(codes)||codes.length<1||codes.length>2)return false;
    for(const code of codes){if(!allowedCode(code)||seen.has(code))return false;seen.add(code);}
  }
  return true;
}
export function loadBindings(storage) {
  try {
    const bindings=JSON.parse(storage.getItem(KEY_BINDINGS_STORAGE));
    // Upgrade the previous untouched Web defaults; preserve intentional custom layouts.
    const legacy={forward:['KeyW','ArrowUp'],back:['KeyS','ArrowDown'],left:['KeyA','ArrowLeft'],right:['KeyD','ArrowRight'],attack:['KeyJ'],guard:['KeyK','Space'],jump:['KeyL'],crouch:['KeyC'],lock:['KeyQ'],switch:['KeyE'],pickup:['KeyF'],weapon1:['Digit1'],weapon2:['Digit2'],weapon3:['Digit3'],weapon4:['Digit4'],weapon5:['Digit5']};
    if(bindings&&Object.entries(legacy).every(([action,codes])=>JSON.stringify(bindings[action])===JSON.stringify(codes)))return defaultBindings();
    if(bindings&&!bindings.drop){const used=new Set(Object.values(bindings).flat());const free=['KeyG',...Array.from({length:26},(_,i)=>`Key${String.fromCharCode(65+i)}`)].find(code=>!used.has(code));if(free)bindings.drop=[free];}
    if(validateBindings(bindings))return Object.fromEntries(Object.keys(DEFAULT_BINDINGS).map(action=>[action,[...bindings[action]]]));
  } catch {}
  return defaultBindings();
}
export function saveBindings(storage,bindings) {
  if(!validateBindings(bindings))throw new Error('键位无效或存在重复，请重新设置。');
  storage.setItem(KEY_BINDINGS_STORAGE,JSON.stringify(bindings));
}
export const bindingMap = bindings => Object.fromEntries(Object.entries(bindings).flatMap(([action,codes])=>codes.map(code=>[code,action])));

// Multiple physical keys can hold the same action; releasing one must not release the other.
export function bindKeyboard(target, { bindings=defaultBindings(), enabled, action }) {
  let mapping=bindingMap(bindings);
  const held=new Map(), continuous=new Set(['forward','back','left','right','guard']);
  const reset=()=>{for(const name of new Set(held.values()))action(name,false);held.clear();};
  const down=e=>{
    if(!enabled()||e.metaKey||e.altKey||(e.ctrlKey&&!mapping.ControlLeft&&!mapping.ControlRight))return;
    const name=mapping[e.code];if(!name)return;e.preventDefault();
    if(e.repeat&&!continuous.has(name))return;
    if(held.has(e.code)){if(e.repeat&&continuous.has(name))action(name,true);return;}
    held.set(e.code,name);action(name,true);
  };
  const up=e=>{const name=held.get(e.code);if(!name)return;held.delete(e.code);if(![...held.values()].includes(name))action(name,false);};
  target.addEventListener('keydown',down);target.addEventListener('keyup',up);target.addEventListener('blur',reset);
  return {reset,setBindings(next){if(!validateBindings(next))throw new Error('无效键位');reset();mapping=bindingMap(next);},dispose(){reset();target.removeEventListener('keydown',down);target.removeEventListener('keyup',up);target.removeEventListener('blur',reset);}};
}
