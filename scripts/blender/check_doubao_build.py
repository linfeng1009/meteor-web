"""Reopen the finished Blender asset and verify packed dependencies and actions."""
import bpy, json, hashlib
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'work/doubao-import-2026-11-10'
path=WORK/'豆包-完整人物-流星动作适配.blend'
bpy.ops.wm.open_mainfile(filepath=str(path),load_ui=False,use_scripts=False)
surface=next(o for o in bpy.context.scene.objects if o.type=='MESH')
arm=next(o for o in bpy.context.scene.objects if o.type=='ARMATURE')
assert len(surface.data.vertices)==107855
assert len(surface.data.polygons)==180698
assert len(arm.data.bones)==39
assert len(surface.vertex_groups)==39
assert not bpy.data.libraries
images=[]
for image in bpy.data.images:
    if image.source!='FILE':continue
    assert image.packed_file, image.name+' must embed its texture bytes'
    resolution=list(image.size)
    _=image.pixels[0]  # Packed images load lazily when a .blend is reopened.
    assert image.has_data, image.name+' must decode from its packed texture'
    assert '/Downloads/' not in image.filepath
    assert resolution==[4096,4096]
    packed_hash=hashlib.sha256(image.packed_file.data).hexdigest()
    assert packed_hash=='9352e39bc145ddd9227049d020b36c400d159746d9fdf0568f03abadc489baa6'
    images.append(dict(name=image.name,packed=True,resolution=list(image.size),packedSha256=packed_hash))
assert len(images)==1
actions=[dict(name=a.name,pose=a.get('native_pose_id'),frames=list(a.frame_range)) for a in bpy.data.actions if 'native_pose_id' in a]
assert sorted(a['pose'] for a in actions)==[6,144,151,262]
max_weight_error=max(abs(sum(g.weight for g in v.groups)-1) for v in surface.data.vertices)
assert max_weight_error<1e-5
result=dict(blender=bpy.app.version_string,blend=str(path.relative_to(ROOT)),blendSha256=hashlib.sha256(path.read_bytes()).hexdigest(),vertices=len(surface.data.vertices),triangles=len(surface.data.polygons),bodyBones=30,hairBones=9,images=images,actions=actions,maxWeightError=max_weight_error,linkedLibraries=0,externalDownloadsRequired=False)
(WORK/'blend-validation.json').write_text(json.dumps(result,ensure_ascii=False,indent=2))
print('BLEND_VERIFIED',json.dumps(result,ensure_ascii=False))
