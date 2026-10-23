#!/usr/bin/env python3
"""Extract exact weapon variants declared in the supplied Meteor.res records.

Does not execute the client or alter the original directory. Shared importer
preserves original bytes and records SHA-256 for every artifact.
"""
import argparse
import importlib.util
import json
from pathlib import Path

ap=argparse.ArgumentParser()
ap.add_argument('--source',type=Path,required=True)
ap.add_argument('--output',type=Path,required=True)
ap.add_argument('--records',type=Path,default=Path(__file__).resolve().parents[1]/'dist/assets/original/characters/meteor-res-data.json')
args=ap.parse_args()
spec=importlib.util.spec_from_file_location('meteor_original_importer',Path(__file__).with_name('import-original.py'))
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
records=json.loads(args.records.read_text())['allRecords']
imp=module.Importer(args.source.resolve(),args.output.resolve())
items=[];models={};errors=[]
try:
    for record in records:
        if record['type']!=1:continue
        model_id=record['model'].lower()
        model_ids=[model_id]
        if model_id.endswith('r'):
            left=model_id[:-1]+'l'
            if any(p.lower().startswith('cmodel/'+left+'.') for p in imp.sources):model_ids.append(left)
        for model in model_ids:
            if model in models:continue
            found=next((p for p in imp.sources if p.lower() in [f'cmodel/{model}.gmb',f'cmodel/{model}.gmc']),None)
            if found is None:
                errors.append({'modelId':model,'error':'source model is absent'});continue
            data,source=imp.read(found)
            try:parsed=module.parse_gmb(data) if found.lower().endswith('.gmb') else module.parse_gmc(data)
            except Exception as error:
                errors.append({'modelId':model,'error':str(error)});continue
            model_url=f'models/{model}/{model}'+Path(found).suffix.lower()
            imp.raw(found,model_url)
            textures=[imp.texture(ref,f'models/{model}/textures',['TexturePatch.pak','ctexture.pak','ETexture.pak'],['texture','Patch']) for ref in parsed['textures']]
            model_entry={'modelId':model,'modelUrl':model_url,'format':parsed['format'],'textures':textures,'stats':{k:parsed[k] for k in ['objectCount','vertexCount','triangleCount']},'source':source}
            des=next((p for p in imp.sources if p.lower()==f'cmodel/{model}.des'),None)
            if des:
                model_entry['description']=imp.raw(des,f'models/{model}/{model}.des')['url']
            models[model]=model_entry
        items.append({'itemId':record['id'],'name':record['name'],'modelId':model_id,'available':model_id in models,'modelIds':[m for m in model_ids if m in models],'parameters':record['parameters'],'effects':record['effects'],'resourceRecordOffset':record['offset']})
    manifest={'source':'local client Meteor.res and cmodel/; read-only extraction','items':items,'models':list(models.values()),'assets':imp.assets,'warnings':imp.warnings,'errors':errors,'stats':{'itemCount':len(items),'modelCount':len(models),'bytes':sum(a['bytes'] for a in imp.assets)}}
    imp.json('manifest.json',manifest)
    print(json.dumps({'itemCount':len(items),'modelCount':len(models),'bytes':manifest['stats']['bytes'],'errors':errors,'warnings':imp.warnings},ensure_ascii=False))
finally:imp.close()
