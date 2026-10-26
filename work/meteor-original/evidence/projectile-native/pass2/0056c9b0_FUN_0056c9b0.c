/* Original Meteor.exe static export @ 0056c9b0; original sample not executed. */
/* XREF 00560ab8 DATA */

undefined4 FUN_0056c9b0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (*(int *)(param_1 + 4) < 2) {
    return 0;
  }
  iVar4 = **(int **)(param_1 + 8);
  iVar1 = (*(int **)(param_1 + 8))[1];
  iVar5 = *(int *)(iVar4 + 4);
  if ((iVar5 < 3) || (4 < iVar5)) {
    iVar3 = param_1;
    if ((6 < iVar5) && (iVar5 < 9)) {
      iVar3 = FUN_00564fc0(*(undefined4 *)(iVar4 + 0xc));
    }
  }
  else {
    iVar3 = FUN_00564f90(*(undefined4 *)(iVar4 + 8));
  }
  if (iVar3 != 0) {
    uVar2 = *(undefined4 *)(iVar3 + 0x20);
    iVar4 = FUN_00567220();
    if (iVar4 != 0) {
      iVar4 = *(int *)(iVar1 + 4);
      if ((iVar4 < 3) || (4 < iVar4)) {
        iVar5 = param_1;
        if ((6 < iVar4) && (iVar4 < 9)) {
          uStack_8 = FUN_00566d40(*(undefined4 *)(iVar1 + 0xc));
          iVar5 = FUN_00567250(uStack_8,0);
        }
      }
      else {
        uStack_8 = *(undefined4 *)(iVar1 + 8);
        iVar5 = FUN_00567250(uStack_8,0);
      }
      if (iVar5 != 0) {
        puVar6 = (undefined4 *)FUN_0047b740();
        puVar7 = (undefined4 *)(*(int *)(iVar3 + 0x28) + 0x98);
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar6 = puVar6 + 1;
        }
        FUN_0047b750();
        if (*(int *)(param_1 + 4) == 3) {
          iVar4 = *(int *)(*(int *)(*(int *)(param_1 + 8) + 8) + 8);
          FUN_00566200(CONCAT31((int3)((uint)iVar4 >> 8),iVar4 != 0));
        }
      }
      if (DAT_0072b6a8 != 0) {
        (*(code *)PTR_FUN_005d1784)(2,uVar2,8,uStack_8,uStack_4);
      }
      return 1;
    }
    return 0;
  }
  return 0;
}

