#!/usr/bin/env python3
"""Read-only structural parse of the original Meteor.res, with byte offsets."""
from pathlib import Path
import hashlib,json,struct,collections
ROOT=Path(__file__).resolve().parents[1]
SOURCE=Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_/Meteor.res')
OUT=ROOT/'dist/assets/original/characters'
data=SOURCE.read_bytes();offset=60
assert data.startswith(b'MTTM Meteor Resource file Version 1.0')
def integer():
 global offset
 n=struct.unpack_from('<i',data,offset)[0];offset+=4;return n
def string():
 global offset
 n=integer();assert 0<n<10000
 raw=data[offset:offset+n];offset+=n;assert raw[-1:]==b'\0'
 return {'big5':raw[:-1].decode('big5','replace'),'gbk':raw[:-1].decode('gbk','replace'),'hex':raw[:-1].hex()}
records=[]
while offset<len(data):
 start=offset;kind=integer();identity=integer();name=string();model=string();flag=integer();byte=data[offset];offset+=1
 n=integer();assert 0<=n<=300
 parameters=[]
 for i in range(n):
  p=offset;values=[integer()for _ in range(3)];parameters.append({'offset':p,'words':values})
 n=integer();assert 0<=n<=300
 effects=[]
 for i in range(n):
  p=offset;values=[integer()for _ in range(10)];effects.append({'offset':p,'words':values,'statKey':values[2],'mode':values[5],'value':values[6],'valueOffset':p+24})
 records.append({'offset':start,'endOffset':offset,'type':kind,'id':identity,'name':name['gbk'if kind in[2,4,5]else'big5'],'nameEncodings':name,'model':model['big5'],'flag':flag,'byteFlag':byte,'parameters':parameters,'effects':effects})
assert offset==len(data)
meta={'case':'meteor-original','sample':str(SOURCE),'sha256':hashlib.sha256(data).hexdigest(),'bytes':len(data),'records':len(records),'typeCounts':dict(collections.Counter(r['type']for r in records)),'exactConsumption':offset==len(data),'firstRecordOffset':60,'allRecords':records}
OUT.mkdir(parents=True,exist_ok=True);(OUT/'meteor-res-data.json').write_text(json.dumps(meta,ensure_ascii=False,indent=2)+'\n')
weapons=[r for r in records if r['type']==1];poses=[r for r in records if r['type']==3];items=[r for r in records if r['type']==2]
summary={'case':'meteor-original','evidence':'E-combat-stat-research','quality':'structurally-validated-original-data','sample':str(SOURCE),'sha256':meta['sha256'],'bytes':meta['bytes'],'recordCount':meta['records'],'recordTypeCounts':meta['typeCounts'],'structure':{'record':'int32 type, int32 id, length-prefixed NUL name, length-prefixed NUL model, int32 flag, uint8 flag, int32 parameterCount, parameter[3*int32][], int32 effectCount, effect[10*int32][]','effectStatKeyWord':2,'effectModeWord':5,'effectValueWord':6},'statSemanticCrossChecks':{'2':'HP: original GBK item name 肉包 / 大肉包 / 小肉包 contains key2 values 300 / 500 / 100; final UI scaling not yet disassembled.','3':'Attack-related: weapon key3 base values, pose key3 mode1 coefficients, 嗜战 item key3 value25.','4':'Defense-related: 铜皮 item key4 value20; normal weapon key4 value15.','5':'Movement-related: 猫足 item key5 mode1 value150, 钝筋 key5 mode1 value50.','6':'Rage-related: 气元 item key6 value100, 元气糖 key6 value25, 气绝21 key6 value-10 and 气丧22 key6 value-20.'},'normalWeaponRecords':[r for r in weapons if r['model']in['W0_0','W7_0','W5_0']],'selectedPoseRecords':[r for r in poses if r['id']in[262,263,264,279,280,281,295,296,297,368,201]],'selectedItemRecords':[r for r in items if r['id']in[1,3,4,5,8,21,22,28]],'limitations':['Effect and parameter semantics are inferred through consistent raw values and original in-file item names; final executable HP/damage/rage formulas remain unverified.','Do not treat pose coefficient 35 or weapon attack 110 as direct HP damage.','TargetMove / TargetPose in POS are movement and reaction descriptors, not this raw attack stat.','Field mode1 appears percentage-like (normal movement100, 猫足150, 钝筋50), but full operation dispatch still needs EXE confirmation.']}
(OUT/'E-combat-stat-research.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2)+'\n')
print(json.dumps({k:meta[k]for k in['bytes','records','typeCounts','exactConsumption']},ensure_ascii=False))
