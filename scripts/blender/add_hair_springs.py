"""Recover hair chains from archived PMX metadata; keep native body binding intact.

Run Blender -b --python scripts/blender/add_hair_springs.py [-- --model emilia].
The original Downloads are no longer required. This is a Web spring rig, not a
reproduction of the source MMD rigid-body solver. No textures are repainted.
"""
import sys, json, math, hashlib, shutil, argparse
from pathlib import Path
import bpy
import numpy as np
from mathutils import Vector, Matrix
sys.path.insert(0, str(Path(__file__).parent))
from hutao_native_rest import B, world as REST

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / 'work/hair-physics-2026-11-10'
CONFIG = {
    'hutao': ('胡桃喵-完整模型-流星动作适配.blend', '胡桃-MOD骨架适配-缺原生脸.blend'),
    'raiden': ('雷神影-礼服模型-流星动作适配.blend',),
    'emilia': ('爱蜜莉雅-完整模型-流星动作适配.blend',),
}

def digest(data):
    return hashlib.sha256(json.dumps(data, separators=(',', ':')).encode()).hexdigest()

def upgrade_model(key, write_blend=True):
    out = ROOT / f'dist/assets/enhanced/{key}'
    audit = json.loads((ROOT / f'work/{key}-pmx-model/source-audit.json').read_text())
    skin = json.loads((out / 'mesh.json').read_text())
    manifest = json.loads((out / 'manifest.json').read_text())
    baseline = WORK / 'baseline' / key
    baseline.mkdir(parents=True, exist_ok=True)
    for name in ['mesh.json', 'manifest.json']:
        if not (baseline / name).exists():
            shutil.copyfile(out / name, baseline / name)
    source_bones = audit['bones']
    head = next(b for b in source_bones if b['name'] == '頭')
    head_native = REST[B[13]['name']].translation
    head_scale = (39.4 - head_native.z) / (audit['bounds'][1][1] - head['position'][1])
    def mapped(p):
        x, y, z = p
        if key == 'hutao':
            ys = [.836, 10.712, 13.2586, 15.4597, 16.2583, 19.3258]
            depth = np.interp(y, ys, [t-s*2.1 for s,t in zip([.135,-.47176,-.65543,-.004875,-.13828,-.13828], [1.122,.0594,.1761,.29493,.11498,.11498])])
            return Vector((x*2.4, z*2.1+depth, float(np.interp(y, [-.032,.836,5.872,10.712,15.4597,16.2583,19.3258], [0,2.1424,10.8188,20.2633,31.787,33.2429,39.4]))))
        return head_native + Vector((x-head['position'][0], z-head['position'][2], y-head['position'][1])) * head_scale

    selected = {b['index'] for b in source_bones if any(t in b['name'].lower() for t in ['hair', '髪', '发']) and '錘' not in b['name']}
    ordered = []
    def add(index):
        if index in ordered: return
        parent = source_bones[index]['parent']
        if parent in selected: add(parent)
        ordered.append(index)
    for index in sorted(selected): add(index)
    remap = {original: 30+i for i,original in enumerate(ordered)}
    children = {j: [i for i in ordered if source_bones[i]['parent'] == j] for j in ordered}
    nodes = []
    for index in ordered:
        b = source_bones[index]
        position = mapped(b['position'])
        candidates = children[index]
        tail_id = b.get('tailBone')
        if tail_id is not None and 0 <= tail_id < len(source_bones) and (mapped(source_bones[tail_id]['position'])-position).length > .1:
            tail = mapped(source_bones[tail_id]['position'])
        elif candidates:
            tail = mapped(source_bones[candidates[0]]['position'])
        else:
            tail = mapped([a+c for a,c in zip(b['position'], b.get('tailOffset', [0,0,0]))])
            if (tail-position).length < .1:
                parent = b['parent']
                direction = position-mapped(source_bones[parent]['position']) if parent in selected else Vector((0,0,-1))
                tail = position + direction.normalized()*max(.6, min(direction.length*.7, 3))
        direction = tail-position
        rotation = direction.to_track_quat('Y', 'Z')
        parent_index = remap.get(b['parent'], 13)
        depth = 0 if parent_index == 13 else nodes[parent_index-30]['depth']+1
        nodes.append(dict(name=f"spring_{b['name']}", sourceBone=index, sourceName=b['name'], parent=parent_index,
                          position=list(position), tail=list(tail), rotation=[rotation.x, rotation.y, rotation.z, rotation.w],
                          depth=depth, stiffness=220 if depth==0 else 150 if depth==1 else 110,
                          damping=30 if depth==0 else 24, maxAngle=.01 if depth==0 else .025, gravity=0 if depth==0 else .003,
                          follow=.98,globalMaxAngle=.04,
                          radius=.16, next=remap.get(candidates[0]) if candidates else None))

    hair_materials = [i for i,m in enumerate(skin['materials']) if m.get('sourceName',m.get('name')) in ['发','Hair','HairFront']]
    hair_vertices = sorted({i for f in skin['faces'] if f['material'] in hair_materials for i in f['indices']})
    protected = {i for f in skin['faces'] if f['material'] not in hair_materials for i in f['indices']}
    hair_vertices = [i for i in hair_vertices if i not in protected]
    original = json.loads((baseline / 'mesh.json').read_text())
    body_ids = sorted(set(range(skin['vertexCount']))-set(hair_vertices))
    def body_binding(s):
        return [[i,s['skinIndices'][i*4:i*4+4],s['skinWeights'][i*4:i*4+4]] for i in body_ids]
    assert body_binding(skin) == body_binding(original), 'body binding changed outside hair'
    positions = np.array(skin['positions']).reshape(-1,3)
    starts = np.array([n['position'] for n in nodes]); ends = np.array([n['tail'] for n in nodes]); axes = ends-starts
    lengths2 = np.sum(axes*axes, axis=1)
    for vertex in hair_vertices:
        p = positions[vertex]
        t = np.clip(np.sum((p-starts)*axes,axis=1)/lengths2,0,1)
        d2 = np.sum((p-starts-t[:,None]*axes)**2,axis=1)
        nearest = np.argsort(d2)[:2]
        acc = {}
        for j in nearest:
            node = nodes[int(j)]; progress = node['depth']+float(t[j])
            fade = max(0,min(1,(progress-.25)/1.25)); fade = fade*fade*(3-2*fade)
            weight = 1/(float(d2[j])+.45)**2
            acc[13] = acc.get(13,0) + weight*(1-fade)
            a,b = 30+int(j), node['next'] or 30+int(j)
            acc[a] = acc.get(a,0)+weight*fade*(1-float(t[j]))
            acc[b] = acc.get(b,0)+weight*fade*float(t[j])
        influences = sorted(((i,w) for i,w in acc.items() if w>1e-8),key=lambda v:-v[1])[:4]
        total = sum(w for i,w in influences)
        skin['skinIndices'][vertex*4:vertex*4+4] = [i for i,w in influences]+[0]*(4-len(influences))
        skin['skinWeights'][vertex*4:vertex*4+4] = [w/total for i,w in influences]+[0]*(4-len(influences))
    face_ids = [i for i,m in enumerate(skin['materials']) if m.get('name') in ['面','面1','面2','Face','Face_NoOutline']]
    fv = list({i for f in skin['faces'] if f['material'] in face_ids for i in f['indices']})
    lo,hi = positions[fv].min(axis=0),positions[fv].max(axis=0)
    center = Vector((lo+hi)/2); center.y += .6
    head_offset = REST[B[13]['name']].inverted() @ center
    rig = dict(schema=1, type='web-spring-bone', nativeBoneCount=30, bones=nodes,
               hairMaterials=hair_materials, vertexCount=len(hair_vertices), bodyBindingSha256=digest(body_binding(original)),
               colliders=[dict(shape='sphere', bone=13, offset=list(head_offset), radius=float((hi[0]-lo[0])*.43)),
                          dict(shape='capsule', bone=12, endBone=1, radius=2.1),
                          dict(shape='capsule', bone=15, endBone=23, radius=1.3)],
               provenance='Recovered source PMX bone positions/hierarchy; smooth proximity weights reconstructed from existing native mesh. Web spring parameters, not source MMD rigid bodies.')
    skin['secondaryMotion'] = rig
    for i in hair_materials:
        skin['materials'][i].update(hairSurface=True, roughness=.62, anisotropy=.35)
    assert body_binding(skin) == body_binding(original)
    manifest['retarget'].update(hairPhysics=True, hairBinding='independent recovered hair chains with restrained inertia, strong damping and body colliders', hairPhysicsProfile='web-spring-bone-v2-restrained', originalMmdPhysics=False)
    manifest['stats']['secondaryBones'] = len(nodes)
    manifest['provenance']['hairPhysics'] = rig['provenance']
    manifest['provenance']['limits'] = [x for x in manifest['provenance']['limits'] if 'hair, cloth or rigid-body' not in x and 'hair, cloth' not in x]
    limit = 'Web hair springs and approximate body colliders; original MMD rigid-body solver, cloth physics and hair self-collision are not reproduced.'
    if limit not in manifest['provenance']['limits']: manifest['provenance']['limits'].append(limit)
    (out / 'mesh.json').write_text(json.dumps(skin,separators=(',',':')),encoding='utf-8')
    (out / 'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
    evidence = dict(model=key, hairVertices=len(hair_vertices), chains=sum(n['parent']==13 for n in nodes), extraBones=len(nodes), bodyBindingSha256=rig['bodyBindingSha256'], meshSha256=hashlib.sha256((out/'mesh.json').read_bytes()).hexdigest())
    if write_blend:
        candidates = [ROOT/f'work/{key}-pmx-model'/n for n in CONFIG[key]]
        src = next((p for p in candidates if p.exists()), None)
        if src:
            bpy.ops.wm.open_mainfile(filepath=str(src))
            ob = next(o for o in bpy.context.scene.objects if o.type=='MESH' and len(o.data.vertices)==skin['vertexCount'] and any(m.type=='ARMATURE' for m in o.modifiers))
            arm = next(m.object for m in ob.modifiers if m.type=='ARMATURE')
            bpy.context.view_layer.objects.active=arm; bpy.ops.object.mode_set(mode='EDIT')
            for node in nodes: arm.data.edit_bones.new(node['name'])
            for node in nodes:
                bone=arm.data.edit_bones[node['name']]; parent=node['parent']
                bone.parent=arm.data.edit_bones[B[parent]['name'] if parent<30 else nodes[parent-30]['name']]
                bone.head=Vector(node['position']); bone.tail=Vector(node['tail'])
                from mathutils import Quaternion
                q=node['rotation']; bone.align_roll(Quaternion((q[3],q[0],q[1],q[2])).to_matrix().col[2])
            bpy.ops.object.mode_set(mode='OBJECT')
            for node in nodes: ob.vertex_groups.new(name=node['name'])
            for vertex in hair_vertices:
                for group in list(ob.data.vertices[vertex].groups): ob.vertex_groups[group.group].remove([vertex])
                for j,w in zip(skin['skinIndices'][vertex*4:vertex*4+4],skin['skinWeights'][vertex*4:vertex*4+4]):
                    if w>0: ob.vertex_groups[B[j]['name'] if j<30 else nodes[j-30]['name']].add([vertex],w,'REPLACE')
            for i in hair_materials:
                mat=ob.data.materials[i]
                if mat.use_nodes:
                    bs=mat.node_tree.nodes.get('Principled BSDF')
                    if bs: bs.inputs['Roughness'].default_value=.62
            arm['web_hair_springs']=json.dumps(rig,ensure_ascii=False)
            dst=WORK/f'{key}-弹簧发束.blend'; bpy.ops.wm.save_as_mainfile(filepath=str(dst)); evidence['blend']=str(dst.relative_to(ROOT))
    (WORK/f'{key}-asset.json').write_text(json.dumps(evidence,ensure_ascii=False,indent=2))
    print('HAIR_RIG',json.dumps(evidence,ensure_ascii=False),flush=True)
    return evidence

if __name__=='__main__':
    parser=argparse.ArgumentParser(); parser.add_argument('--model',choices=list(CONFIG)); parser.add_argument('--skip-blend',action='store_true')
    args=parser.parse_args(sys.argv[sys.argv.index('--')+1:] if '--' in sys.argv else [])
    WORK.mkdir(parents=True,exist_ok=True)
    for key in ([args.model] if args.model else CONFIG): upgrade_model(key,not args.skip_blend)
