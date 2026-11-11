import { NetworkLobby } from './network-lobby.js';
let networkLobby;
import { loadBindings, keyLabel } from './keybindings.js';
import { mountKeySettings } from './keybinding-settings.js';
let keyStorage; try { keyStorage=window.localStorage; } catch {}
let keyBindings=loadBindings(keyStorage), disposeKeySettings=null;
const keyHint=action=>keyBindings[action].map(keyLabel).join(' / ');
function refreshKeyGuide(){
  const guide=document.querySelector('.key-guide');if(!guide)return;
  guide.replaceChildren();
  const items=[[[...['forward','left','back','right'].map(action=>keyLabel(keyBindings[action][0]))].join(' '),'移动'],[keyHint('attack'),'出招'],[keyHint('guard'),'防御'],[keyHint('jump'),'跃起'],[keyHint('lock'),'锁定'],[keyHint('switch'),'换兵器'],[keyHint('drop'),'丢副兵器'],['Esc','暂停']];
  for(const [keys,label] of items){const span=document.createElement('span'),kbd=document.createElement('kbd');kbd.textContent=keys;span.append(kbd,' '+label);guide.append(span);}
}
refreshKeyGuide();
import { NATIVE_CHARACTERS, NATIVE_APPEARANCES } from './native-character.js';
import { appearanceDetails, appearanceCharacterName, appearanceCharacterSeal } from './character-appearances.js';
import { NATIVE_MISSIONS, getNativeMission } from './native-missions.js';
import { NATIVE_WEAPON_MENU, QIANKUN_MODE_NAMES } from './native-weapon-menu.js';
import { renderNativeMoveGuide } from './native-move-guide.js';
import { QIYUN_MAP } from './qiyun-courtyard.js';
const $ = s => document.querySelector(s);
const $$ = s => [...document.querySelectorAll(s)];
const icon = name => `<svg aria-hidden="true"><use href="#i-${name}"/></svg>`;
const swordStyleNames={original:'原版长剑',butterfly:'月蝶剑',raiden:'雷电影佩刀'};
const maps={sifang:{name:'四方阵',english:'THE FOUR SQUARES',poem:'方寸之间，自有天地。'},cave:{name:'钟乳洞',english:'LIMESTONE CAVERN',poem:'暗流无声，剑影初现。'},forge:{name:'炼铁狱',english:'THE IRON FORGE',poem:'烈火淬刃，百炼成锋。'}};
maps[QIYUN_MAP.id] = QIYUN_MAP;
for(const mission of NATIVE_MISSIONS)maps[mission.mapId]={name:mission.name,english:'ORIGINAL MISSION · '+mission.id.toUpperCase(),poem:'原版单机任务'};
const weapons=NATIVE_WEAPON_MENU;
let prefs={showFps:true,weapon:'sword',map:'sifang',character:0,characterAppearance:'original',swordStyle:'butterfly',spearStyle:'original',mission:'sn01',completedMissions:[],difficulty:'normal',infiniteRage:false,muted:true,quality:matchMedia('(pointer:coarse)').matches?'low':'high',best:0};
try{const p=JSON.parse(localStorage.getItem('meteor-web-original-v2')||'{}');for(const k of ['showFps','weapon','map','character','characterAppearance','swordStyle','spearStyle','mission','completedMissions','difficulty','infiniteRage','muted','quality','best'])if(p[k]!==undefined)prefs[k]=p[k];}catch{}
if(!maps[prefs.map]){if(/^sn\d{2}$/.test(prefs.map))maps[prefs.map]={name:prefs.map.toUpperCase(),english:'ORIGINAL MAP',poem:'原版战场'};else prefs.map='sifang';}if(!weapons[prefs.weapon])prefs.weapon='sword';if(!['normal','hard'].includes(prefs.difficulty))prefs.difficulty='normal';if(!['low','high'].includes(prefs.quality))prefs.quality='high';
if(!Object.hasOwn(NATIVE_APPEARANCES,prefs.characterAppearance))prefs.characterAppearance='original';
if(!Object.hasOwn(swordStyleNames,prefs.swordStyle))prefs.swordStyle='butterfly';
if(!['original','phoenix'].includes(prefs.spearStyle))prefs.spearStyle='original';
prefs.infiniteRage=prefs.infiniteRage===true;
const appearanceURL=new URL(location.href);if(Object.hasOwn(NATIVE_APPEARANCES,appearanceURL.searchParams.get('appearance'))){prefs.characterAppearance=appearanceURL.searchParams.get('appearance');if(prefs.characterAppearance!=='original')prefs.character=0;appearanceURL.searchParams.delete('appearance');history.replaceState(null,'',appearanceURL.pathname+appearanceURL.search+appearanceURL.hash);}
if(!Number.isInteger(prefs.character)||!NATIVE_CHARACTERS[prefs.character])prefs.character=0;
const save=()=>{try{localStorage.setItem('meteor-web-original-v2',JSON.stringify(prefs));}catch{}};
if(!getNativeMission(prefs.mission))prefs.mission='sn01';
prefs.completedMissions=NATIVE_MISSIONS.filter(m=>Array.isArray(prefs.completedMissions)&&prefs.completedMissions.includes(m.id)).map(m=>m.id);
let currentMode='training',currentMissionId=prefs.mission;
let dialogueTimer=null,dialogueQueue=[];
let loadingMatch=false,characterSelectionBusy=false;
let mapSelectionRequest=0;
let game,running=false,paused=false,ended=false,modalKind='',toastTimer,announcementTimer,hitTimer,lastCombo=0,lastHp=100;
let nativeCombat=null;
let guideWeapon='sword';
let appearanceUIRequest=0;
async function applyCharacterAppearance(requested,notify=true){const request=++appearanceUIRequest;const button=$('#appearance-toggle');button.disabled=true;const select=$('#character-appearance');if(select)select.disabled=true;try{const result=await game?.setCharacterAppearance(requested);if(request!==appearanceUIRequest)return;const actual=Object.hasOwn(NATIVE_APPEARANCES,result?.appearance)?result.appearance:'original';if(result?.available===false&&NATIVE_APPEARANCES[requested]?.characterId===prefs.character)markAppearanceUnavailable(requested);prefs.characterAppearance=actual;save();updateSelection();if(notify||!result?.available)toast(result?.reason|| ('已切换为'+(NATIVE_APPEARANCES[actual]?.label||'原版人物')));}catch(error){if(request===appearanceUIRequest){console.error(error);if(NATIVE_APPEARANCES[requested]?.characterId===prefs.character)markAppearanceUnavailable(requested);prefs.characterAppearance=game?.hero?.character?.appearance||prefs.characterAppearance;save();updateSelection();toast('人物外观未能载入，已保留此前外观');}}finally{if(request===appearanceUIRequest){button.disabled=prefs.character!==0;const select=$('#character-appearance');if(select)select.disabled=prefs.character!==0;}}}
let originalManifest=null;
const readyAppearances=new Set(['original']);
function markAppearanceUnavailable(id){
  readyAppearances.delete(id);const option=$('#character-appearance')?.querySelector(`option[value="${id}"]`);
  if(option){option.disabled=true;option.textContent=appearanceDetails(id).title+' · 载入失败，刷新重试';}
}
for(const [id,descriptor] of Object.entries(NATIVE_APPEARANCES))if(descriptor.assetPath){
  fetch(new URL('manifest.json',new URL(descriptor.assetPath,import.meta.url))).then(response=>response.ok?response.json():null).then(manifest=>{
    if(manifest?.characterId===descriptor.characterId&&(manifest.appearance===undefined||manifest.appearance===id)&&manifest.complete!==false&&manifest.completeness?.faceGeometry!==false)readyAppearances.add(id);
    const option=$('#character-appearance')?.querySelector(`option[value="${id}"]`);if(option){option.disabled=!readyAppearances.has(id);option.textContent=appearanceDetails(id).title+(readyAppearances.has(id)?'':' · 模型未就绪');}
    refreshCharacterOptions();
  }).catch(()=>{});
}
fetch('./assets/original/manifest.json').then(r=>{if(!r.ok)throw new Error('原版资源清单读取失败');return r.json();}).then(data=>{originalManifest=data;for(const map of data.maps||[])maps[map.id]={name:map.name||map.id.toUpperCase(),english:'ORIGINAL MAP · '+map.id.toUpperCase(),poem:'故地重游，原样重逢。',available:map.available!==false};renderArenaMaps();updateSelection();}).catch(error=>console.warn(error));
import('./native-combat.js').then(m=>m.loadNativeCombat()).then(data=>{nativeCombat=data;}).catch(error=>console.warn('原版招式表暂未加载',error));
const music=new Audio();music.loop=true;music.volume=.18;music.preload='none';let musicTrack='';
function syncMusic(){const mapId=({sifang:'sn06',cave:'sn01',forge:'sn10'}[prefs.map]||prefs.map);const mission=currentMode==='story'?getNativeMission(currentMissionId):null;const track=running?(mission?.music||(mapId==='sn01'?'s1.mp3':mapId==='sn10'?'s10.mp3':'s6.mp3')):'menu.mp3';if(musicTrack!==track){musicTrack=track;music.src='./assets/original/sounds/music/'+track;}if(prefs.muted||document.hidden)music.pause();else music.play().catch(()=>{});}
let priorFocus=null;
const modal=$('#modal');
const toast=text=>{clearTimeout(toastTimer);$('#toast').textContent=text;$('#toast').classList.add('show');toastTimer=setTimeout(()=>$('#toast').classList.remove('show'),2800);};
const announce=(text,ms=2300)=>{clearTimeout(announcementTimer);$('#game-announcement').textContent=text;$('#game-announcement').style.opacity=1;announcementTimer=setTimeout(()=>$('#game-announcement').style.opacity=0,ms);};
function clearDialogue(){clearTimeout(dialogueTimer);dialogueTimer=null;dialogueQueue=[];$('#mission-dialogue').classList.add('hidden');}
function clearCombatFeedback(){clearTimeout(hitTimer);clearTimeout(announcementTimer);$('#hit-feedback').textContent='';$('#hit-feedback').style.opacity=0;$('#game-announcement').textContent='';$('#game-announcement').style.opacity=0;$('#combo-feedback').textContent='';$('#combo-feedback').dataset.command='';$('#game-hud').style.boxShadow='';$('#enemy-status').classList.add('hidden');$('#pickup-hint').classList.add('hidden');$('#musket-reticle').classList.add('hidden');}
function nextDialogue(){
  if(!running){clearDialogue();return;}
  if(paused){dialogueTimer=setTimeout(nextDialogue,250);return;}
  const line=dialogueQueue.shift();if(!line){dialogueTimer=null;$('#mission-dialogue').classList.add('hidden');return;}
  $('#dialogue-speaker').textContent=line.speaker||'';$('#dialogue-text').textContent=line.text||'';$('#mission-dialogue').classList.remove('hidden');
  dialogueTimer=setTimeout(nextDialogue,Math.max(2000,Math.min(10000,(Number(line.duration)||4)*1000)));
}
function showDialogue(line){dialogueQueue.push(line);if(!dialogueTimer)nextDialogue();}
function matchLoading(active){loadingMatch=active;$('#load-screen').classList.toggle('hidden',!active);$('#load-screen').style.opacity=active?'1':'0';$('#start-game').disabled=active;}
function renderArenaMaps(){
  const grid=$('.arena-grid');if(!grid||!originalManifest)return;
  grid.querySelectorAll('[data-generated-map]').forEach(node=>node.remove());
  for(const map of originalManifest.maps||[]){
    if(['sn01','sn06','sn10'].includes(map.id))continue;
    const button=document.createElement('button');button.className='arena-card arena-card-extra';button.dataset.map=map.id;button.dataset.generatedMap='true';button.disabled=map.available===false;button.setAttribute('aria-pressed','false');
    const number=document.createElement('span');number.className='arena-number';number.textContent=map.id.toUpperCase();
    const label=document.createElement('span');label.className='arena-label';const title=document.createElement('strong');title.textContent=map.name||map.id.toUpperCase();const detail=document.createElement('small');detail.textContent=map.available===false?'原文件数据异常 · 暂不可用':map.name?'原版战场':'原版战场 · 名称待核实';label.append(title,detail);
    button.append(number,label);grid.append(button);
  }
}
const canonicalMap=id=>({sifang:'sn06',cave:'sn01',forge:'sn10'}[id]||id);
function updateSelection(){
  $('#infinite-rage').checked=prefs.infiniteRage;
  $('#infinite-rage-status').textContent=prefs.infiniteRage?'已开启':'已关闭';
  $$('.arena-card').forEach(el=>{const selected=canonicalMap(el.dataset.map)===canonicalMap(prefs.map);el.classList.toggle('selected',selected);el.setAttribute('aria-pressed',String(selected));});
  $$('[data-weapon]').forEach(el=>{const selected=el.dataset.weapon===prefs.weapon;el.classList.toggle('selected',selected);el.setAttribute('aria-pressed',String(selected));});
  $$('[data-sword-style]').forEach(el=>{const selected=el.dataset.swordStyle===prefs.swordStyle;el.classList.toggle('selected',selected);el.setAttribute('aria-pressed',String(selected));el.querySelector('.sword-style-status').textContent=selected?'已选':'选择';});
  $$('[data-spear-style]').forEach(el=>{const selected=el.dataset.spearStyle===prefs.spearStyle;el.classList.toggle('selected',selected);el.setAttribute('aria-pressed',String(selected));el.querySelector('.sword-style-status').textContent=selected?'已选':'选择';});
  $('#sword-appearance-section').hidden=prefs.weapon!=='sword';
  $('#spear-appearance-section').hidden=prefs.weapon!=='spear';
  $('#sword-wardrobe-current').textContent=prefs.weapon==='sword'?'演武装备 · '+swordStyleNames[prefs.swordStyle]:'演武装备 · '+(prefs.weapon==='spear'?(prefs.spearStyle==='phoenix'?'霜翎凤鸣枪':'原版长枪'):weapons[prefs.weapon].name);
  $('#difficulty-label').textContent=prefs.difficulty==='hard'?'江湖高手':'江湖新手';
  $('#scene-name').textContent=maps[prefs.map].name;$('#scene-english').textContent=maps[prefs.map].english;$('#scene-poem').textContent=maps[prefs.map].poem;
  $('#start-game small').textContent=prefs.map===QIYUN_MAP.id?'全新战场 · 招式演武':'原版场景 · 招式演武';
  $$('.sound-toggle').forEach(el=>{el.innerHTML=icon(prefs.muted?'muted':'volume');el.setAttribute('aria-label',prefs.muted?'开启音效':'关闭音效');el.title=prefs.muted?'开启音效':'关闭音效';});
  $('#hud-weapon').textContent=weapons[prefs.weapon].name+' · '+weapons[prefs.weapon].motto;
  const name=appearanceCharacterName(prefs.character,prefs.characterAppearance),descriptor=NATIVE_APPEARANCES[prefs.characterAppearance];
  const appearanceApplies=descriptor?.characterId===prefs.character;
  $('#character-label').textContent=name+(appearanceApplies&&appearanceDetails(prefs.characterAppearance).kind==='pmx'?' · 模型外观':'');
  $('#appearance-label').textContent=appearanceApplies?appearanceDetails(prefs.characterAppearance).shortLabel:'原版';$('#appearance-toggle').disabled=prefs.character!==0;
  $('#appearance-toggle').title='依次切换'+Object.keys(NATIVE_APPEARANCES).map(id=>appearanceDetails(id).shortLabel).join('、');
  $('#player-name').textContent=name;$('.player-seal').textContent=appearanceCharacterSeal(prefs.character,prefs.characterAppearance);
  $('#hero-character-name').textContent=name;$('#hero-character-seal').textContent=appearanceCharacterSeal(prefs.character,prefs.characterAppearance);$('.hero-character').setAttribute('aria-label',`选择人物，当前${name}`);
  const appearanceSelect=$('#character-appearance');if(appearanceSelect){appearanceSelect.value=prefs.characterAppearance;appearanceSelect.disabled=prefs.character!==0||$('#appearance-toggle').disabled;}
}
const header=(en,title,desc='')=>`<div class="modal-kicker">${en}</div><h2 class="modal-title">${title}</h2>${desc?`<p class="modal-desc">${desc}</p>`:''}`;
function guideHTML(){return header('THE WAY OF THE WARRIOR','武学招式','方向接攻击，步法接刀锋。选一柄兵器，查看出招指令。')+`<div class="combo-legend"><p><kbd>A</kbd> 是攻击记号：按 <kbd>${keyHint('attack')}</kbd>。</p><p><span>↑ ↓ ← →</span> 对应 <kbd>${['forward','back','left','right'].map(keyHint).join('；')}</kbd>。连续按顺序输入，重复方向先松开再按。<br>跳跃：<kbd>${keyHint('jump')}</kbd>。空中招式需离地后输入，连段需衔接前一招。火铳先按攻击举枪，举枪完成后再按攻击射击；移动鼠标瞄准，防御或跳跃收枪。</p></div><div class="combo-weapon-filter" role="group" aria-label="查看兵器招式">${Object.keys(weapons).map(weapon=>`<button type="button" data-guide-weapon="${weapon}" aria-pressed="${guideWeapon===weapon}" aria-controls="guide-move-panel"${guideWeapon===weapon?' class="selected"':''}>${weapons[weapon].name}</button>`).join('')}</div><div id="guide-move-panel" aria-labelledby="guide-weapon-heading">${renderNativeMoveGuide(guideWeapon)}</div><details class="guide-controls"><summary>移动、防御与其他操作</summary><div class="controls-grid">${[[['forward','left','back','right'].map(keyHint).join('；'),'移动'],['移动鼠标（进入游戏后锁定）','转动视角'],[keyHint('attack'),'攻击（招式中的 A）'],[keyHint('guard'),'防御'],[keyHint('crouch'),'蹲下'],[keyHint('jump'),'跳跃'],[keyHint('lock'),'锁定 / 解除'],[keyHint('switch'),'切换兵器'],['走近物品','自动拾取'],[keyHint('drop'),'丢弃副兵器'],['Esc','暂停 / 返回对战']].map(([k,v])=>`<div class="control-row"><span>${v}</span><kbd>${k}</kbd></div>`).join('')}</div><p class="modal-note">按住 ${keyHint('crouch')}，快速按两次同一方向（两次之间松开），可向前、后、左、右翻滚。触屏按住「蹲」后也可双击方向。<br>触屏使用方向键和「攻」依次输入，「跃」后可施展空中招式。上方兵器按钮只切换查看内容；实际换兵器请按 ${keyHint('switch')}。</p></details><div class="modal-actions"><button class="primary-button" data-do="${running?'resume':'play'}"><span>${running?'重返对决':'执剑入江湖'}</span>${icon('arrow')}</button></div>`;}
function weaponsHTML(){const w=weapons[prefs.weapon];const moves=nativeCombat?.moves?.[prefs.weapon]||[];return header('THE ARMORY','兵器谱','兵无常势，水无常形。选一柄趁手兵器，再入江湖。')+`<div class="weapon-options">${Object.entries(weapons).map(([key,v])=>`<button class="weapon-option ${key===prefs.weapon?'selected':''}" data-weapon="${key}" aria-pressed="${key===prefs.weapon}"><span class="weapon-glyph">${v.glyph}</span><strong>${v.name}</strong><small>${v.motto}<br>${'原版 · '+v.sourceName}</small></button>`).join('')}</div><p class="modal-desc" id="weapon-description">${w.desc}</p>${moves.length?`<div class="native-moves">${moves.map(move=>`<div><strong>${move.name||'第'+move.id+'式'}</strong><span>${move.frameCount} 帧 · ${move.duration.toFixed(2)} 秒</span></div>`).join('')}</div>`:''}<p class="modal-note">当前随身兵器：${w.name}。演武中按 ${keyHint('switch')} 切换主副兵器；单机任务按 ${keyHint('switch')} 切换原随身兵器。按 ${keyHint('attack')} 连击或投掷。</p><div class="modal-actions"><button class="primary-button" data-do="play"><span>携兵入江湖</span>${icon('arrow')}</button></div>`;}

function resourcesHTML(){return header('THE METEOR ARCHIVE','流星典藏','优先读取本地客户端的原始素材，流星资源网提供格式资料与缺失资源补充。')+`<div class="resource-list"><a class="resource-link" href="./assets/original/manifest.json" target="_blank" rel="noopener noreferrer"><span>本</span><div><strong>本地客户端原素材</strong><small>20 位人物 · 22 份地图 · 原始招式与配乐</small></div><span>↗</span></a><a class="resource-link" href="https://www.lxres.com/" target="_blank" rel="noopener noreferrer"><span>源</span><div><strong>流星资源网</strong><small>原版客户端 · 单机任务 · 人物兵器 · 地图资源</small></div><span>↗</span></a><a class="resource-link" href="https://www.lxres.com/LiuXingBiJi/1566.html" target="_blank" rel="noopener noreferrer"><span>图</span><div><strong>地图 GMC 结构笔记</strong><small>原生地图格式的 Web 解析依据</small></div><span>↗</span></a><a class="resource-link" href="./assets/SOURCES.md" target="_blank" rel="noopener noreferrer"><span>记</span><div><strong>本项目素材来源清单</strong><small>已使用的地图、贴图与转换记录</small></div><span>↗</span></a></div><p class="modal-note">这是《流星蝴蝶剑.net》的非官方 Web 实验重构。读取本地原版模型、骨骼、动画与招式表，在浏览器运行；剧情脚本与联网协议仍在逐项移植。原游戏与社区素材的权利归各自权利人所有。</p>`;}
function settingsHTML(){return header('MAKE IT YOUR JIANGHU','江湖设置','设置自动保存在当前浏览器。')+`<div class="settings-row"><label>自定义按键<small>保存键位、恢复默认；仅保存在当前浏览器</small></label><button class="secondary-button" data-open="keys">设置按键</button></div><div class="settings-row"><label for="character-appearance">人物外观<small>高清孟星魂、YS-胡桃、YS-影、RE0-爱蜜莉雅、豆包、春田、甘雨、八重神子、雷电将军、荧、空、芙宁娜、王昭君与刻晴，沿用原版动作</small></label><select id="character-appearance" class="setting-select" ${prefs.character!==0?'disabled':''}>${Object.keys(NATIVE_APPEARANCES).map(id=>`<option value="${id}" ${prefs.characterAppearance===id?'selected':''} ${readyAppearances.has(id)?'':'disabled'}>${appearanceDetails(id).title}${readyAppearances.has(id)?'':' · 模型未就绪'}</option>`).join('')}</select></div><a class="comparison-link" href="./character-compare.html">打开人物外观对照 · 同步动作预览 ↗</a><div class="settings-row" ${prefs.weapon==='sword'?'':'hidden'}><label for="sword-style">长剑外观<small>原版长剑、月蝶剑与雷电影佩刀</small></label><select id="sword-style" class="setting-select"><option value="butterfly" ${prefs.swordStyle==='butterfly'?'selected':''}>月蝶剑 · 试版</option><option value="original" ${prefs.swordStyle==='original'?'selected':''}>原版长剑</option><option value="raiden" ${prefs.swordStyle==='raiden'?'selected':''}>雷电影佩刀</option></select></div><div class="settings-row" ${prefs.weapon==='spear'?'':'hidden'}><label for="spear-style">长枪外观<small>冰蓝双尖、绯红晶芯与银金凤翼</small></label><select id="spear-style" class="setting-select"><option value="original" ${prefs.spearStyle==='original'?'selected':''}>原版长枪</option><option value="phoenix" ${prefs.spearStyle==='phoenix'?'selected':''}>霜翎凤鸣枪</option></select></div><div class="settings-row"><label>刀剑音效<small>挥刃、命中与交锋的声音</small></label><button class="toggle" data-do="sound" aria-label="刀剑音效" aria-pressed="${!prefs.muted}"></button></div><div class="settings-row"><label for="show-fps">实时帧率<small>显示 FPS、帧耗时及渲染倍率</small></label><input id="show-fps" type="checkbox" ${prefs.showFps?'checked':''}></div><div class="settings-row"><label for="quality">画面品质<small>根据帧率自动调整渲染倍率；流畅优先降低像素密度</small></label><select id="quality" class="setting-select"><option value="high" ${prefs.quality==='high'?'selected':''}>精致画面</option><option value="low" ${prefs.quality==='low'?'selected':''}>流畅优先</option></select></div><div class="settings-row"><label for="difficulty">对手难度<small>演武对手的进攻节奏；单机任务读取原关卡配置</small></label><select id="difficulty" class="setting-select"><option value="normal" ${prefs.difficulty==='normal'?'selected':''}>江湖新手</option><option value="hard" ${prefs.difficulty==='hard'?'selected':''}>江湖高手</option></select></div><p class="modal-note">${running?'画质与声音立即生效，难度设置于下一局生效。':'建议桌面浏览器配合键盘与鼠标游玩。手机支持触屏按键，横屏视野更宽。'}${prefs.best?`<br>个人最佳：单局击败 ${Number(prefs.best)||0} 名对手。`:''}</p>`;}
function pauseHTML(){if(networkLobby?.session)return header('MULTIPLAYER','联机对战','打开菜单不会暂停其他玩家的战斗。')+'<div class="pause-actions"><button class="primary-button" data-do="resume">继续对战</button><button class="secondary-button" data-open="keys">自定义按键</button><button class="secondary-button" data-do="lobby">退出房间</button></div>';return `<div class="pause-title">${header('A MOMENT OF STILLNESS','且歇片刻','刀剑暂收，江湖还在。')}</div><div class="pause-actions"><button class="primary-button" data-do="resume"><span>继续对决</span>${icon('arrow')}</button><button class="secondary-button" data-open="guide">查看招式</button><button class="secondary-button" data-open="keys">自定义按键</button><button class="secondary-button" data-do="restart">重新论剑</button><button class="secondary-button" data-do="lobby">返回江湖首页</button></div>`;}
function missionHTML(){return header('THE ORIGINAL STORY','单机任务','选择一段原版任务，重走孟星魂的江湖。')+`<div class="mission-grid">${NATIVE_MISSIONS.map(m=>`<button class="mission-card ${m.id===currentMissionId?'mission-selected':''}" data-do="story" data-mission="${m.id}"><small>${m.id.toUpperCase()} · ${m.objectiveType==='survive'?'生存':m.objectiveType==='assassinate'?'追击':m.objectiveType==='siege'?'破关':'战斗'}任务${prefs.completedMissions.includes(m.id)?' · 已完成':''}</small><strong>${m.name}</strong><p>${m.description}</p><div class="mission-loadout">${m.playerHp} 气血 · ${m.weapon}</div><span>进入${m.name} →</span></button>`).join('')}</div><p class="modal-note">留意各关任务目标；小地图金色方框标记任务目标。完成记录保存在当前浏览器。</p>`;}
function charactersHTML(){
  const choices=Object.keys(NATIVE_APPEARANCES).map(id=>[id,id==='original'?'孟星魂':appearanceDetails(id).name,id==='original'?'原版人物':id==='hd'?'高清试版':id==='raiden'?'礼服外观':'模型外观']);
  return header('CHOOSE YOUR FIGHTER','选择人物','先选一位人物，再执剑入江湖。')+`<div class="character-section-label">精选人物 <span>FEATURED</span></div><div class="featured-characters">${choices.map(([appearance,name,subtitle])=>{const selected=prefs.character===0&&prefs.characterAppearance===appearance,available=readyAppearances.has(appearance);return `<button class="featured-character ${selected?'selected':''} featured-${appearance}" data-pick-appearance="${appearance}" aria-pressed="${selected}" ${characterSelectionBusy||!available?'disabled':''}><span class="featured-seal" aria-hidden="true">${appearanceCharacterSeal(0,appearance)}</span><span class="featured-copy"><strong>${name}</strong><small>${available?subtitle:'资源载入中'}</small></span><span class="featured-check" aria-hidden="true">✓</span></button>`;}).join('')}</div><div class="character-section-label">更多原版人物 <span>ORIGINAL CAST</span></div><div class="character-grid">${NATIVE_CHARACTERS.filter(c=>c.id!==0).map(c=>`<button class="character-option ${c.id===prefs.character&&prefs.characterAppearance==='original'?'selected':''}" data-pick-character="${c.id}" aria-pressed="${c.id===prefs.character&&prefs.characterAppearance==='original'}" ${characterSelectionBusy?'disabled':''}><img src="${c.portrait}" alt="" loading="lazy"><span>${c.name}</span></button>`).join('')}</div><p class="modal-note" id="character-pick-status" role="status">${characterSelectionBusy?'正在载入人物…':'原版单机任务沿用孟星魂身份，可使用已选的孟星魂外观。'}</p>`;
}
function refreshCharacterOptions(){
  if(!modal.open||modalKind!=='characters')return;
  for(const button of $$('[data-pick-appearance]')){const id=button.dataset.pickAppearance,ready=readyAppearances.has(id);button.disabled=characterSelectionBusy||!ready;const small=button.querySelector('small');if(small)small.textContent=ready?({original:'原版人物',hd:'高清试版',hutao:'模型外观',raiden:'礼服外观',emilia:'模型外观'}[id]||'人物外观'):'资源载入中';}
}
async function selectCharacter(id,appearance){
  if(characterSelectionBusy||!game||!Number.isInteger(id)||!NATIVE_CHARACTERS[id]||!Object.hasOwn(NATIVE_APPEARANCES,appearance)||!readyAppearances.has(appearance))return;
  characterSelectionBusy=true;$('#start-game').disabled=true;
  for(const button of $$('[data-pick-character], [data-pick-appearance]'))button.disabled=true;
  const status=$('#character-pick-status');if(status)status.textContent='正在载入人物…';
  try{
    await game.setCharacter(id);
    const result=await game.setCharacterAppearance(appearance);
    if(!result?.available||result.appearance!==appearance)throw new Error(result?.reason||'人物外观未能载入');
    prefs.character=id;prefs.characterAppearance=appearance;save();updateSelection();
    if(modal.open&&modalKind==='characters')closeModal();
  }catch(error){
    console.error(error);prefs.character=game.hero?.modelId??game.characterId??prefs.character;prefs.characterAppearance=game.hero?.character?.appearance||'original';
    if(NATIVE_APPEARANCES[appearance]?.characterId===prefs.character)markAppearanceUnavailable(appearance);
    save();updateSelection();toast('人物未能载入，已保留当前人物');
  }finally{
    characterSelectionBusy=false;$('#start-game').disabled=loadingMatch||Boolean($('#scene-load-status').textContent);
    if(modal.open&&modalKind==='characters')openModal('characters');
  }
}
function mapsHTML(){return header('CHOOSE YOUR BATTLEGROUND','选择战场','选一处江湖，再执剑入场。')+`<div class="original-map-grid">${[QIYUN_MAP,...(originalManifest?.maps||[])].map(map=>`<button class="original-map-option ${map.id===canonicalMap(prefs.map)?'selected':''}" data-map="${map.id}" ${map.available===false?'disabled':''}><small>${map.id===QIYUN_MAP.id?'全新战场':map.id.toUpperCase()}</small><strong>${map.name||'未命名地图'}</strong><span>${map.id===QIYUN_MAP.id?'山间古庭 · 演武':map.available===false?'原文件数据异常':map.name?'原版场景':'名称待核实'}</span></button>`).join('')}</div>`;}
async function selectMap(id){const request=++mapSelectionRequest,previous=prefs.map;prefs.map=id;save();updateSelection();if(modal.open)modal.close();$('#start-game').disabled=true;$('#scene-load-status').textContent='正在读取战场…';try{await game?.menu(id);}catch(error){console.error(error);if(request===mapSelectionRequest){prefs.map=previous;save();updateSelection();toast('这张战场暂未能载入，请重试');}}finally{if(request===mapSelectionRequest){$('#start-game').disabled=false;$('#scene-load-status').textContent='';}}}
function openModal(kind){
  disposeKeySettings?.(); disposeKeySettings=null;
  if(!modal.open)priorFocus=document.activeElement;
  modalKind=kind;
  if(kind==='guide')guideWeapon=weapons[game?.hero?.weapon]?game.hero.weapon:prefs.weapon;
  if(running&&!paused){paused=true;game?.pause(true);}
  const renderers={guide:guideHTML,weapons:weaponsHTML,characters:charactersHTML,mission:missionHTML,maps:mapsHTML,network:()=>header('LAN MULTIPLAYER','联机房间','与同一局域网的朋友切磋。')+'<div id="network-lobby"></div>',resources:resourcesHTML,settings:settingsHTML,keys:()=>header('KEY BINDINGS','自定义按键','让每一招都顺手。')+'<div id="key-settings"></div>',pause:pauseHTML};
  $('#modal-content').innerHTML=(renderers[kind]||guideHTML)();
  if(kind==='network')networkLobby.mount($('#network-lobby'));
  if(kind==='keys')disposeKeySettings=mountKeySettings($('#key-settings'),{bindings:keyBindings,storage:keyStorage,onSave:next=>{keyBindings=next;game?.setKeyBindings(next);refreshKeyGuide();}});
  if(!modal.open)modal.showModal();
}
function closeModal(){disposeKeySettings?.();disposeKeySettings=null;if(modal.open)modal.close();if(ended){returnLobby();return;}if(running&&paused){paused=false;game?.pause(false);}modalKind='';priorFocus?.focus?.();if(running&&!paused&&!matchMedia('(pointer:coarse)').matches)game?.requestMouseLock();}
async function startMatch(mode='training',missionId=currentMissionId,isCurrent=()=>true){
  if(loadingMatch||characterSelectionBusy)return;
  if(typeof mode!=='string')mode='training';if(mode!=='network'&&networkLobby?.client)await networkLobby.leave(false);currentMode=mode==='network'?'network':mode==='story'?'story':'training';const mission=currentMode==='story'?getNativeMission(missionId):null;if(currentMode==='story'){if(!mission){toast('这段原版任务尚未开放');return;}currentMissionId=mission.id;prefs.mission=mission.id;prefs.map=mission.mapId;prefs.character=0;save();updateSelection();}

  if(!game)return;if(!matchMedia('(pointer:coarse)').matches)game.requestMouseLock();$('#start-game').disabled=true;
  if(modal.open)modal.close();ended=false;paused=false;running=true;lastCombo=0;lastHp=mission?.playerHp??1000;clearDialogue();clearCombatFeedback();matchLoading(true);$('#load-status').textContent=mission?'正在载入'+mission.name+'与原版任务脚本…':'正在载入'+maps[prefs.map].name+'…';
  $('#lobby').classList.add('hidden');$('#game-hud').classList.remove('hidden');document.body.classList.add('playing');
  $('#hud-map').textContent=currentMode==='network'?'四方阵 · 双人对战':maps[prefs.map].name+(currentMode==='story'?' · 单机任务':' · 演武');$('#battle-hint-text').textContent='原版招式演武 · 按 '+keyHint('attack')+' 出招';$('#combo-feedback').textContent='';
  try{if(currentMode==='network')await game.setCharacterAppearance('original');if(!isCurrent())return;game.setInfiniteRage(currentMode==='network'?false:prefs.infiniteRage);await game.start({map:currentMode==='network'?'sifang':prefs.map,weapon:currentMode==='network'?'sword':prefs.weapon,difficulty:prefs.difficulty,character:currentMode==='network'?0:prefs.character,mode:currentMode});if(!isCurrent())return;game.setMuted(prefs.muted);game.setQuality(prefs.quality);syncMusic();announce(currentMode==='network'?'联机战场载入中':mission?mission.name+' · 单机任务':'演武 · 开始',2200);$('#world').setAttribute('tabindex','-1');$('#world').focus();}
  catch(e){if(isCurrent()){console.error(e);returnLobby();toast('战场加载失败，请刷新重试');}}
  finally{matchLoading(false);}
}
function returnLobby(){if(networkLobby?.session){networkLobby.leave();return;}if(modal.open)modal.close();running=false;paused=false;ended=false;clearDialogue();clearCombatFeedback();game?.pause(false);game?.menu(prefs.map).then(()=>{if(!running)game.setWeapon(prefs.weapon);}).catch(error=>{console.error(error);toast('返回战场失败，请刷新重试');});syncMusic();$('#lobby').classList.remove('hidden');$('#game-hud').classList.add('hidden');document.body.classList.remove('playing');$$('.nav-link').forEach(el=>el.classList.toggle('active',el.dataset.panel==='home'));$('#start-game').focus();}
function updateHUD(s){if(!running)return;
  const avatarId=game?.hero?.modelId??prefs.character,avatarAppearance=s.characterAppearance?.appearance||'original';$('#player-name').textContent=networkLobby?.session?game.hero.name:appearanceCharacterName(avatarId,avatarAppearance);$('.player-seal').textContent=appearanceCharacterSeal(avatarId,avatarAppearance);
  $('#musket-reticle').classList.toggle('hidden',!s.musketAim);
  const pickup=$('#pickup-hint');pickup.classList.toggle('hidden',!s.pickup);if(s.pickup){pickup.disabled=!!s.pickup.full;pickup.textContent=s.pickup.full?s.pickup.name+' · '+(s.pickup.fullReason==='full-weapons'?'双兵器已满，按 '+keyHint('drop')+' 丢弃副兵器':s.pickup.fullReason==='full-rage'?'怒气已满':'气血已满'):'靠近自动拾取 '+s.pickup.name+' · '+(s.pickup.description||('气血 +'+s.pickup.heal));}
  $('#hp-bar').style.width=Math.max(0,Math.min(100,s.hp/s.maxHp*100))+'%';$('#hp-label').textContent=`${Math.ceil(s.hp)} / ${s.maxHp}`;if($('#stamina-bar'))$('#stamina-bar').style.width=Math.max(0,Math.min(100,s.stamina||0))+'%';$('#rage-bar').style.width=Math.max(0,Math.min(100,s.rage))+'%';$('#rage-mode-label').hidden=!s.infiniteRage;
  const time=Math.max(0,Math.ceil(s.time));$('#timer').textContent=String(Math.floor(time/60)).padStart(2,'0')+':'+String(time%60).padStart(2,'0');$('#kills').textContent=currentMode==='network'?s.kills??0:s.hits??s.kills??0;const counterLabel=$('#battle-counter-label');if(counterLabel)counterLabel.textContent=currentMode==='network'?'击败':'命中';$('#deaths').textContent=s.deaths;
  if(s.weaponName){$('#hud-weapon').textContent=s.weaponName+(s.weapon==='qiankun'?' · '+QIANKUN_MODE_NAMES[s.weaponMode]:'')+(s.weapon2Name?' / 副兵器：'+s.weapon2Name:' / 副兵器：空')+(weapons[s.weapon]?' · '+weapons[s.weapon].name:s.weapon==='dart'?' · 飞镖':'');}
  else if(s.weapon&&weapons[s.weapon]){$('#hud-weapon').textContent=weapons[s.weapon].name+' · '+weapons[s.weapon].motto;}
  $('#enemy-status').classList.toggle('hidden',!s.enemy);if(s.enemy){$('#enemy-name').textContent=(s.locked?'◇ ':'')+'对手 · '+s.enemy.name;$('#enemy-bar').style.width=Math.max(0,s.enemy.hp/s.enemy.maxHp*100)+'%';$('#enemy-hp').textContent=Math.ceil(s.enemy.hp)+' / '+s.enemy.maxHp+' · '+({hit:'受击',guard:'格挡',down:'倒地',recover:'起身'}[s.enemy.reaction]||(Number.isFinite(s.enemy.distance)?'距离 '+Math.round(s.enemy.distance):''));}
  $('#mission-goal').classList.toggle('hidden',currentMode!=='story');if(currentMode==='story'){const mission=getNativeMission(currentMissionId),objective=s.mission?.objective;$('#mission-goal').textContent=mission.objective+(mission.objectiveType==='eliminate'?' · 剩余 '+(s.enemies?.length??0)+' 人':objective?.targetHp!=null?' · '+(objective.targetName||mission.protectName||mission.vipName)+' '+Math.ceil(objective.targetHp)+' / '+objective.targetMaxHp:'');}
  const statusText=(s.statuses||[]).map(item=>item.name+(item.period?' · 每'+item.period+'秒气血 '+item.value:item.statKey===5?' · 移速 '+item.value+'%':' · '+({1:'气血上限',3:'攻击',4:'防御'}[item.statKey]||'属性')+' +'+item.value)+(item.remaining>0?' · '+Math.ceil(item.remaining)+'秒':'')).join('；');$('#player-status').textContent=statusText;$('#player-status').classList.toggle('hidden',!statusText);
  const comboFeedback=$('#combo-feedback'),comboText=s.moveName||(s.combo>1?`${s.combo} 连击`:'');lastCombo=s.combo;
  if(comboFeedback.textContent!==comboText)comboFeedback.textContent=comboText;
  comboFeedback.classList.toggle('named-move',!!s.moveName);if(!s.moveName)comboFeedback.dataset.command='';
  $('#battle-hint-text').textContent=s.inputBlocked?'剧情进行中 · 对话后恢复操作':s.playerReaction==='hit'?'受击中 · 按住 '+keyHint('guard')+' 防御，恢复后接招':s.hp<=0?(currentMode==='story'?'任务结束':'胜败乃兵家常事 · 正在重返战场'):s.infiniteRage?'无限怒气调试中 · 暂停后查看各兵器招式':s.rage>=100?'怒气已满 · 暂停后「查看招式」可查怒气技':s.locked?'镜头跟随锁定目标 · '+keyHint('lock')+' 解除 · 战斗镜头固定方向':(s.weapon==='dart'?'七星飞镖 · '+keyHint('attack')+' 投掷 · 暂停后可查看招式':(game?.mouseLook?.locked?'移动鼠标转视角 · ':'点击画面锁定鼠标 · ')+keyHint('attack')+' 出招');
  if(s.hp<lastHp){$('#game-hud').style.boxShadow='inset 0 0 90px #a2222266';setTimeout(()=>$('#game-hud').style.boxShadow='',180);}lastHp=s.hp;
  drawMinimap(s);
}
function drawMinimap(s){const c=$('#minimap'),ctx=c.getContext('2d'),w=c.width;ctx.clearRect(0,0,w,w);ctx.save();ctx.translate(w/2,w/2);ctx.strokeStyle='#a6916050';ctx.lineWidth=1;ctx.strokeRect(-49,-49,98,98);ctx.beginPath();ctx.moveTo(-65,0);ctx.lineTo(65,0);ctx.moveTo(0,-65);ctx.lineTo(0,65);ctx.stroke();ctx.font='8px sans-serif';ctx.fillStyle='#d9bf8d';ctx.textAlign='center';ctx.fillText('北',0,-61);const bounds=s.mapBounds;const scale=bounds?110/Math.max(bounds.maxX-bounds.minX,bounds.maxZ-bounds.minZ,1):2.2;const cx=bounds?(bounds.minX+bounds.maxX)/2:0,cz=bounds?(bounds.minZ+bounds.maxZ)/2:0;for(const e of [...(s.enemies||[]).map(e=>({...e,ally:false})),...(s.allies||[]).map(e=>({...e,ally:true}))]){ctx.fillStyle=e.ally?'#83bdb3':'#ce6650';ctx.beginPath();ctx.arc(Math.max(-57,Math.min(57,(e.x-cx)*scale)),Math.max(-57,Math.min(57,(e.z-cz)*scale)),3,0,Math.PI*2);ctx.fill();}const objective=s.mission?.objective?.position;if(objective){const x=Math.max(-57,Math.min(57,(objective.x-cx)*scale)),z=Math.max(-57,Math.min(57,(objective.z-cz)*scale));ctx.strokeStyle='#f0cc78';ctx.lineWidth=2;ctx.strokeRect(x-4,z-4,8,8);}if(s.position){ctx.fillStyle='#e4d8a9';const x=Math.max(-57,Math.min(57,(s.position.x-cx)*scale)),z=Math.max(-57,Math.min(57,(s.position.z-cz)*scale));ctx.beginPath();ctx.moveTo(x,z-5);ctx.lineTo(x-4,z+4);ctx.lineTo(x+4,z+4);ctx.closePath();ctx.fill();}ctx.restore();}
function handleEvent(e){if(e.type==='pointer-unlock'){if(running&&!paused&&!loadingMatch)openModal('pause');return;}if(e.type==='pointer-error'){toast(e.text);return;}if(e.type==='load'){$('#load-status').textContent=e.text;return;}if(!running)return;if(e.type==='dialogue'){showDialogue(e);return;}if(e.type==='move'){const feedback=$('#combo-feedback');feedback.textContent=e.text||'';feedback.classList.add('named-move');feedback.dataset.command=e.command||'';return;}if(['mission-diagnostic','mission-compatibility'].includes(e.type)){console.warn(e.text,e);return;}if(e.type==='hit'){
  // Incoming damage has its HP/HUD response; this displays the player's blow.
  if(!e.attackerHero)return;
  clearTimeout(hitTimer);const feedback=$('#hit-feedback');
  feedback.textContent=e.guarded?'被格挡':(e.knockdown?'击倒 · ':e.guardBypassed?'破防 · ':'')+(Number.isFinite(e.amount)?Math.round(e.amount):'命中');
  feedback.dataset.kind=e.guarded?'guard':e.knockdown?'knockdown':'hit';feedback.style.opacity=1;
  hitTimer=setTimeout(()=>feedback.style.opacity=0,420);
}else if(e.text)announce(e.text,e.type==='kill'?1600:2000);}
function handleEnd(r){
  clearDialogue();clearCombatFeedback();running=false;ended=true;paused=true;game?.pause(true);
  const mission=currentMode==='story'?getNativeMission(currentMissionId):null;
  if(mission&&r.win&&!prefs.completedMissions.includes(mission.id))prefs.completedMissions.push(mission.id);
  prefs.best=Math.max(Number(prefs.best)||0,r.kills||0);save();modalKind='result';
  const title=mission?mission.name+' · '+(r.win?'任务完成':'任务失败'):(r.win?'一剑定江湖':'胜负，留待来日');
  const message=mission?(r.win?(mission.successText||'守卫已击败。可以返回任务列表，选择下一场挑战。'):(mission.failureText||'孟星魂倒下了。重整兵器，再试一次。')):(r.win?'剑锋所指，皆为坦途。':'整装，再出发。');
  $('#modal-content').innerHTML=`<span class="result-seal">${r.win?'此战 · 胜':'再战 · 江湖'}</span>${header(mission?'THE ORIGINAL STORY':'THE DUEL IS OVER',title,message)}<div class="results-grid"><div><strong>${Number(r.kills)||0}</strong><span>击败对手</span></div><div><strong>${Number(r.deaths)||0}</strong><span>倒下次数</span></div><div><strong>${Math.round(Number(r.damage)||0)}</strong><span>造成伤害</span></div></div><div class="modal-actions"><button class="primary-button" data-do="restart"><span>再战一场</span>${icon('arrow')}</button>${mission?'<button class="secondary-button" data-open="mission">任务列表</button>':''}<button class="secondary-button" data-do="lobby">返回江湖</button></div>`;if(!modal.open)modal.showModal();
}
function toggleSound(){prefs.muted=!prefs.muted;game?.setMuted(prefs.muted);syncMusic();save();updateSelection();if(modalKind==='settings')openModal('settings');}
document.addEventListener('click',e=>{
  if(characterSelectionBusy)return;
  const sound=e.target.closest('.sound-toggle');if(sound){toggleSound();return;}
  const guideChoice=e.target.closest('[data-guide-weapon]');if(guideChoice&&modalKind==='guide'&&weapons[guideChoice.dataset.guideWeapon]){guideWeapon=guideChoice.dataset.guideWeapon;$$('[data-guide-weapon]').forEach(button=>{const selected=button.dataset.guideWeapon===guideWeapon;button.classList.toggle('selected',selected);button.setAttribute('aria-pressed',String(selected));});$('#guide-move-panel').innerHTML=renderNativeMoveGuide(guideWeapon);return;}
  const map=e.target.closest('[data-map]');if(map&&!running){selectMap(map.dataset.map);return;}
  const spearStyle=e.target.closest('[data-spear-style]');if(spearStyle&&!running&&['original','phoenix'].includes(spearStyle.dataset.spearStyle)){prefs.spearStyle=spearStyle.dataset.spearStyle;prefs.weapon='spear';game?.setSpearStyle(prefs.spearStyle);game?.setWeapon('spear');save();updateSelection();return;}
  const swordStyle=e.target.closest('[data-sword-style]');if(swordStyle&&!running&&Object.hasOwn(swordStyleNames,swordStyle.dataset.swordStyle)){prefs.swordStyle=swordStyle.dataset.swordStyle;prefs.weapon='sword';game?.setSwordStyle(prefs.swordStyle);game?.setWeapon('sword');save();updateSelection();return;}
  const weapon=e.target.closest('[data-weapon]');if(weapon){prefs.weapon=weapon.dataset.weapon;save();game?.setWeapon(prefs.weapon);updateSelection();if(modal.open&&modalKind==='weapons')openModal('weapons');return;}
  const character=e.target.closest('[data-pick-character], [data-pick-appearance]');if(character){const appearance=character.dataset.pickAppearance||'original',id=character.dataset.pickCharacter===undefined?0:Number(character.dataset.pickCharacter);selectCharacter(id,appearance);return;}
  const nav=e.target.closest('[data-panel]');if(nav){if(nav.dataset.panel==='home'){if(modal.open)closeModal();}else openModal(nav.dataset.panel);return;}
  const opener=e.target.closest('[data-open]');if(opener){openModal(opener.dataset.open);return;}
  const action=e.target.closest('[data-do]');if(action){switch(action.dataset.do){case'play':startMatch('training');break;case'restart':startMatch(currentMode);break;case'story':startMatch('story',action.dataset.mission||currentMissionId);break;case'resume':closeModal();break;case'lobby':returnLobby();break;case'sound':toggleSound();break;}}
});
$('#start-game').addEventListener('click',startMatch);$('#close-modal').addEventListener('click',closeModal);$('#pause-button').addEventListener('click',()=>openModal('pause'));
modal.addEventListener('cancel',e=>{e.preventDefault();closeModal();});modal.addEventListener('click',e=>{if(e.target===modal){const r=modal.getBoundingClientRect();if(e.clientX<r.left||e.clientX>r.right||e.clientY<r.top||e.clientY>r.bottom)closeModal();}});
document.addEventListener('keydown',e=>{if(e.key==='Escape'&&!modal.open&&running){e.preventDefault();openModal('pause');}});
document.addEventListener('visibilitychange',()=>{if(document.hidden&&running&&!paused)openModal('pause');syncMusic();});
window.addEventListener('blur',()=>{if(running&&!paused)openModal('pause');});
document.addEventListener('change',e=>{if(e.target.id==='show-fps'){prefs.showFps=e.target.checked;game?.frameOverlay?.setVisible(prefs.showFps);save();return;}if(e.target.id==='infinite-rage'){prefs.infiniteRage=e.target.checked;game?.setInfiniteRage(prefs.infiniteRage);save();updateSelection();return;}if(e.target.id==='spear-style'){if(!['original','phoenix'].includes(e.target.value))return;prefs.spearStyle=e.target.value;game?.setSpearStyle(prefs.spearStyle);save();updateSelection();return;}if(e.target.id==='sword-style'){if(!Object.hasOwn(swordStyleNames,e.target.value))return;prefs.swordStyle=e.target.value;game?.setSwordStyle(prefs.swordStyle);save();updateSelection();return;}if(e.target.id==='quality'){prefs.quality=e.target.value;game?.setQuality(prefs.quality);save();}if(e.target.id==='character-appearance'){applyCharacterAppearance(e.target.value);return;}if(e.target.id==='difficulty'){prefs.difficulty=e.target.value;save();updateSelection();}});
$('#appearance-toggle').addEventListener('click',()=>{const appearances=Object.keys(NATIVE_APPEARANCES).filter(id=>readyAppearances.has(id));applyCharacterAppearance(appearances[(appearances.indexOf(prefs.characterAppearance)+1)%appearances.length]);});
$('#difficulty-toggle').addEventListener('click',()=>{prefs.difficulty=prefs.difficulty==='normal'?'hard':'normal';save();updateSelection();toast(prefs.difficulty==='hard'?'已切换：江湖高手':'已切换：江湖新手');});
$('#fullscreen').addEventListener('click',async()=>{try{if(document.fullscreenElement)await document.exitFullscreen();else if(document.documentElement.requestFullscreen)await document.documentElement.requestFullscreen();else toast('当前浏览器不支持全屏，可使用浏览器全屏模式');}catch{toast('当前浏览器暂不允许全屏');}});
$('#pickup-hint').addEventListener('click',()=>{game?.action('pickup');$('#world').focus();});
$$('[data-action]').filter(button=>button.id!=='pickup-hint').forEach(button=>{button.addEventListener('pointerdown',e=>{e.preventDefault();if(!running||paused)return;button.setPointerCapture(e.pointerId);game.action(button.dataset.action,true);});for(const type of ['pointerup','pointercancel','lostpointercapture'])button.addEventListener(type,e=>{e.preventDefault();game?.action(button.dataset.action,false);});});
networkLobby=new NetworkLobby({getGame:()=>game,onStart:isCurrent=>startMatch('network',undefined,isCurrent),onNotice:text=>toast(text),onStop:text=>{returnLobby();toast(text);}});
updateSelection();
try{
  const {MeteorGame}=await import('./engine.js');game=new MeteorGame($('#world'),{onUpdate:updateHUD,onEvent:handleEvent,onEnd:handleEnd});game.setKeyBindings(keyBindings);window.__game=game;game.frameOverlay.setVisible(prefs.showFps);await game.ready;game.setSwordStyle(prefs.swordStyle);game.setSpearStyle(prefs.spearStyle);game.setInfiniteRage(prefs.infiniteRage);game.setMuted(prefs.muted);game.setQuality(prefs.quality);game.setWeapon(prefs.weapon);await game.setCharacter?.(prefs.character);await game.menu(prefs.map);await applyCharacterAppearance(prefs.characterAppearance,false);
  $('#load-status').textContent='江湖已就绪';$('#load-screen').style.opacity=0;setTimeout(()=>$('#load-screen').classList.add('hidden'),650);
}catch(error){console.error(error);$('#load-screen').classList.add('hidden');const el=document.createElement('div');el.className='fatal-error';const text=document.createElement('p');text.textContent='江湖画卷未能展开。请使用支持 WebGL 的新版浏览器，并通过本地服务器打开。';const btn=document.createElement('button');btn.textContent='重新加载';btn.addEventListener('click',()=>location.reload());el.append(text,btn);document.body.append(el);}
