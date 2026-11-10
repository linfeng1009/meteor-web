004cfca0 MOV EAX,ECX
004cfca2 XOR EDX,EDX
004cfca4 MOV ECX,dword ptr [EAX + 0x10]
004cfca7 CMP ECX,EDX
004cfca9 JZ 0x004cfcd5
004cfcab MOV dword ptr [EAX + 0x390],EDX
004cfcb1 MOV dword ptr [EAX + 0x394],EDX
004cfcb7 MOV dword ptr [EAX + 0x398],EDX
004cfcbd MOV EAX,dword ptr [ECX]
004cfcbf PUSH EDX
004cfcc0 MOV EDX,dword ptr [ESP + 0x10]
004cfcc4 PUSH EDX
004cfcc5 MOV EDX,dword ptr [ESP + 0x10]
004cfcc9 PUSH EDX
004cfcca MOV EDX,dword ptr [ESP + 0x10]
004cfcce PUSH EDX
004cfccf CALL dword ptr [EAX + 0x80]
004cfcd5 RET 0xc
