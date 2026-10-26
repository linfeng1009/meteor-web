004bca50 MOV EAX,dword ptr [ECX + 0x3f0]
004bca56 MOV ECX,dword ptr [ECX + EAX*0x4 + 0x3c8]
004bca5d TEST ECX,ECX
004bca5f JNZ 0x004bca67
004bca61 OR EAX,0xffffffff
004bca64 RET 0x4
004bca67 MOV EDX,dword ptr [ESP + 0x4]
004bca6b MOV EAX,dword ptr [EDX]
004bca6d SUB EAX,0x0
004bca70 JZ 0x004bca8a
004bca72 DEC EAX
004bca73 JNZ 0x004bca9a
004bca75 CMP dword ptr [ECX + 0x9c],0x3
004bca7c JZ 0x004bca9a
004bca7e MOV EAX,dword ptr [ECX]
004bca80 PUSH 0x1
004bca82 CALL dword ptr [EAX + 0x58]
004bca85 XOR EAX,EAX
004bca87 RET 0x4
004bca8a CMP dword ptr [ECX + 0x9c],0x3
004bca91 JZ 0x004bca9a
004bca93 MOV EDX,dword ptr [ECX]
004bca95 PUSH 0x0
004bca97 CALL dword ptr [EDX + 0x58]
004bca9a XOR EAX,EAX
004bca9c RET 0x4
