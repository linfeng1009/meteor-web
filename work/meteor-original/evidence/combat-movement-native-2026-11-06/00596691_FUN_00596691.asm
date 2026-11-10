00596691 PUSH EBP
00596692 MOV EBP,ESP
00596694 SUB ESP,0x30
00596697 FLD double ptr [EBP + 0x38]
0059669a FADD double ptr [EBP + 0x30]
0059669d FSTP double ptr [EBP + -0x10]
005966a0 FLD double ptr [EBP + 0x30]
005966a3 FMUL double ptr [EBP + 0x30]
005966a6 FLD double ptr [EBP + 0x30]
005966a9 FMUL double ptr [EBP + 0x38]
005966ac FADDP
005966ae FLD double ptr [EBP + 0x38]
005966b1 FMUL double ptr [EBP + 0x38]
005966b4 FADDP
005966b6 FSTP double ptr [EBP + -0x20]
005966b9 FLD double ptr [EBP + 0x30]
005966bc FMUL double ptr [EBP + 0x30]
005966bf FMUL double ptr [EBP + 0x30]
005966c2 FLD double ptr [EBP + 0x30]
005966c5 FMUL double ptr [EBP + 0x30]
005966c8 FMUL double ptr [EBP + 0x38]
005966cb FADDP
005966cd FLD double ptr [EBP + 0x38]
005966d0 FMUL double ptr [EBP + 0x38]
005966d3 FMUL double ptr [EBP + 0x30]
005966d6 FADDP
005966d8 FLD double ptr [EBP + 0x38]
005966db FMUL double ptr [EBP + 0x38]
005966de FMUL double ptr [EBP + 0x38]
005966e1 FADDP
005966e3 FSTP double ptr [EBP + -0x28]
005966e6 FLD double ptr [0x005a8460]
005966ec FMUL double ptr [EBP + 0x10]
005966ef FLD double ptr [0x005a8468]
005966f5 FMUL double ptr [EBP + 0x28]
005966f8 FSUBR double ptr [EBP + -0x10]
005966fb FMULP
005966fd FSTP double ptr [EBP + -0x8]
00596700 FLD double ptr [EBP + 0x18]
00596703 FDIV double ptr [0x005a9bd0]
00596709 FLD double ptr [0x005a9bd0]
0059670f FMUL double ptr [EBP + 0x28]
00596712 FLD double ptr [EBP + -0x10]
00596715 FSUB double ptr [EBP + 0x28]
00596718 FMULP
0059671a FSUBR double ptr [EBP + -0x20]
0059671d FMULP
0059671f FSTP double ptr [EBP + -0x30]
00596722 FLD double ptr [EBP + 0x20]
00596725 FDIV double ptr [0x005a9eb0]
0059672b FLD double ptr [0x005a8468]
00596731 FMUL double ptr [EBP + 0x28]
00596734 FLD double ptr [0x005a8468]
0059673a FMUL double ptr [EBP + -0x20]
0059673d FLD double ptr [0x005a9bd0]
00596743 FMUL double ptr [EBP + -0x10]
00596746 FLD double ptr [0x005a8468]
0059674c FMUL double ptr [EBP + 0x28]
0059674f FSUBP
00596751 FMUL double ptr [EBP + 0x28]
00596754 FSUBP
00596756 FMULP
00596758 FSUBR double ptr [EBP + -0x28]
0059675b FMULP
0059675d FSTP double ptr [EBP + -0x18]
00596760 FLD double ptr [EBP + 0x38]
00596763 FSUB double ptr [EBP + 0x30]
00596766 FLD double ptr [EBP + 0x8]
00596769 FADD double ptr [EBP + -0x8]
0059676c FADD double ptr [EBP + -0x30]
0059676f FADD double ptr [EBP + -0x18]
00596772 FMULP
00596774 MOV ESP,EBP
00596776 POP EBP
00596777 RET
