"""Local-only conversion of user-supplied complete Emilia PMX to native p0 skin.
Read-only source assets, no imported executable plugins. Rebuild with Blender -b
--factory-startup --python scripts/blender/build_emilia_pmx.py [-- --skip-render].
"""
import bpy,sys,os,json,math,hashlib,shutil,argparse
from pathlib import Path
from mathutils import Vector,Matrix,Quaternion
import numpy as np
sys.path.insert(0,os.path.dirname(__file__))
from pmx_reader import PMXReader
from hutao_native_rest import B,D,entries,world as REST,resolve
ROOT=Path(__file__).resolve().parents[2];SRC=Path('/Users/dulinfeng/Downloads/Emilia_v1');WORK=ROOT/'work/emilia-pmx-model';OUT=ROOT/'dist/assets/enhanced/emilia'
for p in[WORK,OUT,OUT/'textures']:p.mkdir(parents=True,exist_ok=True)
a=argparse.ArgumentParser();a.add_argument('--skip-render',action='store_true');opt=a.parse_args(sys.argv[sys.argv.index('--')+1:]if'--'in sys.argv else[])
pmx=PMXReader(SRC/'Emilia_v1.pmx').parse();N=len(pmx.vertices);byname={b['name']:b for b in pmx.bones}
(WORK/'source-audit.json').write_text(json.dumps(pmx.summary(),ensure_ascii=False,indent=2))
(WORK/'原模型使用说明.txt').write_text(pmx.comment,encoding='utf-8')
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
# All rest mapping is derived from this model's own joints, not the HuTao body.
def source_point(p):return Vector((p[0],p[2],p[1]))
def bp(name):return source_point(byname[name]['position'])
def target(i):return REST[B[i]['name']].translation
SOURCE_FLOOR=min(v['position'][1]for v in pmx.vertices)
SOURCE_TOP=max(v['position'][1]for v in pmx.vertices)
HIP_Y=(bp('左足').z+bp('右足').z)/2
HEAD_SCALE=(39.4-target(13).z)/(SOURCE_TOP-bp('頭').z)
BODY_WIDTH=(abs(target(15).x)+abs(target(23).x))/(abs(bp('左腕').x)+abs(bp('右腕').x))
height_pairs=[(SOURCE_FLOOR,0),((bp('左足首').z+bp('右足首').z)/2,(target(5).z+target(9).z)/2),((bp('左ひざ').z+bp('右ひざ').z)/2,(target(4).z+target(8).z)/2),(HIP_Y,target(1).z),(bp('上半身b').z,target(2).z),(bp('上半身2').z,target(11).z),(bp('首').z,target(12).z),(bp('頭').z,target(13).z),(SOURCE_TOP,39.4)]
H_Y=[a for a,b in height_pairs];H_Z=[b for a,b in height_pairs]
depth_pairs=[(bp(name).z,target(index).y-bp(name).y*HEAD_SCALE)for name,index in[('下半身',1),('上半身b',2),('上半身2',11),('首',12),('頭',13)]]
def body(p):
 x,y,z=p;dep=float(np.interp(z,[a for a,b in depth_pairs],[b for a,b in depth_pairs]));return Vector((x*BODY_WIDTH,y*HEAD_SCALE+dep,float(np.interp(z,H_Y,H_Z))))
def segment(sa,sb,ta,tb,scale=None):
 axis=(sb-sa).normalized();dest=(tb-ta).normalized();rot=axis.rotation_difference(dest).to_matrix();factor=(tb-ta).length/(sb-sa).length if scale is None else scale;return sa,ta,rot*factor
ARMS={};LEGS={}
for side,offset in [('左',0),('右',8)]:
 ARMS[(side,'upper')]=segment(bp(side+'腕'),bp(side+'ひじ'),target(15+offset),target(16+offset))
 ARMS[(side,'lower')]=segment(bp(side+'ひじ'),bp(side+'手首'),target(16+offset),target(17+offset))
 ARMS[(side,'hand')]=segment(bp(side+'手首'),bp(side+'中指３'),target(17+offset),target(21+offset),HEAD_SCALE)
for side,offset in [('左',0),('右',4)]:
 LEGS[(side,'thigh')]=segment(bp(side+'足'),bp(side+'ひざ'),target(3+offset),target(4+offset))
 LEGS[(side,'calf')]=segment(bp(side+'ひざ'),bp(side+'足首'),target(4+offset),target(5+offset))
 LEGS[(side,'foot')]=segment(bp(side+'足首'),bp(side+'つま先'),target(5+offset),target(6+offset),HEAD_SCALE)
def ancestors(j):
 seen=set()
 while j>=0 and j not in seen:
  seen.add(j);yield pmx.bones[j]['name'];j=pmx.bones[j]['parent']
def classify(j):
 n=pmx.bones[j]['name'];side='左'if n.startswith('左')else'右'if n.startswith('右')else None
 if 'hair'in n.lower():return('hair',None,None)
 if n.startswith('sleeve'):return('arm','左'if'sleeveL'in n else'右','lower')
 if any(s in n for s in['裙','擺','掛飾','skirt']):return('cloth',side,None)
 if side:
  if '肩'in n:return('clavicle',side,None)
  if any(s in n for s in['親指','人指','中指','薬指','小指','手首','ダミー']):return('arm',side,'hand')
  if '手捩'in n or 'ひじ'in n:return('arm',side,'lower')
  if '腕'in n:return('arm',side,'upper')
  if '足首'in n or 'つま先'in n or '足先'in n:return('leg',side,'foot')
  if 'ひざ'in n:return('leg',side,'calf')
  if n in[side+'足',side+'足D']:return('leg',side,'thigh')
 if '頭'in list(ancestors(j))or any(s in n for s in['目','歯','齿','齒','耳']):return('head',None,None)
 if n=='首':return('neck',None,None)
 return('torso',None,None)
CLASS=[classify(i)for i in range(len(pmx.bones))]
def transform(p,j):
 kind,side,part=CLASS[j]
 if kind in['arm','leg']:
  sa,ta,m=(ARMS if kind=='arm'else LEGS)[(side,part)];result=ta+m@(p-sa)
  if kind=='leg'and part=='thigh':
   span=(HIP_Y-(bp('左ひざ').z+bp('右ひざ').z)/2)*.55;t=max(0,min(1,(HIP_Y-p.z)/span));return body(p)*(1-t)+result*t
  return result
 if kind in['head','hair']:return target(13)+(p-bp('頭'))*HEAD_SCALE
 return body(p)
def torso_weights(p):
 z=body(p).z;anchors=[(target(i).z,i)for i in[1,2,11,12,13]]
 if z<=anchors[0][0]:return[(anchors[0][1],1)]
 for (lo,a),(hi,b)in zip(anchors,anchors[1:]):
  if z<=hi:
   t=(z-lo)/(hi-lo);return[(a,1-t),(b,t)]
 return[(13,1)]
def influence(j,p):
 kind,side,part=CLASS[j];off=0 if side=='左'else 8
 if kind=='arm':return[(dict(upper=15,lower=16,hand=17)[part]+off,1)]
 if kind=='leg':
  bone=dict(thigh=3,calf=4,foot=5)[part]+(0 if side=='左'else 4)
  if part=='thigh':
   span=(HIP_Y-(bp('左ひざ').z+bp('右ひざ').z)/2)*.55;t=max(0,min(1,(HIP_Y-p.z)/span));return[(bone,t)]+[(j,w*(1-t))for j,w in torso_weights(p)]
  return[(bone,1)]
 if kind=='head':return[(13,1)]
 if kind=='clavicle':return[(14+off,1)]
 if kind in['torso','neck']:return torso_weights(p)
 if kind=='hair':
  # A first-pass rigid head-bound tail keeps the long authored chain coherent;
  # mixing these vertices across head/spine made attack poses stretch like rubber.
  return[(13,1)]
 if kind=='cloth':
  if p.z>=HIP_Y:return torso_weights(p)
  knee=(bp('左ひざ').z+bp('右ひざ').z)/2;t=max(0,min(.65,(HIP_Y-p.z)/(HIP_Y-knee)*.65));left=max(0,min(1,(p.x/(abs(bp('左足').x)*1.8)+1)/2))
  return[(1,1-t),(3,t*left),(7,t*(1-left))]
 return torso_weights(p)
HEAD_MATERIALS={'Face','Face_NoOutline','EYEBROW','Hair','HairFront','FlowerAcc'}
HEAD_VERTICES=set();CLOTH_VERTICES=set();cursor=0
for m in pmx.materials:
 if m['name']in HEAD_MATERIALS:HEAD_VERTICES.update(pmx.indices[cursor:cursor+m['indexCount']])
 if m['name']=='Cloth':CLOTH_VERTICES.update(pmx.indices[cursor:cursor+m['indexCount']])
 cursor+=m['indexCount']
TP=[];TN=[];TW=[];UV=[];eps=1e-4
for vi,v in enumerate(pmx.vertices):
 src=source_point(v['position']);n=source_point(v['normal']);infs=[(j,w)for j,w in zip(v['joints'],v['weights'])if w>1e-8 and j>=0];tot=sum(w for j,w in infs);assert abs(tot-1)<.001
 if vi in HEAD_VERTICES:
  p=target(13)+(src-bp('頭'))*HEAD_SCALE;nn=n.normalized();weights=[(13,1)]
 else:
  p=sum((transform(src,j)*w for j,w in infs),Vector());acc={}
  for j,w in infs:
   for k,a in influence(j,src):acc[k]=acc.get(k,0)+a*w
  cols=[]
  for axis in range(3):
   q=src.copy();q[axis]+=eps;r=sum((transform(q,j)*w for j,w in infs),Vector());cols.append((r-p)/eps)
  jac=Matrix([tuple(c)for c in cols]).transposed()
  try:nn=(jac.inverted().transposed()@n).normalized()
  except:nn=n.normalized()
  weights=sorted(acc.items(),key=lambda p:-p[1])[:4];total=sum(w for j,w in weights);weights=[(j,w/total)for j,w in weights]
 # A fabric bridge near the back/crotch midline cannot follow both thighs
 # independently during a split-leg jump. Blend this common cloth patch to
 # the pelvis/torso, using source-space height and a smooth midline falloff.
 if vi in CLOTH_VERTICES:
  thigh_span=HIP_Y-(bp('左ひざ').z+bp('右ひざ').z)/2;hip_width=abs(bp('左足').x)
  y=max(0,min(1,(src.z-(HIP_Y-thigh_span*.55))/(thigh_span*.15)))
  x=max(0,min(1,(abs(src.x)-hip_width*.25)/(hip_width*.65)))
  left=sum(w for j,w in infs if CLASS[j][0]=='leg'and CLASS[j][1]=='左')
  right=sum(w for j,w in infs if CLASS[j][0]=='leg'and CLASS[j][1]=='右')
  total_leg=left+right;shared=4*left*right/(total_leg*total_leg)if total_leg>1e-8 else 0
  bridge=(y*y*(3-2*y))*(1-x*x*(3-2*x))*shared
  if bridge>0:
   acc={j:w*(1-bridge)for j,w in weights}
   for j,w in torso_weights(src):acc[j]=acc.get(j,0)+w*bridge
   weights=sorted(acc.items(),key=lambda item:-item[1])[:4];total=sum(w for j,w in weights);weights=[(j,w/total)for j,w in weights]
 TP.append(tuple(p));TN.append(tuple(nn));TW.append(weights);UV.append((v['uv'][0],1-v['uv'][1]))

# SHADING duplicates all Cloth/Skin geometry and authored UVs (independent
# nearest audit max position/UV difference 1.907e-6 and identical weights).
# Bake its transparent SDW color overlay into CLOTH once; do not render two
# coincident physical surfaces or misinterpret SDW as a normal/roughness map.
cloth=bpy.data.images.load(str(SRC/'tex/CLOTH.png'),check_existing=True)
sdw=bpy.data.images.load(str(SRC/'tex/SDW.png'),check_existing=True)
assert tuple(cloth.size)==tuple(sdw.size)
w,h=cloth.size
base=np.asarray(cloth.pixels[:],dtype=np.float32).reshape(h,w,4)
shade=np.asarray(sdw.pixels[:],dtype=np.float32).reshape(h,w,4)
combined=base.copy();combined[:,:,:3]=shade[:,:,:3]*shade[:,:,3:4]+base[:,:,:3]*(1-shade[:,:,3:4]);combined[:,:,3]=1
composed=bpy.data.images.new('Authored CLOTH + transparent SDW',width=w,height=h,alpha=True)
composed.colorspace_settings.name='sRGB';composed.pixels.foreach_set(combined.ravel());composed.file_format='PNG';composed.filepath_raw=str(OUT/'textures/cloth-composed.png');composed.save()
source_hashes=[dict(file=str(p.relative_to(SRC)),sha256=hashlib.sha256(p.read_bytes()).hexdigest(),size=list(bpy.data.images.load(str(p),check_existing=True).size))for p in sorted((SRC/'tex').glob('*.png'))]
kept=[];faces=[];MI=[];spec=[];materials=[];cursor=0;omitted=[]
for source_mi,m in enumerate(pmx.materials):
 inds=pmx.indices[cursor:cursor+m['indexCount']];cursor+=m['indexCount']
 if m['name']=='SHADING':
  omitted.append(dict(material=m['name'],triangles=len(inds)//3,reason='Coincident Cloth+Skin alpha-color overlay, baked from original SDW over CLOTH; exact matched triangles under 1.907e-6 position/UV tolerance.'));continue
 mi=len(spec);kept.append(source_mi);tex_index=m['texture'];relative=None;im=None
 if tex_index>=0:
  src=SRC/pmx.textures[tex_index].replace('\\','/');name={0:'cloth-composed',2:'face',3:'hair',4:'accessories'}[tex_index]+'.png';dest=OUT/'textures'/name
  if tex_index!=0:shutil.copyfile(src,dest)
  relative='textures/'+name;im=bpy.data.images.load(str(dest),check_existing=True);im.alpha_mode='NONE';_=tuple(im.size)
 mat=bpy.data.materials.new(m['name']);mat.use_nodes=True;bs=mat.node_tree.nodes.get('Principled BSDF');bs.inputs['Base Color'].default_value=(*m['diffuse'][:3],1);bs.inputs['Roughness'].default_value=.88;bs.inputs['Specular IOR Level'].default_value=.18
 if im:
  tex=mat.node_tree.nodes.new('ShaderNodeTexImage');tex.image=im;mat.node_tree.links.new(tex.outputs['Color'],bs.inputs['Base Color'])
 materials.append(mat);spec.append(dict(name=m['name'],sourceName=m['name'],texture=relative or'null',color=list(m['diffuse'][:3]),twoSide=True,transparent=False,opacity=1,alphaTest=0,depthWrite=True,roughness=.88,metalness=0))
 for k in range(0,len(inds),3):faces.append((inds[k],inds[k+2],inds[k+1]));MI.append(mi)
mesh=bpy.data.meshes.new('Emilia PMX native-rest surface');mesh.from_pydata(TP,[],faces);mesh.update();ob=bpy.data.objects.new('RE0-爱蜜莉雅 · 完整PMX本地适配',mesh);bpy.context.collection.objects.link(ob)
for m in materials:mesh.materials.append(m)
ul=mesh.uv_layers.new(name='PMX authored UV')
for p in mesh.polygons:
 p.material_index=MI[p.index];p.use_smooth=True
 for li in p.loop_indices:ul.data[li].uv=UV[mesh.loops[li].vertex_index]
mesh.normals_split_custom_set_from_vertices(TN)
for b in B:ob.vertex_groups.new(name=b['name'])
si=[];sw=[]
for i,weights in enumerate(TW):
 for j,w in weights:ob.vertex_groups[j].add([i],w,'REPLACE')
 si.extend([j for j,w in weights]+[0]*(4-len(weights)));sw.extend([round(w,7)for j,w in weights]+[0]*(4-len(weights)))
skin=dict(schema=1,coordinateSystem='original-native-Z-up',materials=spec,positions=[round(x,7)for p in TP for x in p],normals=[round(x,7)for p in TN for x in p],uvs=[round(x,8)for p in UV for x in p],skinIndices=si,skinWeights=sw,faces=[dict(material=m,indices=list(f))for m,f in zip(MI,faces)],vertexCount=N,triangleCount=len(faces))
(OUT/'mesh.json').write_text(json.dumps(skin,separators=(',',':')))
# An edit bone must have a valid head/tail before orientation can be retained.
C=Matrix.Rotation(-math.pi/2,4,'Z');data=bpy.data.armatures.new('Native p0 BNC bind');arm=bpy.data.objects.new('RE0-爱蜜莉雅 · 流星p0动作骨架',data);bpy.context.collection.objects.link(arm);bpy.context.view_layer.objects.active=arm;arm.select_set(True);ob.select_set(False);bpy.ops.object.mode_set(mode='EDIT')
for e in B:data.edit_bones.new(e['name'])
for e in B:
 parent=resolve(e['parent'])
 if parent in data.edit_bones:data.edit_bones[e['name']].parent=data.edit_bones[parent]
for e in B:
 b=data.edit_bones[e['name']];m=REST[e['name']]@C;b.head=m.translation;b.tail=m.translation+m.to_3x3().col[1]*.8;b.align_roll(m.to_3x3().col[2])
bpy.ops.object.mode_set(mode='OBJECT');rest_error=max(abs(x-y)for e in B for a,z in zip(data.bones[e['name']].matrix_local,REST[e['name']]@C)for x,y in zip(a,z));assert rest_error<1e-4,rest_error
mod=ob.modifiers.new('Native BNC/AMB skin','ARMATURE');mod.object=arm;ob.parent=arm;arm.show_in_front=True
for e in D:
 empty=bpy.data.objects.new(e['name'],None);bpy.context.collection.objects.link(empty);empty.empty_display_type='ARROWS';empty.empty_display_size=.5;empty.matrix_world=REST[e['name']];empty.parent=arm;empty.hide_render=True;empty['native_parent']=e['parent'];empty['native_bind']=e
# Same exact native animation sampling as Web, without a different rig bind.
from struct import unpack_from
AMB=[(ROOT/'dist/assets/original/characters/common/character.amb').read_bytes(),(ROOT/'dist/assets/original/characters/p0/p0.amb').read_bytes()]
def pose_frame(source,frame):
 raw=AMB[source];nb,nd,nf,fps=unpack_from('<4i',raw,5);o=21+frame*(20+nb*16+nd*33);local={e['name']:dict(e)for e in entries};r=unpack_from('<3f',raw,o+8);local[B[0]['name']]['position']=[0,0,r[2]]
 for i,e in enumerate(B):local[e['name']]['quaternion']=unpack_from('<4f',raw,o+20+i*16)
 ds=o+20+nb*16
 for i,e in enumerate(D):
  k=ds+i*33;local[e['name']]['parent']=raw[k:k+5].decode().rstrip('\0');local[e['name']]['position']=list(unpack_from('<3f',raw,k+5));local[e['name']]['quaternion']=unpack_from('<4f',raw,k+17)
  if e['name']=='d_base':local[e['name']]['position']=e['position']
 world={}
 def calc(name):
  if name in world:return world[name]
  e=local[name];q=Quaternion(e['quaternion']);q.normalize();m=Matrix.Translation(Vector(e['position']))@q.to_matrix().to_4x4();parent=resolve(e['parent']);world[name]=calc(parent)@m if parent else m;return world[name]
 for e in entries:calc(e['name'])
 for e in B:arm.pose.bones[e['name']].matrix=world[e['name']]@C;bpy.context.view_layer.update()
 return max(abs(x-y)for e in B for a,z in zip(arm.pose.bones[e['name']].matrix,world[e['name']]@C)for x,y in zip(a,z))
# Native sword stance from the game's POS declaration.
import re
pst=(ROOT/'dist/assets/native/combat/P0.POS').read_text(encoding='big5');block=re.search(r'^Pose\s+6\b[^\r\n]*\r?\n\s*\{(.*?)\n\}',pst,re.M|re.S)[1];start=int(re.search(r'^\s*Start\s+(\d+)',block,re.M|re.I)[1]);src=re.search(r'^\s*source\s+(\d+)',block,re.M|re.I);pose_error=pose_frame(int(src[1])if src else 0,start);assert pose_error<1e-3,pose_error
manifest=dict(schema=1,characterId=0,appearance='emilia',label='RE0-爱蜜莉雅 · 完整模型适配',mesh='mesh.json',complete=True,completeness=dict(bodyGeometry=True,headHairGeometry=True,eyes=True,faceGeometry=True,originalSourceGameSkeleton=False,sourcePmxSkeleton=True),stats=dict(sourceVertices=N,sourceTriangles=len(pmx.indices)//3,vertices=N,triangles=len(faces),sourceBones=len(pmx.bones),bones=30,dummies=6,textures=4,sourceTextures=len(source_hashes),textureResolutions=[[2048,2048],[1024,1024],[1024,1024],[512,512]],sourceTextureResolutions=[x['size']for x in source_hashes],usedVertices=len(set(i for f in faces for i in f)),unusedVertices=N-len(set(i for f in faces for i in f)),omittedTriangles=sum(x['triangles']for x in omitted)),retarget=dict(method='Japanese PMX bone semantics and source joint positions map limbs to p0 BNC; continuous native-height torso weights avoid short PMX joint spacing shear. Original AMB drives 30 bones.',provisional=True,sourceSkeletonMissing=False,hairPhysics=False,hairBinding='rigid native head approximation, no hair physics',clothPhysics=False,fingerArticulation='PMX fingers follow native hands; no full MMD finger/morph/IK simulation'),provenance=dict(source='User-provided complete Emilia_v1.pmx; source files read-only; no third-party plugin executed.',sourceGames="Re:Zero Infinity & Witch's Resurrection",modelProvidedBy='Skymoons / Elemental Craft / Kadokawa corp',modelAdaptedBy='chenxs / 陈心舒 (PMX embedded credit)',face='Complete authored PMX face, mouth, teeth, lashes, eyebrows and eyes retained; no face parts extracted into another model.',textures='Authored FACE/HAIR/ACCS colors retained, original transparent SDW shading overlay baked over CLOTH to replace duplicate coincident pass. Four runtime textures from five source PNGs. Hair alpha 229..255 treated opaque, not discarded as cutout.',license='PMX supplies credits but no explicit usage license. Local user-requested conversion only, no upload or redistribution.',limits=['First-pass native p0 animation retarget','No MMD/source-game hair, cloth or rigid-body physics','No MMD facial morph or finger simulation','MMD sphere/toon shading differs from Web PBR']),omittedRenderPasses=omitted,sourceFiles=[dict(file=pmx.path.name,bytes=pmx.path.stat().st_size,sha256=hashlib.sha256(pmx.data).hexdigest())]+source_hashes)
(OUT/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2))
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=24;scene.cycles.use_denoising=True;scene.world.color=(.2,.2,.2);scene.view_settings.view_transform='Standard';scene.render.resolution_x=1000;scene.render.resolution_y=1200;scene.render.resolution_percentage=100
for loc,power,size in[((40,-65,75),20000,55),((-40,-30,45),12000,45),((0,40,60),16000,45)]:
 bpy.ops.object.light_add(type='AREA',location=loc);light=bpy.context.object;light.data.energy=power;light.data.size=size;light.rotation_euler=(Vector((0,0,20))-light.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add(location=(27,-110,44));camera=bpy.context.object;camera.data.type='ORTHO';camera.data.ortho_scale=48;camera.rotation_euler=(Vector((0,0,20))-camera.location).to_track_quat('-Z','Y').to_euler();scene.camera=camera
if not opt.skip_render:
 scene.render.filepath=str(WORK/'retargeted-stance.png');bpy.ops.render.render(write_still=True)
 camera.location=(0,-85,35);camera.rotation_euler=(Vector((0,0,34))-camera.location).to_track_quat('-Z','Y').to_euler();camera.data.ortho_scale=13;scene.render.resolution_x=1000;scene.render.resolution_y=1000;scene.render.filepath=str(WORK/'retargeted-face.png');bpy.ops.render.render(write_still=True)
for im in bpy.data.images:
 if im.source=='FILE':
  try:im.pack()
  except:pass
# Four editable native source actions are baked into the .blend. Web gameplay
# still samples original AMB directly; no baked data is needed by the browser.
clips=[]
for pose_id,label in[(6,'原版持剑待机'),(144,'原版跑步'),(151,'原版跳跃局部姿势'),(262,'原版持剑攻击')]:
 block=re.search(r'^Pose\s+'+str(pose_id)+r'\b[^\r\n]*\r?\n\s*\{(.*?)\n\}',pst,re.M|re.S)[1]
 first=int(re.search(r'^\s*Start\s+(\d+)',block,re.M|re.I)[1]);last=int(re.search(r'^\s*End\s+(\d+)',block,re.M|re.I)[1]);src=re.search(r'^\s*source\s+(\d+)',block,re.M|re.I);source=int(src[1])if src else 0
 arm.animation_data_clear()
 for pb in arm.pose.bones:pb.rotation_mode='QUATERNION'
 for source_frame in range(first,last+1):
  pose_frame(source,source_frame);frame=source_frame-first+1
  for pb in arm.pose.bones:
   pb.keyframe_insert('location',frame=frame,group=pb.name);pb.keyframe_insert('rotation_quaternion',frame=frame,group=pb.name);pb.keyframe_insert('scale',frame=frame,group=pb.name)
 action=arm.animation_data.action;action.name=str(pose_id)+' · '+label;action.use_fake_user=True;action['native_pose_id']=pose_id;action['source']=source;action['source_start']=first;action['source_end']=last;clips.append((action,last-first+1))
arm.animation_data.action=clips[0][0];scene.render.fps=30;scene.frame_start=1;scene.frame_end=clips[0][1];scene.frame_set(1)
arm['native_rest_entries']=json.dumps(entries);arm['native_C_rotation']=-math.pi/2;arm['README']='Complete local PMX body and face; exact p0 native bind and four editable AMB action samples. Jump clip has native local hip motion; browser host applies world jump arc. No MMD/source-game physics/morph implementation.'
scene['source_model_readme']=pmx.comment;scene['source_folder_attribution']='Emilia_v1';scene['local_use_only']=True
bpy.ops.wm.save_as_mainfile(filepath=str(WORK/'爱蜜莉雅-完整模型-流星动作适配.blend'))
(WORK/'build-evidence.json').write_text(json.dumps(dict(blender=bpy.app.version_string,restMatrixError=rest_error,poseMatrixError=pose_error,bakedActions=[dict(name=a.name,frames=n)for a,n in clips],manifest=manifest,hashes={n:hashlib.sha256((OUT/n).read_bytes()).hexdigest()for n in['manifest.json','mesh.json']}),ensure_ascii=False,indent=2))
print('READY',manifest['stats'],'REST',rest_error,'POSE',pose_error,flush=True)
