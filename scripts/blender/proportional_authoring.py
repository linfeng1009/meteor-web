"""Source-length display skeleton and original-AMB rotation retarget in Blender."""
import bpy,json,math,re
from pathlib import Path
from struct import unpack_from
from mathutils import Matrix,Quaternion,Vector
from hutao_native_rest import B,D,entries,world as REST,resolve

ROOT=Path(__file__).resolve().parents[2]
C=Matrix.Rotation(-math.pi/2,4,'Z')

def native_pose(source,frame,raw):
    nb,nd,_,_=unpack_from('<4i',raw,5);offset=21+frame*(20+nb*16+nd*33)
    local={e['name']:dict(e) for e in entries};root=unpack_from('<3f',raw,offset+8);local[B[0]['name']]['position']=[0,0,root[2]]
    for i,e in enumerate(B):local[e['name']]['quaternion']=unpack_from('<4f',raw,offset+20+i*16)
    for i,e in enumerate(D):
        k=offset+20+nb*16+i*33;local[e['name']]['parent']=raw[k:k+5].decode().rstrip('\0');local[e['name']]['position']=list(unpack_from('<3f',raw,k+5));local[e['name']]['quaternion']=unpack_from('<4f',raw,k+17)
        if e['name']=='d_base':local[e['name']]['position']=e['position']
    world={}
    def calc(name):
        if name in world:return world[name]
        e=local[name];q=Quaternion(e['quaternion']);q.normalize();m=Matrix.Translation(Vector(e['position']))@q.to_matrix().to_4x4();parent=resolve(e['parent']);world[name]=calc(parent)@m if parent else m;return world[name]
    for e in entries:calc(e['name'])
    return [world[e['name']] for e in B]

def build_source_armature(surface,rig,hair,label='春田'):
    data=bpy.data.armatures.new(label+' source-length display rig');arm=bpy.data.objects.new(label+' · 原始比例动作骨架',data);bpy.context.collection.objects.link(arm)
    bpy.context.view_layer.objects.active=arm;arm.select_set(True);surface.select_set(False);bpy.ops.object.mode_set(mode='EDIT')
    for b in rig['bones']:data.edit_bones.new(b['name'])
    rest=[]
    for b in rig['bones']:
        q=b['rotation'];matrix=Matrix.Translation(Vector(b['position']))@Quaternion((q[3],q[0],q[1],q[2])).to_matrix().to_4x4();rest.append(matrix)
        bone=data.edit_bones[b['name']]
        if b['parent']>=0:bone.parent=data.edit_bones[rig['bones'][b['parent']]['name']]
        m=matrix@C;bone.head=m.translation;bone.tail=m.translation+m.to_3x3().col[1]*.8;bone.align_roll(m.to_3x3().col[2])
    for b in hair:
        bone=data.edit_bones.new(b['name']);parent=b['parent'];bone.parent=data.edit_bones[rig['bones'][parent]['name'] if parent<30 else hair[parent-30]['name']];bone.head=Vector(b['position']);bone.tail=Vector(b['tail']);q=b['rotation'];bone.align_roll(Quaternion((q[3],q[0],q[1],q[2])).to_matrix().col[2])
    bpy.ops.object.mode_set(mode='OBJECT')
    error=max(abs(x-y) for i,b in enumerate(rig['bones']) for row,want in zip(data.bones[b['name']].matrix_local,rest[i]@C) for x,y in zip(row,want));assert error<1e-4,error
    modifier=surface.modifiers.new('Source proportions + native rotations','ARMATURE');modifier.object=arm;surface.parent=arm;arm.show_in_front=True
    return arm,rest,error

def bake_source_samples(arm,rig,rest):
    raw=[(ROOT/'dist/assets/original/characters/common/character.amb').read_bytes(),(ROOT/'dist/assets/original/characters/p0/p0.amb').read_bytes()]
    text=(ROOT/'dist/assets/native/combat/P0.POS').read_text(encoding='big5');clips=[];max_error=0
    for pose_id,label in [(6,'原比例持剑待机'),(144,'原比例跑步'),(151,'原比例跳跃局部姿势'),(262,'原比例持剑攻击')]:
        block=re.search(r'^Pose\s+'+str(pose_id)+r'\b[^\r\n]*\r?\n\s*\{(.*?)\n\}',text,re.M|re.S)[1];first=int(re.search(r'^\s*Start\s+(\d+)',block,re.M|re.I)[1]);last=int(re.search(r'^\s*End\s+(\d+)',block,re.M|re.I)[1]);source_match=re.search(r'^\s*source\s+(\d+)',block,re.M|re.I);source=int(source_match[1]) if source_match else 0
        arm.animation_data_clear()
        for pb in arm.pose.bones:pb.rotation_mode='QUATERNION'
        for source_frame in range(first,last+1):
            native=native_pose(source,source_frame,raw[source]);posed=[]
            for i,b in enumerate(rig['bones']):
                q=native[i].to_quaternion();parent=b['parent']
                if parent<0:position=Vector(b['position'])+native[0].translation-Vector(rig['nativeRootBind'])
                else:position=posed[parent]@(rest[parent].inverted()@Vector(b['position']))
                matrix=Matrix.Translation(position)@q.to_matrix().to_4x4();posed.append(matrix)
                pb=arm.pose.bones[b['name']];pb.matrix=matrix@C;bpy.context.view_layer.update()
            max_error=max(max_error,max(abs(x-y) for i,b in enumerate(rig['bones']) for row,want in zip(arm.pose.bones[b['name']].matrix,posed[i]@C) for x,y in zip(row,want)))
            for b in rig['bones']:
                pb=arm.pose.bones[b['name']]
                for channel in ['location','rotation_quaternion','scale']:pb.keyframe_insert(channel,frame=source_frame-first+1,group=pb.name)
        action=arm.animation_data.action;action.name=f'{pose_id} · {label}';action.use_fake_user=True;action['native_pose_id']=pose_id;action['source']=source;action['source_start']=first;action['source_end']=last;clips.append(dict(name=action.name,pose=pose_id,frames=last-first+1))
    assert max_error<1e-3,max_error
    arm.animation_data.action=bpy.data.actions[clips[0]['name']];scene=bpy.context.scene;scene.render.fps=30;scene.frame_start=1;scene.frame_end=clips[0]['frames'];scene.frame_set(1)
    arm['source_proportion_rig']=json.dumps(rig,ensure_ascii=False)
    return clips,max_error
