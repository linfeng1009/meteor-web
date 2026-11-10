004fcc10 SUB ESP,0x30
004fcc13 PUSH ESI
004fcc14 MOV ESI,ECX
004fcc16 MOV ECX,dword ptr [ESI + 0xc]
004fcc19 CALL 0x00501030
004fcc1e TEST AL,AL
004fcc20 JNZ 0x004fcc29
004fcc22 POP ESI
004fcc23 ADD ESP,0x30
004fcc26 RET 0x8
004fcc29 LEA EAX,[ESI + 0x18]
004fcc2c PUSH EBP
004fcc2d MOV EDX,EAX
004fcc2f PUSH EDI
004fcc30 MOV EAX,dword ptr [EDX]
004fcc32 MOV dword ptr [ESP + 0xc],EAX
004fcc36 MOV ECX,dword ptr [EDX + 0x4]
004fcc39 MOV dword ptr [ESP + 0x10],ECX
004fcc3d MOV EDI,dword ptr [EDX + 0x8]
004fcc40 MOVSX EDX,byte ptr [ESP + 0x40]
004fcc45 MOV dword ptr [ESP + 0x14],EDI
004fcc49 LEA EBP,[EDX + -0x62]
004fcc4c CMP EBP,0x10
004fcc4f JA 0x004fcd61
004fcc55 XOR EDX,EDX
004fcc57 MOV DL,byte ptr [EBP + 0x4fcdc0]
004fcc5d JMP dword ptr [EDX*0x4 + 0x4fcdac]
004fcc64 FLD float ptr [ESP + 0x44]
004fcc68 FMUL float ptr [ESI + 0x24]
004fcc6b FLD float ptr [ESP + 0x44]
004fcc6f FMUL float ptr [ESI + 0x28]
004fcc72 FLD float ptr [ESP + 0x44]
004fcc76 FMUL float ptr [ESI + 0x2c]
004fcc79 FSTP float ptr [ESP + 0x38]
004fcc7d FLD float ptr [ESP + 0xc]
004fcc81 FADD ST0,ST2
004fcc83 FSTP float ptr [ESP + 0x18]
004fcc87 FLD float ptr [ESP + 0x10]
004fcc8b FADD ST0,ST1
004fcc8d FSTP float ptr [ESP + 0x1c]
004fcc91 FSTP ST0
004fcc93 JMP 0x004fcd3b
004fcc98 FLD float ptr [ESP + 0x44]
004fcc9c FMUL float ptr [ESI + 0x24]
004fcc9f FLD float ptr [ESP + 0x44]
004fcca3 FMUL float ptr [ESI + 0x28]
004fcca6 FLD float ptr [ESP + 0x44]
004fccaa FMUL float ptr [ESI + 0x2c]
004fccad FSTP float ptr [ESP + 0x38]
004fccb1 FLD float ptr [ESP + 0xc]
004fccb5 FSUB ST0,ST2
004fccb7 FSTP float ptr [ESP + 0x18]
004fccbb FLD float ptr [ESP + 0x10]
004fccbf FSUB ST0,ST1
004fccc1 FSTP float ptr [ESP + 0x1c]
004fccc5 FSTP ST0
004fccc7 FSTP ST0
004fccc9 FLD float ptr [ESP + 0x14]
004fcccd FSUB float ptr [ESP + 0x38]
004fccd1 JMP 0x004fcd45
004fccd3 FLD float ptr [ESP + 0x44]
004fccd7 FMUL float ptr [ESI + 0x30]
004fccda FLD float ptr [ESP + 0x44]
004fccde FMUL float ptr [ESI + 0x34]
004fcce1 FLD float ptr [ESP + 0x44]
004fcce5 FMUL float ptr [ESI + 0x38]
004fcce8 FSTP float ptr [ESP + 0x38]
004fccec FLD float ptr [ESP + 0xc]
004fccf0 FSUB ST0,ST2
004fccf2 FSTP float ptr [ESP + 0x18]
004fccf6 FLD float ptr [ESP + 0x10]
004fccfa FSUB ST0,ST1
004fccfc FSTP float ptr [ESP + 0x1c]
004fcd00 FSTP ST0
004fcd02 FSTP ST0
004fcd04 FLD float ptr [ESP + 0x14]
004fcd08 FSUB float ptr [ESP + 0x38]
004fcd0c JMP 0x004fcd45
004fcd0e FLD float ptr [ESP + 0x44]
004fcd12 FMUL float ptr [ESI + 0x30]
004fcd15 FLD float ptr [ESP + 0x44]
004fcd19 FMUL float ptr [ESI + 0x34]
004fcd1c FLD float ptr [ESP + 0x44]
004fcd20 FMUL float ptr [ESI + 0x38]
004fcd23 FSTP float ptr [ESP + 0x38]
004fcd27 FXCH
004fcd29 FADD float ptr [ESP + 0xc]
004fcd2d FSTP float ptr [ESP + 0x18]
004fcd31 FLD float ptr [ESP + 0x10]
004fcd35 FADD ST0,ST1
004fcd37 FSTP float ptr [ESP + 0x1c]
004fcd3b FSTP ST0
004fcd3d FLD float ptr [ESP + 0x38]
004fcd41 FADD float ptr [ESP + 0x14]
004fcd45 FSTP float ptr [ESP + 0x20]
004fcd49 MOV EAX,dword ptr [ESP + 0x18]
004fcd4d MOV ECX,dword ptr [ESP + 0x1c]
004fcd51 MOV EDI,dword ptr [ESP + 0x20]
004fcd55 MOV dword ptr [ESP + 0xc],EAX
004fcd59 MOV dword ptr [ESP + 0x10],ECX
004fcd5d MOV dword ptr [ESP + 0x14],EDI
004fcd61 FLD float ptr [ESP + 0x14]
004fcd65 FADD float ptr [0x005a8e78]
004fcd6b MOV dword ptr [ESP + 0x2c],EDI
004fcd6f MOV dword ptr [ESP + 0x24],EAX
004fcd73 MOV dword ptr [ESP + 0x28],ECX
004fcd77 PUSH 0x0
004fcd79 LEA EAX,[ESP + 0x28]
004fcd7d PUSH 0x0
004fcd7f FSTP float ptr [ESP + 0x1c]
004fcd83 FLD float ptr [ESP + 0x34]
004fcd87 FSUB float ptr [0x005a8b08]
004fcd8d LEA ECX,[ESP + 0x14]
004fcd91 PUSH EAX
004fcd92 PUSH ECX
004fcd93 MOV ECX,dword ptr [0x0066629c]
004fcd99 FSTP float ptr [ESP + 0x3c]
004fcd9d CALL 0x004c1360
004fcda2 POP EDI
004fcda3 POP EBP
004fcda4 POP ESI
004fcda5 ADD ESP,0x30
004fcda8 RET 0x8
