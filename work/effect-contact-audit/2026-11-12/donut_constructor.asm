005880d0 push -1
005880d2 push 0x5a6b18
005880d7 mov eax, dword ptr fs:[0]
005880dd push eax
005880de mov dword ptr fs:[0], esp
005880e5 push ecx
005880e6 mov eax, dword ptr [esp + 0x18]
005880ea push esi
005880eb mov esi, ecx
005880ed mov ecx, dword ptr [esp + 0x18]
005880f1 push eax
005880f2 push ecx
005880f3 mov ecx, esi
005880f5 mov dword ptr [esp + 0xc], esi
005880f9 call 0x5811c0
005880fe mov dword ptr [esi], 0x5b11d0
00588104 mov eax, dword ptr [0x72bce4]
00588109 inc eax
0058810a push 7
0058810c mov dword ptr [0x72bce4], eax
00588111 mov dword ptr [esp + 0x14], 0
00588119 mov dword ptr [esi + 4], 7
00588120 mov dword ptr [esi + 0xc], 0x280
00588127 call 0x58a6d0
0058812c add esp, 4
0058812f lea edx, [esi + 0x14]
00588132 mov cl, byte ptr [eax]
00588134 inc eax
00588135 mov byte ptr [edx], cl
00588137 inc edx
00588138 test cl, cl
0058813a jne 0x588132
0058813c mov eax, 0x43b40000
00588141 push 0x5d2f58
00588146 mov ecx, esi
00588148 mov dword ptr [esi + 0x268], 0x41700000
00588152 mov dword ptr [esi + 0x26c], 0x41c80000
0058815c mov dword ptr [esi + 0x270], 0
00588166 mov dword ptr [esi + 0x274], eax
0058816c mov dword ptr [esi + 0x278], 0
00588176 mov dword ptr [esi + 0x27c], eax
0058817c call 0x581aa0
00588181 mov ecx, dword ptr [esp + 8]
00588185 mov eax, esi
00588187 pop esi
00588188 mov dword ptr fs:[0], ecx
0058818f add esp, 0x10
00588192 ret 8
