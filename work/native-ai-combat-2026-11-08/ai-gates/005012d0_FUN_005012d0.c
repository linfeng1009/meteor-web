/* Original Meteor.exe static export @ 005012d0; original sample not executed. */
/* XREF 00503c8b UNCONDITIONAL_CALL */
/* XREF 00504d65 UNCONDITIONAL_CALL */
/* XREF 00504160 UNCONDITIONAL_CALL */

void __fastcall FUN_005012d0(int *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x005012dd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*piVar1 + 0xb0))();
    return;
  }
  return;
}

