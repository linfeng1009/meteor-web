00430c70 FLD float ptr [ESP + 0xc]
00430c74 FMUL float ptr [0x005a8434]
00430c7a MOV EAX,dword ptr [ESP + 0x4]
00430c7e FDIVR float ptr [ESP + 0x10]
00430c82 FMUL float ptr [ESP + 0x14]
00430c86 FLD ST0
00430c88 FCHS
00430c8a FLD ST1
00430c8c FDIV float ptr [ESP + 0x8]
00430c90 FST float ptr [ESP + 0x10]
00430c94 FCHS
00430c96 FSTP float ptr [ESP + 0xc]
00430c9a FXCH
00430c9c FSUB ST0,ST1
00430c9e FLD float ptr [ESP + 0x1c]
00430ca2 FADD float ptr [0x005a83f4]
00430ca8 FMUL ST1
00430caa FMUL float ptr [0x005a83e8]
00430cb0 FADD ST0,ST2
00430cb2 FSTP float ptr [ESP + 0x8]
00430cb6 FLD float ptr [ESP + 0x1c]
00430cba FADD float ptr [ESP + 0x24]
00430cbe FADD float ptr [0x005a83f4]
00430cc4 FMUL ST1
00430cc6 FMUL float ptr [0x005a83e8]
00430ccc FADD ST0,ST2
00430cce FXCH ST2
00430cd0 FSTP ST1
00430cd2 FSTP ST0
00430cd4 FLD float ptr [ESP + 0x10]
00430cd8 FSUB float ptr [ESP + 0xc]
00430cdc FLD float ptr [ESP + 0x20]
00430ce0 FADD float ptr [0x005a83f4]
00430ce6 FMUL ST1
00430ce8 FMUL float ptr [0x005a83e8]
00430cee FADD float ptr [ESP + 0xc]
00430cf2 FSTP float ptr [ESP + 0x10]
00430cf6 FLD float ptr [ESP + 0x20]
00430cfa FADD float ptr [ESP + 0x28]
00430cfe FADD float ptr [0x005a83f4]
00430d04 FMULP
00430d06 FMUL float ptr [0x005a83e8]
00430d0c FADD float ptr [ESP + 0xc]
00430d10 FLD ST1
00430d12 FSUB float ptr [ESP + 0x8]
00430d16 FLD ST1
00430d18 FSUB float ptr [ESP + 0x10]
00430d1c FLD float ptr [ESP + 0x14]
00430d20 FSUB float ptr [ESP + 0x18]
00430d24 FSTP float ptr [ESP + 0xc]
00430d28 FLD float ptr [ESP + 0x14]
00430d2c FADD ST0,ST0
00430d2e FSTP float ptr [ESP + 0x1c]
00430d32 FLD float ptr [0x005a83f4]
00430d38 FDIV ST0,ST2
00430d3a FST float ptr [ESP + 0x20]
00430d3e FMUL float ptr [ESP + 0x1c]
00430d42 FSTP float ptr [EAX]
00430d44 FLD float ptr [0x005a83f4]
00430d4a FDIV ST0,ST1
00430d4c FSTP ST2
00430d4e FSTP ST0
00430d50 FLD float ptr [ESP + 0x1c]
00430d54 FMUL ST1
00430d56 FSTP float ptr [EAX + 0x14]
00430d59 FXCH ST2
00430d5b FADD float ptr [ESP + 0x8]
00430d5f FMUL float ptr [ESP + 0x20]
00430d63 FSTP float ptr [EAX + 0x20]
00430d66 FADD float ptr [ESP + 0x10]
00430d6a FMUL ST1
00430d6c XOR ECX,ECX
00430d6e MOV dword ptr [EAX + 0x2c],0xbf800000
00430d75 MOV dword ptr [EAX + 0x3c],ECX
00430d78 MOV dword ptr [EAX + 0x34],ECX
00430d7b MOV dword ptr [EAX + 0x30],ECX
00430d7e MOV dword ptr [EAX + 0x1c],ECX
00430d81 FSTP float ptr [EAX + 0x24]
00430d84 MOV dword ptr [EAX + 0x18],ECX
00430d87 MOV dword ptr [EAX + 0x10],ECX
00430d8a FSTP ST0
00430d8c FLD float ptr [0x005a83f4]
00430d92 FDIV float ptr [ESP + 0xc]
00430d96 MOV dword ptr [EAX + 0xc],ECX
00430d99 MOV dword ptr [EAX + 0x8],ECX
00430d9c MOV dword ptr [EAX + 0x4],ECX
00430d9f FLD float ptr [ESP + 0x18]
00430da3 FMUL ST1
00430da5 FSTP float ptr [EAX + 0x28]
00430da8 FMUL float ptr [ESP + 0x14]
00430dac FMUL float ptr [ESP + 0x18]
00430db0 FSTP float ptr [EAX + 0x38]
00430db3 RET
