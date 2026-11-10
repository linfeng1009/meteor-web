004fc2b0 SUB ESP,0x50
004fc2b3 PUSH EBX
004fc2b4 PUSH EBP
004fc2b5 PUSH ESI
004fc2b6 MOV EBX,ECX
004fc2b8 MOV ECX,dword ptr [0x0066629c]
004fc2be PUSH EDI
004fc2bf CALL 0x004c3830
004fc2c4 MOV EBP,EAX
004fc2c6 TEST EBP,EBP
004fc2c8 MOV dword ptr [ESP + 0x14],EBP
004fc2cc JZ 0x004fc455
004fc2d2 MOV EAX,dword ptr [EBX + 0x10]
004fc2d5 MOVSX ECX,word ptr [EAX]
004fc2d8 MOV dword ptr [ESP + 0x10],ECX
004fc2dc FILD dword ptr [ESP + 0x10]
004fc2e0 FMUL float ptr [0x005a83e8]
004fc2e6 FCOM float ptr [ESP + 0x64]
004fc2ea FNSTSW AX
004fc2ec AND EAX,0x4100
004fc2f1 JNZ 0x004fc2f9
004fc2f3 FSTP ST0
004fc2f5 FLD float ptr [ESP + 0x64]
004fc2f9 FLD ST0
004fc2fb FMUL ST1
004fc2fd LEA EDX,[EBX + 0x18]
004fc300 XOR EDI,EDI
004fc302 TEST EBP,EBP
004fc304 MOV EAX,dword ptr [EDX]
004fc306 FSTP float ptr [ESP + 0x64]
004fc30a MOV ECX,dword ptr [EDX + 0x4]
004fc30d MOV dword ptr [ESP + 0x24],EAX
004fc311 FSTP ST0
004fc313 MOV EDX,dword ptr [EDX + 0x8]
004fc316 MOV dword ptr [ESP + 0x28],ECX
004fc31a FLD float ptr [0x005ab844]
004fc320 MOV dword ptr [ESP + 0x2c],EDX
004fc324 FADD float ptr [ESP + 0x2c]
004fc328 FSTP float ptr [ESP + 0x2c]
004fc32c JLE 0x004fc455
004fc332 MOV ECX,dword ptr [0x0066629c]
004fc338 PUSH EDI
004fc339 CALL 0x004c3840
004fc33e MOV ESI,EAX
004fc340 TEST ESI,ESI
004fc342 JZ 0x004fc44c
004fc348 MOV AL,byte ptr [ESI + 0x8]
004fc34b TEST AL,AL
004fc34d JZ 0x004fc44c
004fc353 CMP dword ptr [ESI],0xf
004fc356 JNZ 0x004fc44c
004fc35c MOV EAX,dword ptr [ESI + 0x2c]
004fc35f TEST EAX,EAX
004fc361 JZ 0x004fc44c
004fc367 CMP EDI,dword ptr [EBX + 0xe4]
004fc36d JZ 0x004fc44c
004fc373 FLD float ptr [ESI + 0x48]
004fc376 FADD float ptr [ESI + 0x54]
004fc379 FLD float ptr [ESI + 0x4c]
004fc37c FADD float ptr [ESI + 0x58]
004fc37f FLD float ptr [ESI + 0x50]
004fc382 FADD float ptr [ESI + 0x5c]
004fc385 FSTP float ptr [ESP + 0x5c]
004fc389 FXCH
004fc38b FMUL float ptr [0x005a83e8]
004fc391 FSTP float ptr [ESP + 0x30]
004fc395 MOV EAX,dword ptr [ESP + 0x30]
004fc399 FMUL float ptr [0x005a83e8]
004fc39f MOV dword ptr [ESP + 0x18],EAX
004fc3a3 FSTP float ptr [ESP + 0x34]
004fc3a7 FLD float ptr [ESP + 0x5c]
004fc3ab FMUL float ptr [0x005a83e8]
004fc3b1 MOV ECX,dword ptr [ESP + 0x34]
004fc3b5 MOV dword ptr [ESP + 0x1c],ECX
004fc3b9 FSTP float ptr [ESP + 0x38]
004fc3bd FLD float ptr [0x005ab844]
004fc3c3 FMUL float ptr [0x005a83e8]
004fc3c9 MOV EDX,dword ptr [ESP + 0x38]
004fc3cd MOV dword ptr [ESP + 0x20],EDX
004fc3d1 FADD float ptr [ESP + 0x38]
004fc3d5 FSTP float ptr [ESP + 0x20]
004fc3d9 FLD float ptr [ESP + 0x24]
004fc3dd FSUB float ptr [ESP + 0x18]
004fc3e1 FSTP float ptr [ESP + 0x3c]
004fc3e5 FLD float ptr [ESP + 0x28]
004fc3e9 FSUB float ptr [ESP + 0x1c]
004fc3ed MOV EAX,dword ptr [ESP + 0x3c]
004fc3f1 MOV dword ptr [ESP + 0x48],EAX
004fc3f5 FSTP float ptr [ESP + 0x40]
004fc3f9 FLD float ptr [ESP + 0x2c]
004fc3fd FSUB float ptr [ESP + 0x20]
004fc401 MOV ECX,dword ptr [ESP + 0x40]
004fc405 MOV dword ptr [ESP + 0x4c],ECX
004fc409 LEA ECX,[ESP + 0x48]
004fc40d FSTP float ptr [ESP + 0x44]
004fc411 MOV EDX,dword ptr [ESP + 0x44]
004fc415 MOV dword ptr [ESP + 0x50],EDX
004fc419 CALL 0x0047ed20
004fc41e FCOMP float ptr [ESP + 0x64]
004fc422 FNSTSW AX
004fc424 AND EAX,0x4100
004fc429 JZ 0x004fc44c
004fc42b PUSH 0x0
004fc42d LEA EAX,[ESP + 0x1c]
004fc431 PUSH 0x0
004fc433 LEA ECX,[ESP + 0x2c]
004fc437 PUSH EAX
004fc438 PUSH ECX
004fc439 MOV ECX,dword ptr [0x0066629c]
004fc43f CALL 0x004c1360
004fc444 TEST AL,AL
004fc446 JZ 0x004fc461
004fc448 MOV EBP,dword ptr [ESP + 0x14]
004fc44c INC EDI
004fc44d CMP EDI,EBP
004fc44f JL 0x004fc332
004fc455 POP EDI
004fc456 POP ESI
004fc457 POP EBP
004fc458 XOR AL,AL
004fc45a POP EBX
004fc45b ADD ESP,0x50
004fc45e RET 0x4
004fc461 MOV EAX,dword ptr [ESP + 0x18]
004fc465 MOV ECX,dword ptr [ESP + 0x1c]
004fc469 LEA EDX,[EBX + 0xe8]
004fc46f PUSH 0x0
004fc471 MOV dword ptr [EDX],EAX
004fc473 MOV EAX,dword ptr [ESP + 0x24]
004fc477 MOV dword ptr [EDX + 0x4],ECX
004fc47a MOV dword ptr [EDX + 0x8],EAX
004fc47d MOV ECX,dword ptr [ESI + 0x2c]
004fc480 CALL 0x005679d0
004fc485 MOV dword ptr [EBX + 0xf4],EAX
004fc48b MOV ECX,dword ptr [ESI + 0x2c]
004fc48e PUSH 0x1
004fc490 CALL 0x005679d0
004fc495 MOV dword ptr [EBX + 0xe4],EDI
004fc49b POP EDI
004fc49c POP ESI
004fc49d MOV dword ptr [EBX + 0xf8],EAX
004fc4a3 POP EBP
004fc4a4 MOV AL,0x1
004fc4a6 POP EBX
004fc4a7 ADD ESP,0x50
004fc4aa RET 0x4
