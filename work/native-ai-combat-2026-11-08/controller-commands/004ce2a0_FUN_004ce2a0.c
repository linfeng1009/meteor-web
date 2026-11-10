/* Original Meteor.exe static export @ 004ce2a0; original sample not executed. */
/* XREF 005aa750 DATA */

void __thiscall FUN_004ce2a0(int *param_1,int param_2)

{
  if (param_2 != 0) {
    param_1[0xde] = 1;
    return;
  }
  param_1[0xde] = 0;
                    /* WARNING: Could not recover jumptable at 0x004ce2c9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0xbc))();
  return;
}

