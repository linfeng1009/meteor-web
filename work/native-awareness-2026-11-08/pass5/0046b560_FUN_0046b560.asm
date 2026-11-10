0046b560 PUSH ESI
0046b561 PUSH EDI
0046b562 MOV EDI,dword ptr [ESP + 0xc]
0046b566 MOV ESI,ECX
0046b568 MOV EAX,EDI
0046b56a DEC EAX
0046b56b JZ 0x0046b626
0046b571 DEC EAX
0046b572 JZ 0x0046b60d
0046b578 DEC EAX
0046b579 JNZ 0x0046b675
0046b57f MOV ECX,dword ptr [ESI + 0x8]
0046b582 PUSH 0x1
0046b584 MOV EAX,dword ptr [ECX]
0046b586 CALL dword ptr [EAX + 0xc]
0046b589 MOV ECX,dword ptr [ESI + 0xc]
0046b58c PUSH 0x1
0046b58e MOV EDX,dword ptr [ECX]
0046b590 CALL dword ptr [EDX + 0xc]
0046b593 FLD float ptr [ESI + 0x14]
0046b596 FADD float ptr [ESI + 0x1c]
0046b599 FLD float ptr [0x005c7b60]
0046b59f FMUL float ptr [0x005a8dbc]
0046b5a5 SUB ESP,0x8
0046b5a8 MOV ECX,dword ptr [ESI + 0x8]
0046b5ab FSUBP
0046b5ad FSTP float ptr [ESP + 0x4]
0046b5b1 FLD float ptr [ESI + 0x18]
0046b5b4 FMUL float ptr [0x005a83e8]
0046b5ba FLD float ptr [ESI + 0x20]
0046b5bd FMUL float ptr [0x005a8db8]
0046b5c3 FSUBP
0046b5c5 FMUL float ptr [0x005a83e8]
0046b5cb FADD float ptr [ESI + 0x10]
0046b5ce FSTP float ptr [ESP]
0046b5d1 CALL 0x00463980
0046b5d6 FLD float ptr [ESI + 0x14]
0046b5d9 FADD float ptr [ESI + 0x1c]
0046b5dc FLD float ptr [0x005c7b60]
0046b5e2 FMUL float ptr [0x005a8dbc]
0046b5e8 SUB ESP,0x8
0046b5eb MOV ECX,dword ptr [ESI + 0xc]
0046b5ee FSUBP
0046b5f0 FSTP float ptr [ESP + 0x4]
0046b5f4 FLD float ptr [ESI + 0x18]
0046b5f7 FMUL float ptr [0x005a83e8]
0046b5fd FLD float ptr [ESI + 0x20]
0046b600 FMUL float ptr [0x005a8db8]
0046b606 FSUBP
0046b608 FADD float ptr [ESI + 0x18]
0046b60b JMP 0x0046b664
0046b60d MOV ECX,dword ptr [ESI + 0xc]
0046b610 PUSH 0x1
0046b612 MOV EAX,dword ptr [ECX]
0046b614 CALL dword ptr [EAX + 0xc]
0046b617 MOV ECX,dword ptr [ESI + 0x8]
0046b61a PUSH 0x0
0046b61c MOV EDX,dword ptr [ECX]
0046b61e CALL dword ptr [EDX + 0xc]
0046b621 MOV ECX,dword ptr [ESI + 0xc]
0046b624 JMP 0x0046b63d
0046b626 MOV ECX,dword ptr [ESI + 0xc]
0046b629 PUSH 0x0
0046b62b MOV EAX,dword ptr [ECX]
0046b62d CALL dword ptr [EAX + 0xc]
0046b630 MOV ECX,dword ptr [ESI + 0x8]
0046b633 PUSH 0x1
0046b635 MOV EDX,dword ptr [ECX]
0046b637 CALL dword ptr [EDX + 0xc]
0046b63a MOV ECX,dword ptr [ESI + 0x8]
0046b63d FLD float ptr [ESI + 0x1c]
0046b640 FADD float ptr [ESI + 0x14]
0046b643 FLD float ptr [0x005c7b60]
0046b649 FMUL float ptr [0x005a8dbc]
0046b64f SUB ESP,0x8
0046b652 FSUBP
0046b654 FSTP float ptr [ESP + 0x4]
0046b658 FLD float ptr [ESI + 0x20]
0046b65b FMUL float ptr [0x005a8db8]
0046b661 FSUBR float ptr [ESI + 0x18]
0046b664 FMUL float ptr [0x005a83e8]
0046b66a FADD float ptr [ESI + 0x10]
0046b66d FSTP float ptr [ESP]
0046b670 CALL 0x00463980
0046b675 MOV dword ptr [ESI + 0x54],EDI
0046b678 POP EDI
0046b679 POP ESI
0046b67a RET 0x4
