0057d930 MOV EAX,dword ptr [ESP + 0x4]
0057d934 MOV EDX,dword ptr [ESP + 0x8]
0057d938 ADD ECX,0x40
0057d93b MOV dword ptr [ECX],EAX
0057d93d MOV EAX,dword ptr [ESP + 0xc]
0057d941 MOV dword ptr [ECX + 0x4],EDX
0057d944 MOV dword ptr [ECX + 0x8],EAX
0057d947 RET 0xc
