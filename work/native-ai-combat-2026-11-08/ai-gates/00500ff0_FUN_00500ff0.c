/* Original Meteor.exe static export @ 00500ff0; original sample not executed. */
/* XREF 005042ca UNCONDITIONAL_CALL */

void __thiscall FUN_00500ff0(int *param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x114))(param_2,0);
  }
  return;
}

