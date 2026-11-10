004ce540 SUB ESP,0x78
004ce543 PUSH ESI
004ce544 PUSH EDI
004ce545 MOV EDI,ECX
004ce547 MOV EAX,dword ptr [EDI + 0x34c]
004ce54d TEST EAX,EAX
004ce54f JZ 0x004ce6bc
004ce555 MOV EAX,dword ptr [EDI + 0x10]
004ce558 MOV dword ptr [ESP + 0x38],0x0
004ce560 TEST EAX,EAX
004ce562 MOV dword ptr [ESP + 0x3c],0x0
004ce56a MOV dword ptr [ESP + 0x40],0x3f800000
004ce572 JZ 0x004ce57c
004ce574 LEA ESI,[EAX + 0xfffff9a4]
004ce57a JMP 0x004ce57e
004ce57c XOR ESI,ESI
004ce57e MOV EAX,dword ptr [ESI]
004ce580 LEA ECX,[ESP + 0x50]
004ce584 PUSH 0x2
004ce586 PUSH ECX
004ce587 MOV ECX,ESI
004ce589 CALL dword ptr [EAX + 0x6c]
004ce58c FLD float ptr [ESP + 0x74]
004ce590 FSTP float ptr [ESP + 0x14]
004ce594 FLD float ptr [ESP + 0x78]
004ce598 MOV EAX,dword ptr [EDI + 0x34c]
004ce59e LEA EDX,[ESP + 0x50]
004ce5a2 FSTP float ptr [ESP + 0x18]
004ce5a6 FLD float ptr [ESP + 0x7c]
004ce5aa PUSH 0x2
004ce5ac PUSH EDX
004ce5ad FSTP float ptr [ESP + 0x24]
004ce5b1 PUSH EAX
004ce5b2 CALL 0x0040c6e0
004ce5b7 FLD float ptr [ESP + 0x80]
004ce5be FLD float ptr [ESP + 0x84]
004ce5c5 FLD float ptr [ESP + 0x88]
004ce5cc FSTP float ptr [ESP + 0x1c]
004ce5d0 FXCH
004ce5d2 FSUB float ptr [ESP + 0x20]
004ce5d6 ADD ESP,0xc
004ce5d9 FSTP float ptr [ESP + 0x2c]
004ce5dd MOV ECX,dword ptr [ESP + 0x2c]
004ce5e1 FSUB float ptr [ESP + 0x18]
004ce5e5 MOV dword ptr [ESP + 0x8],ECX
004ce5e9 LEA ECX,[ESP + 0x8]
004ce5ed FSTP float ptr [ESP + 0x30]
004ce5f1 FLD float ptr [ESP + 0x10]
004ce5f5 FSUB float ptr [ESP + 0x1c]
004ce5f9 MOV EDX,dword ptr [ESP + 0x30]
004ce5fd MOV dword ptr [ESP + 0xc],EDX
004ce601 FSTP float ptr [ESP + 0x34]
004ce605 MOV EAX,dword ptr [ESP + 0x34]
004ce609 MOV dword ptr [ESP + 0x10],EAX
004ce60d CALL 0x0047ecf0
004ce612 FCOMP float ptr [0x005aa924]
004ce618 FNSTSW AX
004ce61a TEST AH,0x5
004ce61d JP 0x004ce6af
004ce623 FLD float ptr [ESP + 0x10]
004ce627 CALL 0x00509980
004ce62c CDQ
004ce62d XOR EAX,EDX
004ce62f SUB EAX,EDX
004ce631 CMP EAX,0x64
004ce634 JGE 0x004ce6af
004ce636 LEA ECX,[ESP + 0x8]
004ce63a MOV dword ptr [ESP + 0x10],0x0
004ce642 CALL 0x0047ec40
004ce647 TEST EAX,EAX
004ce649 JZ 0x004ce661
004ce64b MOV EDX,dword ptr [ESP + 0xc]
004ce64f MOV EAX,dword ptr [ESP + 0x10]
004ce653 MOV ECX,dword ptr [ESP + 0x8]
004ce657 MOV dword ptr [ESP + 0x24],EDX
004ce65b MOV dword ptr [ESP + 0x28],EAX
004ce65f JMP 0x004ce677
004ce661 FLD float ptr [ESP + 0x60]
004ce665 MOV ECX,dword ptr [ESP + 0x5c]
004ce669 MOV dword ptr [ESP + 0x28],0x0
004ce671 FCHS
004ce673 FSTP float ptr [ESP + 0x24]
004ce677 MOV EAX,dword ptr [ESP + 0x18]
004ce67b MOV EDX,dword ptr [ESP + 0x14]
004ce67f MOV dword ptr [ESP + 0x20],ECX
004ce683 MOV ECX,dword ptr [ESP + 0x1c]
004ce687 MOV dword ptr [ESP + 0x48],EAX
004ce68b LEA EAX,[ESP + 0x38]
004ce68f MOV dword ptr [ESP + 0x4c],ECX
004ce693 PUSH EAX
004ce694 LEA ECX,[ESP + 0x24]
004ce698 MOV dword ptr [ESP + 0x48],EDX
004ce69c MOV EDX,dword ptr [ESI]
004ce69e LEA EAX,[ESP + 0x48]
004ce6a2 PUSH ECX
004ce6a3 PUSH EAX
004ce6a4 MOV ECX,ESI
004ce6a6 CALL dword ptr [EDX + 0x74]
004ce6a9 POP EDI
004ce6aa POP ESI
004ce6ab ADD ESP,0x78
004ce6ae RET
004ce6af MOV EDX,dword ptr [EDI]
004ce6b1 PUSH 0x0
004ce6b3 PUSH 0x0
004ce6b5 PUSH 0x6
004ce6b7 MOV ECX,EDI
004ce6b9 CALL dword ptr [EDX + 0xc]
004ce6bc POP EDI
004ce6bd POP ESI
004ce6be ADD ESP,0x78
004ce6c1 RET
