004abaa0 PUSH -0x1
004abaa2 PUSH 0x59feec
004abaa7 MOV EAX,FS:[0x0]
004abaad PUSH EAX
004abaae MOV dword ptr FS:[0x0],ESP
004abab5 SUB ESP,0x10
004abab8 PUSH EBX
004abab9 PUSH EBP
004ababa PUSH ESI
004ababb MOV ESI,ECX
004ababd PUSH EDI
004ababe MOV dword ptr [ESP + 0x18],ESI
004abac2 CALL 0x004a9010
004abac7 LEA EBX,[ESI + 0x10]
004abaca XOR EBP,EBP
004abacc MOV ECX,EBX
004abace MOV dword ptr [ESP + 0x28],EBP
004abad2 CALL 0x0054e150
004abad7 LEA ECX,[ESI + 0x108]
004abadd MOV byte ptr [ESP + 0x28],0x1
004abae2 CALL 0x005498c0
004abae7 LEA ECX,[ESI + 0x150]
004abaed CALL 0x005498c0
004abaf2 LEA ECX,[ESI + 0x198]
004abaf8 CALL 0x005498c0
004abafd LEA EDI,[ESI + 0x1ec]
004abb03 LEA EAX,[ESP + 0x10]
004abb07 PUSH 0x8
004abb09 PUSH EAX
004abb0a MOV ECX,EDI
004abb0c MOV dword ptr [ESP + 0x24],EDI
004abb10 CALL 0x00402b70
004abb15 MOV ECX,EDI
004abb17 MOV byte ptr [ESP + 0x28],0x2
004abb1c CALL 0x00402a70
004abb21 LEA EDX,[ESP + 0x11]
004abb25 LEA ECX,[EDI + 0xc]
004abb28 PUSH 0x8
004abb2a PUSH EDX
004abb2b MOV byte ptr [ESP + 0x30],0x3
004abb30 MOV dword ptr [ESP + 0x1c],ECX
004abb34 CALL 0x00402b70
004abb39 MOV ECX,dword ptr [ESP + 0x14]
004abb3d MOV byte ptr [ESP + 0x28],0x4
004abb42 CALL 0x00402a70
004abb47 LEA EAX,[ESP + 0x12]
004abb4b LEA ECX,[EDI + 0x18]
004abb4e PUSH 0x8
004abb50 PUSH EAX
004abb51 MOV byte ptr [ESP + 0x30],0x5
004abb56 MOV dword ptr [ESP + 0x1c],ECX
004abb5a CALL 0x00402b70
004abb5f MOV ECX,dword ptr [ESP + 0x14]
004abb63 MOV byte ptr [ESP + 0x28],0x6
004abb68 CALL 0x00402a70
004abb6d LEA ECX,[EDI + 0x58]
004abb70 MOV byte ptr [ESP + 0x28],0x7
004abb75 CALL 0x00499700
004abb7a MOV dword ptr [EDI + 0x38],EBP
004abb7d MOV dword ptr [EDI + 0x54],EBP
004abb80 MOV dword ptr [EDI + 0x4c],EBP
004abb83 MOV dword ptr [EDI + 0x48],EBP
004abb86 MOV dword ptr [EDI + 0x44],EBP
004abb89 MOV dword ptr [EDI + 0x40],EBP
004abb8c MOV dword ptr [EDI + 0x3c],EBP
004abb8f MOV dword ptr [EDI + 0x50],0x64
004abb96 MOV dword ptr [EDI + 0x2c],0x2
004abb9d MOV dword ptr [EDI + 0x30],0x12c
004abba4 MOV dword ptr [EDI + 0x34],0x3
004abbab LEA ECX,[ESI + 0x258]
004abbb1 MOV byte ptr [ESP + 0x28],0x8
004abbb6 CALL 0x005498c0
004abbbb LEA ECX,[ESI + 0x2a0]
004abbc1 CALL 0x005498c0
004abbc6 LEA ECX,[ESI + 0x2e8]
004abbcc CALL 0x005498c0
004abbd1 LEA ECX,[ESI + 0x330]
004abbd7 CALL 0x005498c0
004abbdc LEA EDI,[ESI + 0x388]
004abbe2 PUSH 0x1c
004abbe4 MOV dword ptr [ESP + 0x20],EDI
004abbe8 MOV dword ptr [EDI],EBP
004abbea CALL 0x00402bf0
004abbef ADD ESP,0x4
004abbf2 MOV dword ptr [EDI],EAX
004abbf4 MOV CL,byte ptr [ESP + 0x12]
004abbf8 MOV byte ptr [ESP + 0x28],0x9
004abbfd MOV byte ptr [EDI + 0x8],CL
004abc00 MOV ECX,EDI
004abc02 MOV dword ptr [EDI + 0x4],EBP
004abc05 CALL 0x004b4a30
004abc0a LEA EDI,[ESI + 0x394]
004abc10 PUSH 0x14
004abc12 MOV byte ptr [ESP + 0x2c],0xa
004abc17 MOV dword ptr [ESP + 0x20],EDI
004abc1b MOV dword ptr [EDI],EBP
004abc1d CALL 0x00402bf0
004abc22 ADD ESP,0x4
004abc25 MOV dword ptr [EDI],EAX
004abc27 MOV DL,byte ptr [ESP + 0x12]
004abc2b MOV ECX,EDI
004abc2d MOV byte ptr [ESP + 0x28],0xb
004abc32 MOV dword ptr [EDI + 0x4],EBP
004abc35 MOV byte ptr [EDI + 0x8],DL
004abc38 CALL 0x004b4a30
004abc3d LEA EDI,[ESI + 0x3a4]
004abc43 LEA EAX,[ESP + 0x12]
004abc47 LEA EDX,[ESP + 0x11]
004abc4b PUSH EAX
004abc4c LEA ECX,[EDI + 0x4]
004abc4f PUSH EDX
004abc50 MOV byte ptr [ESP + 0x30],0xc
004abc55 MOV dword ptr [ESP + 0x24],EDI
004abc59 CALL 0x004b4790
004abc5e LEA EAX,[ESP + 0x10]
004abc62 LEA EDX,[ESP + 0x13]
004abc66 PUSH EAX
004abc67 LEA ECX,[EDI + 0x10]
004abc6a PUSH EDX
004abc6b MOV byte ptr [ESP + 0x30],0xd
004abc70 CALL 0x004b47f0
004abc75 MOV dword ptr [EDI],0x5a9444
004abc7b MOV dword ptr [EDI + 0x24],EBP
004abc7e MOV dword ptr [EDI + 0x20],EBP
004abc81 MOV dword ptr [EDI + 0x1c],EBP
004abc84 MOV ECX,ESI
004abc86 MOV byte ptr [ESP + 0x28],0xe
004abc8b MOV dword ptr [ESI],0x5a9bf8
004abc91 MOV dword ptr [EBX],0x5a9bd8
004abc97 CALL 0x004abe80
004abc9c MOV ECX,dword ptr [ESP + 0x20]
004abca0 MOV EAX,ESI
004abca2 POP EDI
004abca3 POP ESI
004abca4 POP EBP
004abca5 POP EBX
004abca6 MOV dword ptr FS:[0x0],ECX
004abcad ADD ESP,0x1c
004abcb0 RET
