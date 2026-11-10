/* Original Meteor.exe static export @ 004cb700; original sample not executed. */
/* XREF 005aa858 DATA */

void __thiscall FUN_004cb700(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  piVar1 = (int *)(param_1 + 0x2e8);
  if (param_2 != piVar1) {
    iVar2 = param_2[1];
    puVar5 = (undefined4 *)*param_2;
    puVar8 = (undefined4 *)*piVar1;
    uVar3 = *(int *)(param_1 + 0x2ec) - (int)puVar8;
    uVar4 = iVar2 - (int)puVar5;
    if (uVar3 < uVar4) {
      puVar7 = puVar5;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      FUN_00403490((undefined1 *)((int)puVar5 + (*(int *)(param_1 + 0x2ec) - *piVar1)),iVar2);
    }
    else {
      for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar3 = uVar4 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      iVar2 = *(int *)(param_1 + 0x2ec);
      iVar6 = *piVar1 + uVar4;
      if (iVar6 != iVar2) {
        FUN_005092c0(iVar6,iVar2,1);
        *(int *)(param_1 + 0x2ec) = *(int *)(param_1 + 0x2ec) + (iVar6 - iVar2);
        return;
      }
    }
  }
  return;
}

