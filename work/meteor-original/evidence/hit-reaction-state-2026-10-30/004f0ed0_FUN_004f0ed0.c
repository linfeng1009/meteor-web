/* Original Meteor.exe static export @ 004f0ed0; original sample not executed. */
/* XREF 005aa0ec DATA */
/* XREF 005ab574 DATA */
/* XREF 005ab9b4 DATA */
/* XREF 005ab334 DATA */

void __fastcall FUN_004f0ed0(int *param_1)

{
  int *piVar1;
  
  if ((undefined4 *)param_1[0x8e] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)param_1[0x8e])(1);
    param_1[0x8e] = 0;
  }
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
                    /* WARNING: Could not recover jumptable at 0x004f0ef9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*piVar1 + 0x150))();
  return;
}

