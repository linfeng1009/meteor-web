import bpy,sys,os,math,json
from mathutils import Matrix,Vector
sys.path.insert(0,os.path.dirname(__file__))
from hutao_native_rest import B,D,entries,world as REST,resolve
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
d=bpy.data.armatures.new('probe');arm=bpy.data.objects.new('probe',d);bpy.context.collection.objects.link(arm);bpy.context.view_layer.objects.active=arm;arm.select_set(True);bpy.ops.object.mode_set(mode='EDIT');C=Matrix.Rotation(-math.pi/2,4,'Z')
for e in B:d.edit_bones.new(e['name'])
for e in B:
 if resolve(e['parent'])in d.edit_bones:d.edit_bones[e['name']].parent=d.edit_bones[resolve(e['parent'])]
for e in B:
 b=d.edit_bones[e['name']];m=REST[e['name']]@C;b.head=m.translation;b.tail=m.translation+m.to_3x3().col[1]*.8;b.align_roll(m.to_3x3().col[2]);print('EDIT',e['name'],max(abs(x-y)for a,z in zip(b.matrix,m)for x,y in zip(a,z)))
bpy.ops.object.mode_set(mode='OBJECT');print('REST',[(e['name'],max(abs(x-y)for a,z in zip(d.bones[e['name']].matrix_local,REST[e['name']]@C)for x,y in zip(a,z)))for e in B])
