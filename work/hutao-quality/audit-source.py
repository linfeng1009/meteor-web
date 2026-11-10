"""Read-only GIMI buffer inspection; no injector or original game execution."""
from pathlib import Path
from collections import Counter
import hashlib
import json
import math
import struct
import sys

SOURCE = Path(sys.argv[1]) if len(sys.argv) > 1 else Path('/Users/dulinfeng/Downloads/hutao_black_stockings_mod_4k/HuTaoMod4K')
OUTPUT = Path(__file__).with_name('source-audit.json')

def records(name, stride, fmt, offset=0):
    data = (SOURCE / name).read_bytes()
    assert len(data) % stride == 0, f'{name}: incomplete vertex record'
    return [struct.unpack_from(fmt, data, base + offset) for base in range(0, len(data), stride)]

positions = records('HuTaoPosition.buf', 40, '<3f')
normals = records('HuTaoPosition.buf', 40, '<3f', 12)
tangents = records('HuTaoPosition.buf', 40, '<4f', 24)
weights = records('HuTaoBlend.buf', 32, '<4f')
joints = records('HuTaoBlend.buf', 32, '<4I', 16)
colors = records('HuTaoTexcoord.buf', 12, '<4B')
uvs = records('HuTaoTexcoord.buf', 12, '<2f', 4)
count = len(positions)
assert count == len(weights) == len(uvs) == 14672
active = Counter(j for ws, ids in zip(weights, joints) for w, j in zip(ws, ids) if w > 1e-7)
parts = {}
for name in ['HuTaoHead.ib', 'HuTaoBody.ib']:
    data = (SOURCE / name).read_bytes()
    assert len(data) % 12 == 0
    ids = struct.unpack('<' + 'I' * (len(data) // 4), data)
    used = set(ids)
    assert max(ids) < count
    parts[name] = dict(indices=len(ids), triangles=len(ids) // 3, min=min(ids), max=max(ids), uniqueVertices=len(used), outOfBounds=0,
        bbox=[[min(positions[i][a] for i in used) for a in range(3)], [max(positions[i][a] for i in used) for a in range(3)]],
        degenerateIndexTriangles=sum(len(set(ids[i:i+3])) < 3 for i in range(0, len(ids), 3)))
dds = {}
for path in SOURCE.glob('*.dds'):
    data = path.read_bytes()
    assert data[:4] == b'DDS ' and data[84:88] == b'DX10'
    dds[path.name] = dict(magic='DDS ', width=struct.unpack_from('<I', data, 16)[0], height=struct.unpack_from('<I', data, 12)[0],
        mipmaps=struct.unpack_from('<I', data, 28)[0], fourcc='DX10', dxgiFormat=struct.unpack_from('<I', data, 128)[0],
        resourceDimension=struct.unpack_from('<I', data, 132)[0], miscFlags2=struct.unpack_from('<I', data, 144)[0])
result = dict(date='2026-10-27', scope='read-only GIMI source pack; no original game or injector execution', source=str(SOURCE),
    files={p.name: dict(bytes=p.stat().st_size, sha256=hashlib.sha256(p.read_bytes()).hexdigest()) for p in sorted(SOURCE.iterdir()) if p.is_file()},
    vertexCount=count, strideSizes=dict(position=40, blend=32, texcoord=12),
    byteRemainders=dict(position=0, blend=0, texcoord=0), streamCounts=dict(position=count, blend=len(weights), texcoord=len(uvs)),
    bbox=[[min(p[a] for p in positions) for a in range(3)], [max(p[a] for p in positions) for a in range(3)]],
    positionsFinite=all(math.isfinite(v) for p in positions for v in p), uvFinite=all(math.isfinite(v) for uv in uvs for v in uv),
    uvRange=[[min(uv[a] for uv in uvs) for a in range(2)], [max(uv[a] for uv in uvs) for a in range(2)]],
    normalLengthRange=[min(math.sqrt(sum(v*v for v in p)) for p in normals), max(math.sqrt(sum(v*v for v in p)) for p in normals)],
    tangentLengthRange=[min(math.sqrt(sum(v*v for v in p[:3])) for p in tangents), max(math.sqrt(sum(v*v for v in p[:3])) for p in tangents)],
    tangentW=dict(Counter(round(p[3], 5) for p in tangents)),
    weightSumErrorMax=max(abs(sum(ws)-1) for ws in weights), negativeWeights=sum(w < 0 for ws in weights for w in ws),
    activeSourceBones=dict(sorted(active.items())),
    vertexColorRanges=[[min(c[a] for c in colors) for a in range(4)], [max(c[a] for c in colors) for a in range(4)]],
    parts=parts, dds=dds, missingRig=not any(p.suffix.lower() in ['.blend', '.fbx', '.gltf', '.glb', '.pmx', '.bnc'] for p in SOURCE.iterdir()))
OUTPUT.write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n')
print(json.dumps(dict(vertexCount=count, triangles=sum(p['triangles'] for p in parts.values()), sourceRigMissing=result['missingRig'])))
