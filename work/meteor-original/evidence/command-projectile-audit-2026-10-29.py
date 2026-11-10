"""Read-only inventory of source PonEF node headers; no animation-channel decoder."""
from pathlib import Path
import hashlib
import json
import re
import struct

ROOT = Path(__file__).resolve().parents[3]
EVIDENCE = Path(__file__).resolve().parent
SAMPLE = Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_/Meteor.exe')
TYPES = ['AUDIO', 'BOX', 'BILLBOARD', 'CYLINDER', 'DRAG', 'DONUT', 'MODEL', 'PARTICLE', 'PATH', 'PLANE', 'SPHERE', 'TRAPE']

def artifact(path):
    data = path.read_bytes()
    return {'path': str(path.relative_to(ROOT)), 'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}

def inventory(pose_id):
    path = ROOT / f'dist/assets/original/sounds/definitions/pos{pose_id}.ef'
    data = path.read_bytes()
    assert data[:11] == b'PonEF V1.00'
    nodes = []
    for node_type in TYPES:
        marker = node_type.encode().ljust(16, b'\0')
        cursor = 0
        while (offset := data.find(marker, cursor)) >= 0:
            cursor = offset + 1
            name_length = struct.unpack_from('<I', data, offset + 16)[0]
            assert name_length <= 128
            name = data[offset + 20:offset + 20 + name_length].decode('ascii')
            field = offset + 20 + name_length
            raw_fields = struct.unpack_from('<4I', data, field)
            field += 16
            bindings = []
            for _ in range(2):
                length = struct.unpack_from('<I', data, field)[0]
                assert length <= 128
                field += 4
                bindings.append(data[field:field + length].decode('ascii'))
                field += length
            nodes.append({'offset': offset, 'type': node_type, 'name': name, 'rawCommonWords': list(raw_fields), 'bindingStrings': bindings, 'channelDataOffset': field})
    nodes.sort(key=lambda node: node['offset'])
    declared = struct.unpack_from('<I', data, 11)[0]
    assert len(nodes) == declared
    return {**artifact(path), 'poseId': pose_id, 'declaredNodeCount': declared, 'nodes': nodes,
            'sounds': sorted(set(m.decode('ascii') for m in re.findall(rb'[A-Za-z0-9_]+\.[wW][aA][vV]', data)))}

sample = SAMPLE.read_bytes()
pe = struct.unpack_from('<I', sample, 60)[0]
section_count = struct.unpack_from('<H', sample, pe + 6)[0]
optional = pe + 24
base = struct.unpack_from('<I', sample, optional + 28)[0]
sections = optional + struct.unpack_from('<H', sample, pe + 20)[0]
registry_address = 0x005d2f88
registry = []
for index in range(section_count):
    virtual_size, address, raw_size, raw = struct.unpack_from('<IIII', sample, sections + index * 40 + 8)
    if address <= registry_address - base < address + max(virtual_size, raw_size):
        offset = raw + registry_address - base - address
        for slot in range(12):
            row = sample[offset + slot * 20:offset + (slot + 1) * 20]
            registry.append({'address': f'{registry_address + slot * 20:08x}', 'typeId': struct.unpack_from('<I', row)[0], 'typeName': row[4:].split(b'\0')[0].decode('ascii')})
assert len(registry) == 12

effects = [inventory(pose_id) for pose_id in [200, 202, 209, 210, 201, 551, 203, 204, 259]]
output = {
    'id': 'E-command-projectiles-2026-10-29', 'date': '2026-10-29',
    'scope': 'work/meteor-original/scope.md; granted offline static sample and local Web port',
    'sampleSha256': hashlib.sha256(sample).hexdigest(),
    'method': 'Preserved PonEF bytes and local original x86 PE reads; Ghidra readOnly/noanalysis; original Meteor.exe never executed.',
    'typeRegistry': registry, 'effects': effects,
    'runtime': {'addedPoses': [209, 210], 'existingPoses': [200, 202],
                'releaseWindows': {'209': [3550, 3553], '210': [3593, 3596]},
                'weaponAttack': 75, 'poseModifierPercent': 50, 'versusDefense15Damage': 23,
                'singleReleasePerPosWindow': 'Web adapter following source projectile-only gesture and attack interval, not an EXE emitter-count recovery',
                'flight': 'Existing explicit Web adapter: speed50, radius0.12, lifetime3, gravity0, spin28; unverified native constants'},
    'pending': [
        {'poses': [201], 'input': 'ground down-up attack', 'reason': '12 original Attack spheres have separate PLANE bindings; channel transforms, timing, collision identity and full effect playback remain unported.'},
        {'poses': [551], 'input': 'air down-up attack', 'reason': '12 original Attack spheres have separate PLANE bindings; not a verified eight-dart emission pattern.'},
        {'poses': [203, 204, 205], 'input': 'ground down-up-up attack', 'reason': 'Original AttackBall and seven AttackWave CYLINDER nodes (including duplicate AttackWave06 names) require native bound volumes and channel evaluation.'},
        {'poses': [259, 349], 'weapon': 'dagger', 'input': 'ground down-up-up attack', 'reason': 'POS259 attacks only effect at frames9551-9553; linked349 has no attack. Pos259.ef has17 nodes, one AttackBox BOX bound to d_base. Its timed dimensions and full channel-to-world transform are unported; no body-bone or guessed-radius replacement is used.'},
        {'poses': [209, 210], 'reason': 'RES parameter16 references item10/item11 on-hit effects; their temporal propagation is outside this single-flight/damage increment.'}
    ],
    'functions': [
        {'address': '0058a700', 'finding': 'Type-name lookup in 12-row 005d2f88 registry; does not describe attack emission counts or flight vectors.'},
        {'address': '0056e490', 'finding': 'PonEF V1.00 header, node count, typed constructors and virtual node reader.'},
        {'address': '00582d50', 'finding': 'Common length-prefixed name, four common words, two binding strings, channel data and per-node animation-channel list.'},
        {'address': '0058a620', 'finding': 'Length-prefixed source string reader, not null-padded fixed string.'},
        {'address': '00582b50', 'finding': 'Per-node animation-channel count and virtual channel readers; no simple fixed dart-fan emitter established.'},
        {'address': '00589640', 'finding': 'PLANE reader calls common reader then two float-width values; not a projectile emitter.'},
        {'address': '005892b0', 'finding': 'SPHERE/CYLINDER reader calls common reader then five numeric fields; shape fields alone do not establish attack trajectory.'}
    ],
    'artifacts': [artifact(path) for path in sorted((EVIDENCE / 'command-projectile-native-2026-10-29').rglob('*')) if path.is_file()] + [artifact(EVIDENCE / 'native-command-projectiles-2026-10-29.tap')],
    'tests': {'command': 'node --test tests/native-command-projectiles.test.mjs', 'pass': 6, 'fail': 0}
}
(EVIDENCE / 'E-command-projectiles-2026-10-29.json').write_text(json.dumps(output, ensure_ascii=False, indent=2) + '\n', encoding='utf8')
print(json.dumps({'effects': len(effects), 'nodeCounts': {effect['poseId']: effect['declaredNodeCount'] for effect in effects}, 'artifacts': len(output['artifacts']), 'tests': output['tests']}))
