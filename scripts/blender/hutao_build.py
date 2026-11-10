"""Reconstruct user-provided GIMI buffers in Blender and retarget to native p0.

No MOD injection code is run. Missing native face geometry is explicitly retained
as an incomplete-preview condition, never fabricated or replaced by another face.
"""
import bpy,os,sys,struct,json,math,hashlib,argparse
from mathutils import Vector,Matrix,Quaternion
import numpy as np
sys.path.insert(0,os.path.dirname(__file__))
from hutao_native_rest import B,D,entries,world as REST,resolve
ROOT=os.path.abspath(os.path.join(os.path.dirname(__file__),'../..'))
SRC='/Users/dulinfeng/Downloads/hutao_black_stockings_mod_4k/HuTaoMod4K'
OUT=os.path.join(ROOT,'dist/assets/enhanced/hutao');WORK=os.path.join(ROOT,'work/hutao-mod')
for path in[OUT,WORK,os.path.join(OUT,'textures')]:os.makedirs(path,exist_ok=True)
a=argparse.ArgumentParser();a.add_argument('--skip-render',action='store_true');options=a.parse_args(sys.argv[sys.argv.index('--')+1:]if'--'in sys.argv else[])
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
def read(name):return open(os.path.join(SRC,name),'rb').read()
pos=read('HuTaoPosition.buf');blend=read('HuTaoBlend.buf');uvbuf=read('HuTaoTexcoord.buf');N=len(pos)//40
assert N==14672 and len(blend)==N*32 and len(uvbuf)==N*12
P=np.array([struct.unpack_from('<3f',pos,i*40)for i in range(N)],dtype=float)
NORMAL=np.array([struct.unpack_from('<3f',pos,i*40+12)for i in range(N)],dtype=float)
W=[struct.unpack_from('<4f',blend,i*32)for i in range(N)];J=[struct.unpack_from('<4I',blend,i*32+16)for i in range(N)]
UV=[struct.unpack_from('<2f',uvbuf,i*12+4)for i in range(N)]
SOURCE_F=[];MI=[]
for mi,name in enumerate(['HuTaoHead.ib','HuTaoBody.ib']):
 b=read(name);ind=struct.unpack('<'+'I'*(len(b)//4),b)
 assert len(ind)%3==0 and max(ind)<N
 for i in range(0,len(ind),3):SOURCE_F.append(tuple(ind[i:i+3]));MI.append(mi)
# The source is an A-pose in Y-up metres; p0 binds in a Z-up T-pose.
# Semantic GI bone groups identify arm/hand/body/hair membership. This keeps
# disconnected cloth parts on the appropriate anatomical region rather than
# transferring by arbitrary nearest vertex across overlapping coat/hair layers.
HEAD=set(range(31))|{74}
LEFT_ARM={56,57,60,61,62,63,64,65}|set(range(75,92))
RIGHT_ARM={58,59,66,67,68,69,70,71}|set(range(92,109))
LEG_POS={40,73,115,118};LEG_NEG={41,72,116,117}
H_Y=np.array([-.002,.08,.46,.84,1.0,1.1,1.22,1.28,1.33,1.594])
H_Z=np.array([0,2.1424,10.8188,20.2633,25.2,28.4,30.0745,31.787,33.2429,39.05])
def height(y):return float(np.interp(y,H_Y,H_Z))
def segment_transform(source_a,source_b,target_a,target_b):
 sa,sb,ta,tb=map(lambda p:Vector(p),(source_a,source_b,target_a,target_b));axis=(sb-sa).normalized();dest=(tb-ta).normalized();rotation=axis.rotation_difference(dest).to_matrix();scale=(tb-ta).length/(sb-sa).length
 return sa,ta,rotation*scale
ARM={}
for side in[-1,1]:
 s=(side*.10,0,1.22);e=(side*.25,.005,1.04);w=(side*.323,.005,.887);f=(side*.405,0,.775)
 ids=[15,16,17,21]if side>0 else[23,24,25,29]
 t=[REST[B[i]['name']].translation for i in ids]
 ARM[(side,'upper')]=segment_transform(s,e,t[0],t[1]);ARM[(side,'lower')]=segment_transform(e,w,t[1],t[2]);ARM[(side,'hand')]=segment_transform(w,f,t[2],t[3])
def arm_part(j):
 if j in {56,57,60,58,59,66}:return'upper'
 if j in {61,62,63,64,65,67,68,69,70,71}:return'lower'
 return'hand'
def transformed(source,j):
 x,y,z=source;p=Vector((x,-z,y))
 if j in LEFT_ARM or j in RIGHT_ARM:
  side=1 if j in LEFT_ARM else-1;sa,ta,m=ARM[(side,arm_part(j))];return ta+m@(p-sa)
 xx=x*26
 if j in LEG_POS or j in LEG_NEG:
  side=1 if j in LEG_POS else-1;xx+=side*float(np.interp(y,[0,.1,.46,.84],[2.4,1.8,1.05,.367]))
 return Vector((xx,-z*22,height(y)))
def mapped(j,y):
 if j in HEAD:
  # Long hair follows the original torso below the neck. No hair physics is
  # claimed; the source accessory bones are unavailable in this MOD package.
  if y>=1.27:return[(13,1)]
  if y>=1.08:
   head=.25+.75*(y-1.08)/.19;return[(13,head),(11,1-head)]
  if y>=.9:return[(11,.65),(2,.35)]
  return[(2,.45),(1,.55)]
 if j in {56}:return[(14,.25),(15,.75)]
 if j in {58}:return[(22,.25),(23,.75)]
 if j in {57,60}:return[(15,1)]
 if j in {59,66}:return[(23,1)]
 if j in {61,62,63,64,65}:return[(16,1)]
 if j in {67,68,69,70,71}:return[(24,1)]
 if 75<=j<=91:return[(17,1)]
 if 92<=j<=108:return[(25,1)]
 if j==31:return[(11,1)]
 if j==32:return[(2,.65),(11,.35)]
 if j==33:return[(1,.65),(2,.35)]
 if j in {34,35,36,42,43,44,45,46,47,54}:return[(1,.7),(3,.3)]
 if j in {37,38,39,48,49,50,51,52,53,55}:return[(1,.7),(7,.3)]
 if j==40:return[(3,1)]
 if j==41:return[(7,1)]
 if j==73:return[(4,1)]
 if j==72:return[(8,1)]
 if j==115:return[(5,1)]
 if j==116:return[(9,1)]
 if j==118:return[(6,1)]
 if j==117:return[(10,1)]
 if j in range(109,115):return[(1,1)]
 return[(1,1)]
TP=[];TW=[];TN=[];unknown=set()
for i,source in enumerate(P):
 p=Vector();weights={};total=sum(W[i]);assert abs(total-1)<.001
 for w,j in zip(W[i],J[i]):
  if w<1e-8:continue
  p+=transformed(source,j)*w
  for b,v in mapped(j,source[1]):weights[b]=weights.get(b,0)+v*w
 # Transform the original authored normal by the local inverse-transpose of
 # the same blended rest-space warp; do not smooth across texture/coat seams.
 eps=1e-5;columns=[]
 for axis in range(3):
  q=source.copy();q[axis]+=eps;r=Vector()
  for w,j in zip(W[i],J[i]):
   if w>1e-8:r+=transformed(q,j)*w
  columns.append((r-p)/eps)
 jac=Matrix([tuple(c)for c in columns]).transposed()
 try:n=(jac.inverted().transposed()@Vector(NORMAL[i])).normalized()
 except:n=Vector((NORMAL[i][0],-NORMAL[i][2],NORMAL[i][1])).normalized()
 sorted_w=sorted(weights.items(),key=lambda item:-item[1])[:4];s=sum(w for b,w in sorted_w)
 TP.append(tuple(p));TN.append(tuple(n));TW.append([(b,w/s)for b,w in sorted_w])
# Source texture RGB is kept exact. GI alpha is a material/shader mask, not a
# transparency channel. Image alpha is ignored in both Blender and the Web.
materials=[];spec=[]
for name,roughness in [('HuTaoHeadDiffuse',.85),('HuTaoBodyDiffuse',.88)]:
 im=bpy.data.images.load(os.path.join(SRC,name+'.dds'),check_existing=True);_=tuple(im.size);im.alpha_mode='NONE';im.file_format='PNG';im.filepath_raw=os.path.join(OUT,'textures',name+'.png');im.save()
 m=bpy.data.materials.new(name);m.use_nodes=True;bs=m.node_tree.nodes.get('Principled BSDF');bs.inputs['Roughness'].default_value=roughness;tex=m.node_tree.nodes.new('ShaderNodeTexImage');tex.image=im;tex.extension='EXTEND';m.node_tree.links.new(tex.outputs['Color'],bs.inputs['Base Color']);materials.append(m)
 spec.append(dict(name=name,texture='textures/'+name+'.png',twoSide=True,alpha=False,opacity=1,roughness=roughness,metalness=0))
# Preserve the face texture as a documented pending dependency; it is NOT
# assigned to the wrong hair triangles to hide the absent native face mesh.
face=bpy.data.images.load(os.path.join(SRC,'HuTaoFaceHeadDiffuse.dds'),check_existing=True);_=tuple(face.size);face.alpha_mode='NONE';face.file_format='PNG';face.filepath_raw=os.path.join(OUT,'textures/HuTaoFaceHeadDiffuse.png');face.save()
mesh=bpy.data.meshes.new('HuTao retargeted buffer mesh');mesh.from_pydata(TP,[],SOURCE_F);mesh.update();ob=bpy.data.objects.new('胡桃 MOD · 缺原脸几何的骨架预览',mesh);bpy.context.collection.objects.link(ob)
for m in materials:mesh.materials.append(m)
ul=mesh.uv_layers.new(name='GIMI UV to Blender')
for poly in mesh.polygons:
 poly.material_index=MI[poly.index];poly.use_smooth=True
 for li in poly.loop_indices:
  u,v=UV[mesh.loops[li].vertex_index];ul.data[li].uv=(u,1-v)
mesh.normals_split_custom_set_from_vertices(TN)
for b in B:ob.vertex_groups.new(name=b['name'])
for i,weights in enumerate(TW):
 for b,w in weights:ob.vertex_groups[b].add([i],w,'REPLACE')
# Export rest geometry before modifiers; the Web consumes the original BNC/AMB.
positions=[round(v,7)for p in TP for v in p];normals=[round(v,7)for p in TN for v in p];si=[];sw=[]
for weights in TW:
 si.extend([b for b,w in weights]+[0]*(4-len(weights)));sw.extend([round(w,7)for b,w in weights]+[0]*(4-len(weights)))
skin=dict(schema=1,coordinateSystem='original-native-Z-up',materials=spec,positions=positions,uvs=[round(v,8)for u,vv in UV for v in(u,1-vv)],skinIndices=si,skinWeights=sw,normals=normals,faces=[dict(material=m,indices=list(f))for f,m in zip(SOURCE_F,MI)],vertexCount=N,triangleCount=len(SOURCE_F))
with open(os.path.join(OUT,'mesh.json'),'w')as f:json.dump(skin,f,separators=(',',':'))
# Actual Blender armature retains all native bone names/indices and dummy data.
C=Matrix.Rotation(-math.pi/2,4,'Z');data=bpy.data.armatures.new('Original p0 30-bone binding');arm=bpy.data.objects.new('p0原骨架 · 胡桃映射',data);bpy.context.collection.objects.link(arm);bpy.context.view_layer.objects.active=arm;arm.select_set(True);ob.select_set(False);bpy.ops.object.mode_set(mode='EDIT')
for e in B:
 b=data.edit_bones.new(e['name']);b.matrix=REST[e['name']]@C;b.length=.8
for e in B:
 parent=resolve(e['parent'])
 if parent in data.edit_bones:data.edit_bones[e['name']].parent=data.edit_bones[parent]
bpy.ops.object.mode_set(mode='OBJECT');arm.show_in_front=True
mod=ob.modifiers.new('Original native p0 skeleton','ARMATURE');mod.object=arm;ob.parent=arm
for e in D:
 empty=bpy.data.objects.new(e['name'],None);bpy.context.collection.objects.link(empty);empty.empty_display_type='ARROWS';empty.empty_display_size=.5;empty.matrix_world=REST[e['name']];empty.parent=arm;empty.hide_render=True;empty['native_parent']=e['parent'];empty['native_bind']=e
# Pose with explicit source world matrices, updating parents before children.
def pose_frame(source,frame):
 path=os.path.join(ROOT,'dist/assets/original/characters/common/character.amb')if source==0 else os.path.join(ROOT,'dist/assets/original/characters/p0/p0.amb');raw=open(path,'rb').read();nb,nd,nf,fps=struct.unpack_from('<4i',raw,5);o=21+frame*(20+nb*16+nd*33)
 local={e['name']:dict(e)for e in entries};r=struct.unpack_from('<3f',raw,o+8);local[B[0]['name']]['position']=[0,0,r[2]]
 for i,e in enumerate(B):local[e['name']]['quaternion']=struct.unpack_from('<4f',raw,o+20+i*16)
 ds=o+20+nb*16
 for i,e in enumerate(D):
  k=ds+i*33;local[e['name']]['parent']=raw[k:k+5].decode().rstrip('\0');local[e['name']]['position']=list(struct.unpack_from('<3f',raw,k+5));local[e['name']]['quaternion']=struct.unpack_from('<4f',raw,k+17)
  if e['name']=='d_base':local[e['name']]['position']=e['position']
 world={}
 def calc(name):
  if name in world:return world[name]
  e=local[name];q=Quaternion(e['quaternion']);q.normalize();m=Matrix.Translation(Vector(e['position']))@q.to_matrix().to_4x4();parent=resolve(e['parent']);world[name]=calc(parent)@m if parent else m;return world[name]
 for e in entries:calc(e['name'])
 for e in B:
  pb=arm.pose.bones[e['name']];pb.rotation_mode='QUATERNION';pb.matrix=world[e['name']]@C;bpy.context.view_layer.update()
 error=max(sum(abs(x-y)for row1,row2 in zip(arm.pose.bones[e['name']].matrix,world[e['name']]@C)for x,y in zip(row1,row2))for e in B)
 return error
pose_error=pose_frame(0,246) # native sword stance frame, checked below
# Source native stance 6 start is taken from the original POS, not invented.
pos_text=open(os.path.join(ROOT,'dist/assets/native/combat/P0.POS'),encoding='big5').read();match=__import__('re').search(r'^Pose\s+6\b[^\r\n]*\r?\n\s*\{(.*?)\n\}',pos_text,__import__('re').M|__import__('re').S)
if match:
 start=__import__('re').search(r'^\s*Start\s+(\d+)',match[1],__import__('re').M|__import__('re').I);src=__import__('re').search(r'^\s*source\s+(\d+)',match[1],__import__('re').M|__import__('re').I)
 if start:pose_error=pose_frame(int(src[1]) if src else 0,int(start[1]))
manifest=dict(schema=1,characterId=0,appearance='hutao',label='胡桃 · MOD适配预览',mesh='mesh.json',complete=False,completeness=dict(bodyGeometry=True,headHairGeometry=True,eyes=True,faceGeometry=False,originalGenshinSkeleton=False),incompleteReason='此GIMI MOD未包含原神原生脸部几何；只有眼虹膜、帽发和身体，暂不能作为完整人物启用。',stats=dict(sourceVertices=14672,sourceTriangles=17361,vertices=N,triangles=len(SOURCE_F),bones=30,dummies=6,bodyDiffuse=[4096,4096],headDiffuse=[1024,1024]),retarget=dict(method='Semantic source bone-group mapping plus anatomical A-pose to p0 T-pose rest-space warp; original p0 BNC/AMB drives exported skin.',provisional=True,sourceSkeletonMissing=True,hairPhysics=False,fingerArticulation='hand-bound approximation'),provenance=dict(source='User-provided HuTaoMod4K; original files read-only. No injection code executed.',textures='Blender lossless BC7 DDS RGB decode to PNG; GI alpha masks ignored for opacity, LightMap/MetalMap not misused as PBR normal maps.',face='No invented/replacement face added. Original face texture retained as pending dependency.',limits=['Incomplete face geometry','Original Genshin bone hierarchy and bind matrices absent','Retarget and cloth/hair are a first-pass approximation, not Genshin animation or physics']),sourceBuffers=[dict(file=name,bytes=os.path.getsize(os.path.join(SRC,name)),sha256=hashlib.sha256(read(name)).hexdigest())for name in['HuTaoPosition.buf','HuTaoBlend.buf','HuTaoTexcoord.buf','HuTaoHead.ib','HuTaoBody.ib','HuTao.ini']])
with open(os.path.join(OUT,'manifest.json'),'w')as f:json.dump(manifest,f,ensure_ascii=False,indent=2)
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=24;scene.cycles.use_denoising=True;scene.world.color=(.2,.2,.2);scene.view_settings.view_transform='Standard';scene.render.resolution_x=1000;scene.render.resolution_y=1200;scene.render.resolution_percentage=100
for loc,power,size in[((40,-65,75),18000,55),((-40,-30,45),10000,45),((0,40,60),18000,45)]:
 bpy.ops.object.light_add(type='AREA',location=loc);light=bpy.context.object;light.data.energy=power;light.data.size=size;light.rotation_euler=(Vector((0,0,20))-light.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add(location=(27,-110,44));camera=bpy.context.object;camera.data.type='ORTHO';camera.data.ortho_scale=48;camera.rotation_euler=(Vector((0,0,20))-camera.location).to_track_quat('-Z','Y').to_euler();scene.camera=camera
if not options.skip_render:
 scene.render.filepath=os.path.join(WORK,'retargeted-stance.png');bpy.ops.render.render(write_still=True)
 camera.location=(0,-85,35);camera.rotation_euler=(Vector((0,0,34))-camera.location).to_track_quat('-Z','Y').to_euler();camera.data.ortho_scale=13;scene.render.resolution_x=1000;scene.render.resolution_y=1000;scene.render.filepath=os.path.join(WORK,'retargeted-face-incomplete.png');bpy.ops.render.render(write_still=True)
for im in bpy.data.images:
 if im.source=='FILE':
  try:im.pack()
  except:pass
scene['README']='User MOD geometry reconstructed; missing native face geometry is deliberately not fabricated. Runtime preview manifest complete=false. Retarget uses p0 skeleton, semantic group mapping, no original Genshin rig or physics.'
arm['native_rest_entries']=json.dumps(entries);arm['retarget_method']=manifest['retarget']['method'];arm['source_skeleton_missing']=True
bpy.ops.wm.save_as_mainfile(filepath=os.path.join(WORK,'胡桃-MOD骨架适配-缺原生脸.blend'))
with open(os.path.join(WORK,'build-evidence.json'),'w')as f:json.dump(dict(blender=bpy.app.version_string,manifest=manifest,blenderPoseMatrixError=pose_error,outputHashes={name:hashlib.sha256(open(os.path.join(OUT,name),'rb').read()).hexdigest()for name in['manifest.json','mesh.json']}),f,ensure_ascii=False,indent=2)
print('EXPORTED',manifest['stats'],'BLENDER_POSE_ERROR',pose_error,flush=True)
