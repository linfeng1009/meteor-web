"""Reproduce offline PE/table reads for motion and hit timing; never run Meteor.exe."""
from pathlib import Path
import hashlib
import json
import struct
import subprocess

ROOT = Path(__file__).resolve().parents[3]
EVIDENCE = Path(__file__).resolve().parent
SAMPLE = Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_/Meteor.exe')
data = SAMPLE.read_bytes()
sample_hash = hashlib.sha256(data).hexdigest()
assert sample_hash == '289afb0aa44a47921d167fc24d6d404c60d6d00c299ac27d45fc61e16231b498'
pe = struct.unpack_from('<I', data, 60)[0]
optional = pe + 24
base = struct.unpack_from('<I', data, optional + 28)[0]
section_table = optional + struct.unpack_from('<H', data, pe + 20)[0]


def read(address, size):
    rva = address - base
    for index in range(struct.unpack_from('<H', data, pe + 6)[0]):
        virtual_size, start, raw_size, raw = struct.unpack_from('<IIII', data, section_table + index * 40 + 8)
        if start <= rva and rva + size <= start + raw_size:
            return data[raw + rva - start:raw + rva - start + size]
    raise ValueError(f'VA {address:08x} is not backed by {size} file bytes')


def u32(address):
    return struct.unpack('<I', read(address, 4))[0]


def i16(address):
    return struct.unpack('<h', read(address, 2))[0]


def name(symbol):
    return read(u32(0x005aee80 + symbol * 4), 96).split(b'\0')[0].decode('ascii')


def rule(number):
    offset, rhs = i16(0x005ae9b0 + number * 2), []
    while (symbol := i16(0x005aeab8 + offset * 2)) > 0:
        rhs.append(name(symbol))
        offset += 1
    return {'rule': number, 'lhs': name(i16(0x005af030 + number * 2)), 'rhs': rhs}


specifications = [
    (0x32, 'defensevalue', 0x0072b960, 0x0057b5ae, '891560b97200'),
    (0x33, 'defensemove', 0x0072b95c, 0x0057b5be, '890d5cb97200'),
    (0x36, 'targetspeed', 0x0072b97c, 0x0057b5f6, '89157cb97200'),
    (0x37, 'targetmove', 0x0072b980, 0x0057b606, '890d80b97200'),
    (0x38, 'targetvalue', 0x0072b984, 0x0057b616, 'a384b97200'),
]
grammar = []
for number, field, global_address, instruction, expected_bytes in specifications:
    decoded = rule(number)
    assert decoded['rhs'] == ['KEY_' + field, 'KEY_number']
    assert read(instruction, len(bytes.fromhex(expected_bytes))).hex() == expected_bytes
    grammar.append({**decoded, 'field': field, 'scratchAddress': f'{global_address:08x}',
                    'attackRecordOffset': hex(global_address - 0x0072b920),
                    'assignmentInstruction': f'{instruction:08x}', 'assignmentBytes': expected_bytes})

constants = {
    'packScale': struct.unpack('<d', read(0x005a9800, 8))[0],
    'packRounding': struct.unpack('<d', read(0x005a8460, 8))[0],
    'unpackScale': struct.unpack('<f', read(0x005a8410, 4))[0],
    'verticalIntegerThreshold': struct.unpack('<f', read(0x005a83ec, 4))[0],
}
assert constants['packScale'] == 100 and constants['packRounding'] == .5
assert constants['unpackScale'] == struct.unpack('<f', struct.pack('<f', .01))[0]
assert u32(0x005aa9f8 + 0x20) == 0x0055df00
assert read(0x0055df04, 6).hex() == '81c104030000'

node_audit = r'''
import {readFile} from 'node:fs/promises';
import {parsePos,decodeNativeText} from './dist/native-combat.js';
const poses=parsePos(decodeNativeText(await readFile('dist/assets/native/combat/P0.POS')));
const attacks=[...poses.values()].flatMap(pose=>pose.attacks.map(attack=>({poseId:pose.id,...attack})));
const fields=Object.fromEntries(['targetmove','targetvalue','defensemove','defensevalue'].map(field=>[field,{
  missing:attacks.filter(a=>a[field]==null).map(a=>({poseId:a.poseId,line:a.line})),
  minimum:Math.min(...attacks.map(a=>a[field]).filter(Number.isFinite)),
  negative:attacks.filter(a=>a[field]<0).map(a=>({poseId:a.poseId,line:a.line,value:a[field]}))
}]));
console.log(JSON.stringify({poseCount:poses.size,attackCount:attacks.length,fields,
  examples:[262,277,295,315].map(id=>({poseId:id,attack:poses.get(id).attacks[0]}))}));
'''
source_fields = json.loads(subprocess.check_output(['node', '--input-type=module', '-e', node_audit], cwd=ROOT, text=True))
for field in ['targetmove', 'targetvalue']:
    assert source_fields['fields'][field]['missing'] == []
    assert source_fields['fields'][field]['negative'] == []

paths = [
    'combat-movement-native-2026-11-06/0057aaf0_FUN_0057aaf0.c',
    'combat-movement-native-2026-11-06/0057aaf0_FUN_0057aaf0.asm',
    'guard-break-native-2026-10-29/004f3380_FUN_004f3380.asm',
    'decompiled/004af630_FUN_004af630.c',
    'hit-reaction-state-2026-10-30/004f3f50_FUN_004f3f50.asm',
    'combat-movement-native-2026-11-06/004d03f0_FUN_004d03f0.asm',
    'combat-motion-bridge-2026-11-06/004cfc00_FUN_004cfc00.c',
    'pose-blend-native-2026-11-05/0055d260_FUN_0055d260.c',
    'combat-dummy-motion-native-2026-11-06/0055d560_FUN_0055d560.c',
    'combat-dummy-motion-native-2026-11-06/0055d560_FUN_0055d560.asm',
    'combat-guard-motion-native-2026-11-06/0055d910_FUN_0055d910.asm',
    'hit-reaction-selection-2026-10-30/004cdd60_FUN_004cdd60.c',
    'hit-reaction-getup-2026-10-30/004ce850_FUN_004ce850.asm',
    'combat-dummy-motion-native-2026-11-06/0055df00_FUN_0055df00.asm',
    'combat-motion-frame-native-2026-11-06/0055c310_FUN_0055c310.c',
    'combat-motion-frame-native-2026-11-06/00574c90_FUN_00574c90.c',
    'jump-motion-native-2026-11-05/00557ef0_FUN_00557ef0.c',
    'combat-motion-producer-2026-11-06/005570e0_FUN_005570e0.c',
]


def artifact(path):
    content = path.read_bytes()
    return {'path': str(path.relative_to(ROOT)), 'bytes': len(content), 'sha256': hashlib.sha256(content).hexdigest()}


result = {
    'id': 'E-combat-motion-source-2026-11-06', 'observedAt': '2026-11-06',
    'sampleSha256': sample_hash, 'originalExecuted': False, 'originalModified': False,
    'scope': 'work/meteor-original/scope.md',
    'method': 'Original PE section-mapped byte/table reads, readOnly/noanalysis Ghidra exports, and local Web POS parser. No native execution.',
    'grammarTables': {'rhsIndex': '005ae9b0', 'rhs': '005aeab8', 'symbolNames': '005aee80', 'lhs': '005af030'},
    'grammarAssignments': grammar, 'constants': constants,
    'packet': {'producer': '004f3380', 'server': '004af630', 'client': '004f3f50',
               'moveWord': 'word3: DefenseMove high16, TargetMove low16',
               'valueWord': 'word4: DefenseValue high16, TargetValue low16',
               'pack': 'uint16(trunc(float32(value)*double100+double.5))',
               'unpack': 'float32(unsigned16*float32(.01))'},
    'motion': {'targetMoveStorage': '004d03f0 actor+37c',
               'consumer': '004cdd60 -> 004ce850 reads d_base and character virtual+20 scene vector',
               'vectorVtable': '005aa9f8+20 -> 0055df00; copies character+304/+308/+30c',
               'verticalPolicy': 'integer truncation then absolute comparison >= float0.1 overrides native vertical velocity',
               'web': 'Raw d_base frame differences, native axes rotated by Web actor yaw, through existing collision/hazard host'},
    'time': {'storage': '004cfc00 -> 004dbf80 -> 0055d260 animation+608; elapsed at+604',
             'update': '0055d910/0055d560: looping hit pose minimum duration; zero has no explicit hold',
             'terminal': '0055d560 mode1 finishes at End; mode0 resets to LoopStart after LoopEnd'},
    'sourceAttackFields': source_fields,
    'boundaries': [
        'Full scene-vector production, rotation and native air/collision physics remain unresolved; the narrow immediate scan only found unrelated animation-loader bone fields.',
        'DefenseMove/DefenseValue packet semantics are recovered, but guard animation/recoil are not connected by this change.',
        'Native directional target-pose coordinate selection, exact forced-hit blending and all EF remain incomplete.',
        'The queued continuation survives landing by an explicit Web input-host policy, validated against ACT; exact original input scheduling is not asserted.',
        'All source P0 target Move/Value fields are present and nonnegative. Original generic negative duration sentinels are not implemented for unknown records.',
        'Loop clamp discards excess update time as in the inspected native branch; universal frame-partition equivalence is not asserted.'
    ],
    'artifacts': [artifact(EVIDENCE / path) for path in paths] + [artifact(Path(__file__).resolve())]
}
(EVIDENCE / 'E-combat-motion-source-2026-11-06.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf8')
print(json.dumps({'id': result['id'], 'grammarFields': len(grammar), 'attacks': source_fields['attackCount'], 'artifacts': len(result['artifacts']), 'sampleSha256': sample_hash}))
