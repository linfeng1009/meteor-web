import bpy,os
from pathlib import Path
from mathutils import Vector
p=Path(__file__).resolve().parents[2]/'work/hutao-pmx-model';bpy.ops.wm.open_mainfile(filepath=str(p/'胡桃喵-完整模型-流星动作适配.blend'))
for m in bpy.data.materials:
 if not m.use_nodes:continue
 nt=m.node_tree;tex=next((n for n in nt.nodes if n.type=='TEX_IMAGE'),None);out=next(n for n in nt.nodes if n.type=='OUTPUT_MATERIAL');e=nt.nodes.new('ShaderNodeEmission')
 if tex:nt.links.new(tex.outputs['Color'],e.inputs['Color'])
 nt.links.new(e.outputs[0],out.inputs['Surface'])
bpy.context.scene.render.filepath=str(p/'face-emission-only.png');bpy.ops.render.render(write_still=True)
