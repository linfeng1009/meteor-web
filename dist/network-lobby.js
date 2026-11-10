import {NetworkClient} from './network-client.js';
import {NetworkGame} from './network-game.js';
export class NetworkLobby{
  constructor({getGame,onStart,onStop,onNotice}){Object.assign(this,{getGame,onStart,onStop,onNotice});}
  mount(root){this.root=root;this.render();}
  render(){
    const root=this.root;if(!root?.isConnected)return;root.replaceChildren();
    const note=document.createElement('p');note.className='modal-note';note.textContent='局域网双人长剑对战 · 四方阵。双方准备后由房主开局；房主计算命中、气血与重生。房主需保持游戏窗口运行。';root.append(note);
    const button=(text,fn)=>{const b=document.createElement('button');b.type='button';b.className='secondary-button';b.textContent=text;b.addEventListener('click',async()=>{b.disabled=true;try{await fn();}catch(e){this.onNotice(e.message);}finally{b.disabled=false;}});root.append(b);return b;};
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
    if(this.connecting)return;this.connecting=true;this.generation=(this.generation||0)+1;
    const client=new NetworkClient({getAngle:()=>this.getGame()?.cameraAngle||0,getFrame:()=>this.session?.snapshot(),onRoom:r=>this.roomChanged(r),onInput:inputs=>this.session?.inputs(inputs),onFrame:frame=>this.session?.apply(frame),onError:message=>{this.leave(false);this.onStop('联机中断：'+message);}});
    try{this.client=client;await client.connect(kind,data);this.render();}catch(e){this.client=null;this.render();throw e;}finally{this.connecting=false;}
  }
  async roomChanged(room){
    if(!this.client||this.client.closed)return;
    const signature=JSON.stringify(room);if(signature!==this.signature){this.signature=signature;this.render();}
    if(room.phase==='loading'&&!this.session&&!this.loading){
      this.loading=true;const generation=this.generation;try{await this.onStart();if(generation!==this.generation||this.client?.room.phase!=='loading'){this.onStop('房间已结束');return;}this.session=await NetworkGame.create(this.getGame(),this.client,room);await this.client.command('loaded');}
      catch(e){await this.leave(false);this.onStop('战场载入失败：'+e.message);}finally{this.loading=false;}
    }
    if(room.phase==='playing'&&this.session&&!this.session.active){this.session.play();this.onNotice('双方已入场，长剑对战开始');}
    if(room.phase==='waiting'&&this.session){this.session.dispose();this.session=null;this.onStop('对方已离开，本局结束。');}
  }
  async leave(notify=true){this.generation=(this.generation||0)+1;const client=this.client;this.client=null;this.session?.dispose();this.session=null;this.signature='';try{await client?.leave();}catch{}this.render();if(notify)this.onStop('已退出联机房间');}
}
