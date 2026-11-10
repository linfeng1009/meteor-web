004cafb0 PUSH ESI
004cafb1 MOV ESI,ECX
004cafb3 PUSH EDI
004cafb4 MOV EAX,dword ptr [ESI]
004cafb6 CALL dword ptr [EAX + 0x64]
004cafb9 XOR EDI,EDI
004cafbb MOV dword ptr [ESI + 0x360],0x1
004cafc5 MOV dword ptr [ESI + 0x3cc],EDI
004cafcb MOV dword ptr [ESI + 0x374],EDI
004cafd1 MOV dword ptr [ESI + 0x3d0],0x1869f
004cafdb MOV dword ptr [ESI + 0x3c8],EDI
004cafe1 MOV dword ptr [ESI + 0x3c4],EDI
004cafe7 MOV dword ptr [ESI + 0x36c],EDI
004cafed MOV dword ptr [ESI + 0x370],EDI
004caff3 MOV dword ptr [ESI + 0x350],EDI
004caff9 MOV dword ptr [ESI + 0x354],EDI
004cafff MOV dword ptr [ESI + 0xe8],EDI
004cb005 MOV dword ptr [ESI + 0xa8],EDI
004cb00b MOV dword ptr [ESI + 0x368],EDI
004cb011 MOV dword ptr [ESI + 0x380],EDI
004cb017 MOV dword ptr [ESI + 0x37c],EDI
004cb01d MOV dword ptr [ESI + 0x3a8],0x1
004cb027 MOV dword ptr [ESI + 0x390],EDI
004cb02d MOV dword ptr [ESI + 0x394],EDI
004cb033 MOV dword ptr [ESI + 0x398],EDI
004cb039 MOV dword ptr [ESI + 0xc4],EDI
004cb03f MOV dword ptr [ESI + 0xc8],EDI
004cb045 MOV dword ptr [ESI + 0xcc],EDI
004cb04b MOV EDX,dword ptr [ESI + 0x390]
004cb051 MOV EAX,dword ptr [ESI + 0x394]
004cb057 LEA ECX,[ESI + 0x384]
004cb05d PUSH EDI
004cb05e MOV dword ptr [ECX],EDX
004cb060 MOV EDX,dword ptr [ESI + 0x398]
004cb066 MOV dword ptr [ECX + 0x4],EAX
004cb069 MOV EAX,0xc8
004cb06e MOV dword ptr [ECX + 0x8],EDX
004cb071 MOV dword ptr [ESI + 0x39c],EDI
004cb077 MOV dword ptr [ESI + 0x3a0],EDI
004cb07d MOV dword ptr [ESI + 0x3a4],0x3f800000
004cb087 MOV dword ptr [ESI + 0xd0],EDI
004cb08d MOV dword ptr [ESI + 0xd4],EDI
004cb093 MOV dword ptr [ESI + 0xd8],0xc45c8000
004cb09d MOV dword ptr [ESI + 0x70],EAX
004cb0a0 MOV dword ptr [ESI + 0x74],EAX
004cb0a3 MOV EAX,dword ptr [ESI]
004cb0a5 MOV ECX,ESI
004cb0a7 MOV dword ptr [ESI + 0xdc],EDI
004cb0ad MOV dword ptr [ESI + 0xe0],EDI
004cb0b3 MOV dword ptr [ESI + 0xe4],EDI
004cb0b9 MOV dword ptr [ESI + 0x348],EDI
004cb0bf CALL dword ptr [EAX + 0x98]
004cb0c5 MOV dword ptr [ESI + 0x34c],EDI
004cb0cb MOV dword ptr [ESI + 0x358],EDI
004cb0d1 MOV dword ptr [ESI + 0x364],EDI
004cb0d7 MOV dword ptr [ESI + 0x35c],0x1
004cb0e1 MOV dword ptr [ESI + 0x3ac],EDI
004cb0e7 MOV dword ptr [ESI + 0x3b0],EDI
004cb0ed MOV dword ptr [ESI + 0x3b4],EDI
004cb0f3 LEA ECX,[ESI + 0x3d4]
004cb0f9 MOV dword ptr [ESI + 0xb8],EDI
004cb0ff MOV dword ptr [ESI + 0xbc],EDI
004cb105 MOV dword ptr [ESI + 0xc0],EDI
004cb10b MOV dword ptr [ESI + 0x3b8],EDI
004cb111 MOV dword ptr [ESI + 0x3bc],EDI
004cb117 MOV dword ptr [ESI + 0x3c0],EDI
004cb11d MOV EDX,dword ptr [ECX]
004cb11f PUSH 0x5c9c24
004cb124 CALL dword ptr [EDX + 0x20]
004cb127 MOV dword ptr [ESI + 0x524],EDI
004cb12d POP EDI
004cb12e POP ESI
004cb12f RET
