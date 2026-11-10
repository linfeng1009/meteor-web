004dc060 SUB ESP,0x18
004dc063 PUSH ESI
004dc064 MOV ESI,dword ptr [ESP + 0x20]
004dc068 PUSH EDI
004dc069 MOV EDI,ECX
004dc06b TEST ESI,ESI
004dc06d JZ 0x004dc095
004dc06f LEA EAX,[ESP + 0x8]
004dc073 LEA ECX,[EDI + 0xfffffb10]
004dc079 PUSH EAX
004dc07a PUSH 0x3
004dc07c CALL 0x00477d30
004dc081 MOV ECX,dword ptr [ESP + 0x8]
004dc085 MOV EDX,dword ptr [ESP + 0xc]
004dc089 MOV EAX,dword ptr [ESP + 0x10]
004dc08d MOV dword ptr [ESI],ECX
004dc08f MOV dword ptr [ESI + 0x4],EDX
004dc092 MOV dword ptr [ESI + 0x8],EAX
004dc095 MOV ESI,dword ptr [ESP + 0x28]
004dc099 TEST ESI,ESI
004dc09b JZ 0x004dc0fd
004dc09d LEA ECX,[ESP + 0x8]
004dc0a1 PUSH ECX
004dc0a2 PUSH 0x1
004dc0a4 LEA ECX,[EDI + 0xfffffb10]
004dc0aa CALL 0x00477d30
004dc0af FLD float ptr [ESP + 0x8]
004dc0b3 FMUL float ptr [0x005a8430]
004dc0b9 FST float ptr [ESP + 0x14]
004dc0bd FLD float ptr [ESP + 0xc]
004dc0c1 FMUL float ptr [0x005a8430]
004dc0c7 MOV EDX,dword ptr [ESP + 0x14]
004dc0cb MOV dword ptr [ESP + 0x8],EDX
004dc0cf FST float ptr [ESP + 0x18]
004dc0d3 FLD float ptr [ESP + 0x10]
004dc0d7 FMUL float ptr [0x005a8430]
004dc0dd MOV EAX,dword ptr [ESP + 0x18]
004dc0e1 MOV dword ptr [ESP + 0xc],EAX
004dc0e5 FSTP float ptr [ESP + 0x1c]
004dc0e9 MOV ECX,dword ptr [ESP + 0x1c]
004dc0ed FXCH
004dc0ef FSTP float ptr [ESI]
004dc0f1 MOV EDX,ECX
004dc0f3 MOV dword ptr [ESP + 0x10],ECX
004dc0f7 FSTP float ptr [ESI + 0x4]
004dc0fa MOV dword ptr [ESI + 0x8],EDX
004dc0fd MOV ESI,dword ptr [ESP + 0x2c]
004dc101 TEST ESI,ESI
004dc103 JZ 0x004dc12b
004dc105 LEA EAX,[ESP + 0x8]
004dc109 LEA ECX,[EDI + 0xfffffb10]
004dc10f PUSH EAX
004dc110 PUSH 0x2
004dc112 CALL 0x00477d30
004dc117 MOV ECX,dword ptr [ESP + 0x8]
004dc11b MOV EDX,dword ptr [ESP + 0xc]
004dc11f MOV EAX,dword ptr [ESP + 0x10]
004dc123 MOV dword ptr [ESI],ECX
004dc125 MOV dword ptr [ESI + 0x4],EDX
004dc128 MOV dword ptr [ESI + 0x8],EAX
004dc12b POP EDI
004dc12c POP ESI
004dc12d ADD ESP,0x18
004dc130 RET 0xc
