import {MenuSnapshots} from './menu-snapshots.js';
import { NetworkLobby } from './network-lobby.js';
import { NETWORK_MODES } from './network-rules.js';
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
import { DEFAULT_CHARACTER_APPEARANCE, NATIVE_CHARACTERS, NATIVE_APPEARANCES } from './native-character.js';
import { FEATURED_APPEARANCES, appearanceDetails, appearanceCharacterName, appearanceCharacterSeal, battleCharacterSelection, savedBattleCharacterSelection } from './character-appearances.js';
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
let prefs={showFps:false,weapon:'sword',map:'sifang',character:0,characterAppearance:DEFAULT_CHARACTER_APPEARANCE,characterSelected:false,swordStyle:'butterfly',spearStyle:'original',mission:'sn01',completedMissions:[],difficulty:'normal',infiniteRage:false,muted:true,quality:matchMedia('(pointer:coarse)').matches?'low':'high',best:0};
try{const p=JSON.parse(localStorage.getItem('meteor-web-original-v2')||'{}');for(const k of ['showFps','weapon','map','character','characterAppearance','characterSelected','swordStyle','spearStyle','mission','completedMissions','difficulty','infiniteRage','muted','quality','best'])if(p[k]!==undefined)prefs[k]=p[k];}catch{}

if(!maps[prefs.map]){if(/^sn\d{2}$/.test(prefs.map))maps[prefs.map]={name:prefs.map.toUpperCase(),english:'ORIGINAL MAP',poem:'原版战场'};else prefs.map='sifang';}if(!weapons[prefs.weapon])prefs.weapon='sword';if(!['normal','hard'].includes(prefs.difficulty))prefs.difficulty='normal';if(!['low','high'].includes(prefs.quality))prefs.quality='high';
Object.assign(prefs, savedBattleCharacterSelection(prefs));
if(!Object.hasOwn(swordStyleNames,prefs.swordStyle))prefs.swordStyle='butterfly';
if(!['original','phoenix'].includes(prefs.spearStyle))prefs.spearStyle='original';
prefs.infiniteRage=prefs.infiniteRage===true;
const appearanceURL = new URL(location.href);
const linkedAppearance = appearanceURL.searchParams.get('appearance');
if (linkedAppearance !== null) {
  if (Object.hasOwn(NATIVE_APPEARANCES, linkedAppearance)) {
    Object.assign(prefs, battleCharacterSelection({ character: 0, characterAppearance: linkedAppearance }), { characterSelected: true });
  }
  appearanceURL.searchParams.delete('appearance');
  history.replaceState(null, '', appearanceURL.pathname + appearanceURL.search + appearanceURL.hash);
}
const save=()=>{try{localStorage.setItem('meteor-web-original-v2',JSON.stringify(prefs));}catch{}};
if(!getNativeMission(prefs.mission))prefs.mission='sn01';
prefs.completedMissions=NATIVE_MISSIONS.filter(m=>Array.isArray(prefs.completedMissions)&&prefs.completedMissions.includes(m.id)).map(m=>m.id);
let currentMode='training',currentMissionId=prefs.mission;
let dialogueTimer=null,dialogueQueue=[];
let loadingMatch=false,characterSelectionBusy=false;
let mapSelectionRequest=0;
let game,running=false,paused=false,ended=false,modalKind='',toastTimer,announcementTimer,hitTimer,lastCombo=0,lastHp=100;
let nativeCombat=null,menuSnapshots,mapPreviewRequest=0,weaponPreviewRequest=0;
function releaseMenuSnapshots(){mapPreviewRequest++;weaponPreviewRequest++;menuSnapshots?.clear();$('#lobby').style.removeProperty('--selected-map-image');const image=$('#weapon-preview-image');image.hidden=true;image.removeAttribute('src');}
async function refreshMapPreview(){
  const request=++mapPreviewRequest,key=canonicalMap(prefs.map);$('#lobby').style.removeProperty('--selected-map-image');$('#menu-map-state').textContent='正在绘制场景预览…';
  try{const url=await menuSnapshots?.map(key);if(request!==mapPreviewRequest||running)return;if(!url){$('#menu-map-state').textContent='场景预览暂不可用';return;}$('#lobby').style.setProperty('--selected-map-image',`url("${url}")`);$('#menu-map-state').textContent='实景截图 · '+maps[prefs.map].name;}catch(error){if(request===mapPreviewRequest&&!running)$('#menu-map-state').textContent='场景预览未能生成，可继续入场';console.warn(error);}
}
async function refreshWeaponPreview(){
 const request=++weaponPreviewRequest,key=[prefs.weapon,prefs.swordStyle,prefs.spearStyle].join(':');const image=$('#weapon-preview-image');image.hidden=true;image.removeAttribute('src');$('#weapon-preview-status').textContent='正在绘制模型预览…';
 try{const result=await menuSnapshots?.weapon(key);if(request!==weaponPreviewRequest||running)return;if(!result){$('#weapon-preview-status').textContent='模型预览暂不可用，可继续入场';return;}const name=prefs.weapon==='sword'?swordStyleNames[result.style]:prefs.weapon==='spear'?(result.style==='phoenix'?'霜翎凤鸣枪':'原版长枪'):weapons[prefs.weapon].sourceName;image.src=result.url;image.alt=name+'模型预览';image.hidden=false;$('#weapon-preview-title').textContent=name;const expected=prefs.weapon==='sword'?prefs.swordStyle:prefs.weapon==='spear'?prefs.spearStyle:'original';$('#weapon-preview-status').textContent=result.style===expected?'模型实拍 · 选中时更新':'所选外观暂未就绪，显示原版模型';}catch(error){if(request===weaponPreviewRequest&&!running)$('#weapon-preview-status').textContent='模型预览未能生成，可继续入场';console.warn(error);}
}
async function selectMenuWeapon(name){if(running||!game)return;const request=++weaponPreviewRequest;prefs.weapon=name;save();updateSelection();$('#weapon-preview-image').hidden=true;$('#weapon-preview-status').textContent='正在载入兵器…';try{await game.setWeapon(name);if(request===weaponPreviewRequest&&!running)await refreshWeaponPreview();}catch(error){if(request===weaponPreviewRequest)$('#weapon-preview-status').textContent='兵器未能载入，请重试';console.warn(error);}}

let guideWeapon='sword',lobbyPage='home',settingsTab='picture';
const characterSelectionLocked = () => running && currentMode !== 'training';

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
  $('#menu-map-name').textContent=maps[prefs.map].name;$('#menu-map-poem').textContent=maps[prefs.map].poem;
  $('#scene-name').textContent=maps[prefs.map].name;$('#scene-english').textContent=maps[prefs.map].english;$('#scene-poem').textContent=maps[prefs.map].poem;
  $('#start-game small').textContent=prefs.map===QIYUN_MAP.id?'全新战场 · 招式演武':'原版场景 · 招式演武';
  $$('.sound-toggle').forEach(el=>{el.innerHTML=icon(prefs.muted?'muted':'volume');el.setAttribute('aria-label',prefs.muted?'开启音效':'关闭音效');el.title=prefs.muted?'开启音效':'关闭音效';});
  $('#hud-weapon').textContent=weapons[prefs.weapon].name+' · '+weapons[prefs.weapon].motto;
  const name=appearanceCharacterName(prefs.character,prefs.characterAppearance),descriptor=NATIVE_APPEARANCES[prefs.characterAppearance];
  const appearanceApplies=descriptor?.characterId===prefs.character;
  $('#character-label').textContent=name+(appearanceApplies&&appearanceDetails(prefs.characterAppearance).kind==='pmx'?' · 模型外观':'');
  $('#appearance-label').textContent=appearanceApplies?appearanceDetails(prefs.characterAppearance).shortLabel:'原版';$('#appearance-toggle').disabled=prefs.character!==0||characterSelectionLocked();
  $('#appearance-toggle').title='依次切换'+Object.keys(NATIVE_APPEARANCES).map(id=>appearanceDetails(id).shortLabel).join('、');
  $('#player-name').textContent=name;$('.player-seal').textContent=appearanceCharacterSeal(prefs.character,prefs.characterAppearance);
  $('#home-loadout').textContent=name+' · '+weapons[prefs.weapon].name;$('#prep-summary').textContent=name+' / '+weapons[prefs.weapon].name+' / '+maps[prefs.map].name;
  $('#hero-character-name').textContent=name;$('#hero-character-seal').textContent=appearanceCharacterSeal(prefs.character,prefs.characterAppearance);$('.hero-character').setAttribute('aria-label',`选择人物，当前${name}`);
  const appearanceSelect=$('#character-appearance');if(appearanceSelect){appearanceSelect.value=prefs.characterAppearance;appearanceSelect.disabled=prefs.character!==0||$('#appearance-toggle').disabled;}
}
const header=(en,title,desc='')=>`<div class="modal-kicker">${en}</div><h2 class="modal-title">${title}</h2>${desc?`<p class="modal-desc">${desc}</p>`:''}`;
function guideHTML(){return header('THE WAY OF THE WARRIOR','武学招式','方向接攻击，步法接刀锋。选一柄兵器，查看出招指令。')+`<div class="combo-legend"><p><kbd>A</kbd> 是攻击记号：按 <kbd>${keyHint('attack')}</kbd>。</p><p><span>↑ ↓ ← →</span> 对应 <kbd>${['forward','back','left','right'].map(keyHint).join('；')}</kbd>。连续按顺序输入，重复方向先松开再按。<br>跳跃：<kbd>${keyHint('jump')}</kbd>。空中招式需离地后输入，连段需衔接前一招。火铳先按攻击举枪，举枪完成后再按攻击射击；移动鼠标瞄准，防御或跳跃收枪。</p></div><div class="combo-weapon-filter" role="group" aria-label="查看兵器招式">${Object.keys(weapons).map(weapon=>`<button type="button" data-guide-weapon="${weapon}" aria-pressed="${guideWeapon===weapon}" aria-controls="guide-move-panel"${guideWeapon===weapon?' class="selected"':''}>${weapons[weapon].name}</button>`).join('')}</div><div id="guide-move-panel" aria-labelledby="guide-weapon-heading">${renderNativeMoveGuide(guideWeapon)}</div><details class="guide-controls"><summary>移动、防御与其他操作</summary><div class="controls-grid">${[[['forward','left','back','right'].map(keyHint).join('；'),'移动'],['移动鼠标（进入游戏后锁定）','转动视角'],[keyHint('attack'),'攻击（招式中的 A）'],[keyHint('guard'),'防御'],[keyHint('crouch'),'蹲下'],[keyHint('jump'),'跳跃'],[keyHint('lock'),'锁定 / 解除'],[keyHint('switch'),'切换兵器'],['走近物品','自动拾取'],[keyHint('drop'),'丢弃副兵器'],['Esc','暂停 / 返回对战']].map(([k,v])=>`<div class="control-row"><span>${v}</span><kbd>${k}</kbd></div>`).join('')}</div><p class="modal-note">按住 ${keyHint('crouch')}，快速按两次同一方向（两次之间松开），可向前、后、左、右翻滚。触屏按住「蹲」后也可双击方向。<br>触屏使用方向键和「攻」依次输入，「跃」后可施展空中招式。上方兵器按钮只切换查看内容；实际换兵器请按 ${keyHint('switch')}。</p></details><div class="modal-actions"><button class="primary-button" data-do="${running?'resume':'play'}"><span>${running?'重返对决':'前往演武整装'}</span>${icon('arrow')}</button></div>`;}
function weaponsHTML(){const w=weapons[prefs.weapon];const moves=nativeCombat?.moves?.[prefs.weapon]||[];return header('THE ARMORY','兵器谱','兵无常势，水无常形。选一柄趁手兵器，再入江湖。')+`<div class="weapon-options">${Object.entries(weapons).map(([key,v])=>`<button class="weapon-option ${key===prefs.weapon?'selected':''}" data-weapon="${key}" aria-pressed="${key===prefs.weapon}"><span class="weapon-glyph">${v.glyph}</span><strong>${v.name}</strong><small>${v.motto}<br>${'原版 · '+v.sourceName}</small></button>`).join('')}</div><p class="modal-desc" id="weapon-description">${w.desc}</p>${moves.length?`<div class="native-moves">${moves.map(move=>`<div><strong>${move.name||'第'+move.id+'式'}</strong><span>${move.frameCount} 帧 · ${move.duration.toFixed(2)} 秒</span></div>`).join('')}</div>`:''}<p class="modal-note">当前随身兵器：${w.name}。演武中按 ${keyHint('switch')} 切换主副兵器；单机任务按 ${keyHint('switch')} 切换原随身兵器。按 ${keyHint('attack')} 连击或投掷。</p><div class="modal-actions"><button class="primary-button" data-do="play"><span>返回战前整装</span>${icon('arrow')}</button></div>`;}

function resourcesHTML(){return header('THE METEOR ARCHIVE','流星典藏','优先读取本地客户端的原始素材，流星资源网提供格式资料与缺失资源补充。')+`<div class="resource-list"><a class="resource-link" href="./assets/original/manifest.json" target="_blank" rel="noopener noreferrer"><span>本</span><div><strong>本地客户端原素材</strong><small>20 位人物 · 22 份地图 · 原始招式与配乐</small></div><span>↗</span></a><a class="resource-link" href="https://www.lxres.com/" target="_blank" rel="noopener noreferrer"><span>源</span><div><strong>流星资源网</strong><small>原版客户端 · 单机任务 · 人物兵器 · 地图资源</small></div><span>↗</span></a><a class="resource-link" href="https://www.lxres.com/LiuXingBiJi/1566.html" target="_blank" rel="noopener noreferrer"><span>图</span><div><strong>地图 GMC 结构笔记</strong><small>原生地图格式的 Web 解析依据</small></div><span>↗</span></a><a class="resource-link" href="./assets/SOURCES.md" target="_blank" rel="noopener noreferrer"><span>记</span><div><strong>本项目素材来源清单</strong><small>已使用的地图、贴图与转换记录</small></div><span>↗</span></a></div><p class="modal-note">这是《流星蝴蝶剑.net》的非官方 Web 实验重构。读取本地原版模型、骨骼、动画与招式表，在浏览器运行；剧情脚本与联网协议仍在逐项移植。原游戏与社区素材的权利归各自权利人所有。</p>`;}
function settingsHTML(){
  const tabs={picture:'画面',sound:'声音',controls:'操作与键位',interface:'界面与提示'};
  const row=(title,desc,control)=>`<div class="settings-row"><label>${title}<small>${desc}</small></label>${control}</div>`;
  const contents={picture:row('画面品质','根据帧率自动调整渲染倍率；流畅优先降低像素密度',`<select aria-label="画面品质" id="quality" class="setting-select"><option value="high" ${prefs.quality==='high'?'selected':''}>精致画面</option><option value="low" ${prefs.quality==='low'?'selected':''}>流畅优先</option></select>`),sound:row('音乐与音效','立即切换背景音乐与战斗音效',`<button class="secondary-button" data-do="sound" aria-label="音乐与音效" aria-pressed="${!prefs.muted}">${prefs.muted?'开启声音':'关闭声音'}</button>`),controls:row('自定义按键','按移动、战斗和视角配置；支持保存与恢复默认','<button class="secondary-button" data-open="keys">设置按键</button>')+'<p>进入游戏后点击画面锁定鼠标，移动鼠标转动视角。Esc 打开暂停菜单。</p>',interface:row('实时帧率','排查性能时开启；显示 FPS、帧耗时与渲染倍率',`<input id="show-fps" aria-label="实时帧率" type="checkbox" ${prefs.showFps?'checked':''}>`)};
  return header('JIANGHU / SETTINGS','游戏设置','画面、声音与界面设置即时保存到当前浏览器。')+`<div class="settings-layout"><nav class="settings-tabs" aria-label="设置分类">${Object.entries(tabs).map(([id,name])=>`<button data-settings-tab="${id}" aria-pressed="${settingsTab===id}">${name}</button>`).join('')}</nav><section class="settings-content"><h3>${tabs[settingsTab]}</h3>${contents[settingsTab]}<p class="modal-note">角色与兵器在战前整装中选择，对手难度和无限怒气仅放在演武选项中。${running?'关闭后返回暂停菜单。':''}</p></section></div>`;
}
function pauseHTML(){if(networkLobby?.session)return header('MULTIPLAYER','联机对战','打开菜单不会暂停其他玩家的战斗。')+'<div class="pause-actions"><button class="primary-button" data-do="resume">继续对战</button><button class="secondary-button" data-open="guide">查看招式</button><button class="secondary-button" data-open="settings">游戏设置</button><button class="secondary-button" data-do="lobby">退出房间</button></div>';return `<div class="pause-title">${header('A MOMENT OF STILLNESS','且歇片刻','刀剑暂收，江湖还在。')}</div><div class="pause-actions"><button class="primary-button" data-do="resume"><span>继续对决</span>${icon('arrow')}</button><button class="secondary-button" data-open="guide">查看招式</button><button class="secondary-button" data-open="settings">游戏设置</button><button class="secondary-button" data-do="restart">重新论剑</button><button class="secondary-button" data-do="prepare">重新整装</button><button class="secondary-button" data-do="lobby">返回江湖首页</button></div>`;}
function missionHTML(){const chosen=getNativeMission(currentMissionId)||NATIVE_MISSIONS[0];return header('JIANGHU / STORY','单机任务','先查看任务目标与起始装备，再踏入江湖。')+`<div class="mission-layout"><div class="mission-list" aria-label="关卡列表">${NATIVE_MISSIONS.map(m=>`<button class="mission-card ${m.id===chosen.id?'mission-selected':''}" data-select-mission="${m.id}" aria-pressed="${m.id===chosen.id}"><small>${m.id.toUpperCase()}${prefs.completedMissions.includes(m.id)?' · 已完成':''}</small><strong>${m.name}</strong></button>`).join('')}</div><section class="mission-detail"><div class="modal-kicker">本关目标</div><h3>${chosen.name}</h3><p>${chosen.description}</p><p class="mission-objective">${chosen.objective}</p><dl><dt>起始气血</dt><dd>${chosen.playerHp}</dd><dt>起始兵器</dt><dd>${chosen.weapon}</dd><dt>人物身份</dt><dd>孟星魂 · 沿用任务配置</dd></dl><p class="modal-note">本关装备由任务决定，无需在演武中整装。完成记录保存在当前浏览器。</p><div class="page-dock"><span>目标确认，随时入场</span><button class="primary-button" data-do="story" data-mission="${chosen.id}">开始任务 →</button></div></section></div>`;}
function charactersHTML(){
  const choices=Object.keys(NATIVE_APPEARANCES).map(id=>[id,id==='original'?'孟星魂':appearanceDetails(id).name,id==='original'?'原版人物':id==='hd'?'高清试版':id==='raiden'?'礼服外观':'模型外观']);
  return header('CHOOSE YOUR FIGHTER','选择人物','先选一位人物，再执剑入江湖。')+`<div class="character-section-label">精选人物 <span>FEATURED</span></div><div class="featured-characters">${choices.map(([appearance,name,subtitle])=>{const selected=prefs.character===0&&prefs.characterAppearance===appearance,available=readyAppearances.has(appearance);return `<button class="featured-character ${selected?'selected':''} featured-${appearance}" data-pick-appearance="${appearance}" aria-pressed="${selected}" ${characterSelectionBusy||!available?'disabled':''}><span class="featured-seal" aria-hidden="true">${appearanceCharacterSeal(0,appearance)}</span><span class="featured-copy"><strong>${name}</strong><small>${available?subtitle:'资源未就绪'}</small></span><span class="featured-check" aria-hidden="true">✓</span></button>`;}).join('')}</div><div class="character-section-label">更多原版人物 <span>ORIGINAL CAST</span></div><div class="character-grid">${NATIVE_CHARACTERS.filter(c=>c.id!==0).map(c=>`<button class="character-option ${c.id===prefs.character&&prefs.characterAppearance==='original'?'selected':''}" data-pick-character="${c.id}" aria-pressed="${c.id===prefs.character&&prefs.characterAppearance==='original'}" ${characterSelectionBusy?'disabled':''}><img src="${c.portrait}" alt="" loading="lazy"><span>${c.name}</span></button>`).join('')}</div><p class="modal-note" id="character-pick-status" role="status">${characterSelectionBusy?'正在载入人物…':'原版单机任务沿用孟星魂身份，可使用已选的孟星魂外观。'}</p>`;
}
function refreshCharacterOptions(){
  if(!modal.open||modalKind!=='characters')return;
  for(const button of $$('[data-pick-appearance]')){const id=button.dataset.pickAppearance,ready=readyAppearances.has(id);button.disabled=characterSelectionBusy||!ready;const small=button.querySelector('small');if(small)small.textContent=ready?({original:'原版人物',hd:'高清试版',hutao:'模型外观',raiden:'礼服外观',emilia:'模型外观'}[id]||'人物外观'):'资源未就绪';}

}
async function selectCharacter(id,appearance){
  if(characterSelectionBusy||characterSelectionLocked()||!game||!Number.isInteger(id)||!NATIVE_CHARACTERS[id]||!Object.hasOwn(NATIVE_APPEARANCES,appearance)||!readyAppearances.has(appearance))return;
  characterSelectionBusy=true;$('#start-game').disabled=true;
  for(const button of $$('[data-pick-character], [data-pick-appearance]'))button.disabled=true;
  const status=$('#character-pick-status');if(status)status.textContent='正在载入人物…';
  try{
    await game.setCharacter(id, appearance);
    prefs.character=id;prefs.characterAppearance=appearance;prefs.characterSelected=true;save();updateSelection();
    if(modal.open&&modalKind==='characters')closeModal();
  }catch(error){
    console.error(error);
    if(appearance!=='original')markAppearanceUnavailable(appearance);
    updateSelection();toast('人物未能载入，已保留当前人物');
  }finally{
    characterSelectionBusy=false;$('#start-game').disabled=loadingMatch||Boolean($('#scene-load-status').textContent);
    if(modal.open&&modalKind==='characters')openModal('characters');
  }
}
function mapsHTML(){return header('CHOOSE YOUR BATTLEGROUND','选择战场','选一处江湖，再执剑入场。')+`<input id="map-search" class="setting-select map-search" aria-label="搜索战场" placeholder="搜索战场名称或编号"><div class="original-map-grid">${[QIYUN_MAP,...(originalManifest?.maps||[])].map(map=>`<button class="original-map-option ${map.id===canonicalMap(prefs.map)?'selected':''}" data-map="${map.id}" ${map.available===false?'disabled':''}><small>${map.id===QIYUN_MAP.id?'全新战场':map.id.toUpperCase()}</small><strong>${map.name||'未命名地图'}</strong><span>${map.id===QIYUN_MAP.id?'山间古庭 · 演武':map.available===false?'原文件数据异常':map.name?'原版场景':'名称待核实'}</span></button>`).join('')}</div>`;}
async function selectMap(id){const request=++mapSelectionRequest,previous=prefs.map;prefs.map=id;mapPreviewRequest++;$('#lobby').style.removeProperty('--selected-map-image');$('#menu-map-state').textContent='正在读取战场…';save();updateSelection();if(modal.open){modal.close();modalKind='';priorFocus?.focus?.();}$('#start-game').disabled=true;$('#scene-load-status').textContent='正在读取战场…';try{await game?.menu(id);if(request===mapSelectionRequest&&!running)await refreshMapPreview();}catch(error){console.error(error);if(request===mapSelectionRequest){prefs.map=previous;save();updateSelection();refreshMapPreview();toast('这张战场暂未能载入，请重试');}}finally{if(request===mapSelectionRequest){$('#start-game').disabled=false;$('#scene-load-status').textContent='';}}}
const pageKinds=new Set(['network','mission','guide','resources','settings']);
function showLobbyPage(page){
  if(running)return;
  disposeKeySettings?.();disposeKeySettings=null;
  if(modal.open)modal.close();modalKind='';lobbyPage=page;$('#lobby').dataset.page=page;
  $('#home-page').hidden=page!=='home';$('#prep-page').hidden=page!=='prep';$('#page-content').hidden=['home','prep'].includes(page);
  $$('[data-route], .side-nav [data-open]').forEach(button=>{const active=(button.dataset.route||button.dataset.open)===page;if(active)button.setAttribute('aria-current','page');else button.removeAttribute('aria-current');});
  $('#active-room').hidden=!networkLobby?.client;
  window.scrollTo(0,0);
}
function openModal(kind){
  disposeKeySettings?.();disposeKeySettings=null;
  if(kind==='guide')guideWeapon=weapons[game?.hero?.weapon]?game.hero.weapon:prefs.weapon;
  const renderers={guide:guideHTML,weapons:weaponsHTML,characters:charactersHTML,mission:missionHTML,maps:mapsHTML,network:()=>header('JIANGHU / MULTIPLAYER','江湖会武','同一游戏服务中的房间会出现在这里。')+'<div id="network-lobby"></div>',resources:resourcesHTML,settings:settingsHTML,keys:()=>header('SETTINGS / CONTROLS','自定义按键','保存键位后生效；关闭返回设置。')+'<div id="key-settings"></div>',pause:pauseHTML};
  if(!running&&!ended&&pageKinds.has(kind)){
    showLobbyPage(kind);$('#page-content').innerHTML='<button class="game-back" data-route="home" aria-label="返回游戏大厅">← 返回大厅</button>'+(renderers[kind]||guideHTML)();
    if(kind==='network')networkLobby.mount($('#network-lobby'));
    $('#page-content').focus({preventScroll:true});return;
  }
  if(!modal.open)priorFocus=document.activeElement;
  modalKind=kind;modal.dataset.kind=kind;
  if(running&&!paused){paused=true;game?.pause(true);}
  $('#modal-content').innerHTML=(renderers[kind]||guideHTML)();
  if(kind==='network')networkLobby.mount($('#network-lobby'));
  if(kind==='keys')disposeKeySettings=mountKeySettings($('#key-settings'),{bindings:keyBindings,storage:keyStorage,onSave:next=>{keyBindings=next;game?.setKeyBindings(next);refreshKeyGuide();}});
  if(!modal.open)modal.showModal();
}
function closeModal(){
  const previous=modalKind;disposeKeySettings?.();disposeKeySettings=null;if(modal.open)modal.close();modalKind='';
  if(ended){returnLobby();return;}
  if(running&&paused&&previous!=='pause'){openModal('pause');return;}
  if(running&&paused){paused=false;game?.pause(false);}
  priorFocus?.focus?.();if(running&&!paused&&!matchMedia('(pointer:coarse)').matches)game?.requestMouseLock();
}
async function startMatch(mode='training',missionId=currentMissionId,isCurrent=()=>true,roomSelection){

  if(loadingMatch||characterSelectionBusy)return;
  if(typeof mode!=='string')mode='training';if(mode!=='network'&&networkLobby?.client)await networkLobby.leave(false);currentMode=mode==='network'?'network':mode==='story'?'story':'training';const mission=currentMode==='story'?getNativeMission(missionId):null;if(currentMode==='story'){if(!mission){toast('这段原版任务尚未开放');return;}currentMissionId=mission.id;prefs.mission=mission.id;save();}

  const map = mission?.mapId ?? (currentMode === 'network' ? 'sifang' : prefs.map);
  const selection = battleCharacterSelection(currentMode === 'network' ? roomSelection : prefs);
  if(!game)return;releaseMenuSnapshots();game.menuIdle=false;game.frameMeter?.reset();if(!matchMedia('(pointer:coarse)').matches)game.requestMouseLock();$('#start-game').disabled=true;
  if(modal.open)modal.close();$('#page-content').replaceChildren();ended=false;paused=false;running=true;lastCombo=0;lastHp=mission?.playerHp??1000;clearDialogue();clearCombatFeedback();matchLoading(true);$('#load-status').textContent=mission?'正在载入'+mission.name+'与原版任务脚本…':'正在载入'+maps[map].name+'…';
  $('#lobby').classList.add('hidden');$('#game-hud').classList.remove('hidden');document.body.classList.add('playing');
  $('#hud-map').textContent=currentMode==='network'?'四方阵 · 联机对战':maps[map].name+(currentMode==='story'?' · 单机任务':' · 演武');$('#battle-hint-text').textContent='原版招式演武 · 按 '+keyHint('attack')+' 出招';$('#combo-feedback').textContent='';
  try{if(!isCurrent())return;game.setInfiniteRage(currentMode==='training'&&prefs.infiniteRage);await game.start({map,weapon:currentMode==='network'?'sword':prefs.weapon,difficulty:prefs.difficulty,...selection,mode:currentMode});if(!isCurrent())return;game.setMuted(prefs.muted);game.setQuality(prefs.quality);syncMusic();announce(currentMode==='network'?'联机战场载入中':mission?mission.name+' · 单机任务':'演武 · 开始',2200);$('#world').setAttribute('tabindex','-1');$('#world').focus();}
  catch(e){if(isCurrent()){if(currentMode==='network')throw e;console.error(e);returnLobby();toast('战场加载失败，请刷新重试');}}
  finally{matchLoading(false);}
}
function returnLobby(){if(game)game.menuIdle=true;if(networkLobby?.client){networkLobby.leave();return;}if(modal.open)modal.close();running=false;paused=false;ended=false;clearDialogue();clearCombatFeedback();game?.pause(false);game?.menu(prefs.map, battleCharacterSelection(prefs)).then(async()=>{if(!running){await game.setWeapon(prefs.weapon);if(!running){refreshMapPreview();refreshWeaponPreview();}}}).catch(error=>{console.error(error);toast('返回战场失败，请刷新重试');});syncMusic();$('#lobby').classList.remove('hidden');$('#game-hud').classList.add('hidden');document.body.classList.remove('playing');$$('.nav-link').forEach(el=>el.classList.toggle('active',el.dataset.panel==='home'));showLobbyPage('home');$('.mode-primary').focus();}

function updateHUD(s){if(!running)return;
  const avatarId=game?.hero?.modelId??prefs.character,avatarAppearance=s.characterAppearance?.appearance||'original';$('#player-name').textContent=networkLobby?.session?game.hero.name:appearanceCharacterName(avatarId,avatarAppearance);$('.player-seal').textContent=appearanceCharacterSeal(avatarId,avatarAppearance);
  $('#musket-reticle').classList.toggle('hidden',!s.musketAim);
  const pickup=$('#pickup-hint');pickup.classList.toggle('hidden',!s.pickup);if(s.pickup){pickup.disabled=!!s.pickup.full;pickup.textContent=s.pickup.full?s.pickup.name+' · '+(s.pickup.fullReason==='full-weapons'?'双兵器已满，按 '+keyHint('drop')+' 丢弃副兵器':s.pickup.fullReason==='full-rage'?'怒气已满':'气血已满'):'靠近自动拾取 '+s.pickup.name+' · '+(s.pickup.description||('气血 +'+s.pickup.heal));}
  $('#hp-bar').style.width=Math.max(0,Math.min(100,s.hp/s.maxHp*100))+'%';$('#hp-label').textContent=`${Math.ceil(s.hp)} / ${s.maxHp}`;if($('#stamina-bar'))$('#stamina-bar').style.width=Math.max(0,Math.min(100,s.stamina||0))+'%';$('#rage-bar').style.width=Math.max(0,Math.min(100,s.rage))+'%';$('#rage-mode-label').hidden=!s.infiniteRage;
  const rules=currentMode==='network'?networkLobby?.session?.rules:null;if(rules){const title=NETWORK_MODES[rules.mode]+' · '+(rules.mode==='leader'?rules.scoreLimit+'杀获胜':'全灭对方获胜');if($('#hud-map').textContent!==title)$('#hud-map').textContent=title;}
  const time=Math.max(0,Math.ceil(rules?rules.timeLimit-s.time:s.time));$('#timer').textContent=String(Math.floor(time/60)).padStart(2,'0')+':'+String(time%60).padStart(2,'0');$('#kills').textContent=currentMode==='network'?s.kills??0:s.hits??s.kills??0;const counterLabel=$('#battle-counter-label');if(counterLabel)counterLabel.textContent=currentMode==='network'?'击败':'命中';$('#deaths').textContent=s.deaths;
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
function toggleSound(){prefs.muted=!prefs.muted;game?.setMuted(prefs.muted);syncMusic();save();updateSelection();if(modalKind==='settings'||!running&&lobbyPage==='settings')openModal('settings');}
document.addEventListener('click',e=>{
  if(characterSelectionBusy)return;
  const route=e.target.closest('[data-route]');if(route){e.preventDefault();showLobbyPage(route.dataset.route);return;}
  const settingsChoice=e.target.closest('[data-settings-tab]');if(settingsChoice){settingsTab=settingsChoice.dataset.settingsTab;openModal('settings');return;}
  const missionChoice=e.target.closest('[data-select-mission]');if(missionChoice){currentMissionId=missionChoice.dataset.selectMission;openModal('mission');return;}
  const sound=e.target.closest('.sound-toggle');if(sound){toggleSound();return;}
  const guideChoice=e.target.closest('[data-guide-weapon]');if(guideChoice&&(modalKind==='guide'||!running&&lobbyPage==='guide')&&weapons[guideChoice.dataset.guideWeapon]){guideWeapon=guideChoice.dataset.guideWeapon;$$('[data-guide-weapon]').forEach(button=>{const selected=button.dataset.guideWeapon===guideWeapon;button.classList.toggle('selected',selected);button.setAttribute('aria-pressed',String(selected));});$('#guide-move-panel').innerHTML=renderNativeMoveGuide(guideWeapon);return;}
  const map=e.target.closest('[data-map]');if(map&&!running){selectMap(map.dataset.map);return;}
  const spearStyle=e.target.closest('[data-spear-style]');if(spearStyle&&!running&&['original','phoenix'].includes(spearStyle.dataset.spearStyle)){prefs.spearStyle=spearStyle.dataset.spearStyle;prefs.weapon='spear';game?.setSpearStyle(prefs.spearStyle);selectMenuWeapon('spear');return;}
  const swordStyle=e.target.closest('[data-sword-style]');if(swordStyle&&!running&&Object.hasOwn(swordStyleNames,swordStyle.dataset.swordStyle)){prefs.swordStyle=swordStyle.dataset.swordStyle;prefs.weapon='sword';game?.setSwordStyle(prefs.swordStyle);selectMenuWeapon('sword');return;}
  const weapon=e.target.closest('[data-weapon]');if(weapon){selectMenuWeapon(weapon.dataset.weapon);if(modal.open&&modalKind==='weapons')openModal('weapons');return;}
  const character=e.target.closest('[data-pick-character], [data-pick-appearance]');if(character){const appearance=character.dataset.pickAppearance||'original',id=character.dataset.pickCharacter===undefined?0:Number(character.dataset.pickCharacter);selectCharacter(id,appearance);return;}
  const nav=e.target.closest('[data-panel]');if(nav){if(nav.dataset.panel==='home'){if(modal.open)closeModal();}else openModal(nav.dataset.panel);return;}
  const opener=e.target.closest('[data-open]');if(opener){openModal(opener.dataset.open);return;}
  const action=e.target.closest('[data-do]');if(action){switch(action.dataset.do){case'play':if(running)closeModal();else showLobbyPage('prep');break;case'restart':startMatch(currentMode);break;case'story':startMatch('story',action.dataset.mission||currentMissionId);break;case'resume':closeModal();break;case'prepare':returnLobby();showLobbyPage('prep');break;case'lobby':returnLobby();break;case'sound':toggleSound();break;}}
});
$('#start-game').addEventListener('click',startMatch);$('#close-modal').addEventListener('click',closeModal);$('#pause-button').addEventListener('click',()=>openModal('pause'));
modal.addEventListener('cancel',e=>{e.preventDefault();closeModal();});modal.addEventListener('click',e=>{if(e.target===modal){const r=modal.getBoundingClientRect();if(e.clientX<r.left||e.clientX>r.right||e.clientY<r.top||e.clientY>r.bottom)closeModal();}});
document.addEventListener('keydown',e=>{if(e.key!=='Escape'||modal.open)return;if(running){e.preventDefault();openModal('pause');}else if(lobbyPage!=='home'){e.preventDefault();showLobbyPage('home');}});
document.addEventListener('input',e=>{if(e.target.id==='map-search'){const query=e.target.value.trim().toLowerCase();$$('.original-map-option').forEach(button=>button.hidden=!button.textContent.toLowerCase().includes(query));}});
document.addEventListener('visibilitychange',()=>{if(document.hidden&&running&&!paused)openModal('pause');syncMusic();});
window.addEventListener('blur',()=>{if(running&&!paused)openModal('pause');});
document.addEventListener('change',e=>{if(e.target.id==='show-fps'){prefs.showFps=e.target.checked;game?.frameOverlay?.setVisible(prefs.showFps);save();return;}if(e.target.id==='infinite-rage'){prefs.infiniteRage=e.target.checked;game?.setInfiniteRage(currentMode==='training'&&prefs.infiniteRage);save();updateSelection();return;}if(e.target.id==='spear-style'){if(!['original','phoenix'].includes(e.target.value))return;prefs.spearStyle=e.target.value;game?.setSpearStyle(prefs.spearStyle);save();updateSelection();refreshWeaponPreview();return;}if(e.target.id==='sword-style'){if(!Object.hasOwn(swordStyleNames,e.target.value))return;prefs.swordStyle=e.target.value;game?.setSwordStyle(prefs.swordStyle);save();updateSelection();refreshWeaponPreview();return;}if(e.target.id==='quality'){prefs.quality=e.target.value;game?.setQuality(prefs.quality);save();}if(e.target.id==='character-appearance'){selectCharacter(0,e.target.value);return;}if(e.target.id==='difficulty'){prefs.difficulty=e.target.value;save();updateSelection();}});
$('#appearance-toggle').addEventListener('click',()=>{const appearances=Object.keys(NATIVE_APPEARANCES).filter(id=>readyAppearances.has(id));selectCharacter(0,appearances[(appearances.indexOf(prefs.characterAppearance)+1)%appearances.length]);});

$('#difficulty-toggle').addEventListener('click',()=>{prefs.difficulty=prefs.difficulty==='normal'?'hard':'normal';save();updateSelection();toast(prefs.difficulty==='hard'?'已切换：江湖高手':'已切换：江湖新手');});
$('#fullscreen').addEventListener('click',async()=>{try{if(document.fullscreenElement)await document.exitFullscreen();else if(document.documentElement.requestFullscreen)await document.documentElement.requestFullscreen();else toast('当前浏览器不支持全屏，可使用浏览器全屏模式');}catch{toast('当前浏览器暂不允许全屏');}});
$('#pickup-hint').addEventListener('click',()=>{game?.action('pickup');$('#world').focus();});
$$('[data-action]').filter(button=>button.id!=='pickup-hint').forEach(button=>{button.addEventListener('pointerdown',e=>{e.preventDefault();if(!running||paused)return;button.setPointerCapture(e.pointerId);game.action(button.dataset.action,true);});for(const type of ['pointerup','pointercancel','lostpointercapture'])button.addEventListener(type,e=>{e.preventDefault();game?.action(button.dataset.action,false);});});
networkLobby=new NetworkLobby({getGame:()=>game,getSelection:()=>battleCharacterSelection(prefs),onStart:(isCurrent,selection)=>startMatch('network',undefined,isCurrent,selection),onNotice:text=>toast(text),onResult:()=>openModal('network'),onStop:text=>{returnLobby();toast(text);}});
updateSelection();
try{
  const {MeteorGame}=await import('./engine.js');game=new MeteorGame($('#world'),{onUpdate:updateHUD,onEvent:handleEvent,onEnd:handleEnd});game.menuIdle=true;menuSnapshots=new MenuSnapshots(game);game.setKeyBindings(keyBindings);window.__game=game;game.frameOverlay.setVisible(prefs.showFps);await game.ready;game.setSwordStyle(prefs.swordStyle);game.setSpearStyle(prefs.spearStyle);game.setInfiniteRage(prefs.infiniteRage);game.setMuted(prefs.muted);game.setQuality(prefs.quality);await game.setWeapon(prefs.weapon);await game.menu(prefs.map, battleCharacterSelection(prefs));if (Object.hasOwn(NATIVE_APPEARANCES, linkedAppearance)) save();refreshMapPreview();refreshWeaponPreview();

  $('#load-status').textContent='江湖已就绪';$('#load-screen').style.opacity=0;setTimeout(()=>$('#load-screen').classList.add('hidden'),650);
}catch(error){console.error(error);$('#load-screen').classList.add('hidden');const el=document.createElement('div');el.className='fatal-error';const text=document.createElement('p');text.textContent='江湖画卷未能展开。请使用支持 WebGL 的新版浏览器，并通过本地服务器打开。';const btn=document.createElement('button');btn.textContent='重新加载';btn.addEventListener('click',()=>location.reload());el.append(text,btn);document.body.append(el);}

window.addEventListener('pagehide',()=>menuSnapshots?.clear());
window.addEventListener('pageshow',event=>{if(event.persisted&&!running){refreshMapPreview();refreshWeaponPreview();}});
