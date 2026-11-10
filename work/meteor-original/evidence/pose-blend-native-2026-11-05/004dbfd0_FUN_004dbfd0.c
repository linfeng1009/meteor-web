/* Original Meteor.exe static export @ 004dbfd0; original sample not executed. */
/* XREF 004d0378 UNCONDITIONAL_CALL */
/* XREF 0048d6a2 UNCONDITIONAL_CALL */
/* XREF 0048d6b8 UNCONDITIONAL_CALL */

void __thiscall FUN_004dbfd0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_0055d020(param_2,param_3);
  if (iVar1 != 3) {
    *(short *)(param_1 + 0x8a8) = *(short *)(param_1 + 0x8a8) + 1;
    *(undefined4 *)(param_1 + 0x8ac) = 0;
  }
  return;
}

