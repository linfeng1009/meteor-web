/* Original Meteor.exe static read-only export; sample not executed. */

undefined4 __thiscall FUN_004d51a0(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  if (param_2 == 2) {
    iVar4 = 1;
  }
  else if (param_2 == 6) {
    iVar4 = 7;
  }
  piVar1 = *(int **)(param_1 + 0x34);
  piVar2 = *(int **)(param_1 + 0x30);
  for (piVar3 = piVar2; (piVar3 != piVar1 && (*piVar3 != param_2)); piVar3 = piVar3 + 3) {
  }
  if ((piVar3 == piVar1) || (piVar3 == (int *)0x0)) {
    return 0;
  }
  if (piVar2 != piVar1) {
    do {
      if (*piVar2 == iVar4) break;
      piVar2 = piVar2 + 3;
    } while (piVar2 != piVar1);
    if ((piVar2 != piVar1) && (piVar2 != (int *)0x0)) {
      piVar3[2] = (piVar2[2] - piVar3[1]) + piVar2[1];
      return 1;
    }
  }
  return 0;
}

