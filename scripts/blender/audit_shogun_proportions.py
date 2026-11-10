"""Read-only Raiden Shogun source/runtime proportion audit; writes diagnostics only.

Blender --background --factory-startup --disable-autoexec --python scripts/blender/audit_shogun_proportions.py -- --render

The build applies one uniform transform, so every expected relative change is
0%. The point of this audit is to prove that instead of trusting it: the same
source vertex IDs are compared between the uniform reference and the runtime
mesh, and the display rig's segment lengths are compared with the source's.
"""
import bpy, sys, json, math, hashlib
from pathlib import Path
from mathutils import Vector
sys.path.insert(0, str(Path(__file__).parent))
from pmx_reader import PMXReader
from hutao_native_rest import B, world as REST

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'work/shogun-proportions-2026-11-10'; OUT.mkdir(parents=True, exist_ok=True)
SOURCE = ROOT / 'assets/source/shogun/雷电将军.pmx'
CURRENT = ROOT / 'dist/assets/enhanced/shogun/mesh.json'
TARGET_HEIGHT = 39.4

pmx = PMXReader(SOURCE).parse(); skin = json.loads(CURRENT.read_text())
byname = {b['name']: b for b in pmx.bones}


def point(name):
    x, y, z = byname[name]['position']; return Vector((x, z, y))


def native(index): return REST[B[index]['name']].translation


floor = min(v['position'][1] for v in pmx.vertices)
top = max(v['position'][1] for v in pmx.vertices)
scale = TARGET_HEIGHT / (top - floor)
source_points = [Vector((v['position'][0] * scale, v['position'][2] * scale, (v['position'][1] - floor) * scale)) for v in pmx.vertices]
current_points = [Vector(skin['positions'][i:i + 3]) for i in range(0, len(skin['positions']), 3)]


def bounds(points): return [[min(p[a] for p in points), max(p[a] for p in points)] for a in range(3)]


def metric(label, source, current):
    return dict(label=label, sourceReference=round(source, 6), runtime=round(current, 6),
                relativeChangePct=round((current / source - 1) * 100, 6) if source else None)


rig = skin['bodyRig']['bones']


def rig_point(slot): return Vector(rig[slot]['position'])


def metric(label, source, current):
    return dict(label=label, sourceReference=round(source, 6), runtime=round(current, 6),
                relativeChangePct=round((current / source - 1) * 100, 6) if source else None)


hip_source = (point('左足').z + point('右足').z) / 2
hip_runtime = (rig_point(3).z + rig_point(7).z) / 2
runtime_top = bounds(current_points)[2][1]
metrics = [
    metric('total_rest_height', (top - floor) * scale, runtime_top - bounds(current_points)[2][0]),
    metric('shoulder_joint_span', (point('左腕') - point('右腕')).length * scale, (rig_point(15) - rig_point(23)).length),
    metric('clavicle_to_shoulder', (point('左腕') - point('左肩')).length * scale, (rig_point(15) - rig_point(14)).length),
    metric('upper_arm_length', (point('左ひじ') - point('左腕')).length * scale, (rig_point(16) - rig_point(15)).length),
    metric('forearm_length', (point('左手首') - point('左ひじ')).length * scale, (rig_point(17) - rig_point(16)).length),
    metric('thigh_length', (point('左ひざ') - point('左足')).length * scale, (rig_point(4) - rig_point(3)).length),
    metric('calf_length', (point('左足首') - point('左ひざ')).length * scale, (rig_point(5) - rig_point(4)).length),
    metric('foot_length', (point('左つま先') - point('左足首')).length * scale, (rig_point(6) - rig_point(5)).length),
    metric('hip_to_neck_height', (point('首').z - hip_source) * scale, rig_point(12).z - hip_runtime),
    metric('hip_to_lower_spine_height', (point('上半身').z - hip_source) * scale, rig_point(2).z - hip_runtime),
    metric('lower_to_upper_spine_height', (point('上半身2').z - point('上半身').z) * scale, rig_point(11).z - rig_point(2).z),
    metric('upper_spine_to_neck_height', (point('首').z - point('上半身2').z) * scale, rig_point(12).z - rig_point(11).z),
    metric('neck_to_head_height', (point('頭').z - point('首').z) * scale, rig_point(13).z - rig_point(12).z),
    metric('head_to_crown_height', (top - point('頭').z) * scale, runtime_top - rig_point(13).z),
]

# The decisive check: identical source vertices must land on the same point.
vertex_error = max((current_points[i] - source_points[i]).length for i in range(len(source_points)))
assert skin['vertexCount'] == len(pmx.vertices)

# Per-height band cross sections use fixed source vertex IDs, so a uniform
# transform must reproduce the source width and depth exactly.
bands = []
for fraction in [.42, .52, .62, .72, .82]:
    selected = [i for i, v in enumerate(pmx.vertices)
                if abs((v['position'][1] - floor) / (top - floor) - fraction) < .012 and abs(v['position'][0]) < 1.2]
    if len(selected) < 8: continue
    a = bounds([source_points[i] for i in selected]); b = bounds([current_points[i] for i in selected])
    bands.append(dict(sourceHeightFraction=fraction, vertices=len(selected),
                      width=metric('band_width', a[0][1] - a[0][0], b[0][1] - b[0][0]),
                      depth=metric('band_depth', a[1][1] - a[1][0], b[1][1] - b[1][0])))

SOURCE_NAMES = ['センター', '下半身', '上半身', '左足D', '左ひざD', '左足首D', '左つま先', '右足D', '右ひざD', '右足首D', '右つま先',
                '上半身2', '首', '頭', '左肩', '左腕', '左ひじ', '左手首', '左親指０', '左親指１', '左中指１', '左中指３',
                '右肩', '右腕', '右ひじ', '右手首', '右親指０', '右親指１', '右中指１', '右中指３']


def uniform_point(name):
    x, y, z = byname[name]['position']
    return Vector((x * scale, z * scale, (y - floor) * scale))


rig_error = max((Vector(rig[i]['position']) - uniform_point(name)).length for i, name in enumerate(SOURCE_NAMES))

evidence = dict(
    date='2026-11-10', runtimeModified=False, method='single-uniform-transform',
    source='assets/source/shogun/雷电将军.pmx', current='dist/assets/enhanced/shogun/mesh.json',
    sourceSha256=hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
    currentSha256=hashlib.sha256(CURRENT.read_bytes()).hexdigest(),
    realWorldCentimeterCalibration=None, heightTarget=TARGET_HEIGHT, runtimeScale=.08, sourceUniformScale=scale,
    sourceVertices=len(pmx.vertices), runtimeVertices=skin['vertexCount'],
    sourceTriangles=len(pmx.indices) // 3, runtimeTriangles=skin['triangleCount'],
    sourceProportionDisplayRig=bool(skin.get('bodyRig')),
    maxVertexDeviationFromUniformSource=vertex_error,
    maxDisplayRigPositionError=rig_error,
    sourceBounds=bounds(source_points), runtimeBounds=bounds(current_points),
    metrics=metrics, measuredMeshBands=bands,
    segmentsThatChangeLength=[m['label'] for m in metrics if m['relativeChangePct'] is not None and abs(m['relativeChangePct']) > .01],
    notes=['Every source vertex passes through one uniform scale and a floor offset; no segment-wise height, head or width scaling exists in build_shogun.py.',
           'Metrics compare the uniform source reference against the runtime mesh and the 30-bone display rig.',
           'Mesh bands use exactly the same source vertex IDs in both models.',
           'Source PMX has no verified real-world centimetre calibration; no physical height is claimed.'])
(OUT / 'proportions.json').write_text(json.dumps(evidence, ensure_ascii=False, indent=2) + '\n')
print('SHOGUN_PROPORTION_AUDIT', json.dumps(dict(maxVertexDeviation=vertex_error, maxRigError=rig_error,
                                               changed=[m['label'] for m in metrics if m['relativeChangePct'] and abs(m['relativeChangePct']) > .01],
                                               metrics=metrics), ensure_ascii=False), flush=True)
if '--render' not in sys.argv: sys.exit(0)

# ---- clay comparison render: identical material, lights and camera ----
bpy.ops.object.select_all(action='SELECT'); bpy.ops.object.delete(use_global=False)
material = bpy.data.materials.new('Same clay for both meshes'); material.use_nodes = True
bs = material.node_tree.nodes.get('Principled BSDF')
bs.inputs['Base Color'].default_value = (.72, .74, .78, 1); bs.inputs['Roughness'].default_value = .62
faces = [(a, c, b) for a, b, c in zip(pmx.indices[::3], pmx.indices[1::3], pmx.indices[2::3])]
objects = []
for label, points, center in [('SOURCE / UNIFORM', source_points, -18), ('CURRENT WEB', current_points, 18)]:
    bottom = min(p.z for p in points)
    verts = [(p.x + center, p.y, p.z - bottom) for p in points]
    mesh = bpy.data.meshes.new(label); mesh.from_pydata(verts, [], faces); mesh.update()
    for polygon in mesh.polygons: polygon.use_smooth = True
    obj = bpy.data.objects.new(label, mesh); bpy.context.collection.objects.link(obj)
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


render('source-vs-current.png', (0, -60, 21), (0, 0, 20), 52)
# Side view: rotate the pair so depth (a classic distortion axis) is visible.
for obj in objects: obj.rotation_euler[2] = math.radians(90)
render('source-vs-current-side.png', (0, -60, 21), (0, 0, 20), 52)
print('SHOGUN_AUDIT_RENDER_DONE', flush=True)