/* Original Meteor.exe static export @ 00500c60; original sample not executed. */
/* XREF 004fd5da UNCONDITIONAL_CALL */
/* XREF 004fc5f0 UNCONDITIONAL_CALL */
/* XREF 00501253 UNCONDITIONAL_CALL */
/* XREF 0050399b UNCONDITIONAL_CALL */
/* XREF 004fdea8 UNCONDITIONAL_CALL */
/* XREF 004fdeb9 UNCONDITIONAL_CALL */
/* XREF 00504061 UNCONDITIONAL_CALL */
/* XREF 0050441d UNCONDITIONAL_CALL */
/* XREF 00504438 UNCONDITIONAL_CALL */

void __fastcall FUN_00500c60(int *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00500c7b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*piVar1 + 0xa8))();
    return;
  }
  return;
}

