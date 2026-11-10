/* Original Meteor.exe static export @ 004dbf80; original sample not executed. */
/* XREF 0048f47b UNCONDITIONAL_CALL */
/* XREF 004cfc6d UNCONDITIONAL_CALL */
/* XREF 004dbf77 UNCONDITIONAL_CALL */

void __thiscall
FUN_004dbf80(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  
  iVar1 = FUN_0055d260(param_2,param_3,param_4,param_5,1);
  if (iVar1 != 0) {
    *(short *)(param_1 + 0x8a8) = *(short *)(param_1 + 0x8a8) + 1;
    *(undefined4 *)(param_1 + 0x8ac) = param_3;
    *(undefined4 *)(param_1 + 0x8b0) = param_5;
  }
  return;
}

