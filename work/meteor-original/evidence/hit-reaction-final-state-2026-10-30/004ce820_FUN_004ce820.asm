004ce820 MOV EDX,dword ptr [ESP + 0x4]
004ce824 TEST EDX,EDX
004ce826 JZ 0x004ce849
004ce828 MOV EAX,dword ptr [ECX + 0x10]
004ce82b TEST EAX,EAX
004ce82d JZ 0x004ce849
004ce82f MOV ECX,dword ptr [EAX + 0x1d0]
004ce835 MOV dword ptr [EDX],ECX
004ce837 MOV ECX,dword ptr [EAX + 0x1d4]
004ce83d MOV dword ptr [EDX + 0x4],ECX
004ce840 MOV EAX,dword ptr [EAX + 0x1d8]
004ce846 MOV dword ptr [EDX + 0x8],EAX
004ce849 RET 0x4
