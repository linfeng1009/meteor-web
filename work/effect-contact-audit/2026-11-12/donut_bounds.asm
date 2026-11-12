005881a0 sub esp, 0x54
005881a3 push ebx
005881a4 push ebp
005881a5 push esi
005881a6 push edi
005881a7 mov ebx, ecx
005881a9 call 0x582000
005881ae mov eax, dword ptr [ebx + 0x1ec]
005881b4 mov dword ptr [esp + 0x10], 0
005881bc mov eax, dword ptr [eax + 8]
005881bf dec eax
005881c0 jne 0x5881d8
005881c2 fld dword ptr [ebx + 0x26c]
005881c8 fsub dword ptr [ebx + 0x268]
005881ce fmul dword ptr [0x5a83e8]
005881d4 fstp dword ptr [esp + 0x10]
005881d8 mov ecx, dword ptr [esp + 0x10]
005881dc xor esi, esi
005881de mov dword ptr [ebx + 0x1fc], esi
005881e4 mov dword ptr [ebx + 0x200], esi
005881ea mov dword ptr [ebx + 0x204], ecx
005881f0 mov edx, dword ptr [ebx + 0x26c]
005881f6 fld dword ptr [ebx + 0x26c]
005881fc fsub dword ptr [ebx + 0x268]
00588202 mov dword ptr [esp + 0x14], edx
00588206 lea ebp, [ebx + 0x158]
0058820c fld dword ptr [esp + 0x14]
00588210 fadd st(0), st(0)
00588212 fst dword ptr [ebx + 0x1f0]
00588218 fstp dword ptr [ebx + 0x1f4]
0058821e fstp dword ptr [ebx + 0x1f8]
00588224 fld dword ptr [ebx + 0x1f0]
0058822a fmul dword ptr [0x5a83e8]
00588230 fstp dword ptr [esp + 0x18]
00588234 fld dword ptr [ebx + 0x1f4]
0058823a fmul dword ptr [0x5a83e8]
00588240 mov eax, dword ptr [esp + 0x18]
00588244 fstp dword ptr [esp + 0x1c]
00588248 fld dword ptr [ebx + 0x1f8]
0058824e fmul dword ptr [0x5a83e8]
00588254 mov ecx, dword ptr [esp + 0x1c]
00588258 mov dword ptr [ebx + 0x1f0], eax
0058825e mov dword ptr [ebx + 0x1f4], ecx
00588264 mov ecx, ebp
00588266 fstp dword ptr [esp + 0x20]
0058826a mov edx, dword ptr [esp + 0x20]
0058826e mov dword ptr [ebx + 0x1f8], edx
00588274 call 0x477200
00588279 mov eax, dword ptr [esp + 0x10]
0058827d push esi
0058827e push eax
0058827f push esi
00588280 push esi
00588281 mov ecx, ebp
00588283 call 0x4781d0
00588288 lea ecx, [esp + 0x24]
0058828c push ecx
0058828d mov ecx, ebp
0058828f call 0x477ad0
00588294 mov edx, dword ptr [ebx + 0x27c]
0058829a lea edi, [ebx + 0x198]
005882a0 mov ecx, 0x10
005882a5 mov esi, eax
005882a7 mov eax, dword ptr [ebx + 0x278]
005882ad push edx
005882ae mov edx, dword ptr [ebx + 0x270]
005882b4 push eax
005882b5 mov eax, dword ptr [ebx + 0x26c]
005882bb rep movsd dword ptr es:[edi], dword ptr [esi]
005882bd mov ecx, dword ptr [ebx + 0x274]
005882c3 push ecx
005882c4 mov ecx, dword ptr [ebx + 0x268]
005882ca push edx
005882cb push eax
005882cc push ecx
005882cd mov ecx, dword ptr [ebx + 0x1ec]
005882d3 add ecx, 0x10c
005882d9 call 0x47d8b0
005882de sub esp, 0x40
005882e1 mov ecx, 0x10
005882e6 mov esi, ebp
005882e8 mov edi, esp
005882ea rep movsd dword ptr es:[edi], dword ptr [esi]
005882ec mov ecx, dword ptr [ebx + 0x1ec]
005882f2 add ecx, 0x10c
005882f8 call 0x47de20
005882fd pop edi
005882fe pop esi
005882ff pop ebp
00588300 pop ebx
00588301 add esp, 0x54
00588304 ret 
