/* Original Meteor.exe static export @ 004cfd20; original sample not executed. */
/* XREF 005aa740 DATA */

undefined4 __thiscall FUN_004cfd20(int param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_004e3d80(param_2);
  if (piVar1 == (int *)0x0) {
    return 0;
  }
  if (*(int **)(param_1 + 0x348) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x348) + 0xc))(param_1);
  }
  (**(code **)(*piVar1 + 8))(param_1);
  *(int **)(param_1 + 0x348) = piVar1;
  return 1;
}

