"""Build the Furina swimwear variant from the archived GIMI vertex streams.

Run with Blender --background --factory-startup --disable-autoexec --python.
The existing Furina runtime mesh supplies the face draw pass and its textures.
"""
import hashlib
import json
from pathlib import Path
import sys

import bpy
import numpy as np
from mathutils import Vector

sys.path.insert(0, str(Path(__file__).parent))
from hutao_native_rest import B, world as REST
from proportional_authoring import bake_source_samples, build_source_armature


ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'assets/source/furina/swimwear'
BASE = ROOT / 'dist/assets/enhanced/furina'
OUT = BASE.with_name('furina-swimwear')
WORK = ROOT / 'work/furina-swimwear-import-2026-11-13'
LABEL = '芙宁娜 · 泳装'


def read_stream(part, layout, width):
    return np.fromfile(SOURCE / f'FurinaDark{part}', dtype=layout).reshape(-1, width)


def quaternion_components(q):
    return [q.x, q.y, q.z, q.w]


def source_weights(blend, palette_id):
    return np.where(blend['indices'] == palette_id, blend['weights'], 0).sum(axis=1)


def joint_between(positions, blend, left, right):
    overlap = np.minimum(source_weights(blend, left), source_weights(blend, right))
    return np.average(positions, weights=overlap ** 3, axis=0)


def build_body_rig(base_rig, transform):
    # Landmark centres are sampled from the paired skin-weight bands around
    # each source joint. The mesh itself only receives a uniform transform.
    anchors = {
        0: (0, -.008, .848), 1: (0, -.009, .863), 2: (0, -.013, .981),
        11: (0, -.014, 1.139), 12: (0, .002, 1.244), 13: (0, .002, 1.307),
    }
    left_side = {
        3: (.073, -.013, .863), 4: (.052, -.029, .453),
        5: (.044, .006, .100), 6: (.047, -.074, .023),
        14: (.038, .006, 1.202), 15: (.107, .003, 1.207),
        16: (.214, .009, 1.017), 17: (.319, .003, .866),
        18: (.327, -.019, .851), 19: (.334, -.045, .833),
        20: (.359, .002, .818), 21: (.391, .002, .789),
    }
    for slot, (x, y, z) in left_side.items():
        anchors[slot] = (x, y, z)
        anchors[slot + (4 if slot < 7 else 8)] = (-x, y, z)
    anchors = [Vector(transform(anchors[i])) for i in range(len(B))]
    axis_links = {3: 4, 4: 5, 5: 6, 7: 8, 8: 9, 9: 10, 14: 15, 15: 16, 16: 17,
                  17: 21, 18: 19, 20: 21, 22: 23, 23: 24, 24: 25, 25: 29, 26: 27, 28: 29}
    bones = []
    for i, bone in enumerate(base_rig['bones']):
        bind = REST[B[i]['name']]
        q = bind.to_quaternion()
        if i in axis_links:
            child = axis_links[i]
            native_axis = REST[B[child]['name']].translation - bind.translation
            source_axis = anchors[child] - anchors[i]
            q = native_axis.rotation_difference(source_axis) @ q
        bones.append({**bone, 'position': list(anchors[i]), 'rotation': quaternion_components(q)})
    return {**base_rig, 'bones': bones}


def build_hair_rig(positions, blend, material_index):
    bones, palette = [], {}
    # Weight overlap gives the transitions between the scalp and each curl.
    # Only the three short strands get springs. The tiara stays on the head.
    for label, root, tip in [('呆毛', 12, 13), ('右侧发', 14, 15), ('左侧发', 16, 17)]:
        anchor = joint_between(positions, blend, 62, root)
        joint = joint_between(positions, blend, root, tip)
        end = np.average(positions, weights=source_weights(blend, tip)**4, axis=0)
        parent = 13
        for depth, (palette_id, start, stop) in enumerate([(root, anchor, joint), (tip, joint, end)]):
            axis = Vector(stop - start)
            palette[palette_id] = 30 + len(bones)
            bones.append(dict(name=f'泳装_{label}_{depth + 1}', parent=parent, sourceBone=palette_id,
                              position=start.tolist(), tail=stop.tolist(),
                              rotation=quaternion_components(axis.to_track_quat('Y', 'Z')),
                              stiffness=150, damping=28, maxAngle=.025, gravity=.001,
                              follow=.98, globalMaxAngle=.035, radius=.08))
            parent = palette[palette_id]
    return dict(schema=1, type='web-spring-bone', nativeBoneCount=30, bones=bones,
                hairMaterials=[material_index], colliders=[dict(shape='sphere', bone=13, radius=1.5)]), palette


def skin_stream(blend, hair_palette):
    palette = {
        7: 11, 18: 13, 38: 1, 57: 23, 58: 23, 59: 15, 60: 15, 62: 13, 63: 8, 64: 22,
        65: 26, 66: 27, 67: 27, 80: 9, 81: 24, 82: 25, 83: 7, 84: 9, 85: 12, 86: 4, 87: 14,
        88: 18, 89: 19, 90: 19, 103: 5, 104: 16, 105: 17, 106: 3, 107: 5, 108: 2, 110: 11,
        **hair_palette,
    }
    for i in range(12):
        palette[68 + i] = 28 if i % 3 == 0 else 29
        palette[91 + i] = 20 if i % 3 == 0 else 21
    indices = np.zeros((len(blend), 4), dtype=np.uint16)
    weights = np.zeros((len(blend), 4))
    for vertex, row in enumerate(blend):
        folded = {}
        for palette_id, weight in zip(row['indices'], row['weights']):
            if weight > 1e-6:
                slot = palette[int(palette_id)]
                folded[slot] = folded.get(slot, 0) + float(weight)
        total = sum(folded.values())
        assert total > 0, vertex
        for lane, (slot, weight) in enumerate(sorted(folded.items(), key=lambda pair: -pair[1])):
            indices[vertex, lane] = slot
            weights[vertex, lane] = weight / total
    return indices, weights


def export_texture(part, filename):
    # The mod's colour pass is ps-t1 for Head and ps-t0 for Dress. The
    # transparency shader uses a constant blend factor, independent of DDS alpha.
    source = SOURCE / f'FurinaDark{part}.dds'
    dest = OUT / 'textures' / filename
    image = bpy.data.images.load(str(source))
    image.alpha_mode = 'CHANNEL_PACKED'
    image.scale(2048, 2048)
    image.file_format = 'JPEG'
    image.save(filepath=str(dest), quality=95)
    bpy.data.images.remove(image)
    return 'textures/' + filename


def create_editable_scene(skin, rig, hair, face_indices):
    bpy.ops.object.select_all(action='SELECT')
    bpy.ops.object.delete(use_global=False)
    mesh = bpy.data.meshes.new(LABEL)
    positions = np.asarray(skin['positions']).reshape(-1, 3)
    mesh.from_pydata(positions.tolist(), [], [face['indices'] for face in skin['faces']])
    mesh.update()
    surface = bpy.data.objects.new(LABEL, mesh)
    bpy.context.collection.objects.link(surface)
    normals = np.asarray(skin['normals']).reshape(-1, 3)
    uv = np.asarray(skin['uvs']).reshape(-1, 2)
    uv_layer = mesh.uv_layers.new(name='Source UV')
    loops = np.empty(len(mesh.loops), dtype=np.int32)
    mesh.loops.foreach_get('vertex_index', loops)
    uv_layer.uv.foreach_set('vector', uv[loops].astype(np.float32).ravel())
    mesh.polygons.foreach_set('material_index', [face['material'] for face in skin['faces']])
    mesh.polygons.foreach_set('use_smooth', np.ones(len(mesh.polygons), dtype=np.bool_))
    mesh.normals_split_custom_set_from_vertices(normals.tolist())
    for spec in skin['materials']:
        mat = bpy.data.materials.new(spec['name'])
        mat.use_nodes = True
        bsdf = mat.node_tree.nodes.get('Principled BSDF')
        bsdf.inputs['Roughness'].default_value = spec['roughness']
        bsdf.inputs['Metallic'].default_value = spec['metalness']
        bsdf.inputs['Base Color'].default_value = (*[(spec['color'] >> shift & 255) / 255 for shift in (16, 8, 0)], 1)
        bsdf.inputs['Alpha'].default_value = spec['opacity']
        if spec['texture'] not in ('null', None, ''):
            node = mat.node_tree.nodes.new('ShaderNodeTexImage')
            node.image = bpy.data.images.load(str((OUT / spec['texture']).resolve()), check_existing=True)
            if not node.image.packed_file:
                node.image.pack()
            if spec['color'] == 0xffffff:
                mat.node_tree.links.new(node.outputs['Color'], bsdf.inputs['Base Color'])
            else:
                tint = mat.node_tree.nodes.new('ShaderNodeMixRGB')
                tint.blend_type = 'MULTIPLY'
                tint.inputs[0].default_value = 1
                tint.inputs[2].default_value = bsdf.inputs['Base Color'].default_value
                mat.node_tree.links.new(node.outputs['Color'], tint.inputs[1])
                mat.node_tree.links.new(tint.outputs[0], bsdf.inputs['Base Color'])
            if spec.get('alphaTest'):
                alpha = mat.node_tree.nodes.new('ShaderNodeMath')
                alpha.operation = 'GREATER_THAN'
                alpha.inputs[1].default_value = spec['alphaTest']
                mat.node_tree.links.new(node.outputs['Alpha'], alpha.inputs[0])
                mat.node_tree.links.new(alpha.outputs[0], bsdf.inputs['Alpha'])
        mesh.materials.append(mat)
    # A separate material set and vertex group keep the shared face identifiable.
    groups = [surface.vertex_groups.new(name=b['name']) for b in rig['bones'] + hair['bones']]
    for i, (joints, weights) in enumerate(zip(np.asarray(skin['skinIndices']).reshape(-1, 4),
                                               np.asarray(skin['skinWeights']).reshape(-1, 4))):
        for slot, weight in zip(joints, weights):
            if weight > 0:
                groups[slot].add([i], weight, 'REPLACE')
    surface.vertex_groups.new(name='常服共享的脸部网格').add(face_indices, 1, 'REPLACE')
    arm, rest, rest_error = build_source_armature(surface, rig, hair['bones'], label=LABEL)
    clips, pose_error = bake_source_samples(arm, rig, rest)
    arm.animation_data.action = None
    for pose_bone in arm.pose.bones:
        pose_bone.matrix_basis.identity()
    scene = bpy.context.scene
    scene.frame_set(1)
    scene.unit_settings.system = 'NONE'
    scene['source_archive'] = str(SOURCE.relative_to(ROOT))
    scene['setup'] = '无武器原始站姿。四组《流星》动作可在动作编辑器中选用。Web 端运行轻量头发跟随。'
    arm.hide_set(True)
    surface.select_set(True)
    bpy.context.view_layer.objects.active = surface
    centre = Vector((0, 0, max(positions[:, 2]) / 2))
    for screen in bpy.data.screens:
        for area in screen.areas:
            if area.type == 'VIEW_3D':
                space = area.spaces.active
                space.overlay.show_overlays = False
                space.shading.color_type = 'TEXTURE'
                region = space.region_3d
                region.view_location = centre
                region.view_rotation = Vector((.26, 1, -.06)).to_track_quat('-Z', 'Y')
                region.view_distance = 59
    bpy.context.preferences.filepaths.save_version = 0
    bpy.ops.wm.save_as_mainfile(filepath=str(SOURCE / '芙宁娜泳装.blend'))
    return dict(restMatrixError=rest_error, poseMatrixError=pose_error, bakedActions=clips)


def main():
    (OUT / 'textures').mkdir(parents=True, exist_ok=True)
    WORK.mkdir(parents=True, exist_ok=True)
    base = json.loads((BASE / 'mesh.json').read_text())
    source = read_stream('Position.buf', '<f4', 10)
    positions = source[:, [0, 2, 1]].astype(np.float64)
    positions[:, 1] *= -1
    normals = source[:, [3, 5, 4]].copy()
    normals[:, 1] *= -1
    uv = read_stream('Texcoord.buf', '<f4', 5)[:, 1:3].copy()
    uv[:, 1] = 1 - uv[:, 1]
    blend = np.fromfile(SOURCE / 'FurinaDarkBlend.buf', dtype=[('weights', '<f4', 4), ('indices', '<u4', 4)])
    head, body, dress = (read_stream(f'{part}.ib', '<u4', 3) for part in ('Head', 'Body', 'Dress'))
    assert len(positions) == len(uv) == len(blend) == 43336
    assert not len(body) and max(head.max(), dress.max()) < len(positions)

    floor = positions[:, 2].min()
    size = 39.4 / (positions[:, 2].max() - floor)
    offset = np.array([0, 0, floor])

    def transform(p):
        return (p - offset) * size

    positions = transform(positions)
    eyes = (np.isin(blend['indices'][:, 0], [10, 11]) & (blend['weights'][:, 0] > .999))
    eye_faces = eyes[head]
    assert np.array_equal(eye_faces.any(axis=1), eye_faces.all(axis=1)), 'unexpected eye boundary'
    head = head[~eye_faces.all(axis=1)]
    hair_face = np.isin(blend['indices'][head, 0], [12, 13, 14, 15, 16, 17, 62]).all(axis=1)
    mod_indices = np.unique(np.concatenate([head.ravel(), dress.ravel()]))
    mod_remap = np.full(len(positions), -1, dtype=np.int32)
    mod_remap[mod_indices] = np.arange(len(mod_indices))
    body_rig = build_body_rig(base['bodyRig'], transform)
    body_rig.update(sourceUniformScale=size, sourceFloor=float(floor))
    hair, hair_palette = build_hair_rig(positions, blend, 1)
    joints, weights = skin_stream(blend[mod_indices], hair_palette)
    hair['vertexCount'] = int(((joints >= 30) & (weights > 0)).any(axis=1).sum())

    head_tex = export_texture('HeadLightMap', 'swimwear.jpg')
    dress_tex = export_texture('DressDiffuse', 'veil.jpg')
    material = dict(texture=head_tex, color=0xffffff, twoSide=True, opacity=1, alphaTest=0,
                    transparent=False, depthWrite=True, roughness=.69, metalness=.01, textureAnisotropy=8)
    materials = [
        {**material, 'name': '泳装、身体及配饰'},
        {**material, 'name': '短发', 'roughness': .63, 'hairSurface': True, 'anisotropy': .26},
        {**material, 'name': '薄纱', 'texture': dress_tex, 'opacity': .4, 'transparent': True, 'depthWrite': False},
    ]
    faces = [
        dict(material=slot, indices=indices)
        for slot, source_faces in enumerate((head[~hair_face], head[hair_face], dress))
        for indices in mod_remap[source_faces].tolist()
    ]
    face_names = {'颜', '颜2', '二重', '睫', '口舌', '齿', '眉', '白目', '目', '星目'}
    face_materials = {}
    for slot, spec in enumerate(base['materials']):
        if spec['name'] in face_names:
            face_materials[slot] = len(materials)
            materials.append({**spec, 'texture': f"../furina/{spec['texture']}"})
    base_pos = np.asarray(base['positions']).reshape(-1, 3)
    # The PMX has coincident face triangles along the nose and jaw, with
    # different split normals. Keep one layer so they cannot fight for depth.
    face_surface = next(i for i, spec in enumerate(base['materials']) if spec['name'] == '颜')
    base_faces = []
    face_triangles = set()
    for face in base['faces']:
        if face['material'] not in face_materials:
            continue
        if face['material'] == face_surface:
            key = tuple(sorted(map(tuple, base_pos[face['indices']].round(4))))
            if key in face_triangles:
                continue
            face_triangles.add(key)
        base_faces.append(face)
    base_indices = sorted({index for face in base_faces for index in face['indices']})
    base_remap = {index: i + len(mod_indices) for i, index in enumerate(base_indices)}
    faces.extend(dict(material=face_materials[f['material']], indices=[base_remap[i] for i in f['indices']])
                 for f in base_faces)
    iris = {index for f in base_faces if base['materials'][f['material']]['name'] == '目' for index in f['indices']}
    face_offset = positions[eyes].mean(axis=0) - base_pos[sorted(iris)].mean(axis=0)
    face_offset[0] = 0
    face_offset[1] -= .18  # place the face slightly forward to clear the inner hair shell
    face_positions = base_pos[base_indices] + face_offset
    face_joints = np.zeros((len(base_indices), 4), dtype=np.uint16)
    face_joints[:, 0] = 13
    face_weights = np.zeros((len(base_indices), 4))
    face_weights[:, 0] = 1

    skin = dict(
        schema=1, coordinateSystem='original-native-Z-up', bodyRig=body_rig, materials=materials, faces=faces,
        positions=np.round(np.concatenate([positions[mod_indices], face_positions]).ravel(), 7).tolist(),
        normals=np.round(np.concatenate([normals[mod_indices], np.asarray(base['normals']).reshape(-1, 3)[base_indices]]).ravel(), 7).tolist(),
        uvs=np.round(np.concatenate([uv[mod_indices].astype(np.float64), np.asarray(base['uvs']).reshape(-1, 2)[base_indices]]).ravel(), 8).tolist(),
        skinIndices=np.concatenate([joints, face_joints]).ravel().tolist(),
        skinWeights=np.round(np.concatenate([weights, face_weights]).ravel(), 7).tolist(),
        vertexCount=len(mod_indices) + len(base_indices), triangleCount=len(faces), secondaryMotion=hair,
    )
    (OUT / 'mesh.json').write_text(json.dumps(skin, separators=(',', ':'), ensure_ascii=False))
    manifest = dict(
        schema=1, characterId=0, appearance='furina-swimwear', variantOf='furina', label=LABEL,
        mesh='mesh.json', complete=True,
        completeness=dict(bodyGeometry=True, headHairGeometry=True, eyes=True, faceGeometry=True,
                          sourcePmxSkeleton=False, originalSourceGameSkeleton=False),
        stats=dict(sourceVertices=len(positions), sourceTriangles=len(head) + len(dress) + int(eye_faces.all(axis=1).sum()),
                   vertices=skin['vertexCount'], triangles=skin['triangleCount'], bones=30,
                   secondaryBones=len(hair['bones']), materials=len(materials), textures=4),
        retarget=dict(method='Recovered source weights transferred to the native Furina display rig layout at measured source joint centres.',
                      hairPhysics=True, hairPhysicsProfile='web-spring-bone-v2-restrained', clothPhysics=False),
        provenance=dict(sourceArchive=str(SOURCE.relative_to(ROOT)), sourceModel='FurinaDark',
                        sharedFace=dict(appearance='furina', modelAuthor='miHoYo', rigAuthor='观海（BiliBili：观海子）'),
                        limits=['Package contains vertex streams and texture overrides, without the source game skeleton or face mesh.',
                                'Pose binding and web materials approximate the source game.',
                                'Dress overlay follows the body weights; no cloth physics.']),
    )
    (OUT / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n')
    evidence = create_editable_scene(skin, body_rig, hair, list(base_remap.values()))
    evidence.update(stats=manifest['stats'], sourceScale=size, faceOffset=face_offset.tolist(),
                    replacedEyeTriangles=int(eye_faces.all(axis=1).sum()), sharedFaceVertices=len(base_indices),
                    hashes={name: hashlib.sha256((OUT / name).read_bytes()).hexdigest() for name in ['manifest.json', 'mesh.json']})
    (WORK / 'build-evidence.json').write_text(json.dumps(evidence, ensure_ascii=False, indent=2) + '\n')


if __name__ == '__main__':
    main()
