004cc840 SUB ESP,0xfc
004cc846 PUSH EBX
004cc847 MOV EBX,ECX
004cc849 PUSH ESI
004cc84a PUSH EDI
004cc84b MOV EAX,dword ptr [EBX + 0x10]
004cc84e TEST EAX,EAX
004cc850 JZ 0x004ccad4
004cc856 LEA ESI,[EAX + 0xfffff9a4]
004cc85c LEA ECX,[ESP + 0xd8]
004cc863 PUSH 0x2
004cc865 PUSH ECX
004cc866 MOV EAX,dword ptr [ESI]
004cc868 MOV ECX,ESI
004cc86a CALL dword ptr [EAX + 0x6c]
004cc86d MOV EDX,dword ptr [ESI + 0x65c]
004cc873 LEA EAX,[ESP + 0x90]
004cc87a PUSH EAX
004cc87b LEA EAX,[ESP + 0xa0]
004cc882 LEA ECX,[ESI + 0x65c]
004cc888 PUSH EAX
004cc889 LEA EAX,[ESP + 0xc8]
004cc890 PUSH EAX
004cc891 CALL dword ptr [EDX + 0x4]
004cc894 MOV ECX,dword ptr [ESP + 0x9c]
004cc89b MOV EDX,dword ptr [ESP + 0xa0]
004cc8a2 MOV EAX,dword ptr [ESP + 0xa4]
004cc8a9 MOV dword ptr [ESP + 0x18],ECX
004cc8ad MOV ECX,dword ptr [ESP + 0x90]
004cc8b4 LEA ESI,[EBX + 0x390]
004cc8ba MOV dword ptr [ESP + 0x1c],EDX
004cc8be MOV EDX,dword ptr [ESP + 0x94]
004cc8c5 MOV dword ptr [ESP + 0x84],ECX
004cc8cc MOV ECX,ESI
004cc8ce MOV dword ptr [ESP + 0x20],EAX
004cc8d2 MOV EAX,dword ptr [ESP + 0x98]
004cc8d9 MOV dword ptr [ESP + 0x88],EDX
004cc8e0 MOV EDX,dword ptr [ECX]
004cc8e2 MOV dword ptr [ESP + 0x8c],EAX
004cc8e9 MOV dword ptr [ESP + 0x78],EDX
004cc8ed MOV EAX,dword ptr [ECX + 0x4]
004cc8f0 MOV dword ptr [ESP + 0x7c],EAX
004cc8f4 MOV ECX,dword ptr [ECX + 0x8]
004cc8f7 MOV dword ptr [ESP + 0x80],ECX
004cc8fe LEA ECX,[ESP + 0x78]
004cc902 MOV dword ptr [ESP + 0x80],0x0
004cc90d CALL 0x0047ec40
004cc912 MOV ECX,dword ptr [ESP + 0x104]
004cc919 MOV EDX,dword ptr [ESP + 0xfc]
004cc920 MOV EAX,dword ptr [ESP + 0x100]
004cc927 MOV dword ptr [ESP + 0x68],ECX
004cc92b LEA ECX,[ESP + 0x18]
004cc92f MOV dword ptr [ESP + 0x60],EDX
004cc933 MOV dword ptr [ESP + 0x64],EAX
004cc937 CALL 0x0047ec40
004cc93c LEA EDX,[ESP + 0x54]
004cc940 LEA EAX,[ESP + 0x84]
004cc947 PUSH EDX
004cc948 LEA ECX,[ESP + 0x1c]
004cc94c PUSH EAX
004cc94d PUSH ECX
004cc94e CALL 0x00529c40
004cc953 ADD ESP,0xc
004cc956 LEA ECX,[ESP + 0x54]
004cc95a CALL 0x0047ec40
004cc95f XOR EDI,EDI
004cc961 MOV EAX,EDI
004cc963 SUB EAX,0x0
004cc966 JZ 0x004cca2a
004cc96c DEC EAX
004cc96d JZ 0x004cc9e3
004cc96f DEC EAX
004cc970 JNZ 0x004cca42
004cc976 FLD float ptr [ESP + 0x54]
004cc97a FMUL float ptr [0x005a8430]
004cc980 FLD float ptr [ESP + 0x58]
004cc984 FMUL float ptr [0x005a8430]
004cc98a FLD float ptr [ESP + 0x5c]
004cc98e FMUL float ptr [0x005a8430]
004cc994 FSTP float ptr [ESP + 0xb0]
004cc99b FXCH
004cc99d FADD float ptr [ESP + 0x18]
004cc9a1 FSTP float ptr [ESP + 0x30]
004cc9a5 FLD float ptr [ESP + 0x1c]
004cc9a9 FADD ST0,ST1
004cc9ab MOV EDX,dword ptr [ESP + 0x30]
004cc9af MOV dword ptr [ESP + 0x24],EDX
004cc9b3 FSTP float ptr [ESP + 0x34]
004cc9b7 MOV EAX,dword ptr [ESP + 0x34]
004cc9bb FSTP ST0
004cc9bd FLD float ptr [ESP + 0x20]
004cc9c1 FADD float ptr [ESP + 0xb0]
004cc9c8 MOV dword ptr [ESP + 0x28],EAX
004cc9cc FSTP float ptr [ESP + 0x38]
004cc9d0 MOV ECX,dword ptr [ESP + 0x38]
004cc9d4 MOV dword ptr [ESP + 0x2c],ECX
004cc9d8 LEA ECX,[ESP + 0x24]
004cc9dc CALL 0x0047ec40
004cc9e1 JMP 0x004cca42
004cc9e3 FLD float ptr [ESP + 0x54]
004cc9e7 FADD float ptr [ESP + 0x18]
004cc9eb FSTP float ptr [ESP + 0x6c]
004cc9ef FLD float ptr [ESP + 0x1c]
004cc9f3 FADD float ptr [ESP + 0x58]
004cc9f7 MOV EDX,dword ptr [ESP + 0x6c]
004cc9fb MOV dword ptr [ESP + 0x24],EDX
004cc9ff FSTP float ptr [ESP + 0x70]
004cca03 FLD float ptr [ESP + 0x20]
004cca07 FADD float ptr [ESP + 0x5c]
004cca0b MOV EAX,dword ptr [ESP + 0x70]
004cca0f MOV dword ptr [ESP + 0x28],EAX
004cca13 FSTP float ptr [ESP + 0x74]
004cca17 MOV ECX,dword ptr [ESP + 0x74]
004cca1b MOV dword ptr [ESP + 0x2c],ECX
004cca1f LEA ECX,[ESP + 0x24]
004cca23 CALL 0x0047ec40
004cca28 JMP 0x004cca42
004cca2a MOV EDX,dword ptr [ESP + 0x18]
004cca2e MOV EAX,dword ptr [ESP + 0x1c]
004cca32 MOV ECX,dword ptr [ESP + 0x20]
004cca36 MOV dword ptr [ESP + 0x24],EDX
004cca3a MOV dword ptr [ESP + 0x28],EAX
004cca3e MOV dword ptr [ESP + 0x2c],ECX
004cca42 FLD float ptr [ESP + 0x24]
004cca46 FMUL float ptr [0x005a8b08]
004cca4c FLD float ptr [ESP + 0x28]
004cca50 FMUL float ptr [0x005a8b08]
004cca56 FLD float ptr [ESP + 0x2c]
004cca5a FMUL float ptr [0x005a8b08]
004cca60 FSTP float ptr [ESP + 0xbc]
004cca67 FXCH
004cca69 FADD float ptr [ESP + 0x60]
004cca6d FSTP float ptr [ESP + 0xc]
004cca71 FLD float ptr [ESP + 0x64]
004cca75 FADD ST0,ST1
004cca77 MOV EDX,dword ptr [ESP + 0xc]
004cca7b MOV dword ptr [ESP + 0x3c],EDX
004cca7f LEA EDX,[ESP + 0x48]
004cca83 PUSH EDX
004cca84 LEA EDX,[ESP + 0x64]
004cca88 FSTP float ptr [ESP + 0x14]
004cca8c MOV EAX,dword ptr [ESP + 0x14]
004cca90 FSTP ST0
004cca92 FLD float ptr [ESP + 0x6c]
004cca96 FADD float ptr [ESP + 0xc0]
004cca9d MOV dword ptr [ESP + 0x44],EAX
004ccaa1 LEA EAX,[ESP + 0xd0]
004ccaa8 PUSH EAX
004ccaa9 FSTP float ptr [ESP + 0x1c]
004ccaad MOV ECX,dword ptr [ESP + 0x1c]
004ccab1 MOV dword ptr [ESP + 0x4c],ECX
004ccab5 LEA ECX,[ESP + 0x44]
004ccab9 PUSH ECX
004ccaba MOV ECX,dword ptr [EBX + 0xa8]
004ccac0 PUSH EDX
004ccac1 CALL 0x005644f0
004ccac6 TEST EAX,EAX
004ccac8 JNZ 0x004ccae2
004ccaca INC EDI
004ccacb CMP EDI,0x3
004ccace JL 0x004cc961
004ccad4 POP EDI
004ccad5 POP ESI
004ccad6 XOR EAX,EAX
004ccad8 POP EBX
004ccad9 ADD ESP,0xfc
004ccadf RET 0x4
004ccae2 FLD float ptr [ESP + 0x50]
004ccae6 FMUL float ptr [ESI + 0x8]
004ccae9 FLD float ptr [ESP + 0x4c]
004ccaed FMUL float ptr [ESI + 0x4]
004ccaf0 MOV EAX,ESI
004ccaf2 FADDP
004ccaf4 FLD float ptr [ESP + 0x48]
004ccaf8 FMUL float ptr [ESI]
004ccafa FADDP
004ccafc FLD float ptr [ESP + 0x48]
004ccb00 FMUL ST1
004ccb02 FLD float ptr [ESP + 0x4c]
004ccb06 FMUL ST2
004ccb08 FSTP float ptr [ESP + 0x40]
004ccb0c FLD float ptr [ESP + 0x50]
004ccb10 FMUL ST2
004ccb12 FSTP float ptr [ESP + 0x44]
004ccb16 FLD float ptr [ESI]
004ccb18 FSUB ST0,ST1
004ccb1a FSTP float ptr [ESP + 0xc]
004ccb1e MOV ECX,dword ptr [ESP + 0xc]
004ccb22 FSTP ST0
004ccb24 FSTP ST0
004ccb26 FLD float ptr [ESI + 0x4]
004ccb29 FSUB float ptr [ESP + 0x40]
004ccb2d FSTP float ptr [ESP + 0x10]
004ccb31 FLD float ptr [ESI + 0x8]
004ccb34 FSUB float ptr [ESP + 0x44]
004ccb38 MOV EDX,dword ptr [ESP + 0x10]
004ccb3c MOV dword ptr [EAX],ECX
004ccb3e MOV dword ptr [EAX + 0x4],EDX
004ccb41 MOV EDX,dword ptr [ESP + 0x48]
004ccb45 FSTP float ptr [ESP + 0x14]
004ccb49 FLD float ptr [ESP + 0x50]
004ccb4d MOV ECX,dword ptr [ESP + 0x14]
004ccb51 MOV dword ptr [ESP + 0xc],EDX
004ccb55 FADD float ptr [0x005a83f4]
004ccb5b MOV dword ptr [EAX + 0x8],ECX
004ccb5e MOV EAX,dword ptr [ESP + 0x4c]
004ccb62 MOV ECX,EDX
004ccb64 MOV dword ptr [ESP + 0x10],EAX
004ccb68 MOV EDX,EAX
004ccb6a MOV dword ptr [ESP + 0x30],ECX
004ccb6e FSTP float ptr [ESP + 0x14]
004ccb72 MOV EAX,dword ptr [ESP + 0x14]
004ccb76 LEA ECX,[ESP + 0x30]
004ccb7a MOV dword ptr [ESP + 0x34],EDX
004ccb7e MOV dword ptr [ESP + 0x38],EAX
004ccb82 CALL 0x0047ec40
004ccb87 MOV EAX,dword ptr [ESP + 0x10c]
004ccb8e TEST EAX,EAX
004ccb90 JZ 0x004ccb9a
004ccb92 FLD float ptr [0x005aa8c0]
004ccb98 JMP 0x004ccba0
004ccb9a FLD float ptr [0x005a84c0]
004ccba0 FLD float ptr [ESP + 0x30]
004ccba4 FMUL ST1
004ccba6 FLD float ptr [ESP + 0x34]
004ccbaa FMUL ST2
004ccbac SUB EDI,0x0
004ccbaf FSTP float ptr [ESP + 0x40]
004ccbb3 FLD float ptr [ESP + 0x38]
004ccbb7 FMUL ST2
004ccbb9 FSTP float ptr [ESP + 0x44]
004ccbbd FADD float ptr [ESI]
004ccbbf FSTP float ptr [ESP + 0xc]
004ccbc3 MOV ECX,dword ptr [ESP + 0xc]
004ccbc7 FSTP ST0
004ccbc9 FLD float ptr [ESP + 0x40]
004ccbcd FADD float ptr [ESI + 0x4]
004ccbd0 FSTP float ptr [ESP + 0x10]
004ccbd4 FLD float ptr [ESP + 0x44]
004ccbd8 FADD float ptr [ESI + 0x8]
004ccbdb MOV EDX,dword ptr [ESP + 0x10]
004ccbdf MOV dword ptr [ESI],ECX
004ccbe1 MOV dword ptr [ESI + 0x4],EDX
004ccbe4 FSTP float ptr [ESP + 0x14]
004ccbe8 MOV EAX,dword ptr [ESP + 0x14]
004ccbec MOV dword ptr [ESI + 0x8],EAX
004ccbef JZ 0x004ccc43
004ccbf1 DEC EDI
004ccbf2 JZ 0x004ccc1d
004ccbf4 DEC EDI
004ccbf5 JNZ 0x004ccc58
004ccbf7 MOV EDX,dword ptr [EBX]
004ccbf9 PUSH 0xbf800000
004ccbfe PUSH 0x0
004ccc00 PUSH 0x0
004ccc02 PUSH 0xa0
004ccc07 MOV ECX,EBX
004ccc09 CALL dword ptr [EDX + 0x74]
004ccc0c POP EDI
004ccc0d POP ESI
004ccc0e MOV EAX,0x1
004ccc13 POP EBX
004ccc14 ADD ESP,0xfc
004ccc1a RET 0x4
004ccc1d MOV EAX,dword ptr [EBX]
004ccc1f PUSH 0xbf800000
004ccc24 PUSH 0x0
004ccc26 PUSH 0x0
004ccc28 PUSH 0x9f
004ccc2d MOV ECX,EBX
004ccc2f CALL dword ptr [EAX + 0x74]
004ccc32 POP EDI
004ccc33 POP ESI
004ccc34 MOV EAX,0x1
004ccc39 POP EBX
004ccc3a ADD ESP,0xfc
004ccc40 RET 0x4
004ccc43 MOV EDX,dword ptr [EBX]
004ccc45 PUSH 0xbf800000
004ccc4a PUSH 0x0
004ccc4c PUSH 0x0
004ccc4e PUSH 0x9d
004ccc53 MOV ECX,EBX
004ccc55 CALL dword ptr [EDX + 0x74]
004ccc58 POP EDI
004ccc59 POP ESI
004ccc5a MOV EAX,0x1
004ccc5f POP EBX
004ccc60 ADD ESP,0xfc
004ccc66 RET 0x4
