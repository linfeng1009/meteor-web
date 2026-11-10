/* Original Meteor.exe static export @ 00500c40; original sample not executed. */
/* XREF 004fd185 UNCONDITIONAL_CALL */
/* XREF 004fd1fd UNCONDITIONAL_CALL */
/* XREF 004fd299 UNCONDITIONAL_CALL */
/* XREF 004fce99 UNCONDITIONAL_CALL */

void __fastcall FUN_00500c40(int *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00500c4d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*piVar1 + 0x108))();
    return;
  }
  return;
}

