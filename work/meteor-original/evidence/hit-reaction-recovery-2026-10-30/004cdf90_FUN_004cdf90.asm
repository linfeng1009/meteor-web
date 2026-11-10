004cdf90 MOV EAX,dword ptr [ECX + 0x60]
004cdf93 TEST EAX,EAX
004cdf95 JNZ 0x004cdfd5
004cdf97 MOV EDX,dword ptr [ECX + 0x64]
004cdf9a TEST EDX,EDX
004cdf9c JNZ 0x004cdfd3
004cdf9e CMP dword ptr [ECX + 0x378],0x1
004cdfa5 JNZ 0x004cdfb4
004cdfa7 MOV EAX,dword ptr [ECX]
004cdfa9 CALL dword ptr [EAX + 0xf8]
004cdfaf XOR EAX,EAX
004cdfb1 RET 0x8
004cdfb4 FLD double ptr [ESP + 0x4]
004cdfb8 MOV EDX,dword ptr [ECX]
004cdfba LEA EAX,[ECX + 0xd0]
004cdfc0 PUSH 0x3f800000
004cdfc5 PUSH EAX
004cdfc6 PUSH ECX
004cdfc7 FSTP float ptr [ESP]
004cdfca CALL dword ptr [EDX + 0xc8]
004cdfd0 RET 0x8
004cdfd3 TEST EAX,EAX
004cdfd5 JLE 0x004cdfdc
004cdfd7 MOV byte ptr [ESP + 0x4],0x66
004cdfdc TEST EAX,EAX
004cdfde JGE 0x004cdfe5
004cdfe0 MOV byte ptr [ESP + 0x4],0x62
004cdfe5 MOV EAX,dword ptr [ECX + 0x64]
004cdfe8 TEST EAX,EAX
004cdfea JLE 0x004cdff1
004cdfec MOV byte ptr [ESP + 0x4],0x72
004cdff1 JGE 0x004cdff8
004cdff3 MOV byte ptr [ESP + 0x4],0x6c
004cdff8 MOV EAX,dword ptr [ESP + 0x4]
004cdffc MOV EDX,dword ptr [ECX]
004cdffe PUSH 0x0
004ce000 PUSH EAX
004ce001 CALL dword ptr [EDX + 0x114]
004ce007 XOR EAX,EAX
004ce009 RET 0x8
