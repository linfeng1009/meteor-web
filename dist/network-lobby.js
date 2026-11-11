import {NetworkClient} from './network-client.js';
import {NetworkGame} from './network-game.js';
export class NetworkLobby{
  constructor({getGame,onStart,onStop,onNotice,createClient=options=>new NetworkClient(options),createSession=(...args)=>NetworkGame.create(...args)}){Object.assign(this,{getGame,onStart,onStop,onNotice,createClient,createSession});}
  mount(root){this.root=root;this.render();}
  render(){
    const root=this.root;if(!root?.isConnected)return;root.replaceChildren();
    const note=document.createElement('p');note.className='modal-note';note.textContent='局域网双人长剑对战 · 四方阵。双方准备后由房主开局；房主计算命中、气血与重生。房主需保持游戏窗口运行。';root.append(note);
    const button=(text,fn)=>{const b=document.createElement('button');b.type='button';b.className='secondary-button';b.textContent=text;b.addEventListener('click',async()=>{b.disabled=true;try{await fn();}catch(e){this.onNotice(e.message);}finally{b.disabled=false;}});root.append(b);return b;};
    if(this.connecting&&!this.client?.room){const status=document.createElement('p');status.textContent='正在连接房间…';root.append(status);button('取消连接',()=>this.leave());return;}
    if(!this.client){
      const name=document.createElement('input');name.placeholder='玩家名字';name.maxLength=16;name.setAttribute('aria-label','联机玩家名字');name.value='江湖来客';name.className='setting-select';root.append(name);
      button('创建房间',()=>this.connect('create',{name:name.value}));
      const code=document.createElement('input');code.placeholder='六位房间号';code.maxLength=6;code.setAttribute('aria-label','房间号');code.className='setting-select';root.append(code);button('加入房间',()=>this.connect('join',{name:name.value,code:code.value.trim().toUpperCase()}));return;
    }
    const room=this.client.room,title=document.createElement('h3');title.textContent='房间号：'+room.code;root.append(title);
    for(const p of room.players){const row=document.createElement('p');row.textContent=`${p.name}${p.id===room.hostId?'（房主）':''}${p.id===this.client.playerId?'（你）':''} · ${p.ready?'已准备':'未准备'}${room.phase==='loading'?(p.loaded?' · 载入完成':' · 载入中'):''}`;root.append(row);}
    if(room.phase==='waiting'){
      const self=room.players.find(p=>p.id===this.client.playerId);
      button(self.ready?'取消准备':'准备',()=>this.client.command('ready',{ready:!self.ready}));
      if(this.client.host)button('开始对战',()=>this.client.command('start')).disabled=room.players.length!==2||!room.players.every(p=>p.ready);
    }
    button('退出房间',()=>this.leave());
  }
  async connect(kind,data){
    if(this.connecting||this.client)return;this.connecting=true;const generation=this.generation=(this.generation||0)+1;
    const current=()=>this.client===client&&this.generation===generation;
    const stop=message=>{if(current()){this.leave(false);this.onStop(message);}};
    const client=this.createClient({getAngle:()=>this.getGame()?.cameraAngle||0,getPitch:()=>this.getGame()?.localControl?.aimPitch||0,getFrame:()=>current()?this.session?.snapshot():null,
      onRoom:r=>{if(current())this.roomChanged(r,client).catch(error=>stop('联机状态错误：'+error.message));},
      onInput:inputs=>{if(!current())return;if(!this.session?.active)throw Error('战斗未就绪，无法应用操作');this.session.inputs(inputs);},
      onFrame:frame=>{if(current())this.session?.apply(frame);},onError:message=>stop('联机中断：'+message)});
    try{this.client=client;this.render();await client.connect(kind,data);if(current())this.render();}
    catch(e){if(current()){this.client=null;this.render();throw e;}}
    finally{if(this.generation===generation)this.connecting=false;}
  }
  async roomChanged(room,client=this.client){
    if(!client||client!==this.client||client.closed)return;
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
    if(room.phase==='playing'&&this.session&&!this.session.active){this.session.play();this.onNotice('双方已入场，长剑对战开始');}
    if(room.phase==='waiting'&&this.session){this.session.dispose();this.session=null;this.onStop('对方已离开，本局结束。');}
  }
  async leave(notify=true){this.generation=(this.generation||0)+1;this.connecting=false;const client=this.client;this.client=null;this.session?.dispose();this.session=null;this.signature='';this.render();if(notify)this.onStop('已退出联机房间');try{await client?.leave();}catch{}}
}
