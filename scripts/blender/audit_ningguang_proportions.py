"""Read-only Ningguang .blend vs runtime proportion audit; writes diagnostics only.

Blender --background --factory-startup --disable-autoexec --python scripts/blender/audit_ningguang_proportions.py -- --render
"""
import bpy, sys, json, math, hashlib
from pathlib import Path
from mathutils import Vector

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'work/ningguang-proportions-2026-11-11'; OUT.mkdir(parents=True, exist_ok=True)
SRC = ROOT / 'assets/source/ningguang/凝光_纱中幽兰_可编辑.blend'
CURRENT = ROOT / 'dist/assets/enhanced/ningguang/mesh.json'
TARGET_HEIGHT = 39.4

bpy.ops.wm.open_mainfile(filepath=str(SRC))
ob = bpy.data.objects['凝光_mesh']
arm = bpy.data.objects['凝光_arm']
mesh = ob.data
skin = json.loads(CURRENT.read_text())
group_bone = {g.index: g.name for g in ob.vertex_groups}
bone_head = {b.name: b.head_local.copy() for b in arm.data.bones}

zs = [v.co.z for v in mesh.vertices]
top = max(zs)
sole = [v.co.z for v in mesh.vertices
        if any(group_bone[g.group] in ('足.L', '足.R', '足首.L', '足首.R', '足先EX.L', '足先EX.R', 'つま先.L', 'つま先.R')
               and g.weight >= .5 for g in v.groups)]
mesh_floor = min(zs)
floor = min(sole) if sole else mesh_floor
scale = TARGET_HEIGHT / (top - floor)


def uniform(p): return Vector((p.x * scale, p.y * scale, (p.z - floor) * scale))


def point(name): return bone_head[name]


# Decal layers (颜2/白目/睫) carry a deliberate sub-millimetre outward bias in the
# build, so the uniform-transform invariant is checked on everything else.
DECAL = {'颜2', '白目', '睫'}
material_names = [m.name if m else '' for m in mesh.materials]
decal_vertices = set()
for poly in mesh.polygons:
    if material_names[poly.material_index] in DECAL: decal_vertices.update(poly.vertices)
source_points = [uniform(v.co) for v in mesh.vertices]
current_points = [Vector(skin['positions'][i:i + 3]) for i in range(0, len(skin['positions']), 3)]
assert len(source_points) == len(current_points)
vertex_error = max((current_points[i] - source_points[i]).length
                   for i in range(len(source_points)) if i not in decal_vertices)
decal_error = max(((current_points[i] - source_points[i]).length for i in decal_vertices), default=0.0)


def bounds(points): return [[min(p[a] for p in points), max(p[a] for p in points)] for a in range(3)]


rig = skin['bodyRig']['bones']


def rig_point(slot): return Vector(rig[slot]['position'])


def metric(label, source, current):
    return dict(label=label, sourceReference=round(source, 6), runtime=round(current, 6),
                relativeChangePct=round((current / source - 1) * 100, 6) if source else None)


ANCHORS = ['センター', '下半身', '上半身', '足.L', 'ひざ.L', '足首.L', '足先EX.L',
           '足.R', 'ひざ.R', '足首.R', '足先EX.R', '上半身2', '首', '頭',
           '肩.L', '腕.L', 'ひじ.L', '手首.L', '親指０.L', '親指１.L', '中指１.L', '中指３.L',
           '肩.R', '腕.R', 'ひじ.R', '手首.R', '親指０.R', '親指１.R', '中指１.R', '中指３.R']
rig_error = max((rig_point(i) - uniform(point(name))).length for i, name in enumerate(ANCHORS))

hip_src = (point('足.L').z + point('足.R').z) / 2
hip_rt = (rig_point(3).z + rig_point(7).z) / 2
runtime_top = bounds(current_points)[2][1]
metrics = [
    metric('total_rest_height', (top - floor) * scale, runtime_top),
    metric('shoulder_joint_span', (point('腕.L') - point('腕.R')).length * scale, (rig_point(15) - rig_point(23)).length),
    metric('clavicle_to_shoulder', (point('腕.L') - point('肩.L')).length * scale, (rig_point(15) - rig_point(14)).length),
    metric('upper_arm_length', (point('ひじ.L') - point('腕.L')).length * scale, (rig_point(16) - rig_point(15)).length),
    metric('forearm_length', (point('手首.L') - point('ひじ.L')).length * scale, (rig_point(17) - rig_point(16)).length),
    metric('thigh_length', (point('ひざ.L') - point('足.L')).length * scale, (rig_point(4) - rig_point(3)).length),
    metric('calf_length', (point('足首.L') - point('ひざ.L')).length * scale, (rig_point(5) - rig_point(4)).length),
    metric('foot_length', (point('足先EX.L') - point('足首.L')).length * scale, (rig_point(6) - rig_point(5)).length),
    metric('hip_to_neck_height', (point('首').z - hip_src) * scale, rig_point(12).z - hip_rt),
    metric('hip_to_lower_spine_height', (point('上半身').z - hip_src) * scale, rig_point(2).z - hip_rt),
    metric('lower_to_upper_spine_height', (point('上半身2').z - point('上半身').z) * scale, rig_point(11).z - rig_point(2).z),
    metric('upper_spine_to_neck_height', (point('首').z - point('上半身2').z) * scale, rig_point(12).z - rig_point(11).z),
    metric('neck_to_head_height', (point('頭').z - point('首').z) * scale, rig_point(13).z - rig_point(12).z),
    metric('head_to_crown_height', (top - point('頭').z) * scale, runtime_top - rig_point(13).z),
]

bands = []
for fraction in [.42, .52, .62, .72, .82]:
    selected = [i for i, v in enumerate(mesh.vertices) if abs((v.co.z - floor) / (top - floor) - fraction) < .012 and abs(v.co.x) < .06]
    if len(selected) < 8: continue
    a = bounds([source_points[i] for i in selected]); b = bounds([current_points[i] for i in selected])
    bands.append(dict(sourceHeightFraction=fraction, vertices=len(selected),
                      width=metric('band_width', a[0][1] - a[0][0], b[0][1] - b[0][0]),
                      depth=metric('band_depth', a[1][1] - a[1][0], b[1][1] - b[1][0])))

evidence = dict(
    date='2026-11-11', runtimeModified=False, method='single-uniform-transform',
    source='assets/source/ningguang/凝光_纱中幽兰_可编辑.blend', current='dist/assets/enhanced/ningguang/mesh.json',
    sourceSha256=hashlib.sha256(SRC.read_bytes()).hexdigest(),
    currentSha256=hashlib.sha256(CURRENT.read_bytes()).hexdigest(),
    realWorldCentimeterCalibration=None, heightTarget=TARGET_HEIGHT, runtimeScale=.08, sourceUniformScale=scale,
    sourceVertices=len(mesh.vertices), runtimeVertices=skin['vertexCount'],
    sourceTriangles=len(mesh.polygons), runtimeTriangles=skin['triangleCount'],
    sourceProportionDisplayRig=bool(skin.get('bodyRig')),
    meshFloor=mesh_floor, soleFloor=floor, geometryBelowSole=floor - mesh_floor,
    maxVertexDeviationFromUniformSource=vertex_error, decalVertices=len(decal_vertices),
    decalBiasMax=decal_error, maxDisplayRigPositionError=rig_error,
    sourceBounds=bounds(source_points), runtimeBounds=bounds(current_points), metrics=metrics, measuredMeshBands=bands,
    segmentsThatChangeLength=[m['label'] for m in metrics if m['relativeChangePct'] is not None and abs(m['relativeChangePct']) > .01],
    notes=['The .blend is read directly; every source vertex passes through one uniform scale and a floor offset taken from the foot vertices.',
           'Metrics compare that uniform reference against the runtime mesh and the 30-bone display rig.',
           'Mesh bands use exactly the same source vertex IDs in both models.',
           'The source has no verified real-world centimetre calibration; no physical height is claimed.'])
(OUT / 'proportions.json').write_text(json.dumps(evidence, ensure_ascii=False, indent=2) + '\n')
print('NINGGUANG_PROPORTION_AUDIT', json.dumps(dict(maxVertexDeviation=vertex_error, maxRigError=rig_error,
                                                   changed=evidence['segmentsThatChangeLength'], metrics=metrics), ensure_ascii=False), flush=True)
if '--render' not in sys.argv: sys.exit(0)

# clay comparison: identical material, lights and camera, soles aligned
bpy.ops.object.select_all(action='SELECT'); bpy.ops.object.delete(use_global=False)
material = bpy.data.materials.new('Same clay for both meshes'); material.use_nodes = True
bs = material.node_tree.nodes.get('Principled BSDF')
bs.inputs['Base Color'].default_value = (.72, .74, .78, 1); bs.inputs['Roughness'].default_value = .62
faces = [tuple(p.vertices) for p in mesh.polygons]
objects = []
for label, pts, center in [('SOURCE / UNIFORM', source_points, -14), ('CURRENT WEB', current_points, 14)]:
    verts = [(p.x + center, p.y, p.z) for p in pts]
    m = bpy.data.meshes.new(label); m.from_pydata(verts, [], [f for f in faces if len(f) == 3]); m.update()
    for polygon in m.polygons: polygon.use_smooth = True
    obj = bpy.data.objects.new(label, m); bpy.context.collection.objects.link(obj)
    obj.data.materials.append(material); objects.append(obj)

scene = bpy.context.scene
scene.render.engine = 'CYCLES'; scene.cycles.samples = 28; scene.cycles.use_denoising = True
scene.render.resolution_x = 1100; scene.render.resolution_y = 1200; scene.render.resolution_percentage = 100
scene.view_settings.view_transform = 'AgX'
scene.world = bpy.data.worlds.new('Neutral'); scene.world.use_nodes = True
scene.world.node_tree.nodes['Background'].inputs[0].default_value = (.04, .05, .07, 1)
for loc, power, size in [((0, -30, 26), 2600, 22), ((-26, -12, 14), 1400, 18), ((26, -8, 12), 1200, 18), ((0, 24, 20), 1600, 20)]:
    bpy.ops.object.light_add(type='AREA', location=loc); light = bpy.context.object
    light.data.energy = power; light.data.size = size
    light.rotation_euler = (Vector((0, 0, 20)) - light.location).to_track_quat('-Z', 'Y').to_euler()


def render(name, camera_location, target, ortho):
    bpy.ops.object.camera_add(location=camera_location); camera = bpy.context.object
    camera.rotation_euler = (Vector(target) - camera.location).to_track_quat('-Z', 'Y').to_euler()
    camera.data.type = 'ORTHO'; camera.data.ortho_scale = ortho
    scene.camera = camera
    scene.render.filepath = str(OUT / name)
    bpy.ops.render.render(write_still=True)


render('source-vs-current.png', (0, -60, 21), (0, 0, 20), 46)
for obj in objects: obj.rotation_euler[2] = math.radians(90)
render('source-vs-current-side.png', (0, -60, 21), (0, 0, 20), 46)
print('NINGGUANG_AUDIT_RENDER_DONE', flush=True)