0056db90 PUSH -0x1
0056db92 PUSH 0x5a5af6
0056db97 MOV EAX,FS:[0x0]
0056db9d PUSH EAX
0056db9e MOV dword ptr FS:[0x0],ESP
0056dba5 SUB ESP,0x8
0056dba8 PUSH EBX
0056dba9 PUSH ESI
0056dbaa MOV ESI,ECX
0056dbac XOR EBX,EBX
0056dbae MOV dword ptr [ESP + 0x8],ESI
0056dbb2 MOV dword ptr [ESI + 0x4c],EBX
0056dbb5 MOV dword ptr [ESI + 0x50],EBX
0056dbb8 MOV dword ptr [ESI + 0x54],EBX
0056dbbb PUSH 0x928
0056dbc0 MOV dword ptr [ESP + 0x1c],EBX
0056dbc4 CALL 0x00508b38
0056dbc9 ADD ESP,0x4
0056dbcc MOV dword ptr [ESP + 0xc],EAX
0056dbd0 CMP EAX,EBX
0056dbd2 MOV byte ptr [ESP + 0x18],0x1
0056dbd7 JZ 0x0056dbe5
0056dbd9 PUSH 0x1
0056dbdb PUSH ESI
0056dbdc MOV ECX,EAX
0056dbde CALL 0x005838f0
0056dbe3 JMP 0x0056dbe7
0056dbe5 XOR EAX,EAX
0056dbe7 LEA ECX,[ESI + 0x5c]
0056dbea MOV byte ptr [ESP + 0x18],BL
0056dbee MOV dword ptr [ESI + 0x12c],EAX
0056dbf4 MOV dword ptr [ESI + 0x128],EBX
0056dbfa MOV dword ptr [ESI + 0x48],EBX
0056dbfd MOV dword ptr [ESI + 0x44],EBX
0056dc00 MOV byte ptr [ESI + 0x58],BL
0056dc03 MOV byte ptr [ESI + 0x3c],BL
0056dc06 MOV byte ptr [ESI + 0x3d],BL
0056dc09 MOV byte ptr [ESI + 0x59],BL
0056dc0c MOV byte ptr [ESI + 0x3e],BL
0056dc0f MOV dword ptr [ESI + 0x20],EBX
0056dc12 MOV dword ptr [ESI + 0x24],EBX
0056dc15 MOV dword ptr [ESI + 0x1c],EBX
0056dc18 MOV dword ptr [ESI + 0x18],EBX
0056dc1b MOV dword ptr [ESI + 0x38],EBX
0056dc1e MOV dword ptr [ESI + 0x34],EBX
0056dc21 MOV dword ptr [ESI + 0x30],EBX
0056dc24 MOV dword ptr [ESI + 0x40],EBX
0056dc27 CALL 0x00477200
0056dc2c PUSH ESI
0056dc2d CALL dword ptr [0x005a80cc]
0056dc33 MOV ECX,dword ptr [ESP + 0x10]
0056dc37 MOV EAX,ESI
0056dc39 POP ESI
0056dc3a POP EBX
0056dc3b MOV dword ptr FS:[0x0],ECX
0056dc42 ADD ESP,0x14
0056dc45 RET
