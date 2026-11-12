"""Save the repaired Liuchao game asset as an editable Blender project.

Run after build_liuchao.py:
Blender -b --factory-startup --disable-autoexec --python scripts/blender/save_liuchao_blend.py
"""

import hashlib
import json
import math
import sys
from pathlib import Path

import bpy
import numpy as np
from mathutils import Matrix, Quaternion, Vector

sys.path.insert(0, str(Path(__file__).resolve().parent))
from proportional_authoring import bake_source_samples, build_source_armature


ROOT = Path(__file__).resolve().parents[2]
ASSET = ROOT / 'dist/assets/enhanced/liuchao'
PARTS = ROOT / 'work/liuchao-import-2026-11-11/build-evidence.json'
DESTINATION = ROOT / 'assets/source/liuchao/琉潮-修复版.blend'


def srgb_channel(value):
    value /= 255
    return value / 12.92 if value <= .04045 else ((value + .055) / 1.055) ** 2.4


def create_material(spec):
    material = bpy.data.materials.new(spec['name'])
    material.use_nodes = True
    material.use_backface_culling = not spec.get('twoSide', False)
    nodes, links = material.node_tree.nodes, material.node_tree.links
    shader = nodes['Principled BSDF']
    color = spec.get('color', 0xffffff)
    rgba = (*(srgb_channel((color >> shift) & 255) for shift in (16, 8, 0)), 1)
    material.diffuse_color = rgba
    shader.inputs['Base Color'].default_value = rgba
    shader.inputs['Roughness'].default_value = spec.get('roughness', .78)
    shader.inputs['Metallic'].default_value = spec.get('metalness', 0)
    if spec.get('hairSurface'):
        shader.inputs['Anisotropic'].default_value = spec.get('anisotropy', .35)
        shader.inputs['Specular IOR Level'].default_value = .4
    elif spec.get('skinSurface'):
        shader.inputs['Specular IOR Level'].default_value = .35

    texture = spec.get('texture')
    if texture and texture != 'null':
        image = bpy.data.images.load(str(ASSET / texture), check_existing=True)
        if not image.packed_file:
            image.pack()
        texture_node = nodes.new('ShaderNodeTexImage')
        texture_node.image = image
        texture_node.location = (-440, 180)
        links.new(texture_node.outputs['Color'], shader.inputs['Base Color'])
        if spec.get('alphaTest', 0) > 0:
            cutoff = nodes.new('ShaderNodeMath')
            cutoff.operation = 'GREATER_THAN'
            cutoff.inputs[1].default_value = spec['alphaTest']
            links.new(texture_node.outputs['Alpha'], cutoff.inputs[0])
            links.new(cutoff.outputs[0], shader.inputs['Alpha'])
    return material


def create_parts(skin, parts, collection):
    positions = np.asarray(skin['positions'], dtype=np.float32).reshape(-1, 3)
    normals = np.asarray(skin['normals'], dtype=np.float32).reshape(-1, 3)
    uvs = np.asarray(skin['uvs'], dtype=np.float32).reshape(-1, 2)
    joints = np.asarray(skin['skinIndices']).reshape(-1, 4)
    weights = np.asarray(skin['skinWeights']).reshape(-1, 4)
    materials = [create_material(spec) for spec in skin['materials']]
    bone_names = [bone['name'] for bone in skin['bodyRig']['bones']]

    objects = []
    vertex_start = face_start = 0
    for part in parts:
        vertex_end = vertex_start + part['runtimeVertices']
        face_end = face_start + part['triangles']
        faces = skin['faces'][face_start:face_end]
        triangles = np.asarray([face['indices'] for face in faces], dtype=np.int32) - vertex_start
        assert triangles.min() >= 0 and triangles.max() < part['runtimeVertices'], part['name']

        name = part['name']
        if name == '身体 · 连续曲面':
            name = '身体 · 已修肩背及泳装下装'
        elif name == '官方面部 · 眼睛与表情形态键':
            name = '官方面部 · 游戏适配'
        mesh = bpy.data.meshes.new(name)
        mesh.from_pydata(positions[vertex_start:vertex_end].tolist(), [], triangles.tolist())
        obj = bpy.data.objects.new(name, mesh)
        collection.objects.link(obj)
        objects.append(obj)

        used_materials = sorted({face['material'] for face in faces})
        slots = {source: index for index, source in enumerate(used_materials)}
        for source in used_materials:
            mesh.materials.append(materials[source])
        mesh.polygons.foreach_set('material_index', np.asarray(
            [slots[face['material']] for face in faces], dtype=np.int32))
        mesh.polygons.foreach_set('use_smooth', np.ones(len(faces), dtype=np.bool_))
        uv = mesh.uv_layers.new(name='游戏 UV')
        uv.uv.foreach_set('vector', uvs[vertex_start + triangles].ravel())
        mesh.normals_split_custom_set_from_vertices(normals[vertex_start:vertex_end].tolist())
        mesh.update()

        joint_rows = joints[vertex_start:vertex_end]
        weight_rows = weights[vertex_start:vertex_end]
        groups = {int(index): obj.vertex_groups.new(name=bone_names[index])
                  for index in np.unique(joint_rows[weight_rows > 0])}
        for vertex, (indices, amounts) in enumerate(zip(joint_rows, weight_rows)):
            for index, amount in zip(indices, amounts):
                if amount > 0:
                    groups[int(index)].add([vertex], float(amount), 'REPLACE')
        vertex_start, face_start = vertex_end, face_end

    assert vertex_start == skin['vertexCount'] and face_start == skin['triangleCount']
    return objects


def set_relaxed_stance(armature, rig, rest):
    """Author a neutral inspection pose on the same editable rig."""
    armature.animation_data.action = None
    pose = [armature.pose.bones[bone['name']] for bone in rig['bones']]
    for bone in pose:
        bone.matrix_basis.identity()
    bpy.context.view_layer.update()

    def aim(joint, endpoint, direction):
        pivot = joint.head.copy()
        swing = (endpoint.head - pivot).normalized().rotation_difference(Vector(direction).normalized())
        around_joint = Matrix.Translation(pivot) @ swing.to_matrix().to_4x4() @ Matrix.Translation(-pivot)
        joint.matrix = around_joint @ joint.matrix
        bpy.context.view_layer.update()

    for side, thigh, ankle, upper_arm, forearm, hand, fingers, fingertips in [
        (1, 3, 5, 15, 16, 17, 20, 21),
        (-1, 7, 9, 23, 24, 25, 28, 29),
    ]:
        # Widen the source stance a little while keeping the sandal soles flat.
        target = Vector((side * 1.67, rest[ankle].translation.y, rest[ankle].translation.z))
        aim(pose[thigh], pose[ankle], target - pose[thigh].head)
        foot_heading = Quaternion((0, 0, 1), side * math.radians(5)).to_matrix().to_4x4()
        rest_foot = pose[ankle].bone.matrix_local.copy()
        foot = foot_heading @ rest_foot
        foot.translation = pose[ankle].head
        pose[ankle].matrix = foot
        bpy.context.view_layer.update()

        aim(pose[upper_arm], pose[forearm], (side * .29, -.025, -1))
        aim(pose[forearm], pose[hand], (side * .09, -.15, -1))
        aim(pose[hand], pose[fingers], (-side * .04, -.08, -1))
        aim(pose[fingers], pose[fingertips], (-side * .18, -.08, -1))

    # Place the lower of the two flat soles back at the bind ground level.
    height = min(pose[i].head.z - rest[i].translation.z for i in (5, 9))
    root = pose[0].matrix.copy()
    root.translation.z -= height
    pose[0].matrix = root
    bpy.context.view_layer.update()
    for bone in pose:
        for channel in ('location', 'rotation_quaternion', 'scale'):
            bone.keyframe_insert(channel, frame=1, group=bone.name)
    action = armature.animation_data.action
    action.name = '自然站立 · 放松垂臂'
    action.use_fake_user = True
    bpy.context.scene.frame_set(1)


def set_up_preview(scene, armature):
    studio = bpy.data.collections.new('预览相机与灯光')
    scene.collection.children.link(studio)
    target = Vector((0, 0, 19.7))
    left = armature.pose.bones['bau_L_UpperArm'].head
    right = armature.pose.bones['bau_R_UpperArm'].head
    up = Vector((0, 0, 1))
    back = up.cross(left - right).normalized()

    def camera(name, direction):
        data = bpy.data.cameras.new(name)
        data.type = 'ORTHO'
        data.ortho_scale = 45
        obj = bpy.data.objects.new(name, data)
        studio.objects.link(obj)
        obj.location = target + direction * 80 + up * 3
        obj.rotation_euler = (target - obj.location).to_track_quat('-Z', 'Y').to_euler()
        return obj

    scene.camera = camera('背面 · 肩背与下装', back)
    camera('正面 · 全身', -back)
    side = back.cross(up)
    for name, location, energy, size, color in [
        ('背面主光', target + back * 42 + up * 30 + side * 20, 9500, 33, (1, .94, .87)),
        ('侧面补光', target + back * 40 + up * 10 - side * 25, 6000, 32, (.87, .94, 1)),
        ('正面补光', target - back * 45 + up * 20, 9000, 34, (1, .96, .92)),
    ]:
        data = bpy.data.lights.new(name, 'AREA')
        data.energy, data.size, data.color = energy, size, color
        obj = bpy.data.objects.new(name, data)
        studio.objects.link(obj)
        obj.location = location
        obj.rotation_euler = (target - location).to_track_quat('-Z', 'Y').to_euler()

    scene.world.use_nodes = True
    background = scene.world.node_tree.nodes['Background']
    background.inputs['Color'].default_value = (.17, .21, .24, 1)
    background.inputs['Strength'].default_value = .65
    scene.render.engine = 'CYCLES'
    scene.cycles.samples = 32
    scene.cycles.use_denoising = True
    scene.render.resolution_x, scene.render.resolution_y = 800, 950
    scene.render.resolution_percentage = 100
    for screen in bpy.data.screens:
        for area in screen.areas:
            if area.type == 'VIEW_3D':
                space = area.spaces.active
                space.shading.type = 'MATERIAL'
                space.overlay.show_overlays = False
                space.region_3d.view_perspective = 'CAMERA'
                space.region_3d.view_camera_zoom = 10


def main():
    raw = (ASSET / 'mesh.json').read_bytes()
    skin = json.loads(raw)
    parts = json.loads(PARTS.read_text())['objects']
    rig = skin['bodyRig']
    bpy.ops.object.select_all(action='SELECT')
    bpy.ops.object.delete(use_global=False)
    scene = bpy.context.scene
    scene.name = '琉潮 · 修复版'
    collection = bpy.data.collections.new('琉潮 · 可编辑网格')
    scene.collection.children.link(collection)
    objects = create_parts(skin, parts, collection)
    body = next(obj for obj in objects if obj.name.startswith('身体 · '))
    armature, rest, rest_error = build_source_armature(body, rig, [], label='琉潮')
    for obj in objects:
        if obj is body:
            continue
        obj.parent = armature
        modifier = obj.modifiers.new('游戏动作骨架', 'ARMATURE')
        modifier.object = armature
    clips, pose_error = bake_source_samples(armature, rig, rest)
    set_relaxed_stance(armature, rig, rest)
    armature.show_in_front = False
    set_up_preview(scene, armature)
    scene.unit_settings.system = 'METRIC'
    scene.unit_settings.scale_length = 1 / rig['sourceUniformScale']
    scene['game_mesh_sha256'] = hashlib.sha256(raw).hexdigest()
    notes = bpy.data.texts.new('打开这里 · 修复说明')
    notes.write(
        '琉潮 · 修复版\n\n'
        '从游戏使用的修复模型还原为可编辑网格，贴图已打包。'
        '身体对象含肩背修整和与身体共用顶点的泳装下装，短发、马尾及饰物分别保留为网格。\n'
        '打开时显示自然站立的背面，另有正面相机。'
        '可在动作编辑器中选自然站立、持剑待机、跑步、跳跃或挥剑。\n'
        '此副本使用 30 根游戏动作骨骼，原有 MMD 控制器、面部形态键和曲线对象可在同目录的琉潮.blend 中找到。\n'
    )
    armature.select_set(False)
    body.select_set(True)
    bpy.context.view_layer.objects.active = body
    bpy.ops.wm.save_as_mainfile(filepath=str(DESTINATION), compress=True)
    print('LIUCHAO_BLEND_READY', len(objects), len(clips), rest_error, pose_error, flush=True)


if __name__ == '__main__':
    main()
