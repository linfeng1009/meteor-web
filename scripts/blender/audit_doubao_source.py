"""Inspect archived inert model data; resolve and pack local image dependencies."""
import bpy, json
from pathlib import Path
from mathutils import Vector

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'assets/source/doubao'
WORK = ROOT / 'work/doubao-import-2026-11-10'
bpy.ops.wm.open_mainfile(filepath=str(SOURCE / '豆包模型.blend'), load_ui=False, use_scripts=False)
images = []
for image in bpy.data.images:
    if image.source != 'FILE':
        continue
    original = image.filepath
    basename = Path(original.replace('\\', '/')).name
    candidates = [SOURCE / basename, SOURCE / 'tex' / basename]
    resolved = next((p for p in candidates if p.is_file()), None)
    if resolved:
        image.filepath = str(resolved)
        image.reload()
    if not image.packed_file and image.has_data:
        image.pack()
    images.append(dict(name=image.name, original=original, archivePath=str(resolved.relative_to(ROOT)) if resolved else None, packed=bool(image.packed_file), size=list(image.size)))
objects = []
for ob in bpy.context.scene.objects:
    row = dict(name=ob.name, type=ob.type, matrix=[list(r) for r in ob.matrix_world])
    if ob.type == 'MESH':
        row.update(vertices=len(ob.data.vertices), polygons=len(ob.data.polygons), materials=[m.name if m else None for m in ob.data.materials], groups=[g.name for g in ob.vertex_groups], modifiers=[dict(type=m.type, name=m.name) for m in ob.modifiers])
    if ob.type == 'ARMATURE':
        row['bones'] = [dict(name=b.name, parent=b.parent.name if b.parent else None, head=list(b.head_local), tail=list(b.tail_local)) for b in ob.data.bones]
    objects.append(row)
(WORK / 'blender-source-audit.json').write_text(json.dumps(dict(blender=bpy.app.version_string, images=images, objects=objects), ensure_ascii=False, indent=2))
bpy.ops.wm.save_as_mainfile(filepath=str(WORK / '豆包-源模型-贴图已内嵌.blend'))
print('SOURCE_AUDIT', json.dumps(dict(objects=[dict(name=o['name'], type=o['type'], vertices=o.get('vertices'), bones=len(o.get('bones', []))) for o in objects], images=images), ensure_ascii=False))
