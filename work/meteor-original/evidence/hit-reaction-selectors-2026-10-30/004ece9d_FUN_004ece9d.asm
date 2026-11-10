004ece9d PUSH 0x62
004ece9f MOV ECX,EAX
004ecea1 CALL dword ptr [EDX + 0x114]
004ecea7 JMP 0x004ecee4
004ecee4 MOV EAX,dword ptr [ESI]
004ecee6 MOV ECX,ESI
004ecee8 CALL dword ptr [EAX + 0x14c]
004eceee MOV ECX,dword ptr [ESI + 0x258]
004ecef4 PUSH 0x0
004ecef6 CALL 0x005499a0
004ecefb TEST EAX,EAX
004ecefd JZ 0x004ecf09
004eceff MOV EDX,dword ptr [ESI]
004ecf01 MOV ECX,ESI
004ecf03 CALL dword ptr [EDX + 0x88]
004ecf09 MOV EAX,dword ptr [ESI]
004ecf0b MOV ECX,ESI
004ecf0d CALL dword ptr [EAX + 0x44]
004ecf10 MOV EDX,dword ptr [EAX]
004ecf12 MOV ECX,EAX
004ecf14 CALL dword ptr [EDX + 0x130]
004ecf1a CMP EAX,0x4
004ecf1d JNZ 0x004ecf2b
004ecf1f MOV EAX,dword ptr [ESI]
004ecf21 PUSH 0x2
004ecf23 MOV ECX,ESI
004ecf25 CALL dword ptr [EAX + 0x198]
004ecf2b POP ESI
004ecf2c ADD ESP,0x1c
004ecf2f RET 0x4
