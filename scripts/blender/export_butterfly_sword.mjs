import {writeFile} from 'node:fs/promises';
import {createButterflySword} from '../../dist/butterfly-sword.js';
const root=createButterflySword();root.updateMatrixWorld(true);const objects=[];
root.traverse(o=>{if(!o.isMesh)return;const g=o.geometry.clone();g.applyMatrix4(o.matrixWorld);const p=g.getAttribute('position');const idx=g.index?Array.from(g.index.array):Array.from({length:p.count},(_,i)=>i);objects.push({name:o.name||'Sword part',positions:Array.from(p.array),indices:idx,color:o.material.color.toArray(),metalness:o.material.metalness,roughness:o.material.roughness});});
await writeFile(new URL('../../work/butterfly-sword/mesh-parts.json',import.meta.url),JSON.stringify(objects));
