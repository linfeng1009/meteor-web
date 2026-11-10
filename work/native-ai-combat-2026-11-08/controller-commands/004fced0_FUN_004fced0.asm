004fced0 FLD float ptr [ECX + 0x3c]
004fced3 FSUB float ptr [ECX + 0xe0]
004fced9 FABS
004fcedb FLD float ptr [ESP + 0x4]
004fcedf FCOMPP
004fcee1 FNSTSW AX
004fcee3 AND EAX,0x100
004fcee8 JNZ 0x004fcef2
004fceea MOV EAX,0x1
004fceef RET 0x4
004fcef2 XOR EAX,EAX
004fcef4 RET 0x4
