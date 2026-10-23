#!/usr/bin/env python3
"""Read-only extraction of Meteor's native SKC/BNC/AMB character data."""
from pathlib import Path
import argparse, hashlib, json, re, shutil, struct, subprocess, zipfile, math

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SOURCE = Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_')
CHARACTER_NAMES=['孟星魂','冷燕','铁胡子','破空','夜猫子','冯浩','孙剑','萧安','子与','王强','无名','叶翔','小何','凤凰','石群','屠城','范璇','高寄萍','孙玉伯','律香川']

def find_ci(directory, name):
    return next(p for p in directory.iterdir() if p.name.lower() == name.lower())

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def inspect_amb(path):
    data=path.read_bytes()
    assert data[:5] == b'BANIM'
    bones,dummies,frames,fps=struct.unpack_from('<4i',data,5)
    stride=20+bones*16+dummies*33
    assert len(data)==21+frames*stride
    max_error=0.0
    parents=[set() for _ in range(dummies)]
    for frame in range(frames):
        offset=21+frame*stride
        assert struct.unpack_from('<ii',data,offset)==(-1,frame)
        root=struct.unpack_from('<3f',data,offset+8)
        assert all(math.isfinite(v) for v in root)
        for j in range(bones):
            q=struct.unpack_from('<4f',data,offset+20+j*16)
            assert all(math.isfinite(v) for v in q)
            max_error=max(max_error,abs(sum(v*v for v in q)-1))
        for j in range(dummies):
            p=offset+20+bones*16+j*33
            parents[j].add(data[p:p+5].split(b'\0')[0].decode('ascii'))
            assert all(math.isfinite(v) for v in struct.unpack_from('<7f',data,p+5))
    return dict(bones=bones,dummies=dummies,frames=frames,fps=fps,stride=stride,bytes=len(data),maxQuaternionNormSquaredError=max_error,dummyParents=[sorted(p) for p in parents],sha256=sha(path))

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--source',type=Path,default=DEFAULT_SOURCE);parser.add_argument('--ids',nargs='+',type=int,default=[0]);args=parser.parse_args()
    source=args.source.resolve();out=ROOT/'dist/assets/original/characters';out.mkdir(parents=True,exist_ok=True)
    pm=find_ci(source,'pmodel');texture_archive=find_ci(source,'ptexture.pak');common=find_ci(find_ci(source,'Common'),'character.amb')
    (out/'common').mkdir(exist_ok=True);shutil.copy2(common,out/'common/character.amb')
    manifest={'sourceRoot':str(source),'readOnlySource':True,'common':inspect_amb(common),'characters':[],'formatReferences':['https://www.lxres.com/LiuXingBiJi/1758.html','https://github.com/IceRiverr/Meteor/blob/master/Tools/AmbToTxt/compile_amb.cpp'],'sourceCodeCopied':False}
    with zipfile.ZipFile(texture_archive) as archive:
        names={Path(n).name.lower():n for n in archive.namelist() if not n.endswith('/')}
        for actor_id in args.ids:
            target=out/f'p{actor_id}';target.mkdir(exist_ok=True);
            portraits=out/'portraits';portraits.mkdir(exist_ok=True);portrait_source=find_ci(find_ci(source,'image'),f'P00{actor_id+1}.JPG');shutil.copy2(portrait_source,portraits/f'p{actor_id}.jpg');(target/'textures').mkdir(exist_ok=True)
            files={ext:find_ci(pm,f'p{actor_id}.{ext}') for ext in ['skc','bnc','amb','pos']}
            for ext,path in files.items():shutil.copy2(path,target/f'p{actor_id}.{ext}')
            skin=files['skc'].read_text(encoding='gbk',errors='replace')
            textures=list(dict.fromkeys(re.findall(r'^\s*Texture\s+(\S+)',skin,re.M)))
            extracted=[]
            for name in textures:
                if name.lower()=='null':continue
                original=target/'textures'/name.lower();original.write_bytes(archive.read(names[name.lower()]))
                if original.suffix.lower() in ['.tga','.bmp']:
                    browser=original.with_suffix('.png')
                    subprocess.run(['sips','-s','format','png',str(original),'--out',str(browser)],check=True,stdout=subprocess.DEVNULL)
                    extracted.append({'source':name,'web':browser.name,'sha256':sha(original)})
                else:extracted.append({'source':name,'web':original.name,'sha256':sha(original)})
            vertices=re.findall(r'^\s*v\s+([^\r\n]+)',skin,re.M);faces=re.findall(r'^\s*f\s+([^\r\n]+)',skin,re.M)
            assert len(vertices)==int(re.search(r'Vertices:\s*(\d+)',skin)[1])
            assert len(faces)==int(re.search(r'Triangles:\s*(\d+)',skin)[1])
            weight_error=0.0;largest_bone=-1
            for line in vertices:
                raw=line.split('Bones',1)[1].split();count=int(raw[0]);assert len(raw)==1+count*2
                influences=[(int(raw[1+i*2]),float(raw[2+i*2])) for i in range(count)]
                weight_error=max(weight_error,abs(sum(v for _,v in influences)-1));largest_bone=max(largest_bone,max(i for i,_ in influences))
            for line in faces:
                data=list(map(int,line.split()));assert data[0]==3 and all(0<=i<len(vertices) for i in data[2:])
            info={'id':actor_id,'name':CHARACTER_NAMES[actor_id],'portrait':f'./assets/original/characters/portraits/p{actor_id}.jpg','portraitSource':str(portrait_source),'vertices':len(vertices),'triangles':len(faces),'maxBoneIndex':largest_bone,'maxWeightSumError':weight_error,'files':{ext:{'bytes':p.stat().st_size,'sha256':sha(p)} for ext,p in files.items()},'animation':inspect_amb(files['amb']),'textures':extracted}
            assert largest_bone<info['animation']['bones']
            manifest['characters'].append(info)
    (out/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')
    (out/'E-character-extraction.json').write_text(json.dumps({'case':'meteor-original','type':'E-character-format','quality':'validated-original-data','equivalentImportAnchor':'SKC texture names + bone indices reference ptexture ZIP and BNC; BANIM 30 bones / 6 dummies / per-frame records. Data files have no executable import table.','manifest':manifest},ensure_ascii=False,indent=2)+'\n')
    print(json.dumps({'characters':[(a['id'],a['vertices'],a['triangles']) for a in manifest['characters']],'commonFrames':manifest['common']['frames'],'output':str(out)},ensure_ascii=False))

if __name__=='__main__':main()
