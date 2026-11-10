004dee40 MOV EAX,dword ptr [ESP + 0x8]
004dee44 CMP EAX,0xad
004dee49 JA 0x004deeb9
004dee4b XOR ECX,ECX
004dee4d MOV CL,byte ptr [EAX + 0x4deedc]
004dee53 JMP dword ptr [ECX*0x4 + 0x4deebc]
004dee5a MOV EDX,dword ptr [ESP + 0x4]
004dee5e MOV ECX,dword ptr [EDX + 0x36c]
004dee64 TEST ECX,ECX
004dee66 JZ 0x004deeb9
004dee68 MOV EAX,0xd5
004dee6d RET 0x8
004dee70 MOV EAX,0xa4
004dee75 RET 0x8
004dee78 MOV EAX,0xa7
004dee7d RET 0x8
004dee80 MOV EAX,0xaa
004dee85 RET 0x8
004dee88 MOV EAX,0xad
004dee8d RET 0x8
004dee90 MOV ECX,dword ptr [ESP + 0x4]
004dee94 MOV EDX,dword ptr [ECX + 0x36c]
004dee9a TEST EDX,EDX
004dee9c JZ 0x004deeb9
004dee9e MOV EAX,0x92
004deea3 RET 0x8
004deea6 MOV EDX,dword ptr [ESP + 0x4]
004deeaa MOV ECX,dword ptr [EDX + 0x36c]
004deeb0 TEST ECX,ECX
004deeb2 JZ 0x004deeb9
004deeb4 MOV EAX,0x93
004deeb9 RET 0x8
