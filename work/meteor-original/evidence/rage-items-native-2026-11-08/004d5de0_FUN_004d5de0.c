/* Original Meteor.exe static export @ 004d5de0; original sample not executed. */
/* XREF 005a94c0 DATA */

int __thiscall FUN_004d5de0(int param_1,int param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = *(int **)(param_1 + 0x30);
      (piVar1 != *(int **)(param_1 + 0x34) && (*piVar1 != param_2)); piVar1 = piVar1 + 3) {
  }
  if ((piVar1 == *(int **)(param_1 + 0x34)) || (piVar1 == (int *)0x0)) {
    if (param_3 != (int *)0x0) {
      *param_3 = 0;
    }
    iVar2 = 0;
  }
  else {
    iVar2 = piVar1[2] + piVar1[1];
    if (param_3 != (int *)0x0) {
      *param_3 = piVar1[1];
      return iVar2;
    }
  }
  return iVar2;
}

