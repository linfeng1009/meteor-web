import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { decodeCourtyardGeometry } from '../dist/qiyun-courtyard.js';

// Read the shipped Blender export and raycast its actual collision triangles.
// Only image decoding is omitted in Node; the map and physics are production code.
const dist = new URL('../dist/', import.meta.url), originalFetch = globalThis.fetch;
const originalLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function(url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const v = (x=0,y=0,z=0) => new THREE.Vector3(x,y,z);
const game = Object.create(MeteorGame.prototype);
Object.assign(game, { collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }), raycaster: new THREE.Raycaster(),
  hostPhysics: { radius:.4,step:.55,gravity:34 }, mode:'training', scene:new THREE.Scene(),
  renderer:{shadowMap:{},toneMapping:THREE.NoToneMapping}, baseLights:[new THREE.HemisphereLight(),new THREE.DirectionalLight()] });
game.scene.background = new THREE.Color();
game.currentMap = await game._readMap('qiyun');
after(() => { game._disposeMap(game.currentMap); game.collisionMaterial.dispose(); globalThis.fetch=originalFetch; THREE.TextureLoader.prototype.load=originalLoad; });

test('the shipped map has usable spawns and continuous ground across the entire fight surface', () => {
  assert.equal(game.currentMap.id,'qiyun');
  assert.ok(game.currentMap.spawns.length >= 4);
  for(const spawn of game.currentMap.spawns) {
    const hit = game._ground(spawn.position.x,spawn.position.z,spawn.position.y+3);
    assert.ok(hit,spawn.name); assert.ok(Math.abs(hit.point.y-.765)<.02);
  }
  for(let z=-15;z<=15;z+=.65) for(let x=-15;x<=15;x+=.65) {
    if(Math.hypot(x,z)>17)continue;
    assert.ok(game._ground(x,z,2),`no crack at ${x},${z}`);
  }
});

test('real movement crosses slab seams and the north approach without getting stuck or falling', () => {
  const actor = {root:new THREE.Group(),velocity:v(),vy:0,grounded:true,combat:{busy:false}};
  actor.root.position.set(0,.78,10);
  for(let i=0;i<340;i++)game._move(actor,v(0,0,-1),8,1/60);
  assert.ok(actor.root.position.z < -29,'crossed the centre, passed the gate and climbed the shrine stairs');
  assert.ok(actor.grounded); assert.ok(actor.root.position.y > 1.9);
  assert.ok(Math.abs(game._ground(22,-8,3).point.y-1.7)<.02,'side pavilion has a solid floor');
  assert.equal(game._horizontalBlocked(v(0,.8,-19),0,-1),false,'gate opening remains clear');
  assert.equal(game._horizontalBlocked(v(5.5,.8,-19.7),0,-1),true,'solid gate pillar blocks movement');
  for(let i=0;i<64;i++) {
    const a=(i+.5)*Math.PI*2/64;
    if(Math.abs(a-Math.PI)<.45 || (a>1.75&&a<2.3))continue;
    assert.equal(game._horizontalBlocked(v(Math.sin(a)*16.9,.78,Math.cos(a)*16.9),Math.sin(a)*.65,Math.cos(a)*.65),true,`continuous rail at ${a}`);
  }
});

test('presentation and low quality restore correctly when leaving the new map', () => {
  game._applyMapPresentation();
  assert.equal(game.renderer.toneMapping,THREE.ACESFilmicToneMapping);
  assert.ok(game.renderer.shadowMap.enabled); assert.ok(game.baseLights.every(l=>!l.visible));
  game.quality='low'; game._applyMapPresentation(); assert.equal(game.renderer.shadowMap.enabled,false);
  const map=game.currentMap; game.currentMap={id:'sn01'}; game._applyMapPresentation();
  assert.equal(game.scene.fog,null); assert.equal(game.renderer.toneMapping,THREE.NoToneMapping);
  assert.equal(game.renderer.shadowMap.enabled,false); assert.ok(game.baseLights.every(l=>l.visible));
  game.currentMap=map; game.quality='high';
});

test('map animation uses elapsed simulation time and corrupt buffers fail explicitly', () => {
  const water=game.currentMap.model.children.find(m=>m.name==='water / Still jade water');
  assert.ok(water);
  const before=water.material.uniforms.time.value; game.currentMap.update(.5);
  assert.equal(water.material.uniforms.time.value,before+.5);
  const invalid={positions:{offset:0,count:6}};
  assert.throws(()=>decodeCourtyardGeometry(invalid,new ArrayBuffer(4)),/不完整/);
});

test('eviction disposes scene resources once and retains the engine collision material', () => {
  let sharedDisposed=0, disposed=0;
  game.collisionMaterial.addEventListener('dispose',()=>sharedDisposed++);
  const resources=new Set();
  game.currentMap.model.traverse(m=>{if(m.geometry)resources.add(m.geometry);if(m.material&&m.material!==game.collisionMaterial)resources.add(m.material);});
  for(const r of resources)r.addEventListener('dispose',()=>disposed++);
  const map=game.currentMap;
  game._disposeMap(map);
  assert.equal(sharedDisposed,0); assert.equal(disposed,resources.size);
  // Prevent the teardown hook from disposing the same map a second time.
  game.currentMap={model:new THREE.Group()};
});
