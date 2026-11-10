/* Original Meteor.exe static read-only source export; not executed. */

void __thiscall FUN_004881e0(int param_1,undefined4 param_2)

{
  int *piVar1;
  
  (**(code **)(*(int *)(param_1 + 0x2488) + 0xb4))(param_2);
  piVar1 = (int *)**(int **)(param_1 + 0x2960);
  if (piVar1 != *(int **)(param_1 + 0x2960)) {
    do {
      (**(code **)(*(int *)piVar1[2] + 0xb4))(param_2);
      piVar1 = (int *)*piVar1;
    } while (piVar1 != (int *)*(int *)(param_1 + 0x2960));
  }
  return;
}

