"""Refresh only source UV speeds in existing EF manifests; preserve every other field."""
from pathlib import Path
import argparse,json,runpy

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
            if 'uvSpeed' in source:node['uvSpeed']=source['uvSpeed']
            else:node.pop('uvSpeed',None)
            unique[(parsed['sha256'],node['offset'])]=(node['type'],bool(node.get('texture')),source.get('uvSpeed'))
    outputs.append((path,payload))
# Validate every input before writing any manifest.
for path,payload in outputs:
    if args.check:
        if json.loads(path.read_text(encoding='utf-8'))!=payload:raise ValueError(f'UV speed metadata differs from original EF: {path.name}')
    elif json.loads(path.read_text(encoding='utf-8'))!=payload:
        path.write_text(json.dumps(payload,ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
scrolling=[record for record in unique.values() if record[2]]
print(json.dumps(dict(checked=args.check,scrollingNodes=len(scrolling),texturedScrollingNodes=sum(record[1] for record in scrolling))))
