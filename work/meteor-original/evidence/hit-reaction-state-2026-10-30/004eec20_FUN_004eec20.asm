004eec20 SUB ESP,0x3c
004eec23 PUSH ESI
004eec24 MOV ESI,ECX
004eec26 PUSH EDI
004eec27 MOV EAX,dword ptr [ESI]
004eec29 CALL dword ptr [EAX + 0x48]
004eec2c TEST EAX,EAX
004eec2e JZ 0x004eede7
004eec34 LEA EDI,[EAX + 0x65c]
004eec3a TEST EDI,EDI
004eec3c JZ 0x004eede7
004eec42 MOV EDX,dword ptr [EDI]
004eec44 PUSH EBX
004eec45 PUSH EBP
004eec46 LEA EAX,[ESP + 0x2c]
004eec4a PUSH 0x0
004eec4c LEA ECX,[ESP + 0x18]
004eec50 PUSH EAX
004eec51 PUSH ECX
004eec52 MOV ECX,EDI
004eec54 CALL dword ptr [EDX + 0x4]
004eec57 ADD EDI,0xfffff9a4
004eec5d MOV ECX,EDI
004eec5f CALL 0x0055c4d0
004eec64 MOV EBX,EAX
004eec66 MOV EAX,dword ptr [ESI + 0x364]
004eec6c CMP EBX,EAX
004eec6e JZ 0x004eec7a
004eec70 MOV dword ptr [ESI + 0x360],0x0
004eec7a MOV EDX,dword ptr [EDI + 0x8ac]
004eec80 MOV AX,word ptr [EDI + 0x614]
004eec87 SHL EDX,0xd
004eec8a OR EBX,EDX
004eec8c MOV EDX,dword ptr [ESI]
004eec8e MOV ECX,ESI
004eec90 MOV word ptr [ESP + 0x10],AX
004eec95 CALL dword ptr [EDX + 0x44]
004eec98 MOV EBP,EAX
004eec9a XOR EDI,EDI
004eec9c TEST EBP,EBP
004eec9e JZ 0x004eecc1
004eeca0 MOV EAX,dword ptr [EBP]
004eeca3 LEA ECX,[ESP + 0x20]
004eeca7 PUSH ECX
004eeca8 MOV ECX,EBP
004eecaa CALL dword ptr [EAX + 0x3c]
004eecad MOV EDX,dword ptr [EBP]
004eecb0 MOV ECX,EBP
004eecb2 CALL dword ptr [EDX + 0x168]
004eecb8 TEST EAX,EAX
004eecba JZ 0x004eecc1
004eecbc MOV EDI,0x1
004eecc1 FLD float ptr [ESP + 0x14]
004eecc5 FMUL float ptr [0x005a84ac]
004eeccb FADD double ptr [0x005a8460]
004eecd1 CALL 0x00509980
004eecd6 FLD float ptr [ESP + 0x18]
004eecda FMUL float ptr [0x005a84ac]
004eece0 MOV word ptr [ESP + 0x38],AX
004eece5 FADD double ptr [0x005a8460]
004eeceb CALL 0x00509980
004eecf0 FLD float ptr [ESP + 0x1c]
004eecf4 FMUL float ptr [0x005a84ac]
004eecfa MOV word ptr [ESP + 0x3a],AX
004eecff FADD double ptr [0x005a8460]
004eed05 CALL 0x00509980
004eed0a FLD float ptr [ESP + 0x2c]
004eed0e FMUL float ptr [0x005a9bac]
004eed14 MOV word ptr [ESP + 0x3c],AX
004eed19 FADD double ptr [0x005a8460]
004eed1f CALL 0x00509980
004eed24 FLD float ptr [ESP + 0x30]
004eed28 FMUL float ptr [0x005a9bac]
004eed2e MOV word ptr [ESP + 0x3e],AX
004eed33 FADD double ptr [0x005a8460]
004eed39 CALL 0x00509980
004eed3e FLD float ptr [ESP + 0x20]
004eed42 FMUL float ptr [0x005a8f50]
004eed48 MOV word ptr [ESP + 0x40],AX
004eed4d FADD double ptr [0x005a8460]
004eed53 CALL 0x00509980
004eed58 FLD float ptr [ESP + 0x24]
004eed5c FMUL float ptr [0x005a8f50]
004eed62 MOV word ptr [ESP + 0x42],AX
004eed67 FADD double ptr [0x005a8460]
004eed6d CALL 0x00509980
004eed72 FLD float ptr [ESP + 0x28]
004eed76 FMUL float ptr [0x005a8f50]
004eed7c MOV word ptr [ESP + 0x44],AX
004eed81 FADD double ptr [0x005a8460]
004eed87 CALL 0x00509980
004eed8c MOV CX,word ptr [ESI + 0x360]
004eed93 MOV DX,word ptr [ESP + 0x10]
004eed98 MOV word ptr [ESP + 0x46],AX
004eed9d LEA EAX,[EDI + EDI*0x1]
004eeda0 OR CX,AX
004eeda3 MOV word ptr [ESP + 0x4a],DX
004eeda8 SHL ECX,0xb
004eedab OR ECX,EBX
004eedad MOV word ptr [ESP + 0x48],CX
004eedb2 CALL 0x00487830
004eedb7 MOV EDX,dword ptr [ESI]
004eedb9 MOV EDI,EAX
004eedbb LEA EAX,[ESP + 0x38]
004eedbf PUSH 0x14
004eedc1 MOV EBX,dword ptr [EDI]
004eedc3 PUSH EAX
004eedc4 MOV ECX,ESI
004eedc6 CALL dword ptr [EDX + 0x4c]
004eedc9 PUSH EAX
004eedca MOV ECX,EDI
004eedcc CALL dword ptr [EBX + 0x330]
004eedd2 PUSH 0x0
004eedd4 LEA EAX,[ESP + 0x3c]
004eedd8 PUSH 0x14
004eedda PUSH EAX
004eeddb PUSH 0x1
004eeddd LEA ECX,[ESI + 0x10]
004eede0 CALL 0x0054a6c0
004eede5 POP EBP
004eede6 POP EBX
004eede7 POP EDI
004eede8 POP ESI
004eede9 ADD ESP,0x3c
004eedec RET
