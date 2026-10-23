#!/usr/bin/env python3
"""Read-only audit of current extracted asset manifests. Writes only evidence."""
import hashlib,json
from pathlib import Path
from collections import Counter
from datetime import datetime
from zoneinfo import ZoneInfo
ROOT=Path(__file__).resolve().parents[2]
BASE=ROOT/'dist/assets/original'
E=ROOT/'work/meteor-original/evidence'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
issues=[];verified=[];summaries={}
for name,folder in [('main',BASE),('sceneModels',BASE/'scene-models'),('weaponModels',BASE/'weapon-models')]:
 manifest=folder/'manifest.json';d=json.loads(manifest.read_text())
 for a in d['assets']:
  p=folder/a['url']
  if not p.exists():issues.append({'path':str(p.relative_to(ROOT)),'error':'missing'});continue
  if p.stat().st_size!=a['bytes']:issues.append({'path':str(p.relative_to(ROOT)),'error':'size mismatch'})
  actual=sha(p)
  if actual!=a['sha256']:issues.append({'path':str(p.relative_to(ROOT)),'error':'hash mismatch','expected':a['sha256'],'actual':actual})
  verified.append(str(p.relative_to(ROOT)))
 summaries[name]={'manifest':str(manifest.relative_to(ROOT)),'manifestSha256':sha(manifest),'stats':d['stats'],'verifiedAssetEntries':len(d['assets']),'warnings':d.get('warnings',[]),'errors':d.get('errors',[])}
 if name=='main':
  summaries[name]['assetPrefixes']=dict(Counter(a['url'].split('/')[0] for a in d['assets']))
  summaries[name]['unavailableMaps']=[{'id':m['id'],'reason':m.get('unavailableReason')} for m in d['maps'] if m.get('available') is False]
  summaries[name]['limitations']=d['limitations']
 if name=='weaponModels':summaries[name]['availableItems']=sum(bool(x['available']) for x in d['items'])
 if name=='sceneModels':summaries[name]['unavailableModels']=[{'id':m['id'],'reason':m.get('unavailableReason') or m.get('error') or m.get('reason')} for m in d['models'] if not m.get('available')]
folder=BASE/'characters';manifest=folder/'manifest.json';d=json.loads(manifest.read_text());n=0
for ch in d['characters']:
 for ext,desc in ch['files'].items():
  p=folder/f"p{ch['id']}"/f"p{ch['id']}.{ext}"
  if not p.exists():issues.append({'path':str(p.relative_to(ROOT)),'error':'missing'});continue
  if sha(p)!=desc['sha256'] or p.stat().st_size!=desc['bytes']:issues.append({'path':str(p.relative_to(ROOT)),'error':'character source hash/size mismatch'})
  verified.append(str(p.relative_to(ROOT)));n+=1
 for t in ch['textures']:
  source=folder/f"p{ch['id']}"/'textures'/t['source'].lower();web=folder/f"p{ch['id']}"/'textures'/t['web']
  if not source.exists() or sha(source)!=t['sha256']:issues.append({'path':str(source.relative_to(ROOT)),'error':'texture source mismatch'})
  if not web.exists():issues.append({'path':str(web.relative_to(ROOT)),'error':'web texture missing'})
 p=ROOT/'dist'/ch['portrait'].removeprefix('./')
 if not p.exists():issues.append({'path':str(p.relative_to(ROOT)),'error':'portrait missing'})
common=folder/'common/character.amb'
if sha(common)!=d['common']['sha256'] or common.stat().st_size!=d['common']['bytes']:issues.append({'path':str(common.relative_to(ROOT)),'error':'common animation mismatch'})
verified.append(str(common.relative_to(ROOT)));n+=1
charfiles=[p for p in folder.rglob('*') if p.is_file()]
summaries['characters']={'manifest':str(manifest.relative_to(ROOT)),'manifestSha256':sha(manifest),'characters':len(d['characters']),'ids':[c['id'] for c in d['characters']],'verifiedSourceFiles':n,'actualFiles':len(charfiles),'actualBytes':sum(p.stat().st_size for p in charfiles),'common':d['common'],'portraitCount':len(list((folder/'portraits').glob('*.jpg')))}
allfiles=[p for p in BASE.rglob('*') if p.is_file()]
out={'observedAt':datetime.now(ZoneInfo('Asia/Shanghai')).isoformat(),'scope':'current extracted filesystem and four manifest snapshots; read-only audit; does not assert gameplay implementation completeness','manifests':summaries,'verifiedEntries':len(verified),'uniqueVerifiedPaths':len(set(verified)),'issues':issues,'actualOriginalDirectory':{'files':len(allfiles),'bytes':sum(p.stat().st_size for p in allfiles)},'separateManifestRoots':['main','scene-models','weapon-models','characters'],'coverageLimits':['Main manifest stats exclude separate scene-models/weapon-models/characters trees.','Asset availability does not establish support for its AI, mission, collision, event, effect or network behavior.','sn22 is retained as source but unavailable due to nonfinite GMB vertices.','Weapon w6_5 source is absent; scene model warnings and unavailable models are preserved verbatim.']}
(E/'E-asset-coverage-current.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n')
print(json.dumps({'verifiedEntries':len(verified),'issues':issues,'summary':{k:{a:v for a,v in s.items() if a in ['stats','characters','actualFiles','actualBytes','availableItems']} for k,s in summaries.items()},'actualOriginalDirectory':out['actualOriginalDirectory']},ensure_ascii=False))
