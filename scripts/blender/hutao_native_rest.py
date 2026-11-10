import os,re,json,math
from mathutils import Matrix,Quaternion,Vector
ROOT=os.path.abspath(os.path.join(os.path.dirname(__file__),'../..'))
s=open(os.path.join(ROOT,'dist/assets/original/characters/p0/p0.bnc')).read();entries=[]
for m in re.finditer(r'\b(bone|Dummey)\s+(\S+)\s*\{([^}]+)\}',s):
 def get(k):return re.search(k+r'\s+([^\r\n]+)',m[3])[1].strip()
 entries.append(dict(kind='bone'if m[1]=='bone'else'dummy',name=m[2],parent=get('parent'),position=list(map(float,get('pivot').split())),quaternion=list(map(float,get('quaternion').split()))))
B=[e for e in entries if e['kind']=='bone'];D=[e for e in entries if e['kind']=='dummy'];by={e['name']:e for e in entries}
def resolve(n):
 if n in by:return n
 if re.fullmatch(r'b\d+',n):return B[int(n[1:])]['name']
 if re.fullmatch(r'd\d+',n):return D[int(n[1:])]['name']
 return None
world={}
def calc(n):
 if n in world:return world[n]
 e=by[n];q=Quaternion(e['quaternion']);q.normalize();m=Matrix.Translation(Vector(e['position']))@q.to_matrix().to_4x4();p=resolve(e['parent']);world[n]=calc(p)@m if p else m;return world[n]
for e in entries:calc(e['name'])
if __name__=='__main__':
 for i,b in enumerate(B):print(i,b['name'],[round(x,4)for x in world[b['name']].translation])
 with open(os.path.join(ROOT,'work/hutao-mod/native-rest.json'),'w')as f:json.dump({'entries':entries,'world':{k:[list(row)for row in v]for k,v in world.items()}},f)
