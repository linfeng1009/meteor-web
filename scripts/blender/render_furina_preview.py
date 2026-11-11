"""Render the built Furina rig with its original textures for visual acceptance.

Blender --background --python scripts/blender/render_furina_preview.py
"""
import bpy, os
from pathlib import Path
from mathutils import Vector

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / 'work/furina-import-2026-11-11'
bpy.ops.wm.open_mainfile(filepath=str(WORK / '芙宁娜-流星动作适配.blend'))

scene = bpy.context.scene
scene.render.engine = 'CYCLES'; scene.cycles.samples = 48; scene.cycles.use_denoising = True
scene.render.resolution_x = 900; scene.render.resolution_y = 1300; scene.render.resolution_percentage = 100
scene.view_settings.view_transform = 'AgX'
scene.view_settings.exposure = 1.35
scene.view_settings.look = 'AgX - Medium High Contrast' if 'AgX - Medium High Contrast' in [i.identifier for i in bpy.types.ColorManagedViewSettings.bl_rna.properties['look'].enum_items] else 'None'
world = bpy.data.worlds.new('Studio'); scene.world = world; world.use_nodes = True
world.node_tree.nodes['Background'].inputs[0].default_value = (.035, .045, .06, 1)
world.node_tree.nodes['Background'].inputs[1].default_value = .35

# Frame 1 of the baked native idle keeps the source rig length and the game pose.
scene.frame_set(1)

for location, power, size, color in [((28, -54, 46), 9000, 30, (1, .96, .9)),
                                     ((-40, -30, 34), 5200, 26, (.72, .86, 1)),
                                     ((34, 24, 40), 6400, 26, (.86, .9, 1)),
                                     ((0, 46, 26), 3400, 22, (.9, .88, .98)),
                                     ((0, -46, 12), 5200, 34, (.96, .97, 1)),
                                     ((-18, -40, 6), 2600, 26, (.9, .95, 1))]:
    bpy.ops.object.light_add(type='AREA', location=location)
    light = bpy.context.object
    light.data.energy = power; light.data.size = size; light.data.color = color
    light.rotation_euler = (Vector((0, 0, 22)) - light.location).to_track_quat('-Z', 'Y').to_euler()


def shot(name, location, target, ortho):
    bpy.ops.object.camera_add(location=location)
    camera = bpy.context.object
    camera.rotation_euler = (Vector(target) - camera.location).to_track_quat('-Z', 'Y').to_euler()
    camera.data.type = 'ORTHO'; camera.data.ortho_scale = ortho
    scene.camera = camera
    # Camera-axis sun: guarantees every surface facing the viewer is lit, so the
    # silhouette never falls into an unlit black band.
    bpy.ops.object.light_add(type='SUN')
    sun = bpy.context.object
    sun.data.energy = 2.6; sun.data.angle = .6
    sun.rotation_euler = camera.rotation_euler
    scene.render.filepath = str(WORK / name)
    bpy.ops.render.render(write_still=True)
    bpy.data.objects.remove(camera, do_unlink=True)
    bpy.data.objects.remove(sun, do_unlink=True)


shot('preview.png', (26, -66, 34), (0, 0, 21), 44)
shot('preview-front.png', (0, -70, 26), (0, 0, 21), 44)
print('FURINA_PREVIEW_DONE', flush=True)