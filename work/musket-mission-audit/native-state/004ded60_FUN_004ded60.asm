004ded60 MOV EAX,dword ptr [ESP + 0x4]
004ded64 CMP dword ptr [EAX + 0x36c],0x1
004ded6b JNZ 0x004ded77
004ded6d MOV dword ptr [EAX + 0x36c],0x0
004ded77 MOV EAX,0x1
004ded7c RET 0x4
