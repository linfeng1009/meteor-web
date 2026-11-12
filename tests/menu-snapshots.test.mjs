import test from 'node:test';
import assert from 'node:assert/strict';
import {SnapshotCache,MenuSnapshots,weaponPreviewSource} from '../dist/menu-snapshots.js';
import * as THREE from '../dist/vendor/three.module.js';

test('预览缓存按最近使用淘汰并释放图片，清空不留下对象地址',async()=>{
  const revoked=[],cache=new SnapshotCache(2,value=>revoked.push(value));
  await cache.get('a',async()=>'blob:a');await cache.get('b',async()=>'blob:b');
  assert.equal(await cache.get('a',()=>assert.fail('应命中缓存')),'blob:a');
  await cache.get('c',async()=>'blob:c');assert.deepEqual(revoked,['blob:b']);
  cache.clear();assert.deepEqual(new Set(revoked),new Set(['blob:a','blob:b','blob:c']));assert.equal(cache.entries.size,0);
});
test('重复截图请求只执行一次，离开菜单后迟到结果必须释放',async()=>{
  let complete,creates=0;const revoked=[],cache=new SnapshotCache(2,url=>revoked.push(url));
  const create=()=>{creates++;return new Promise(resolve=>complete=resolve);};
  const first=cache.get('map',create),second=cache.get('map',create);cache.clear();
  const current=cache.get('map',async()=>'blob:new');complete('blob:old');
  assert.equal(await first,null);assert.equal(await second,null);assert.equal(await current,'blob:new');assert.equal(creates,1);assert.deepEqual(revoked,['blob:old']);assert.equal(cache.entries.get('map'),'blob:new');
});
test('截图失败后可重试，不缓存错误',async()=>{
  const cache=new SnapshotCache(2,()=>{});await assert.rejects(cache.get('weapon',async()=>{throw Error('GPU failed');}));
  assert.equal(cache.pending.size,0);assert.equal(await cache.get('weapon',async()=>'blob:retry'),'blob:retry');
});
test('武器预览选择当前可见外观，失败的外观使用真实原版模型',()=>{
  const original={visible:false},enhanced={visible:true},hero={weapon:'sword',weaponModels:[original],butterflySword:enhanced};
  assert.deepEqual(weaponPreviewSource(hero,'butterfly','original'),{style:'butterfly',models:[enhanced]});
  enhanced.visible=false;original.visible=true;assert.deepEqual(weaponPreviewSource(hero,'raiden','original'),{style:'original',models:[original]});
  hero.weapon='dual';hero.weaponModels=[original,{visible:true}];assert.equal(weaponPreviewSource(hero,'original','original').models.length,2);
});
test('战斗期间和已销毁游戏不允许截图或分配预览资源',async()=>{
  const game={running:true,menuIdle:false},snapshots=new MenuSnapshots(game);
  assert.equal(await snapshots.map('sifang'),null);assert.equal(await snapshots.weapon('sword'),null);
  game.running=false;game.menuIdle=true;game.disposed=true;assert.equal(await snapshots.map('forge'),null);
  assert.equal(snapshots.maps.entries.size,0);assert.equal(snapshots.weapons.entries.size,0);
});

test('截图编码尚未完成时角色已经恢复可见，避免切入战斗时隐藏角色',async()=>{
  let complete;const hero={root:new THREE.Group()},hidden={root:new THREE.Group()};hidden.root.visible=false;
  const snapshots=new MenuSnapshots({menuIdle:true,running:false,hero,enemies:[hidden],camera:new THREE.PerspectiveCamera(),currentMap:{},scene:new THREE.Scene()});
  snapshots.render=()=>{assert.equal(hero.root.visible,false);return new Promise(resolve=>complete=resolve);};
  const pending=snapshots.map('sifang');assert.equal(hero.root.visible,true);assert.equal(hidden.root.visible,false);
  complete(null);assert.equal(await pending,null);
});

test('GPU截图失败仍恢复渲染目标、视口、裁切和清屏状态',async()=>{
  const state={target:null,scissor:true,alpha:.7,color:new THREE.Color(0x334455),viewport:new THREE.Vector4(3,4,800,600),crop:new THREE.Vector4(8,9,70,60)};
  const renderer={autoClear:false,getRenderTarget:()=>state.target,getViewport:v=>v.copy(state.viewport),getScissor:v=>v.copy(state.crop),getScissorTest:()=>state.scissor,getClearColor:v=>v.copy(state.color),getClearAlpha:()=>state.alpha,
    setRenderTarget:value=>state.target=value,setViewport:value=>state.viewport.copy(value),setScissor:value=>state.crop.copy(value),setScissorTest:value=>state.scissor=value,setClearColor:(value,alpha)=>{state.color.set(value);state.alpha=alpha;},render(){throw Error('GPU failure');}};
  const snapshots=new MenuSnapshots({menuIdle:true,running:false,renderer});
  assert.throws(()=>snapshots.render({}, {}, 32,32),/GPU failure/);
  assert.equal(state.target,null);assert.equal(state.scissor,true);assert.equal(state.alpha,.7);assert.equal(state.color.getHex(),0x334455);assert.equal(renderer.autoClear,false);assert.deepEqual(state.viewport.toArray(),[3,4,800,600]);assert.deepEqual(state.crop.toArray(),[8,9,70,60]);
});

test('人物截图编码前恢复原父节点和子节点顺序，战斗期间禁止截图',async()=>{
  const parent=new THREE.Group(),before=new THREE.Group(),root=new THREE.Group(),after=new THREE.Group();parent.add(before,root,after);root.position.set(3,0,5);
  const game={menuIdle:true,running:false,hero:{root}},shots=new MenuSnapshots(game);let finish;
  shots.render=()=>{assert.notEqual(root.parent,parent);return new Promise(resolve=>finish=resolve);};
  const pending=shots.character('hero');assert.equal(root.parent,parent);assert.deepEqual(parent.children,[before,root,after]);assert.deepEqual(root.position.toArray(),[3,0,5]);finish(null);await pending;
  game.running=true;assert.equal(await shots.character('other'),null);
});
