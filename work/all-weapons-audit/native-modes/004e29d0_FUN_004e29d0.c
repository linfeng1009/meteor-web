/* Original Meteor.exe static export @ 004e29d0; original sample not executed. */
/* XREF 005aaf04 DATA */

void __thiscall FUN_004e29d0(int param_1,int *param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int iStack_4;
  
  uVar4 = param_3;
  iStack_4 = param_1;
  iVar1 = *(int *)(param_1 + 0x60);
  iVar3 = iVar1;
  iVar2 = *(int *)(iVar1 + 4);
  while (iVar2 != 0) {
    if (*(uint *)(iVar2 + 0x10) < param_3) {
      iVar2 = *(int *)(iVar2 + 0xc);
    }
    else {
      iVar3 = iVar2;
      iVar2 = *(int *)(iVar2 + 8);
    }
  }
  if ((iVar3 == iVar1) || (param_3 < *(uint *)(iVar3 + 0x10))) {
    iStack_4 = iVar1;
    piVar5 = &iStack_4;
  }
  else {
    piVar5 = (int *)&param_3;
  }
  param_3 = iVar3;
  if (*piVar5 != *(int *)(param_1 + 0x60)) {
    (**(code **)(*param_2 + 0x1d4))(*(undefined4 *)(*piVar5 + 0x14));
  }
  FUN_004dd130(param_2,uVar4);
  return;
}

