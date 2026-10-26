004aa370 PUSH ECX
004aa371 MOV EAX,dword ptr [ESP + 0x8]
004aa375 PUSH ESI
004aa376 LEA ESI,[ECX + 0x4]
004aa379 LEA ECX,[ESP + 0x4]
004aa37d LEA EDX,[ESP + 0xc]
004aa381 PUSH ECX
004aa382 PUSH EDX
004aa383 MOV ECX,ESI
004aa385 MOV dword ptr [ESP + 0xc],EAX
004aa389 CALL 0x0049d3c0
004aa38e MOV EAX,dword ptr [ESP + 0xc]
004aa392 MOV ECX,dword ptr [ESI]
004aa394 CMP EAX,ECX
004aa396 JZ 0x004aa4f3
004aa39c MOV ECX,dword ptr [EAX + 0xdc]
004aa3a2 MOV ESI,0x1
004aa3a7 CMP ECX,ESI
004aa3a9 JZ 0x004aa3cf
004aa3ab LEA ECX,[EAX + 0x18]
004aa3ae ADD EAX,0x30
004aa3b1 MOV EDX,dword ptr [ECX]
004aa3b3 MOV dword ptr [EAX],EDX
004aa3b5 MOV EDX,dword ptr [ECX + 0x4]
004aa3b8 MOV dword ptr [EAX + 0x4],EDX
004aa3bb MOV ECX,dword ptr [ECX + 0x8]
004aa3be MOV dword ptr [EAX + 0x8],ECX
004aa3c1 MOV EDX,dword ptr [ESP + 0xc]
004aa3c5 MOV dword ptr [EDX + 0xdc],ESI
004aa3cb MOV EAX,dword ptr [ESP + 0xc]
004aa3cf LEA ECX,[EAX + 0x18]
004aa3d2 MOV EAX,dword ptr [ESP + 0x10]
004aa3d6 PUSH EDI
004aa3d7 MOVSX EDX,word ptr [EAX]
004aa3da MOV dword ptr [ESP + 0x14],EDX
004aa3de ADD EAX,0x2
004aa3e1 FILD dword ptr [ESP + 0x14]
004aa3e5 ADD EAX,0x2
004aa3e8 ADD EAX,0x2
004aa3eb FMUL float ptr [0x005a83ec]
004aa3f1 ADD EAX,0x2
004aa3f4 ADD EAX,0x2
004aa3f7 ADD EAX,0x2
004aa3fa FST float ptr [ECX]
004aa3fc FSTP float ptr [ECX + 0x24]
004aa3ff MOVSX EDX,word ptr [EAX + -0xa]
004aa403 MOV dword ptr [ESP + 0x14],EDX
004aa407 ADD EAX,0x2
004aa40a FILD dword ptr [ESP + 0x14]
004aa40e ADD EAX,0x2
004aa411 FMUL float ptr [0x005a83ec]
004aa417 FST float ptr [ECX + 0x4]
004aa41a FSTP float ptr [ECX + 0x28]
004aa41d MOVSX EDX,word ptr [EAX + -0xc]
004aa421 MOV dword ptr [ESP + 0x14],EDX
004aa425 FILD dword ptr [ESP + 0x14]
004aa429 FMUL float ptr [0x005a83ec]
004aa42f FST float ptr [ECX + 0x8]
004aa432 FSTP float ptr [ECX + 0x2c]
004aa435 MOVSX EDX,word ptr [EAX + -0xa]
004aa439 MOV dword ptr [ESP + 0x14],EDX
004aa43d FILD dword ptr [ESP + 0x14]
004aa441 FMUL float ptr [0x005a8414]
004aa447 FSTP float ptr [ECX + 0xc]
004aa44a MOVSX EDX,word ptr [EAX + -0x8]
004aa44e MOV dword ptr [ESP + 0x14],EDX
004aa452 XOR EDX,EDX
004aa454 FILD dword ptr [ESP + 0x14]
004aa458 MOV dword ptr [ECX + 0x14],EDX
004aa45b FMUL float ptr [0x005a8414]
004aa461 FSTP float ptr [ECX + 0x10]
004aa464 MOVSX EDI,word ptr [EAX + -0x6]
004aa468 MOV dword ptr [ESP + 0x14],EDI
004aa46c FILD dword ptr [ESP + 0x14]
004aa470 FMUL float ptr [0x005a9bcc]
004aa476 FSTP float ptr [ECX + 0x30]
004aa479 MOVSX EDI,word ptr [EAX + -0x4]
004aa47d MOV dword ptr [ESP + 0x14],EDI
004aa481 FILD dword ptr [ESP + 0x14]
004aa485 FMUL float ptr [0x005a9bcc]
004aa48b FSTP float ptr [ECX + 0x34]
004aa48e MOVSX EDI,word ptr [EAX + -0x2]
004aa492 MOV dword ptr [ESP + 0x14],EDI
004aa496 FILD dword ptr [ESP + 0x14]
004aa49a FMUL float ptr [0x005a9bcc]
004aa4a0 FSTP float ptr [ECX + 0x38]
004aa4a3 MOVSX EDI,word ptr [EAX]
004aa4a6 MOV dword ptr [ECX + 0x3c],EDI
004aa4a9 XOR EDI,EDI
004aa4ab MOV DI,word ptr [EAX + 0x2]
004aa4af MOV dword ptr [ECX + 0x40],EDI
004aa4b2 MOV EAX,dword ptr [ESP + 0x10]
004aa4b6 MOV EDI,dword ptr [EAX + 0x250]
004aa4bc INC EDI
004aa4bd MOV dword ptr [EAX + 0x250],EDI
004aa4c3 MOV EAX,dword ptr [ESP + 0x10]
004aa4c7 POP EDI
004aa4c8 CMP dword ptr [EAX + 0x200],ESI
004aa4ce JNZ 0x004aa4da
004aa4d0 MOV dword ptr [EAX + 0x210],EDX
004aa4d6 MOV EAX,dword ptr [ESP + 0xc]
004aa4da MOV ECX,dword ptr [EAX + 0x54]
004aa4dd TEST CH,0x10
004aa4e0 JZ 0x004aa4ed
004aa4e2 MOV dword ptr [EAX + 0x20c],ESI
004aa4e8 POP ESI
004aa4e9 POP ECX
004aa4ea RET 0xc
004aa4ed MOV dword ptr [EAX + 0x20c],EDX
004aa4f3 POP ESI
004aa4f4 POP ECX
004aa4f5 RET 0xc
