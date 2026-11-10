/* Original Meteor.exe static export @ 0048b610; original sample not executed. */
/* XREF 005a9310 DATA */

undefined4 __fastcall FUN_0048b610(int param_1)

{
  undefined4 uVar1;
  
  if (*(int **)(param_1 + 0x212c) == (int *)0x0) {
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x0048b621. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(**(int **)(param_1 + 0x212c) + 0x6c))();
  return uVar1;
}

