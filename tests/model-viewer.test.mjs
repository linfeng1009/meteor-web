import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import {previewCamera,visibleModelBounds} from '../dist/menu-snapshots.js';
import {mountModelViewer} from '../dist/model-viewer.js';
test('取景按实际模型尺寸，头饰和长枪在默认与旋转视角都完整入画',()=>{
  for(const size of [[1,5,.8],[12,.2,.3],[3,2,4]])for(const aspect of [.6,1.5,2.2])for(const yaw of [0,.35,1.6,3]){
    const box=new THREE.Box3(new THREE.Vector3(-size[0]/2,0,-size[2]/2),new THREE.Vector3(size[0]/2,size[1],size[2]/2)),camera=previewCamera(box,aspect,{yaw,pitch:.7});
    for(const x of [box.min.x,box.max.x])for(const y of [box.min.y,box.max.y])for(const z of [box.min.z,box.max.z]){const point=new THREE.Vector3(x,y,z).project(camera);assert.ok(Math.abs(point.x)<=1&&Math.abs(point.y)<=1&&Math.abs(point.z)<=1);}
  }
});
test('隐藏的装备不撑大人物取景范围',()=>{const root=new THREE.Group(),body=new THREE.Mesh(new THREE.BoxGeometry(1,3,1)),hidden=new THREE.Group();hidden.visible=false;hidden.add(new THREE.Mesh(new THREE.BoxGeometry(100,100,100)));root.add(body,hidden);const bounds=visibleModelBounds(root);assert.equal(bounds.getSize(new THREE.Vector3()).y,3);});
test('拖拽合并同一帧请求，静止不渲染，关闭取消任务与监听',async()=>{
  const previous={raf:globalThis.requestAnimationFrame,caf:globalThis.cancelAnimationFrame,observer:globalThis.ResizeObserver};let scheduled=null,count=0,disconnected=false;const listeners=new Map();
  globalThis.requestAnimationFrame=fn=>(scheduled=fn,1);globalThis.cancelAnimationFrame=()=>scheduled=null;globalThis.ResizeObserver=class{observe(){}disconnect(){disconnected=true;}};
  const canvas={width:720,height:540,addEventListener:(name,fn)=>listeners.set(name,fn),removeEventListener:name=>listeners.delete(name),getBoundingClientRect:()=>({width:800,height:400}),setPointerCapture(){},hasPointerCapture:()=>false};
  try{const viewer=mountModelViewer({canvas,draw:()=>{count++;}});let frame=scheduled;scheduled=null;await frame();assert.equal(count,1);assert.equal(scheduled,null);viewer.adjust('left');viewer.adjust('right');assert.ok(scheduled);frame=scheduled;scheduled=null;await frame();assert.equal(count,2);assert.equal(scheduled,null);viewer.adjust('in');viewer.dispose();assert.equal(scheduled,null);assert.equal(listeners.size,0);assert.ok(disconnected);assert.equal(canvas.width,1);}finally{globalThis.requestAnimationFrame=previous.raf;globalThis.cancelAnimationFrame=previous.caf;globalThis.ResizeObserver=previous.observer;}
});
