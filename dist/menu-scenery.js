export const SCENERY_MAPS = [
  {id:'qiyun',name:'栖云古庭',image:'./assets/enhanced/maps/qiyun/preview.png'},
  {id:'sn06',name:'四方阵',image:'./assets/menu/maps/sn06.webp'},
  {id:'sn01',name:'钟乳洞',image:'./assets/menu/maps/sn01.webp'},
  {id:'sn10',name:'炼铁狱',image:'./assets/menu/maps/sn10.webp'},
  {id:'sn14',name:'炎硫岛',image:'./assets/menu/maps/sn14.webp'},
];
export const sceneryMapId=id=>({sifang:'sn06',cave:'sn01',forge:'sn10'}[id]||id);
export const sceneryImage=id=>{const key=sceneryMapId(id);return SCENERY_MAPS.find(map=>map.id===key)?.image||(/^sn(0[1-9]|1[0-9]|2[01])$/.test(key)?`./assets/menu/maps/${key}.webp`:null);};
// Only changes presentation; never loads a 3D scene or changes the chosen match map.
export class SceneryCarousel {
  constructor({show,active,delay=9000,schedule=(fn,ms)=>setTimeout(fn,ms),cancel=id=>clearTimeout(id)}){Object.assign(this,{show,active,delay,schedule,cancel});this.id='qiyun';this.timer=null;this.paused=false;this.enabled=false;}
  display(id){this.id=sceneryMapId(id);this.show(this.id);}
  start(id=this.id){this.stop();this.enabled=true;this.display(id);this.arm();}
  arm(){if(this.enabled&&!this.paused&&this.active())this.timer=this.schedule(()=>{this.timer=null;this.step(1);},this.delay);}
  stop(){if(this.timer!==null)this.cancel(this.timer);this.timer=null;this.enabled=false;}
  step(direction=1){if(this.timer!==null)this.cancel(this.timer);this.timer=null;if(!this.enabled||!this.active())return;const index=SCENERY_MAPS.findIndex(map=>map.id===this.id);this.display(SCENERY_MAPS[(index+direction+SCENERY_MAPS.length)%SCENERY_MAPS.length].id);this.arm();}
  choose(id){this.start(id);}
  setPaused(value){this.paused=value;if(this.timer!==null)this.cancel(this.timer);this.timer=null;this.arm();}
}
