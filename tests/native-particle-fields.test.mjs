import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {execFileSync} from 'node:child_process';
import {createHash} from 'node:crypto';
const root=new URL('../',import.meta.url),original=new URL('../dist/assets/original/',import.meta.url);
const python=process.platform==='win32'?'python':'python3';
const manifest=JSON.parse(await readFile(new URL('particle-vfx.json',original),'utf8'));

test('全部粒子参数可由仓库原EF重新导出，源字节和节点尾部均未改写',async()=>{
 const result=JSON.parse(execFileSync(python,['-S','scripts/import-particle-vfx.py','--check'],{cwd:root,encoding:'utf8'}));
 assert.equal(result.checked,true);assert.equal(result.effects,246);assert.equal(result.emitters,555);
 for(const effect of Object.values(manifest.effects)){
  const raw=await readFile(new URL(effect.source,original));assert.equal(createHash('sha256').update(raw).digest('hex'),effect.sha256);
  for(const node of effect.nodes){const p=node.parameters,tail=raw.subarray(p.tailOffset,p.tailOffset+p.tailBytes);assert.equal(createHash('sha256').update(tail).digest('hex'),p.tailSha256);assert.equal(tail.readUInt32LE(0),p.capacity);assert.equal(tail.readFloatLE(24),p.lifetimeRange[0]);assert.equal(tail.readFloatLE(32),p.speedRange[0]);}
 }
});

test('原剑262足部粒子保留20个容量、8至12尺寸、2秒寿命及原方向和绑定',()=>{
 const p=manifest.effects.pos262.nodes.find(n=>n.name==='Particle_1').parameters;
 assert.equal(p.capacity,20);assert.equal(p.capacityLimit,2000);assert.deepEqual(p.sizeRange,[8,12]);assert.deepEqual(p.secondarySizeRange,[8,12]);
 assert.deepEqual(p.lifetimeRange,[2,2]);assert.deepEqual(p.speedRange,[10,30]);assert.deepEqual(p.directionChangeRange,[5,5]);
 assert.deepEqual(p.directionFrom,[-1,.5,0]);assert.deepEqual(p.directionTo,[1,1,Math.fround(.1)]);assert.deepEqual(p.references,['bad_L_Foot','Character','']);
 assert.equal(p.rotate,0);assert.equal(p.stretch,0);assert.deepEqual(p.angularSpeedRange,[360,720]);assert.deepEqual(p.directionJitter,Array(3).fill(Math.fround(.2)));
});

test('0、16和28字节原扩展均被保留，不将旧格式误读为新格式',()=>{
 const counts=new Map();for(const effect of Object.values(manifest.effects))for(const node of effect.nodes){const p=node.parameters,blob=Buffer.from(p.extensionHex,'hex');counts.set(blob.length,(counts.get(blob.length)||0)+1);
  if(blob.length){assert.equal(blob.readUInt32LE(0),p.rotate);assert.equal(blob.readUInt32LE(4),p.stretch);assert.equal(blob.readFloatLE(8),p.angularSpeedRange[0]);assert.equal(blob.readFloatLE(12),p.angularSpeedRange[1]);}
  if(blob.length===28)for(let i=0;i<3;i++)assert.equal(blob.readFloatLE(16+i*4),p.directionJitter[i]);
 }
 assert.deepEqual([...counts].sort((a,b)=>a[0]-b[0]),[[0,255],[16,5],[28,295]]);
});

test('不完整尾部、超长绑定和未核实扩展被拒绝，不补造粒子参数',()=>{
 const code="import runpy,struct;parse=runpy.run_path('scripts/import-rage-vfx.py')['read_particle_fields'];tail=bytearray(96)+struct.pack('<III',0,0,0);bad=[(b'',b''),(tail[:99],b''),(tail,b'1234'),(bytearray(96)+struct.pack('<I',257),b'')];count=0\nfor raw,blob in bad:\n try:parse(raw,0,len(raw),blob)\n except ValueError:count+=1\nassert count==len(bad);print(count)";
 assert.equal(execFileSync(python,['-S','-c',code],{cwd:root,encoding:'utf8'}).trim(),'4');
});
