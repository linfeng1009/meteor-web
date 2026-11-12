00585360 push -1
00585362 push 0x5a69e8
00585367 mov eax, dword ptr fs:[0]
0058536d push eax
0058536e mov dword ptr fs:[0], esp
00585375 push ecx
00585376 mov eax, dword ptr [esp + 0x18]
0058537a push esi
0058537b mov esi, ecx
0058537d mov ecx, dword ptr [esp + 0x18]
00585381 push eax
00585382 push ecx
00585383 mov ecx, esi
00585385 mov dword ptr [esp + 0xc], esi
00585389 call 0x5811c0
0058538e mov dword ptr [esi], 0x5b0fb0
00585394 mov eax, dword ptr [0x72bbe0]
00585399 inc eax
0058539a push 0xb
0058539c mov dword ptr [0x72bbe0], eax
005853a1 mov dword ptr [esp + 0x14], 0
005853a9 mov dword ptr [esi + 4], 0xb
005853b0 mov dword ptr [esi + 0xc], 0x270
005853b7 call 0x58a6d0
005853bc add esp, 4
005853bf lea edx, [esi + 0x14]
005853c2 mov cl, byte ptr [eax]
005853c4 inc eax
005853c5 mov byte ptr [edx], cl
005853c7 inc edx
005853c8 test cl, cl
005853ca jne 0x5853c2
005853cc mov eax, 0x41200000
005853d1 push 0x5d2f14
005853d6 mov ecx, esi
005853d8 mov dword ptr [esi + 0x26c], eax
005853de mov dword ptr [esi + 0x268], eax
005853e4 call 0x581aa0
005853e9 mov ecx, dword ptr [esp + 8]
005853ed mov eax, esi
005853ef pop esi
005853f0 mov dword ptr fs:[0], ecx
005853f7 add esp, 0x10
005853fa ret 8
