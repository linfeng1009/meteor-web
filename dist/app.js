import { NATIVE_CHARACTERS } from './native-character.js';
const $ = s => document.querySelector(s);
const $$ = s => [...document.querySelectorAll(s)];
const icon = name => `<svg aria-hidden="true"><use href="#i-${name}"/></svg>`;
const maps={sifang:{name:'四方阵',english:'THE FOUR SQUARES',poem:'方寸之间，自有天地。'},cave:{name:'钟乳洞',english:'LIMESTONE CAVERN',poem:'暗流无声，剑影初现。'},forge:{name:'炼铁狱',english:'THE IRON FORGE',poem:'烈火淬刃，百炼成锋。'}};
const weapons={dart:{name:'飞镖',glyph:'镖',motto:'七星',desc:'原版七星飞镖。按 J 投掷，按 Q 锁定目标；墙壁与场景物件会阻挡飞镖。'},dagger:{name:'匕首',glyph:'匕',motto:'蛇吻',desc:'原版蛇吻匕首，轻巧迅疾。钟乳洞任务中的起始兵器。'},sword:{name:'长剑',glyph:'剑',motto:'剑气纵横',desc:'轻灵迅捷，攻守兼备。三式连剑，进退自如。',power:65,speed:85,range:65},blade:{name:'大刀',glyph:'刀',motto:'一刀破势',desc:'势大力沉，以力破巧。斩击伤害高，出招需留余地。',power:95,speed:45,range:70},spear:{name:'长枪',glyph:'枪',motto:'一点寒芒',desc:'一寸长，一寸强。保持身位，以长兵制敌。',power:70,speed:60,range:98}};
let prefs={weapon:'sword',map:'sifang',character:0,difficulty:'normal',muted:true,quality:matchMedia('(pointer:coarse)').matches?'low':'high',best:0};
try{const p=JSON.parse(localStorage.getItem('meteor-web-original-v2')||'{}');for(const k of ['weapon','map','character','difficulty','muted','quality','best'])if(p[k]!==undefined)prefs[k]=p[k];}catch{}
if(!maps[prefs.map]){if(/^sn\d{2}$/.test(prefs.map))maps[prefs.map]={name:prefs.map.toUpperCase(),english:'ORIGINAL MAP',poem:'原版战场'};else prefs.map='sifang';}if(!weapons[prefs.weapon])prefs.weapon='sword';if(!['normal','hard'].includes(prefs.difficulty))prefs.difficulty='normal';if(!['low','high'].includes(prefs.quality))prefs.quality='high';
if(!Number.isInteger(prefs.character)||!NATIVE_CHARACTERS[prefs.character])prefs.character=0;
const save=()=>{try{localStorage.setItem('meteor-web-original-v2',JSON.stringify(prefs));}catch{}};
let currentMode='training';
let dialogueTimer=null,dialogueQueue=[];
let loadingMatch=false;
let game,running=false,paused=false,ended=false,modalKind='',toastTimer,announcementTimer,hitTimer,lastCombo=0,lastHp=100;
let nativeCombat=null;
let originalManifest=null;
fetch('./assets/original/manifest.json').then(r=>{if(!r.ok)throw new Error('原版资源清单读取失败');return r.json();}).then(data=>{originalManifest=data;for(const map of data.maps||[])maps[map.id]={name:map.name||map.id.toUpperCase(),english:'ORIGINAL MAP · '+map.id.toUpperCase(),poem:'故地重游，原样重逢。',available:map.available!==false};updateSelection();}).catch(error=>console.warn(error));
import('./native-combat.js').then(m=>m.loadNativeCombat()).then(data=>{nativeCombat=data;}).catch(error=>console.warn('原版招式表暂未加载',error));
const music=new Audio();music.loop=true;music.volume=.18;music.preload='none';let musicTrack='';
function syncMusic(){const mapId=({sifang:'sn06',cave:'sn01',forge:'sn10'}[prefs.map]||prefs.map);const track=running?(mapId==='sn01'?'s1.mp3':mapId==='sn10'?'s10.mp3':'s6.mp3'):'menu.mp3';if(musicTrack!==track){musicTrack=track;music.src='./assets/original/sounds/music/'+track;}if(prefs.muted||document.hidden)music.pause();else music.play().catch(()=>{});}
let priorFocus=null;
const modal=$('#modal');
const toast=text=>{clearTimeout(toastTimer);$('#toast').textContent=text;$('#toast').classList.add('show');toastTimer=setTimeout(()=>$('#toast').classList.remove('show'),2800);};
const announce=(text,ms=2300)=>{clearTimeout(announcementTimer);$('#game-announcement').textContent=text;$('#game-announcement').style.opacity=1;announcementTimer=setTimeout(()=>$('#game-announcement').style.opacity=0,ms);};
function clearDialogue(){clearTimeout(dialogueTimer);dialogueTimer=null;dialogueQueue=[];$('#mission-dialogue').classList.add('hidden');}
function clearCombatFeedback(){clearTimeout(hitTimer);clearTimeout(announcementTimer);$('#hit-feedback').textContent='';$('#hit-feedback').style.opacity=0;$('#game-announcement').textContent='';$('#game-announcement').style.opacity=0;$('#combo-feedback').textContent='';$('#game-hud').style.boxShadow='';$('#enemy-status').classList.add('hidden');$('#pickup-hint').classList.add('hidden');}
function nextDialogue(){
  if(!running){clearDialogue();return;}
  if(paused){dialogueTimer=setTimeout(nextDialogue,250);return;}
  const line=dialogueQueue.shift();if(!line){dialogueTimer=null;$('#mission-dialogue').classList.add('hidden');return;}
  $('#dialogue-speaker').textContent=line.speaker||'';$('#dialogue-text').textContent=line.text||'';$('#mission-dialogue').classList.remove('hidden');
  dialogueTimer=setTimeout(nextDialogue,Math.max(2000,Math.min(10000,(Number(line.duration)||4)*1000)));
}
function showDialogue(line){dialogueQueue.push(line);if(!dialogueTimer)nextDialogue();}
function matchLoading(active){loadingMatch=active;$('#load-screen').classList.toggle('hidden',!active);$('#load-screen').style.opacity=active?'1':'0';$('#start-game').disabled=active;}
function updateSelection(){
  $$('.arena-card').forEach(el=>{const selected=el.dataset.map===prefs.map;el.classList.toggle('selected',selected);el.setAttribute('aria-pressed',String(selected));});
  $$('[data-weapon]').forEach(el=>{const selected=el.dataset.weapon===prefs.weapon;el.classList.toggle('selected',selected);el.setAttribute('aria-pressed',String(selected));});
  $('#difficulty-label').textContent=prefs.difficulty==='hard'?'江湖高手':'江湖新手';
  $('#scene-name').textContent=maps[prefs.map].name;$('#scene-english').textContent=maps[prefs.map].english;$('#scene-poem').textContent=maps[prefs.map].poem;
  $$('.sound-toggle').forEach(el=>{el.innerHTML=icon(prefs.muted?'muted':'volume');el.setAttribute('aria-label',prefs.muted?'开启音效':'关闭音效');el.title=prefs.muted?'开启音效':'关闭音效';});
  $('#hud-weapon').textContent=weapons[prefs.weapon].name+' · '+weapons[prefs.weapon].motto;
  $('#character-label').textContent=NATIVE_CHARACTERS[prefs.character].name;
  $('#player-name').textContent=NATIVE_CHARACTERS[prefs.character].name;
  $('.player-seal').textContent=NATIVE_CHARACTERS[prefs.character].name.slice(0,1);
}
const header=(en,title,desc='')=>`<div class="modal-kicker">${en}</div><h2 class="modal-title">${title}</h2>${desc?`<p class="modal-desc">${desc}</p>`:''}`;
function guideHTML(){return header('THE WAY OF THE WARRIOR','武学入门','以步法寻破绽，以招式见高下。近身后连续出招，观察对手的出招与攻势。')+`<div class="controls-grid">${[['W A S D','移动 / 方向键亦可'],['拖动鼠标','转动视角'],['J / 鼠标左键','普通攻击 · 原版连招'],['Space / K（按住）','防御'],['C','蹲下'],['鼠标右键 / L','跳跃'],['Q','锁定并跟随镜头 / 解除'],['E','切换兵器'],['F','拾取附近肉包（单机）'],['1 / 2 / 3 / 4 / 5','剑 / 刀 / 枪 / 匕首 / 飞镖（演武）'],['Esc','暂停 / 返回对战']].map(([k,v])=>`<div class="control-row"><span>${v}</span><kbd>${k}</kbd></div>`).join('')}</div><p class="modal-note">演武场读取原版人物与招式帧，支持原版基本连击、护架和跳跃。手机可使用屏幕下方的方向键与招式按钮。</p><div class="modal-actions"><button class="primary-button" data-do="${running?'resume':'play'}"><span>${running?'重返对决':'执剑入江湖'}</span>${icon('arrow')}</button></div>`;}
function weaponsHTML(){const w=weapons[prefs.weapon];const moves=nativeCombat?.moves?.[prefs.weapon]||[];return header('THE ARMORY','兵器谱','兵无常势，水无常形。选一柄趁手兵器，再入江湖。')+`<div class="weapon-options">${Object.entries(weapons).map(([key,v])=>`<button class="weapon-option ${key===prefs.weapon?'selected':''}" data-weapon="${key}" aria-pressed="${key===prefs.weapon}"><span class="weapon-glyph">${v.glyph}</span><strong>${v.name}</strong><small>${v.motto}<br>${key==='dart'?'原版 · 七星':key==='dagger'?'原版 · 蛇吻':key==='sword'?'原版 · 碧血剑':key==='blade'?'原版 · 斩铁刀':'原版 · 战戟'}</small></button>`).join('')}</div><p class="modal-desc" id="weapon-description">${w.desc}</p>${moves.length?`<div class="native-moves">${moves.map(move=>`<div><strong>${move.name||'第'+move.id+'式'}</strong><span>${move.frameCount} 帧 · ${move.duration.toFixed(2)} 秒</span></div>`).join('')}</div>`:''}<p class="modal-note">当前随身兵器：${w.name}。演武中按 1–5 切换，单机任务按 E 切换原随身兵器。按 J 连击或投掷。</p><div class="modal-actions"><button class="primary-button" data-do="play"><span>携兵入江湖</span>${icon('arrow')}</button></div>`;}

function resourcesHTML(){return header('THE METEOR ARCHIVE','流星典藏','优先读取本地客户端的原始素材，流星资源网提供格式资料与缺失资源补充。')+`<div class="resource-list"><a class="resource-link" href="./assets/original/manifest.json" target="_blank" rel="noopener noreferrer"><span>本</span><div><strong>本地客户端原素材</strong><small>20 位人物 · 22 份地图 · 原始招式与配乐</small></div><span>↗</span></a><a class="resource-link" href="https://www.lxres.com/" target="_blank" rel="noopener noreferrer"><span>源</span><div><strong>流星资源网</strong><small>原版客户端 · 单机任务 · 人物兵器 · 地图资源</small></div><span>↗</span></a><a class="resource-link" href="https://www.lxres.com/LiuXingBiJi/1566.html" target="_blank" rel="noopener noreferrer"><span>图</span><div><strong>地图 GMC 结构笔记</strong><small>原生地图格式的 Web 解析依据</small></div><span>↗</span></a><a class="resource-link" href="./assets/SOURCES.md" target="_blank" rel="noopener noreferrer"><span>记</span><div><strong>本项目素材来源清单</strong><small>已使用的地图、贴图与转换记录</small></div><span>↗</span></a></div><p class="modal-note">这是《流星蝴蝶剑.net》的非官方 Web 实验重构。读取本地原版模型、骨骼、动画与招式表，在浏览器运行；剧情脚本与联网协议仍在逐项移植。原游戏与社区素材的权利归各自权利人所有。</p>`;}
function settingsHTML(){return header('MAKE IT YOUR JIANGHU','江湖设置','设置自动保存在当前浏览器。')+`<div class="settings-row"><label>刀剑音效<small>挥刃、命中与交锋的声音</small></label><button class="toggle" data-do="sound" aria-label="刀剑音效" aria-pressed="${!prefs.muted}"></button></div><div class="settings-row"><label for="quality">画面品质<small>低配模式降低渲染像素密度</small></label><select id="quality" class="setting-select"><option value="high" ${prefs.quality==='high'?'selected':''}>精致画面</option><option value="low" ${prefs.quality==='low'?'selected':''}>流畅优先</option></select></div><div class="settings-row"><label for="difficulty">对手难度<small>演武对手的进攻节奏；单机任务读取原关卡配置</small></label><select id="difficulty" class="setting-select"><option value="normal" ${prefs.difficulty==='normal'?'selected':''}>江湖新手</option><option value="hard" ${prefs.difficulty==='hard'?'selected':''}>江湖高手</option></select></div><p class="modal-note">${running?'画质与声音立即生效，难度设置于下一局生效。':'建议桌面浏览器配合键盘与鼠标游玩。手机支持触屏按键，横屏视野更宽。'}${prefs.best?`<br>个人最佳：单局击败 ${Number(prefs.best)||0} 名对手。`:''}</p>`;}
function pauseHTML(){return `<div class="pause-title">${header('A MOMENT OF STILLNESS','且歇片刻','刀剑暂收，江湖还在。')}</div><div class="pause-actions"><button class="primary-button" data-do="resume"><span>继续对决</span>${icon('arrow')}</button><button class="secondary-button" data-open="guide">查看招式</button><button class="secondary-button" data-do="restart">重新论剑</button><button class="secondary-button" data-do="lobby">返回江湖首页</button></div>`;}
function missionHTML(){return header('THE ORIGINAL STORY','单机任务','读取原版关卡脚本，重走孟星魂的第一段江湖。')+`<button class="mission-card" data-do="story"><small>第一关 · SN01</small><strong>钟乳洞</strong><p>原版孟星魂 · 蛇吻匕首开局<br>原关卡守卫、对话与巡逻路线</p><span>进入原版任务 →</span></button><p class="modal-note">其余原版战场可从「更多原版战场」进入演武。剧情流程逐关验证后开放。</p>`;}
function charactersHTML(){return header('THE ORIGINAL CAST','江湖人物','二十位故人，原版造型与招式动画。')+`<div class="character-grid">${NATIVE_CHARACTERS.map(c=>`<button class="character-option ${c.id===prefs.character?'selected':''}" data-character="${c.id}" aria-pressed="${c.id===prefs.character}"><img src="${c.portrait}" alt="${c.name}" loading="lazy"><span>${c.name}</span></button>`).join('')}</div><p class="modal-note">已选：${NATIVE_CHARACTERS[prefs.character].name}。使用原版人物的模型、纹理、骨架与动作。</p>`;}
function mapsHTML(){return header('THE ORIGINAL BATTLEGROUNDS','原版战场','从本地客户端读取的地图。选一处故地，再走一回。')+`<div class="original-map-grid">${(originalManifest?.maps||[]).map(map=>`<button class="original-map-option ${map.id===({sifang:'sn06',cave:'sn01',forge:'sn10'}[prefs.map]||prefs.map)?'selected':''}" data-map="${map.id}" ${map.available===false?'disabled':''}><small>${map.id.toUpperCase()}</small><strong>${map.name||'未命名地图'}</strong><span>${map.available===false?'原文件数据异常':map.name?'原版场景':'名称待核实'}</span></button>`).join('')}</div>`;}
async function selectMap(id){prefs.map=id;save();updateSelection();if(modal.open)modal.close();$('#start-game').disabled=true;$('#scene-load-status').textContent='正在读取原版战场…';try{await game?.menu(id);}catch(error){console.error(error);toast('这张原版地图暂未能载入');}finally{$('#start-game').disabled=false;$('#scene-load-status').textContent='';}}
function openModal(kind){
  if(!modal.open)priorFocus=document.activeElement;
  modalKind=kind;
  if(running&&!paused){paused=true;game?.pause(true);}
  const renderers={guide:guideHTML,weapons:weaponsHTML,characters:charactersHTML,mission:missionHTML,maps:mapsHTML,resources:resourcesHTML,settings:settingsHTML,pause:pauseHTML};
  $('#modal-content').innerHTML=(renderers[kind]||guideHTML)();
  if(!modal.open)modal.showModal();
}
function closeModal(){if(modal.open)modal.close();if(ended){returnLobby();return;}if(running&&paused){paused=false;game?.pause(false);}modalKind='';priorFocus?.focus?.();}
async function startMatch(mode='training'){
  if(loadingMatch)return;
  if(typeof mode!=='string')mode='training';currentMode=mode;if(mode==='story'){prefs.map='cave';prefs.character=0;updateSelection();}

  if(!game)return;$('#start-game').disabled=true;
  if(modal.open)modal.close();ended=false;paused=false;running=true;lastCombo=0;lastHp=currentMode==='story'?1500:1000;clearDialogue();clearCombatFeedback();matchLoading(true);$('#load-status').textContent=currentMode==='story'?'正在载入钟乳洞与原版任务脚本…':'正在载入原版演武场…';
  $('#lobby').classList.add('hidden');$('#game-hud').classList.remove('hidden');document.body.classList.add('playing');
  $('#hud-map').textContent=maps[prefs.map].name+(currentMode==='story'?' · 单机任务':' · 演武');$('#battle-hint-text').textContent='原版招式演武 · 按 J 或鼠标左键出招';$('#combo-feedback').textContent='';
  try{await game.start({map:prefs.map,weapon:prefs.weapon,difficulty:prefs.difficulty,character:prefs.character,mode:currentMode});game.setMuted(prefs.muted);game.setQuality(prefs.quality);syncMusic();announce(currentMode==='story'?'钟乳洞 · 第一关':'演武 · 开始',2200);$('#world').setAttribute('tabindex','-1');$('#world').focus();}
  catch(e){console.error(e);returnLobby();toast('战场加载失败，请刷新重试');}
  matchLoading(false);
}
function returnLobby(){if(modal.open)modal.close();running=false;paused=false;ended=false;clearDialogue();clearCombatFeedback();game?.pause(false);game?.menu(prefs.map).then(()=>{if(!running)game.setWeapon(prefs.weapon);}).catch(error=>{console.error(error);toast('返回战场失败，请刷新重试');});syncMusic();$('#lobby').classList.remove('hidden');$('#game-hud').classList.add('hidden');document.body.classList.remove('playing');$$('.nav-link').forEach(el=>el.classList.toggle('active',el.dataset.panel==='home'));$('#start-game').focus();}
function updateHUD(s){if(!running)return;
  const pickup=$('#pickup-hint');pickup.classList.toggle('hidden',!s.pickup);if(s.pickup){pickup.disabled=!!s.pickup.full;pickup.textContent=s.pickup.full?s.pickup.name+' · 气血已满':'拾取'+s.pickup.name+' · 气血 +'+s.pickup.heal+'（F）';}
  $('#hp-bar').style.width=Math.max(0,s.hp/s.maxHp*100)+'%';$('#hp-label').textContent=`${Math.ceil(s.hp)} / ${s.maxHp}`;if($('#stamina-bar'))$('#stamina-bar').style.width=Math.max(0,Math.min(100,s.stamina||0))+'%';$('#rage-bar').style.width=Math.max(0,Math.min(100,s.rage))+'%';
  const time=Math.max(0,Math.ceil(s.time));$('#timer').textContent=String(Math.floor(time/60)).padStart(2,'0')+':'+String(time%60).padStart(2,'0');$('#kills').textContent=s.hits??s.kills??0;$('#deaths').textContent=s.deaths;
  if(s.weaponName){$('#hud-weapon').textContent=s.weaponName+(weapons[s.weapon]?' · '+weapons[s.weapon].name:s.weapon==='dart'?' · 飞镖':'');}
  else if(s.weapon&&weapons[s.weapon]){$('#hud-weapon').textContent=weapons[s.weapon].name+' · '+weapons[s.weapon].motto;}
  $('#enemy-status').classList.toggle('hidden',!s.enemy);if(s.enemy){$('#enemy-name').textContent=(s.locked?'◇ ':'')+s.enemy.name;$('#enemy-bar').style.width=Math.max(0,s.enemy.hp/s.enemy.maxHp*100)+'%';$('#enemy-hp').textContent=Math.ceil(s.enemy.hp)+' / '+s.enemy.maxHp+(Number.isFinite(s.enemy.distance)?' · 距离 '+Math.round(s.enemy.distance):'');}
  $('#mission-goal').classList.toggle('hidden',currentMode!=='story');if(currentMode==='story')$('#mission-goal').textContent='击败守卫 · 剩余 '+(s.enemies?.length??0)+' 人';
  if(s.combo!==lastCombo){lastCombo=s.combo;$('#combo-feedback').textContent=s.combo>1?`${s.combo} 连击`:'';}
  $('#battle-hint-text').textContent=s.hp<=0?(currentMode==='story'?'任务结束':'胜败乃兵家常事 · 正在重返战场'):s.rage>=100?'怒气已满':s.locked?'镜头跟随锁定目标 · Q 解除 · 拖动鼠标转动视角':(s.weapon==='dart'?'七星飞镖 · J 投掷 · Q 锁定 · E 换兵器':'原版招式演武 · 按 J 或鼠标左键出招');
  if(s.hp<lastHp){$('#game-hud').style.boxShadow='inset 0 0 90px #a2222266';setTimeout(()=>$('#game-hud').style.boxShadow='',180);}lastHp=s.hp;
  drawMinimap(s);
}
function drawMinimap(s){const c=$('#minimap'),ctx=c.getContext('2d'),w=c.width;ctx.clearRect(0,0,w,w);ctx.save();ctx.translate(w/2,w/2);ctx.strokeStyle='#a6916050';ctx.lineWidth=1;ctx.strokeRect(-49,-49,98,98);ctx.beginPath();ctx.moveTo(-65,0);ctx.lineTo(65,0);ctx.moveTo(0,-65);ctx.lineTo(0,65);ctx.stroke();ctx.font='8px sans-serif';ctx.fillStyle='#d9bf8d';ctx.textAlign='center';ctx.fillText('北',0,-61);const bounds=s.mapBounds;const scale=bounds?110/Math.max(bounds.maxX-bounds.minX,bounds.maxZ-bounds.minZ,1):2.2;const cx=bounds?(bounds.minX+bounds.maxX)/2:0,cz=bounds?(bounds.minZ+bounds.maxZ)/2:0;for(const e of s.enemies||[]){ctx.fillStyle='#ce6650';ctx.beginPath();ctx.arc(Math.max(-57,Math.min(57,(e.x-cx)*scale)),Math.max(-57,Math.min(57,(e.z-cz)*scale)),3,0,Math.PI*2);ctx.fill();}if(s.position){ctx.fillStyle='#e4d8a9';const x=Math.max(-57,Math.min(57,(s.position.x-cx)*scale)),z=Math.max(-57,Math.min(57,(s.position.z-cz)*scale));ctx.beginPath();ctx.moveTo(x,z-5);ctx.lineTo(x-4,z+4);ctx.lineTo(x+4,z+4);ctx.closePath();ctx.fill();}ctx.restore();}
function handleEvent(e){if(e.type==='load'){$('#load-status').textContent=e.text;return;}if(!running)return;if(e.type==='dialogue'){showDialogue(e);return;}if(['mission-diagnostic','mission-compatibility'].includes(e.type)){console.warn(e.text,e);return;}if(e.type==='hit'&&e.amount){clearTimeout(hitTimer);$('#hit-feedback').textContent=Math.round(e.amount);$('#hit-feedback').style.opacity=1;hitTimer=setTimeout(()=>$('#hit-feedback').style.opacity=0,600);}else if(e.text)announce(e.text,e.type==='kill'?1600:2000);}
function handleEnd(r){clearDialogue();clearCombatFeedback();running=false;ended=true;paused=true;game?.pause(true);prefs.best=Math.max(Number(prefs.best)||0,r.kills||0);save();modalKind='result';$('#modal-content').innerHTML=`<span class="result-seal">${r.win?'此战 · 胜':'再战 · 江湖'}</span>${header(currentMode==='story'?'THE ORIGINAL STORY':'THE DUEL IS OVER',currentMode==='story'?(r.win?'钟乳洞 · 任务完成':'钟乳洞 · 任务失败'):(r.win?'一剑定江湖':'胜负，留待来日'),currentMode==='story'?(r.win?'三名守卫已击败。':'孟星魂倒下了。重整兵器，再试一次。'):(r.win?'剑锋所指，皆为坦途。':'整装，再出发。'))}<div class="results-grid"><div><strong>${Number(r.kills)||0}</strong><span>击败对手</span></div><div><strong>${Number(r.deaths)||0}</strong><span>倒下次数</span></div><div><strong>${Math.round(Number(r.damage)||0)}</strong><span>造成伤害</span></div></div><div class="modal-actions"><button class="primary-button" data-do="restart"><span>再战一场</span>${icon('arrow')}</button><button class="secondary-button" data-do="lobby">返回江湖</button></div>`;if(!modal.open)modal.showModal();}
function toggleSound(){prefs.muted=!prefs.muted;game?.setMuted(prefs.muted);syncMusic();save();updateSelection();if(modalKind==='settings')openModal('settings');}
document.addEventListener('click',e=>{
  const sound=e.target.closest('.sound-toggle');if(sound){toggleSound();return;}
  const map=e.target.closest('[data-map]');if(map&&!running){selectMap(map.dataset.map);return;}
  const weapon=e.target.closest('[data-weapon]');if(weapon){prefs.weapon=weapon.dataset.weapon;save();game?.setWeapon(prefs.weapon);updateSelection();if(modal.open&&modalKind==='weapons')openModal('weapons');return;}
  const character=e.target.closest('[data-character]');if(character){prefs.character=Number(character.dataset.character);save();updateSelection();game?.setCharacter?.(prefs.character);openModal('characters');return;}
  const nav=e.target.closest('[data-panel]');if(nav){if(nav.dataset.panel==='home'){if(modal.open)closeModal();}else openModal(nav.dataset.panel);return;}
  const opener=e.target.closest('[data-open]');if(opener){openModal(opener.dataset.open);return;}
  const action=e.target.closest('[data-do]');if(action){switch(action.dataset.do){case'play':startMatch('training');break;case'restart':startMatch(currentMode);break;case'story':startMatch('story');break;case'resume':closeModal();break;case'lobby':returnLobby();break;case'sound':toggleSound();break;}}
});
$('#start-game').addEventListener('click',startMatch);$('#close-modal').addEventListener('click',closeModal);$('#pause-button').addEventListener('click',()=>openModal('pause'));
modal.addEventListener('cancel',e=>{e.preventDefault();closeModal();});modal.addEventListener('click',e=>{if(e.target===modal){const r=modal.getBoundingClientRect();if(e.clientX<r.left||e.clientX>r.right||e.clientY<r.top||e.clientY>r.bottom)closeModal();}});
document.addEventListener('keydown',e=>{if(e.key==='Escape'&&!modal.open&&running){e.preventDefault();openModal('pause');}});
document.addEventListener('visibilitychange',()=>{if(document.hidden&&running&&!paused)openModal('pause');syncMusic();});
window.addEventListener('blur',()=>{if(running&&!paused)openModal('pause');});
document.addEventListener('change',e=>{if(e.target.id==='quality'){prefs.quality=e.target.value;game?.setQuality(prefs.quality);save();}if(e.target.id==='difficulty'){prefs.difficulty=e.target.value;save();updateSelection();}});
$('#difficulty-toggle').addEventListener('click',()=>{prefs.difficulty=prefs.difficulty==='normal'?'hard':'normal';save();updateSelection();toast(prefs.difficulty==='hard'?'已切换：江湖高手':'已切换：江湖新手');});
$('#fullscreen').addEventListener('click',async()=>{try{if(document.fullscreenElement)await document.exitFullscreen();else if(document.documentElement.requestFullscreen)await document.documentElement.requestFullscreen();else toast('当前浏览器不支持全屏，可使用浏览器全屏模式');}catch{toast('当前浏览器暂不允许全屏');}});
$('#pickup-hint').addEventListener('click',()=>{game?.action('pickup');$('#world').focus();});
$$('[data-action]').filter(button=>button.id!=='pickup-hint').forEach(button=>{button.addEventListener('pointerdown',e=>{e.preventDefault();if(!running||paused)return;button.setPointerCapture(e.pointerId);game.action(button.dataset.action,true);});for(const type of ['pointerup','pointercancel','lostpointercapture'])button.addEventListener(type,e=>{e.preventDefault();game?.action(button.dataset.action,false);});});
updateSelection();
try{
  const {MeteorGame}=await import('./engine.js');game=new MeteorGame($('#world'),{onUpdate:updateHUD,onEvent:handleEvent,onEnd:handleEnd});window.__game=game;await game.ready;game.setMuted(prefs.muted);game.setQuality(prefs.quality);game.setWeapon(prefs.weapon);await game.setCharacter?.(prefs.character);await game.menu(prefs.map);
  $('#load-status').textContent='江湖已就绪';$('#load-screen').style.opacity=0;setTimeout(()=>$('#load-screen').classList.add('hidden'),650);
}catch(error){console.error(error);$('#load-screen').classList.add('hidden');const el=document.createElement('div');el.className='fatal-error';const text=document.createElement('p');text.textContent='江湖画卷未能展开。请使用支持 WebGL 的新版浏览器，并通过本地服务器打开。';const btn=document.createElement('button');btn.textContent='重新加载';btn.addEventListener('click',()=>location.reload());el.append(text,btn);document.body.append(el);}
