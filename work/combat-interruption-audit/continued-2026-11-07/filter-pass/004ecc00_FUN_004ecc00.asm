004ecc00 PUSH -0x1
004ecc02 PUSH 0x5a31b8
004ecc07 MOV EAX,FS:[0x0]
004ecc0d PUSH EAX
004ecc0e MOV dword ptr FS:[0x0],ESP
004ecc15 PUSH ECX
004ecc16 PUSH ESI
004ecc17 MOV ESI,ECX
004ecc19 MOV dword ptr [ESP + 0x4],ESI
004ecc1d MOV dword ptr [ESI],0x5ab228
004ecc23 MOV dword ptr [ESI + 0x10],0x5ab1f8
004ecc2a MOV dword ptr [ESP + 0x10],0x0
004ecc32 CALL 0x004ecdd0
004ecc37 MOV ECX,ESI
004ecc39 MOV dword ptr [ESP + 0x10],0xffffffff
004ecc41 CALL 0x004ed450
004ecc46 MOV ECX,dword ptr [ESP + 0x8]
004ecc4a POP ESI
004ecc4b MOV dword ptr FS:[0x0],ECX
004ecc52 ADD ESP,0x10
004ecc55 RET
