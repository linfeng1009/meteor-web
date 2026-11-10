"""Render the converted runtime sword and save an editable, texture-packed blend."""
import bpy,json
from pathlib import Path
from mathutils import Vector
ROOT=Path(__file__).resolve().parents[2];ASSET=ROOT/'dist/assets/enhanced/weapons/raiden-sword';WORK=ROOT/'work/raiden-sword';WORK.mkdir(parents=True,exist_ok=True)
data=json.loads((ASSET/'mesh.json').read_text());p=data['positions'];vertices=[p[i:i+3]for i in range(0,len(p),3)]
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
mesh=bpy.data.meshes.new('Raiden sword runtime mesh');mesh.from_pydata(vertices,[],[face['indices']for face in data['faces']]);mesh.update();ob=bpy.data.objects.new('雷电影佩刀 · 原版长剑挂点适配',mesh);bpy.context.collection.objects.link(ob)
uv=mesh.uv_layers.new(name='PMX authored UV')
for poly,face in zip(mesh.polygons,data['faces']):
 poly.material_index=face['material'];poly.use_smooth=True
 for li in poly.loop_indices:
  vi=mesh.loops[li].vertex_index;uv.data[li].uv=data['uvs'][vi*2:vi*2+2]
mesh.normals_split_custom_set_from_vertices([data['normals'][i:i+3]for i in range(0,len(data['normals']),3)])
for source in data['materials']:
 mat=bpy.data.materials.new(source['name']);mat.use_nodes=True;nodes=mat.node_tree.nodes;bs=nodes.get('Principled BSDF')
 tex=nodes.new('ShaderNodeTexImage');tex.image=bpy.data.images.load(str(ASSET/source['texture']),check_existing=True);mat.node_tree.links.new(tex.outputs['Color'],bs.inputs['Base Color']);bs.inputs['Metallic'].default_value=source['metalness'];bs.inputs['Roughness'].default_value=source['roughness'];bs.inputs['Coat Weight'].default_value=.45;bs.inputs['Coat Roughness'].default_value=.25
 if source.get('emissive'):
  em=nodes.new('ShaderNodeTexImage');em.image=bpy.data.images.load(str(ASSET/source['emissive']),check_existing=True);mat.node_tree.links.new(em.outputs['Color'],bs.inputs['Emission Color']);bs.inputs['Emission Strength'].default_value=source['emissiveIntensity']
 mesh.materials.append(mat)
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=32;scene.cycles.use_denoising=True;scene.world.color=(.14,.18,.24);scene.view_settings.view_transform='AgX';scene.render.resolution_x=1000;scene.render.resolution_y=1500;scene.render.resolution_percentage=100
for loc,power,size in [((7,-10,20),1600,14),((-8,-7,5),1300,12),((4,5,13),1800,10)]:
 bpy.ops.object.light_add(type='AREA',location=loc);light=bpy.context.object;light.data.energy=power;light.data.size=size;light.rotation_euler=(Vector((-.6,0,8.4))-light.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add(location=(-.7,-55,8.4));cam=bpy.context.object;cam.rotation_euler=(Vector((-.7,0,8.4))-cam.location).to_track_quat('-Z','Y').to_euler();cam.data.type='ORTHO';cam.data.ortho_scale=26;scene.camera=cam
scene.render.filepath=str(WORK/'雷电影佩刀-预览.png');bpy.ops.render.render(write_still=True);bpy.ops.file.pack_all();bpy.ops.wm.save_as_mainfile(filepath=str(WORK/'雷电影佩刀.blend'))
