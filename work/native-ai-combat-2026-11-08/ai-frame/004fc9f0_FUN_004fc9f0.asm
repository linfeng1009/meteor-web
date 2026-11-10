004fc9f0 MOV EAX,dword ptr [ESP + 0x4]
004fc9f4 SUB ESP,0x1c
004fc9f7 TEST EAX,EAX
004fc9f9 PUSH ESI
004fc9fa PUSH EDI
004fc9fb MOV ESI,ECX
004fc9fd JNZ 0x004fca09
004fc9ff POP EDI
004fca00 XOR AL,AL
004fca02 POP ESI
004fca03 ADD ESP,0x1c
004fca06 RET 0x4
004fca09 MOV EDI,dword ptr [ESI + 0x58]
004fca0c TEST EDI,EDI
004fca0e JGE 0x004fca1a
004fca10 POP EDI
004fca11 XOR AL,AL
004fca13 POP ESI
004fca14 ADD ESP,0x1c
004fca17 RET 0x4
004fca1a FLD float ptr [ESI + 0x18]
004fca1d FSUB float ptr [EAX + 0x18]
004fca20 FSTP float ptr [ESP + 0x18]
004fca24 FLD float ptr [ESI + 0x1c]
004fca27 FSUB float ptr [EAX + 0x1c]
004fca2a FSTP float ptr [ESP + 0x1c]
004fca2e FLD float ptr [ESI + 0x20]
004fca31 FSUB float ptr [EAX + 0x20]
004fca34 MOV ECX,dword ptr [ESP + 0x1c]
004fca38 MOV EAX,dword ptr [ESP + 0x18]
004fca3c MOV dword ptr [ESP + 0x10],ECX
004fca40 LEA ECX,[ESP + 0xc]
004fca44 MOV dword ptr [ESP + 0xc],EAX
004fca48 FSTP float ptr [ESP + 0x20]
004fca4c MOV EDX,dword ptr [ESP + 0x20]
004fca50 MOV dword ptr [ESP + 0x14],EDX
004fca54 CALL 0x0047ed20
004fca59 FSTP float ptr [ESP + 0x8]
004fca5d LEA EAX,[EDI*0x8 + 0x0]
004fca64 MOV ECX,ESI
004fca66 SUB EAX,EDI
004fca68 FLD float ptr [EAX*0x8 + 0x666a04]
004fca6f FLD ST0
004fca71 FMUL ST1
004fca73 FSTP float ptr [ESP + 0x28]
004fca77 FSTP ST0
004fca79 CALL 0x004fcf70
004fca7e TEST AL,AL
004fca80 JZ 0x004fca9b
004fca82 FLD float ptr [ESP + 0x8]
004fca86 FCOMP float ptr [ESP + 0x28]
004fca8a FNSTSW AX
004fca8c TEST AH,0x5
004fca8f JNP 0x004fcaec
004fca91 POP EDI
004fca92 XOR EAX,EAX
004fca94 POP ESI
004fca95 ADD ESP,0x1c
004fca98 RET 0x4
004fca9b MOV ECX,dword ptr [ESI + 0xc]
004fca9e CALL 0x00501030
004fcaa3 TEST AL,AL
004fcaa5 JZ 0x004fcac6
004fcaa7 FLD float ptr [ESP + 0x14]
004fcaab FABS
004fcaad FCOMP double ptr [0x005ab858]
004fcab3 FNSTSW AX
004fcab5 AND EAX,0x4100
004fcaba JNZ 0x004fca82
004fcabc POP EDI
004fcabd XOR AL,AL
004fcabf POP ESI
004fcac0 ADD ESP,0x1c
004fcac3 RET 0x4
004fcac6 LEA ECX,[ESP + 0xc]
004fcaca MOV dword ptr [ESP + 0x14],0x0
004fcad2 CALL 0x0047ed20
004fcad7 FLD float ptr [ESP + 0x28]
004fcadb FMUL float ptr [0x005a8e84]
004fcae1 FCOMPP
004fcae3 FNSTSW AX
004fcae5 AND EAX,0x4100
004fcaea JNZ 0x004fca91
004fcaec POP EDI
004fcaed MOV EAX,0x1
004fcaf2 POP ESI
004fcaf3 ADD ESP,0x1c
004fcaf6 RET 0x4
