import { ACTION_LABELS, defaultBindings, allowedCode, keyLabel, saveBindings } from './keybindings.js';

export function mountKeySettings(root, { bindings, storage, onSave }) {
  let draft=structuredClone(bindings), pending=null;
  const message=text=>{root.querySelector('[role="status"]').textContent=text;};
  function render(){
    root.innerHTML='<p class="modal-note">点击键位后按下键盘或鼠标按键。每个动作最多两个键；Esc 取消录入，暂停键 Esc 固定。默认采用原版键鼠布局，触屏按钮保持可用。修改后点击保存。</p><div class="keybinding-list"></div><p role="status" aria-live="polite"></p><div class="modal-actions"><button type="button" class="primary-button" data-keys-save>保存键位</button><button type="button" class="secondary-button" data-keys-reset>恢复默认</button></div>';
    const list=root.querySelector('.keybinding-list');
    for(const action of ['forward','back','left','right','jump','crouch','attack','guard','lock','switch','drop']){
      const label=ACTION_LABELS[action],group={forward:'移动与身法',attack:'攻击与防御',lock:'锁定与兵器'}[action];if(group){const heading=document.createElement('h3');heading.textContent=group;list.append(heading);}
      const row=document.createElement('div');row.className='settings-row keybinding-row';
      const title=document.createElement('span');title.textContent=label;row.append(title);
      const slots=document.createElement('div');slots.className='keybinding-slots';
      for(let slot=0;slot<2;slot++){
        const button=document.createElement('button');button.type='button';button.className='secondary-button keybinding-key';button.textContent=draft[action][slot]?keyLabel(draft[action][slot]):'未设置';button.setAttribute('aria-label',`${label}，键位 ${slot+1}：${button.textContent}`);
        button.addEventListener('click',()=>{if(pending)pending.button.textContent=pending.previous;pending={action,slot,button,previous:button.textContent};button.textContent='请按键…';message('按下新按键，Esc 取消。');});slots.append(button);
      }
      const clear=document.createElement('button');clear.type='button';clear.textContent='清除备用键';clear.className='keybinding-clear';clear.disabled=draft[action].length<2;clear.addEventListener('click',()=>{draft[action]=draft[action].slice(0,1);pending=null;render();});slots.append(clear);row.append(slots);list.append(row);
    }
    root.querySelector('[data-keys-save]').addEventListener('click',()=>commit(draft,'键位已保存，返回游戏后生效。'));
    root.querySelector('[data-keys-reset]').addEventListener('click',()=>{if(commit(defaultBindings(),'已恢复并保存默认键位。')){pending=null;render();message('已恢复并保存默认键位。');}});
  }
  function commit(next,text){try{saveBindings(storage,next);draft=structuredClone(next);onSave(structuredClone(next));pending=null;render();message(text);return true;}catch{message('保存失败，浏览器可能禁止本地存储。原设置未更改，请重试。');return false;}}
  const capture=e=>{
    if(!pending)return;e.preventDefault();e.stopImmediatePropagation();
    if(e.code==='Escape'){pending.button.textContent=pending.previous;pending=null;message('已取消录入。');return;}
    if(e.repeat)return;
    if((e.ctrlKey&&!e.code.startsWith('Control'))||e.altKey||e.metaKey||!allowedCode(e.code)){message('请选择字母、数字、方向键、空格或其他常用单键；Esc 保留为暂停。');return;}
    const {action,slot}=pending;
    const conflict=Object.keys(draft).find(name=>draft[name].some((code,index)=>code===e.code&&(name!==action||index!==slot)));
    if(conflict){message(`${keyLabel(e.code)} 已用于「${ACTION_LABELS[conflict]}」，请先更改该键位。`);return;}
    draft[action][slot]=e.code;pending=null;render();message('键位已修改，点击「保存键位」生效。');
  };
  const captureMouse=e=>{if(pending)capture({code:'Mouse'+e.button,preventDefault:()=>e.preventDefault(),stopImmediatePropagation:()=>e.stopImmediatePropagation()});};
  const context=e=>e.preventDefault();
  document.addEventListener('keydown',capture,true);document.addEventListener('pointerdown',captureMouse,true);root.addEventListener('contextmenu',context);render();
  return ()=>{document.removeEventListener('keydown',capture,true);document.removeEventListener('pointerdown',captureMouse,true);root.removeEventListener('contextmenu',context);};
}
