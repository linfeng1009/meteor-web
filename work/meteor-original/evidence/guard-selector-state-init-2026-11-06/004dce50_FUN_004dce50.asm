004dce50 PUSH ESI
004dce51 MOV ESI,ECX
004dce53 MOV EAX,dword ptr [ESI + 0x20]
004dce56 MOV ECX,dword ptr [ESI + 0x1c]
004dce59 SUB EAX,ECX
004dce5b AND AL,0xfc
004dce5d CMP EAX,0x1c
004dce60 JL 0x004dcef5
004dce66 MOV EAX,dword ptr [ESP + 0xc]
004dce6a CMP EAX,0x3
004dce6d JA 0x004dcee2
004dce6f JMP dword ptr [EAX*0x4 + 0x4dcefc]
004dce76 CALL 0x0050a8de
004dce7b MOV dword ptr [ESP + 0xc],EAX
004dce7f FILD dword ptr [ESP + 0xc]
004dce83 FMUL double ptr [0x005aaaf8]
004dce89 CALL 0x00509980
004dce8e MOV ECX,dword ptr [ESI + 0x1c]
004dce91 POP ESI
004dce92 MOV EDX,dword ptr [ECX + EAX*0x4]
004dce95 MOV EAX,dword ptr [ESP + 0xc]
004dce99 MOV dword ptr [EAX],EDX
004dce9b MOV EAX,0x1
004dcea0 RET 0xc
004dcea3 MOV ECX,dword ptr [ESI + 0x1c]
004dcea6 MOV EAX,dword ptr [ESP + 0x10]
004dceaa POP ESI
004dceab MOV EDX,dword ptr [ECX + 0x10]
004dceae MOV dword ptr [EAX],EDX
004dceb0 MOV EAX,0x1
004dceb5 RET 0xc
004dceb8 MOV ECX,dword ptr [ESI + 0x1c]
004dcebb MOV EAX,dword ptr [ESP + 0x10]
004dcebf POP ESI
004dcec0 MOV EDX,dword ptr [ECX + 0x14]
004dcec3 MOV dword ptr [EAX],EDX
004dcec5 MOV EAX,0x1
004dceca RET 0xc
004dcecd MOV ECX,dword ptr [ESI + 0x1c]
004dced0 MOV EAX,dword ptr [ESP + 0x10]
004dced4 POP ESI
004dced5 MOV EDX,dword ptr [ECX + 0x18]
004dced8 MOV dword ptr [EAX],EDX
004dceda MOV EAX,0x1
004dcedf RET 0xc
004dcee2 MOV ECX,dword ptr [ESP + 0x10]
004dcee6 MOV EAX,0x1
004dceeb POP ESI
004dceec MOV dword ptr [ECX],0x0
004dcef2 RET 0xc
004dcef5 XOR EAX,EAX
004dcef7 POP ESI
004dcef8 RET 0xc
