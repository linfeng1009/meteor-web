"""Preserve original ordinary-attack EF nodes that can use existing textures."""
from pathlib import Path
import json, runpy, subprocess

ROOT=Path(__file__).resolve().parents[1]
read_effect=runpy.run_path(str(ROOT/'scripts/import-rage-vfx.py'))['read_effect']
code="""import fs from 'node:fs';import{parsePos}from './dist/native-combat.js';import{NATIVE_MOVE_CATALOG}from './dist/native-move-catalog.js';
const p=parsePos(fs.readFileSync('dist/assets/original/characters/p0/p0.pos','utf8')),ids=new Set();
for(const move of NATIVE_MOVE_CATALOG.filter(m=>!m.pending&&!m.rage)){let id=move.poseId,seen=new Set();while(p.has(id)&&!seen.has(id)){seen.add(id);const pose=p.get(id);if(pose.raw.fields.effectid)ids.add(pose.raw.fields.effectid.toLowerCase());id=pose.link;}}
console.log(JSON.stringify([...ids].sort()));"""
ids=json.loads(subprocess.run(['node','--input-type=module','-e',code],cwd=ROOT,check=True,capture_output=True,text=True).stdout)
textures=json.loads((ROOT/'dist/assets/original/rage-vfx/manifest.json').read_text(encoding='utf-8'))['textures']
effects={}
for name in ids:
    file=ROOT/'dist/assets/original/sounds/definitions'/f'{name}.ef'
    if not file.exists():continue
    record=read_effect(file)
    if any(n['type'] in {'PLANE','BILLBOARD','SPHERE','CYLINDER','BOX','PARTICLE'} and n['texture'] in textures for n in record['nodes']):
        record['particleAdapter']=True
        effects[name]=record
output=ROOT/'dist/assets/original/combat-vfx.json'
output.write_text(json.dumps({'version':1,'source':'Preserved ordinary POS/ACT-linked PonEF files; existing original texture atlas only','effects':effects,'adapter':'Existing visual mesh/key sampler. PARTICLE uses bounded browser emission with original keys, anchors and textures; native emitter physics pending. No attack volumes are registered.'},ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
print(json.dumps({'effects':len(effects),'texturedNodes':sum(n['texture'] in textures and n['type'] in {'PLANE','BILLBOARD','SPHERE','CYLINDER','BOX','PARTICLE'} for e in effects.values() for n in e['nodes']),'bytes':output.stat().st_size}))
