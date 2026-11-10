/* Original Meteor.exe static read-only export; sample not executed. */

undefined4 __thiscall FUN_004d4d30(int *param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = 0;
  iVar1 = 0;
  if (param_2 == 2) {
    iVar4 = 1;
  }
  else if (param_2 == 6) {
    iVar4 = 7;
  }
  for (piVar3 = (int *)param_1[0xc]; (piVar3 != (int *)param_1[0xd] && (*piVar3 != param_2));
      piVar3 = piVar3 + 3) {
  }
  uVar5 = -(uint)(piVar3 != (int *)param_1[0xd]) & (uint)piVar3;
  if (iVar4 != 0) {
    iVar1 = (**(code **)(*param_1 + 0x34))(iVar4,0);
  }
  iVar2 = *(int *)(uVar5 + 8) + *(int *)(uVar5 + 4) + param_3;
  if (-1 < iVar2) {
    if ((iVar4 != 0) && (iVar1 < iVar2)) {
      *param_4 = (iVar1 - iVar2) + param_3;
      return 0;
    }
    *param_4 = param_3;
    return 0;
  }
  *param_4 = param_3 - iVar2;
  return 0;
}

