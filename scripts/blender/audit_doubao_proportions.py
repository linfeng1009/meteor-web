"""Read-only source/current proportion audit; writes diagnostic artifacts only."""
import bpy,sys,json,math,hashlib
from pathlib import Path
from mathutils import Vector
sys.path.insert(0,str(Path(__file__).parent))
from pmx_reader import PMXReader
from hutao_native_rest import B,world as REST

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'work/doubao-proportions-2026-11-10';OUT.mkdir(parents=True,exist_ok=True)
SOURCE=ROOT/'assets/source/doubao/豆包模型.pmx'
CURRENT=ROOT/'dist/assets/enhanced/doubao/mesh.json'
pmx=PMXReader(SOURCE).parse();skin=json.loads(CURRENT.read_text())
byname={b['name']:b for b in pmx.bones}
def point(name):
    x,y,z=byname[name]['position'];return Vector((x,z,y))
def native(index):
    return Vector(skin['bodyRig']['bones'][index]['position']) if skin.get('bodyRig') else REST[B[index]['name']].translation
floor=min(v['position'][1] for v in pmx.vertices)
top=max(v['position'][1] for v in pmx.vertices)
uniform=39.4/(top-floor)
head=skin['bodyRig']['sourceUniformScale'] if skin.get('bodyRig') else (39.4-native(13).z)/(top-point('頭').z)
width=(abs(native(15).x)+abs(native(23).x))/(abs(point('左腕').x)+abs(point('右腕').x))
def metric(label,source,current):return dict(label=label,sourceAtSameHeight=source,currentTarget=current,relativeChangePct=(current/source-1)*100)
metrics=[
    metric('shoulder_joint_span',(point('左腕')-point('右腕')).length*uniform,(native(15)-native(23)).length),
    metric('head_linear_scale',uniform,head),
    metric('hip_to_neck_height',(point('首').z-(point('左足').z+point('右足').z)/2)*uniform,native(12).z-native(1).z),
    metric('hip_to_lower_spine_height',(point('上半身').z-(point('左足').z+point('右足').z)/2)*uniform,native(2).z-native(1).z),
    metric('lower_to_upper_spine_height',(point('上半身2').z-point('上半身').z)*uniform,native(11).z-native(2).z),
    metric('upper_arm_length',(point('左ひじ')-point('左腕')).length*uniform,(native(16)-native(15)).length),
    metric('forearm_length',(point('左手首')-point('左ひじ')).length*uniform,(native(17)-native(16)).length),
    metric('thigh_length',(point('左ひざ')-point('左足')).length*uniform,(native(4)-native(3)).length),
    metric('calf_length',(point('左足首')-point('左ひざ')).length*uniform,(native(5)-native(4)).length)
]
source_points=[Vector((v['position'][0]*uniform,v['position'][2]*uniform,(v['position'][1]-floor)*uniform)) for v in pmx.vertices]
current_points=[Vector(skin['positions'][i:i+3]) for i in range(0,len(skin['positions']),3)]
def bounds(points):return [[min(p[a] for p in points),max(p[a] for p in points)] for a in range(3)]
sb,cb=bounds(source_points),bounds(current_points)
# A centerline strip excludes the different arm rest orientations. Changes in
# vertical distances and local cross-section widths are actual mesh changes.
bands=[]
for fraction in [.45,.55,.65,.72]:
    selected=[i for i,v in enumerate(pmx.vertices) if abs((v['position'][1]-floor)/(top-floor)-fraction)<.012 and abs(v['position'][0])<1.2]
    if not selected:continue
    a=[source_points[i] for i in selected];b=[current_points[i] for i in selected];ab,bb=bounds(a),bounds(b)
    bands.append(dict(sourceHeightFraction=fraction,vertices=len(selected),width=metric('same_source_vertex_band_width',ab[0][1]-ab[0][0],bb[0][1]-bb[0][0]),depth=metric('same_source_vertex_band_depth',ab[1][1]-ab[1][0],bb[1][1]-bb[1][0])))
evidence=dict(date='2026-11-10',runtimeModified=False,source='assets/source/doubao/豆包模型.pmx',current='dist/assets/enhanced/doubao/mesh.json',sourceSha256=hashlib.sha256(SOURCE.read_bytes()).hexdigest(),currentSha256=hashlib.sha256(CURRENT.read_bytes()).hexdigest(),nativeBncSha256=hashlib.sha256((ROOT/'dist/assets/original/characters/p0/p0.bnc').read_bytes()).hexdigest(),realWorldCentimeterCalibration=None,heightTarget=39.4,runtimeScale=.08,sourceUniformScale=uniform,headLinearScale=head,torsoWidthScale=width,adaptationType='source-proportions' if skin.get('bodyRig') else 'legacy-segmented',sourceBounds=sb,currentRestBounds=cb,currentRestHeight=cb[2][1]-cb[2][0],metrics=metrics,measuredMeshBands=bands,sourceVertices=len(pmx.vertices),runtimeVertices=skin['vertexCount'],sourceTriangles=len(pmx.indices)//3,runtimeTriangles=skin['triangleCount'],sourceProportionDisplayRig=bool(skin.get('bodyRig')),textureUnchanged=hashlib.sha256((ROOT/'assets/source/doubao/tex/Color.jpg').read_bytes()).digest()==hashlib.sha256((ROOT/'dist/assets/enhanced/doubao/textures/color.jpg').read_bytes()).digest(),notes=['Metrics compare the active display joint dimensions against uniform source geometry at the same 39.4-unit target height.','Mesh-band dimensions use exactly the same source vertex IDs in both models.','Rest arm orientations differ; image is a geometry diagnosis, not a same-motion comparison.','PMX units have no verified real-world centimeter calibration.'])
(OUT/'proportions.json').write_text(json.dumps(evidence,ensure_ascii=False,indent=2)+'\n')
print('PROPORTION_AUDIT',json.dumps(dict(currentHeight=evidence['currentRestHeight'],metrics=metrics,meshBands=bands),ensure_ascii=False),flush=True)
if '--render' not in sys.argv:sys.exit(0)

bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
image=bpy.data.images.load(str(ROOT/'dist/assets/enhanced/doubao/textures/color.jpg'),check_existing=True)
material=bpy.data.materials.new('Same original 4K atlas and lighting');material.use_nodes=True
bs=material.node_tree.nodes.get('Principled BSDF');bs.inputs['Roughness'].default_value=.84;bs.inputs['Specular IOR Level'].default_value=.18
node=material.node_tree.nodes.new('ShaderNodeTexImage');node.image=image;material.node_tree.links.new(node.outputs['Color'],bs.inputs['Base Color'])
faces=[(a,c,b) for a,b,c in zip(pmx.indices[::3],pmx.indices[1::3],pmx.indices[2::3])]
extents=[]
source_normals=[(v['normal'][0],v['normal'][2],v['normal'][1]) for v in pmx.vertices]
current_normals=[skin['normals'][i:i+3] for i in range(0,len(skin['normals']),3)]
models=[('SOURCE / UNIFORM',source_points,source_normals,-20),('CURRENT WEB',current_points,current_normals,20)]
before_path=OUT/'before/mesh.json'
if skin.get('bodyRig') and before_path.is_file():
    before=json.loads(before_path.read_text());before_points=[Vector(before['positions'][i:i+3]) for i in range(0,len(before['positions']),3)];before_normals=[before['normals'][i:i+3] for i in range(0,len(before['normals']),3)]
    models=[('SOURCE / UNIFORM',source_points,source_normals,-40),('PREVIOUS WEB',before_points,before_normals,0),('FIXED WEB',current_points,current_normals,40)]
for name,points,normals,center in models:
    bottom=min(p.z for p in points);positions=[(p.x+center,p.y,p.z-bottom) for p in points]
    mesh=bpy.data.meshes.new(name);mesh.from_pydata(positions,[],faces);mesh.update();mesh.materials.append(material)
    obj=bpy.data.objects.new(name,mesh);bpy.context.collection.objects.link(obj)
    uv=mesh.uv_layers.new(name='Original atlas')
    for poly in mesh.polygons:
        poly.use_smooth=True
        for li in poly.loop_indices:
            v=pmx.vertices[mesh.loops[li].vertex_index];uv.data[li].uv=(v['uv'][0],1-v['uv'][1])
    mesh.normals_split_custom_set_from_vertices(normals)
    extents.extend(p[0] for p in positions)
    bpy.ops.object.text_add(location=(center,-2,42),rotation=(math.pi/2,0,0))
    text=bpy.context.object;text.data.body=name;text.data.align_x='CENTER';text.data.size=1.15
    ink=bpy.data.materials.get('Label') or bpy.data.materials.new('Label');ink.diffuse_color=(.8,.85,.87,1);text.data.materials.append(ink)
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=16;scene.cycles.use_denoising=True
scene.render.threads_mode='FIXED';scene.render.threads=8
scene.render.resolution_x=900*len(models);scene.render.resolution_y=1125;scene.render.resolution_percentage=100;aspect=scene.render.resolution_x/scene.render.resolution_y
world=bpy.data.worlds.new('Equal flat environment');world.use_nodes=True;world.node_tree.nodes['Background'].inputs['Color'].default_value=(.12,.16,.18,1);world.node_tree.nodes['Background'].inputs['Strength'].default_value=.7;scene.world=world
for position,energy,angle in [((25,-60,70),2.5,.15),((-45,-20,45),1.0,.25),((0,40,60),1.2,.2)]:
    bpy.ops.object.light_add(type='SUN',location=position);light=bpy.context.object;light.data.energy=energy;light.data.angle=angle;light.rotation_euler=(Vector((0,0,20))-light.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add(location=(0,-140,20));camera=bpy.context.object;camera.data.type='ORTHO';camera.data.ortho_scale=max(49*aspect,max(extents)-min(extents)+5);camera.rotation_euler=(Vector((0,0,20))-camera.location).to_track_quat('-Z','Y').to_euler();scene.camera=camera
scene.view_settings.view_transform='Standard';scene.render.filepath=str(OUT/'source-vs-current.png');bpy.ops.render.render(write_still=True)
print('COMPARISON_READY',flush=True)
