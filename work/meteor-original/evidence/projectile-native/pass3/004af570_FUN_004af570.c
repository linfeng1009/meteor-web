/* Original Meteor.exe static export @ 004af570; original sample not executed. */
/* XREF 005a9c60 DATA */
/* XREF 005aa3d0 DATA */
/* XREF 005aa528 DATA */

void __thiscall FUN_004af570(int param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iStack_8;
  int iStack_4;
  
  iVar5 = 0;
  if (0 < param_4) {
    do {
      uVar6 = *(uint *)(param_3 + iVar5 * 4) & 0xffff;
      iVar1 = *(int *)(param_1 + 0x3a8);
      iStack_8 = iVar1;
      iVar2 = *(int *)(iVar1 + 4);
      while (iVar2 != 0) {
        if (*(uint *)(iVar2 + 0x10) < param_2) {
          iVar2 = *(int *)(iVar2 + 0xc);
        }
        else {
          iStack_8 = iVar2;
          iVar2 = *(int *)(iVar2 + 8);
        }
      }
      if ((iStack_8 == iVar1) || (param_2 < *(uint *)(iStack_8 + 0x10))) {
        iStack_4 = iVar1;
        piVar3 = &iStack_4;
      }
      else {
        piVar3 = &iStack_8;
      }
      uVar4 = (**(code **)(*(int *)(*piVar3 + 0x88) + 0x40))
                        (*(undefined2 *)(param_3 + 2 + iVar5 * 4));
      uVar7 = param_2;
      FUN_00487830(uVar6,param_2,uVar4);
      FUN_005643f0(uVar6,uVar7,uVar4);
      iVar5 = iVar5 + 1;
    } while (iVar5 < param_4);
  }
  return;
}

