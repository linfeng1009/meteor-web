// Extract original AttrPOIS channels without inventing geometry or keys.
import fs from 'node:fs';
import {createHash} from 'node:crypto';
const source=new URL('../dist/assets/original/sounds/definitions/AttrPOIS.ef',import.meta.url),data=fs.readFileSync(source);
if(data.subarray(0,11).toString()!=='PonEF V1.00')throw Error('Invalid PonEF');
const types=['AUDIO','BOX','BILLBOARD','CYLINDER','DRAG','DONUT','MODEL','PARTICLE','PATH','PLANE','SPHERE','TRAPE'];
const dims={PLANE:2,BILLBOARD:2,CYLINDER:5,SPHERE:5,BOX:3};
const offsets=types.flatMap(type=>{const marker=Buffer.from(type.padEnd(16,'\0')),found=[];for(let at=data.indexOf(marker);at>=0;at=data.indexOf(marker,at+1))found.push({type,offset:at});return found;}).sort((a,b)=>a.offset-b.offset);
if(offsets.length!==data.readUInt32LE(11))throw Error('Node count mismatch');
const nodes=offsets.map(({type,offset},index)=>{
  const end=offsets[index+1]?.offset??data.length;let cursor=offset+16;
  const string=()=>{const n=data.readUInt32LE(cursor);cursor+=4;if(n>256||cursor+n>end)throw Error('Invalid string');const s=new TextDecoder('big5').decode(data.subarray(cursor,cursor+n)).replace(/\0+$/,'');cursor+=n;return s;};
  const name=string(),flags=Array.from({length:4},(_,i)=>data.readUInt32LE(cursor+4*i));cursor+=16;
  const bindings=[string(),string()],texture=string().toLowerCase();cursor+=93;
  const count=data.readUInt32LE(cursor);cursor+=4;if(count<1||count>256||cursor+count*112+4>end)throw Error('Invalid keys');
  const keys=Array.from({length:count},()=>{const key=Array.from({length:28},(_,i)=>data.readFloatLE(cursor+4*i));cursor+=112;if(!key.every(Number.isFinite))throw Error('Nonfinite key');return key;});
  const blob=data.readUInt32LE(cursor);cursor+=4+blob;
  const node={type,name,flags,bindings,texture,keys,offset};
  if(dims[type]){if(cursor+dims[type]*4!==end)throw Error('Invalid dimensions');node.dimensions=Array.from({length:dims[type]},(_,i)=>data.readFloatLE(cursor+4*i));}
  else node.unsupportedVisual=type!=='AUDIO';
  return node;
});
const definition={id:'attrpois',source:'sounds/definitions/AttrPOIS.ef',sha256:createHash('sha256').update(data).digest('hex'),nodes};
fs.writeFileSync(new URL('../dist/assets/original/poison-vfx.json',import.meta.url),JSON.stringify({version:1,effects:{attrpois:definition},adapters:'Original AttrPOIS particle keys and ZS2 texture; bounded Web looping, spread and attachment are adapters.'},null,2)+'\n');
console.log(`Extracted ${nodes.length} original AttrPOIS nodes; emitter motion remains a Web adapter.`);


