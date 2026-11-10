"""Local-only conversion of user-supplied complete Hu Tao PMX to native p0 skin.
Read-only source assets, no imported executable plugins. Rebuild with Blender -b
--factory-startup --python scripts/blender/build_hutao_pmx.py [-- --skip-render].
"""
import bpy,sys,os,json,math,hashlib,shutil,argparse
from pathlib import Path
from mathutils import Vector,Matrix,Quaternion
import numpy as np
sys.path.insert(0,os.path.dirname(__file__))
from pmx_reader import PMXReader
from hutao_native_rest import B,D,entries,world as REST,resolve
ROOT=Path(__file__).resolve().parents[2];SRC=Path('/Users/dulinfeng/Downloads/胡桃喵_by_摸鱼大水怪_0a83a5cf9e74a157fa2c751ce7b84384');WORK=ROOT/'work/hutao-pmx-model';OUT=ROOT/'dist/assets/enhanced/hutao'
for p in[WORK,OUT,OUT/'textures']:p.mkdir(parents=True,exist_ok=True)
# Archive superseded partial GIMI textures locally; keep runtime assets lean.
archive=WORK/'old-incomplete-textures';archive.mkdir(exist_ok=True)
for stale in (OUT/'textures').glob('HuTao*.png'):shutil.move(str(stale),str(archive/stale.name))
a=argparse.ArgumentParser();a.add_argument('--skip-render',action='store_true');opt=a.parse_args(sys.argv[sys.argv.index('--')+1:]if'--'in sys.argv else[])
pmx=PMXReader(SRC/'胡桃喵1.0.pmx').parse();N=len(pmx.vertices);byname={b['name']:b for b in pmx.bones}
(WORK/'source-audit.json').write_text(json.dumps(pmx.summary(),ensure_ascii=False,indent=2))
(WORK/'原模型使用说明.txt').write_text(pmx.comment,encoding='utf-8')
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
def source_point(p):return Vector((p[0],p[2],p[1])) # PMX is left-handed Y-up, authored face points -Z.
def bp(name):return source_point(byname[name]['position'])
def target(i):return REST[B[i]['name']].translation
H_Y=[-.032,.836,5.872,10.712,15.4597,16.2583,19.3258];H_Z=[0,2.1424,10.8188,20.2633,31.787,33.2429,39.4]
D_Y=[.836,10.712,13.2586,15.4597,16.2583,19.3258];D_S=[.135,-.47176,-.65543,-.004875,-.13828,-.13828];D_T=[1.122,.0594,.1761,.29493,.11498,.11498]
def body(p):
 x,y,z=p;dep=float(np.interp(z,D_Y,[t-s*2.1 for s,t in zip(D_S,D_T)]));return Vector((x*2.4,y*2.1+dep,float(np.interp(z,H_Y,H_Z))))
def segment(sa,sb,ta,tb,scale=None):
 axis=(sb-sa).normalized();dest=(tb-ta).normalized();rot=axis.rotation_difference(dest).to_matrix();factor=(tb-ta).length/(sb-sa).length if scale is None else scale;return sa,ta,rot*factor
ARMS={};LEGS={}
for side,offset in [('左',0),('右',8)]:
 ARMS[(side,'upper')]=segment(bp(side+'腕'),bp(side+'ひじ'),target(15+offset),target(16+offset))
 ARMS[(side,'lower')]=segment(bp(side+'ひじ'),bp(side+'手首'),target(16+offset),target(17+offset))
 ARMS[(side,'hand')]=segment(bp(side+'手首'),bp(side+'中指３'),target(17+offset),target(21+offset),2.05)
for side,offset in [('左',0),('右',4)]:
 LEGS[(side,'thigh')]=segment(bp(side+'足D'),bp(side+'ひざD'),target(3+offset),target(4+offset))
 LEGS[(side,'calf')]=segment(bp(side+'ひざD'),bp(side+'足首D'),target(4+offset),target(5+offset))
 LEGS[(side,'foot')]=segment(bp(side+'足首D'),bp(side+'足先EX'),target(5+offset),target(6+offset),2.1)
def classify(j):
 n=pmx.bones[j]['name'];side='左' if n.startswith('左')else'右'if n.startswith('右')else None
 if side:
  if any(s in n for s in['親指','人指','中指','薬指','小指','手首']):return('arm',side,'hand')
  if '手捩'in n or 'ひじ'in n:return('arm',side,'lower')
  if '腕'in n:return('arm',side,'upper')
  if '足首'in n or 'つま先'in n or '足先'in n:return('leg',side,'foot')
  if 'ひざ'in n:return('leg',side,'calf')
  if n in[side+'足',side+'足D']:return('leg',side,'thigh')
 if any(s in n for s in['发','流苏']):return('hair',None,None)
 if '后摆'in n or '带_'in n:return('cloth',side,None)
 if any(s in n for s in['頭','目','歯','齿','耳']):return('head',None,None)
 if n=='首':return('neck',None,None)
 if n=='上半身2':return('torso',None,None)
 if n in['上半身','上半身3']:return('spine',None,None)
 if side and'肩'in n:return('clavicle',side,None)
 return('pelvis',None,None)
CLASS=[classify(i)for i in range(len(pmx.bones))]
def transform(p,j):
 kind,side,part=CLASS[j]
 if kind in['arm','leg']:
  sa,ta,m=(ARMS if kind=='arm'else LEGS)[(side,part)];return ta+m@(p-sa)
 if kind=='head':return target(13)+(p-bp('頭'))*2.1
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
 if kind=='leg':return[(dict(thigh=3,calf=4,foot=5)[part]+(0 if side=='左'else 4),1)]
 if kind=='head':return[(13,1)]
 if kind=='neck':return torso_weights(p)
 if kind=='clavicle':return[(14+off,1)]
 if kind in['torso','spine','pelvis']:return torso_weights(p)
 if kind=='hair':
  # Preserve long tails without claiming MMD rigid-body physics. Their upper
  # portion follows the head; lower lengths blend toward the torso/pelvis.
  y=p.z
  if y>=15.4:return[(13,1)]
  if y>=13.3:
   w=(y-13.3)/2.1;return[(13,w),(11,1-w)]
  if y>=10.7:
   w=(y-10.7)/2.6;return[(11,w),(1,1-w)]
  return[(1,1)]
 if kind=='cloth':
  if p.z>=10.7:return torso_weights(p)
  leg=3 if p.x>=0 else 7;w=max(0,min(.3,(10.7-p.z)/15));return[(1,1-w),(leg,w)]
 return[(1,1)]
TP=[];TN=[];TW=[];UV=[];eps=1e-4
for v in pmx.vertices:
 src=source_point(v['position']);n=source_point(v['normal']);infs=[(j,w)for j,w in zip(v['joints'],v['weights'])if w>1e-8 and j>=0];tot=sum(w for j,w in infs);assert abs(tot-1)<.001
 p=sum((transform(src,j)*w for j,w in infs),Vector());weights={}
 for j,w in infs:
  for k,a in influence(j,src):weights[k]=weights.get(k,0)+a*w
 cols=[]
 for axis in range(3):
  q=src.copy();q[axis]+=eps;r=sum((transform(q,j)*w for j,w in infs),Vector());cols.append((r-p)/eps)
 jac=Matrix([tuple(c)for c in cols]).transposed()
 try:nn=(jac.inverted().transposed()@n).normalized()
 except:nn=n.normalized()
 weights=sorted(weights.items(),key=lambda p:-p[1])[:4];total=sum(w for j,w in weights)
 TP.append(tuple(p));TN.append(tuple(nn));TW.append([(j,w/total)for j,w in weights]);UV.append((v['uv'][0],1-v['uv'][1]))
# Ordinary color maps only. MMD additive sphere-map overlay is a renderer pass,
# not independent geometry: omit its 3340 identical triangles to avoid z-fight.
kept=[];faces=[];MI=[];spec=[];materials=[];cursor=0;omitted=[];source_hashes=[]
for source_mi,m in enumerate(pmx.materials):
 inds=pmx.indices[cursor:cursor+m['indexCount']];cursor+=m['indexCount']
 if m['name']=='发sp+':omitted.append(dict(material=m['name'],triangles=len(inds)//3,reason='MMD additive sphere/specular overlay duplicates hair triangles; Web PBR uses one surface.'));continue
 mi=len(spec);kept.append(source_mi);tex_index=m['texture'];relative=None;im=None
 if tex_index>=0:
  src=SRC/pmx.textures[tex_index].replace('\\','/');name={0:'face',2:'hair-hat',3:'hair',6:'body',9:'cat-ears'}.get(tex_index,'map-'+str(tex_index))+'.png';dest=OUT/'textures'/name
  if src.suffix.lower()=='.png':shutil.copyfile(src,dest)
  else:
   im=bpy.data.images.load(str(src),check_existing=True);_=tuple(im.size);im.file_format='PNG';im.filepath_raw=str(dest);im.save()
  relative='textures/'+name;im=bpy.data.images.load(str(dest),check_existing=True);im.alpha_mode='NONE';_=tuple(im.size)
  if not any(x['file']==str(src.relative_to(SRC))for x in source_hashes):source_hashes.append(dict(file=str(src.relative_to(SRC)),sha256=hashlib.sha256(src.read_bytes()).hexdigest(),size=list(im.size)))
 mat=bpy.data.materials.new(m['name']);mat.use_nodes=True;bs=mat.node_tree.nodes.get('Principled BSDF');bs.inputs['Base Color'].default_value=(*m['diffuse'][:3],1);bs.inputs['Roughness'].default_value=.88;bs.inputs['Specular IOR Level'].default_value=.18
 if im:
  tex=mat.node_tree.nodes.new('ShaderNodeTexImage');tex.image=im;mat.node_tree.links.new(tex.outputs['Color'],bs.inputs['Base Color'])
 materials.append(mat);spec.append(dict(name=m['name'],texture=relative or'null',color=list(m['diffuse'][:3]),twoSide=True,transparent=False,opacity=1,roughness=.88,metalness=0))
 for k in range(0,len(inds),3):faces.append((inds[k],inds[k+2],inds[k+1]));MI.append(mi)
mesh=bpy.data.meshes.new('HuTao PMX native-rest surface');mesh.from_pydata(TP,[],faces);mesh.update();ob=bpy.data.objects.new('YS-胡桃 · 完整PMX本地适配',mesh);bpy.context.collection.objects.link(ob)
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
C=Matrix.Rotation(-math.pi/2,4,'Z');data=bpy.data.armatures.new('Native p0 BNC bind');arm=bpy.data.objects.new('YS-胡桃 · 流星p0动作骨架',data);bpy.context.collection.objects.link(arm);bpy.context.view_layer.objects.active=arm;arm.select_set(True);ob.select_set(False);bpy.ops.object.mode_set(mode='EDIT')
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
manifest=dict(schema=1,characterId=0,appearance='hutao',label='YS-胡桃 · 完整模型适配',mesh='mesh.json',complete=True,completeness=dict(bodyGeometry=True,headHairGeometry=True,eyes=True,faceGeometry=True,originalGenshinSkeleton=False,sourcePmxSkeleton=True),stats=dict(sourceVertices=N,sourceTriangles=len(pmx.indices)//3,vertices=N,triangles=len(faces),sourceBones=len(pmx.bones),bones=30,dummies=6,textures=5,textureResolution=[2048,2048],omittedTriangles=sum(x['triangles']for x in omitted)),retarget=dict(method='Japanese PMX bone semantics and source joint positions map limbs to p0 BNC; continuous native-height torso weights avoid short PMX joint spacing shear. Original AMB drives 30 bones.',provisional=True,sourceSkeletonMissing=False,hairPhysics=False,clothPhysics=False,fingerArticulation='PMX fingers follow native hands; no full MMD finger/morph/IK simulation'),provenance=dict(source='User-provided complete 胡桃喵1.0.pmx; source files read-only; no third-party plugin executed.',modelProvidedBy='miHoYo',modelAdaptedBy='观海 (PMX embedded readme); 摸鱼大水怪 (user folder attribution)',face='Complete authored PMX face, mouth, teeth, lashes, eyebrows and eyes retained; no face parts extracted into another model.',textures='Five original 2048x2048 PNG color maps, original PMX UVs retained; incompatible earlier 4K GIMI maps are not mixed.',license='Embedded model instructions: noncommercial, no redistribution or extraction of parts for other models. Conversion retained locally.',limits=['First-pass native p0 animation retarget','No MMD/Genshin hair, cloth or rigid-body physics','No MMD facial morph or finger simulation','MMD additive sphere-map pass represented by normal Web material specular, not a duplicate mesh']),omittedRenderPasses=omitted,sourceFiles=[dict(file=pmx.path.name,bytes=pmx.path.stat().st_size,sha256=hashlib.sha256(pmx.data).hexdigest())]+source_hashes)
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
arm['native_rest_entries']=json.dumps(entries);arm['native_C_rotation']=-math.pi/2;arm['README']='Complete local PMX body and face; exact p0 native bind and four editable AMB action samples. Jump clip has native local hip motion; browser host applies world jump arc. No MMD/Genshin physics/morph implementation.'
scene['source_model_readme']=pmx.comment;scene['source_folder_attribution']='摸鱼大水怪';scene['local_use_only']=True
bpy.ops.wm.save_as_mainfile(filepath=str(WORK/'胡桃喵-完整模型-流星动作适配.blend'))
(WORK/'build-evidence.json').write_text(json.dumps(dict(blender=bpy.app.version_string,restMatrixError=rest_error,poseMatrixError=pose_error,bakedActions=[dict(name=a.name,frames=n)for a,n in clips],manifest=manifest,hashes={n:hashlib.sha256((OUT/n).read_bytes()).hexdigest()for n in['manifest.json','mesh.json']}),ensure_ascii=False,indent=2))
print('READY',manifest['stats'],'REST',rest_error,'POSE',pose_error,flush=True)
