/* Original Meteor.exe static export @ 004dc6a0; original sample not executed. */
/* XREF 005aaa4c DATA */

void __thiscall FUN_004dc6a0(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int unaff_EBX;
  uint uVar4;
  
  uVar4 = 0xc;
  iVar1 = FUN_005569b0(s_d_wpnR_005c92cc);
  iVar2 = FUN_005569b0(s_d_wpnL_005c93b8);
  if (param_2 == iVar1) {
    uVar4 = 0xd;
  }
  if (param_2 == iVar2) {
    uVar4 = uVar4 | 2;
  }
  iVar1 = (**(code **)(*param_1 + 0x60))(uVar4);
  if (iVar1 == 0) {
    piVar3 = (int *)FUN_005598c0(param_2);
    if (piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 8))(1);
    }
  }
  (**(code **)(*param_1 + 0x18))(param_2,param_3);
  param_1[0x22e] = unaff_EBX;
  return;
}

