004fdbb0 SUB ESP,0x14
004fdbb3 PUSH ESI
004fdbb4 MOV ESI,ECX
004fdbb6 PUSH EDI
004fdbb7 MOV dword ptr [ESP + 0x8],ESI
004fdbbb MOV EDI,dword ptr [ESI + 0x68]
004fdbbe MOV EAX,dword ptr [ESI + 0x6c]
004fdbc1 CMP EDI,EAX
004fdbc3 MOV dword ptr [ESP + 0x10],EDI
004fdbc7 JZ 0x004fdd09
004fdbcd PUSH EBX
004fdbce LEA EBX,[EDI + 0x30]
004fdbd1 PUSH EBP
004fdbd2 MOV dword ptr [ESP + 0x1c],EBX
004fdbd6 CMP dword ptr [EBX + -0x24],0x504be0
004fdbdd JNZ 0x004fdcf0
004fdbe3 MOV EAX,dword ptr [ESI + 0x6c]
004fdbe6 CMP EBX,EAX
004fdbe8 JZ 0x004fdcde
004fdbee SUB EAX,EBX
004fdbf0 MOV ECX,EAX
004fdbf2 MOV EAX,0x2aaaaaab
004fdbf7 IMUL ECX
004fdbf9 SAR EDX,0x3
004fdbfc MOV EAX,EDX
004fdbfe SHR EAX,0x1f
004fdc01 ADD EDX,EAX
004fdc03 TEST EDX,EDX
004fdc05 JLE 0x004fdcde
004fdc0b ADD EBX,0x20
004fdc0e MOV dword ptr [ESP + 0x14],EDX
004fdc12 LEA ECX,[EBX + -0x20]
004fdc15 LEA EDX,[EBX + -0x50]
004fdc18 MOV EAX,dword ptr [ECX]
004fdc1a MOV dword ptr [EDX],EAX
004fdc1c MOV EAX,dword ptr [ECX + 0x4]
004fdc1f MOV dword ptr [EDX + 0x4],EAX
004fdc22 LEA EAX,[EBX + -0x40]
004fdc25 MOV ECX,dword ptr [ECX + 0x8]
004fdc28 MOV dword ptr [EDX + 0x8],ECX
004fdc2b MOV EDX,dword ptr [EBX + -0x14]
004fdc2e LEA ECX,[EBX + -0x10]
004fdc31 MOV dword ptr [EBX + -0x44],EDX
004fdc34 CMP ECX,EAX
004fdc36 JZ 0x004fdc48
004fdc38 MOV EDX,dword ptr [EBX + -0xc]
004fdc3b MOV EAX,dword ptr [EBX + -0x10]
004fdc3e PUSH EDX
004fdc3f PUSH EAX
004fdc40 LEA ECX,[EBX + -0x40]
004fdc43 CALL 0x00403200
004fdc48 LEA ECX,[EBX + -0x34]
004fdc4b LEA EDX,[EBX + -0x4]
004fdc4e CMP EDX,ECX
004fdc50 JZ 0x004fdcb8
004fdc52 MOV EAX,dword ptr [EBX]
004fdc54 MOV EBP,dword ptr [EBX + -0x4]
004fdc57 MOV EDI,dword ptr [EBX + -0x34]
004fdc5a MOV ECX,dword ptr [EBX + -0x30]
004fdc5d LEA EDX,[EBX + -0x34]
004fdc60 MOV dword ptr [ESP + 0x20],EAX
004fdc64 SUB EAX,EBP
004fdc66 SUB ECX,EDI
004fdc68 CMP EAX,ECX
004fdc6a MOV ESI,EBP
004fdc6c JA 0x004fdc90
004fdc6e MOV ECX,EAX
004fdc70 MOV EBP,ECX
004fdc72 SHR ECX,0x2
004fdc75 MOVSD.REP ES:EDI,ESI
004fdc77 MOV ECX,EBP
004fdc79 AND ECX,0x3
004fdc7c MOVSB.REP ES:EDI,ESI
004fdc7e MOV ECX,dword ptr [EBX + -0x30]
004fdc81 PUSH ECX
004fdc82 MOV ECX,dword ptr [EDX]
004fdc84 ADD ECX,EAX
004fdc86 PUSH ECX
004fdc87 MOV ECX,EDX
004fdc89 CALL 0x00402b30
004fdc8e JMP 0x004fdcb4
004fdc90 MOV EAX,ECX
004fdc92 SHR ECX,0x2
004fdc95 MOVSD.REP ES:EDI,ESI
004fdc97 MOV ECX,EAX
004fdc99 AND ECX,0x3
004fdc9c MOVSB.REP ES:EDI,ESI
004fdc9e MOV EAX,dword ptr [EBX + -0x30]
004fdca1 MOV EDI,dword ptr [EDX]
004fdca3 MOV ECX,dword ptr [ESP + 0x20]
004fdca7 SUB EAX,EDI
004fdca9 ADD EAX,EBP
004fdcab PUSH ECX
004fdcac PUSH EAX
004fdcad MOV ECX,EDX
004fdcaf CALL 0x00403490
004fdcb4 MOV ESI,dword ptr [ESP + 0x10]
004fdcb8 MOV ECX,dword ptr [EBX + 0x8]
004fdcbb MOV EAX,dword ptr [ESP + 0x14]
004fdcbf MOV dword ptr [EBX + -0x28],ECX
004fdcc2 MOV EDX,dword ptr [EBX + 0xc]
004fdcc5 MOV dword ptr [EBX + -0x24],EDX
004fdcc8 ADD EBX,0x30
004fdccb DEC EAX
004fdccc MOV dword ptr [ESP + 0x14],EAX
004fdcd0 JNZ 0x004fdc12
004fdcd6 MOV EDI,dword ptr [ESP + 0x18]
004fdcda MOV EBX,dword ptr [ESP + 0x1c]
004fdcde MOV EAX,dword ptr [ESI + 0x6c]
004fdce1 ADD EAX,-0x30
004fdce4 MOV ECX,EAX
004fdce6 MOV dword ptr [ESI + 0x6c],EAX
004fdce9 CALL 0x004c82d0
004fdcee JMP 0x004fdcfe
004fdcf0 ADD EDI,0x30
004fdcf3 ADD EBX,0x30
004fdcf6 MOV dword ptr [ESP + 0x18],EDI
004fdcfa MOV dword ptr [ESP + 0x1c],EBX
004fdcfe CMP EDI,dword ptr [ESI + 0x6c]
004fdd01 JNZ 0x004fdbd6
004fdd07 POP EBP
004fdd08 POP EBX
004fdd09 POP EDI
004fdd0a POP ESI
004fdd0b ADD ESP,0x14
004fdd0e RET
