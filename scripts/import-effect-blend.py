"""Refresh only original EF blend-mode/factor words in existing manifests."""
from pathlib import Path
import argparse,collections,json,runpy

ROOT=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser()
parser.add_argument('--check',action='store_true')
args=parser.parse_args()
read_effect=runpy.run_path(str(ROOT/'scripts/import-rage-vfx.py'))['read_effect']
original=ROOT/'dist/assets/original'
outputs=[]
unique={}
for name in ['combat-vfx.json','rage-vfx/manifest.json','item-vfx.json']:
    path=original/name
    payload=json.loads(path.read_text(encoding='utf-8'))
    for effect_id,definition in payload['effects'].items():
        parsed=read_effect(original/definition['source'])
        if parsed['sha256']!=definition['sha256']:raise ValueError(f'EF source hash mismatch: {effect_id}')
        nodes={n['offset']:n for n in parsed['nodes']}
        if len(nodes)!=len(definition['nodes']):raise ValueError(f'EF node count mismatch: {effect_id}')
        for node in definition['nodes']:
            source=nodes[node['offset']]
            if (node['name'],node['type'])!=(source['name'],source['type']):raise ValueError(f'EF node identity mismatch: {effect_id}')
            node['blend']=source['blend']
            unique[(parsed['sha256'],node['offset'])]=source['blend'][0]
    outputs.append((path,payload))
for path,payload in outputs:
    current=json.loads(path.read_text(encoding='utf-8'))
    if args.check:
        if current!=payload:raise ValueError(f'Blend metadata differs from original EF: {path.name}')
    elif current!=payload:
        indent=2 if path.name=='item-vfx.json' else None
        path.write_text(json.dumps(payload,ensure_ascii=False,indent=indent,separators=None if indent else (',',':'))+'\n',encoding='utf-8')
print(json.dumps(dict(checked=args.check,nodes=len(unique),modes=dict(sorted(collections.Counter(unique.values()).items())))))
