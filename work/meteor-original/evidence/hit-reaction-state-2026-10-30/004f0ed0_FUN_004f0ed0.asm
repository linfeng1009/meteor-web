004f0ed0 PUSH ESI
004f0ed1 MOV ESI,ECX
004f0ed3 MOV ECX,dword ptr [ESI + 0x238]
004f0ed9 TEST ECX,ECX
004f0edb JZ 0x004f0eed
004f0edd MOV EAX,dword ptr [ECX]
004f0edf PUSH 0x1
004f0ee1 CALL dword ptr [EAX]
004f0ee3 MOV dword ptr [ESI + 0x238],0x0
004f0eed MOV EDX,dword ptr [ESI]
004f0eef MOV ECX,ESI
004f0ef1 CALL dword ptr [EDX + 0x44]
004f0ef4 MOV EDX,dword ptr [EAX]
004f0ef6 MOV ECX,EAX
004f0ef8 POP ESI
004f0ef9 JMP dword ptr [EDX + 0x150]
