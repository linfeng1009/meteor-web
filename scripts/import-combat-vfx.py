"""Preserve ordinary EF nodes and close their original mesh-texture references."""
from pathlib import Path
import argparse, json, runpy, subprocess

ROOT=Path(__file__).resolve().parents[1]
helpers=runpy.run_path(str(ROOT/'scripts/import-rage-vfx.py'))
read_effect=helpers['read_effect']
parser=argparse.ArgumentParser()
parser.add_argument('--source',type=Path,help='Original directory containing ETexture.pak and TexturePatch.pak, only needed for missing textures')
parser.add_argument('--textures-only',action='store_true',help='Fill mesh texture references without changing the existing EF list or particle-adapter policy')
args=parser.parse_args()
code="""import fs from 'node:fs';import{parsePos}from './dist/native-combat.js';import{NATIVE_MOVE_CATALOG}from './dist/native-move-catalog.js';
const p=parsePos(fs.readFileSync('dist/assets/original/characters/p0/p0.pos','utf8')),ids=new Set();
for(const move of NATIVE_MOVE_CATALOG.filter(m=>!m.pending&&!m.rage)){let id=move.poseId,seen=new Set();while(p.has(id)&&!seen.has(id)){seen.add(id);const pose=p.get(id);if(pose.raw.fields.effectid)ids.add(pose.raw.fields.effectid.toLowerCase());id=pose.link;}}
console.log(JSON.stringify([...ids].sort()));"""
ids=json.loads(subprocess.run(['node','--input-type=module','-e',code],cwd=ROOT,check=True,capture_output=True,text=True).stdout)
atlas=ROOT/'dist/assets/original/rage-vfx/manifest.json'
manifest=json.loads(atlas.read_text(encoding='utf-8'));textures=manifest['textures']
records={}
for name in ids:
    file=ROOT/'dist/assets/original/sounds/definitions'/f'{name}.ef'
    if not file.exists():continue
    records[name]=read_effect(file)
mesh_types={'PLANE','BILLBOARD','SPHERE','CYLINDER','BOX'}
required={n['texture'] for e in records.values() for n in e['nodes'] if n['type'] in mesh_types and n['texture']}
missing=required-textures.keys()
if missing:
    if not args.source:raise FileNotFoundError(f'Original mesh textures missing: {sorted(missing)}; pass --source <original directory>')
    helpers['extract_effect_textures'](missing,textures,args.source,atlas.parent)
    atlas.write_text(json.dumps(manifest,ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
if args.textures_only:
    print(json.dumps({'addedTextures':len(missing),'requiredMeshTextures':len(required),'effectsRegenerated':False}))
    raise SystemExit(0)
effects={}
for name,record in records.items():
    if any(n['type'] in {'PLANE','BILLBOARD','SPHERE','CYLINDER','BOX','PARTICLE'} and n['texture'] in textures for n in record['nodes']):
        record['particleAdapter']=True
        effects[name]=record
output=ROOT/'dist/assets/original/combat-vfx.json'
output.write_text(json.dumps({'version':1,'source':'Preserved ordinary POS/ACT-linked PonEF files and original PAK mesh textures','effects':effects,'adapter':'Existing visual mesh/key sampler. PARTICLE uses bounded browser emission with original keys, anchors and textures; native emitter physics pending. No attack volumes are registered.'},ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
print(json.dumps({'effects':len(effects),'texturedNodes':sum(n['texture'] in textures and n['type'] in {'PLANE','BILLBOARD','SPHERE','CYLINDER','BOX','PARTICLE'} for e in effects.values() for n in e['nodes']),'bytes':output.stat().st_size}))
