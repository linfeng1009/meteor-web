004fcb00 MOV EAX,dword ptr [ESP + 0x4]
004fcb04 TEST EAX,EAX
004fcb06 JZ 0x004fcb30
004fcb08 MOV EAX,dword ptr [ECX + 0x58]
004fcb0b TEST EAX,EAX
004fcb0d JL 0x004fcb30
004fcb0f LEA EDX,[EAX*0x8 + 0x0]
004fcb16 SUB EDX,EAX
004fcb18 FLD float ptr [EDX*0x8 + 0x666a0c]
004fcb1f FSTP float ptr [ESP + 0x4]
004fcb23 MOV EAX,dword ptr [ESP + 0x4]
004fcb27 MOV dword ptr [ESP + 0x4],EAX
004fcb2b JMP 0x004fced0
004fcb30 XOR AL,AL
004fcb32 RET 0x4
