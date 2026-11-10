004dc9a0 PUSH -0x1
004dc9a2 PUSH 0x5a27d9
004dc9a7 MOV EAX,FS:[0x0]
004dc9ad PUSH EAX
004dc9ae MOV dword ptr FS:[0x0],ESP
004dc9b5 SUB ESP,0x8
004dc9b8 PUSH EBX
004dc9b9 PUSH ESI
004dc9ba MOV ESI,ECX
004dc9bc PUSH 0xc
004dc9be MOV dword ptr [ESP + 0x10],ESI
004dc9c2 CALL 0x00402bf0
004dc9c7 MOV dword ptr [ESI + 0x10],EAX
004dc9ca MOV dword ptr [EAX],EAX
004dc9cc MOV EAX,dword ptr [ESI + 0x10]
004dc9cf ADD ESP,0x4
004dc9d2 MOV dword ptr [EAX + 0x4],EAX
004dc9d5 MOV dword ptr [ESI + 0x4],0x5aaae8
004dc9dc MOV dword ptr [ESI + 0xc],0x1869f
004dc9e3 XOR EBX,EBX
004dc9e5 MOV dword ptr [ESP + 0x18],EBX
004dc9e9 MOV dword ptr [ESI + 0x1c],EBX
004dc9ec MOV dword ptr [ESI + 0x20],EBX
004dc9ef MOV dword ptr [ESI + 0x24],EBX
004dc9f2 MOV dword ptr [ESI + 0x28],EBX
004dc9f5 MOV dword ptr [ESI + 0x2c],EBX
004dc9f8 MOV dword ptr [ESI + 0x30],EBX
004dc9fb MOV ECX,0x5d59e8
004dca00 MOV byte ptr [ESP + 0x18],0x2
004dca05 MOV dword ptr [ESI + 0x34],EBX
004dca08 CALL 0x00402330
004dca0d MOV EAX,[0x005d59b0]
004dca12 MOV byte ptr [ESP + 0x18],0x3
004dca17 CMP EAX,EBX
004dca19 JNZ 0x004dca27
004dca1b PUSH 0x18
004dca1d CALL 0x00403290
004dca22 ADD ESP,0x4
004dca25 JMP 0x004dca2f
004dca27 MOV ECX,dword ptr [EAX]
004dca29 MOV dword ptr [0x005d59b0],ECX
004dca2f MOV DL,byte ptr [ESP + 0xb]
004dca33 MOV dword ptr [0x005d59e8],EBX
004dca39 MOV dword ptr [ESI + 0x34],EAX
004dca3c MOV dword ptr [ESI + 0x38],EBX
004dca3f MOV byte ptr [ESI + 0x3c],DL
004dca42 MOV byte ptr [EAX],BL
004dca44 MOV EAX,dword ptr [ESI + 0x34]
004dca47 MOV ECX,dword ptr [ESP + 0x10]
004dca4b MOV dword ptr [EAX + 0x4],EBX
004dca4e MOV EAX,dword ptr [ESI + 0x34]
004dca51 MOV dword ptr [EAX + 0x8],EAX
004dca54 MOV EAX,dword ptr [ESI + 0x34]
004dca57 MOV dword ptr [EAX + 0xc],EAX
004dca5a MOV dword ptr [ESI],0x5aaa78
004dca60 MOV dword ptr [ESI + 0x18],EBX
004dca63 MOV EAX,ESI
004dca65 POP ESI
004dca66 POP EBX
004dca67 MOV dword ptr FS:[0x0],ECX
004dca6e ADD ESP,0x14
004dca71 RET
