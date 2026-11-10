/* Original Meteor.exe static export @ 005012f0; original sample not executed. */
/* XREF 004bfec8 UNCONDITIONAL_CALL */
/* XREF 004f9ed0 UNCONDITIONAL_CALL */

void __fastcall FUN_005012f0(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  iVar2 = FUN_00571660(&DAT_005c9b48);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(&DAT_005c9b48);
    piVar1 = (int *)(param_1 + 0x418);
    if ((int *)(iVar2 + 0xc) != piVar1) {
      iVar6 = *(int *)(iVar2 + 0x10);
      puVar5 = *(undefined4 **)(iVar2 + 0xc);
      puVar8 = (undefined4 *)*piVar1;
      uVar3 = iVar6 - (int)puVar5;
      uVar4 = *(int *)(param_1 + 0x41c) - (int)puVar8;
      if (uVar4 < uVar3) {
        puVar7 = puVar5;
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
        FUN_00403490((undefined1 *)((*(int *)(param_1 + 0x41c) - *piVar1) + (int)puVar5),iVar6);
      }
      else {
        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar8 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar8 = puVar8 + 1;
        }
        for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar8 = *(undefined1 *)puVar5;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
          puVar8 = (undefined4 *)((int)puVar8 + 1);
        }
        iVar2 = *(int *)(param_1 + 0x41c);
        iVar6 = *piVar1 + uVar3;
        if (iVar6 != iVar2) {
          FUN_005092c0(iVar6,iVar2,1);
          *(int *)(param_1 + 0x41c) = *(int *)(param_1 + 0x41c) + (iVar6 - iVar2);
        }
      }
    }
  }
  iVar2 = FUN_00571660(&DAT_005ca2c4);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(&DAT_005ca2c4);
    *(undefined2 *)(param_1 + 0x430) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_Think_005ca2bc);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_Think_005ca2bc);
    *(undefined2 *)(param_1 + 0x432) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_Attack1_005ca2b4);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_Attack1_005ca2b4);
    *(undefined2 *)(param_1 + 0x442) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_Attack2_005ca2ac);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_Attack2_005ca2ac);
    *(undefined2 *)(param_1 + 0x444) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_Attack3_005ca2a4);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_Attack3_005ca2a4);
    *(undefined2 *)(param_1 + 0x446) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_Guard_005c9cdc);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_Guard_005c9cdc);
    *(undefined2 *)(param_1 + 0x434) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_Dodge_005ca1ac);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_Dodge_005ca1ac);
    *(undefined2 *)(param_1 + 0x436) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(&DAT_005c9cd4);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(&DAT_005c9cd4);
    *(undefined2 *)(param_1 + 0x438) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(&DAT_005ca29c);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(&DAT_005ca29c);
    *(undefined2 *)(param_1 + 0x43a) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_Burst_005ca294);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_Burst_005ca294);
    *(undefined2 *)(param_1 + 0x43c) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(&PTR_DAT_005ca290);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(&PTR_DAT_005ca290);
    *(undefined2 *)(param_1 + 0x43e) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_GetItem_005ca194);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_GetItem_005ca194);
    *(undefined2 *)(param_1 + 0x440) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(s_Spawn_005ca288);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(s_Spawn_005ca288);
    *(undefined2 *)(param_1 + 0x448) = *(undefined2 *)(iVar2 + 8);
  }
  iVar2 = FUN_00571660(&DAT_005ca284);
  if (iVar2 != 0) {
    iVar2 = FUN_00571660(&DAT_005ca284);
    *(undefined2 *)(param_1 + 0x44a) = *(undefined2 *)(iVar2 + 8);
  }
  return;
}

