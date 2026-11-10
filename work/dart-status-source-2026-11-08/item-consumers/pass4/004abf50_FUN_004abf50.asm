004abf50 PUSH -0x1
004abf52 PUSH 0x59ffd0
004abf57 MOV EAX,FS:[0x0]
004abf5d PUSH EAX
004abf5e MOV dword ptr FS:[0x0],ESP
004abf65 SUB ESP,0x10
004abf68 PUSH EBX
004abf69 PUSH ESI
004abf6a MOV ESI,ECX
004abf6c PUSH EDI
004abf6d MOV dword ptr [ESP + 0x10],ESI
004abf71 MOV dword ptr [ESI],0x5a9bf8
004abf77 MOV dword ptr [ESI + 0x10],0x5a9bd8
004abf7e MOV EAX,dword ptr [ESI + 0x104]
004abf84 XOR EBX,EBX
004abf86 CMP EAX,EBX
004abf88 MOV dword ptr [ESP + 0x24],0x5
004abf90 JZ 0x004abf9b
004abf92 PUSH EAX
004abf93 CALL 0x00507850
004abf98 ADD ESP,0x4
004abf9b MOV EAX,dword ptr [ESI + 0x37c]
004abfa1 MOV dword ptr [ESI + 0x104],EBX
004abfa7 CMP EAX,EBX
004abfa9 JZ 0x004abfb4
004abfab PUSH EAX
004abfac CALL 0x00509e57
004abfb1 ADD ESP,0x4
004abfb4 PUSH EBP
004abfb5 CALL 0x004b3420
004abfba MOV ECX,EAX
004abfbc CALL 0x0054da60
004abfc1 LEA EDI,[ESI + 0x3a4]
004abfc7 MOV dword ptr [ESP + 0x18],EDI
004abfcb MOV dword ptr [EDI],0x5a9444
004abfd1 LEA EBP,[EDI + 0x10]
004abfd4 MOV dword ptr [ESP + 0x1c],EBP
004abfd8 MOV ECX,EBP
004abfda MOV byte ptr [ESP + 0x28],0x7
004abfdf CALL 0x004b48d0
004abfe4 MOV EBP,dword ptr [EBP]
004abfe7 PUSH 0x78
004abfe9 PUSH EBP
004abfea MOV byte ptr [ESP + 0x30],0x6
004abfef CALL 0x00402e90
004abff4 ADD EDI,0x4
004abff7 ADD ESP,0x8
004abffa MOV dword ptr [ESP + 0x1c],EDI
004abffe MOV EAX,dword ptr [EDI + 0x4]
004ac001 MOV byte ptr [ESP + 0x28],0x8
004ac006 CMP EAX,EBX
004ac008 POP EBP
004ac009 JZ 0x004ac02a
004ac00b MOV EAX,dword ptr [EDI]
004ac00d MOV ECX,dword ptr [EAX + 0x4]
004ac010 PUSH ECX
004ac011 MOV ECX,EDI
004ac013 CALL 0x0049d200
004ac018 MOV EAX,dword ptr [EDI]
004ac01a MOV dword ptr [EAX + 0x8],EAX
004ac01d MOV EDX,dword ptr [EDI]
004ac01f MOV dword ptr [EDX + 0x4],EBX
004ac022 MOV EAX,dword ptr [EDI]
004ac024 MOV dword ptr [EAX + 0xc],EAX
004ac027 MOV dword ptr [EDI + 0x4],EBX
004ac02a MOV EDI,dword ptr [EDI]
004ac02c PUSH 0x2b8
004ac031 PUSH EDI
004ac032 MOV byte ptr [ESP + 0x2c],0x4
004ac037 CALL 0x00402e90
004ac03c LEA EDI,[ESI + 0x394]
004ac042 ADD ESP,0x8
004ac045 MOV dword ptr [ESP + 0x18],EDI
004ac049 MOV EAX,dword ptr [EDI + 0x4]
004ac04c MOV byte ptr [ESP + 0x24],0x9
004ac051 CMP EAX,EBX
004ac053 JZ 0x004ac074
004ac055 MOV EAX,dword ptr [EDI]
004ac057 MOV ECX,dword ptr [EAX + 0x4]
004ac05a PUSH ECX
004ac05b MOV ECX,EDI
004ac05d CALL 0x0049d4a0
004ac062 MOV EAX,dword ptr [EDI]
004ac064 MOV dword ptr [EAX + 0x8],EAX
004ac067 MOV EDX,dword ptr [EDI]
004ac069 MOV dword ptr [EDX + 0x4],EBX
004ac06c MOV EAX,dword ptr [EDI]
004ac06e MOV dword ptr [EAX + 0xc],EAX
004ac071 MOV dword ptr [EDI + 0x4],EBX
004ac074 MOV EDI,dword ptr [EDI]
004ac076 MOV ECX,0x5d59e8
004ac07b CALL 0x00402330
004ac080 MOV EAX,[0x005d59b0]
004ac085 MOV dword ptr [EDI],EAX
004ac087 MOV dword ptr [0x005d59b0],EDI
004ac08d LEA EDI,[ESI + 0x388]
004ac093 MOV dword ptr [0x005d59e8],EBX
004ac099 MOV dword ptr [ESP + 0x18],EDI
004ac09d MOV EAX,dword ptr [EDI + 0x4]
004ac0a0 MOV byte ptr [ESP + 0x24],0xa
004ac0a5 CMP EAX,EBX
004ac0a7 JZ 0x004ac0c8
004ac0a9 MOV ECX,dword ptr [EDI]
004ac0ab MOV EDX,dword ptr [ECX + 0x4]
004ac0ae MOV ECX,EDI
004ac0b0 PUSH EDX
004ac0b1 CALL 0x004b4c80
004ac0b6 MOV EAX,dword ptr [EDI]
004ac0b8 MOV dword ptr [EAX + 0x8],EAX
004ac0bb MOV EAX,dword ptr [EDI]
004ac0bd MOV dword ptr [EAX + 0x4],EBX
004ac0c0 MOV EAX,dword ptr [EDI]
004ac0c2 MOV dword ptr [EAX + 0xc],EAX
004ac0c5 MOV dword ptr [EDI + 0x4],EBX
004ac0c8 MOV EDI,dword ptr [EDI]
004ac0ca MOV ECX,0x5d59e8
004ac0cf CALL 0x00402330
004ac0d4 MOV ECX,dword ptr [0x005d59b4]
004ac0da MOV dword ptr [EDI],ECX
004ac0dc MOV dword ptr [0x005d59b4],EDI
004ac0e2 LEA EDI,[ESI + 0x1ec]
004ac0e8 MOV dword ptr [0x005d59e8],EBX
004ac0ee MOV dword ptr [ESP + 0x18],EDI
004ac0f2 LEA ECX,[EDI + 0x58]
004ac0f5 MOV byte ptr [ESP + 0x24],0xd
004ac0fa CALL 0x004998a0
004ac0ff LEA ECX,[EDI + 0x18]
004ac102 MOV byte ptr [ESP + 0x24],0xc
004ac107 CALL 0x00402bd0
004ac10c LEA ECX,[EDI + 0xc]
004ac10f MOV byte ptr [ESP + 0x24],0xb
004ac114 CALL 0x00402bd0
004ac119 MOV ECX,EDI
004ac11b MOV byte ptr [ESP + 0x24],0x1
004ac120 CALL 0x00402bd0
004ac125 LEA ECX,[ESI + 0x10]
004ac128 MOV byte ptr [ESP + 0x24],BL
004ac12c CALL 0x0054e3d0
004ac131 MOV ECX,ESI
004ac133 MOV dword ptr [ESP + 0x24],0xffffffff
004ac13b CALL 0x004a9190
004ac140 MOV ECX,dword ptr [ESP + 0x1c]
004ac144 POP EDI
004ac145 POP ESI
004ac146 POP EBX
004ac147 MOV dword ptr FS:[0x0],ECX
004ac14e ADD ESP,0x1c
004ac151 RET
