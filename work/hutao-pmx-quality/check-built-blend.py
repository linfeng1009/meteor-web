"""Read-only independent bind audit of the saved authoring file."""
import bpy, json, math, sys
from pathlib import Path
from mathutils import Matrix
ROOT=Path('/Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web')
sys.path.insert(0,str(ROOT/'scripts/blender'))
import hutao_native_rest as native
path=ROOT/'work/hutao-pmx-model/胡桃喵-完整模型-流星动作适配.blend'
bpy.ops.wm.open_mainfile(filepath=str(path))
arm=next(ob for ob in bpy.data.objects if ob.type=='ARMATURE')
mesh=next(ob for ob in bpy.data.objects if ob.type=='MESH')
C=Matrix.Rotation(-math.pi/2,4,'Z')
errors={e['name']:max(abs(x-y)for a,b in zip(arm.data.bones[e['name']].matrix_local,native.world[e['name']]@C)for x,y in zip(a,b))for e in native.B}
evaluated=mesh.evaluated_get(bpy.context.evaluated_depsgraph_get()).to_mesh()
report=dict(blend=str(path.relative_to(ROOT)),blender=bpy.app.version_string,bones=len(arm.data.bones),meshVertices=len(mesh.data.vertices),meshTriangles=len(mesh.data.polygons),shapeKeys=bool(mesh.data.shape_keys),actions=[dict(name=a.name,frames=list(a.frame_range),slots=len(a.slots))for a in bpy.data.actions],restMatrixErrors=errors,maxRestMatrixError=max(errors.values()),armatureModifier=[dict(type=m.type,correctArmature=m.object==arm)for m in mesh.modifiers if m.type=='ARMATURE'],evaluatedVertexFinite=all(math.isfinite(x)for v in evaluated.vertices for x in v.co))
mesh.evaluated_get(bpy.context.evaluated_depsgraph_get()).to_mesh_clear()
(ROOT/'work/hutao-pmx-quality/blend-audit.json').write_text(json.dumps(report,ensure_ascii=False,indent=2))
assert max(errors.values())<1e-4,report
assert report['evaluatedVertexFinite']
print('INDEPENDENT_BLEND_AUDIT',json.dumps({k:v for k,v in report.items()if k!='restMatrixErrors'},ensure_ascii=False))
