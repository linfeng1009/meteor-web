import bpy,json,os
from mathutils import Vector
root=os.path.abspath(os.path.join(os.path.dirname(__file__),'../..'))
work=os.path.join(root,'work/butterfly-sword')
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
for i,item in enumerate(json.load(open(os.path.join(work,'mesh-parts.json')))):
 p=item['positions'];idx=item['indices'];verts=[(p[i],p[i+1],p[i+2]) for i in range(0,len(p),3)];faces=[idx[i:i+3] for i in range(0,len(idx),3)]
 mesh=bpy.data.meshes.new('Part %02d'%i);mesh.from_pydata(verts,[],faces);mesh.update();ob=bpy.data.objects.new('Sword part %02d'%i,mesh);bpy.context.collection.objects.link(ob)
 mat=bpy.data.materials.new('Material %02d'%i);mat.diffuse_color=(*item['color'],1);mat.use_nodes=True;bs=mat.node_tree.nodes.get('Principled BSDF');bs.inputs['Base Color'].default_value=(*item['color'],1);bs.inputs['Metallic'].default_value=item['metalness'];bs.inputs['Roughness'].default_value=item['roughness'];ob.data.materials.append(mat)
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=24;scene.cycles.use_denoising=True;scene.world.color=(.08,.1,.13);scene.view_settings.view_transform='AgX';scene.render.resolution_x=800;scene.render.resolution_y=1200;scene.render.resolution_percentage=100
for loc,power,size in [((8,-10,19),1200,12),((-10,-7,5),1500,14),((5,7,12),1800,10)]:
 bpy.ops.object.light_add(type='AREA',location=loc);l=bpy.context.object;l.data.energy=power;l.data.size=size;l.rotation_euler=(Vector((0,0,8))-l.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add(location=(0,-38,8));cam=bpy.context.object;cam.rotation_euler=(Vector((0,0,8))-cam.location).to_track_quat('-Z','Y').to_euler();cam.data.type='ORTHO';cam.data.ortho_scale=27;scene.camera=cam
scene.render.filepath=os.path.join(work,'月蝶剑-预览.png');bpy.ops.render.render(write_still=True);bpy.ops.wm.save_as_mainfile(filepath=os.path.join(work,'月蝶剑-三维试版.blend'))
