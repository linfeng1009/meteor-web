"""Offline source audit: PE tables/bytes and read-only Ghidra exports, no native execution."""
from pathlib import Path
import hashlib
import json
import re
import struct
import subprocess
from fractions import Fraction

ROOT = Path(__file__).resolve().parents[3]
EVIDENCE = Path(__file__).resolve().parent
sample = Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_/Meteor.exe').read_bytes()
sample_hash = hashlib.sha256(sample).hexdigest()
assert sample_hash == '289afb0aa44a47921d167fc24d6d404c60d6d00c299ac27d45fc61e16231b498'
pe = struct.unpack_from('<I', sample, 60)[0]
optional = pe + 24
base = struct.unpack_from('<I', sample, optional + 28)[0]
sections = optional + struct.unpack_from('<H', sample, pe + 20)[0]


def read(va, size):
    for n in range(struct.unpack_from('<H', sample, pe + 6)[0]):
        _, rva, raw_size, raw = struct.unpack_from('<IIII', sample, sections + n * 40 + 8)
        if rva <= va - base and va - base + size <= rva + raw_size:
            return sample[raw + va - base - rva:raw + va - base - rva + size]
    raise ValueError(hex(va))


def u32(va):
    return struct.unpack('<I', read(va, 4))[0]


def i16(va):
    return struct.unpack('<h', read(va, 2))[0]


def name(symbol):
    return read(u32(0x005aee80 + symbol * 4), 96).split(b'\0')[0].decode('ascii')


grammar = []
for rule, field in enumerate(['targetpose', 'targetposefront', 'targetposeback', 'targetposeleft', 'targetposeright'], 0x39):
    offset = i16(0x005ae9b0 + rule * 2)
    rhs = [name(i16(0x005aeab8 + (offset + n) * 2)) for n in range(2)]
    assert rhs == ['KEY_' + field, 'KEY_number']
    grammar.append({'rule': rule, 'field': field, 'recordOffset': hex(0x48 + (rule - 0x39) * 4), 'rhs': rhs})

angles = {f'{va:08x}': struct.unpack('<d', read(va, 8))[0] for va in [0x005ab620, 0x005ab628, 0x005ab630, 0x005ab638]}
assert angles == {'005ab620': -2.3561924999999997, '005ab628': -.7853975, '005ab630': 2.3561924999999997, '005ab638': .7853975}
assert struct.unpack('<f', read(0x005a8430, 4))[0] == -1
guard_random_scale = struct.unpack('<d', read(0x005aaaf8, 8))[0]
assert read(0x005aaaf8, 8).hex() == '800040002000203f'
assert guard_random_scale == 4 / 32767
assert read(0x0050a8e6, 12).hex() == '69c9fd43030081c1c39e2600'
assert read(0x0050a8f7, 8).hex() == 'c1e81025ff7f0000'
assert read(0x0050f131, 10).hex() == '68000003006800000100'
assert read(0x004dd092, 6).hex() == 'c7000ad7233c'
assert read(0x004cfc18, 8).hex() == 'c74424088fc2f53d'
assert u32(0x005aa970 + 4) == 0x004dc060


def rounded_significand(value, bits):
    if not value:
        return value
    exponent = value.numerator.bit_length() - value.denominator.bit_length()
    power = Fraction(2) ** exponent
    if value < power:
        exponent -= 1
    step = Fraction(2) ** (exponent - bits + 1)
    scaled = value / step
    integer, remainder = divmod(scaled.numerator, scaled.denominator)
    if remainder * 2 > scaled.denominator or remainder * 2 == scaled.denominator and integer & 1:
        integer += 1
    return integer * step


# The EXE's CRT initializer calls controlfp(0x10000,0x30000); its converter
# maps that to hardware CW precision bits0x200 (53-bit). Pure64-bit extended
# precision gives a different endpoint and must not be assumed from x87 alone.
front_counts = {}
for bits in [24, 53, 64]:
    counts = [0] * 5
    for draw in range(32768):
        product = rounded_significand(Fraction.from_float(guard_random_scale) * draw, bits)
        counts[product.numerator // product.denominator] += 1
    front_counts[str(bits)] = counts
assert front_counts['24'] == front_counts['53'] == [8192, 8192, 8192, 8191, 1]
assert front_counts['64'] == [8192, 8192, 8192, 8192, 0]

bindings = {'sword': ('004dd370', 16), 'spear': ('004ddac0', 17), 'blade': ('004de220', 18),
            'dart': ('004df190', 11), 'hammer': ('004e0080', 19), 'dagger': ('004e07c0', 15), 'dual': ('004e0ed0', 14)}
profiles = {}
for weapon, (function, guard) in bindings.items():
    path = EVIDENCE / f'guard-selector-state-init-2026-11-06/{function}_FUN_{function}.c'
    text = path.read_text()
    stance = re.search(r'\*\(undefined4 \*\)\(param_1 \+ 0x18\) = (0x[0-9a-f]+|[0-9]+);', text)
    assert int(stance[1], 0) == guard
    prefix = text.split('puStack_28 = *(undefined1 **)(param_1 + 0x2c)')[0]
    poses = [int(value, 16) for value in re.findall(r'local_10 = \(undefined1 \*\)(0x[0-9a-f]+);', prefix)]
    assert len(poses) == 7
    profiles[weapon] = {'initializer': function, 'guardStance': guard, 'poses': poses}

runtime_profiles = json.loads(subprocess.check_output(['node', '--input-type=module', '-e',
    "import{NATIVE_GUARD_REACTIONS}from'./dist/native-combat.js';console.log(JSON.stringify(NATIVE_GUARD_REACTIONS))"], cwd=ROOT, text=True))
assert {weapon: runtime_profiles[weapon] for weapon in profiles} == {weapon: profile['poses'] for weapon, profile in profiles.items()}

folders = ['directional-guard-native-2026-11-06', 'directional-guard-state-native-2026-11-06',
           'actor-state-factories-2026-11-06', 'actor-state-constructors-2026-11-06',
           'actor-world-getter-2026-11-06', 'guard-blend-callback-native-2026-11-06', 'guard-selector-state-init-2026-11-06',
           'fpu-policy-native-2026-11-06', 'd3d-init-native-2026-11-06', 'fpu-d3d-caller-native-2026-11-06',
           'fpu-device-creation-native-2026-11-06']
files = [path for folder in folders for path in sorted((EVIDENCE / folder).glob('*')) if path.is_file()]
files += [EVIDENCE / 'decompiled/005754d0_FUN_005754d0.c',
          EVIDENCE / 'combat-motion-bridge-2026-11-06/004cfc00_FUN_004cfc00.asm',
          EVIDENCE / 'combat-scene-delta-native-2026-11-06/004db920_FUN_004db920.c',
          EVIDENCE / 'guard-crt-rand-2026-11-06.asm', ROOT / 'scripts/analysis/ReadOnlyFpuPolicy.java', Path(__file__).resolve()]


def artifact(path):
    content = path.read_bytes()
    return {'path': str(path.relative_to(ROOT)), 'bytes': len(content), 'sha256': hashlib.sha256(content).hexdigest()}


result = {
    'id': 'E-directional-guard-source-2026-11-06', 'observedAt': '2026-11-06',
    'sampleSha256': sample_hash, 'originalExecuted': False, 'originalModified': False,
    'scope': 'work/meteor-original/scope.md', 'method': 'PE section-mapped bytes/tables, readOnly/noanalysis Ghidra, runtime profile comparison; no original executable launched.',
    'grammar': grammar, 'angleThresholds': angles,
    'direction': {'producer': '004f3380 ->00548270', 'facingGetter': '004dc060: minus native row1 of actor matrix',
        'webAxes': 'native(x,y)=(Web x,-Web z); use target yaw and vector from target to attacker',
        'sectors': ['0:front, -low<angle<low, TargetPoseFront', '1:negative side, -high<angle<=-low, TargetPoseRight',
                    '2:positive side, low<=angle<high, TargetPoseLeft', '3:back, angle<=-high or angle>=high, TargetPoseBack'],
        'fallback': '005754d0 copies TargetPose to directional fields left unset(-1)'},
    'guard': {'server': '004af630: AttackType0 and held-guard flag; direction does not create a damage cone',
        'clientPath': '004f4010 ->004d04d0 ->weapon-state+1c/004dcf10 ->state+68/004dce50 ->004d03f0',
        'selector': 'front trunc(CRT15-bit rand*(4/32767)); directions1/2/3 use list4/5/6', 'profiles': profiles,
        'randomScale': guard_random_scale, 'randomScaleBytes': read(0x005aaaf8, 8).hex(),
        'crtRandom': {'function': '0050a8de', 'update': 'state=state*214013+2531011 modulo2^32; return(state>>16)&32767',
                      'frontSlotCountsOverAllDrawsByPrecision': front_counts},
        'parameters': 'DefenseMove/DefenseValue from high16 message halves, using existing recovered hundredth wire conversion'},
    'forcedBlend': {'entry': '004cfc00 ->state+30/004dd070 ->00559720 ->004dbf80/0055d260',
        'defaultBits': '3df5c28f', 'defaultSeconds': struct.unpack('<f', bytes.fromhex('8fc2f53d'))[0],
        'guardListMemberBits': '3c23d70a', 'guardListMemberSeconds': struct.unpack('<f', bytes.fromhex('0ad7233c'))[0],
        'timer': 'Animation minimum-duration clock advances after its forced blend; source timeline stays at Start during blending'},
    'floatingPointPolicy': {'crtInitializer': '0050f131: controlfp(0x10000,0x30000)',
        'hardwareMapping': '0051283e maps0x10000 precision to CW0x200 (53-bit)',
        'roundingAndTruncation': '00509980 changes only rounding bits for FISTP, then restores CW; preceding FMUL uses the active precision',
        'deviceCreation': '00481fe0 creates D3D8; 00482e30 calls CreateDevice with enumerated behavior flags',
        'inference': 'The normal CRT53-bit path, or Direct3D default24-bit path, both select guard slot4 for draw32767; arbitrary driver/plugin control-word changes are not observed or emulated.',
        'primaryReferences': ['https://learn.microsoft.com/en-us/windows/win32/dxtecharts/top-issues-for-windows-titles',
                              'https://learn.microsoft.com/en-us/previous-versions/ms889264(v=msdn.10)']},
    'boundaries': ['Front guard variant uses Web RNG; original CRT seed/sequence and multiplayer message scheduling are not reproduced.',
        'World yaw, current pose snapshots, gravity, contact and collision remain Web host implementations; full native vector/physics parity is not asserted.',
        'Signed-angle selection uses recovered sectors with Web coordinates and JS arithmetic, not an x87 instruction emulator.',
        'Some common/personal POS versions differ in frame offsets; runtime retains the current character personal POS, without rewriting source files.',
        'Five remaining weapon families, complete EF, exact input scheduling and remaining story missions remain incomplete.'],
    'artifacts': [artifact(path) for path in files]
}
(EVIDENCE / 'E-directional-guard-source-2026-11-06.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n')
print(json.dumps({'id': result['id'], 'profiles': len(profiles), 'artifacts': len(files), 'sampleSha256': sample_hash}))
