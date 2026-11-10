import assert from 'node:assert/strict';

export function sourcePmxVertices(bytes){
  assert.equal(bytes.subarray(0,4).toString(),'PMX ');
  const header=bytes.subarray(9,9+bytes[8]),extra=header[1],boneBytes=header[5];let offset=9+bytes[8];
  for(let i=0;i<4;i++){const length=bytes.readInt32LE(offset);offset+=4+length;}
  const count=bytes.readInt32LE(offset);offset+=4;const vertices=[];
  for(let i=0;i<count;i++){
    const position=[0,1,2].map(a=>bytes.readFloatLE(offset+a*4)),normal=[0,1,2].map(a=>bytes.readFloatLE(offset+12+a*4)),uv=[bytes.readFloatLE(offset+24),bytes.readFloatLE(offset+28)];offset+=32+extra*16;
    const deform=bytes[offset++];offset+=deform===0?boneBytes:deform===1?boneBytes*2+4:deform===3?boneBytes*2+40:boneBytes*4+16;offset+=4;
    vertices.push({position,normal,uv});
  }
  return vertices;
}

