004fc610 MOV EAX,dword ptr [ESP + 0x4]
004fc614 FLD float ptr [EAX]
004fc616 FSUB float ptr [ECX + 0x18]
004fc619 FLD float ptr [EAX + 0x4]
004fc61c FSUB float ptr [ECX + 0x1c]
004fc61f FLD float ptr [EAX + 0x8]
004fc622 FSUB float ptr [ECX + 0x20]
004fc625 FMUL float ptr [ECX + 0x2c]
004fc628 FXCH
004fc62a FMUL float ptr [ECX + 0x28]
004fc62d FADDP
004fc62f FXCH
004fc631 FMUL float ptr [ECX + 0x24]
004fc634 FADDP
004fc636 FCOMP float ptr [0x005a83e4]
004fc63c FNSTSW AX
004fc63e AND EAX,0x4100
004fc643 JNZ 0x004fc64d
004fc645 MOV EAX,0x1
004fc64a RET 0x4
004fc64d XOR EAX,EAX
004fc64f RET 0x4
