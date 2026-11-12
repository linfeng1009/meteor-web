"""Extract verified original particle fields without enabling a new renderer."""
from pathlib import Path
import argparse,json,runpy

ROOT=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser()
parser.add_argument('--check',action='store_true',help='Verify checked-in fields against every original EF without writing')
args=parser.parse_args()
read_effect=runpy.run_path(str(ROOT/'scripts/import-rage-vfx.py'))['read_effect']
original=ROOT/'dist/assets/original'
effects={}
for name in ['combat-vfx.json','rage-vfx/manifest.json','item-vfx.json']:
    effects.update(json.loads((original/name).read_text(encoding='utf-8'))['effects'])
records={}
for name,definition in sorted(effects.items()):
    parsed=read_effect(original/definition['source'],include_particles=True)
    if parsed['sha256']!=definition['sha256']:raise ValueError(f'EF source hash mismatch: {name}')
    nodes=[dict(name=n['name'],offset=n['offset'],parameters=n['particle']) for n in parsed['nodes'] if n['type']=='PARTICLE']
    if nodes:records[name]=dict(source=definition['source'],sha256=parsed['sha256'],nodes=nodes)
payload=dict(version=1,source='Original EF tails; static Meteor.exe 2479bc4bdf916d4a6386ed6352cfa9c5446708de9c1b5e859d4a674a3b42da94',
    evidence=dict(reader='00587380',writer='00587170',initializer='00586d40',step='00586690',capacityClamp='00585d9f',render='00585ff0'),
    nativeWordOrder=['026c','02f4','02f0','02fc','02f8','02e4','02e8','02ec','0304','0300','0308','030c','0320','0324','0328','032c','0330','0334','0270','0274','0280','0278','0284','027c'],
    extensionWordOrder=['0318','031c','0310','0314','0338','033c','0340'],
    scope='Verified parameter preservation only. Secondary size range and reference-target resolution remain unported; existing particle presentation is unchanged.',effects=records)
output=original/'particle-vfx.json'
if args.check:
    if json.loads(output.read_text(encoding='utf-8'))!=payload:raise ValueError('Checked-in particle parameters differ from original EF')
else:output.write_text(json.dumps(payload,ensure_ascii=False,separators=(',',':'))+'\n',encoding='utf-8')
print(json.dumps(dict(effects=len(records),emitters=sum(len(e['nodes']) for e in records.values()),checked=args.check,bytes=output.stat().st_size)))
