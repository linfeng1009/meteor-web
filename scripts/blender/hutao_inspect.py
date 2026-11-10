import bpy,struct,os,math,json,hashlib
from mathutils import Vector
ROOT=os.path.abspath(os.path.join(os.path.dirname(__file__),'../..'))
SRC='/Users/dulinfeng/Downloads/hutao_black_stockings_mod_4k/HuTaoMod4K'
OUT=os.path.join(ROOT,'dist/assets/enhanced/hutao');WORK=os.path.join(ROOT,'work/hutao-mod')
os.makedirs(os.path.join(OUT,'textures'),exist_ok=True);os.makedirs(WORK,exist_ok=True)
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
def buf(name):return open(os.path.join(SRC,name),'rb').read()
a=buf('HuTaoPosition.buf');uvdata=buf('HuTaoTexcoord.buf');N=len(a)//40
P=[struct.unpack_from('<3f',a,i*40)for i in range(N)];UV=[struct.unpack_from('<2f',uvdata,i*12+4)for i in range(N)]
materials=[]
for name in ['HuTaoHeadDiffuse','HuTaoBodyDiffuse','HuTaoFaceHeadDiffuse','HuTaoHeadLightMap','HuTaoBodyLightMap']:
 im=bpy.data.images.load(os.path.join(SRC,name+'.dds'),check_existing=True); _=tuple(im.size); im.alpha_mode='NONE'; im.file_format='PNG';im.filepath_raw=os.path.join(OUT,'textures',name+'.png');im.save();print(name,tuple(im.size),flush=True)
 if name in ['HuTaoHeadDiffuse','HuTaoBodyDiffuse']:
  m=bpy.data.materials.new(name);m.use_nodes=True;bs=m.node_tree.nodes.get('Principled BSDF');bs.inputs['Roughness'].default_value=.8;tex=m.node_tree.nodes.new('ShaderNodeTexImage');tex.image=im;m.node_tree.links.new(tex.outputs['Color'],bs.inputs['Base Color']);materials.append(m)
F=[];MI=[]
for mi,name in enumerate(['HuTaoHead.ib','HuTaoBody.ib']):
 b=buf(name);inds=struct.unpack('<'+'I'*(len(b)//4),b)
 for i in range(0,len(inds),3):F.append(inds[i:i+3]);MI.append(mi)
mesh=bpy.data.meshes.new('Reconstructed source buffers');mesh.from_pydata([(x,-z,y)for x,y,z in P],[],F);mesh.update();ob=bpy.data.objects.new('HuTao original MOD buffers',mesh);bpy.context.collection.objects.link(ob)
for m in materials:mesh.materials.append(m)
ul=mesh.uv_layers.new(name='Source DX UV flipped V')
for poly in mesh.polygons:
 poly.material_index=MI[poly.index];poly.use_smooth=True
 for li in poly.loop_indices:
  u,v=UV[mesh.loops[li].vertex_index];ul.data[li].uv=(u,1-v)
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=12;scene.cycles.use_denoising=True;scene.world.color=(.35,.35,.35);scene.view_settings.view_transform='Standard';scene.render.resolution_x=1000;scene.render.resolution_y=1200;scene.render.resolution_percentage=100
for loc,power,size in [((2,-3,4),500,3),((-2,-2,2),250,2),((0,2,3),400,2)]:
 bpy.ops.object.light_add(type='AREA',location=loc);l=bpy.context.object;l.data.energy=power;l.data.size=size;l.rotation_euler=(Vector((0,0,.8))-l.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add(location=(.4,-4,1.4));c=bpy.context.object;c.data.type='ORTHO';c.data.ortho_scale=1.9;c.rotation_euler=(Vector((0,0,.8))-c.location).to_track_quat('-Z','Y').to_euler();scene.camera=c
scene.render.filepath=os.path.join(WORK,'source-front.png');bpy.ops.render.render(write_still=True)
c.location=(0,-3,1.39);c.data.ortho_scale=.55;c.rotation_euler=(Vector((0,-.03,1.39))-c.location).to_track_quat('-Z','Y').to_euler();scene.render.resolution_x=1000;scene.render.resolution_y=1000;scene.render.filepath=os.path.join(WORK,'source-face.png');bpy.ops.render.render(write_still=True)
bpy.ops.wm.save_as_mainfile(filepath=os.path.join(WORK,'胡桃-原缓冲还原.blend'))
