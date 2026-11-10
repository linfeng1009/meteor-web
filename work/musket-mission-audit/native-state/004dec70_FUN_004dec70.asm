004dec70 PUSH ESI
004dec71 MOV ESI,dword ptr [ESP + 0x8]
004dec75 PUSH 0x0
004dec77 PUSH 0x0
004dec79 MOV EAX,dword ptr [ESI]
004dec7b PUSH 0x6
004dec7d MOV ECX,ESI
004dec7f CALL dword ptr [EAX + 0xc]
004dec82 MOV dword ptr [ESI + 0x36c],0x0
004dec8c POP ESI
004dec8d RET 0x4
