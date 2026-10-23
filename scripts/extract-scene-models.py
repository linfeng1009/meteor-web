#!/usr/bin/env python3
"""Extract actual DES-referenced cmodel resources; never alter source client files."""
from pathlib import Path
import argparse, importlib.util, json, re, collections

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('meteor_original_importer', ROOT/'scripts/import-original.py')
source_importer = importlib.util.module_from_spec(spec); spec.loader.exec_module(source_importer)


def inspect_fmc(data):
    text, encoding = source_importer.text_bytes(data)
    header = re.search(r'SceneObjects\s+(\d+)\s+Dumm?eyObjects\s+(\d+)', text, re.I)
    timing = re.search(r'FPS\s+(\d+)\s+Frames\s+(\d+)\s+Mode:\s*(\w+)', text, re.I)
    if not header or not timing or timing[3].upper() != 'RIGID': raise ValueError('Unsupported FMC header/mode')
    frames = list(re.finditer(r'frame\s+(\d+)\s*\{([^}]+)\}', text, re.I))
    objects, dummies = int(header[1]), int(header[2]); count, fps = int(timing[2]), int(timing[1])
    if len(frames) != count: raise ValueError('FMC frame count mismatch')
    for index, match in enumerate(frames):
        rows = re.findall(r'\bt\s+([\deE.+-]+)\s+([\deE.+-]+)\s+([\deE.+-]+)\s+q\s+([\deE.+-]+)\s+([\deE.+-]+)\s+([\deE.+-]+)\s+([\deE.+-]+)', match[2])
        if int(match[1]) != index or len(rows) != objects + dummies: raise ValueError('FMC rigid transform count mismatch')
    return dict(format='FMC RIGID', encoding=encoding, fps=fps, frames=count, sceneObjects=objects, dummyObjects=dummies)


def has_source_model(importer, name):
    for extension in ('gmc','gmb'):
        try: importer.read(f'cmodel/{name}.{extension}'); return True
        except FileNotFoundError: pass
    return False


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source',type=Path,default=Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_'))
    parser.add_argument('--dry-run',action='store_true')
    args=parser.parse_args(); source=args.source.resolve(); out=ROOT/'dist/assets/original/scene-models'
    maps_manifest=json.loads((ROOT/'dist/assets/original/manifest.json').read_text())
    references=collections.defaultdict(list)
    for scene in maps_manifest['maps']:
        if scene.get('available') is False: continue
        meta=json.loads((ROOT/'dist/assets/original'/scene['metadata']).read_text())
        des=next((f['parsed'] for f in meta['files'] if f.get('parsed',{}).get('format')=='DES'),{})
        for obj in des.get('objects',[]):
            model=obj.get('properties',{}).get('model','').strip('"').lower()
            if model and re.fullmatch(r'[a-z0-9_]+',model):references[model].append(dict(map=scene['id'],object=obj['name']))
    references['w1_0'].append(dict(reason='Original sn01 PlayerWeapon=5 / Meteor.res weapon id5'))
    importer=source_importer.Importer(source,out,args.dry_run)
    try:
        models=[];pending=list(sorted(references));seen=set();archive_names=list(importer.archives)
        while pending:
            name=pending.pop(0)
            if name in seen:continue
            seen.add(name);entry=dict(id=name,instances=references[name],textures=[],available=True)
            model_data=model_ref=model_ext=None
            for extension in ['gmb','gmc']:
                try:model_data,model_ref=importer.read(f'cmodel/{name}.{extension}');model_ext=extension;break
                except FileNotFoundError:pass
            if model_data is None:
                # Scene DES uses logical dual-spike prefixes, while actual files
                # and RES items have r/l suffixes. Preserve this distinction.
                if name in ('w8_0','w8_3'):
                    pair=[name+'r',name+'l']
                    if all(has_source_model(importer, part) for part in pair):
                        entry.update(pairedModels=pair,format='LOGICAL_PAIR',pairingProvenance='DES logical prefix resolves actual r/l files; displaying both together is a browser-host choice, not recovered EXE placement semantics.')
                        for part in pair:
                            references[part].append(dict(parentModel=name,reason='DES logical paired-weapon prefix'))
                            if part not in seen: pending.append(part)
                        models.append(entry);continue
                entry.update(available=False,unavailableReason='No original cmodel GMB/GMC file found');models.append(entry);continue
            try:parsed=(source_importer.parse_gmb if model_ext=='gmb' else source_importer.parse_gmc)(model_data)
            except Exception as error:entry.update(available=False,unavailableReason=str(error));models.append(entry);continue
            directory=f'models/{name}';entry['model']=importer.write(f'{directory}/{name}.{model_ext}',model_data,model_ref)['url'];entry['format']=model_ext.upper();entry['stats']=parsed
            for extension,field in [('des','description'),('fmc','animation'),('pos','poses')]:
                try:data,ref=importer.read(f'cmodel/{name}.{extension}')
                except FileNotFoundError:continue
                entry[field]=importer.write(f'{directory}/{name}.{extension}',data,ref)['url']
                if extension=='fmc':
                    try:entry['animationInfo']=inspect_fmc(data)
                    except Exception as error:entry['animationError']=str(error)
                if extension=='des':
                    des=source_importer.parse_des(data);entry['objects']=des['objects']
                    for obj in des['objects']:
                        nested=obj.get('properties',{}).get('model','').strip('"').lower()
                        if nested and re.fullmatch(r'[a-z0-9_]+',nested) and nested not in seen:
                            references[nested].append(dict(parentModel=name,object=obj['name']));pending.append(nested)
            for texture in parsed.get('textures',[]):
                entry['textures'].append(importer.texture(texture,'textures',['TexturePatch.pak','ctexture.pak','ETexture.pak']+[a for a in archive_names if re.match(r'sn\d+\.pak$',a)],['texture','ctexture','cmodel']))
            models.append(entry)
        unique={a['url']:a for a in importer.assets}; manifest=dict(schemaVersion=1,readOnlySource=True,sourceRoot=str(source),models=models,assets=list(unique.values()),warnings=importer.warnings,stats=dict(modelCount=len(models),available=sum(m['available'] for m in models),uniqueFiles=len(unique),bytes=sum(a['bytes'] for a in unique.values()),fmcCount=sum('animationInfo' in m for m in models)))
        importer.json('manifest.json',manifest)
        if not args.dry_run:
            (ROOT/'work/meteor-original/evidence/E-scene-model-extraction.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')
        print(json.dumps(dict(dryRun=args.dry_run,**manifest['stats'],unavailable=[m['id'] for m in models if not m['available']],warnings=importer.warnings),ensure_ascii=False))
    finally:importer.close()

if __name__=='__main__':main()
