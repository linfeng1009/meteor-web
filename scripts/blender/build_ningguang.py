"""Build Ningguang (凝光 · 纱中幽兰) directly from the editable .blend.

Blender --background --factory-startup --disable-autoexec --python scripts/blender/build_ningguang.py

Unlike the PMX imports this reads the author's own Blender scene: one skinned mesh
plus one 94-bone MMD-style armature, textures packed inside the file. The same
proportion policy applies: every vertex goes through ONE uniform scale and a floor
offset taken from the foot vertices, so the body cannot be compressed or widened.
"""
import bpy, json, math, hashlib, shutil
from pathlib import Path
from collections import defaultdict
from mathutils import Vector
import sys
sys.path.insert(0, str(Path(__file__).parent))
from hutao_native_rest import B, world as REST
from proportional_authoring import build_source_armature, bake_source_samples

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / 'assets/source/ningguang'
BLEND_NAME = '凝光_纱中幽兰_可编辑.blend'
OUT = ROOT / 'dist/assets/enhanced/ningguang'
WORK = ROOT / 'work/ningguang-import-2026-11-11'
for path in [OUT, OUT / 'textures', WORK]: path.mkdir(parents=True, exist_ok=True)

MESH_NAME = '凝光_mesh'
ARM_NAME = '凝光_arm'
bpy.ops.wm.open_mainfile(filepath=str(SRC / BLEND_NAME))
ob = bpy.data.objects[MESH_NAME]
arm = bpy.data.objects[ARM_NAME]
mesh = ob.data
bones = list(arm.data.bones)
bone_pos = {b.name: b.head_local.copy() for b in bones}
bone_parent = {b.name: (b.parent.name if b.parent else None) for b in bones}
group_bone = {g.index: g.name for g in ob.vertex_groups}

# ---- material layers that duplicate other surfaces -------------------------
# The author ships a preview node group ("隐藏共面叠色层") for exactly this:
# 肌 repeats 体2's vertices and 肌2 sits inside 体. Drawing both would double
# shade the same surface, so the overlay pass is recorded and dropped.
OVERLAY_OF = {'肌': '体2', '肌2': '体'}

material_names = [m.name if m else f'material_{i}' for i, m in enumerate(mesh.materials)]
kept = [i for i, n in enumerate(material_names) if n not in OVERLAY_OF]

# ---- uniform transform -----------------------------------------------------
zs = [v.co.z for v in mesh.vertices]
top = max(zs)
sole = [v.co.z for v in mesh.vertices
        if any(group_bone[g.group] in ('足.L', '足.R', '足首.L', '足首.R', '足先EX.L', '足先EX.R', 'つま先.L', 'つま先.R')
               and g.weight >= .5 for g in v.groups)]
floor = min(sole) if sole else min(zs)
mesh_floor = min(zs)
scale = 39.4 / (top - floor)
print('TOP', top, 'FLOOR', floor, 'MESH_FLOOR', mesh_floor, 'SCALE', scale, flush=True)


def uniform(p): return Vector((p.x * scale, p.y * scale, (p.z - floor) * scale))


# ---- 30 native slots -------------------------------------------------------
# This rig uses MMD names with .L/.R suffixes instead of 左/右 prefixes.
SIDED = {'肩': (14, 22), '腕': (15, 23), 'ひじ': (16, 24), '手首': (17, 25),
         '足': (3, 7), 'ひざ': (4, 8), '足首': (5, 9), '足先EX': (6, 10), 'つま先': (6, 10), '踵': (5, 9),
         '親指０': (18, 26), '親指１': (19, 27), '親指２': (19, 27), '親指先': (19, 27),
         '人指１': (20, 28), '人指２': (21, 29), '人指３': (21, 29), '人指先': (21, 29),
         '中指１': (20, 28), '中指２': (21, 29), '中指３': (21, 29), '中指先': (21, 29),
         '薬指１': (20, 28), '薬指２': (21, 29), '薬指３': (21, 29), '薬指先': (21, 29),
         '小指１': (20, 28), '小指２': (21, 29), '小指３': (21, 29), '小指先': (21, 29)}
CENTER = {'操作中心': 0, '全ての親': 0, 'センター': 0, 'センター2': 0, 'グルーブ': 0, 'グルーブ2': 0,
          '腰': 2, '下半身': 1, '上半身': 2, '上半身2': 11, '上半身3': 11, '首': 12, '頭': 13,
          'おっぱい調整': 11, '胸上': 11, '胸下': 11, '胸先': 11, '胸': 11, 'ス親': 11}
SKIP = {'足IK親.L', '足IK親.R', '足ＩＫ.L', '足ＩＫ.R', 'つま先ＩＫ.L', 'つま先ＩＫ.R'}

_slot_cache = {}


def slot_of(name, seen=None):
    if name in _slot_cache: return _slot_cache[name]
    if name in SKIP or name is None: return None
    seen = set() if seen is None else seen
    if name in seen: return None
    seen.add(name)
    base, _, side = name.partition('.')
    if base in CENTER:
        return CENTER[base]
    if base in SIDED:
        left, right = SIDED[base]
        return left if side == 'L' else right if side == 'R' else None
    if base.startswith('目') or base.startswith('齿') or base.startswith('齿') or base in ('両目',):
        return 13
    parent = bone_parent.get(name)
    result = slot_of(parent, seen) if parent else None
    if parent is None or result is not None:
        _slot_cache[name] = result
    return result


ANCHORS = ['センター', '下半身', '上半身', '足.L', 'ひざ.L', '足首.L', '足先EX.L',
           '足.R', 'ひざ.R', '足首.R', '足先EX.R', '上半身2', '首', '頭',
           '肩.L', '腕.L', 'ひじ.L', '手首.L', '親指０.L', '親指１.L', '中指１.L', '中指３.L',
           '肩.R', '腕.R', 'ひじ.R', '手首.R', '親指０.R', '親指１.R', '中指１.R', '中指３.R']
missing = [n for n in ANCHORS if n not in bone_pos]
assert not missing, missing
anchors = [uniform(bone_pos[n]) for n in ANCHORS]
parents = [-1, 0, 0, 1, 3, 4, 5, 1, 7, 8, 9, 2, 11, 12, 11, 14, 15, 16, 17, 18, 17, 20, 11, 22, 23, 24, 25, 26, 25, 28]
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
                sourceUniformScale=scale, sourceFloor=floor)

# ---- vertices --------------------------------------------------------------
head_materials = {'颜', '颜2', '白目', '眉', '二重', '睫', '目光', '目', '星目', '齿', '口舌'}
head_polys = {p.index for p in mesh.polygons if material_names[p.material_index] in head_materials}
head_vertices = set()
for pi in head_polys:
    head_vertices.update(mesh.polygons[pi].vertices)

# These layers share vertex positions exactly with the layer underneath them
# (measured: 颜2 vs 颜 46 shared points, 白目 vs 颜2 46, 睫 vs 颜 32). MMD draws
# them in a fixed order; a depth-tested renderer needs a physical bias.
DECAL_OFFSET = {'颜2': .0015, '白目': .0025, '睫': .0035}
decal_of_vertex = {}
for poly in mesh.polygons:
    off = DECAL_OFFSET.get(material_names[poly.material_index])
    if off is None: continue
    for vi in poly.vertices:
        if off > decal_of_vertex.get(vi, 0.0): decal_of_vertex[vi] = off

uv_layer = mesh.uv_layers.active
first_loop = {}
for loop in mesh.loops:
    first_loop.setdefault(loop.vertex_index, loop.index)
positions = []; normals = []; uvs = []; weights = []
for v in mesh.vertices:
    n_up = v.normal.normalized()
    bias = decal_of_vertex.get(v.index, 0.0)
    positions.append(tuple(uniform(v.co + n_up * bias)))
    n = v.normal.normalized()
    normals.append((n.x, n.y, n.z))
    li = first_loop.get(v.index)
    uv = uv_layer.data[li].uv if li is not None else (0.0, 0.0)
    # Blender image rows start at the bottom, and three.js uploads textures with
    # flipY=true, so the authored V is already the runtime V. (PMX needed 1-v.)
    uvs.append((uv[0], uv[1]))
    acc = defaultdict(float)
    for g in v.groups:
        if g.weight <= 1e-8: continue
        slot = slot_of(group_bone[g.group])
        if slot is not None: acc[slot] += g.weight
    if v.index in head_vertices: acc = {13: 1.0}
    ranked = sorted(acc.items(), key=lambda kv: -kv[1])[:4] or [(13, 1.0)]
    total = sum(w for _, w in ranked)
    weights.append([(s, w / total) for s, w in ranked])

# The only intentional deviation from a pure uniform transform is the decal
# bias above, so it is measured separately: undecaled vertices must be exact.
geometry_error = max((Vector(positions[i]) - uniform(mesh.vertices[i].co)).length
                     for i in range(len(positions)) if i not in decal_of_vertex)
assert geometry_error < 1e-9, geometry_error
decal_error = max((Vector(positions[i]) - uniform(mesh.vertices[i].co)).length for i in decal_of_vertex)
assert decal_error <= max(DECAL_OFFSET.values()) * scale * 1.01, decal_error

# ---- materials and packed textures ----------------------------------------
images = {}; source_hashes = []


def save_image(image):
    name = image.name
    if name in images: return 'textures/' + name
    target = OUT / 'textures' / name
    if not target.suffix: target = target.with_suffix('.png')
    image.filepath_raw = str(target)
    image.file_format = 'PNG'
    image.save()
    images[name] = target.name
    source_hashes.append(dict(file='packed:' + name, runtime='textures/' + target.name,
                              sha256=hashlib.sha256(target.read_bytes()).hexdigest(), size=list(image.size)))
    return 'textures/' + target.name


ROUGHNESS = {'髪': .55, '颜': .55, '颜2': .55, '白目': .5, '目': .35, '目光': .3, '星目': .3,
             '眉': .55, '二重': .55, '睫': .55, '肌': .6, '肌2': .6, '体': .68, '体2': .68,
             '鞋1': .5, '神之眼': .22, '神之眼AL': .22, '头饰': .35, '头饰2': .35, '耳饰': .3,
             '首饰': .35, '手饰': .35, '臂饰': .35, '挂饰1': .4, '流苏': .55, '裙': .75, '裙饰': .6}

spec = []; faces = []; material_ids = []
for mi in kept:
    mat = mesh.materials[mi]
    nt = mat.node_tree if (mat and mat.use_nodes) else None
    image = None
    if nt:
        node = nt.nodes.get('mmd_base_tex')
        if node is None:
            node = next((n for n in nt.nodes if n.type == 'TEX_IMAGE' and n.image and 'toon' not in n.name), None)
        if node is not None: image = node.image
    texture = save_image(image) if image is not None else 'null'
    method = getattr(mat, 'surface_render_method', None)
    blend = 'BLEND' if method == 'BLENDED' else 'CLIP' if method == 'DITHERED' else getattr(mat, 'blend_method', 'OPAQUE')
    transparent = blend == 'BLEND'
    cutout = blend == 'CLIP'
    item = dict(name=mat.name, sourceName=mat.name, texture=texture, color=0xffffff,
                twoSide=not bool(getattr(mat, 'use_backface_culling', False)),
                opacity=1, transparent=transparent,
                alphaTest=.015 if transparent else .5 if cutout else 0,
                depthWrite=not transparent,
                roughness=ROUGHNESS.get(mat.name, .62),
                metalness=.35 if mat.name.startswith('神之眼') else .04,
                textureAnisotropy=8)
    if mat.name in ('肌', '肌2', '颜', '颜2'): item.update(skinSurface=True)
    if mat.name == '髪': item.update(hairSurface=True, anisotropy=.35)
    spec.append(item)
    for poly in mesh.polygons:
        if poly.material_index != mi: continue
        idx = list(poly.vertices)
        if len(idx) == 3: faces.append(tuple(idx))
        else:
            for k in range(1, len(idx) - 1): faces.append((idx[0], idx[k], idx[k + 1]))
        material_ids.append(len(spec) - 1)

rig = None  # hair is rigid to the head in this model; no spring chain exists
skin = dict(schema=1, coordinateSystem='original-native-Z-up', bodyRig=body_rig, materials=spec,
            positions=[round(v, 7) for p in positions for v in p],
            normals=[round(v, 7) for p in normals for v in p],
            uvs=[round(v, 8) for p in uvs for v in p],
            skinIndices=[], skinWeights=[],
            faces=[dict(material=i, indices=list(f)) for i, f in zip(material_ids, faces)],
            vertexCount=len(positions), triangleCount=len(faces), secondaryMotion=None)
# pad each vertex to exactly four influences
pad_i = []; pad_w = []
for ranked in weights:
    slots = [s for s, _ in ranked] + [0] * (4 - len(ranked))
    vals = [round(w, 7) for _, w in ranked] + [0.0] * (4 - len(ranked))
    pad_i.extend(slots); pad_w.extend(vals)
skin['skinIndices'] = pad_i; skin['skinWeights'] = pad_w
(OUT / 'mesh.json').write_text(json.dumps(skin, separators=(',', ':')))

credits = '凝光「纱中幽兰」可编辑模型；原模型版权归 miHoYo，本包未附署名或配布说明文件。'
manifest = dict(
    schema=1, characterId=0, appearance='ningguang', label='凝光 · 纱中幽兰', mesh='mesh.json', complete=True,
    completeness=dict(bodyGeometry=True, headHairGeometry=True, eyes=True, faceGeometry=True,
                      sourcePmxSkeleton=False, originalSourceGameSkeleton=False),
    stats=dict(sourceVertices=len(mesh.vertices), sourceTriangles=len(mesh.polygons),
               vertices=len(positions), triangles=len(faces), sourceBones=len(bones), bones=30, dummies=6,
               secondaryBones=0, materials=len(spec), textures=len(images),
               omittedTriangles=sum(1 for p in mesh.polygons if material_names[p.material_index] in OVERLAY_OF)),
    retarget=dict(
        method='Original mesh proportions preserved by a single uniform transform; independent source-length display skeleton follows original AMB/POS rotations; display weapon sockets follow the new hands.',
        provisional=True, sourceSkeletonMissing=False, hairPhysics=False, hairPhysicsProfile='none (hair is rigid to the head)',
        originalMmdPhysics=False, clothPhysics=False,
        fingerArticulation='Thumb and index chains of the native rig drive the source finger groups; other fingers fold into those two chains.'),
    provenance=dict(sourceArchive='assets/source/ningguang', sourceModel=BLEND_NAME,
                    modelAuthor='miHoYo（原模型）', rigAuthor='未提供署名文件', credit=credits,
                    license='No readme, credit or licence file was shipped with this pack. Treated as a private local conversion; not redistributed or published.',
                    limits=['Original source proportions preserved; action retarget remains approximate.',
                            'Source is a .blend scene, not a PMX, so PMX-specific statistics are not applicable.',
                            'Co-planar colour layers 肌 (duplicate of 体2) and 肌2 (inside 体) are skipped.',
                            'Hair has no secondary chain in the source; it stays rigid on the head.',
                            'Skirt and sash cloth are rigid on their parent body bones; no cloth solver.',
                            'No expression morphs; sphere/toon maps are not reproduced.']),
    omittedRenderPasses=[dict(material=k, duplicateOf=v, reason='Co-planar colour layer sharing the base surface vertices.') for k, v in OVERLAY_OF.items()],
    sourceFiles=[dict(file=BLEND_NAME, bytes=(SRC / BLEND_NAME).stat().st_size,
                      sha256=hashlib.sha256((SRC / BLEND_NAME).read_bytes()).hexdigest())] + source_hashes)
(OUT / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2))

# ---- editable surface + baked actions -------------------------------------
surface = bpy.data.objects.new('凝光 · 纱中幽兰 · 原版动作适配', ob.data.copy())
bpy.context.collection.objects.link(surface)
# The source ships 53 MMD morphs. Direct vertex writes are ignored while shape
# keys exist, so they are cleared on this editable copy (the runtime has no morph
# support) before the uniform transform is baked into the mesh.
if surface.data.shape_keys: surface.shape_key_clear()
surface.modifiers.clear()
while surface.vertex_groups:
    surface.vertex_groups.remove(surface.vertex_groups[0])
for e in B:
    surface.vertex_groups.new(name=e['name'])
for vi, ranked in enumerate(weights):
    for slot, weight in ranked:
        surface.vertex_groups[slot].add([vi], weight, 'REPLACE')
for v in surface.data.vertices: v.co = uniform(v.co)
armature, rest, rest_error = build_source_armature(surface, body_rig, [], label='凝光')
clips, pose_error = bake_source_samples(armature, body_rig, rest)
scene = bpy.context.scene
scene['attribution'] = credits
scene['source_archive'] = 'assets/source/ningguang'
bpy.ops.wm.save_as_mainfile(filepath=str(WORK / '凝光-纱中幽兰-流星动作适配.blend'))

evidence = dict(blender=bpy.app.version_string, source='assets/source/ningguang/' + BLEND_NAME,
                sourceFormat='blend', sourceDownloadsRequired=False,
                restMatrixError=rest_error, poseMatrixError=pose_error, bakedActions=clips,
                sourceGeometryMaxError=geometry_error, decalVertices=len(decal_of_vertex), decalBiasSource=DECAL_OFFSET,
                decalBiasMax=decal_error, proportionalDisplayRig=True,
                sourceBones=len(bones), nativeSlots=30, secondaryBones=0,
                meshFloor=mesh_floor, soleFloor=floor, geometryBelowSole=floor - mesh_floor,
                stats=manifest['stats'], skippedOverlays=OVERLAY_OF,
                hashes={name: hashlib.sha256((OUT / name).read_bytes()).hexdigest() for name in ['manifest.json', 'mesh.json']})
evidence['packedImages'] = [dict(name=r['runtime'], size=r['size'], sha256=r['sha256']) for r in source_hashes]
(WORK / 'build-evidence.json').write_text(json.dumps(evidence, ensure_ascii=False, indent=2))
print('NINGGUANG_READY', json.dumps(manifest['stats'], ensure_ascii=False), 'REST', rest_error, 'POSE', pose_error, flush=True)