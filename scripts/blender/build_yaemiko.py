"""Build YaeMiko (八重神子) from the project-owned PMX archive; runtime reads dist only.

Blender --background --factory-startup --disable-autoexec --python scripts/blender/build_yaemiko.py

Proportion policy: every source vertex goes through ONE uniform scale plus a
floor offset. There is no per-segment height mapping, no head scale and no
torso width scale, so the built surface cannot be compressed or widened
relative to the source PMX. The 30-bone display rig keeps source segment
lengths and only receives the original AMB/POS rotations.
"""
import bpy, sys, json, math, hashlib, shutil
from pathlib import Path
from collections import defaultdict
from mathutils import Vector, Matrix
sys.path.insert(0, str(Path(__file__).parent))
from pmx_reader import PMXReader
from hutao_native_rest import B, world as REST
from proportional_authoring import build_source_armature, bake_source_samples

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / 'assets/source/yaemiko'
PMX_NAME = '八重神子.pmx'
OUT = ROOT / 'dist/assets/enhanced/yaemiko'
WORK = ROOT / 'work/yaemiko-import-2026-11-10'
for path in [OUT, OUT / 'textures', WORK]: path.mkdir(parents=True, exist_ok=True)

pmx = PMXReader(SRC / PMX_NAME).parse()
audit = pmx.summary(); audit['source'] = 'assets/source/yaemiko/' + pmx.path.name
(WORK / 'source-audit.json').write_text(json.dumps(audit, ensure_ascii=False, indent=2))

bpy.ops.object.select_all(action='SELECT'); bpy.ops.object.delete(use_global=False)
byname = {b['name']: b for b in pmx.bones}


def sp(p): return Vector((p[0], p[2], p[1]))          # PMX Y-up -> native Z-up
def bp(name): return sp(byname[name]['position'])
def target(index): return REST[B[index]['name']].translation


floor, top = audit['bounds'][1]
uniform_scale = 39.4 / (top - floor)


def uniform(p): return Vector((p.x * uniform_scale, p.y * uniform_scale, (p.z - floor) * uniform_scale))


def head(p): return uniform(p)


# The 30 native slots, in native order, anchored to the matching source bones.
source_names = ['センター', '下半身', '上半身', '左足D', '左ひざD', '左足首D', '左足先EX', '右足D', '右ひざD', '右足首D', '右足先EX',
                '上半身2', '首', '頭', '左肩', '左腕', '左ひじ', '左手首', '左親指０', '左親指１', '左中指１', '左中指３',
                '右肩', '右腕', '右ひじ', '右手首', '右親指０', '右親指１', '右中指１', '右中指３']
parents = [-1, 0, 0, 1, 3, 4, 5, 1, 7, 8, 9, 2, 11, 12, 11, 14, 15, 16, 17, 18, 17, 20, 11, 22, 23, 24, 25, 26, 25, 28]
missing = [name for name in source_names if name not in byname]
assert not missing, missing
anchors = [uniform(bp(name)) for name in source_names]

# Only the display rig's arm/leg axes are aligned to the native rest so an
# A-pose asset takes the native moves. Mesh geometry is never touched.
links = {3: 4, 4: 5, 5: 6, 7: 8, 8: 9, 9: 10, 14: 15, 15: 16, 16: 17, 17: 21, 18: 19, 20: 21,
         22: 23, 23: 24, 24: 25, 25: 29, 26: 27, 28: 29}
body_bones = []
for i, e in enumerate(B):
    q = REST[e['name']].to_quaternion()
    if i in links:
        j = links[i]
        native_axis = REST[B[j]['name']].translation - REST[e['name']].translation
        source_axis = anchors[j] - anchors[i]
        if native_axis.length > 1e-5 and source_axis.length > 1e-5:
            q = native_axis.normalized().rotation_difference(source_axis.normalized()) @ q
    body_bones.append(dict(name=e['name'], nativeBone=i, parent=parents[i], position=list(anchors[i]),
                           rotation=[q.x, q.y, q.z, q.w]))
body_rig = dict(schema=1, type='source-proportions', bones=body_bones,
                nativeRootBind=list(REST[B[0]['name']].translation),
                sourceUniformScale=uniform_scale, sourceFloor=floor)

# Preserve the source side/back hair and head-ribbon chains. Fox ears and
# earrings stay rigid on the head, separate from the subtle hair simulation.
hair_source = {b['index'] for b in pmx.bones if '髪' in b['name'] or '頭绳' in b['name']}
ordered = []


def order(index):
    if index in ordered: return
    parent = pmx.bones[index]['parent']
    if parent in hair_source: order(parent)
    ordered.append(index)


for i in sorted(hair_source): order(i)
hair_index = {i: 30 + j for j, i in enumerate(ordered)}
hair_bones = []
for index in ordered:
    b = pmx.bones[index]
    position = uniform(sp(b['position']))
    child = next((i for i in ordered if pmx.bones[i]['parent'] == index), None)
    tail_id = b.get('tailBone')
    if tail_id is not None and 0 <= tail_id < len(pmx.bones): tail = uniform(sp(pmx.bones[tail_id]['position']))
    elif child is not None: tail = uniform(sp(pmx.bones[child]['position']))
    else: tail = uniform(sp([x + y for x, y in zip(b['position'], b.get('tailOffset', [0, 0, 0]))]))
    if (tail - position).length < .05:
        axis = position - uniform(sp(pmx.bones[b['parent']]['position']))
        tail = position + (axis.normalized() if axis.length > .05 else Vector((0, 0, -1))) * .6
    q = (tail - position).to_track_quat('Y', 'Z')
    parent = hair_index.get(b['parent'], 13)
    depth = 0 if parent == 13 else hair_bones[parent - 30]['depth'] + 1
    hair_bones.append(dict(name='yaemiko_' + b['name'], sourceBone=index, sourceName=b['name'], parent=parent,
                           position=list(position), tail=list(tail), rotation=[q.x, q.y, q.z, q.w], depth=depth,
                           stiffness=210 if depth == 0 else 145 if depth == 1 else 105,
                           damping=32 if depth == 0 else 25, maxAngle=.01 if depth == 0 else .025,
                           gravity=0 if depth == 0 else .0028, follow=.98, globalMaxAngle=.038, radius=.12))


# Every source bone folds into one of the 30 native slots (or a hair slot).
# Skirt, tassel and waist bones stay rigid on the pelvis; face parts stay rigid
# on the head. No slot changes segment length.
def classify(index, seen=None):
    seen = set() if seen is None else seen
    if index < 0 or index in seen: return 0
    seen.add(index)
    b = pmx.bones[index]; n = b['name']
    side = '左' if n.startswith('左') else '右' if n.startswith('右') else None
    if index in hair_source: return hair_index[index]
    if n.startswith(('前摆', '后摆')) or n == '下半身': return 1
    if n in ('上半身2', '上半身3') or n == 'おっぱい調整' or n.startswith('胸'): return 11
    if n == '上半身': return 2
    if n == '腰': return 2
    if n == '首': return 12
    if n == '頭' or any(t in n for t in ['目', '歯', '齿', '耳', '角', '面', '睫', '二重', '眉', '口', '白目', '脸红']): return 13
    if side:
        off = 0 if side == '左' else 8
        if '肩' in n: return 14 + off
        if '親指' in n: return (19 + off) if any(t in n for t in ['１', '２', '先']) else (18 + off)
        if any(t in n for t in ['人指', '中指', '薬指', '小指']):
            return (21 + off) if any(t in n for t in ['２', '３', '先']) else (20 + off)
        if any(t in n for t in ['手首', 'ダミー', 'Weapon']): return 17 + off
        if '手捩' in n or 'ひじ' in n: return 16 + off
        if '腕' in n: return 15 + off
        if '足首' in n or 'つま先' in n or '足先' in n: return 5 + (0 if side == '左' else 4)
        if 'ひざ' in n: return 4 + (0 if side == '左' else 4)
        if n in [side + '足', side + '足D']: return 3 + (0 if side == '左' else 4)
    return classify(b['parent'], seen)


classes = [classify(i) for i in range(len(pmx.bones))]

head_names = {'颜', '颜2', '睫', '二重', '眉', '目', '星目', '口舌', '齿', '白目', '头饰', '耳饰+神之眼AL'}
hair_materials = {'髪', '前髪', '髪+', '前髪+'}
head_vertices = set(); hair_vertices = set(); hidden = []; source_faces = []; cursor = 0
for mi, m in enumerate(pmx.materials):
    ids = pmx.indices[cursor:cursor + m['indexCount']]; cursor += m['indexCount']
    if m['name'] in head_names: head_vertices.update(ids)
    if m['name'] in hair_materials: hair_vertices.update(ids)
    if m['diffuse'][3] < .001:
        hidden.append(dict(material=m['name'], sourceMaterial=mi, triangles=len(ids) // 3, reason='Authored default alpha zero.'))
        continue
    source_faces.append((mi, ids))

# Merge weights of every source bone that classifies to the same slot, so a
# vertex keeps its full influence budget after folding.
keys = [tuple(round(x, 5) for x in v['position']) for v in pmx.vertices]
merged = defaultdict(lambda: defaultdict(float))
for key, v in zip(keys, pmx.vertices):
    for j, w in zip(v['joints'], v['weights']):
        if j >= 0 and w > 1e-8: merged[key][classes[j]] += w

positions = []; normals = []; weights = []; uvs = []; rigid_head = []; hair_driven = []
for vi, v in enumerate(pmx.vertices):
    positions.append(tuple(uniform(sp(v['position']))))
    normals.append(tuple(sp(v['normal']).normalized()))
    uvs.append((v['uv'][0], 1 - v['uv'][1]))
    acc = dict(merged[keys[vi]])
    if vi in head_vertices: acc = {13: 1}; rigid_head.append(vi)
    elif vi in hair_vertices: acc = {j: w for j, w in acc.items() if j == 13 or j >= 30}
    ranked = sorted(((j, w) for j, w in acc.items() if w > 1e-8), key=lambda item: -item[1])[:4] or [(13, 1)]
    total = sum(w for j, w in ranked); ranked = [(j, w / total) for j, w in ranked]
    weights.append(ranked)
    if any(j >= 30 for j, w in ranked): hair_driven.append(vi)
geometry_error = max((Vector(positions[i]) - uniform(sp(v['position']))).length for i, v in enumerate(pmx.vertices))
assert geometry_error < 1e-8, geometry_error

# ---- materials and source textures ----
images = {}; source_hashes = []


def texture(relative):
    source = SRC / relative.replace('\\', '/'); destination = OUT / 'textures' / source.name
    if source.name not in images:
        shutil.copyfile(source, destination)
        image = bpy.data.images.load(str(destination), check_existing=True)
        image.pack(); images[source.name] = image
        source_hashes.append(dict(file=str(source.relative_to(SRC)), runtime='textures/' + source.name,
                                  sha256=hashlib.sha256(source.read_bytes()).hexdigest(), size=list(image.size)))
    return 'textures/' + source.name, images[source.name]


roughness_by_material = {'肌': .62, '颜': .55, '颜2': .55, '髪': .62, '前髪': .62, '髪+': .62, '前髪+': .62,
                         '体': .78, '袖': .78, '前摆': .78, '前摆2': .78, '裙': .78, '裙侧': .78, '裙侧内': .78,
                         '头饰': .4, '耳饰+神之眼AL': .32}
cutout_materials = {'睫', '二重', '眉', '肌', '星目'}
# The source spa_h PNG has alpha 0..41, so these are faint transparent
# highlights, not opaque replacement hair. Keep their original mesh passes.
transparent_materials = {'髪+', '前髪+'}
spec = []; materials = []; faces = []; material_ids = []; material_sources = []
for source_mi, ids in source_faces:
    m = pmx.materials[source_mi]; name = m['name']; texture_id = m['texture']; relative = None; image = None
    if texture_id >= 0: relative, image = texture(pmx.textures[texture_id])
    transparent = name in transparent_materials
    cutout = name in cutout_materials
    item = dict(name=name, sourceName=name, texture=relative or 'null',
                color=sum(round(max(0, min(1, c)) * 255) << (16 - 8 * i) for i, c in enumerate(m['diffuse'][:3])),
                twoSide=bool(m['flags'] & 1), opacity=1, transparent=transparent,
                alphaTest=.015 if transparent else .25 if cutout else 0, depthWrite=not transparent,
                roughness=roughness_by_material.get(name, .6), metalness=.3 if name == '耳饰+神之眼AL' else .04,
                textureAnisotropy=8)
    if name in ('肌', '颜', '颜2', '首'): item.update(skinSurface=True)
    if name in hair_materials: item.update(hairSurface=True, anisotropy=.35)
    mat = bpy.data.materials.new(name); mat.use_nodes = True
    bs = mat.node_tree.nodes.get('Principled BSDF')
    bs.inputs['Base Color'].default_value = (*m['diffuse'][:3], 1)
    bs.inputs['Roughness'].default_value = item['roughness']
    bs.inputs['Metallic'].default_value = item['metalness']
    bs.inputs['Specular IOR Level'].default_value = .25
    if image:
        node = mat.node_tree.nodes.new('ShaderNodeTexImage'); node.image = image
        mat.node_tree.links.new(node.outputs['Color'], bs.inputs['Base Color'])
        if transparent:
            mat.node_tree.links.new(node.outputs['Alpha'], bs.inputs['Alpha'])
        elif cutout:
            gate = mat.node_tree.nodes.new('ShaderNodeMath'); gate.operation = 'GREATER_THAN'
            gate.inputs[1].default_value = .25
            mat.node_tree.links.new(node.outputs['Alpha'], gate.inputs[0])
            mat.node_tree.links.new(gate.outputs[0], bs.inputs['Alpha'])
    mi = len(spec); spec.append(item); materials.append(mat); material_sources.append(source_mi)
    for a, b, c in zip(ids[::3], ids[1::3], ids[2::3]): faces.append((a, c, b)); material_ids.append(mi)

mesh = bpy.data.meshes.new('YaeMiko PMX native-rest surface')
mesh.from_pydata(positions, [], faces); mesh.update()
surface = bpy.data.objects.new('八重神子 · 原版动作适配', mesh)
bpy.context.collection.objects.link(surface)
for material in materials: mesh.materials.append(material)
uv = mesh.uv_layers.new(name='Source PMX UV')
for polygon in mesh.polygons:
    polygon.material_index = material_ids[polygon.index]; polygon.use_smooth = True
    for li in polygon.loop_indices: uv.data[li].uv = uvs[mesh.loops[li].vertex_index]
mesh.normals_split_custom_set_from_vertices(normals)

bone_names = [b['name'] for b in B] + [b['name'] for b in hair_bones]
for name in bone_names: surface.vertex_groups.new(name=name)
skin_indices = []; skin_weights = []
for vi, ranked in enumerate(weights):
    for j, w in ranked: surface.vertex_groups[j].add([vi], w, 'REPLACE')
    skin_indices.extend([j for j, w in ranked] + [0] * (4 - len(ranked)))
    skin_weights.extend([round(w, 7) for j, w in ranked] + [0] * (4 - len(ranked)))

rig = dict(schema=1, type='web-spring-bone', nativeBoneCount=30, bones=hair_bones,
           hairMaterials=[i for i, m in enumerate(spec) if m.get('hairSurface')],
           vertexCount=len(hair_driven),
           colliders=[dict(shape='sphere', bone=13, offset=[0, 0, 0], radius=1.8),
                      dict(shape='capsule', bone=12, endBone=1, radius=2.1),
                      dict(shape='capsule', bone=15, endBone=23, radius=1.3)],
           provenance='Source PMX hair hierarchy and vertex influences retained; restrained Web springs, not the original MMD rigid-body solver.')
skin = dict(schema=1, coordinateSystem='original-native-Z-up', bodyRig=body_rig, materials=spec,
            positions=[round(v, 7) for p in positions for v in p],
            normals=[round(v, 7) for p in normals for v in p],
            uvs=[round(v, 8) for p in uvs for v in p],
            skinIndices=skin_indices, skinWeights=skin_weights,
            faces=[dict(material=i, indices=list(f)) for i, f in zip(material_ids, faces)],
            vertexCount=len(positions), triangleCount=len(faces), secondaryMotion=rig)
(OUT / 'mesh.json').write_text(json.dumps(skin, separators=(',', ':')))

credits = '模型提供：miHoYo；模型改造：观海（BiliBili：观海子）。'
manifest = dict(
    schema=1, characterId=0, appearance='yaemiko', label='八重神子 · 模型适配', mesh='mesh.json', complete=True,
    completeness=dict(bodyGeometry=True, headHairGeometry=True, eyes=True, faceGeometry=True,
                      sourcePmxSkeleton=True, originalSourceGameSkeleton=False),
    stats=dict(sourceVertices=len(pmx.vertices), sourceTriangles=len(pmx.indices) // 3,
               vertices=len(positions), triangles=len(faces), sourceBones=len(pmx.bones), bones=30, dummies=6,
               secondaryBones=len(hair_bones), materials=len(spec), textures=len(images),
               omittedTriangles=sum(m['triangles'] for m in hidden)),
    retarget=dict(
        method='Original mesh proportions preserved by a single uniform transform; independent source-length display skeleton follows original AMB/POS rotations; display weapon sockets follow the new hands.',
        provisional=True, sourceSkeletonMissing=False, hairPhysics=True,
        hairPhysicsProfile='web-spring-bone-v2-restrained', originalMmdPhysics=False, clothPhysics=False,
        fingerArticulation='Thumb and index chains of the native rig drive source finger groups; other fingers fold into those chains.'),
    provenance=dict(sourceArchive='assets/source/yaemiko', sourceModel=audit['name'], modelAuthor='miHoYo',
                    rigAuthor='观海（BiliBili：观海子）', credit=credits,
                    license='Original distribution readme retained verbatim. It forbids redistribution, part extraction and commercial use; this is a user-requested local adaptation, not a rights grant or published distribution.',
                    limits=['Original source proportions preserved; action retarget remains approximate.',
                            'Source PMX has no verified real-world centimetre calibration; no physical height is claimed.',
                            'Source hair skeleton and weights retained but MMD rigid bodies are not executed.',
                            'Skirt folds follow their source parent body region; sleeves and attached tassels follow the arm; no cloth solver.',
                            'No expression morph or independent per-finger solver.',
                            'Original toon ramp and sphere-map lighting are not reproduced; original base colour, transparent hair highlight passes, alpha cutout and roughness are used.']),
    omittedRenderPasses=hidden,
    sourceFiles=[dict(file=pmx.path.name, bytes=len(pmx.data), sha256=hashlib.sha256(pmx.data).hexdigest())] + source_hashes)
(OUT / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2))
notes = (SRC / '原始配布Readme.txt').read_text()
(OUT / '原始配布Readme.txt').write_text(notes)
(OUT / '署名.txt').write_text(credits + '\n')

arm, rest, rest_error = build_source_armature(surface, body_rig, hair_bones, label='八重神子')
clips, pose_error = bake_source_samples(arm, body_rig, rest)
arm['web_hair_springs'] = json.dumps(rig, ensure_ascii=False)
arm['README'] = 'Original body AMB actions are baked. Hair follows the head in Blender; restrained spring simulation runs in Web. Jump world arc is applied by the game host.'
scene = bpy.context.scene
scene['attribution'] = credits
scene['source_archive'] = 'assets/source/yaemiko'
scene['source_readme'] = notes
bpy.ops.wm.save_as_mainfile(filepath=str(WORK / '八重神子-流星动作适配.blend'))

evidence = dict(blender=bpy.app.version_string, sourceArchive='assets/source/yaemiko', sourceDownloadsRequired=False,
                restMatrixError=rest_error, poseMatrixError=pose_error, bakedActions=clips, stats=manifest['stats'],
                sourceMaterialMap=material_sources, rigidHeadVertices=len(rigid_head), hairVertices=len(hair_driven),
                hiddenMaterials=hidden, sourceUniformScale=uniform_scale, sourceGeometryMaxError=geometry_error,
                proportionalDisplayRig=True,
                packedImages=[dict(name=i.name, packed=bool(i.packed_file), size=list(i.size)) for i in images.values()],
                hashes={name: hashlib.sha256((OUT / name).read_bytes()).hexdigest() for name in ['manifest.json', 'mesh.json']})
(WORK / 'build-evidence.json').write_text(json.dumps(evidence, ensure_ascii=False, indent=2))
print('YAEMIKO_READY', json.dumps(manifest['stats'], ensure_ascii=False), 'REST', rest_error, 'POSE', pose_error, flush=True)