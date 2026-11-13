"""Static-only export of original effect bounds. Requires pefile and capstone.
Never loads or executes the target PE. Keep reference clients outside the repo.
"""
from pathlib import Path
import argparse, hashlib, json, struct
import capstone
import pefile

FUNCTIONS = {'plane_constructor': 0x585360, 'plane_bounds': 0x585400,
             'donut_constructor': 0x5880d0, 'donut_bounds': 0x5881a0}


def inspect(path):
    raw = path.read_bytes()
    pe = pefile.PE(data=raw)
    base = pe.OPTIONAL_HEADER.ImageBase
    if base != 0x400000 or struct.unpack('<f', pe.get_data(0x5a83e8-base, 4))[0] != .5:
        raise ValueError('Unsupported reference layout')
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    functions = {}
    for name, address in FUNCTIONS.items():
        instructions = []
        for instruction in decoder.disasm(pe.get_data(address-base, 2048), address):
            instructions.append(instruction)
            if instruction.mnemonic == 'ret':
                break
        if not instructions or instructions[-1].mnemonic != 'ret':
            raise ValueError(f'Incomplete static export: {name}')
        code = b''.join(bytes(i.bytes) for i in instructions)
        functions[name] = {'address': hex(address), 'bytes': len(code),
                           'sha256': hashlib.sha256(code).hexdigest(),
                           'assembly': '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n'}
    return {'sample': path.name, 'sha256': hashlib.sha256(raw).hexdigest(),
            'executed': False, 'functions': functions}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('sample', type=Path)
    parser.add_argument('--compare', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    primary, comparison = inspect(args.sample), inspect(args.compare)
    for name, function in primary['functions'].items():
        if function['sha256'] != comparison['functions'][name]['sha256']:
            raise ValueError(f'Reference variants differ: {name}')
    args.output.mkdir(parents=True, exist_ok=True)
    for name, function in primary['functions'].items():
        (args.output/f'{name}.asm').write_text(function.pop('assembly'), encoding='utf-8')
        comparison['functions'][name].pop('assembly')
    result = {'primary': primary, 'comparison': comparison, 'relevantFunctionsIdentical': True,
              'planeHalf': ['abs(width)/2', 'abs(height)/2', 3],
              'planeBaseOffsetZ': 'flag0==1 ? height/2 : 0',
              'donutHalf': ['abs(outer)', 'abs(outer)', 'abs(outer-inner)/2'],
              'donutBaseOffsetZ': 'flag0==1 ? (outer-inner)/2 : 0',
              'notes': 'Source attack tests use oriented bounds, not visual triangles or the donut hole. Web body shape, interpolation and time sampling remain adapters.'}
    (args.output/'evidence.json').write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    print(json.dumps({'identical': True, 'sampleHashes': [primary['sha256'], comparison['sha256']]}))


if __name__ == '__main__':
    main()
