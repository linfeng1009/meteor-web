0055a180 PUSH ESI
0055a181 MOV ESI,ECX
0055a183 MOV ECX,dword ptr [ESP + 0x8]
0055a187 TEST ECX,ECX
0055a189 MOV dword ptr [ESI + 0x1678],ECX
0055a18f JZ 0x0055a274
0055a195 FLD float ptr [ECX + 0x1f8]
0055a19b FCOMP float ptr [ECX + 0x1fc]
0055a1a1 FNSTSW AX
0055a1a3 AND EAX,0x4100
0055a1a8 JNZ 0x0055a1ca
0055a1aa MOV EAX,dword ptr [ESI + 0x38]
0055a1ad FLD float ptr [ESI + 0x3c]
0055a1b0 MOV dword ptr [ESI + 0xaa8],EAX
0055a1b6 FDIV float ptr [ECX + 0x1f8]
0055a1bc FMUL float ptr [ECX + 0x1fc]
0055a1c2 FSTP float ptr [ESI + 0xaac]
0055a1c8 JMP 0x0055a1e8
0055a1ca FLD float ptr [ESI + 0x38]
0055a1cd FDIV float ptr [ECX + 0x1fc]
0055a1d3 FMUL float ptr [ECX + 0x1f8]
0055a1d9 MOV ECX,dword ptr [ESI + 0x3c]
0055a1dc MOV dword ptr [ESI + 0xaac],ECX
0055a1e2 FSTP float ptr [ESI + 0xaa8]
0055a1e8 MOV EDX,dword ptr [ESI + 0xaac]
0055a1ee MOV EAX,dword ptr [ESI + 0xaa8]
0055a1f4 PUSH EDI
0055a1f5 LEA EDI,[ESI + 0x410]
0055a1fb PUSH EDX
0055a1fc PUSH EAX
0055a1fd MOV ECX,EDI
0055a1ff CALL 0x0047c3a0
0055a204 PUSH 0x3f000000
0055a209 PUSH 0x3e4ccccd
0055a20e PUSH 0x3e4ccccd
0055a213 PUSH 0x3e4ccccd
0055a218 MOV ECX,EDI
0055a21a CALL 0x0047dd50
0055a21f MOV EAX,dword ptr [ESI + 0x1678]
0055a225 POP EDI
0055a226 FLD float ptr [ESI + 0xaa8]
0055a22c FDIV float ptr [EAX + 0x1f8]
0055a232 FSTP float ptr [ESI + 0xab0]
0055a238 FLD float ptr [ESI + 0xaac]
0055a23e FDIV float ptr [EAX + 0x1fc]
0055a244 FSTP float ptr [ESI + 0xab4]
0055a24a FLD float ptr [ESI + 0x40]
0055a24d FSUB float ptr [0x005a8b80]
0055a253 FSUB float ptr [ESI + 0xaa8]
0055a259 FSTP float ptr [ESI + 0xaa0]
0055a25f FLD float ptr [ESI + 0x44]
0055a262 FSUB float ptr [0x005a8b80]
0055a268 FSUB float ptr [ESI + 0xaac]
0055a26e FSTP float ptr [ESI + 0xaa4]
0055a274 POP ESI
0055a275 RET 0x4
