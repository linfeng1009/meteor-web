/* Original Meteor.exe static export @ 005012a0; original sample not executed. */
/* XREF 004fd5e4 UNCONDITIONAL_CALL */
/* XREF 004fc5fa UNCONDITIONAL_CALL */
/* XREF 00501263 UNCONDITIONAL_CALL */
/* XREF 00504407 UNCONDITIONAL_CALL */
/* XREF 00504442 UNCONDITIONAL_CALL */

void __fastcall FUN_005012a0(int *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x005012bb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*piVar1 + 0xac))();
    return;
  }
  return;
}

