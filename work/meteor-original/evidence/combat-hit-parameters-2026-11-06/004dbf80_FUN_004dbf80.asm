004dbf80 MOV EAX,dword ptr [ESP + 0x10]
004dbf84 MOV EDX,dword ptr [ESP + 0x4]
004dbf88 PUSH ESI
004dbf89 PUSH EDI
004dbf8a MOV EDI,dword ptr [ESP + 0x10]
004dbf8e MOV ESI,ECX
004dbf90 MOV ECX,dword ptr [ESP + 0x14]
004dbf94 PUSH 0x1
004dbf96 PUSH EAX
004dbf97 PUSH ECX
004dbf98 PUSH EDI
004dbf99 PUSH EDX
004dbf9a MOV ECX,ESI
004dbf9c CALL 0x0055d260
004dbfa1 TEST EAX,EAX
004dbfa3 JZ 0x004dbfbc
004dbfa5 MOV ECX,dword ptr [ESP + 0x18]
004dbfa9 INC word ptr [ESI + 0x8a8]
004dbfb0 MOV dword ptr [ESI + 0x8ac],EDI
004dbfb6 MOV dword ptr [ESI + 0x8b0],ECX
004dbfbc POP EDI
004dbfbd POP ESI
004dbfbe RET 0x10
