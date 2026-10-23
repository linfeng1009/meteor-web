/* Meteor.exe original x86 @ 004d3cd0 */
/* Caller: 004d5359 */
/* Caller: 004d5371 */
/* Caller: 004d373f */
/* Caller: 004d60ba */

int __thiscall FUN_004d3cd0(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  piVar2 = (int *)(param_1 + 4);
  if ((int *)(param_2 + 4) != piVar2) {
    iVar1 = *(int *)(param_2 + 8);
    puVar6 = *(undefined4 **)(param_2 + 4);
    puVar8 = (undefined4 *)*piVar2;
    uVar3 = *(int *)(param_1 + 8) - (int)puVar8;
    uVar4 = iVar1 - (int)puVar6;
    if (uVar3 < uVar4) {
      puVar7 = puVar6;
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
      FUN_00403490((undefined1 *)((*(int *)(param_1 + 8) - *piVar2) + (int)puVar6),iVar1);
    }
    else {
      for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar3 = uVar4 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      FUN_00402b30(*piVar2 + uVar4,*(undefined4 *)(param_1 + 8));
    }
  }
  piVar2 = (int *)(param_1 + 0x10);
  if ((int *)(param_2 + 0x10) != piVar2) {
    iVar1 = *(int *)(param_2 + 0x14);
    puVar6 = *(undefined4 **)(param_2 + 0x10);
    puVar8 = (undefined4 *)*piVar2;
    uVar4 = *(int *)(param_1 + 0x14) - (int)puVar8;
    uVar3 = iVar1 - (int)puVar6;
    if (uVar4 < uVar3) {
      puVar7 = puVar6;
      for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      FUN_00403490((undefined1 *)((*(int *)(param_1 + 0x14) - *piVar2) + (int)puVar6),iVar1);
    }
    else {
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar8 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      iVar1 = *(int *)(param_1 + 0x14);
      iVar5 = *piVar2 + uVar3;
      if (iVar5 != iVar1) {
        FUN_005092c0(iVar5,iVar1,1);
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + (iVar5 - iVar1);
      }
    }
  }
  piVar2 = (int *)(param_1 + 0x1c);
  if ((int *)(param_2 + 0x1c) != piVar2) {
    iVar1 = *(int *)(param_2 + 0x20);
    puVar6 = *(undefined4 **)(param_2 + 0x1c);
    puVar8 = (undefined4 *)*piVar2;
    uVar3 = *(int *)(param_1 + 0x20) - (int)puVar8;
    uVar4 = iVar1 - (int)puVar6;
    if (uVar3 < uVar4) {
      puVar7 = puVar6;
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
      FUN_00403490((undefined1 *)((*(int *)(param_1 + 0x20) - *piVar2) + (int)puVar6),iVar1);
    }
    else {
      for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar3 = uVar4 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      FUN_00402b30(*piVar2 + uVar4,*(undefined4 *)(param_1 + 0x20));
    }
  }
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
  FUN_004d4000(param_2 + 0x30);
  return param_1;
}

