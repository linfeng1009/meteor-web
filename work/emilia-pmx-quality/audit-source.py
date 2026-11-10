"""Independent read-only PMX geometry/material/bone audit (Python stdlib)."""
import collections, hashlib, json, math, pathlib, struct

ROOT = pathlib.Path(__file__).resolve().parent
SOURCE = pathlib.Path('/Users/dulinfeng/Downloads/Emilia_v1/Emilia_v1.pmx')
raw = SOURCE.read_bytes()
offset = 0

def unpack(fmt):
    global offset
    size = struct.calcsize('<' + fmt)
    result = struct.unpack_from('<' + fmt, raw, offset)
    offset += size
    return result[0] if len(result) == 1 else list(result)

def blob(size):
    global offset
    data = raw[offset:offset + size]
    assert len(data) == size
    offset += size
    return data

assert blob(4) == b'PMX '
version = unpack('f')
header = list(blob(unpack('B')))
encoding = 'utf-16-le' if header[0] == 0 else 'utf-8'
extra_uv, vertex_size, texture_size, material_size, bone_size, morph_size, rigid_size = header[1:8]
def string(): return blob(unpack('i')).decode(encoding)
def index(size, unsigned=False): return unpack({1:'B' if unsigned else 'b', 2:'H' if unsigned else 'h', 4:'I' if unsigned else 'i'}[size])
names = {key:string() for key in ['name', 'englishName', 'comment', 'englishComment']}

vertices=[]
types=collections.Counter()
for _ in range(unpack('i')):
    pos, normal, uv = unpack('3f'), unpack('3f'), unpack('2f')
    extras = [unpack('4f') for _ in range(extra_uv)]
    kind = unpack('B'); types[kind] += 1
    if kind == 0:
        bones, weights = [index(bone_size)], [1.]
    elif kind in [1, 3]:
        bones = [index(bone_size), index(bone_size)]; w=unpack('f'); weights=[w,1-w]
        if kind == 3: sdef = unpack('9f')
    elif kind in [2, 4]:
        bones=[index(bone_size) for _ in range(4)]; weights=unpack('4f')
    else: raise ValueError(('deformation', kind, offset))
    edge=unpack('f')
    vertices.append(dict(position=pos,normal=normal,uv=uv,bones=bones,weights=weights,edge=edge))
faces = [index(vertex_size,True) for _ in range(unpack('i'))]
textures = [string() for _ in range(unpack('i'))]
materials=[]
face_cursor=0
for _ in range(unpack('i')):
    name,en=string(),string()
    diffuse,specular,power,ambient=unpack('4f'),unpack('3f'),unpack('f'),unpack('3f')
    flags,edge_color,edge_size=unpack('B'),unpack('4f'),unpack('f')
    texture,sphere,mode=index(texture_size),index(texture_size),unpack('B')
    shared=unpack('B'); toon=unpack('B') if shared else index(texture_size)
    comment=string(); count=unpack('i')
    used=sorted(set(faces[face_cursor:face_cursor+count])); face_cursor+=count
    coords=[vertices[i]['position'] for i in used]
    bounds=[[min(v[k] for v in coords),max(v[k] for v in coords)] for k in range(3)] if coords else None
    materials.append(dict(name=name,englishName=en,diffuse=diffuse,texture=texture,texturePath=textures[texture] if texture>=0 else None,sphere=sphere,sphereMode=mode,toon=toon,sharedToon=shared,flags=flags,comment=comment,indices=count,triangles=count//3,uniqueVertices=len(used),bounds=bounds))
assert face_cursor == len(faces)
bones=[]
for i in range(unpack('i')):
    name,en=string(),string();pos=unpack('3f'); parent=index(bone_size);layer=unpack('i'); flags=unpack('H')
    tail=index(bone_size) if flags & 1 else unpack('3f')
    inheritance=None
    if flags & 0x300: inheritance=[index(bone_size),unpack('f')]
    if flags & 0x400: axis=unpack('3f')
    if flags & 0x800: localAxes=unpack('6f')
    if flags & 0x2000: external=unpack('i')
    ik=None
    if flags & 0x20:
        target=index(bone_size); loops=unpack('i'); angle=unpack('f'); links=[]
        for _ in range(unpack('i')):
            link=index(bone_size); limited=unpack('B'); limits=unpack('6f') if limited else None
            links.append(dict(bone=link,limits=limits))
        ik=dict(target=target,loops=loops,angle=angle,links=links)
    bones.append(dict(index=i,name=name,englishName=en,position=pos,parent=parent,layer=layer,flags=flags,tail=tail,inheritance=inheritance,ik=ik))
geometry_end=offset
morphs=[]
for i in range(unpack('i')):
    name,en=string(),string();panel,kind=unpack('B'),unpack('B');count=unpack('i')
    for _ in range(count):
        if kind in [0,9]: index(morph_size);unpack('f')
        elif kind == 1: index(vertex_size,True);unpack('3f')
        elif kind == 2: index(bone_size);unpack('7f')
        elif kind in range(3,8): index(vertex_size,True);unpack('4f')
        elif kind == 8: index(material_size);unpack('B');unpack('28f')
        elif kind == 10: index(rigid_size);unpack('B');unpack('6f')
        else: raise ValueError(('morph',kind,offset))
    morphs.append(dict(name=name,englishName=en,kind=kind,count=count))
display_count=unpack('i')
for _ in range(display_count):
    string();string();unpack('B')
    for _ in range(unpack('i')):
        kind=unpack('B');index(bone_size if kind == 0 else morph_size)
rigid_count=unpack('i')
for _ in range(rigid_count):
    string();string();index(bone_size);unpack('B');unpack('H');unpack('B');unpack('14f');unpack('B')
joint_count=unpack('i')
for _ in range(joint_count):
    string();string();kind=unpack('B');assert kind==0
    index(rigid_size);index(rigid_size);unpack('24f')

files=[]
for p in sorted(SOURCE.parent.rglob('*')):
    if p.is_file() and p.name != '.DS_Store':
        data=p.read_bytes();entry=dict(path=str(p.relative_to(SOURCE.parent)),bytes=len(data),sha256=hashlib.sha256(data).hexdigest())
        if data.startswith(b'\x89PNG\r\n\x1a\n'): entry['dimensions']=list(struct.unpack_from('>II',data,16))
        if data.startswith(b'BM'):entry['dimensions']=list(struct.unpack_from('<ii',data,18))
        files.append(entry)
positions=[v['position'] for v in vertices]
errors=[]
for i,v in enumerate(vertices):
    if not all(math.isfinite(x) for values in [v['position'],v['normal'],v['uv'],v['weights']] for x in values): errors.append(['nonfinite',i])
    if abs(sum(v['weights'])-1)>1e-5:errors.append(['weights',i,sum(v['weights'])])
    if any(b<0 or b>=len(bones) for b,w in zip(v['bones'],v['weights']) if w>1e-7):errors.append(['boneindex',i])
for path in textures:
    target=SOURCE.parent.joinpath(*path.replace('\\','/').split('/'))
    if not target.is_file():errors.append(['missingtexture',path])
assert all(i>=0 and i<len(vertices) for i in faces)
degenerate=sum(len(set(faces[i:i+3]))<3 for i in range(0,len(faces),3))
report=dict(source=str(SOURCE),sha256=hashlib.sha256(raw).hexdigest(),bytes=len(raw),version=version,header=header,names=names,vertices=len(vertices),triangles=len(faces)//3,deformationTypes=dict(types),textures=textures,materials=materials,bones=bones,morphs=morphs,rigidBodies=rigid_count,joints=joint_count,bytesConsumed=offset,trailingBytes=len(raw)-offset,geometryEnd=geometry_end,bounds=[[min(p[k]for p in positions),max(p[k]for p in positions)]for k in range(3)],normalLengthRange=[min(math.dist(v['normal'],[0,0,0])for v in vertices),max(math.dist(v['normal'],[0,0,0])for v in vertices)],indexDegenerateTriangles=degenerate,errors=errors,files=files)
(ROOT/'source-audit.json').write_text(json.dumps(report,ensure_ascii=False,indent=2))
print(json.dumps({k:report[k]for k in ['vertices','triangles','version','bounds','deformationTypes','normalLengthRange','rigidBodies','joints','trailingBytes','errors','sha256']},ensure_ascii=False,indent=2))
print('MODEL:',names)
print('MATERIALS:',json.dumps(materials,ensure_ascii=False))
print('BONES:',[(b['index'],b['name'],b['englishName'])for b in bones])
