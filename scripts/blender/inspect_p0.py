import bpy, os, re, math, json
from mathutils import Vector, Matrix, Quaternion
ROOT=os.path.abspath(os.path.join(os.path.dirname(__file__),'../..'))
SRC=os.path.join(ROOT,'dist/assets/original/characters/p0')
WORK=os.path.join(ROOT,'work/character-hd')
bpy.ops.object.select_all(action='SELECT'); bpy.ops.object.delete(use_global=False)
text=open(os.path.join(SRC,'p0.skc')).read()
verts=[];uvs=[];faces=[];mis=[]
for line in text.splitlines():
    t=line.split()
    if t and t[0]=='v': verts.append(tuple(map(float,t[1:4])));u=t.index('vt');uvs.append(tuple(map(float,t[u+1:u+3])))
    if t and t[0]=='f': faces.append(tuple(map(int,t[3:6])));mis.append(int(t[2]))
mesh=bpy.data.meshes.new('SKC');mesh.from_pydata(verts,[],faces);mesh.update()
ob=bpy.data.objects.new('Original P0',mesh);bpy.context.collection.objects.link(ob)
uv=mesh.uv_layers.new(name='Original UV')
for p in mesh.polygons:
    for i in p.loop_indices: uv.data[i].uv=(uvs[mesh.loops[i].vertex_index][0],uvs[mesh.loops[i].vertex_index][1])
    p.material_index=mis[p.index];p.use_smooth=True
for i in range(5):
    m=bpy.data.materials.new('Original '+str(i));m.use_nodes=True;n=m.node_tree.nodes;p=n.get('Principled BSDF');p.inputs['Roughness'].default_value=.85
    im=bpy.data.images.load(os.path.join(SRC,'textures/nm001f01.jpg' if i in [2,3] else 'textures/nm001b01.png'),check_existing=True)
    tex=n.new('ShaderNodeTexImage');tex.image=im;m.node_tree.links.new(tex.outputs['Color'],p.inputs['Base Color'])
    if i in [0,1,4]:m.node_tree.links.new(tex.outputs['Alpha'],p.inputs['Alpha']);m.surface_render_method='DITHERED'
    mesh.materials.append(m)
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=24
scene.world.color=(.2,.2,.2)
def track(o,target):o.rotation_euler=(Vector(target)-o.location).to_track_quat('-Z','Y').to_euler()
for name,loc,power,size in [('Key',(25,-50,70),18000,40),('Fill',(-40,-10,40),9000,35),('Rim',(10,40,60),18000,30)]:
    bpy.ops.object.light_add(type='AREA',location=loc);l=bpy.context.object;l.name=name;l.data.energy=power;l.data.shape='DISK';l.data.size=size;track(l,(0,0,20))
bpy.ops.object.camera_add(location=(48,-95,47));cam=bpy.context.object;track(cam,(0,0,20));cam.data.type='ORTHO';cam.data.ortho_scale=48;scene.camera=cam
scene.render.resolution_x=900;scene.render.resolution_y=900;scene.render.resolution_percentage=100
scene.view_settings.view_transform='AgX';scene.render.image_settings.file_format='PNG';scene.render.filepath=os.path.join(WORK,'original-inspect.png')
bpy.ops.wm.save_as_mainfile(filepath=os.path.join(WORK,'p0-inspect.blend'));bpy.ops.render.render(write_still=True)
print('BOUNDS',[(min(v[i] for v in verts),max(v[i] for v in verts)) for i in range(3)],flush=True)
