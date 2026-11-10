0057d5d0 PUSH -0x1
0057d5d2 PUSH 0x5a660b
0057d5d7 MOV EAX,FS:[0x0]
0057d5dd PUSH EAX
0057d5de MOV dword ptr FS:[0x0],ESP
0057d5e5 SUB ESP,0x10
0057d5e8 PUSH EBX
0057d5e9 PUSH EBP
0057d5ea PUSH ESI
0057d5eb MOV ESI,ECX
0057d5ed PUSH EDI
0057d5ee MOV dword ptr [ESP + 0x10],ESI
0057d5f2 LEA EDI,[ESI + 0x4c]
0057d5f5 MOV ECX,EDI
0057d5f7 CALL 0x0047bfd0
0057d5fc FLD double ptr [0x005afd10]
0057d602 FCOS
0057d604 XOR EAX,EAX
0057d606 MOV EDX,0x3f800000
0057d60b MOV ECX,0x42700000
0057d610 MOV dword ptr [ESI + 0x13c],EAX
0057d616 MOV dword ptr [ESI + 0x140],EAX
0057d61c MOV dword ptr [ESI + 0x144],EAX
0057d622 MOV dword ptr [ESI + 0x148],EAX
0057d628 MOV byte ptr [ESI + 0x14c],AL
0057d62e MOV byte ptr [ESI + 0x14d],AL
0057d634 MOV byte ptr [ESI + 0x14e],AL
0057d63a MOV dword ptr [ESI + 0x150],0x1
0057d644 MOV dword ptr [ESI + 0x154],EAX
0057d64a MOV dword ptr [ESI + 0x158],EDX
0057d650 MOV dword ptr [ESI + 0x15c],EAX
0057d656 MOV dword ptr [ESI + 0x160],0xb
0057d660 MOV dword ptr [ESI + 0x17c],ECX
0057d666 MOV dword ptr [ESI + 0x1a0],ECX
0057d66c MOV ECX,0x447a0000
0057d671 MOV dword ptr [ESI + 0x16c],EAX
0057d677 MOV dword ptr [ESI + 0x174],EAX
0057d67d MOV dword ptr [ESI + 0x170],EAX
0057d683 MOV dword ptr [ESI],EAX
0057d685 MOV dword ptr [ESI + 0x178],0x41f00000
0057d68f MOV dword ptr [ESI + 0x1a4],0x42a00000
0057d699 MOV dword ptr [ESP + 0x28],EAX
0057d69d FSTP float ptr [ESI + 0x1a8]
0057d6a3 MOV dword ptr [ESI + 0x28],ECX
0057d6a6 MOV dword ptr [ESI + 0x2c],ECX
0057d6a9 MOV dword ptr [ESI + 0x30],0x43480000
0057d6b0 MOV dword ptr [ESI + 0x168],EAX
0057d6b6 FLD float ptr [ESI + 0x30]
0057d6b9 LEA ECX,[ESI + 0x34]
0057d6bc FST float ptr [ESI + 0x164]
0057d6c2 FMUL float ptr [0x005a83e8]
0057d6c8 MOV dword ptr [ESI + 0x4],EAX
0057d6cb MOV dword ptr [ESI + 0x8],EAX
0057d6ce MOV EBX,ECX
0057d6d0 FSTP float ptr [ESI + 0xc]
0057d6d3 FLD float ptr [ESI + 0x28]
0057d6d6 FMUL float ptr [0x005a83e8]
0057d6dc FSTP float ptr [ESP + 0x14]
0057d6e0 FLD float ptr [ESI + 0x2c]
0057d6e3 FMUL float ptr [0x005a83e8]
0057d6e9 MOV EBP,dword ptr [ESP + 0x14]
0057d6ed FSTP float ptr [ESP + 0x18]
0057d6f1 FLD float ptr [ESI + 0x30]
0057d6f4 FMUL float ptr [0x005a83e8]
0057d6fa MOV dword ptr [EBX],EBP
0057d6fc MOV EBP,dword ptr [ESP + 0x18]
0057d700 MOV dword ptr [EBX + 0x4],EBP
0057d703 FSTP float ptr [ESP + 0x1c]
0057d707 MOV EBP,dword ptr [ESP + 0x1c]
0057d70b MOV dword ptr [EBX + 0x8],EBP
0057d70e LEA EBX,[ESI + 0x10]
0057d711 FLD float ptr [ESI + 0x4]
0057d714 FSUB float ptr [ECX]
0057d716 FSTP float ptr [ESP + 0x14]
0057d71a FLD float ptr [ESI + 0x8]
0057d71d FSUB float ptr [ECX + 0x4]
0057d720 MOV EBP,dword ptr [ESP + 0x14]
0057d724 FSTP float ptr [ESP + 0x18]
0057d728 FLD float ptr [ESI + 0xc]
0057d72b FSUB float ptr [ECX + 0x8]
0057d72e MOV dword ptr [EBX],EBP
0057d730 MOV EBP,dword ptr [ESP + 0x18]
0057d734 MOV dword ptr [EBX + 0x4],EBP
0057d737 FSTP float ptr [ESP + 0x1c]
0057d73b MOV EBP,dword ptr [ESP + 0x1c]
0057d73f MOV dword ptr [EBX + 0x8],EBP
0057d742 PUSH EDX
0057d743 FLD float ptr [ESI + 0x4]
0057d746 FADD float ptr [ECX]
0057d748 PUSH EDX
0057d749 PUSH EDX
0057d74a PUSH EDX
0057d74b FSTP float ptr [ESP + 0x24]
0057d74f FLD float ptr [ESI + 0x8]
0057d752 FADD float ptr [ECX + 0x4]
0057d755 MOV EBX,dword ptr [ESP + 0x24]
0057d759 FSTP float ptr [ESP + 0x28]
0057d75d FLD float ptr [ESI + 0xc]
0057d760 FADD float ptr [ECX + 0x8]
0057d763 LEA ECX,[ESI + 0x1c]
0057d766 MOV dword ptr [ESI + 0x1c],EBX
0057d769 MOV EBX,dword ptr [ESP + 0x28]
0057d76d FSTP float ptr [ESP + 0x2c]
0057d771 MOV dword ptr [ECX + 0x4],EBX
0057d774 MOV EBX,dword ptr [ESP + 0x2c]
0057d778 MOV dword ptr [ECX + 0x8],EBX
0057d77b MOV ECX,0x41000000
0057d780 MOV dword ptr [ESI + 0x18c],ECX
0057d786 MOV dword ptr [ESI + 0x188],ECX
0057d78c MOV dword ptr [ESI + 0x40],EDX
0057d78f MOV dword ptr [ESI + 0x44],EAX
0057d792 MOV dword ptr [ESI + 0x48],EAX
0057d795 FLD float ptr [ESI + 0x40]
0057d798 FMUL float ptr [0x005a83e4]
0057d79e FSTP float ptr [ESP + 0x24]
0057d7a2 FLD float ptr [ESI + 0x44]
0057d7a5 FMUL float ptr [0x005a83e4]
0057d7ab MOV ECX,dword ptr [ESP + 0x24]
0057d7af FSTP float ptr [ESP + 0x28]
0057d7b3 FLD float ptr [ESI + 0x48]
0057d7b6 FMUL float ptr [0x005a83e4]
0057d7bc MOV dword ptr [ESI + 0x40],ECX
0057d7bf MOV ECX,dword ptr [ESP + 0x28]
0057d7c3 MOV dword ptr [ESI + 0x44],ECX
0057d7c6 FSTP float ptr [ESP + 0x2c]
0057d7ca MOV ECX,dword ptr [ESP + 0x2c]
0057d7ce MOV dword ptr [ESI + 0x48],ECX
0057d7d1 MOV dword ptr [ESI + 0x1e0],EAX
0057d7d7 MOV dword ptr [ESI + 0x1e4],EDX
0057d7dd MOV dword ptr [ESI + 0x1e8],EAX
0057d7e3 MOV dword ptr [ESI + 0x1f8],EDX
0057d7e9 MOV dword ptr [ESI + 0x1fc],EAX
0057d7ef MOV dword ptr [ESI + 0x200],EAX
0057d7f5 MOV dword ptr [ESI + 0x1ec],EAX
0057d7fb MOV dword ptr [ESI + 0x1f0],EAX
0057d801 MOV dword ptr [ESI + 0x1f4],EDX
0057d807 MOV byte ptr [ESI + 0x1b1],AL
0057d80d MOV ECX,0xbf800000
0057d812 MOV AL,0x1
0057d814 MOV dword ptr [ESI + 0x190],0x3f000000
0057d81e MOV dword ptr [ESI + 0x180],0x3d4ccccd
0057d828 MOV dword ptr [ESI + 0x184],0x3e4ccccd
0057d832 MOV dword ptr [ESI + 0x194],ECX
0057d838 MOV dword ptr [ESI + 0x198],ECX
0057d83e MOV byte ptr [ESI + 0x1b0],AL
0057d844 MOV byte ptr [ESI + 0x14c],AL
0057d84a CALL 0x00475c00
0057d84f ADD ESP,0x10
0057d852 MOV ECX,EDI
0057d854 MOV dword ptr [ESI + 0x1ac],EAX
0057d85a PUSH 0x4
0057d85c CALL 0x0047c140
0057d861 MOV ECX,dword ptr [ESP + 0x20]
0057d865 MOV EAX,ESI
0057d867 POP EDI
0057d868 POP ESI
0057d869 POP EBP
0057d86a POP EBX
0057d86b MOV dword ptr FS:[0x0],ECX
0057d872 ADD ESP,0x1c
0057d875 RET
