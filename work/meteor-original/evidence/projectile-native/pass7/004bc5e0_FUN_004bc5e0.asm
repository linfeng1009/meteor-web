004bc5e0 SUB ESP,0x48
004bc5e3 PUSH EBX
004bc5e4 PUSH ESI
004bc5e5 PUSH EDI
004bc5e6 MOV EDI,ECX
004bc5e8 LEA EAX,[ESP + 0x30]
004bc5ec PUSH 0x0
004bc5ee LEA ECX,[ESP + 0x28]
004bc5f2 PUSH EAX
004bc5f3 PUSH ECX
004bc5f4 CALL 0x00410ce0
004bc5f9 PUSH EAX
004bc5fa CALL 0x00407c10
004bc5ff FLD float ptr [ESP + 0x34]
004bc603 MOV EAX,dword ptr [ESP + 0x68]
004bc607 MOV ESI,dword ptr [ESP + 0x6c]
004bc60b FLD ST0
004bc60d MOV EDX,ESI
004bc60f ADD ESP,0x10
004bc612 FSTP float ptr [EAX]
004bc614 FLD float ptr [ESP + 0x28]
004bc618 FST float ptr [EAX + 0x4]
004bc61b FLD float ptr [ESP + 0x2c]
004bc61f FST float ptr [ESP + 0x58]
004bc623 FSTP float ptr [EAX + 0x8]
004bc626 FLD float ptr [ESP + 0x30]
004bc62a FSTP float ptr [ESP + 0xc]
004bc62e FLD float ptr [ESP + 0x34]
004bc632 FSTP float ptr [ESP + 0x10]
004bc636 FLD float ptr [ESP + 0x38]
004bc63a FSTP float ptr [ESP + 0x14]
004bc63e FLD float ptr [ESP + 0xc]
004bc642 FMUL float ptr [0x005a9bac]
004bc648 FLD float ptr [ESP + 0x10]
004bc64c FMUL float ptr [0x005a9bac]
004bc652 FSTP float ptr [ESP + 0x40]
004bc656 FLD float ptr [ESP + 0x14]
004bc65a FMUL float ptr [0x005a9bac]
004bc660 FSTP float ptr [ESP + 0x44]
004bc664 FXCH ST2
004bc666 FADD ST0,ST2
004bc668 FSTP float ptr [ESP + 0x18]
004bc66c MOV ECX,dword ptr [ESP + 0x18]
004bc670 FSTP ST1
004bc672 FADD float ptr [ESP + 0x40]
004bc676 MOV dword ptr [EDX],ECX
004bc678 FSTP float ptr [ESP + 0x1c]
004bc67c FLD float ptr [ESP + 0x58]
004bc680 FADD float ptr [ESP + 0x44]
004bc684 MOV ECX,dword ptr [ESP + 0x1c]
004bc688 MOV dword ptr [EDX + 0x4],ECX
004bc68b FSTP float ptr [ESP + 0x20]
004bc68f MOV ECX,dword ptr [ESP + 0x20]
004bc693 MOV dword ptr [EDX + 0x8],ECX
004bc696 LEA EDX,[ESP + 0x48]
004bc69a LEA ECX,[ESP + 0xc]
004bc69e PUSH EDX
004bc69f PUSH ECX
004bc6a0 PUSH EAX
004bc6a1 CALL 0x00487830
004bc6a6 MOV ECX,EAX
004bc6a8 ADD ECX,0x20
004bc6ab CALL 0x00564920
004bc6b0 TEST EAX,EAX
004bc6b2 JZ 0x004bc6e6
004bc6b4 MOV EAX,dword ptr [ESP + 0x48]
004bc6b8 MOV ECX,dword ptr [ESP + 0x4c]
004bc6bc MOV EDX,dword ptr [ESP + 0x50]
004bc6c0 PUSH 0x0
004bc6c2 SUB ESP,0xc
004bc6c5 MOV dword ptr [ESI],EAX
004bc6c7 MOV EBX,ESP
004bc6c9 MOV dword ptr [ESI + 0x4],ECX
004bc6cc MOV dword ptr [ESI + 0x8],EDX
004bc6cf MOV ESI,dword ptr [EDI]
004bc6d1 MOV dword ptr [EBX],EAX
004bc6d3 PUSH 0x5c9a5c
004bc6d8 MOV dword ptr [EBX + 0x4],ECX
004bc6db MOV ECX,EDI
004bc6dd MOV dword ptr [EBX + 0x8],EDX
004bc6e0 CALL dword ptr [ESI + 0x140]
004bc6e6 POP EDI
004bc6e7 POP ESI
004bc6e8 MOV EAX,0x1
004bc6ed POP EBX
004bc6ee ADD ESP,0x48
004bc6f1 RET 0x8
