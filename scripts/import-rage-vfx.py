"""Read-only PonEF extraction. Keeps source keys and archive images intact.
Supported visual nodes: PLANE/BILLBOARD/CYLINDER/SPHERE/BOX. The independent
contact host consumes source attack bounds; this importer registers no hits.
Emitter simulation and full native blend/IFL semantics remain incomplete.
"""
from pathlib import Path
from io import BytesIO
import argparse, hashlib, json, math, re, struct, zipfile, subprocess

ROOT = Path(__file__).resolve().parents[1]
TYPES = ['AUDIO','BOX','BILLBOARD','CYLINDER','DRAG','DONUT','MODEL','PARTICLE','PATH','PLANE','SPHERE','TRAPE']
DIMS = {'PLANE':2, 'BILLBOARD':2, 'CYLINDER':5, 'SPHERE':5, 'BOX':3, 'DONUT':6}

def read_particle_fields(data, cursor, end, blob):
    """00587380 read order;00586d40 init;00586690 step. No renderer guesses."""
    start=cursor
    if cursor+96>end:raise ValueError('Truncated native particle parameters')
    count=struct.unpack_from('<I',data,cursor)[0]
    values=list(struct.unpack_from('<23f',data,cursor+4))
    flags={i:struct.unpack_from('<I',data,cursor+i*4)[0] for i in [18,19,20,22]}
    if not all(math.isfinite(value) for i,value in enumerate(values,1) if i not in flags):raise ValueError('Nonfinite native particle parameters')
    cursor+=96
    names=[]
    for _ in range(3):
        if cursor+4>end:raise ValueError('Truncated particle binding length')
        length=struct.unpack_from('<I',data,cursor)[0];cursor+=4
        if length>256 or cursor+length>end:raise ValueError('Invalid particle binding')
        names.append(data[cursor:cursor+length].decode('cp950').rstrip('\0'));cursor+=length
    if cursor!=end:raise ValueError('Unexpected particle parameter tail')
    if len(blob) not in [0,16,28]:raise ValueError('Unverified native particle extension size')
    native_jitter=struct.unpack('<f',struct.pack('<I',0x3e4ccccd))[0]
    rotate,stretch,angular,jitter=0,0,[360.,720.],[native_jitter]*3
    if blob:
        rotate,stretch=struct.unpack_from('<2I',blob);angular=list(struct.unpack_from('<2f',blob,8))
        if len(blob)==28:jitter=list(struct.unpack_from('<3f',blob,16))
    if not all(math.isfinite(v) for v in angular+jitter):raise ValueError('Nonfinite particle extension')
    f=lambda index:values[index-1]
    return dict(capacity=count,capacityLimit=2000,sizeRange=[f(1),f(2)],secondarySizeRange=[f(3),f(4)],
                steering=f(5),lifetimeRange=[f(6),f(7)],speedRange=[f(8),f(9)],directionChangeRange=[f(10),f(11)],
                directionFrom=[f(i) for i in [12,13,14]],directionTo=[f(i) for i in [15,16,17]],
                singleCycle=flags[18],slowDown=flags[19],fadeIn=flags[20],fadeInRatio=f(21),fadeOut=flags[22],fadeOutRatio=f(23),
                references=names,rotate=rotate,stretch=stretch,angularSpeedRange=angular,directionJitter=jitter,
                tailOffset=start,tailBytes=end-start,tailSha256=hashlib.sha256(data[start:end]).hexdigest(),extensionHex=blob.hex())

def read_effect(path, include_particles=False):
    data = path.read_bytes()
    if data[:11] != b'PonEF V1.00': raise ValueError(f'Invalid EF header: {path}')
    offsets = sorted((m.start(), t) for t in TYPES for m in re.finditer(re.escape(t.encode().ljust(16,b'\0')),data))
    if len(offsets) != struct.unpack_from('<I',data,11)[0]: raise ValueError(f'EF node inventory mismatch: {path}')
    nodes = []
    for index,(offset,kind) in enumerate(offsets):
        end = offsets[index+1][0] if index+1<len(offsets) else len(data)
        cursor = offset+16
        def string():
            nonlocal cursor
            length = struct.unpack_from('<I',data,cursor)[0]; cursor += 4
            if length>256 or cursor+length>end: raise ValueError(f'Invalid EF string: {path}:{cursor}')
            text = data[cursor:cursor+length].decode('cp950').rstrip('\0'); cursor+=length
            return text
        name = string(); flags = struct.unpack_from('<4I',data,cursor); cursor+=16
        bindings = [string(),string()]
        texture = string()
        # 0058e8a0: the material's +78/+7c UV speeds are at byte73/77
        # in this 93-byte payload (common effect data +b0/+b4).
        if cursor+93>end:raise ValueError('Truncated EF material payload')
        uv_speed=list(struct.unpack_from('<2f',data,cursor+73))
        if not all(math.isfinite(value) for value in uv_speed):raise ValueError('Nonfinite EF UV speed')
        # 0058e8a0 reads material+a4 (common effect data+dc). Native draw
        # routines reject nonzero values; transform/contact queries do not.
        hidden=struct.unpack_from('<I',data,cursor+69)[0]!=0
        # 0058e540 selects modes0..4; 0058e6d0 maps the two custom
        # factor indices only for mode4. Preserve unused factor words too.
        blend=list(struct.unpack_from('<3I',data,cursor+81))
        if blend[0]>4 or (blend[0]==4 and any(value>9 for value in blend[1:])):raise ValueError('Unverified EF blend mode or factor')
        cursor+=93
        count = struct.unpack_from('<I',data,cursor)[0]; cursor+=4
        if not 0<count<=256 or cursor+112*count+4>end: raise ValueError(f'Invalid EF key stream: {path}:{name}')
        keys = [list(struct.unpack_from('<28f',data,cursor+i*112)) for i in range(count)]; cursor+=112*count
        if not all(math.isfinite(v) for key in keys for v in key): raise ValueError('Nonfinite EF channel')
        if any(a[0]>b[0] for a,b in zip(keys,keys[1:])): raise ValueError('EF time order')
        blob = struct.unpack_from('<I',data,cursor)[0]; cursor+=4
        blob_data=data[cursor:cursor+blob] if include_particles and kind=='PARTICLE' else b''
        cursor+=blob
        if cursor>end: raise ValueError('EF blob exceeds node')
        node = dict(type=kind,name=name,flags=list(flags),bindings=bindings,texture=texture.lower(),keys=keys,offset=offset)
        if any(uv_speed):node['uvSpeed']=uv_speed
        if hidden:node['hidden']=True
        node['blend']=blend
        if kind in DIMS:
            if end-cursor != DIMS[kind]*4: raise ValueError(f'Unexpected shape size {path}:{name}:{end-cursor}')
            node['dimensions'] = list(struct.unpack_from('<'+'f'*DIMS[kind],data,cursor))
            if kind=='DONUT': node['unsupportedVisual']=True
        else:
            node['unsupportedVisual'] = kind != 'AUDIO'
            if kind=='PARTICLE' and include_particles:node['particle']=read_particle_fields(data,cursor,end,blob_data)
        nodes.append(node)
    return dict(id=path.stem.lower(),source=f'sounds/definitions/{path.name}',sha256=hashlib.sha256(data).hexdigest(),nodes=nodes)

def extract_effect_textures(references,textures,source,output):
    if not references:return
    from PIL import Image
    archives=[]
    for name in ['TexturePatch.pak','ETexture.pak']:
        archive=zipfile.ZipFile(source/name)
        archives.append((name,archive,{Path(n).name.lower():n for n in archive.namelist()}))
    def extract(name):
        key=Path(name.replace('\\','/')).name.lower()
        if not key or key in textures:return
        for archive_name,archive,index in archives:
            if key not in index:continue
            member=index[key];data=archive.read(member)
            record=dict(reference=key,archive=archive_name,member=member,sha256=hashlib.sha256(data).hexdigest())
            textures[key]=record
            if key.endswith('.ifl'):
                frames=[]
                for line in data.decode('ascii').splitlines():
                    fields=line.split()
                    if not fields:continue
                    frame=fields[0].lower();duration=int(fields[1]) if len(fields)>1 and fields[1].isdigit() else 1
                    extract(frame); frames.extend([frame]*duration)
                record['frames']=frames;record['fpsAdapter']=30
            else:
                image=Image.open(BytesIO(data));image.load()
                filename=key.replace('.','_')+'.png';directory=output/'textures';directory.mkdir(exist_ok=True)
                image.save(directory/filename)
                record.update(url='textures/'+filename,width=image.width,height=image.height)
            return
        raise FileNotFoundError(f'Original effect texture missing: {key}')
    try:
        for reference in sorted(references):extract(reference)
    finally:
        for _,archive,_ in archives:archive.close()


def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--source',type=Path,default=Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_'))
    parser.add_argument('--include-pose',type=int,action='append',default=[],help='Import an additional original pose/link chain for inspection without enabling its command')
    parser.add_argument('--extend-existing',action='store_true',help='Merge requested EF definitions; extract missing textures from --source if needed')
    args=parser.parse_args()
    source=args.source; output=ROOT/'dist/assets/original/rage-vfx';output.mkdir(parents=True,exist_ok=True)
    # Discover enabled rage commands from the same runtime catalog, retaining
    # every automatic POS link. This also tracks newly ported weapon families.
    code = '''import {readFileSync} from 'node:fs';
import {parsePos,decodeNativeText} from './dist/native-combat.js';
import {NATIVE_MOVE_CATALOG} from './dist/native-move-catalog.js';
const poses=parsePos(decodeNativeText(readFileSync('dist/assets/native/combat/P0.POS'))), effects=new Map();
for(const move of [...NATIVE_MOVE_CATALOG.filter(m=>m.rage&&!m.pending),...process.argv.slice(1).map(id=>({poseId:Number(id),weapon:'asset-inspection'}))]){let id=move.poseId,seen=new Set();while(!seen.has(id)&&poses.has(id)){seen.add(id);const p=poses.get(id),effectId=p.raw.fields.effectid;if(effectId)effects.set(effectId.toLowerCase(),{id:effectId.toLowerCase(),poseId:id,weapon:move.weapon,start:p.start,end:p.end});id=p.link;}}
process.stdout.write(JSON.stringify([...effects.values()]));'''
    requested=json.loads(subprocess.run(['node','--input-type=module','-e',code,*map(str,args.include_pose)],cwd=ROOT,check=True,capture_output=True,text=True).stdout)
    if args.extend_existing:
        # Preserve prior explicitly imported poses and extracted texture records.
        # Validate the complete batch before writing; never silently omit images.
        manifest_path=output/'manifest.json'
        manifest=json.loads(manifest_path.read_text(encoding='utf-8'))
        added={}
        for request in requested:
            if request['id'] in manifest['effects']: continue
            effect=read_effect(ROOT/f'dist/assets/original/sounds/definitions/{request["id"]}.ef')
            added[effect['id']]=effect
        references={node['texture'] for effect in added.values() for node in effect['nodes'] if node['type']!='AUDIO' and node['texture'] and node['texture'] not in manifest['textures']}
        extract_effect_textures(references,manifest['textures'],source,output)
        manifest['effects'].update(added)
        manifest_path.write_text(json.dumps(manifest,ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
        print(json.dumps(dict(added=list(added),sourceHashes={k:v['sha256'] for k,v in added.items()})))
        return
    evidence_dir=ROOT/'work/rage-vfx';evidence_dir.mkdir(parents=True,exist_ok=True)
    (evidence_dir/'requested-effects.json').write_text(json.dumps(requested,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    textures={}
    effects={}
    for request in requested:
        path=ROOT/f'dist/assets/original/sounds/definitions/{request["id"]}.ef'
        if not path.exists(): continue
        effect=read_effect(path);effects[effect['id']]=effect
    extract_effect_textures({node['texture'] for effect in effects.values() for node in effect['nodes'] if node['type']!='AUDIO' and node['texture']},textures,source,output)
    weapons=json.loads((ROOT/'dist/assets/original/weapon-models/manifest.json').read_text(encoding='utf-8'))
    attachments={}
    for model in weapons['models']:
        model_id=model['modelId'].lower();path=ROOT/f'dist/assets/original/weapon-models/models/{model_id}/{model_id}.des'
        if not path.exists():continue
        for block in re.finditer(r'Object\s+(d_wpn\w+)\s*\{([^}]+)\}',path.read_text(errors='replace'),re.I):
            position=re.search(r'Position:\s+([-+\d.]+)\s+([-+\d.]+)\s+([-+\d.]+)',block[2])
            quaternion=re.search(r'Quaternion:\s+([-+\d.]+)\s+([-+\d.]+)\s+([-+\d.]+)\s+([-+\d.]+)',block[2])
            if position and quaternion:attachments.setdefault(model_id,{})[block[1].lower()]=dict(position=list(map(float,position.groups())),quaternion=list(map(float,quaternion.groups())))
    manifest=dict(version=1,source='Original PonEF V1.00 + ETexture.pak / TexturePatch.pak; read-only offline extraction',keyLayout='28 float32: time, positionXYZ, quaternionXYZW, scaleXYZ, material channels; opacity at 24. Raw values retained.',presentationAdapters=['Linear key interpolation / quaternion slerp.','Textured shape meshing and additive brightness limit .65.','IFL playback at 30fps; full native texture-channel semantics remain pending.','Particle emitters, DRAG, MODEL, PATH and DONUT are not synthesized. Source SPHERE/BOX/CYLINDER/PLANE/DONUT attack bounds are consumed independently by native-effect-contacts.js.'],effects=effects,textures=textures,weaponAttachments=attachments)
    (output/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
    supported=sum(1 for effect in effects.values() for node in effect['nodes'] if node['type'] in {'PLANE','BILLBOARD','CYLINDER','SPHERE','BOX'} and node['texture'])
    evidence=dict(effects=len(effects),texturedShapes=supported,textures=len(textures),sourceHashes={k:v['sha256'] for k,v in effects.items()},unsupported=sorted(set(node['type'] for effect in effects.values() for node in effect['nodes'] if node.get('unsupportedVisual'))))
    (ROOT/'work/rage-vfx/extraction.json').write_text(json.dumps(evidence,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(evidence,ensure_ascii=False))
if __name__=='__main__':main()
