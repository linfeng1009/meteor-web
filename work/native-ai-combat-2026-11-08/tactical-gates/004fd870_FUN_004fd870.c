/* Original Meteor.exe static export @ 004fd870; original sample not executed. */
/* XREF 004f9975 UNCONDITIONAL_CALL */
/* XREF 005045f9 UNCONDITIONAL_CALL */
/* XREF 00504649 UNCONDITIONAL_CALL */
/* XREF 00504660 UNCONDITIONAL_CALL */
/* XREF 005048e1 UNCONDITIONAL_CALL */
/* XREF 00504685 UNCONDITIONAL_CALL */
/* XREF 00504b2b UNCONDITIONAL_CALL */
/* XREF 00504d6f UNCONDITIONAL_CALL */
/* XREF 00503ea0 UNCONDITIONAL_CALL */
/* XREF 005041ab UNCONDITIONAL_CALL */
/* XREF 00504551 UNCONDITIONAL_CALL */
/* XREF 00504920 UNCONDITIONAL_CALL */
/* XREF 00504948 UNCONDITIONAL_CALL */
/* XREF 005049bd UNCONDITIONAL_CALL */
/* XREF 00504a3e UNCONDITIONAL_CALL */
/* XREF 00504a56 UNCONDITIONAL_CALL */

void __fastcall FUN_004fd870(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  iVar2 = *(int *)(param_1 + 0x6c);
  if (*(int *)(param_1 + 0x68) == iVar2) {
    return;
  }
  if (*(undefined **)(iVar2 + -0x24) == &DAT_00504be0) {
    piVar1 = (int *)(param_1 + 0x8c);
    if ((int *)(iVar2 + -0x20) != piVar1) {
      iVar3 = *(int *)(iVar2 + -0x1c);
      puVar7 = *(undefined4 **)(iVar2 + -0x20);
      puVar9 = (undefined4 *)*piVar1;
      uVar4 = *(int *)(param_1 + 0x90) - (int)puVar9;
      uVar5 = iVar3 - (int)puVar7;
      if (uVar4 < uVar5) {
        puVar8 = puVar7;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar9 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar9 = puVar9 + 1;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar9 = *(undefined1 *)puVar8;
          puVar8 = (undefined4 *)((int)puVar8 + 1);
          puVar9 = (undefined4 *)((int)puVar9 + 1);
        }
        FUN_00403490((undefined1 *)((int)puVar7 + (*(int *)(param_1 + 0x90) - *piVar1)),iVar3);
      }
      else {
        for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar9 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar9 = puVar9 + 1;
        }
        for (uVar4 = uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
          puVar7 = (undefined4 *)((int)puVar7 + 1);
          puVar9 = (undefined4 *)((int)puVar9 + 1);
        }
        iVar3 = *(int *)(param_1 + 0x90);
        iVar6 = *piVar1 + uVar5;
        if (iVar6 != iVar3) {
          FUN_005092c0(iVar6,iVar3,1);
          *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + (iVar6 - iVar3);
        }
      }
    }
    piVar1 = (int *)(param_1 + 0x98);
    if ((int *)(iVar2 + -0x14) != piVar1) {
      iVar3 = *(int *)(iVar2 + -0x10);
      puVar7 = *(undefined4 **)(iVar2 + -0x14);
      puVar9 = (undefined4 *)*piVar1;
      uVar5 = *(int *)(param_1 + 0x9c) - (int)puVar9;
      uVar4 = iVar3 - (int)puVar7;
      if (uVar5 < uVar4) {
        puVar8 = puVar7;
        for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar9 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar9 = puVar9 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar9 = *(undefined1 *)puVar8;
          puVar8 = (undefined4 *)((int)puVar8 + 1);
          puVar9 = (undefined4 *)((int)puVar9 + 1);
        }
        FUN_00403490((undefined1 *)((*(int *)(param_1 + 0x9c) - *piVar1) + (int)puVar7),iVar3);
      }
      else {
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar9 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar9 = puVar9 + 1;
        }
        for (uVar5 = uVar4 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
          puVar7 = (undefined4 *)((int)puVar7 + 1);
          puVar9 = (undefined4 *)((int)puVar9 + 1);
        }
        iVar3 = *(int *)(param_1 + 0x9c);
        iVar6 = *piVar1 + uVar4;
        if (iVar6 != iVar3) {
          FUN_005092c0(iVar6,iVar3,1);
          *(int *)(param_1 + 0x9c) = *(int *)(param_1 + 0x9c) + (iVar6 - iVar3);
        }
      }
    }
  }
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(iVar2 + -4);
  *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(iVar2 + -8);
  FUN_004fd5b0(*(undefined4 *)(iVar2 + -0x24));
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(iVar2 + -0x30);
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(iVar2 + -0x2c);
  *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(iVar2 + -0x28);
  *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + -0x30;
  FUN_004c82d0();
  return;
}

