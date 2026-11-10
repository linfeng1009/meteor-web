0055a920 MOV EAX,dword ptr [ESP + 0x4]
0055a924 PUSH ESI
0055a925 MOV ESI,ECX
0055a927 MOV ECX,dword ptr [ESP + 0xc]
0055a92b CMP EAX,ECX
0055a92d PUSH EDI
0055a92e JLE 0x0055a936
0055a930 MOV EAX,ECX
0055a932 MOV dword ptr [ESP + 0xc],EAX
0055a936 TEST EAX,EAX
0055a938 JGE 0x0055a940
0055a93a XOR EAX,EAX
0055a93c MOV dword ptr [ESP + 0xc],EAX
0055a940 FILD dword ptr [ESP + 0xc]
0055a944 LEA EDI,[ESI + 0x11bc]
0055a94a MOV dword ptr [ESI + 0x14],ECX
0055a94d MOV ECX,EDI
0055a94f MOV dword ptr [ESI + 0xc],EAX
0055a952 FIDIV dword ptr [ESP + 0x10]
0055a956 FSTP float ptr [ESI + 0x1668]
0055a95c CALL 0x00481b30
0055a961 FLD float ptr [ESI + 0x1668]
0055a967 FMUL float ptr [ESI + 0x28]
0055a96a MOV ECX,EDI
0055a96c FMUL float ptr [0x005a8ff0]
0055a972 FSTP float ptr [EAX]
0055a974 FLD float ptr [ESI + 0x2c]
0055a977 FMUL float ptr [0x005a8ff0]
0055a97d FSTP float ptr [EAX + 0x4]
0055a980 FLD float ptr [ESI + 0x1668]
0055a986 FMUL float ptr [ESI + 0x28]
0055a989 FMUL float ptr [0x005a83e8]
0055a98f FSTP float ptr [EAX + 0x18]
0055a992 FLD float ptr [ESI + 0x2c]
0055a995 FMUL float ptr [0x005a8ff0]
0055a99b FSTP float ptr [EAX + 0x1c]
0055a99e FLD float ptr [ESI + 0x1668]
0055a9a4 FMUL float ptr [ESI + 0x28]
0055a9a7 FMUL float ptr [0x005a83e8]
0055a9ad FSTP float ptr [EAX + 0x30]
0055a9b0 FLD float ptr [ESI + 0x2c]
0055a9b3 FMUL float ptr [0x005a83e8]
0055a9b9 FSTP float ptr [EAX + 0x34]
0055a9bc FLD float ptr [ESI + 0x1668]
0055a9c2 FMUL float ptr [ESI + 0x28]
0055a9c5 FMUL float ptr [0x005a8ff0]
0055a9cb FSTP float ptr [EAX + 0x48]
0055a9ce FLD float ptr [ESI + 0x2c]
0055a9d1 FMUL float ptr [0x005a83e8]
0055a9d7 FSTP float ptr [EAX + 0x4c]
0055a9da CALL 0x00481b90
0055a9df POP EDI
0055a9e0 POP ESI
0055a9e1 RET 0x8
