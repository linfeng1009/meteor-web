004cfb00 SUB ESP,0x8
004cfb03 PUSH EBX
004cfb04 PUSH ESI
004cfb05 MOV ESI,ECX
004cfb07 PUSH EDI
004cfb08 MOV EAX,dword ptr [ESI]
004cfb0a CALL dword ptr [EAX + 0x94]
004cfb10 MOV EDI,EAX
004cfb12 TEST EDI,EDI
004cfb14 JZ 0x004cfbc9
004cfb1a MOV EBX,dword ptr [ESP + 0x18]
004cfb1e MOV EDX,dword ptr [ESI]
004cfb20 PUSH EBX
004cfb21 MOV ECX,ESI
004cfb23 CALL dword ptr [EDX + 0x1a0]
004cfb29 MOV EAX,dword ptr [ESP + 0x20]
004cfb2d TEST EAX,EAX
004cfb2f JZ 0x004cfb43
004cfb31 MOV EAX,dword ptr [ESI]
004cfb33 MOV ECX,ESI
004cfb35 CALL dword ptr [EAX + 0x134]
004cfb3b CMP EAX,EBX
004cfb3d JZ 0x004cfbc9
004cfb43 MOV ECX,EDI
004cfb45 CALL 0x0055de10
004cfb4a MOV ECX,dword ptr [ESP + 0x24]
004cfb4e MOV EDI,dword ptr [ESP + 0x1c]
004cfb52 MOV EDX,dword ptr [ESI]
004cfb54 LEA EAX,[ESP + 0x18]
004cfb58 PUSH EAX
004cfb59 PUSH ECX
004cfb5a PUSH EDI
004cfb5b PUSH EBX
004cfb5c MOV ECX,ESI
004cfb5e MOV dword ptr [ESP + 0x28],0x0
004cfb66 CALL dword ptr [EDX + 0x58]
004cfb69 MOV ECX,dword ptr [ESI + 0x348]
004cfb6f PUSH ESI
004cfb70 MOV EDX,dword ptr [ECX]
004cfb72 CALL dword ptr [EDX + 0x6c]
004cfb75 FLD float ptr [ESP + 0x18]
004cfb79 FMUL float ptr [0x005a8f7c]
004cfb7f SHL EDI,0x8
004cfb82 OR EDI,EBX
004cfb84 FADD double ptr [0x005a8460]
004cfb8a MOV dword ptr [ESP + 0xc],EDI
004cfb8e CALL 0x00509980
004cfb93 FLD float ptr [ESP + 0x24]
004cfb97 FADD float ptr [0x005a8b80]
004cfb9d MOV EDI,EAX
004cfb9f SHL EDI,0x8
004cfba2 FMUL float ptr [0x005a84c8]
004cfba8 FADD float ptr [0x005a83e8]
004cfbae CALL 0x00509980
004cfbb3 LEA ECX,[ESP + 0xc]
004cfbb7 OR EDI,EAX
004cfbb9 MOV EAX,dword ptr [ESI]
004cfbbb PUSH 0x8
004cfbbd PUSH ECX
004cfbbe PUSH 0x4
004cfbc0 MOV ECX,ESI
004cfbc2 MOV dword ptr [ESP + 0x1c],EDI
004cfbc6 CALL dword ptr [EAX + 0xc]
004cfbc9 POP EDI
004cfbca POP ESI
004cfbcb POP EBX
004cfbcc ADD ESP,0x8
004cfbcf RET 0x10
