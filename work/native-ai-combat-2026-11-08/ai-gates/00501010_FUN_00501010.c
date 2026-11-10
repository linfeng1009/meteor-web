/* Original Meteor.exe static export @ 00501010; original sample not executed. */
/* XREF 004fde38 UNCONDITIONAL_CALL */

void __fastcall FUN_00501010(int *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0050101d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*piVar1 + 0x1c8))();
    return;
  }
  return;
}

