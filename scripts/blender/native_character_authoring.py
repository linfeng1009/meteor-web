"""Author exact BNC rest matrices and four editable AMB samples in Blender."""
import bpy, math, re, json
from pathlib import Path
from struct import unpack_from
from mathutils import Matrix, Quaternion, Vector
from hutao_native_rest import B, D, entries, world as REST, resolve

ROOT = Path(__file__).resolve().parents[2]
C = Matrix.Rotation(-math.pi / 2, 4, 'Z')

def make_native_armature(surface, label, secondary_bones=()):
    data = bpy.data.armatures.new(label + ' · BNC bind')
    arm = bpy.data.objects.new(label + ' · 流星动作骨架', data)
    bpy.context.collection.objects.link(arm)
    bpy.context.view_layer.objects.active = arm
    arm.select_set(True); surface.select_set(False)
    bpy.ops.object.mode_set(mode='EDIT')
    for entry in B:
        data.edit_bones.new(entry['name'])
    for entry in B:
        bone = data.edit_bones[entry['name']]
        parent = resolve(entry['parent'])
        if parent in data.edit_bones:
            bone.parent = data.edit_bones[parent]
        matrix = REST[entry['name']] @ C
        bone.head = matrix.translation
        bone.tail = matrix.translation + matrix.to_3x3().col[1] * .8
        bone.align_roll(matrix.to_3x3().col[2])
    for spec in secondary_bones:
        bone = data.edit_bones.new(spec['name'])
        parent = spec['parent']
        bone.parent = data.edit_bones[B[parent]['name'] if parent < 30 else secondary_bones[parent-30]['name']]
        bone.head = Vector(spec['position']); bone.tail = Vector(spec['tail'])
        q = spec['rotation']
        bone.align_roll(Quaternion((q[3], q[0], q[1], q[2])).to_matrix().col[2])
    bpy.ops.object.mode_set(mode='OBJECT')
    rest_error = max(abs(x-y) for e in B for row, expected in zip(data.bones[e['name']].matrix_local, REST[e['name']] @ C) for x,y in zip(row, expected))
    assert rest_error < 1e-4, f'Native rest matrix error {rest_error}'
    modifier = surface.modifiers.new('Native BNC/AMB skin', 'ARMATURE'); modifier.object = arm
    surface.parent = arm; arm.show_in_front = True
    for entry in D:
        empty = bpy.data.objects.new(entry['name'], None)
        bpy.context.collection.objects.link(empty)
        empty.matrix_world = REST[entry['name']]; empty.parent = arm
        empty.empty_display_type = 'ARROWS'; empty.empty_display_size = .5; empty.hide_render = True
        empty['native_parent'] = entry['parent']; empty['native_bind'] = entry
    arm['native_rest_entries'] = json.dumps(entries)
    arm['native_C_rotation'] = -math.pi / 2
    return arm, rest_error

def bake_native_samples(arm, include_secondary=True):
    amb = [(ROOT / 'dist/assets/original/characters/common/character.amb').read_bytes(), (ROOT / 'dist/assets/original/characters/p0/p0.amb').read_bytes()]
    poses = (ROOT / 'dist/assets/native/combat/P0.POS').read_text(encoding='big5')
    def apply_frame(source, frame):
        raw = amb[source]; nb, nd, _, _ = unpack_from('<4i', raw, 5)
        offset = 21 + frame * (20 + nb*16 + nd*33)
        local = {e['name']: dict(e) for e in entries}
        root = unpack_from('<3f', raw, offset+8)
        local[B[0]['name']]['position'] = [0, 0, root[2]]
        for i,e in enumerate(B):
            local[e['name']]['quaternion'] = unpack_from('<4f', raw, offset+20+i*16)
        for i,e in enumerate(D):
            k = offset+20+nb*16+i*33
            local[e['name']]['parent'] = raw[k:k+5].decode().rstrip('\0')
            local[e['name']]['position'] = list(unpack_from('<3f', raw, k+5))
            local[e['name']]['quaternion'] = unpack_from('<4f', raw, k+17)
            if e['name'] == 'd_base':
                local[e['name']]['position'] = e['position']
        world = {}
        def calculate(name):
            if name in world: return world[name]
            e = local[name]; q = Quaternion(e['quaternion']); q.normalize()
            matrix = Matrix.Translation(Vector(e['position'])) @ q.to_matrix().to_4x4()
            parent = resolve(e['parent'])
            world[name] = calculate(parent) @ matrix if parent else matrix
            return world[name]
        for e in entries: calculate(e['name'])
        for e in B:
            arm.pose.bones[e['name']].matrix = world[e['name']] @ C
            bpy.context.view_layer.update()
        return max(abs(x-y) for e in B for row, expected in zip(arm.pose.bones[e['name']].matrix, world[e['name']] @ C) for x,y in zip(row, expected))
    clips = []; max_error = 0
    for pose_id, label in [(6,'原版持剑待机'), (144,'原版跑步'), (151,'原版跳跃局部姿势'), (262,'原版持剑攻击')]:
        block = re.search(r'^Pose\s+'+str(pose_id)+r'\b[^\r\n]*\r?\n\s*\{(.*?)\n\}', poses, re.M|re.S)[1]
        first = int(re.search(r'^\s*Start\s+(\d+)', block, re.M|re.I)[1])
        last = int(re.search(r'^\s*End\s+(\d+)', block, re.M|re.I)[1])
        source_match = re.search(r'^\s*source\s+(\d+)', block, re.M|re.I)
        source = int(source_match[1]) if source_match else 0
        arm.animation_data_clear()
        for pb in arm.pose.bones: pb.rotation_mode = 'QUATERNION'
        for source_frame in range(first, last+1):
            max_error = max(max_error, apply_frame(source, source_frame))
            frame = source_frame-first+1
            for pb in arm.pose.bones:
                if not include_secondary and pb.name not in {b['name'] for b in B}:
                    continue
                for channel in ['location','rotation_quaternion','scale']:
                    pb.keyframe_insert(channel, frame=frame, group=pb.name)
        action = arm.animation_data.action; action.name = f'{pose_id} · {label}'; action.use_fake_user = True
        action['native_pose_id'] = pose_id; action['source'] = source
        action['source_start'] = first; action['source_end'] = last
        clips.append(dict(name=action.name, frames=last-first+1, pose=pose_id))
    assert max_error < 1e-3, f'Native pose matrix error {max_error}'
    arm.animation_data.action = bpy.data.actions[clips[0]['name']]
    scene = bpy.context.scene; scene.render.fps = 30; scene.frame_start = 1; scene.frame_end = clips[0]['frames']; scene.frame_set(1)
    return clips, max_error
