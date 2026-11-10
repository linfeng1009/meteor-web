004fc8a0 SUB ESP,0x28
004fc8a3 LEA EAX,[ECX + 0x18]
004fc8a6 MOV EDX,dword ptr [ECX + 0x18]
004fc8a9 MOV dword ptr [ESP + 0x4],EDX
004fc8ad MOV EDX,dword ptr [EAX + 0x4]
004fc8b0 MOV dword ptr [ESP + 0x8],EDX
004fc8b4 MOV EAX,dword ptr [EAX + 0x8]
004fc8b7 MOV dword ptr [ESP + 0xc],EAX
004fc8bb MOV EAX,dword ptr [ECX + 0x58]
004fc8be FLD float ptr [ESP + 0xc]
004fc8c2 TEST EAX,EAX
004fc8c4 JL 0x004fc8d8
004fc8c6 LEA EDX,[EAX*0x8 + 0x0]
004fc8cd SUB EDX,EAX
004fc8cf FADD float ptr [EDX*0x8 + 0x666a08]
004fc8d6 JMP 0x004fc8de
004fc8d8 FADD float ptr [0x005a8dbc]
004fc8de MOV EAX,dword ptr [ECX + 0x10]
004fc8e1 PUSH ESI
004fc8e2 FSTP float ptr [ESP + 0x10]
004fc8e6 MOVSX EDX,word ptr [EAX]
004fc8e9 MOV dword ptr [ESP + 0x4],EDX
004fc8ed MOV ESI,dword ptr [ESP + 0x30]
004fc8f1 FILD dword ptr [ESP + 0x4]
004fc8f5 FMUL float ptr [ECX + 0x114]
004fc8fb FSTP float ptr [ESP + 0x4]
004fc8ff FLD float ptr [ESI]
004fc901 FSUB float ptr [ESP + 0x8]
004fc905 FSTP float ptr [ESP + 0x14]
004fc909 FLD float ptr [ESI + 0x4]
004fc90c FSUB float ptr [ESP + 0xc]
004fc910 MOV EAX,dword ptr [ESP + 0x14]
004fc914 MOV dword ptr [ESP + 0x20],EAX
004fc918 FSTP float ptr [ESP + 0x18]
004fc91c FLD float ptr [ESI + 0x8]
004fc91f FSUB float ptr [ESP + 0x10]
004fc923 MOV ECX,dword ptr [ESP + 0x18]
004fc927 MOV dword ptr [ESP + 0x24],ECX
004fc92b LEA ECX,[ESP + 0x20]
004fc92f FSTP float ptr [ESP + 0x1c]
004fc933 MOV EDX,dword ptr [ESP + 0x1c]
004fc937 MOV dword ptr [ESP + 0x28],EDX
004fc93b CALL 0x0047ed20
004fc940 FLD float ptr [ESP + 0x4]
004fc944 FMUL float ptr [ESP + 0x4]
004fc948 FCOMPP
004fc94a FNSTSW AX
004fc94c TEST AH,0x5
004fc94f JP 0x004fc95a
004fc951 XOR AL,AL
004fc953 POP ESI
004fc954 ADD ESP,0x28
004fc957 RET 0x4
004fc95a MOV ECX,dword ptr [0x0066629c]
004fc960 PUSH 0x0
004fc962 PUSH 0x0
004fc964 LEA EAX,[ESP + 0x10]
004fc968 PUSH ESI
004fc969 PUSH EAX
004fc96a CALL 0x004c1360
004fc96f NEG AL
004fc971 SBB EAX,EAX
004fc973 POP ESI
004fc974 INC EAX
004fc975 ADD ESP,0x28
004fc978 RET 0x4
