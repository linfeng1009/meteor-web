004ce2a0 MOV EAX,dword ptr [ESP + 0x4]
004ce2a4 TEST EAX,EAX
004ce2a6 JZ 0x004ce2b5
004ce2a8 MOV dword ptr [ECX + 0x378],0x1
004ce2b2 RET 0x4
004ce2b5 MOV EAX,dword ptr [ECX]
004ce2b7 MOV dword ptr [ECX + 0x378],0x0
004ce2c1 MOV dword ptr [ESP + 0x4],0x0
004ce2c9 JMP dword ptr [EAX + 0xbc]
