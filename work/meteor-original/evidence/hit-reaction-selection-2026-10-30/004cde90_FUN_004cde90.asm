004cde90 PUSH ESI
004cde91 MOV ESI,ECX
004cde93 MOV EAX,dword ptr [ESI + 0x10]
004cde96 TEST EAX,EAX
004cde98 JZ 0x004cdea2
004cde9a LEA ECX,[EAX + 0xfffff9a4]
004cdea0 JMP 0x004cdea4
004cdea2 XOR ECX,ECX
004cdea4 CALL 0x0055c300
004cdea9 CMP EAX,0x4
004cdeac JNZ 0x004cdec0
004cdeae MOV EAX,dword ptr [ESI]
004cdeb0 PUSH 0x1
004cdeb2 MOV ECX,ESI
004cdeb4 CALL dword ptr [EAX + 0x12c]
004cdeba XOR EAX,EAX
004cdebc POP ESI
004cdebd RET 0x8
004cdec0 FLD double ptr [ESP + 0x8]
004cdec4 MOV EDX,dword ptr [ESI]
004cdec6 LEA EAX,[ESI + 0xd0]
004cdecc PUSH 0x3f800000
004cded1 PUSH EAX
004cded2 PUSH ECX
004cded3 MOV ECX,ESI
004cded5 FSTP float ptr [ESP]
004cded8 CALL dword ptr [EDX + 0xc8]
004cdede POP ESI
004cdedf RET 0x8
