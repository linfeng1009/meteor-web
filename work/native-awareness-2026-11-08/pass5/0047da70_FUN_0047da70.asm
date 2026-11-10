0047da70 SUB ESP,0x1c
0047da73 FILD dword ptr [ESP + 0x20]
0047da77 MOV EAX,dword ptr [ESP + 0x20]
0047da7b PUSH EBP
0047da7c MOV EBP,ECX
0047da7e MOV dword ptr [ESP + 0xc],0x0
0047da86 FDIVR float ptr [0x005a83f4]
0047da8c LEA ECX,[EAX + EAX*0x2]
0047da8f LEA EDX,[EAX + EAX*0x1]
0047da92 ADD ECX,ECX
0047da94 PUSH ECX
0047da95 PUSH EDX
0047da96 SHL EAX,0x2
0047da99 PUSH EAX
0047da9a MOV ECX,EBP
0047da9c FLD float ptr [ESP + 0x34]
0047daa0 FMUL ST1
0047daa2 FSTP float ptr [ESP + 0x20]
0047daa6 FLD float ptr [ESP + 0x38]
0047daaa FMUL float ptr [0x005a83e8]
0047dab0 FSTP float ptr [ESP + 0x14]
0047dab4 FLD float ptr [ESP + 0x34]
0047dab8 FMUL float ptr [0x005a8ff0]
0047dabe FST float ptr [ESP + 0x10]
0047dac2 FADD float ptr [ESP + 0x20]
0047dac6 FSTP float ptr [ESP + 0x34]
0047daca FST float ptr [ESP + 0x28]
0047dace FSTP float ptr [ESP + 0x38]
0047dad2 CALL 0x0047c1e0
0047dad7 TEST EAX,EAX
0047dad9 JNZ 0x0047dae2
0047dadb POP EBP
0047dadc ADD ESP,0x1c
0047dadf RET 0xc
