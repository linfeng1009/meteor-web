"""Build Doubao from the project-owned archive; never depend on Downloads.

Blender --background --factory-startup --disable-autoexec --python scripts/blender/build_doubao.py
Add -- --render to produce a Blender stance preview. Runtime uses only dist/.
"""
import bpy, sys, json, shutil, hashlib, math, argparse
from pathlib import Path
from collections import defaultdict
from mathutils import Vector, Matrix
import numpy as np

sys.path.insert(0, str(Path(__file__).parent))
from pmx_reader import PMXReader
from hutao_native_rest import B, world as REST
from native_character_authoring import make_native_armature, bake_native_samples

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / 'assets/source/doubao'
OUT = ROOT / 'dist/assets/enhanced/doubao'
WORK = ROOT / 'work/doubao-import-2026-11-10'
options = argparse.ArgumentParser(); options.add_argument('--render', action='store_true')
args = options.parse_args(sys.argv[sys.argv.index('--')+1:] if '--' in sys.argv else [])
for path in [OUT, OUT/'textures', WORK]: path.mkdir(parents=True, exist_ok=True)
pmx = PMXReader(SRC/'豆包模型.pmx').parse()
audit = pmx.summary(); audit['source'] = 'assets/source/doubao/豆包模型.pmx'
(WORK/'source-audit.json').write_text(json.dumps(audit, ensure_ascii=False, indent=2))
bpy.ops.object.select_all(action='SELECT'); bpy.ops.object.delete(use_global=False)
byname = {b['name']: b for b in pmx.bones}
def source_point(p): return Vector((p[0], p[2], p[1]))
def bp(name): return source_point(byname[name]['position'])
def target(index): return REST[B[index]['name']].translation
floor, top = audit['bounds'][1]
hip = (bp('左足').z+bp('右足').z)/2
head_scale = (39.4-target(13).z)/(top-bp('頭').z)
width_scale = (abs(target(15).x)+abs(target(23).x))/(abs(bp('左腕').x)+abs(bp('右腕').x))
height_pairs = [(floor,0), ((bp('左足首').z+bp('右足首').z)/2,(target(5).z+target(9).z)/2), ((bp('左ひざ').z+bp('右ひざ').z)/2,(target(4).z+target(8).z)/2), (hip,target(1).z), (bp('上半身').z,target(2).z), (bp('上半身2').z,target(11).z), (bp('首').z,target(12).z), (bp('頭').z,target(13).z), (top,39.4)]
depth_pairs = [(bp(n).z, target(i).y-bp(n).y*head_scale) for n,i in [('下半身',1),('上半身',2),('上半身2',11),('首',12),('頭',13)]]
def body(p):
    depth = float(np.interp(p.z, [a for a,b in depth_pairs], [b for a,b in depth_pairs]))
    return Vector((p.x*width_scale, p.y*head_scale+depth, float(np.interp(p.z,[a for a,b in height_pairs],[b for a,b in height_pairs]))))
def head(p): return target(13)+(p-bp('頭'))*head_scale
def segment(a,b,x,y,scale=None):
    rotation = (b-a).normalized().rotation_difference((y-x).normalized()).to_matrix()
    return a,x,rotation*((y-x).length/(b-a).length if scale is None else scale)
limbs = {}
for side,offset in [('左',0),('右',8)]:
    limbs[side,'upper'] = segment(bp(side+'腕'),bp(side+'ひじ'),target(15+offset),target(16+offset))
    limbs[side,'lower'] = segment(bp(side+'ひじ'),bp(side+'手首'),target(16+offset),target(17+offset))
    limbs[side,'hand'] = segment(bp(side+'手首'),bp(side+'中指３'),target(17+offset),target(21+offset),head_scale)
for side,offset in [('左',0),('右',4)]:
    for part,a,b,x,y in [('thigh','足','ひざ',3,4),('calf','ひざ','足首',4,5),('foot','足首','つま先',5,6)]:
        limbs[side,part] = segment(bp(side+a),bp(side+b),target(x+offset),target(y+offset),head_scale if part=='foot' else None)
def ancestors(index):
    seen=set()
    while index >= 0 and index not in seen:
        seen.add(index); yield pmx.bones[index]['name']; index=pmx.bones[index]['parent']
hair_source = {b['index'] for b in pmx.bones if 'CF_' in b['name'] or '髮' in b['name']}
def classify(index):
    name=pmx.bones[index]['name']; side='左' if name.startswith('左') else '右' if name.startswith('右') else None
    if index in hair_source: return 'hair',None,None
    if side:
        if '肩' in name: return 'clavicle',side,None
        if any(token in name for token in ['親指','人指','中指','薬指','小指','手首','ダミー']): return 'arm',side,'hand'
        if '手捩' in name or 'ひじ' in name: return 'arm',side,'lower'
        if '腕' in name: return 'arm',side,'upper'
        if '足首' in name or 'つま先' in name or '足先' in name: return 'leg',side,'foot'
        if 'ひざ' in name: return 'leg',side,'calf'
        if name in [side+'足',side+'足D']: return 'leg',side,'thigh'
    if '頭' in ancestors(index): return 'head',None,None
    return 'torso',None,None
classes=[classify(i) for i in range(len(pmx.bones))]
ordered=[]
def order(index):
    if index in ordered: return
    parent=pmx.bones[index]['parent']
    if parent in hair_source: order(parent)
    ordered.append(index)
for i in sorted(hair_source): order(i)
hair_indices={original:30+i for i,original in enumerate(ordered)}
hair_bones=[]
for index in ordered:
    b=pmx.bones[index]; position=head(source_point(b['position']))
    child=next((c for c in ordered if pmx.bones[c]['parent']==index),None)
    tail_id=b.get('tailBone')
    if tail_id is not None and 0 <= tail_id < len(pmx.bones): tail=head(source_point(pmx.bones[tail_id]['position']))
    elif child is not None: tail=head(source_point(pmx.bones[child]['position']))
    else: tail=head(source_point([x+y for x,y in zip(b['position'],b.get('tailOffset',[0,0,0]))]))
    if (tail-position).length < .05:
        parent_position=head(source_point(pmx.bones[b['parent']]['position']))
        axis=position-parent_position
        tail=position+(axis.normalized() if axis.length>.05 else Vector((0,0,-1)))*.6
    q=(tail-position).to_track_quat('Y','Z'); parent=hair_indices.get(b['parent'],13)
    depth=0 if parent==13 else hair_bones[parent-30]['depth']+1
    hair_bones.append(dict(name='doubao_spring_'+b['name'],sourceBone=index,sourceName=b['name'],parent=parent,position=list(position),tail=list(tail),rotation=[q.x,q.y,q.z,q.w],depth=depth,stiffness=220 if depth==0 else 150 if depth==1 else 110,damping=30 if depth==0 else 24,maxAngle=.01 if depth==0 else .025,gravity=0 if depth==0 else .003,follow=.98,globalMaxAngle=.04,radius=.08))
def torso_weights(p):
    z=body(p).z; anchors=[(target(i).z,i) for i in [1,2,11,12,13]]
    if z <= anchors[0][0]: return [(anchors[0][1],1)]
    for (lo,a),(hi,b) in zip(anchors,anchors[1:]):
        if z<=hi:
            t=(z-lo)/(hi-lo); return [(a,1-t),(b,t)]
    return [(13,1)]
def transform(p,index):
    kind,side,part=classes[index]
    if kind in ['head','hair']: return head(p)
    if kind in ['arm','leg']:
        a,x,m=limbs[side,part]; result=x+m@(p-a)
        if part=='thigh':
            span=(hip-(bp('左ひざ').z+bp('右ひざ').z)/2)*.55
            t=max(0,min(1,(hip-p.z)/span)); return body(p)*(1-t)+result*t
        return result
    return body(p)
def influence(p,index):
    kind,side,part=classes[index]
    if kind=='hair': return [(hair_indices[index],1)]
    if kind=='head': return [(13,1)]
    if kind=='arm': return [(dict(upper=15,lower=16,hand=17)[part]+(0 if side=='左' else 8),1)]
    if kind=='clavicle': return [(14+(0 if side=='左' else 8),1)]
    if kind=='leg':
        bone=dict(thigh=3,calf=4,foot=5)[part]+(0 if side=='左' else 4)
        if part=='thigh':
            span=(hip-(bp('左ひざ').z+bp('右ひざ').z)/2)*.55;t=max(0,min(1,(hip-p.z)/span))
            return [(bone,t)]+[(j,w*(1-t)) for j,w in torso_weights(p)]
        return [(bone,1)]
    return torso_weights(p)
def smoothstep(lo,hi,value):
    t=max(0,min(1,(value-lo)/(hi-lo))); return t*t*(3-2*t)
# The source's auto binding jumps from a leg to the root across adjacent skirt
# triangles. Detect the authored dark fabric from its unchanged atlas, then
# smooth its influence over the welded surface, including duplicate UV seams.
texture_source=SRC/pmx.textures[0].replace('\\','/')
analysis_image=bpy.data.images.load(str(texture_source),check_existing=False)
analysis_image.colorspace_settings.name='Non-Color';analysis_image.reload()
texture_width,texture_height=analysis_image.size
atlas=np.asarray(analysis_image.pixels[:],dtype=np.float32).reshape(texture_height,texture_width,4)
bpy.data.images.remove(analysis_image)
source_keys=[tuple(round(value,5) for value in v['position']) for v in pmx.vertices]
groups={key:i for i,key in enumerate(dict.fromkeys(source_keys))}
group_ids=np.array([groups[key] for key in source_keys],dtype=np.int32)
raw_cloth=np.zeros(len(pmx.vertices),dtype=np.float64)
coincident_weights=defaultdict(lambda:defaultdict(float))
for i,v in enumerate(pmx.vertices):
    u,t=v['uv'];color=atlas[int((1-t)*texture_height)%texture_height,int(u*texture_width)%texture_width,:3]
    y=v['position'][1]
    raw_cloth[i]=(1-smoothstep(.23,.45,float(color.mean())))*smoothstep(3.9,4.55,y)*(1-smoothstep(6.8,7.4,y))
    for j,w in zip(v['joints'],v['weights']):
        if j>=0 and w>1e-8: coincident_weights[group_ids[i]][j]+=w
counts=np.bincount(group_ids,minlength=len(groups))
cloth=np.bincount(group_ids,weights=raw_cloth,minlength=len(groups))/counts
edge_set=set()
for a,b,c in zip(pmx.indices[::3],pmx.indices[1::3],pmx.indices[2::3]):
    for x,y in [(a,b),(b,c),(c,a)]:
        x,y=sorted((int(group_ids[x]),int(group_ids[y])))
        if x!=y:edge_set.add((x,y))
graph=np.array(list(edge_set),dtype=np.int32)
degree=np.bincount(graph.ravel(),minlength=len(groups));degree=np.maximum(1,degree)
for iteration in range(6):
    neighbors=np.bincount(graph[:,0],weights=cloth[graph[:,1]],minlength=len(groups))+np.bincount(graph[:,1],weights=cloth[graph[:,0]],minlength=len(groups))
    cloth=.5*cloth+.5*neighbors/degree
positions=[]; normals=[]; weights=[]; uvs=[]; source_hair=[]; rigid_head=[]; stabilized_cloth=[]
for vi,v in enumerate(pmx.vertices):
    p=source_point(v['position']); n=source_point(v['normal'])
    merged=coincident_weights[group_ids[vi]]; merged_total=sum(merged.values())
    influences=[(j,w/merged_total) for j,w in merged.items()]
    assert abs(sum(w for j,w in influences)-1)<.001
    head_weight=sum(w for j,w in influences if classes[j][0] in ['head','hair'])
    # Keep the entire authored face coherent despite the source's coarse auto rig.
    is_head=p.z>bp('首').z and head_weight>.45
    mapped=head(p) if is_head else sum((transform(p,j)*w for j,w in influences),Vector())
    acc=defaultdict(float)
    for j,w in influences:
        for bone,amount in influence(p,j): acc[bone]+=amount*w
    cloth_amount=float(cloth[group_ids[vi]])
    if cloth_amount>1e-6:
        mapped=mapped.lerp(body(p),cloth_amount)
        acc=defaultdict(float,{j:w*(1-cloth_amount) for j,w in acc.items()})
        left=max(0,min(1,(p.x/(abs(bp('左足').x)*2)+1)/2))
        for j,w in [(1,.92),(3,.08*left),(7,.08*(1-left))]: acc[j]+=w*cloth_amount
        if cloth_amount>.5:stabilized_cloth.append(vi)
    if is_head:
        acc=defaultdict(float,{bone:w for bone,w in acc.items() if bone==13 or bone>=30})
    ranked=sorted(((j,w) for j,w in acc.items() if w>1e-8),key=lambda item:-item[1])[:4]
    total=sum(w for j,w in ranked); ranked=[(j,w/total) for j,w in ranked]
    if not is_head:
        columns=[]
        for axis in range(3):
            q=p.copy();q[axis]+=1e-4
            neighbor=sum((transform(q,j)*w for j,w in influences),Vector()).lerp(body(q),cloth_amount)
            columns.append((neighbor-mapped)/1e-4)
        jacobian=Matrix([tuple(c) for c in columns]).transposed()
        try: n=(jacobian.inverted().transposed()@n).normalized()
        except ValueError: n.normalize()
    else: n.normalize()
    positions.append(tuple(mapped)); normals.append(tuple(n)); weights.append(ranked); uvs.append((v['uv'][0],1-v['uv'][1]))
    if any(j>=30 for j,w in ranked): source_hair.append(vi)
    elif is_head: rigid_head.append(vi)
    if vi%25000==0: print('RETARGET_VERTEX',vi,flush=True)

# Repair abrupt auto-rig transitions at the armpits as a smooth displacement
# field. Smoothing offsets rather than coordinates retains the source surface
# detail; the complete head and authored hair influences remain locked.
group_weights=np.zeros((len(groups),30+len(hair_bones)),dtype=np.float64)
for vi,ranked in enumerate(weights):
    for joint,amount in ranked:group_weights[group_ids[vi],joint]+=amount
group_weights/=counts[:,None]
base=np.array([tuple(body(source_point(v['position']))) for v in pmx.vertices])
offsets=np.array(positions)-base
group_offsets=np.column_stack([np.bincount(group_ids,weights=offsets[:,axis],minlength=len(groups))/counts for axis in range(3)])
locked=np.zeros(len(groups),dtype=bool);locked[group_ids[rigid_head+source_hair]]=True
for iteration in range(8):
    for field in [group_weights,group_offsets]:
        neighbor=np.column_stack([np.bincount(graph[:,0],weights=field[graph[:,1],axis],minlength=len(groups))+np.bincount(graph[:,1],weights=field[graph[:,0],axis],minlength=len(groups)) for axis in range(field.shape[1])])
        updated=.55*field+.45*neighbor/degree[:,None]
        field[~locked]=updated[~locked]
positions=[tuple(p) for p in base+group_offsets[group_ids]]
weights=[]
for group in group_ids:
    row=group_weights[group];chosen=np.argsort(row)[-4:][::-1]
    ranked=[(int(j),float(row[j])) for j in chosen if row[j]>1e-8];total=sum(w for j,w in ranked)
    weights.append([(j,w/total) for j,w in ranked])

texture_target=OUT/'textures/color.jpg'; shutil.copyfile(texture_source,texture_target)
image=bpy.data.images.load(str(texture_target),check_existing=True); image.alpha_mode='NONE'; resolution=list(image.size); image.pack()
spec=[dict(name='豆包 · 原4K颜色贴图',sourceName=pmx.materials[0]['name'],texture='textures/color.jpg',color=[1,1,1],twoSide=True,transparent=False,opacity=1,alphaTest=0,roughness=.84,metalness=0,depthWrite=True)]
material=bpy.data.materials.new(spec[0]['name']);material.use_nodes=True
bsdf=material.node_tree.nodes.get('Principled BSDF');bsdf.inputs['Roughness'].default_value=.84;bsdf.inputs['Specular IOR Level'].default_value=.18
node=material.node_tree.nodes.new('ShaderNodeTexImage');node.image=image;material.node_tree.links.new(node.outputs['Color'],bsdf.inputs['Base Color'])
faces=[(a,c,b) for a,b,c in zip(pmx.indices[::3],pmx.indices[1::3],pmx.indices[2::3])]
position_array=np.array(positions);triangles=np.array(faces);surface_normals=np.cross(position_array[triangles[:,1]]-position_array[triangles[:,0]],position_array[triangles[:,2]]-position_array[triangles[:,0]])
group_normals=np.zeros((len(groups),3),dtype=np.float64)
for corner in range(3):np.add.at(group_normals,group_ids[triangles[:,corner]],surface_normals)
normal_lengths=np.linalg.norm(group_normals,axis=1);group_normals/=np.maximum(1e-12,normal_lengths[:,None])
for vi,group in enumerate(group_ids):
    if not locked[group] and normal_lengths[group]>1e-12:normals[vi]=tuple(group_normals[group])
mesh=bpy.data.meshes.new('Doubao native-rest full surface');mesh.from_pydata(positions,[],faces);mesh.materials.append(material);mesh.update()
surface=bpy.data.objects.new('豆包 · 完整人物 · 原版动作适配',mesh);bpy.context.collection.objects.link(surface)
uv=mesh.uv_layers.new(name='Source atlas UV')
for poly in mesh.polygons:
    poly.use_smooth=True
    for li in poly.loop_indices: uv.data[li].uv=uvs[mesh.loops[li].vertex_index]
mesh.normals_split_custom_set_from_vertices(normals)
bone_names=[b['name'] for b in B]+[b['name'] for b in hair_bones]
for name in bone_names: surface.vertex_groups.new(name=name)
indices=[]; strengths=[]
for i,ranked in enumerate(weights):
    for j,w in ranked: surface.vertex_groups[j].add([i],w,'REPLACE')
    indices.extend([j for j,w in ranked]+[0]*(4-len(ranked)))
    strengths.extend([round(w,7) for j,w in ranked]+[0]*(4-len(ranked)))
head_offset=REST[B[13]['name']].inverted()@head(bp('頭')+Vector((0,0,.65)))
rig=dict(schema=1,type='web-spring-bone',nativeBoneCount=30,bones=hair_bones,hairMaterials=[],vertexCount=len(source_hair),colliders=[dict(shape='sphere',bone=13,offset=list(head_offset),radius=1.8),dict(shape='capsule',bone=12,endBone=1,radius=2.1)],provenance='Source CF/hair bone hierarchy and source vertex hair influences retained; restrained Web springs, not MMD rigid bodies.')
skin=dict(schema=1,coordinateSystem='original-native-Z-up',materials=spec,positions=[round(x,7) for p in positions for x in p],normals=[round(x,7) for p in normals for x in p],uvs=[round(x,8) for p in uvs for x in p],skinIndices=indices,skinWeights=strengths,faces=[dict(material=0,indices=list(f)) for f in faces],vertexCount=len(positions),triangleCount=len(faces),secondaryMotion=rig)
(OUT/'mesh.json').write_text(json.dumps(skin,separators=(',',':')))
credits='版权归属《豆包》；建模原作者：sdn1111；绑定：鹿铃。允许规范使用、二次修改优化和规范转载；使用或发布时注明原作者和版权方。'
manifest=dict(schema=1,characterId=0,appearance='doubao',label='豆包 · 模型适配',mesh='mesh.json',complete=True,completeness=dict(bodyGeometry=True,headHairGeometry=True,faceGeometry=True,eyes=True,sourcePmxSkeleton=True,originalSourceGameSkeleton=False),stats=dict(sourceVertices=len(pmx.vertices),sourceTriangles=len(faces),vertices=len(positions),triangles=len(faces),sourceBones=len(pmx.bones),bones=30,dummies=6,secondaryBones=len(hair_bones),textures=1,textureResolutions=[resolution]),retarget=dict(method='Source PMX joint positions and influences retargeted to native p0 BNC rest; native AMB/POS drives the original body and weapon attachments.',provisional=True,sourceSkeletonMissing=False,hairPhysics=True,hairPhysicsProfile='web-spring-bone-v2-restrained',originalMmdPhysics=False,clothPhysics=False,fingerArticulation='Source fingers follow native hands; no independent facial morph or full finger solver.'),provenance=dict(sourceArchive='assets/source/doubao',source='Project-owned archived Doubao PMX and original 4K JPEG atlas.',copyright='豆包',modelAuthor='sdn1111',rigAuthor='鹿铃',license=credits,sourceNotes='Source author notes possible rig bugs and no cloth physics.',limits=['Native p0 body proportions require approximate limb/torso retargeting.','Restrained Web hair springs are not original MMD rigid-body simulation.','No facial morph, cloth physics or individual finger animation.','Full source triangle count retained; more geometry than other imported appearances.']),sourceFiles=[dict(file='豆包模型.pmx',bytes=len(pmx.data),sha256=hashlib.sha256(pmx.data).hexdigest()),dict(file='tex/Color.jpg',bytes=texture_source.stat().st_size,sha256=hashlib.sha256(texture_source.read_bytes()).hexdigest())])
(OUT/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2))
(OUT/'署名与使用说明.txt').write_text(credits+'\n\n'+(SRC/'注意事项.txt').read_text(encoding='utf-8-sig'),encoding='utf-8')
arm,rest_error=make_native_armature(surface,'豆包',hair_bones)
clips,pose_error=bake_native_samples(arm)
arm['web_hair_springs']=json.dumps(rig,ensure_ascii=False)
arm['README']='Native body actions are baked for editing; Web samples original AMB/POS and simulates restrained hair separately. Jump world arc is applied by Web host.'
scene=bpy.context.scene;scene['attribution']=credits;scene['source_archive']='assets/source/doubao'
scene.render.engine='CYCLES';scene.cycles.samples=16;scene.cycles.use_denoising=True;scene.world.color=(.18,.18,.18)
scene.view_settings.view_transform='Standard';scene.render.resolution_x=900;scene.render.resolution_y=1100;scene.render.resolution_percentage=100
for loc,power,size in [((40,-65,75),20000,55),((-40,-30,45),12000,45),((0,40,60),16000,45)]:
    bpy.ops.object.light_add(type='AREA',location=loc);light=bpy.context.object;light.data.energy=power;light.data.size=size;light.rotation_euler=(Vector((0,0,20))-light.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add(location=(20,-110,43));camera=bpy.context.object;camera.data.type='ORTHO';camera.data.ortho_scale=47;camera.rotation_euler=(Vector((0,0,20))-camera.location).to_track_quat('-Z','Y').to_euler();scene.camera=camera
if args.render:
    scene.render.filepath=str(WORK/'retargeted-stance.png');bpy.ops.render.render(write_still=True)
bpy.ops.wm.save_as_mainfile(filepath=str(WORK/'豆包-完整人物-流星动作适配.blend'))
evidence=dict(blender=bpy.app.version_string,sourceArchive='assets/source/doubao',sourceDownloadsRequired=False,runtimeRoot='dist/assets/enhanced/doubao',restMatrixError=rest_error,poseMatrixError=pose_error,bakedActions=clips,hairVertices=source_hair,rigidHeadVertices=rigid_head,stabilizedClothVertices=stabilized_cloth,sourceWeldGroups=len(groups),stats=manifest['stats'],hashes={name:hashlib.sha256((OUT/name).read_bytes()).hexdigest() for name in ['manifest.json','mesh.json','textures/color.jpg']})
(WORK/'build-evidence.json').write_text(json.dumps(evidence,ensure_ascii=False,indent=2))
print('DOUBAO_READY',json.dumps(manifest['stats'],ensure_ascii=False),'REST',rest_error,'POSE',pose_error,flush=True)
