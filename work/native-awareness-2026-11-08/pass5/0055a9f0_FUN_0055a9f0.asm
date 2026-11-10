0055a9f0 MOV EAX,dword ptr [ESP + 0x4]
0055a9f4 PUSH ESI
0055a9f5 MOV ESI,ECX
0055a9f7 MOV ECX,dword ptr [ESP + 0xc]
0055a9fb CMP EAX,ECX
0055a9fd PUSH EDI
0055a9fe JLE 0x0055aa06
0055aa00 MOV EAX,ECX
0055aa02 MOV dword ptr [ESP + 0xc],EAX
0055aa06 TEST EAX,EAX
0055aa08 JGE 0x0055aa10
0055aa0a XOR EAX,EAX
0055aa0c MOV dword ptr [ESP + 0xc],EAX
0055aa10 FILD dword ptr [ESP + 0xc]
0055aa14 LEA EDI,[ESI + 0xfd8]
0055aa1a MOV dword ptr [ESI + 0x10],ECX
0055aa1d MOV ECX,EDI
0055aa1f MOV dword ptr [ESI + 0x8],EAX
0055aa22 FIDIV dword ptr [ESP + 0x10]
0055aa26 FSTP float ptr [ESI + 0x1664]
0055aa2c CALL 0x00481b30
0055aa31 FLD float ptr [ESI + 0x1664]
0055aa37 FMUL float ptr [ESI + 0x28]
0055aa3a MOV ECX,EDI
0055aa3c FMUL float ptr [0x005a8ff0]
0055aa42 FSTP float ptr [EAX]
0055aa44 FLD float ptr [ESI + 0x2c]
0055aa47 FMUL float ptr [0x005a8ff0]
0055aa4d FSTP float ptr [EAX + 0x4]
0055aa50 FLD float ptr [ESI + 0x1664]
0055aa56 FMUL float ptr [ESI + 0x28]
0055aa59 FMUL float ptr [0x005a83e8]
0055aa5f FSTP float ptr [EAX + 0x18]
0055aa62 FLD float ptr [ESI + 0x2c]
0055aa65 FMUL float ptr [0x005a8ff0]
0055aa6b FSTP float ptr [EAX + 0x1c]
0055aa6e FLD float ptr [ESI + 0x1664]
0055aa74 FMUL float ptr [ESI + 0x28]
0055aa77 FMUL float ptr [0x005a83e8]
0055aa7d FSTP float ptr [EAX + 0x30]
0055aa80 FLD float ptr [ESI + 0x2c]
0055aa83 FMUL float ptr [0x005a83e8]
0055aa89 FSTP float ptr [EAX + 0x34]
0055aa8c FLD float ptr [ESI + 0x1664]
0055aa92 FMUL float ptr [ESI + 0x28]
0055aa95 FMUL float ptr [0x005a8ff0]
0055aa9b FSTP float ptr [EAX + 0x48]
0055aa9e FLD float ptr [ESI + 0x2c]
0055aaa1 FMUL float ptr [0x005a83e8]
0055aaa7 FSTP float ptr [EAX + 0x4c]
0055aaaa CALL 0x00481b90
0055aaaf POP EDI
0055aab0 POP ESI
0055aab1 RET 0x8
