import {NETWORK_MODES} from './network-rules.js';
import {NetworkClient} from './network-client.js';
import {NetworkGame} from './network-game.js';
export class NetworkLobby{
  constructor({getGame,onStart,onStop,onNotice,onResult=()=>{},createClient=options=>new NetworkClient(options),createSession=(...args)=>NetworkGame.create(...args)}){Object.assign(this,{getGame,onStart,onStop,onNotice,onResult,createClient,createSession});}
  mount(root){this.root=root;this.render();if(!this.client)this.refreshRooms();}
  async refreshRooms(){
    if(this.listLoading||this.client)return;this.listLoading=true;this.listError='';this.render();
    try{const result=await new NetworkClient().api('/api/rooms/list');this.availableRooms=result.rooms;}catch(error){this.listError=error.message;}finally{this.listLoading=false;if(!this.client)this.render();}
  }
  render(){
    const root=this.root;if(!root?.isConnected)return;root.replaceChildren();
    const node=(tag,text,cls,parent=root)=>{const el=document.createElement(tag);if(text!==undefined)el.textContent=text;if(cls)el.className=cls;parent.append(el);return el;};
    const button=(text,fn,parent=root,cls='')=>{const b=node('button',text,'secondary-button '+cls,parent);b.type='button';b.addEventListener('click',async()=>{b.disabled=true;try{await fn();}catch(e){this.onNotice(e.message);}finally{if(b.isConnected)b.disabled=false;}});return b;};
    if(this.error)node('p',this.error).setAttribute('role','alert');
    if(this.connecting&&!this.client?.room){node('p','正在连接房间…','room-status').setAttribute('role','status');button('取消连接',()=>this.leave());return;}
    if(!this.client){
      const draft=this.draft||={name:'江湖来客',mode:'leader',maxPlayers:4,scoreLimit:10,timeLimit:600,code:''};
      const layout=node('div',undefined,'room-browser'),main=node('section',undefined,'room-browser-main',layout),aside=node('section',undefined,'room-create',layout);
      const tools=node('div',undefined,'room-tools',main);node('h3','局域网房间','',tools);button(this.listLoading?'正在读取…':'刷新列表',()=>this.refreshRooms(),tools).disabled=!!this.listLoading;
      node('p','同一服务 · 2～4 人 · 四方阵','',main);
      const filters=node('div',undefined,'room-filters',main);for(const [value,label] of [['all','全部'],...Object.entries(NETWORK_MODES)]){const choice=button(label,()=>{this.roomFilter=value;this.render();},filters);choice.setAttribute('aria-pressed',String((this.roomFilter||'all')===value));}
      if(this.listError)node('p',this.listError,'',main).setAttribute('role','alert');
      else if(!this.listLoading&&!(this.availableRooms||[]).length)node('p','尚无房间。创建一间，邀请朋友加入；请确认大家使用同一个局域网游戏地址。','',main);
      const visibleRooms=(this.availableRooms||[]).filter(room=>!this.roomFilter||this.roomFilter==='all'||room.mode===this.roomFilter);if(!this.listLoading&&(this.availableRooms||[]).length&&!visibleRooms.length)node('p','当前模式没有房间，可切换模式或创建房间。','',main);
      for(const room of visibleRooms){const row=node('div',undefined,'room-row',main);node('p',`${room.hostName}的房间\n${room.code} · ${NETWORK_MODES[room.mode]||'盟主'} · ${room.players}/${room.maxPlayers}人 · ${room.phase==='waiting'?'等待加入':room.phase==='finished'?'已结束':'对战中'}`,'',row);button(room.phase!=='waiting'?'不可加入':room.players>=room.maxPlayers?'已满':'加入 '+room.code,()=>this.connect('join',{name:draft.name,code:room.code}),row).disabled=room.phase!=='waiting'||room.players>=room.maxPlayers;}
      node('h3','召集同道','',aside);
      const input=(label,key,max)=>{const field=node('input',undefined,'setting-select',aside);field.value=draft[key];field.maxLength=max;field.setAttribute('aria-label',label);field.placeholder=label;field.addEventListener('input',()=>draft[key]=field.value);return field;};
      input('联机玩家名字','name',16);
      const select=(label,key,options)=>{const box=node('label',label,'',aside),field=node('select',undefined,'setting-select',box);field.setAttribute('aria-label',label);for(const [value,text] of options){const option=node('option',text,'',field);option.value=value;}field.value=draft[key];field.addEventListener('change',()=>{draft[key]=field.value;if(key==='mode')this.render();});return field;};
      select('模式','mode',Object.entries(NETWORK_MODES));select('人数上限','maxPlayers',[[4,'4人'],[3,'3人'],[2,'2人']]);
      if(draft.mode==='leader')select('盟主击杀上限','scoreLimit',[[10,'10杀'],[5,'5杀'],[20,'20杀']]);
      select('时限','timeLimit',[[600,'10分钟'],[300,'5分钟'],[900,'15分钟']]);
      button('创建房间',()=>this.connect('create',{name:draft.name,mode:draft.mode,maxPlayers:Number(draft.maxPlayers),scoreLimit:Number(draft.scoreLimit),timeLimit:Number(draft.timeLimit)}),aside,'create-primary');
      node('p','已有房间号？','',aside);input('房间号','code',6);button('加入房间',()=>this.connect('join',{name:draft.name,code:draft.code.trim().toUpperCase()}),aside);
      node('p','房主需保持游戏窗口运行。房间号仅用于当前服务。','',aside);return;
    }
    const room=this.client.room,heading=node('div',undefined,'room-heading');node('h3',`房间 ${room.code} · ${NETWORK_MODES[room.mode]||'盟主'} · ${room.players.length}/${room.maxPlayers||4}人`,'',heading);
    button('复制邀请',async()=>{const url=new URL(location.href);url.hash='';url.search='';if(['localhost','127.0.0.1','::1'].includes(url.hostname)){this.onNotice('请复制朋友可访问的局域网地址，并告知房间号 '+room.code);return;}try{await navigator.clipboard.writeText(url.href+' 房间号：'+room.code);this.onNotice('邀请已复制');}catch{this.onNotice('请复制当前游戏地址，房间号：'+room.code);}},heading);
    node('p',room.mode==='deathmatch'?`四方阵 · 红蓝两队 · 队友免伤 · 阵亡后本局不复活 · ${room.timeLimit/60}分钟超时平局`:`四方阵 · 自由混战 · ${room.scoreLimit}杀或${room.timeLimit/60}分钟结算`,'room-status');
    const seats=node('div',undefined,'room-seats');for(const p of room.players){const row=node('div',`${p.name}${p.id===room.hostId?'（房主）':''}${p.id===this.client.playerId?'（你）':''}\n${room.mode==='deathmatch'?(p.team===1?'红队 · ':'蓝队 · '):''}${p.ready?'已准备':'未准备'}${room.phase==='loading'?(p.loaded?' · 载入完成':' · 载入中'):''}`,'room-seat',seats);if(room.mode==='deathmatch')row.dataset.team=p.team;}
    for(let i=room.players.length;i<(room.maxPlayers||4);i++)node('div','等待同道加入','room-seat empty',seats);
    const rules=node('section',undefined,'room-rules');node('h3','本局说明','',rules);node('p','联机固定四方阵、原版人物与长剑。所有人准备后，由房主开局。','',rules);
    if(room.phase==='loading')node('p','正在等待：'+room.players.filter(p=>!p.loaded).map(p=>p.name).join('、')+' 载入战场','room-wait').setAttribute('role','status');
    const actions=node('div',undefined,'room-actions');button('退出房间',()=>this.leave(),actions);
    if(room.phase==='waiting'){
      const self=room.players.find(p=>p.id===this.client.playerId);
      if(room.mode==='deathmatch')button(self.team===1?'切换到蓝队':'切换到红队',()=>this.client.command('team',{team:self.team===1?2:1}),actions);
      button(self.ready?'取消准备':'准备',()=>this.client.command('ready',{ready:!self.ready}),actions,this.client.host?'':'start-primary');
      const waiting=room.players.filter(p=>!p.ready).map(p=>p.name);node('p',room.players.length<2?'至少两位玩家才能开局':waiting.length?'等待准备：'+waiting.join('、'):room.mode==='deathmatch'&&new Set(room.players.map(p=>p.team)).size<2?'请分到红蓝两队':'所有玩家已准备，等待房主开始','room-wait');
      if(this.client.host)button('开始对战',()=>this.client.command('start'),actions,'start-primary').disabled=room.players.length<2||!room.players.every(p=>p.ready)||room.mode==='deathmatch'&&new Set(room.players.map(p=>p.team)).size<2;
    }
    if(room.phase==='finished'){
      const ids=room.result?.winnerIds||[];node('h3',ids.length?(room.mode==='deathmatch'?(room.result.winnerTeam===1?'红队获胜':'蓝队获胜'):(ids.length>1?'并列第一：':'获胜：')+room.players.filter(p=>ids.includes(p.id)).map(p=>p.name).join('、')):'平局');
      for(const score of [...(room.scores||[])].sort((a,b)=>b.kills-a.kills))node('p',`${room.players.find(p=>p.id===score.id)?.name||'已离场玩家'} · ${score.kills}击杀 / ${score.deaths}死亡`);
      if(this.client.host)button('再来一局',()=>this.client.command('rematch'),actions,'start-primary');else node('p','等待房主开启下一局','room-wait');
    }
  }
  async connect(kind,data){
    if(this.connecting||this.client)return;this.error='';this.connecting=true;const generation=this.generation=(this.generation||0)+1;
    const current=()=>this.client===client&&this.generation===generation;
    const stop=message=>{if(current()){this.leave(false);this.onStop(message);}};
    const client=this.createClient({getAngle:()=>this.getGame()?.cameraAngle||0,getPitch:()=>this.getGame()?.localControl?.aimPitch||0,getFrame:()=>current()?this.session?.snapshot():null,
      onRoom:r=>{if(current())this.roomChanged(r,client).catch(error=>stop('联机状态错误：'+error.message));},
      onInput:inputs=>{if(!current())return;if(!this.session?.active)throw Error('战斗未就绪，无法应用操作');this.session.inputs(inputs);},
      onFrame:frame=>{if(current())this.session?.apply(frame);},onError:message=>stop('联机中断：'+message)});
    try{this.client=client;this.render();await client.connect(kind,data);if(current())this.render();}
    catch(e){if(current()){client.closed=true;clearInterval(client.timer);this.client=null;this.error=e.message;throw e;}}
    finally{if(this.generation===generation){this.connecting=false;this.render();}}
  }
  async roomChanged(room,client=this.client){
    if(!client||client!==this.client||client.closed)return;
    this.session?.reconcile?.(room);
    const signature=JSON.stringify(room);if(signature!==this.signature){this.signature=signature;this.render();}
    if(room.phase==='loading'&&!this.session&&!this.loading){
      const task=this.loading={},generation=this.generation;let game;
      const current=()=>generation===this.generation&&this.client===client&&!client.closed;
      const valid=()=>current()&&client.room.round===room.round&&client.room.phase==='loading'&&(!game||this.getGame()===game);
      try{
        await this.onStart(valid);if(!valid()){if(current()&&client.room.phase==='waiting')this.onStop('房间已结束');return;}
        game=this.getGame();const session=await this.createSession(game,client,room,{isCurrent:valid});
        if(!valid()){session?.dispose();if(current()&&client.room.phase==='waiting')this.onStop('房间已结束');return;}
        if(!session)return;this.session=session;await client.command('loaded');
      }
      catch(e){if(current()){this.leave(false);this.onStop('战场载入失败：'+e.message);}}
      finally{if(this.loading===task)this.loading=null;}
    }
    if(room.phase==='playing'&&this.session&&!this.session.active){this.session.play();this.onNotice(`${NETWORK_MODES[room.mode]||'盟主'}开始`);}
    if(room.phase==='finished'&&this.session){this.session.finish?.(room.result);if(this.resultRound!==room.round){this.resultRound=room.round;this.onResult(room);}}
    if(room.phase==='waiting'&&this.session){this.session.dispose();this.session=null;this.onNotice('已回到房间，请准备下一局');this.render();}
  }
  async leave(notify=true){this.generation=(this.generation||0)+1;this.connecting=false;this.error='';this.resultRound=null;const client=this.client;this.client=null;this.session?.dispose();this.session=null;this.signature='';this.render();if(notify)this.onStop('已退出联机房间');try{await client?.leave();}catch{}}
}
