004dbfd0 MOV EAX,dword ptr [ESP + 0x8]
004dbfd4 PUSH ESI
004dbfd5 MOV ESI,ECX
004dbfd7 MOV ECX,dword ptr [ESP + 0x8]
004dbfdb PUSH EAX
004dbfdc PUSH ECX
004dbfdd MOV ECX,ESI
004dbfdf CALL 0x0055d020
004dbfe4 CMP EAX,0x3
004dbfe7 JZ 0x004dbffa
004dbfe9 INC word ptr [ESI + 0x8a8]
004dbff0 MOV dword ptr [ESI + 0x8ac],0x0
004dbffa POP ESI
004dbffb RET 0x8
