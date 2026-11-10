import bpy,os,re,struct,math,json
from mathutils import Matrix,Vector,Quaternion
ROOT='/Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web';SRC=os.path.join(ROOT,'dist/assets/original/characters/p0')
bpy.ops.wm.open_mainfile(filepath=os.path.join(ROOT,'work/character-hd/孟星魂-高清对照.blend'))
entries=[]
for m in re.finditer(r'\b(bone|Dummey)\s+(\S+)\s*\{([^}]+)\}',open(os.path.join(SRC,'p0.bnc')).read()):
 def get(k):return re.search(k+r'\s+([^\r\n]+)',m[3])[1].strip()
 entries.append(dict(kind=m[1],name=m[2],parent=get('parent'),position=list(map(float,get('pivot').split())),quaternion=list(map(float,get('quaternion').split()))))
B=[e for e in entries if e['kind']=='bone'];D=[e for e in entries if e['kind']=='Dummey'];by={e['name']:e for e in entries}
def resolve(n):return n if n in by else(B[int(n[1:])]['name']if re.fullmatch(r'b\d+',n)else(D[int(n[1:])]['name']if re.fullmatch(r'd\d+',n)else None))
def worlds(data):
 out={}
 def calc(n):
  if n in out:return out[n]
  e=data[n];q=Quaternion(e['quaternion']);q.normalize();m=Matrix.Translation(Vector(e['position']))@q.to_matrix().to_4x4();p=resolve(e['parent']);out[n]=calc(p)@m if p else m;return out[n]
 for n in by:calc(n)
 return out
REST=worlds(by)
local={n:dict(e)for n,e in by.items()};data=open(os.path.join(SRC,'p0.amb'),'rb').read();nb,nd,nf,fps=struct.unpack_from('<iiii',data,5);o=21+(20+nb*16+nd*33)
for i,e in enumerate(B):local[e['name']]['quaternion']=struct.unpack_from('<ffff',data,o+20+i*16)
root=struct.unpack_from('<fff',data,o+8);local[B[0]['name']]['position']=[0,0,root[2]]
for i,e in enumerate(D):
 a=o+20+nb*16+i*33;local[e['name']]['parent']=data[a:a+5].decode().rstrip('\0');local[e['name']]['position']=struct.unpack_from('<fff',data,a+5);local[e['name']]['quaternion']=struct.unpack_from('<ffff',data,a+17)
 if e['name']=='d_base':local[e['name']]['position']=e['position']
ANIM=worlds(local);C=Matrix.Rotation(-math.pi/2,4,'Z');arm=bpy.data.objects['ORIGINAL RIG • 30 bones + 6 attachments']
matdiff=lambda a,b:max(abs(a[i][j]-b[i][j])for i in range(4)for j in range(4))
restErrors={e['name']:matdiff(REST[e['name']]@C,arm.data.bones[e['name']].matrix_local)for e in B}
poseErrors={e['name']:matdiff(ANIM[e['name']]@C,arm.pose.bones[e['name']].matrix)for e in B}
ob=bpy.data.objects['ORIGINAL • SKC 1482 triangles'];ev=ob.evaluated_get(bpy.context.evaluated_depsgraph_get());mesh=ev.to_mesh();diffs=[]
for v in ob.data.vertices:
 expected=Vector((0,0,0,0));total=sum(g.weight for g in v.groups)
 for g in v.groups:
  name=ob.vertex_groups[g.group].name;expected+=(ANIM[name]@REST[name].inverted()@Vector((*v.co,1)))*(g.weight/total)
 actual=mesh.vertices[v.index].co;diffs.append((actual-expected.xyz).length)
result={'restErrorMax':max(restErrors.values()),'restErrors':restErrors,'poseErrorMax':max(poseErrors.values()),'evaluatedVertexErrorMax':max(diffs),'evaluatedVertexErrorMean':sum(diffs)/len(diffs),'errorVerticesTop':sorted(enumerate(diffs),key=lambda x:-x[1])[:12]}
print(json.dumps(result));open(os.path.join(ROOT,'work/hutao-quality/previous-p0-rig-audit.json'),'w').write(json.dumps(result,indent=2)+'\n');ev.to_mesh_clear()
