004cabd0 PUSH -0x1
004cabd2 PUSH 0x5a195b
004cabd7 MOV EAX,FS:[0x0]
004cabdd PUSH EAX
004cabde MOV dword ptr FS:[0x0],ESP
004cabe5 SUB ESP,0x10
004cabe8 PUSH EBX
004cabe9 PUSH EBP
004cabea PUSH ESI
004cabeb MOV ESI,ECX
004cabed PUSH EDI
004cabee MOV dword ptr [ESP + 0x14],ESI
004cabf2 CALL 0x00502d80
004cabf7 XOR EBX,EBX
004cabf9 LEA ECX,[ESI + 0xf0]
004cabff MOV dword ptr [ESP + 0x28],EBX
004cac03 CALL 0x005498c0
004cac08 LEA ECX,[ESI + 0x138]
004cac0e CALL 0x005498c0
004cac13 LEA ECX,[ESI + 0x180]
004cac19 CALL 0x005498c0
004cac1e LEA ECX,[ESI + 0x1c8]
004cac24 CALL 0x005498c0
004cac29 LEA ECX,[ESI + 0x210]
004cac2f CALL 0x005498c0
004cac34 LEA ECX,[ESI + 0x258]
004cac3a CALL 0x005498c0
004cac3f LEA ECX,[ESI + 0x2a0]
004cac45 CALL 0x005498c0
004cac4a LEA EDI,[ESI + 0x2e8]
004cac50 PUSH 0x8
004cac52 MOV ECX,EDI
004cac54 MOV dword ptr [ESP + 0x1c],EDI
004cac58 MOV dword ptr [EDI],EBX
004cac5a MOV dword ptr [EDI + 0x4],EBX
004cac5d MOV dword ptr [EDI + 0x8],EBX
004cac60 CALL 0x004608a0
004cac65 MOV ECX,EDI
004cac67 MOV byte ptr [ESP + 0x28],0x1
004cac6c CALL 0x00402a70
004cac71 LEA EDI,[ESI + 0x2f4]
004cac77 PUSH 0x8
004cac79 MOV ECX,EDI
004cac7b MOV byte ptr [ESP + 0x2c],0x2
004cac80 MOV dword ptr [ESP + 0x1c],EDI
004cac84 MOV dword ptr [EDI],EBX
004cac86 MOV dword ptr [EDI + 0x4],EBX
004cac89 MOV dword ptr [EDI + 0x8],EBX
004cac8c CALL 0x004608a0
004cac91 MOV ECX,EDI
004cac93 MOV byte ptr [ESP + 0x28],0x3
004cac98 CALL 0x00402a70
004cac9d LEA ECX,[ESI + 0x300]
004caca3 MOV byte ptr [ESP + 0x28],0x4
004caca8 CALL 0x005498c0
004cacad LEA EDI,[ESI + 0x3d4]
004cacb3 PUSH 0x18
004cacb5 MOV dword ptr [ESP + 0x1c],EDI
004cacb9 MOV dword ptr [EDI + 0x4],EBX
004cacbc CALL 0x00402bf0
004cacc1 MOV CL,byte ptr [ESP + 0x17]
004cacc5 MOV dword ptr [EDI + 0x4],EAX
004cacc8 MOV dword ptr [EDI + 0x8],EBX
004caccb MOV byte ptr [EDI + 0xc],CL
004cacce MOV byte ptr [EAX],BL
004cacd0 MOV EDX,dword ptr [EDI + 0x4]
004cacd3 MOV dword ptr [EDX + 0x4],EBX
004cacd6 MOV EAX,dword ptr [EDI + 0x4]
004cacd9 MOV dword ptr [EAX + 0x8],EAX
004cacdc MOV EAX,dword ptr [EDI + 0x4]
004cacdf MOV dword ptr [EAX + 0xc],EAX
004cace2 LEA EBP,[EDI + 0x10]
004cace5 PUSH 0x18
004cace7 MOV byte ptr [ESP + 0x30],0x5
004cacec MOV dword ptr [ESP + 0x24],EBP
004cacf0 MOV dword ptr [EBP],EBX
004cacf3 CALL 0x00402bf0
004cacf8 ADD ESP,0x8
004cacfb MOV dword ptr [EBP],EAX
004cacfe MOV byte ptr [ESP + 0x28],0x6
004cad03 MOV AL,byte ptr [ESP + 0x13]
004cad07 MOV ECX,EBP
004cad09 MOV dword ptr [EBP + 0x4],EBX
004cad0c MOV byte ptr [EBP + 0x8],AL
004cad0f CALL 0x004b4a30
004cad14 LEA EBP,[EDI + 0x1c]
004cad17 MOV byte ptr [ESP + 0x28],0x7
004cad1c LEA ECX,[EBP + 0x8]
004cad1f MOV dword ptr [EBP],EBX
004cad22 MOV dword ptr [EBP + 0x4],EBX
004cad25 CALL 0x00502330
004cad2a LEA ECX,[EBP + 0x18]
004cad2d CALL 0x00502330
004cad32 PUSH EBX
004cad33 MOV ECX,EBP
004cad35 CALL 0x004d21e0
004cad3a MOV ECX,EDI
004cad3c MOV byte ptr [ESP + 0x28],0x8
004cad41 MOV dword ptr [EDI],0x5aa88c
004cad47 CALL 0x004d0e10
004cad4c MOV ECX,ESI
004cad4e MOV byte ptr [ESP + 0x28],0x9
004cad53 MOV dword ptr [ESI],0x5aa6a8
004cad59 CALL 0x004cafb0
004cad5e MOV ECX,dword ptr [ESP + 0x20]
004cad62 MOV EAX,ESI
004cad64 POP EDI
004cad65 POP ESI
004cad66 POP EBP
004cad67 POP EBX
004cad68 MOV dword ptr FS:[0x0],ECX
004cad6f ADD ESP,0x1c
004cad72 RET
