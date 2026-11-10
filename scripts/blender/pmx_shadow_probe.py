import bpy,os
from pathlib import Path
p=Path(__file__).resolve().parents[2]/'work/hutao-pmx-model';bpy.ops.wm.open_mainfile(filepath=str(p/'胡桃喵-完整模型-流星动作适配.blend'))
ob=next(o for o in bpy.data.objects if o.type=='MESH');ob.visible_shadow=False
bpy.context.scene.render.filepath=str(p/'face-no-self-shadow.png');bpy.ops.render.render(write_still=True)
