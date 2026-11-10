004fcb40 MOV EAX,dword ptr [ESP + 0x4]
004fcb44 SUB ESP,0x18
004fcb47 TEST EAX,EAX
004fcb49 PUSH ESI
004fcb4a JNZ 0x004fcb55
004fcb4c XOR AL,AL
004fcb4e POP ESI
004fcb4f ADD ESP,0x18
004fcb52 RET 0x4
004fcb55 MOV ESI,dword ptr [ECX + 0x58]
004fcb58 TEST ESI,ESI
004fcb5a JGE 0x004fcb65
004fcb5c XOR AL,AL
004fcb5e POP ESI
004fcb5f ADD ESP,0x18
004fcb62 RET 0x4
004fcb65 FLD float ptr [ECX + 0x18]
004fcb68 FSUB float ptr [EAX + 0x18]
004fcb6b FSTP float ptr [ESP + 0x4]
004fcb6f FLD float ptr [ECX + 0x1c]
004fcb72 FSUB float ptr [EAX + 0x1c]
004fcb75 FSTP float ptr [ESP + 0x8]
004fcb79 FLD float ptr [ECX + 0x20]
004fcb7c FSUB float ptr [EAX + 0x20]
004fcb7f MOV ECX,dword ptr [ESP + 0x8]
004fcb83 MOV EAX,dword ptr [ESP + 0x4]
004fcb87 MOV dword ptr [ESP + 0x14],ECX
004fcb8b LEA ECX,[ESP + 0x10]
004fcb8f MOV dword ptr [ESP + 0x10],EAX
004fcb93 FSTP float ptr [ESP + 0xc]
004fcb97 MOV EDX,dword ptr [ESP + 0xc]
004fcb9b MOV dword ptr [ESP + 0x18],EDX
004fcb9f CALL 0x0047ecf0
004fcba4 LEA EAX,[ESI*0x8 + 0x0]
004fcbab SUB EAX,ESI
004fcbad FCOMP float ptr [EAX*0x8 + 0x666a00]
004fcbb4 FNSTSW AX
004fcbb6 TEST AH,0x5
004fcbb9 JP 0x004fcbc7
004fcbbb MOV EAX,0x1
004fcbc0 POP ESI
004fcbc1 ADD ESP,0x18
004fcbc4 RET 0x4
004fcbc7 XOR EAX,EAX
004fcbc9 POP ESI
004fcbca ADD ESP,0x18
004fcbcd RET 0x4
