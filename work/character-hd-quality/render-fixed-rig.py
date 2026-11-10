import bpy,os
from mathutils import Vector
root=os.path.abspath(os.getcwd())
work=os.path.join(root,'work/character-hd')
bpy.ops.wm.open_mainfile(filepath=os.path.join(work,'孟星魂-高清对照.blend'))
scene=bpy.context.scene;scene.cycles.samples=20;scene.render.resolution_x=1400;scene.render.resolution_y=1050
scene.render.filepath=os.path.join(work,'p0-comparison-full.png');bpy.ops.render.render(write_still=True)
for label,name,other in [('original','ORIGINAL RIG • 30 bones + 6 attachments','HD RIG • same original bind'),('enhanced','HD RIG • same original bind','ORIGINAL RIG • 30 bones + 6 attachments')]:
 arm=bpy.data.objects[name];other=bpy.data.objects[other]
 for ob in other.children:ob.hide_render=True
 scene.camera.location=(arm.location.x+9,-36,37);scene.camera.rotation_euler=(Vector((arm.location.x,0,34))-scene.camera.location).to_track_quat('-Z','Y').to_euler();scene.camera.data.ortho_scale=10
 scene.render.resolution_x=900;scene.render.resolution_y=900;scene.render.filepath=os.path.join(work,'p0-'+label+'-face.png');bpy.ops.render.render(write_still=True)
 for ob in other.children:
  if ob.type=='MESH':ob.hide_render=False
