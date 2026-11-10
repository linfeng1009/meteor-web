004a4b30 MOV EDX,ECX
004a4b32 PUSH ESI
004a4b33 XOR ESI,ESI
004a4b35 PUSH EDI
004a4b36 MOV ECX,0x6
004a4b3b XOR EAX,EAX
004a4b3d LEA EDI,[EDX + 0x154]
004a4b43 MOV dword ptr [EDX + 0x194],ESI
004a4b49 MOV dword ptr [EDX + 0x440],ESI
004a4b4f MOV dword ptr [EDX + 0x444],ESI
004a4b55 MOV dword ptr [EDX + 0x448],ESI
004a4b5b MOV dword ptr [EDX + 0x150],ESI
004a4b61 STOSD.REP ES:EDI
004a4b63 MOV EAX,0x1
004a4b68 MOV dword ptr [EDX + 0x420],ESI
004a4b6e MOV dword ptr [EDX + 0x1c0],ESI
004a4b74 MOV dword ptr [EDX + 0x16c],ESI
004a4b7a MOV dword ptr [EDX + 0x1d4],ESI
004a4b80 MOV dword ptr [EDX + 0x1d8],ESI
004a4b86 MOV dword ptr [EDX + 0x1dc],ESI
004a4b8c MOV dword ptr [EDX + 0x1e4],ESI
004a4b92 MOV dword ptr [EDX + 0x1ec],ESI
004a4b98 MOV dword ptr [EDX + 0x3f8],ESI
004a4b9e MOV dword ptr [EDX + 0x1f4],ESI
004a4ba4 MOV dword ptr [EDX + 0x400],ESI
004a4baa MOV dword ptr [EDX + 0x404],ESI
004a4bb0 MOV dword ptr [EDX + 0x408],ESI
004a4bb6 MOV dword ptr [EDX + 0x14c],ESI
004a4bbc MOV dword ptr [EDX + 0x1e0],ESI
004a4bc2 MOV dword ptr [EDX + 0x478],ESI
004a4bc8 MOV dword ptr [EDX + 0x1f0],ESI
004a4bce MOV dword ptr [EDX + 0x190],ESI
004a4bd4 MOV dword ptr [EDX + 0x198],ESI
004a4bda MOV dword ptr [EDX + 0x470],ESI
004a4be0 MOV dword ptr [EDX + 0x434],ESI
004a4be6 MOV dword ptr [EDX + 0x438],ESI
004a4bec MOV dword ptr [EDX + 0x43c],ESI
004a4bf2 MOV dword ptr [EDX + 0x418],ESI
004a4bf8 MOV dword ptr [EDX + 0x41c],ESI
004a4bfe MOV dword ptr [EDX + 0x47c],ESI
004a4c04 MOV dword ptr [EDX + 0x424],ESI
004a4c0a MOV dword ptr [EDX + 0x42c],ESI
004a4c10 MOV dword ptr [EDX + 0x170],ESI
004a4c16 MOV dword ptr [EDX + 0x174],ESI
004a4c1c MOV dword ptr [EDX + 0x430],ESI
004a4c22 MOV dword ptr [EDX + 0x1c8],ESI
004a4c28 POP EDI
004a4c29 MOV dword ptr [EDX + 0x1e8],EAX
004a4c2f MOV dword ptr [EDX + 0x1c4],0x2
004a4c39 MOV dword ptr [EDX + 0x1d0],EAX
004a4c3f MOV dword ptr [EDX + 0x480],0x3
004a4c49 MOV dword ptr [EDX + 0x3fc],0x3f800000
004a4c53 MOV dword ptr [EDX + 0x428],0xffffffff
004a4c5d POP ESI
004a4c5e RET
