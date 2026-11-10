004fb730 PUSH ESI
004fb731 MOV ESI,ECX
004fb733 CALL 0x004fda00
004fb738 XOR EAX,EAX
004fb73a OR ECX,0xffffffff
004fb73d MOV dword ptr [ESI + 0x80],EAX
004fb743 MOV dword ptr [ESI + 0x54],ECX
004fb746 MOV dword ptr [ESI + 0x50],ECX
004fb749 MOV dword ptr [ESI + 0x5c],ECX
004fb74c MOV dword ptr [ESI + 0x58],ECX
004fb74f MOV dword ptr [ESI + 0x4],EAX
004fb752 MOV dword ptr [ESI + 0xc],EAX
004fb755 MOV dword ptr [ESI + 0x10],EAX
004fb758 MOV dword ptr [ESI + 0x8],ECX
004fb75b MOV byte ptr [ESI + 0x62],AL
004fb75e MOV dword ptr [ESI + 0x11c],EAX
004fb764 POP ESI
004fb765 RET
