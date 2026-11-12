00585400 push ecx
00585401 push ebx
00585402 push esi
00585403 push edi
00585404 mov ebx, ecx
00585406 call 0x582000
0058540b mov eax, dword ptr [ebx + 0x1ec]
00585411 mov dword ptr [esp + 0xc], 0
00585419 mov eax, dword ptr [eax + 8]
0058541c dec eax
0058541d jne 0x58542f
0058541f fld dword ptr [ebx + 0x26c]
00585425 fmul dword ptr [0x5a83e8]
0058542b fstp dword ptr [esp + 0xc]
0058542f mov ecx, dword ptr [esp + 0xc]
00585433 xor edi, edi
00585435 mov dword ptr [ebx + 0x1fc], edi
0058543b mov dword ptr [ebx + 0x200], edi
00585441 mov dword ptr [ebx + 0x204], ecx
00585447 lea esi, [ebx + 0x158]
0058544d fld dword ptr [ebx + 0x26c]
00585453 fmul dword ptr [0x5a83e8]
00585459 fld dword ptr [ebx + 0x268]
0058545f fmul dword ptr [0x5a83e8]
00585465 mov ecx, esi
00585467 mov dword ptr [ebx + 0x1f8], 0x40400000
00585471 fstp dword ptr [ebx + 0x1f0]
00585477 fstp dword ptr [ebx + 0x1f4]
0058547d call 0x477200
00585482 mov edx, dword ptr [esp + 0xc]
00585486 push edi
00585487 push edx
00585488 push edi
00585489 push edi
0058548a mov ecx, esi
0058548c call 0x4781d0
00585491 push 0x3fc90fdb
00585496 mov ecx, esi
00585498 call 0x477f40
0058549d mov eax, dword ptr [ebx + 0x26c]
005854a3 mov ecx, dword ptr [ebx + 0x268]
005854a9 push eax
005854aa push ecx
005854ab mov ecx, dword ptr [ebx + 0x1ec]
005854b1 add ecx, 0x10c
005854b7 call 0x47c3a0
005854bc sub esp, 0x40
005854bf mov ecx, 0x10
005854c4 mov edi, esp
005854c6 rep movsd dword ptr es:[edi], dword ptr [esi]
005854c8 mov ecx, dword ptr [ebx + 0x1ec]
005854ce add ecx, 0x10c
005854d4 call 0x47de20
005854d9 pop edi
005854da pop esi
005854db pop ebx
005854dc pop ecx
005854dd ret 
