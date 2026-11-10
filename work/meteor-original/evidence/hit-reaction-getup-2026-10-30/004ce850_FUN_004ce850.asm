004ce850 SUB ESP,0x94
004ce856 PUSH EBX
004ce857 MOV EBX,ECX
004ce859 PUSH EBP
004ce85a PUSH ESI
004ce85b MOV EAX,dword ptr [EBX + 0x10]
004ce85e PUSH EDI
004ce85f TEST EAX,EAX
004ce861 JZ 0x004ce86b
004ce863 LEA EBP,[EAX + 0xfffff9a4]
004ce869 JMP 0x004ce86d
004ce86b XOR EBP,EBP
004ce86d MOV EAX,dword ptr [EBP]
004ce870 LEA ECX,[ESP + 0x44]
004ce874 PUSH 0x2
004ce876 PUSH ECX
004ce877 MOV ECX,EBP
004ce879 CALL dword ptr [EAX + 0x6c]
004ce87c PUSH 0x5c928c
004ce881 MOV ECX,EBP
004ce883 CALL 0x005569b0
004ce888 CMP EAX,-0x1
004ce88b JZ 0x004ceb41
004ce891 LEA EDX,[ESP + 0x74]
004ce895 MOV ECX,EBP
004ce897 PUSH EDX
004ce898 PUSH EAX
004ce899 CALL 0x00557ef0
004ce89e MOV EAX,dword ptr [EBP]
004ce8a1 LEA ECX,[ESP + 0x38]
004ce8a5 PUSH ECX
004ce8a6 MOV ECX,EBP
004ce8a8 CALL dword ptr [EAX + 0x20]
004ce8ab MOV ECX,0x9
004ce8b0 LEA ESI,[ESP + 0x74]
004ce8b4 LEA EDI,[ESP + 0x44]
004ce8b8 LEA EAX,[ESP + 0x44]
004ce8bc MOVSD.REP ES:EDI,ESI
004ce8be MOV EDX,dword ptr [EBP]
004ce8c1 XOR EDI,EDI
004ce8c3 PUSH EDI
004ce8c4 PUSH EAX
004ce8c5 MOV ECX,EBP
004ce8c7 CALL dword ptr [EDX + 0x70]
004ce8ca FLD float ptr [0x005a83f4]
004ce8d0 FDIV float ptr [ESP + 0xa8]
004ce8d7 CMP dword ptr [EBX + 0x35c],EDI
004ce8dd FLD float ptr [ESP + 0x38]
004ce8e1 FMUL ST1
004ce8e3 FMUL float ptr [ESP + 0xb0]
004ce8ea FSTP float ptr [ESP + 0x1c]
004ce8ee FLD float ptr [ESP + 0x3c]
004ce8f2 FMUL ST1
004ce8f4 FMUL float ptr [ESP + 0xb0]
004ce8fb FSTP float ptr [ESP + 0x20]
004ce8ff FMUL float ptr [ESP + 0x40]
004ce903 FMUL float ptr [ESP + 0xb0]
004ce90a FLD float ptr [0x005a9b30]
004ce910 JZ 0x004ce91a
004ce912 FSTP ST0
004ce914 FLD float ptr [0x005aa928]
004ce91a FMUL float ptr [ESP + 0xa8]
004ce921 LEA EBP,[EBX + 0x3b8]
004ce927 MOV ECX,EBP
004ce929 FSUBR float ptr [0x005a83f4]
004ce92f FLD ST0
004ce931 FMUL float ptr [EBP]
004ce934 FSTP float ptr [ESP + 0x10]
004ce938 MOV EDX,dword ptr [ESP + 0x10]
004ce93c FLD ST0
004ce93e FMUL float ptr [EBP + 0x4]
004ce941 FSTP float ptr [ESP + 0x14]
004ce945 MOV EAX,dword ptr [ESP + 0x14]
004ce949 FMUL float ptr [EBP + 0x8]
004ce94c MOV dword ptr [ECX],EDX
004ce94e MOV dword ptr [ECX + 0x4],EAX
004ce951 FSTP float ptr [ESP + 0x18]
004ce955 MOV EDX,dword ptr [ESP + 0x18]
004ce959 FLD ST0
004ce95b MOV dword ptr [ECX + 0x8],EDX
004ce95e CALL 0x00509980
004ce963 CDQ
004ce964 XOR EAX,EDX
004ce966 SUB EAX,EDX
004ce968 MOV dword ptr [ESP + 0x28],EAX
004ce96c FILD dword ptr [ESP + 0x28]
004ce970 FCOMP float ptr [0x005a83ec]
004ce976 FNSTSW AX
004ce978 TEST AH,0x5
004ce97b JP 0x004ce9a4
004ce97d MOV EAX,dword ptr [ESP + 0xac]
004ce984 FSTP ST0
004ce986 FLD float ptr [ESP + 0xa8]
004ce98d FMUL float ptr [EAX + 0x8]
004ce990 FST float ptr [EBX + 0x3c0]
004ce996 FADD float ptr [EBX + 0x398]
004ce99c FSTP float ptr [EBX + 0x398]
004ce9a2 JMP 0x004ce9b0
004ce9a4 FST float ptr [EBX + 0x398]
004ce9aa FSTP float ptr [EBX + 0x3c0]
004ce9b0 FLD float ptr [ESP + 0x1c]
004ce9b4 FADD float ptr [EBP]
004ce9b7 LEA ESI,[EBX + 0x390]
004ce9bd MOV dword ptr [ESP + 0x2c],0x0
004ce9c5 MOV ECX,ESI
004ce9c7 MOV dword ptr [ESP + 0x30],0x0
004ce9cf MOV dword ptr [ESP + 0x34],0x41200000
004ce9d7 FSTP float ptr [ESI]
004ce9d9 FLD float ptr [ESP + 0x20]
004ce9dd FADD float ptr [EBX + 0x3bc]
004ce9e3 FSTP float ptr [EBX + 0x394]
004ce9e9 FLD float ptr [ESI]
004ce9eb FADD float ptr [EBX + 0xb8]
004ce9f1 FSTP float ptr [ESP + 0x10]
004ce9f5 FLD float ptr [ESI + 0x4]
004ce9f8 FADD float ptr [EBX + 0xbc]
004ce9fe MOV EDX,dword ptr [ESP + 0x10]
004cea02 FSTP float ptr [ESP + 0x14]
004cea06 FLD float ptr [ESI + 0x8]
004cea09 FADD float ptr [EBX + 0xc0]
004cea0f MOV EAX,dword ptr [ESP + 0x14]
004cea13 MOV dword ptr [ECX],EDX
004cea15 MOV dword ptr [ECX + 0x4],EAX
004cea18 MOV EAX,dword ptr [EBX + 0xa8]
004cea1e FSTP float ptr [ESP + 0x18]
004cea22 MOV EDX,dword ptr [ESP + 0x18]
004cea26 CMP EAX,EDI
004cea28 MOV dword ptr [ECX + 0x8],EDX
004cea2b JZ 0x004ceb41
004cea31 CMP dword ptr [EBX + 0x3a8],EDI
004cea37 JZ 0x004ceb41
004cea3d FLD float ptr [ESP + 0xa8]
004cea44 MOV EAX,dword ptr [EBX]
004cea46 PUSH EDI
004cea47 LEA ECX,[ESP + 0x30]
004cea4b PUSH EDI
004cea4c PUSH ECX
004cea4d MOV ECX,EBX
004cea4f SUB ESP,0x8
004cea52 FSTP double ptr [ESP]
004cea55 PUSH ESI
004cea56 PUSH ESI
004cea57 CALL dword ptr [EAX + 0xfc]
004cea5d FLD float ptr [ESI]
004cea5f FCOMP float ptr [0x005a83e4]
004cea65 MOV dword ptr [EBX + 0x368],EAX
004cea6b FNSTSW AX
004cea6d TEST AH,0x44
004cea70 JP 0x004cea75
004cea72 MOV dword ptr [EBP],EDI
004cea75 FLD float ptr [EBX + 0x394]
004cea7b FCOMP float ptr [0x005a83e4]
004cea81 FNSTSW AX
004cea83 TEST AH,0x44
004cea86 JP 0x004cea8e
004cea88 MOV dword ptr [EBX + 0x3bc],EDI
004cea8e FLD float ptr [EBX + 0x398]
004cea94 FCOMP float ptr [0x005a83e4]
004cea9a FNSTSW AX
004cea9c TEST AH,0x44
004cea9f JP 0x004ceaa7
004ceaa1 MOV dword ptr [EBX + 0x3c0],EDI
004ceaa7 FLD float ptr [ESP + 0xa8]
004ceaae FMUL float ptr [EBX + 0x3ac]
004ceab4 LEA ECX,[EBX + 0x3ac]
004ceaba FSTP float ptr [ESP + 0x10]
004ceabe FLD float ptr [ESP + 0xa8]
004ceac5 FMUL float ptr [ECX + 0x4]
004ceac8 MOV EDX,dword ptr [ESP + 0x10]
004ceacc MOV dword ptr [ESP + 0x1c],EDX
004cead0 FSTP float ptr [ESP + 0x14]
004cead4 FLD float ptr [ESP + 0xa8]
004ceadb FMUL float ptr [ECX + 0x8]
004ceade MOV EAX,dword ptr [ESP + 0x14]
004ceae2 MOV dword ptr [ESP + 0x20],EAX
004ceae6 FSTP float ptr [ESP + 0x18]
004ceaea MOV EDX,dword ptr [ESP + 0x18]
004ceaee MOV dword ptr [ESP + 0x24],EDX
004ceaf2 CALL 0x0047ecf0
004ceaf7 FCOMP float ptr [0x005a8f74]
004ceafd FNSTSW AX
004ceaff AND EAX,0x4100
004ceb04 JNZ 0x004ceb2e
004ceb06 FLD float ptr [ESP + 0xa8]
004ceb0d PUSH EDI
004ceb0e LEA ECX,[ESP + 0x30]
004ceb12 MOV EAX,dword ptr [EBX]
004ceb14 PUSH EDI
004ceb15 PUSH ECX
004ceb16 LEA EDX,[ESP + 0x28]
004ceb1a SUB ESP,0x8
004ceb1d LEA ECX,[ESP + 0x30]
004ceb21 FSTP double ptr [ESP]
004ceb24 PUSH EDX
004ceb25 PUSH ECX
004ceb26 MOV ECX,EBX
004ceb28 CALL dword ptr [EAX + 0xfc]
004ceb2e MOV EAX,dword ptr [EBX + 0x368]
004ceb34 POP EDI
004ceb35 POP ESI
004ceb36 POP EBP
004ceb37 POP EBX
004ceb38 ADD ESP,0x94
004ceb3e RET 0xc
004ceb41 POP EDI
004ceb42 POP ESI
004ceb43 POP EBP
004ceb44 XOR EAX,EAX
004ceb46 POP EBX
004ceb47 ADD ESP,0x94
004ceb4d RET 0xc
