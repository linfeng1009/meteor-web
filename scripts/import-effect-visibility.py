"""Refresh only original EF display flags; keep helper transforms and attack data."""
from pathlib import Path
import argparse,json,runpy

ROOT=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser()
parser.add_argument('--check',action='store_true')
args=parser.parse_args()
read_effect=runpy.run_path(str(ROOT/'scripts/import-rage-vfx.py'))['read_effect']
original=ROOT/'dist/assets/original'
outputs=[]
hidden={}
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
            if source.get('hidden'):
                node['hidden']=True
                hidden[(parsed['sha256'],node['offset'])]=(node['type'],bool(node.get('texture')))
            else:node.pop('hidden',None)
    outputs.append((path,payload))
for path,payload in outputs:
    current=json.loads(path.read_text(encoding='utf-8'))
    if args.check:
        if current!=payload:raise ValueError(f'Visibility metadata differs from original EF: {path.name}')
    elif current!=payload:path.write_text(json.dumps(payload,ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
print(json.dumps(dict(checked=args.check,hiddenNodes=len(hidden),texturedHiddenNodes=sum(record[1] for record in hidden.values()))))
