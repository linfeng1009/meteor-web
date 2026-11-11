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
    const note=document.createElement('p');note.className='modal-note';note.textContent='局域网2～4人 · 四方阵。盟主自由混战、无限重生；死斗分红蓝两队，全灭对方获胜。所有玩家准备后由房主开局。房主需保持游戏窗口运行。';root.append(note);
    const button=(text,fn)=>{const b=document.createElement('button');b.type='button';b.className='secondary-button';b.textContent=text;b.addEventListener('click',async()=>{b.disabled=true;try{await fn();}catch(e){this.onNotice(e.message);}finally{b.disabled=false;}});root.append(b);return b;};
    if(this.error){const message=document.createElement('p');message.setAttribute('role','alert');message.textContent=this.error;root.append(message);}
    if(this.connecting&&!this.client?.room){const status=document.createElement('p');status.textContent='正在连接房间…';root.append(status);button('取消连接',()=>this.leave());return;}
    if(!this.client){
      const name=document.createElement('input');name.placeholder='玩家名字';name.maxLength=16;name.setAttribute('aria-label','联机玩家名字');name.value='江湖来客';name.className='setting-select';root.append(name);
      const select=(label,options)=>{const box=document.createElement('label');box.textContent=label+' ';const field=document.createElement('select');field.className='setting-select';field.setAttribute('aria-label',label);for(const [value,text] of options){const option=document.createElement('option');option.value=value;option.textContent=text;field.append(option);}box.append(field);root.append(box);return field;};
      const mode=select('模式',Object.entries(NETWORK_MODES)),capacity=select('人数上限',[[4,'4人'],[3,'3人'],[2,'2人']]),score=select('盟主击杀上限',[[10,'10杀'],[5,'5杀'],[20,'20杀']]),time=select('时限',[[600,'10分钟'],[300,'5分钟'],[900,'15分钟']]);
      mode.addEventListener('change',()=>{score.parentElement.hidden=mode.value==='deathmatch';});
      button('创建房间',()=>this.connect('create',{name:name.value,mode:mode.value,maxPlayers:Number(capacity.value),scoreLimit:Number(score.value),timeLimit:Number(time.value)}));
      const code=document.createElement('input');code.placeholder='六位房间号';code.maxLength=6;code.setAttribute('aria-label','房间号');code.className='setting-select';root.append(code);button('加入房间',()=>this.connect('join',{name:name.value,code:code.value.trim().toUpperCase()}));
      const heading=document.createElement('h3');heading.textContent='局域网房间';root.append(heading);
      button(this.listLoading?'正在读取房间…':'刷新房间列表',()=>this.refreshRooms()).disabled=!!this.listLoading;
      if(this.listError){const error=document.createElement('p');error.setAttribute('role','alert');error.textContent=this.listError;root.append(error);}
      else if(!this.listLoading&&!(this.availableRooms||[]).length){const empty=document.createElement('p');empty.textContent='暂无房间。请确认大家打开同一个局域网游戏地址，或创建房间后刷新列表。';root.append(empty);}
      for(const room of this.availableRooms||[]){const row=document.createElement('p');row.textContent=`${room.hostName} · ${room.code} · ${NETWORK_MODES[room.mode]||'盟主'} · ${room.players}/${room.maxPlayers}人 · ${room.phase==='waiting'?'等待入场':room.phase==='finished'?'已结束':'对战中'}`;root.append(row);button('加入 '+room.code,()=>this.connect('join',{name:name.value,code:room.code})).disabled=room.phase!=='waiting'||room.players>=room.maxPlayers;}
      return;
    }
    const room=this.client.room,title=document.createElement('h3');title.textContent=`房间号：${room.code} · ${NETWORK_MODES[room.mode]||'盟主'} · ${room.players.length}/${room.maxPlayers||4}人`;root.append(title);const rules=document.createElement('p');rules.textContent=room.mode==='deathmatch'?`红蓝两队 · 队友免伤 · 阵亡后本局不复活 · ${room.timeLimit/60}分钟超时平局`:`自由混战 · ${room.scoreLimit}杀或${room.timeLimit/60}分钟结算`;root.append(rules);
    for(const p of room.players){const row=document.createElement('p');row.textContent=`${p.name}${p.id===room.hostId?'（房主）':''}${p.id===this.client.playerId?'（你）':''}${room.mode==='deathmatch'?(p.team===1?' · 红队':' · 蓝队'):''} · ${p.ready?'已准备':'未准备'}${room.phase==='loading'?(p.loaded?' · 载入完成':' · 载入中'):''}`;root.append(row);}
    if(room.phase==='waiting'){
      const self=room.players.find(p=>p.id===this.client.playerId);
      if(room.mode==='deathmatch')button(self.team===1?'切换到蓝队':'切换到红队',()=>this.client.command('team',{team:self.team===1?2:1}));
      button(self.ready?'取消准备':'准备',()=>this.client.command('ready',{ready:!self.ready}));
      if(this.client.host)button('开始对战',()=>this.client.command('start')).disabled=room.players.length<2||!room.players.every(p=>p.ready)||room.mode==='deathmatch'&&new Set(room.players.map(p=>p.team)).size<2;
    }
    if(room.phase==='finished'){
      const result=document.createElement('h3'),ids=room.result?.winnerIds||[];result.textContent=ids.length?(room.mode==='deathmatch'?(room.result.winnerTeam===1?'红队获胜':'蓝队获胜'):(ids.length>1?'并列第一：':'获胜：')+room.players.filter(p=>ids.includes(p.id)).map(p=>p.name).join('、')):'平局';root.append(result);
      for(const score of [...(room.scores||[])].sort((a,b)=>b.kills-a.kills)){const row=document.createElement('p');row.textContent=`${room.players.find(p=>p.id===score.id)?.name||'已离场玩家'} · ${score.kills}击杀 / ${score.deaths}死亡`;root.append(row);}
      if(this.client.host)button('再来一局',()=>this.client.command('rematch'));
    }
    button('退出房间',()=>this.leave());
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
  async leave(notify=true){this.generation=(this.generation||0)+1;this.connecting=false;this.resultRound=null;const client=this.client;this.client=null;this.session?.dispose();this.session=null;this.signature='';this.render();if(notify)this.onStop('已退出联机房间');try{await client?.leave();}catch{}}
}
