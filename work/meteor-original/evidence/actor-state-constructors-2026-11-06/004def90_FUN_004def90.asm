004def90 PUSH -0x1
004def92 PUSH 0x5a29a8
004def97 MOV EAX,FS:[0x0]
004def9d PUSH EAX
004def9e MOV dword ptr FS:[0x0],ESP
004defa5 PUSH ECX
004defa6 PUSH ESI
004defa7 MOV ESI,ECX
004defa9 MOV dword ptr [ESP + 0x4],ESI
004defad CALL 0x004dc9a0
004defb2 MOV ECX,ESI
004defb4 MOV dword ptr [ESP + 0x10],0x0
004defbc MOV dword ptr [ESI],0x5aacc0
004defc2 CALL 0x004df190
004defc7 MOV ECX,dword ptr [ESP + 0x8]
004defcb MOV EAX,ESI
004defcd POP ESI
004defce MOV dword ptr FS:[0x0],ECX
004defd5 ADD ESP,0x10
004defd8 RET
