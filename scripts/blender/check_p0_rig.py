import bpy,os,re,struct,math
from mathutils import Matrix,Vector,Quaternion
ROOT=os.path.abspath(os.path.join(os.path.dirname(__file__),'../..'));SRC=os.path.join(ROOT,'dist/assets/original/characters/p0')
bpy.ops.wm.open_mainfile(filepath=os.path.join(ROOT,'work/character-hd/孟星魂-高清对照.blend'))
es=[]
for m in re.finditer(r'\b(bone|Dummey)\s+(\S+)\s*\{([^}]+)\}',open(os.path.join(SRC,'p0.bnc')).read()):
 def get(k):return re.search(k+r'\s+([^\r\n]+)',m[3])[1].strip()
 es.append(dict(kind=m[1],name=m[2],parent=get('parent'),position=list(map(float,get('pivot').split())),quaternion=list(map(float,get('quaternion').split()))))
B=[e for e in es if e['kind']=='bone'];D=[e for e in es if e['kind']=='Dummey'];by={e['name']:e for e in es};data=open(os.path.join(SRC,'p0.amb'),'rb').read();nb,nd,nf,fps=struct.unpack_from('<iiii',data,5);o=21+20+nb*16+nd*33
for i,e in enumerate(B):e['quaternion']=struct.unpack_from('<ffff',data,o+20+i*16)
root=struct.unpack_from('<fff',data,o+8);B[0]['position']=[0,0,root[2]]
for i,e in enumerate(D):
 a=o+20+nb*16+i*33;e['parent']=data[a:a+5].decode().rstrip('\0');e['position']=struct.unpack_from('<fff',data,a+5);e['quaternion']=struct.unpack_from('<ffff',data,a+17)
 if e['name']=='d_base':e['position']=[0,0,0]
def resolve(n):return n if n in by else(B[int(n[1:])]['name']if re.fullmatch(r'b\d+',n)else(D[int(n[1:])]['name']if re.fullmatch(r'd\d+',n)else None))
world={}
def calc(n):
 if n in world:return world[n]
 e=by[n];q=Quaternion(e['quaternion']);q.normalize();m=Matrix.Translation(Vector(e['position']))@q.to_matrix().to_4x4();p=resolve(e['parent']);world[n]=calc(p)@m if p else m;return world[n]
C=Matrix.Rotation(-math.pi/2,4,'Z')
arm=bpy.data.objects['ORIGINAL RIG • 30 bones + 6 attachments']
for e in B:
 a=calc(e['name'])@C;b=arm.pose.bones[e['name']].matrix;print(e['name'],max(abs(a[i][j]-b[i][j])for i in range(4)for j in range(4)),tuple(a.translation),tuple(b.translation))
