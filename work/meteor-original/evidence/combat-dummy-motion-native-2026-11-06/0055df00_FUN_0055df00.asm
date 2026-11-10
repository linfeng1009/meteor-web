0055df00 MOV EAX,dword ptr [ESP + 0x4]
0055df04 ADD ECX,0x304
0055df0a PUSH ESI
0055df0b MOV EDX,EAX
0055df0d MOV ESI,dword ptr [ECX]
0055df0f MOV dword ptr [EDX],ESI
0055df11 MOV ESI,dword ptr [ECX + 0x4]
0055df14 MOV dword ptr [EDX + 0x4],ESI
0055df17 POP ESI
0055df18 MOV ECX,dword ptr [ECX + 0x8]
0055df1b MOV dword ptr [EDX + 0x8],ECX
0055df1e RET 0x4
