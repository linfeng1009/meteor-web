#!/usr/bin/env python3
"""Read-only PE32 survey; does not load or execute the target."""
import argparse
import hashlib
import json
import re
import struct
from pathlib import Path

ap=argparse.ArgumentParser()
ap.add_argument('sample',type=Path)
ap.add_argument('--output',type=Path,required=True)
args=ap.parse_args()
b=args.sample.read_bytes()
if b[:2]!=b'MZ':raise ValueError('Expected PE image')
pe=struct.unpack_from('<I',b,60)[0]
if b[pe:pe+4]!=b'PE\0\0':raise ValueError('Invalid PE signature')
machine,nsec,timestamp,_,_,optsz,flags=struct.unpack_from('<HHIIIHH',b,pe+4)
opt=pe+24
if struct.unpack_from('<H',b,opt)[0]!=0x10b:raise ValueError('Expected PE32 optional header')
base=struct.unpack_from('<I',b,opt+28)[0]
entry=struct.unpack_from('<I',b,opt+16)[0]
sections=[]
for i in range(nsec):
    o=opt+optsz+i*40
    vs,va,rs,raw=struct.unpack_from('<IIII',b,o+8)
    sections.append(dict(name=b[o:o+8].split(b'\0')[0].decode(),va=va,size=vs,raw=raw,rawsize=rs))
def offset(rva):
    for s in sections:
        if s['va']<=rva<s['va']+max(s['size'],s['rawsize']):return s['raw']+rva-s['va']
    return rva
def address(o):
    for s in sections:
        if s['raw']<=o<s['raw']+s['rawsize']:return base+s['va']+o-s['raw']
    return None
def cstr(o):return b[o:b.index(b'\0',o)].decode('ascii',errors='replace')
imports=[]
import_rva=struct.unpack_from('<I',b,opt+104)[0]
for i in range(200):
    orig,stamp,fwd,name,thunk=struct.unpack_from('<IIIII',b,offset(import_rva)+i*20)
    if not any([orig,stamp,fwd,name,thunk]):break
    functions=[]
    for j in range(10000):
        v=struct.unpack_from('<I',b,offset(orig or thunk)+j*4)[0]
        if v==0:break
        functions.append(dict(name=('ordinal:'+str(v&65535)) if v&0x80000000 else cstr(offset(v)+2),iat=hex(base+thunk+j*4)))
    imports.append(dict(dll=cstr(offset(name)),functions=functions))
strings=[]
for match in re.finditer(rb'[\x20-\x7e]{4,}',b):
    text=match.group().decode()
    if re.search(r'skc|bnc|amb|targetmove|targetvalue|defensemove|nextpose|pose|character\.act|attackvalue|key_attack|frameweight|framebuffer|\.gmb|\.gmc|\.pst',text,re.I):
        strings.append(dict(address=hex(address(match.start()) or match.start()),offset=match.start(),text=text))
data=dict(sample=str(args.sample.resolve()),sha256=hashlib.sha256(b).hexdigest(),size=len(b),machine=hex(machine),imageBase=hex(base),entryPoint=hex(base+entry),sections=sections,imports=imports,formatStrings=strings)
args.output.parent.mkdir(parents=True,exist_ok=True)
args.output.write_text(json.dumps(data,ensure_ascii=False,indent=2))
print(json.dumps(dict(sha256=data['sha256'],architecture='x86 PE32',entryPoint=data['entryPoint'],importLibraries=len(imports),formatStrings=len(strings),output=str(args.output)),ensure_ascii=False))
