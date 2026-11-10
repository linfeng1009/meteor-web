import bpy, sys, math, json
from mathutils import Matrix, Vector
sys.path.insert(0,'/Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web/scripts/blender')
import hutao_native_rest as native
C=Matrix.Rotation(-math.pi/2,4,'Z')
R={e['name']:native.world[e['name']]@C for e in native.B}
results={}
for variant in ['matrix-length-parent','parent-matrix-length','head-tail-roll','matrix-no-length']:
 bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
 arm=bpy.data.armatures.new(variant);ob=bpy.data.objects.new(variant,arm);bpy.context.collection.objects.link(ob);bpy.context.view_layer.objects.active=ob;ob.select_set(True)
 bpy.ops.object.mode_set(mode='EDIT')
 for e in native.B:
  b=arm.edit_bones.new(e['name']);b.head=(0,0,0);b.tail=(0,0,.8)
 if variant!='matrix-length-parent':
  for e in native.B:
   p=native.resolve(e['parent'])
   if p in arm.edit_bones:arm.edit_bones[e['name']].parent=arm.edit_bones[p]
 for e in native.B:
  b=arm.edit_bones[e['name']];m=R[e['name']]
  if variant=='head-tail-roll':
   b.head=m.translation;b.tail=m.translation+m.to_3x3()@Vector((0,.8,0));b.align_roll(m.to_3x3()@Vector((0,0,1)))
  else:
   b.matrix=m
   if variant!='matrix-no-length':b.length=.8
 if variant=='matrix-length-parent':
  for e in native.B:
   p=native.resolve(e['parent'])
   if p in arm.edit_bones:arm.edit_bones[e['name']].parent=arm.edit_bones[p]
 bpy.ops.object.mode_set(mode='OBJECT')
 results[variant]={e['name']:max(abs(x-y)for ra,rb in zip(arm.bones[e['name']].matrix_local,R[e['name']])for x,y in zip(ra,rb)) for e in native.B}
print('REST_MATRIX_RESULT',json.dumps(results))
open('/Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web/work/hutao-pmx-quality/edit-rest-audit.json','w').write(json.dumps(results,indent=2))
