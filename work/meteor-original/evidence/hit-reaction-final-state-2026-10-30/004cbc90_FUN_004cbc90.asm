004cbc90 PUSH ECX
004cbc91 PUSH ESI
004cbc92 MOV ESI,ECX
004cbc94 MOV EAX,dword ptr [ESI + 0x3c4]
004cbc9a TEST EAX,EAX
004cbc9c JNZ 0x004cbcd1
004cbc9e CALL 0x00487830
004cbca3 MOV EDX,dword ptr [EAX]
004cbca5 LEA ECX,[ESP + 0x4]
004cbca9 PUSH ECX
004cbcaa MOV ECX,dword ptr [ESP + 0x10]
004cbcae AND ECX,0xff
004cbcb4 PUSH ECX
004cbcb5 MOV ECX,EAX
004cbcb7 CALL dword ptr [EDX + 0x2e8]
004cbcbd MOV EAX,dword ptr [ESP + 0x10]
004cbcc1 MOV ECX,dword ptr [ESP + 0x4]
004cbcc5 MOV EDX,dword ptr [ESI]
004cbcc7 PUSH EAX
004cbcc8 PUSH ECX
004cbcc9 MOV ECX,ESI
004cbccb CALL dword ptr [EDX + 0x1a4]
004cbcd1 POP ESI
004cbcd2 POP ECX
004cbcd3 RET 0x8
