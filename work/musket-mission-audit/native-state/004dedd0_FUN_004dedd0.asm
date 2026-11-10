004dedd0 PUSH ESI
004dedd1 MOV ESI,dword ptr [ESP + 0x8]
004dedd5 PUSH EDI
004dedd6 PUSH ESI
004dedd7 CALL 0x004dd0a0
004deddc MOV EDI,EAX
004dedde MOV EAX,dword ptr [ESI + 0x370]
004dede4 CMP EAX,0x1
004dede7 JNZ 0x004dee2d
004dede9 MOV EAX,dword ptr [ESI]
004dedeb MOV ECX,ESI
004deded CALL dword ptr [EAX + 0x94]
004dedf3 MOV ECX,EAX
004dedf5 CALL 0x0055ddd0
004dedfa TEST EAX,EAX
004dedfc JZ 0x004dee2d
004dedfe MOV EDX,dword ptr [ESI]
004dee00 MOV ECX,ESI
004dee02 CALL dword ptr [EDX + 0x94]
004dee08 MOV ECX,EAX
004dee0a CALL 0x0055c4e0
004dee0f LEA ECX,[ESP + 0xc]
004dee13 MOV dword ptr [ESP + 0xc],EAX
004dee17 MOV EAX,dword ptr [ESI]
004dee19 PUSH 0x4
004dee1b PUSH ECX
004dee1c PUSH 0xa
004dee1e MOV ECX,ESI
004dee20 CALL dword ptr [EAX + 0xc]
004dee23 MOV dword ptr [ESI + 0x370],0x0
004dee2d MOV EAX,EDI
004dee2f POP EDI
004dee30 POP ESI
004dee31 RET 0x4
