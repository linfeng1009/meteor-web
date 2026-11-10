004fd530 SUB ESP,0xc
004fd533 MOV EAX,dword ptr [ESP + 0x10]
004fd537 FLD float ptr [0x005ab844]
004fd53d ADD EAX,0x18
004fd540 FMUL float ptr [0x005a83e8]
004fd546 MOV EDX,dword ptr [EAX]
004fd548 MOV dword ptr [ESP],EDX
004fd54c MOV EDX,dword ptr [EAX + 0x4]
004fd54f MOV dword ptr [ESP + 0x4],EDX
004fd553 LEA EDX,[ESP]
004fd557 MOV EAX,dword ptr [EAX + 0x8]
004fd55a PUSH EDX
004fd55b MOV dword ptr [ESP + 0xc],EAX
004fd55f FADD float ptr [ESP + 0xc]
004fd563 FSTP float ptr [ESP + 0xc]
004fd567 CALL 0x004fd4c0
004fd56c ADD ESP,0xc
004fd56f RET 0x4
