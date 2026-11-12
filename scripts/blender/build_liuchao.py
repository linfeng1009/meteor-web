"""Export 琉潮 from its archived Blender scene to the game.
Run Blender --background --factory-startup --disable-autoexec --python scripts/blender/build_liuchao.py
"""
import bpy,json,hashlib,math,sys
from pathlib import Path
from collections import Counter, defaultdict
from mathutils import Vector
import numpy as np
sys.path.insert(0,str(Path(__file__).parent))
from hutao_native_rest import B, world as REST
ROOT=Path(__file__).resolve().parents[2]
SRC=ROOT/'assets/source/liuchao/琉潮.blend'
OUT=ROOT/'dist/assets/enhanced/liuchao'
WORK=ROOT/'work/liuchao-import-2026-11-11'
for d in (OUT,OUT/'textures',WORK):d.mkdir(parents=True,exist_ok=True)
bpy.ops.wm.open_mainfile(filepath=str(SRC))
arm=bpy.data.objects['角色骨骼 · 官方夜兰 MMD']
arm.data.pose_position='REST'
bpy.context.view_layer.update()
bones=list(arm.data.bones)
bone_pos={b.name:arm.matrix_world @ b.head_local for b in bones}
bone_parent={b.name:b.parent.name if b.parent else None for b in bones}
objects=[o for o in bpy.context.scene.objects if o.type in {'MESH','CURVE'} and not o.hide_render and any(c.name.startswith(('01 ·','02 ·','03 ·','04 ·')) for c in o.users_collection)]
assert len(objects)>100
BODY = '身体 · 连续曲面'
SWIM_BOTTOM = '泳装下装 · 连续布面'
HAIR_CAP = '髮.001'
HAIR_LOCKS = '海蓝黑 · 青绿渐变发束'
# Preserve the source. For the runtime only, reduce the dense body and cap subdivision.
for o in objects:
 if o.type=='CURVE':
  o.data.resolution_u=min(o.data.resolution_u,4)
  o.data.bevel_resolution=min(o.data.bevel_resolution,2)
 for m in o.modifiers:
  if m.type=='ARMATURE': m.show_viewport=False
  if m.type=='SUBSURF' and not o.name.startswith(('低束马尾 · 发束', '鬓边青色发梢')):
   m.levels=min(m.levels,1)
 if o.name==BODY:
  m=o.modifiers.new('Runtime body reduction','DECIMATE');m.ratio=.42
bpy.context.view_layer.update()
deps=bpy.context.evaluated_depsgraph_get()
# Use the actual rendered soles as the ground plane, including the shoe thickness.
sole_heights = []
for ob in objects:
    if not ob.name.startswith('凉鞋 · 鞋底'):
        continue
    evaluated = ob.evaluated_get(deps)
    sole_mesh = evaluated.to_mesh()
    sole_heights.extend((evaluated.matrix_world @ vertex.co).z for vertex in sole_mesh.vertices)
    evaluated.to_mesh_clear()
assert sole_heights, 'The source sandal soles are missing'
floor = min(sole_heights)
top=max((o.matrix_world @ Vector(corner)).z for o in objects for corner in o.bound_box)
scale=39.4/(top-floor)
def uniform(p): return Vector((p.x*scale,p.y*scale,(p.z-floor)*scale))
SIDED = {'肩': (14, 22), '腕': (15, 23), 'ひじ': (16, 24), '手首': (17, 25),
         '足': (3, 7), '足D': (3, 7), 'ひざ': (4, 8), 'ひざD': (4, 8),
         '足首': (5, 9), '足首D': (5, 9), '足先EX': (5, 9), 'つま先': (5, 9), '踵': (5, 9),
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
links = {3: 4, 4: 5, 7: 8, 8: 9, 14: 15, 15: 16, 16: 17, 17: 21, 18: 19, 20: 21,
         22: 23, 23: 24, 24: 25, 25: 29, 26: 27, 28: 29}
body_bones = []
for i, e in enumerate(B):
    q = REST[e['name']].to_quaternion()
    if i in links or i in (5, 9):
        j = i + 1 if i in (5, 9) else links[i]
        native_axis = REST[B[j]['name']].translation - REST[e['name']].translation
        source_axis = anchors[j] - anchors[i]
        if i in (5, 9):
            # These toe pivots sit at different depths below the ankles. Only
            # align their headings so a flat sandal stays flat in a planted pose.
            native_axis.z = source_axis.z = 0
        if native_axis.length > 1e-5 and source_axis.length > 1e-5:
            q = native_axis.normalized().rotation_difference(source_axis.normalized()) @ q
    body_bones.append(dict(name=e['name'], nativeBone=i, parent=parents[i], position=list(anchors[i]),
                           rotation=[q.x, q.y, q.z, q.w]))
body_rig = dict(schema=1, type='source-proportions', bones=body_bones,
                nativeRootBind=list(REST[B[0]['name']].translation),
                sourceUniformScale=scale, sourceFloor=floor)


def smoothstep(low, high, value):
    t = min(1.0, max(0.0, (value - low) / (high - low)))
    return t * t * (3 - 2 * t)


def smooth_shoulder_surface(mesh, world_matrix):
    """Soften the rear deltoid join on the exported body mesh."""
    local = np.empty((len(mesh.vertices), 3), dtype=np.float32)
    mesh.vertices.foreach_get('co', local.ravel())
    transform = np.asarray(world_matrix, dtype=np.float64)
    native = (local @ transform[:3, :3].T + transform[:3, 3]) * scale
    native[:, 2] -= floor * scale

    # Use Springfield's continuous upper-back profile as the shape reference.
    # Fade out at the spine, neck, front of the shoulder and lower upper arm.
    width = (abs(anchors[15].x) + abs(anchors[23].x)) / 2
    shoulder_height = (anchors[15].z + anchors[23].z) / 2
    shoulder_depth = (anchors[15].y + anchors[23].y) / 2
    lateral = np.abs(native[:, 0]) - width
    vertical = native[:, 2] - shoulder_height
    posterior = native[:, 1] - shoulder_depth

    def falloff(low, high, values):
        t = np.clip((values - low) / (high - low), 0.0, 1.0)
        return t * t * (3 - 2 * t)

    influence = (
        falloff(-1.54, -.54, lateral)
        * (1 - falloff(1.01, 2.46, lateral))
        * falloff(-3.31, -1.71, vertical)
        * falloff(-.84, .46, posterior)
    )
    active = np.flatnonzero(influence > 1e-5)
    assert len(active), 'The shoulder region is missing from the body mesh'

    edges = np.empty((len(mesh.edges), 2), dtype=np.int32)
    mesh.edges.foreach_get('vertices', edges.ravel())
    neighbors = np.concatenate((edges, edges[:, ::-1]))
    active_lookup = np.full(len(local), -1, dtype=np.int32)
    active_lookup[active] = np.arange(len(active), dtype=np.int32)
    neighbors = neighbors[active_lookup[neighbors[:, 0]] >= 0]
    row = active_lookup[neighbors[:, 0]]
    adjacent = neighbors[:, 1]
    degree = np.bincount(row, minlength=len(active))
    strength = (influence[active] * .5)[:, None]
    original = native.copy()
    for _ in range(190):
        average = np.column_stack([
            np.bincount(row, weights=native[adjacent, axis], minlength=len(active)) / degree
            for axis in range(3)
        ])
        native[active] += (average - native[active]) * strength

    # Keep the existing weight field anchored to the original bind positions.
    # Recompute the surface normals from the adjusted mesh before export.
    adjusted = local.copy()
    displacement = (native[active] - original[active]) / scale
    adjusted[active] += displacement @ np.linalg.inv(transform[:3, :3]).T
    mesh.vertices.foreach_set('co', adjusted.ravel())
    mesh.update()
    return local


def blend_shoulder_weights(position, weights):
    # The generated body mesh has chest and upper-arm groups but no clavicle
    # group. Bridge those groups locally at the shoulder and armpit.
    clavicle, upper_arm = (14, 15) if position.x >= 0 else (22, 23)
    shoulder = anchors[upper_arm]
    distance_from_center = abs(position.x)
    shoulder_width = abs(shoulder.x)
    height = smoothstep(shoulder.z - 4.7, shoulder.z - 0.7, position.z)
    lateral = smoothstep(shoulder_width - 1.5, shoulder_width + 0.4, distance_from_center)
    depth = 1 - smoothstep(0.9, 2.4, abs(position.y - shoulder.y))
    region = height * lateral * depth
    original_arm = weights.get(upper_arm, 0.0)
    original_chest = weights.get(11, 0.0)
    total = original_arm + original_chest
    if region <= 1e-6 or total <= 1e-6:
        return
    # Spread the chest-to-arm change over the upper shoulder instead of
    # stretching the same narrow ring of vertices in every animation frame.
    arm_fraction = smoothstep(shoulder_width - 0.7, shoulder_width + 3.2, distance_from_center)
    arm_weight = original_arm * (1 - region) + total * arm_fraction * region
    chest_weight = total - arm_weight
    from_chest = chest_weight * region * 0.25
    from_arm = arm_weight * (1 - arm_weight) * region * 0.35
    weights[11] = chest_weight - from_chest
    weights[upper_arm] = arm_weight - from_arm
    weights[clavicle] += from_chest + from_arm


def swim_bottom_profile():
    garment = bpy.data.objects[SWIM_BOTTOM]
    edge_uses = Counter(tuple(sorted(edge)) for face in garment.data.polygons for edge in face.edge_keys)
    rim = defaultdict(set)
    for (a, b), uses in edge_uses.items():
        if uses == 1:
            rim[a].add(b)
            rim[b].add(a)
    assert all(len(neighbors) == 2 for neighbors in rim.values()), 'Expected closed swimsuit rims'

    loops = []
    while rim:
        first = next(iter(rim))
        pending = [first]
        loop = []
        while pending:
            index = pending.pop()
            if index not in rim:
                continue
            pending.extend(rim.pop(index))
            loop.append(uniform(garment.matrix_world @ garment.data.vertices[index].co))
        loops.append(np.array(loop))
    assert len(loops) == 2, 'Expected two swimsuit rims'
    leg_rim, waist_rim = sorted(loops, key=lambda loop: loop[:, 2].mean())
    center = waist_rim[:, :2].mean(axis=0)

    def profile(loop):
        xy = loop[:, :2] - center
        return np.arctan2(xy[:, 1], xy[:, 0]), loop[:, 2]

    return center, profile(leg_rim), profile(waist_rim)


def append_swim_body_faces(mesh, base, skin_material, cloth_material):
    # Cut the cloth panel along the authored waist and leg-opening profiles.
    # Cloth and skin share the same edge vertices and skinning, so the surface
    # stays closed when the hips rotate or either leg bends.
    center, leg_profile, waist_profile = swim_bottom_profile()
    points = np.array(positions[base * 3:]).reshape(-1, 3)
    angle = np.arctan2(points[:, 1] - center[1], points[:, 0] - center[0])
    leg_height = np.interp(angle, *leg_profile, period=2 * np.pi)
    waist_height = np.interp(angle, *waist_profile, period=2 * np.pi)
    distances = list(zip(waist_height - points[:, 2], points[:, 2] - leg_height))
    cuts = {}

    def cut_vertex(a, b, rim_index):
        key = (*sorted((a, b)), rim_index)
        if key in cuts:
            return cuts[key]
        da, db = distances[a][rim_index], distances[b][rim_index]
        if abs(da) <= 1e-7:
            return a
        if abs(db) <= 1e-7:
            return b
        t = da / (da - db)
        index = len(positions) // 3 - base
        cuts[key] = index
        distances.append(tuple((1 - t) * x + t * y for x, y in zip(distances[a], distances[b])))

        def interpolate(array, count):
            start, end = (base + a) * count, (base + b) * count
            return [(1 - t) * array[start + i] + t * array[end + i] for i in range(count)]

        positions.extend(round(value, 6) for value in interpolate(positions, 3))
        normals.extend(round(value, 6) for value in Vector(interpolate(normals, 3)).normalized())
        uvs.extend(round(value, 7) for value in interpolate(uvs, 2))
        weights = defaultdict(float)
        for vertex, share in ((a, 1 - t), (b, t)):
            start = (base + vertex) * 4
            for slot, weight in zip(skin_i[start:start + 4], skin_w[start:start + 4]):
                weights[slot] += share * weight
        append_skin_weights(weights, 1)
        return index

    def split(polygon, rim_index):
        inside, outside = [], []
        for a, b in zip(polygon, polygon[1:] + polygon[:1]):
            a_in = distances[a][rim_index] >= 0
            b_in = distances[b][rim_index] >= 0
            (inside if a_in else outside).append(a)
            if a_in != b_in:
                vertex = cut_vertex(a, b, rim_index)
                inside.append(vertex)
                outside.append(vertex)
        return inside, outside

    def emit(polygon, material):
        if len(polygon) < 3:
            return
        for i in range(1, len(polygon) - 1):
            triangle = [base + polygon[k] for k in (0, i, i + 1)]
            if len(set(triangle)) == 3:
                faces.append({'material': material, 'indices': triangle})

    for tri in mesh.loop_triangles:
        below_waist, torso = split(list(tri.vertices), 0)
        emit(torso, skin_material)
        if len(below_waist) >= 3:
            cloth, legs = split(below_waist, 1)
            emit(cloth, cloth_material)
            emit(legs, skin_material)


def strand_uvs(mesh):
    # The author stores root-to-tip position on the strand mesh, rather than
    # in a UV map. Keep it as U so anisotropic highlights follow the strand.
    gradient = mesh.attributes['发尾渐变']
    length = np.array([value.value for value in gradient.data])
    points = np.array([vertex.co[:] for vertex in mesh.vertices])
    root = points[length <= np.quantile(length, .2)].mean(axis=0)
    tip = points[length >= np.quantile(length, .8)].mean(axis=0)
    axis = tip - root
    axis /= max(np.linalg.norm(axis), 1e-6)
    across = np.cross(axis, [0., 1., 0.])
    if np.linalg.norm(across) < .2:
        across = np.cross(axis, [0., 0., 1.])
    width = points @ across
    return np.column_stack((
        np.clip(length, 0, 1),
        (width - width.min()) / max(np.ptp(width), 1e-6),
    ))


def save_hair_map(name, pixels):
    height, width = pixels.shape[:2]
    image = bpy.data.images.new(name, width=width, height=height, alpha=False)
    rgba = np.ones((height, width, 4), dtype=np.float32)
    rgba[:, :, :3] = np.clip(pixels, 0, 1)
    image.pixels.foreach_set(rgba.ravel())
    image.filepath_raw = str(OUT / 'textures' / name)
    image.file_format = 'JPEG' if name.endswith('.jpg') else 'PNG'
    image.save(quality=96)
    bpy.data.images.remove(image)
    saved[name] = 'textures/' + name
    return saved[name]


def make_hair_lock_map(nodes):
    ramp = next(node.color_ramp for node in nodes if node.type == 'VALTORGB')
    length = np.linspace(0, 1, 256)
    color = np.array([ramp.evaluate(float(value))[:3] for value in length])
    width = np.linspace(0, 1, 128)[:, None]
    # Springfield's diffuse map keeps fine longitudinal color variations.
    # Use that treatment with Liuchao's own navy-to-teal color ramp.
    grain = .09 * np.sin(2 * np.pi * (width * 9 + length * .13))
    grain += .035 * np.sin(2 * np.pi * (width * 23 - length * .22))
    linear = color[None, :, :] * (1 + grain[:, :, None])
    srgb = np.where(linear <= .0031308, linear * 12.92, 1.055 * np.maximum(linear, 0) ** (1 / 2.4) - .055)
    return save_hair_map('hair-locks.png', srgb)


def make_hair_cap_map(image):
    width, height = image.size
    pixels = np.empty(width * height * 4, dtype=np.float32)
    image.pixels.foreach_get(pixels)
    rgb = pixels.reshape(height, width, 4)[:, :, :3]
    # Bring out the existing strand strokes on the cap atlas without using
    # its strengthened colors on the eye material that shares the source map.
    blurred = rgb.copy()
    for axis in (0, 1):
        blurred = (np.roll(blurred, -8, axis=axis) + 2 * blurred + np.roll(blurred, 8, axis=axis)) * .25
    return save_hair_map('hair-cap.jpg', rgb + .75 * (rgb - blurred))


# Convert each evaluated object, including bone-parented curve accessories.
positions=[];normals=[];uvs=[];skin_i=[];skin_w=[];faces=[];spec=[];mat_ids={};saved={};object_stats=[]
def rgb_hex(rgb):
 def channel(v):
  v=max(0,min(1,float(v)));v=12.92*v if v<=.0031308 else 1.055*v**(1/2.4)-.055
  return round(v*255)
 c=[channel(x) for x in rgb[:3]]
 return (c[0]<<16)|(c[1]<<8)|c[2]
def material_id(mat):
 name=mat.name if mat else 'default'
 if name in mat_ids:return mat_ids[name]
 nodes=mat.node_tree.nodes if mat and mat.use_nodes else []
 shader=next((n for n in nodes if n.type=='BSDF_PRINCIPLED'),None)
 imgs=[n.image for n in nodes if n.type=='TEX_IMAGE' and n.image and n.image.size[0]>=512]
 image=imgs[0] if imgs else None
 tex='null'
 if image:
  if image.name not in saved:
   dest=OUT/'textures'/image.name
   if image.packed_file:dest.write_bytes(bytes(image.packed_file.data))
   else: raise RuntimeError('Image not packed: '+image.name)
   saved[image.name]='textures/'+dest.name
  tex=saved[image.name]
 color=rgb_hex(shader.inputs['Base Color'].default_value) if shader and not image else 0xffffff
 rough=float(shader.inputs['Roughness'].default_value) if shader else .6
 metal=float(shader.inputs['Metallic'].default_value) if shader else 0
 item=dict(name=name,sourceName=name,texture=tex,color=color,twoSide=True,opacity=1,transparent=False,alphaTest=.25 if name=='睫眉' else 0,depthWrite=True,roughness=rough,metalness=metal,textureAnisotropy=8)
 if '肤' in name or name.startswith('颜'):item['skinSurface']=True
 if name in (HAIR_CAP, HAIR_LOCKS):
  item.update(hairSurface=True, roughness=.62, metalness=0, anisotropy=.35)
  if name == HAIR_CAP:
   item['texture'] = make_hair_cap_map(image)
  else:
   item.update(texture=make_hair_lock_map(nodes), color=0xffffff)
 mat_ids[name]=len(spec);spec.append(item);return mat_ids[name]
def append_skin_weights(weights, default):
    ranked = sorted(
        ((slot, weight) for slot, weight in weights.items() if weight > 1e-8),
        key=lambda item: -item[1],
    )[:4] or [(default, 1.)]
    total = sum(weight for _, weight in ranked)
    skin_i.extend([slot for slot, _ in ranked] + [0] * (4 - len(ranked)))
    skin_w.extend([round(weight / total, 7) for _, weight in ranked] + [0] * (4 - len(ranked)))


for ob in objects:
 if ob.name == SWIM_BOTTOM:
  continue  # Its pattern is applied to the body below.
 ev=ob.evaluated_get(deps); me=ev.to_mesh(preserve_all_data_layers=True,depsgraph=deps)
 if not me:continue
 original_body = smooth_shoulder_surface(me, ev.matrix_world) if ob.name == BODY else None
 me.calc_loop_triangles()
 group_names={g.index:g.name for g in ob.vertex_groups}
 default=slot_of(ob.parent_bone) if ob.parent_type=='BONE' else None
 if default is None:default=13
 uv=me.uv_layers.active;first={}
 for loop in me.loops:first.setdefault(loop.vertex_index,loop.index)
 hair_uv = strand_uvs(me) if '发尾渐变' in me.attributes else None
 base=len(positions)//3;normal_matrix=ev.matrix_world.to_3x3().inverted().transposed()
 for v in me.vertices:
  pos=uniform(ev.matrix_world @ v.co);n=(normal_matrix @ v.normal).normalized();li=first.get(v.index);t=uv.data[li].uv if uv and li is not None else (0,0)
  if hair_uv is not None:
   t = hair_uv[v.index]
  positions.extend(round(x,6) for x in pos);normals.extend(round(x,6) for x in n);uvs.extend((round(t[0],7),round(t[1],7)))
  acc=defaultdict(float)
  for g in v.groups:
   slot=slot_of(group_names.get(g.group))
   if slot is not None and g.weight>1e-8:acc[slot]+=g.weight
  if original_body is not None:
   blend_shoulder_weights(uniform(ev.matrix_world @ Vector(original_body[v.index])), acc)
  append_skin_weights(acc, default)
 mids=[material_id(m) for m in me.materials]
 face_start = len(faces)
 if original_body is not None:
  fabric = material_id(bpy.data.objects[SWIM_BOTTOM].data.materials[0])
  append_swim_body_faces(me, base, mids[0], fabric)
 else:
  for tri in me.loop_triangles:
   mi=mids[tri.material_index] if tri.material_index<len(mids) else material_id(None)
   faces.append({'material':mi,'indices':[base+i for i in tri.vertices]})
 object_stats.append({'name':ob.name,'sourceVertices':len(ob.data.vertices) if ob.type=='MESH' else None,'runtimeVertices':len(positions)//3-base,'triangles':len(faces)-face_start})
 ev.to_mesh_clear()
print('GEOMETRY',len(positions)//3,len(faces),'floor',floor,'top',top,flush=True)
skin=dict(schema=1,coordinateSystem='original-native-Z-up',bodyRig=body_rig,materials=spec,positions=positions,normals=normals,uvs=uvs,skinIndices=skin_i,skinWeights=skin_w,faces=faces,vertexCount=len(positions)//3,triangleCount=len(faces),secondaryMotion=None)
(OUT/'mesh.json').write_text(json.dumps(skin,separators=(',',':')))
manifest=dict(schema=1,characterId=0,appearance='liuchao',label='琉潮 · 原创角色',mesh='mesh.json',complete=True,completeness=dict(bodyGeometry=True,headHairGeometry=True,eyes=True,faceGeometry=True,sourcePmxSkeleton=False,originalSourceGameSkeleton=False),stats=dict(vertices=len(positions)//3,triangles=len(faces),sourceBones=len(bones),bones=30,dummies=6,secondaryBones=0,materials=len(spec),textures=len(saved)),retarget=dict(method='Source-length skeleton with native animation rotations; evaluated Blender objects, uniform scale and reduced body mesh.',provisional=True,hairPhysics=False,clothPhysics=False),provenance=dict(sourceArchive='assets/source/liuchao/琉潮.blend',limits=['Body mesh reduced for runtime; Blender procedural materials approximated.','Hair and clothing follow bones; no secondary physics or expression morphs.']),sourceFiles=[dict(file=SRC.name,bytes=SRC.stat().st_size,sha256=hashlib.sha256(SRC.read_bytes()).hexdigest())])
(OUT/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2))
(WORK/'build-evidence.json').write_text(json.dumps(dict(objects=object_stats,floor=floor,top=top,scale=scale,sourceHash=manifest['sourceFiles'][0]['sha256'],runtimeBytes=(OUT/'mesh.json').stat().st_size,textures=saved),ensure_ascii=False,indent=2))
print('LIUCHAO_READY',manifest['stats'],flush=True)
