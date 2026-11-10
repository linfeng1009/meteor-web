004ecb80 PUSH -0x1
004ecb82 PUSH 0x5a3198
004ecb87 MOV EAX,FS:[0x0]
004ecb8d PUSH EAX
004ecb8e MOV dword ptr FS:[0x0],ESP
004ecb95 PUSH ECX
004ecb96 PUSH ESI
004ecb97 MOV ESI,ECX
004ecb99 MOV dword ptr [ESP + 0x4],ESI
004ecb9d CALL 0x004ed1e0
004ecba2 LEA ECX,[ESI + 0x3c0]
004ecba8 MOV dword ptr [ESP + 0x10],0x0
004ecbb0 CALL 0x005498c0
004ecbb5 MOV ECX,ESI
004ecbb7 MOV dword ptr [ESI],0x5ab228
004ecbbd MOV dword ptr [ESI + 0x10],0x5ab1f8
004ecbc4 CALL 0x004ecb20
004ecbc9 MOV ECX,dword ptr [ESP + 0x8]
004ecbcd MOV EAX,ESI
004ecbcf POP ESI
004ecbd0 MOV dword ptr FS:[0x0],ECX
004ecbd7 ADD ESP,0x10
004ecbda RET
