004deda0 MOV EDX,dword ptr [ESP + 0x8]
004deda4 PUSH ESI
004deda5 MOV ESI,dword ptr [ESP + 0x8]
004deda9 PUSH EDX
004dedaa PUSH ESI
004dedab CALL 0x004dd130
004dedb0 XOR EAX,EAX
004dedb2 CMP EDX,0x3a
004dedb5 JZ 0x004dedc9
004dedb7 CMP EDX,0x92
004dedbd JZ 0x004dedc9
004dedbf MOV dword ptr [ESI + 0x370],0x1
004dedc9 POP ESI
004dedca RET 0x8
