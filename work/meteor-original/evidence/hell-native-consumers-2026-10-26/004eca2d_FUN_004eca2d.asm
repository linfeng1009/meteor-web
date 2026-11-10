004ec9c7 CMP dword ptr [ESI + 0x200],0x1
004ec9ce JNZ 0x004eca99
004ec9d4 MOV ECX,dword ptr [ESI + 0xd0]
004ec9da MOV EDX,dword ptr [ESI + 0xcc]
004ec9e0 SUB ECX,EDX
004ec9e2 MOV EAX,0x38e38e39
004ec9e7 IMUL ECX
004ec9e9 SAR EDX,0x4
004ec9ec MOV EAX,EDX
004ec9ee SHR EAX,0x1f
004ec9f1 ADD EDX,EAX
004ec9f3 JZ 0x004eca99
004ec9f9 CALL 0x00487830
004ec9fe MOV ECX,dword ptr [ESI + 0x10]
004eca01 MOV EDX,dword ptr [EAX]
004eca03 PUSH ECX
004eca04 MOV ECX,EAX
004eca06 CALL dword ptr [EDX + 0x12c]
004eca0c TEST EAX,EAX
004eca0e JZ 0x004eca99
004eca14 LEA EDI,[EAX + 0xfffff9a4]
004eca1a TEST EDI,EDI
004eca1c JZ 0x004eca99
004eca1e CALL 0x00487830
004eca23 MOV EDX,dword ptr [EAX]
004eca25 LEA ECX,[ESP + 0x10]
004eca29 PUSH EDI
004eca2a PUSH ECX
004eca2b MOV ECX,EAX
004eca2d CALL dword ptr [EDX + 0xd8]
004eca33 MOV EAX,dword ptr [ESP + 0x10]
004eca37 SUB EAX,0x6
004eca3a JZ 0x004eca7a
004eca3c DEC EAX
004eca3d JZ 0x004eca64
004eca3f DEC EAX
004eca40 JNZ 0x004eca99
004eca42 CMP dword ptr [ESI + 0x208],0x1
004eca49 JNZ 0x004eca53
004eca4b MOV EAX,dword ptr [EBX + 0x58]
004eca4e OR AL,0x4
004eca50 MOV dword ptr [EBX + 0x58],EAX
004eca53 CMP dword ptr [ESI + 0x208],EBP
004eca59 JNZ 0x004eca5e
004eca5b OR dword ptr [EBX + 0x58],EBP
004eca5e MOV EDX,dword ptr [ESI + 0x10]
004eca61 PUSH EDX
004eca62 JMP 0x004eca90
004eca64 CMP dword ptr [ESI + 0x208],EBP
004eca6a JNZ 0x004eca99
004eca6c MOV EDX,dword ptr [EBX + 0x58]
004eca6f OR EDX,EBP
004eca71 MOV dword ptr [EBX + 0x58],EDX
004eca74 MOV EAX,dword ptr [ESI + 0x10]
004eca77 PUSH EAX
004eca78 JMP 0x004eca90
004eca7a CMP dword ptr [ESI + 0x208],0x1
004eca81 JNZ 0x004eca99
004eca83 MOV ECX,dword ptr [EBX + 0x58]
004eca86 OR ECX,0x4
004eca89 MOV dword ptr [EBX + 0x58],ECX
004eca8c MOV ECX,dword ptr [ESI + 0x10]
004eca8f PUSH ECX
004eca90 LEA ECX,[ESP + 0x14]
004eca94 CALL 0x005603b0
004eca99 MOV EAX,dword ptr [ESI + 0xc]
004eca9c TEST EAX,EAX
004eca9e JZ 0x004ecab4
004ecaa0 MOV ESI,EAX
004ecaa2 MOV EAX,dword ptr [ESI + 0x8]
004ecaa5 TEST EAX,EAX
004ecaa7 JZ 0x004ecacd
004ecaa9 MOV ESI,EAX
004ecaab MOV EAX,dword ptr [ESI + 0x8]
004ecaae TEST EAX,EAX
004ecab0 JNZ 0x004ecaa9
004ecab2 JMP 0x004ecacd
004ecab4 MOV EAX,dword ptr [ESI + 0x4]
004ecab7 CMP ESI,dword ptr [EAX + 0xc]
004ecaba JNZ 0x004ecac6
004ecabc MOV ESI,EAX
004ecabe MOV EAX,dword ptr [EAX + 0x4]
004ecac1 CMP ESI,dword ptr [EAX + 0xc]
004ecac4 JZ 0x004ecabc
004ecac6 CMP dword ptr [ESI + 0xc],EAX
004ecac9 JZ 0x004ecacd
004ecacb MOV ESI,EAX
004ecacd MOV EDX,dword ptr [ESP + 0x20]
004ecad1 CMP ESI,dword ptr [EDX + 0x3a8]
004ecad7 JNZ 0x004ec9c7
004ecadd POP EDI
004ecade POP EBP
004ecadf POP ESI
004ecae0 POP EBX
004ecae1 ADD ESP,0xc
004ecae4 RET 0x4
