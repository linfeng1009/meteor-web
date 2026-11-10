"""Render the final local blend without changing exported runtime assets."""
import bpy
from pathlib import Path
from mathutils import Vector
p=Path(__file__).resolve().parents[2]/'work/hutao-pmx-model';bpy.ops.wm.open_mainfile(filepath=str(p/'胡桃喵-完整模型-流星动作适配.blend'))
s=bpy.context.scene;s.frame_set(1);c=s.camera;c.location=(27,-110,44);c.data.ortho_scale=48;c.rotation_euler=(Vector((0,0,20))-c.location).to_track_quat('-Z','Y').to_euler();s.render.resolution_x=1000;s.render.resolution_y=1200;s.render.filepath=str(p/'retargeted-stance.png');bpy.ops.render.render(write_still=True)
c.location=(0,-85,35);c.data.ortho_scale=13;c.rotation_euler=(Vector((0,0,34))-c.location).to_track_quat('-Z','Y').to_euler();s.render.resolution_x=1000;s.render.resolution_y=1000;s.render.filepath=str(p/'retargeted-face.png');bpy.ops.render.render(write_still=True)
