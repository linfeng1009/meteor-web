004fd5b0 PUSH ESI
004fd5b1 MOV ESI,ECX
004fd5b3 MOV EAX,dword ptr [ESI + 0xc]
004fd5b6 TEST EAX,EAX
004fd5b8 JZ 0x004fd613
004fd5ba CALL 0x004fd580
004fd5bf CALL 0x004fdd10
004fd5c4 MOV ECX,dword ptr [ESI + 0xc]
004fd5c7 CALL 0x00500fa0
004fd5cc CMP dword ptr [ESI + 0x64],0x504be0
004fd5d3 JZ 0x004fd5fe
004fd5d5 MOV ECX,dword ptr [ESI + 0xc]
004fd5d8 PUSH 0x0
004fd5da CALL 0x00500c60
004fd5df MOV ECX,dword ptr [ESI + 0xc]
004fd5e2 PUSH 0x0
004fd5e4 CALL 0x005012a0
004fd5e9 MOV EAX,dword ptr [ESP + 0x8]
004fd5ed MOV dword ptr [ESI + 0x84],0xffffffff
004fd5f7 MOV dword ptr [ESI + 0x64],EAX
004fd5fa POP ESI
004fd5fb RET 0x4
004fd5fe MOV ECX,dword ptr [ESP + 0x8]
004fd602 MOV dword ptr [ESI + 0x84],0xffffffff
004fd60c MOV dword ptr [ESI + 0x64],ECX
004fd60f POP ESI
004fd610 RET 0x4
004fd613 MOV EDX,dword ptr [ESP + 0x8]
004fd617 MOV dword ptr [ESI + 0x84],0xffffffff
004fd621 MOV dword ptr [ESI + 0x64],EDX
004fd624 POP ESI
004fd625 RET 0x4
