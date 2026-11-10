"""Render the exported game model. Run export_phoenix_spear.mjs first."""
import json
import math
import os
import bpy
from mathutils import Vector

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
WORK = os.path.join(ROOT, 'work/phoenix-spear')
with open(os.path.join(WORK, 'mesh-parts.json')) as source:
    data = json.load(source)
bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.delete(use_global=False)

# Exported PNGs preserve DataTexture bytes and its lower-left UV origin.
images = []
for item in data['textures']:
    image = bpy.data.images.load(os.path.join(WORK, item['png']), check_existing=False)
    image.colorspace_settings.name = 'sRGB'
    images.append(image)

materials = []
for item in data['materials']:
    material = bpy.data.materials.new(item['name'])
    material.use_nodes = True
    material.diffuse_color = (*item['color'], item['opacity'])
    shader = material.node_tree.nodes.get('Principled BSDF')
    shader.inputs['Base Color'].default_value = (*item['color'], 1)
    shader.inputs['Metallic'].default_value = item['metalness']
    shader.inputs['Roughness'].default_value = item['roughness']
    shader.inputs['Coat Weight'].default_value = item['clearcoat']
    shader.inputs['Coat Roughness'].default_value = item['clearcoatRoughness']
    shader.inputs['Alpha'].default_value = item['opacity']
    shader.inputs['Emission Color'].default_value = (*item['emissive'], 1)
    shader.inputs['Emission Strength'].default_value = item['emissiveIntensity']
    shader.inputs['Sheen Weight'].default_value = item['sheen']
    shader.inputs['Sheen Tint'].default_value = (*item['sheenColor'], 1)
    if item['map'] is not None:
        texture = material.node_tree.nodes.new('ShaderNodeTexImage')
        texture.image = images[item['map']]
        texture.extension = 'EXTEND'
        # MeshPhysicalMaterial multiplies the map by material.color.
        multiply = material.node_tree.nodes.new('ShaderNodeMixRGB')
        multiply.blend_type = 'MULTIPLY'
        multiply.inputs[0].default_value = 1
        multiply.inputs[2].default_value = (*item['color'], 1)
        material.node_tree.links.new(texture.outputs['Color'], multiply.inputs[1])
        material.node_tree.links.new(multiply.outputs['Color'], shader.inputs['Base Color'])
    materials.append(material)

for item in data['objects']:
    positions, indices = item['positions'], item['indices']
    vertices = [positions[i:i+3] for i in range(0, len(positions), 3)]
    triangles = [indices[i:i+3] for i in range(0, len(indices), 3)]
    mesh = bpy.data.meshes.new(item['name'])
    mesh.from_pydata(vertices, [], triangles)
    mesh.update()
    obj = bpy.data.objects.new(item['name'], mesh)
    bpy.context.collection.objects.link(obj)
    for material_id in item['materials']:
        mesh.materials.append(materials[material_id])
    for group in item['groups']:
        for face in range(group['start'] // 3, (group['start'] + group['count']) // 3):
            mesh.polygons[face].material_index = group['materialIndex']
    if item['uvs']:
        uv_layer = mesh.uv_layers.new(name='Game UV')
        for loop in mesh.loops:
            offset = loop.vertex_index * 2
            uv_layer.data[loop.index].uv = item['uvs'][offset:offset+2]
    if item['normals']:
        normals = item['normals']
        mesh.normals_split_custom_set_from_vertices([normals[i:i+3] for i in range(0, len(normals), 3)])
        for polygon in mesh.polygons:
            polygon.use_smooth = True

scene = bpy.context.scene
scene.render.engine = 'CYCLES'
scene.cycles.device = 'CPU'
scene.cycles.samples = 32
scene.cycles.use_denoising = True
scene.render.resolution_x = 1000
scene.render.resolution_y = 1700
scene.render.resolution_percentage = 100
scene.render.film_transparent = False
scene.view_settings.view_transform = 'AgX'
scene.world.use_nodes = True
background = scene.world.node_tree.nodes.get('Background')
background.inputs['Color'].default_value = (.055, .085, .15, 1)
background.inputs['Strength'].default_value = .6
for location, energy, size, color in [((-18,-24,29),13000,24,(.86,.94,1)),((16,-17,3),11000,20,(1,.91,.79)),((2,14,15),15000,22,(.59,.78,1))]:
    bpy.ops.object.light_add(type='AREA', location=location)
    light = bpy.context.object
    light.data.energy = energy
    light.data.shape = 'DISK'
    light.data.size = size
    light.data.color = color
    light.rotation_euler = (Vector((0,0,5)) - light.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add(location=(0,-90,4.5))
camera = bpy.context.object
camera.rotation_euler = (Vector((0,0,4.5))-camera.location).to_track_quat('-Z','Y').to_euler()
camera.data.type = 'ORTHO'
camera.data.ortho_scale = 60
scene.camera = camera
scene.render.filepath = os.path.join(WORK, '霜翎凤鸣枪-预览.png')
bpy.ops.render.render(write_still=True)
for image in images:
    image.pack()
bpy.ops.wm.save_as_mainfile(filepath=os.path.join(WORK, '霜翎凤鸣枪.blend'))
print('Rendered runtime spear at time=0.5, with %d meshes and %d textures.' % (len(data['objects']), len(images)))
