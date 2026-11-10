"""Render final saved local Raiden .blend using the authored preview camera."""
import bpy
from pathlib import Path
from mathutils import Vector
ROOT=Path(__file__).resolve().parents[2];WORK=ROOT/'work/raiden-pmx-model'
bpy.ops.wm.open_mainfile(filepath=str(WORK/'雷神影-礼服模型-流星动作适配.blend'))
s=bpy.context.scene;s.cycles.samples=24
# Fit the full authored long hair, not just the body's humanoid bounding box.
ob=next(o for o in s.objects if o.type=='MESH');evaluated=ob.evaluated_get(bpy.context.evaluated_depsgraph_get());surface=evaluated.to_mesh();points=[evaluated.matrix_world@v.co for v in surface.vertices]
c=s.camera;basis=c.rotation_euler.to_matrix();right=basis.col[0];up=basis.col[1]
xs=[v.dot(right)for v in points];ys=[v.dot(up)for v in points];shift=right*((min(xs)+max(xs))/2-c.location.dot(right))+up*((min(ys)+max(ys))/2-c.location.dot(up));c.location+=shift
c.data.ortho_scale=max(max(ys)-min(ys),(max(xs)-min(xs))*s.render.resolution_y/s.render.resolution_x)*1.13;evaluated.to_mesh_clear()
s.render.filepath=str(WORK/'retargeted-stance.png');bpy.ops.render.render(write_still=True)
c=s.camera;c.location=(0,-85,35);c.rotation_euler=(Vector((0,0,34))-c.location).to_track_quat('-Z','Y').to_euler();c.data.ortho_scale=13;s.render.resolution_x=1000;s.render.resolution_y=1000;s.render.filepath=str(WORK/'retargeted-face.png');bpy.ops.render.render(write_still=True)
