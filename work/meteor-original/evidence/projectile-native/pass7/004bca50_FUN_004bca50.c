/* Original Meteor.exe static export @ 004bca50; original sample not executed. */
/* XREF 005aa188 DATA */

undefined4 __thiscall FUN_004bca50(int param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x3c8 + *(int *)(param_1 + 0x3f0) * 4);
  if (piVar1 == (int *)0x0) {
    return 0xffffffff;
  }
  if (*param_2 == 0) {
    if (piVar1[0x27] != 3) {
      (**(code **)(*piVar1 + 0x58))(0);
    }
  }
  else if ((*param_2 == 1) && (piVar1[0x27] != 3)) {
    (**(code **)(*piVar1 + 0x58))(1);
    return 0;
  }
  return 0;
}

