"""Extract the original NPC command tables from a verified static export.

The constrained parser reads only scalar/stack assignments and fixed copy
loops from Ghidra's004ff200 export. It never executes the target or its C.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re
import struct

ROOT = Path(__file__).resolve().parents[1]
SAMPLE_SHA256 = '289afb0aa44a47921d167fc24d6d404c60d6d00c299ac27d45fc61e16231b498'
EXPORT_SHA256 = '2a35007f47a7526af459298366e565559af6536f7ea002d0dda3d3ea668f154c'
FAMILIES = ['sword', 'dagger', 'musket', 'dart', 'hammer', 'blade', 'wheel', 'spear', 'dual', 'qiankun', 'knuckle', 'ninja']


def extract(sample, export):
    data = sample.read_bytes()
    if hashlib.sha256(data).hexdigest() != SAMPLE_SHA256:
        raise ValueError('NPC tables require the verified original Meteor.exe sample')
    if hashlib.sha256(export.read_bytes()).hexdigest() != EXPORT_SHA256:
        raise ValueError('NPC tables require the verified004ff200 static export')
    source = export.read_text()
    # Both operand orders denote the same fixed target vector in this export.
    source = re.sub(r'\(DAT_([0-9a-f]{8}) \+ iVar3\)', r'(iVar3 + DAT_\1)', source)
    stack, vectors, events = {}, {}, []
    patterns = {
        'stack': r'(local_[0-9a-f]+)\[(0x[0-9a-f]+|\d+)\] = (?:\(undefined \*\*\))?&(?:DAT_|PTR_DAT_)([0-9a-f]{8});',
        'direct': r'\*DAT_([0-9a-f]{8}) = &(?:DAT_|PTR_DAT_)([0-9a-f]{8});',
        'copy': r'\*\(undefined4 \*\)\(iVar3 \+ DAT_([0-9a-f]{8})\) = \*\(undefined4 \*\)\(\(int\)(local_[0-9a-f]+) \+ iVar3(?: \+ (0x[0-9a-f]+|\d+))?\);[\s\S]*?while \(iVar3 < (0x[0-9a-f]+|\d+)\);'
    }
    for kind, pattern in patterns.items():
        events.extend((m.start(), kind, m) for m in re.finditer(pattern, source))
    for _, kind, match in sorted(events):
        if kind == 'stack':
            stack[-int(match[1].split('_')[1], 16) + int(match[2], 0) * 4] = int(match[3], 16)
        elif kind == 'direct':
            vectors[int(match[1], 16)] = [int(match[2], 16)]
        else:
            start = -int(match[2].split('_')[1], 16) + int(match[3] or '0', 0)
            vectors[int(match[1], 16)] = [stack[start + i] for i in range(0, int(match[4], 0), 4)]
    if len(vectors) != 36:
        raise ValueError(f'Expected all36 original command vectors, got{len(vectors)}')
    scalars = {int(address, 16): int(value, 0) for address, value in
               re.findall(r'_DAT_([0-9a-f]{8}) = (0x[0-9a-f]+|\d+);', source)}

    def string(va):
        offset = va - 0x400000  # This sample's data RVA and file offset agree.
        end = data.find(b'\0', offset)
        value = data[offset:end].decode('ascii')
        if not re.fullmatch('[fblr]*', value):
            raise ValueError(f'Unexpected original NPC command at{va:08x}')
        return value

    def scalar(va):
        bits = scalars[va]
        return struct.unpack('<f', struct.pack('<I', bits))[0]

    profiles = {}
    for index, weapon in enumerate(FAMILIES):
        base = 0x666a00 + index * 0x38
        groups = [vectors[base + 0x10 + group * 12] for group in range(3)]
        profiles[weapon] = {'index': index, 'tableAddress': f'{base:08x}',
                            'minimumDistance': scalar(base), 'maximumDistance': scalar(base + 4),
                            'eyeHeight': scalar(base + 8), 'angleTolerance': scalar(base + 12),
                            'ranged': bool(scalars[base + 0x34]),
                            'commands': [[string(va) for va in group] for group in groups],
                            'commandAddresses': [[f'{va:08x}' for va in group] for group in groups]}
    air = [struct.unpack_from('<I', data, 0x5ca240 - 0x400000 + i * 4)[0] for i in range(17)]
    return {'version': 1, 'source': {'sampleSha256': SAMPLE_SHA256, 'initializerAddress': '004ff200',
            'initializerBytes': 5028, 'initializerSha256': hashlib.sha256(data[0xff200:0xff200 + 5028]).hexdigest(),
            'decompileSha256': hashlib.sha256(export.read_bytes()).hexdigest(),
            'method': 'Constrained static initializer extraction plus original PE string bytes; target not executed.'},
            'profiles': profiles, 'airCommands': [string(va) for va in air],
            'airCommandAddresses': [f'{va:08x}' for va in air]}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--sample', type=Path, default=Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_/Meteor.exe'))
    parser.add_argument('--export', type=Path, default=ROOT / 'work/native-ai-combat-2026-11-08/command-tables/004ff200_FUN_004ff200.c')
    parser.add_argument('--output', type=Path, default=ROOT / 'dist/assets/original/npc-ai/manifest.json')
    args = parser.parse_args()
    result = extract(args.sample, args.export)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, ensure_ascii=False, separators=(',', ':')) + '\n')
    print(json.dumps({'profiles': len(result['profiles']), 'commandVectors': 36,
                      'commands': sum(len(group) for row in result['profiles'].values() for group in row['commands']),
                      'airCommands': len(result['airCommands']), 'sha256': hashlib.sha256(args.output.read_bytes()).hexdigest()}))


if __name__ == '__main__':
    main()
