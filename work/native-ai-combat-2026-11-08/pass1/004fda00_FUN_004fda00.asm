004fda00 SUB ESP,0x8
004fda03 PUSH EBX
004fda04 PUSH EBP
004fda05 PUSH ESI
004fda06 MOV ESI,ECX
004fda08 XOR EBX,EBX
004fda0a PUSH EDI
004fda0b MOV dword ptr [ESI + 0x7c],EBX
004fda0e CALL 0x0050a8de
004fda13 CDQ
004fda14 MOV ECX,0x3e8
004fda19 MOV dword ptr [ESI + 0x64],0x5038e0
004fda20 IDIV ECX
004fda22 MOV dword ptr [ESP + 0x10],EDX
004fda26 FILD dword ptr [ESP + 0x10]
004fda2a FMUL float ptr [0x005ab86c]
004fda30 FSTP float ptr [ESI + 0x80]
004fda36 MOV EAX,dword ptr [ESI + 0x8c]
004fda3c MOV ECX,dword ptr [ESI + 0x90]
004fda42 CMP EAX,ECX
004fda44 JZ 0x004fda54
004fda46 MOV byte ptr [EAX],BL
004fda48 MOV EDX,dword ptr [ESI + 0x8c]
004fda4e MOV dword ptr [ESI + 0x90],EDX
004fda54 MOV EAX,dword ptr [ESI + 0x98]
004fda5a MOV ECX,dword ptr [ESI + 0x9c]
004fda60 CMP EAX,ECX
004fda62 JZ 0x004fda72
004fda64 MOV byte ptr [EAX],BL
004fda66 MOV EAX,dword ptr [ESI + 0x98]
004fda6c MOV dword ptr [ESI + 0x9c],EAX
004fda72 MOV dword ptr [ESI + 0x84],0xffffffff
004fda7c MOV EAX,dword ptr [ESI + 0x68]
004fda7f MOV EDI,dword ptr [ESI + 0x6c]
004fda82 MOV dword ptr [ESP + 0x14],EAX
004fda86 MOV ECX,dword ptr [ESP + 0x14]
004fda8a PUSH EBX
004fda8b PUSH ECX
004fda8c PUSH EAX
004fda8d PUSH EDI
004fda8e PUSH EDI
004fda8f CALL 0x004fece0
004fda94 MOV ECX,dword ptr [ESI + 0x6c]
004fda97 ADD ESP,0x14
004fda9a CMP EAX,ECX
004fda9c MOV dword ptr [ESP + 0x10],ECX
004fdaa0 MOV EBP,EAX
004fdaa2 JZ 0x004fdab7
004fdaa4 PUSH EBX
004fdaa5 MOV ECX,EBP
004fdaa7 CALL 0x004c82b0
004fdaac MOV EAX,dword ptr [ESP + 0x10]
004fdab0 ADD EBP,0x30
004fdab3 CMP EBP,EAX
004fdab5 JNZ 0x004fdaa4
004fdab7 MOV EAX,dword ptr [ESP + 0x14]
004fdabb SUB EDI,EAX
004fdabd MOV EAX,0xd5555555
004fdac2 IMUL EDI
004fdac4 SAR EDX,0x3
004fdac7 MOV EAX,EDX
004fdac9 MOV EDI,dword ptr [ESI + 0x6c]
004fdacc SHR EAX,0x1f
004fdacf ADD EDX,EAX
004fdad1 LEA ECX,[EDX + EDX*0x2]
004fdad4 SHL ECX,0x4
004fdad7 ADD EDI,ECX
004fdad9 OR ECX,0xffffffff
004fdadc MOV dword ptr [ESI + 0x6c],EDI
004fdadf MOV dword ptr [ESI + 0x88],EBX
004fdae5 MOV dword ptr [ESI + 0xc4],ECX
004fdaeb MOV dword ptr [ESI + 0xdc],EBX
004fdaf1 MOV dword ptr [ESI + 0xd8],EBX
004fdaf7 MOV dword ptr [ESI + 0xd4],EBX
004fdafd MOV dword ptr [ESI + 0xe0],EBX
004fdb03 MOV dword ptr [ESI + 0x3c],EBX
004fdb06 MOV dword ptr [ESI + 0x40],EBX
004fdb09 MOV dword ptr [ESI + 0x78],EBX
004fdb0c MOV dword ptr [ESI + 0x74],EBX
004fdb0f MOV EAX,dword ptr [ESI + 0xfc]
004fdb15 CMP EAX,dword ptr [ESI + 0x100]
004fdb1b JZ 0x004fdb2b
004fdb1d MOV byte ptr [EAX],BL
004fdb1f MOV EDX,dword ptr [ESI + 0xfc]
004fdb25 MOV dword ptr [ESI + 0x100],EDX
004fdb2b MOV dword ptr [ESI + 0x114],0x3f800000
004fdb35 MOV dword ptr [ESI + 0xe4],ECX
004fdb3b MOV EAX,dword ptr [ESI + 0x10c]
004fdb41 MOV EDI,dword ptr [ESI + 0x108]
004fdb47 MOV ECX,EAX
004fdb49 MOV EDX,EDI
004fdb4b SUB ECX,EAX
004fdb4d SAR ECX,0x1
004fdb4f CMP ECX,EBX
004fdb51 JLE 0x004fdb70
004fdb53 MOV EBP,EAX
004fdb55 MOV dword ptr [ESP + 0x10],ECX
004fdb59 SUB EBP,EDI
004fdb5b MOV CX,word ptr [EDX + EBP*0x1]
004fdb5f MOV word ptr [EDX],CX
004fdb62 MOV ECX,dword ptr [ESP + 0x10]
004fdb66 ADD EDX,0x2
004fdb69 DEC ECX
004fdb6a MOV dword ptr [ESP + 0x10],ECX
004fdb6e JNZ 0x004fdb5b
004fdb70 MOV ECX,dword ptr [ESI + 0x10c]
004fdb76 SUB EAX,EDI
004fdb78 SAR EAX,0x1
004fdb7a NEG EAX
004fdb7c ADD EAX,EAX
004fdb7e ADD ECX,EAX
004fdb80 MOV dword ptr [ESI + 0x10c],ECX
004fdb86 MOV ECX,ESI
004fdb88 MOV dword ptr [ESI + 0x120],EBX
004fdb8e CALL 0x004fcc00
004fdb93 CALL 0x004fdd10
004fdb98 MOV ECX,ESI
004fdb9a POP EDI
004fdb9b POP ESI
004fdb9c POP EBP
004fdb9d POP EBX
004fdb9e ADD ESP,0x8
004fdba1 JMP 0x004fd580
