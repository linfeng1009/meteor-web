004dd130 MOV EAX,dword ptr [ESP + 0x4]
004dd134 MOV ECX,dword ptr [ESP + 0x8]
004dd138 MOV dword ptr [EAX + 0x3d0],ECX
004dd13e MOV dword ptr [EAX + 0x3cc],0x1
004dd148 XOR EAX,EAX
004dd14a RET 0x8
