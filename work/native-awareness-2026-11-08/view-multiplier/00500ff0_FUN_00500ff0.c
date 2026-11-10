/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall FUN_00500ff0(int *param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x114))(param_2,0);
  }
  return;
}

