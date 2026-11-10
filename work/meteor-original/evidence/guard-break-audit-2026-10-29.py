"""Read original PE bytes and Bison debug tables; never execute Meteor.exe."""
from pathlib import Path
import hashlib
import json
import struct

ROOT = Path(__file__).resolve().parents[3]
EVIDENCE = Path(__file__).resolve().parent
SAMPLE = Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_/Meteor.exe')
data = SAMPLE.read_bytes()
pe = struct.unpack_from('<I', data, 60)[0]
optional = pe + 24
base = struct.unpack_from('<I', data, optional + 28)[0]
section_table = optional + struct.unpack_from('<H', data, pe + 20)[0]

def read(address, size):
    for index in range(struct.unpack_from('<H', data, pe + 6)[0]):
        virtual_size, rva, raw_size, raw = struct.unpack_from('<IIII', data, section_table + index * 40 + 8)
        if rva <= address - base < rva + max(virtual_size, raw_size):
            offset = raw + address - base - rva
            return data[offset:offset + size]
    raise ValueError(hex(address))

def u32(address):
    return struct.unpack('<I', read(address, 4))[0]

def i16(address):
    return struct.unpack('<h', read(address, 2))[0]

def symbol_name(symbol):
    return read(u32(0x005aee80 + symbol * 4), 96).split(b'\0')[0].decode('ascii')

def rule(number):
    offset = i16(0x005ae9b0 + number * 2)
    result = []
    while (symbol := i16(0x005aeab8 + offset * 2)) > 0:
        result.append(symbol_name(symbol))
        offset += 1
    return {'rule': number, 'rhs': result, 'lhs': symbol_name(i16(0x005af030 + number * 2))}

attack_rule = rule(0x30)
assert attack_rule == {'rule': 0x30, 'rhs': ['KEY_attacktype', 'KEY_number'], 'lhs': 'attacktype'}
assert u32(0x005d1974) == 0x107
assert read(0x005d1978, 11) == b'attacktype\0'
# Exact fixed-width x86 MOV/relative-CALL sequence at source attack-block init.
assert read(0x0057b73a, 1) == b'\xb9'
assert u32(0x0057b73b) == 0x0072b920
assert read(0x0057b73f, 1) == b'\xe8'
assert 0x0057b744 + struct.unpack('<i', read(0x0057b740, 4))[0] == 0x00574c90
assert read(0x0057b58b, 5) == b'\xa3\x50\xb9\x72\x00'
assert 0x0072b950 - 0x0072b920 == 0x30

def artifact(path):
    content = path.read_bytes()
    return {'path': str(path.relative_to(ROOT)), 'bytes': len(content), 'sha256': hashlib.sha256(content).hexdigest()}

files = [path for path in sorted((EVIDENCE / 'guard-break-native-2026-10-29').rglob('*')) if path.is_file()]
files += [EVIDENCE / 'decompiled/0057aaf0_FUN_0057aaf0.c', EVIDENCE / 'decompiled/00574c90_FUN_00574c90.c', EVIDENCE / 'decompiled/005754d0_FUN_005754d0.c', EVIDENCE / 'native-guard-break-2026-10-29.tap', ROOT / 'tests/native-guard-break.test.mjs']
result = {
    'id': 'E-guard-break-2026-10-29', 'date': '2026-10-29',
    'scope': 'work/meteor-original/scope.md; granted offline static analysis and local Web port',
    'sampleSha256': hashlib.sha256(data).hexdigest(),
    'method': 'Original PE byte and Bison debug grammar reads; existing/new Ghidra readOnly/noanalysis exports; source EXE never executed.',
    'keyword': {'token': 0x107, 'tokenAddress': '005d1974', 'nameAddress': '005d1978', 'name': 'attacktype'},
    'grammar': {**attack_rule, 'rhsIndexTable': '005ae9b0', 'rhsTable': '005aeab8', 'symbolNameTable': '005aee80', 'lhsTable': '005af030'},
    'parseAssignment': {'parser': '0057aaf0', 'semanticCase': '0x30', 'scratchAddress': '0072b950', 'writeInstruction': '0057b58b', 'writeBytes': read(0x0057b58b, 5).hex(), 'source': 'KEY_number -> __ftol -> MOV [0072b950],EAX'},
    'attackRecord': {'scratchBase': '0072b920', 'initMovAddress': '0057b73a', 'initCall': '0057b73f -> 00574c90', 'offsetOfAttackType': 0x30, 'initBytes': read(0x0057b73a, 10).hex(), 'append': '005754d0 copies the 0x68-byte attack record'},
    'packet': {'builder': '004f3380', 'load': '004f3548 MOV EDX,[ESI+0x30]', 'shift': '004f3555 SHL EDX,0xa', 'consumer': '004af630', 'decode': '(word1 >> 10) & 0x3f'},
    'guardCondition': {'consumerBranch': '004af78a TEST decodedType; 004af794 JNZ 004af881; 004af79a CMP victim+0x20c,1', 'condition': 'decodedAttackType == 0 && victim.guardFlag == 1', 'otherwise': 'normal source HP damage path at 004af881', 'web': 'guarded = !!target.guard && ((attack.attacktype ?? 0) & 0x3f) === 0'},
    'tests': {'command': 'node --test tests/native-guard-break.test.mjs', 'pass': 7, 'fail': 0, 'sourcePoseDamage': {'blade298': 89, 'blade300': 50, 'spear286EachWindow': 37, 'spear291': 122}, 'targetDefense': 15, 'typeZeroBlade295': {'guardedDamage': 0, 'guardRage': 1, 'unguardedDamage': 44}},
    'boundaries': ['No recovered hit-reaction displacement or knockback implementation is claimed.', 'The Web guard boolean remains a host state; original complete guard angles, animation/state transitions and multiplayer events are not implemented by this change.', 'A bypass hit selects ordinary impact audio and reports guardBypassed but does not invent a persistent target.guard state change.'],
    'artifacts': [artifact(path) for path in files]
}
(EVIDENCE / 'E-guard-break-2026-10-29.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf8')
print(json.dumps({'grammar': attack_rule, 'attackTypeOffset': 0x30, 'condition': result['guardCondition']['web'], 'tests': result['tests'], 'artifacts': len(files)}))
