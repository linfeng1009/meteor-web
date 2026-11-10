/* Original Meteor.exe static export @ 004fd630; original sample not executed. */
/* XREF 004f9251 UNCONDITIONAL_CALL */
/* XREF 004f93e9 UNCONDITIONAL_CALL */
/* XREF 004fd213 UNCONDITIONAL_CALL */
/* XREF 004f94cc UNCONDITIONAL_CALL */
/* XREF 004fdf1a UNCONDITIONAL_CALL */
/* XREF 004fddb4 UNCONDITIONAL_CALL */
/* XREF 004fdeed UNCONDITIONAL_CALL */
/* XREF 004fe0b0 UNCONDITIONAL_CALL */
/* XREF 00503bfa UNCONDITIONAL_CALL */
/* XREF 005046b9 UNCONDITIONAL_CALL */
/* XREF 00503eac UNCONDITIONAL_CALL */
/* XREF 005041fa UNCONDITIONAL_CALL */

void __thiscall FUN_004fd630(int param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 **ppuVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined1 local_41;
  undefined4 **local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined *local_30;
  undefined4 *local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 *local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a3d91;
  local_c = ExceptionList;
  local_40 = &local_2c;
  local_2c = (undefined4 *)0x0;
  local_28 = 0;
  local_24 = 0;
  ExceptionList = &local_c;
  FUN_004608a0(8);
  local_4 = 0;
  FUN_00402a70();
  local_4 = 1;
  FUN_004024a0(&local_41);
  local_4 = 2;
  local_3c = *(undefined4 *)(param_1 + 0xd4);
  local_30 = *(undefined **)(param_1 + 100);
  local_38 = *(undefined4 *)(param_1 + 0xd8);
  local_14 = *(undefined4 *)(param_1 + 0x88);
  local_34 = *(undefined4 *)(param_1 + 0xdc);
  local_10 = *(undefined4 *)(param_1 + 0x78);
  if (local_30 == &DAT_00504be0) {
    if ((undefined4 **)(param_1 + 0x8c) != &local_2c) {
      iVar1 = *(int *)(param_1 + 0x90);
      puVar5 = *(undefined4 **)(param_1 + 0x8c);
      uVar4 = local_28 - (int)local_2c;
      uVar3 = iVar1 - (int)puVar5;
      if (uVar4 < uVar3) {
        puVar6 = puVar5;
        puVar7 = local_2c;
        for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
          puVar7 = (undefined4 *)((int)puVar7 + 1);
        }
        FUN_00403490((undefined1 *)((local_28 - (int)local_2c) + (int)puVar5),iVar1);
      }
      else {
        puVar6 = local_2c;
        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
        FUN_00402b30((undefined1 *)(uVar3 + (int)local_2c),local_28);
      }
    }
    if ((undefined4 **)(param_1 + 0x98) != &local_20) {
      iVar1 = *(int *)(param_1 + 0x9c);
      puVar5 = *(undefined4 **)(param_1 + 0x98);
      uVar4 = local_1c - (int)local_20;
      uVar3 = iVar1 - (int)puVar5;
      if (uVar4 < uVar3) {
        puVar6 = puVar5;
        puVar7 = local_20;
        for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
          puVar7 = (undefined4 *)((int)puVar7 + 1);
        }
        FUN_00403490((undefined1 *)((local_1c - (int)local_20) + (int)puVar5),iVar1);
      }
      else {
        puVar6 = local_20;
        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
        FUN_00402b30((undefined1 *)(uVar3 + (int)local_20),local_1c);
      }
    }
  }
  if (param_2 != &LAB_00503e00) {
    *(undefined4 *)(param_1 + 0x78) = 0;
  }
  ppuVar2 = *(undefined4 ***)(param_1 + 0x6c);
  if (ppuVar2 == *(undefined4 ***)(param_1 + 0x70)) {
    FUN_004fe3e0(ppuVar2,&local_3c);
  }
  else {
    local_4._0_1_ = 3;
    local_40 = ppuVar2;
    if (ppuVar2 != (undefined4 **)0x0) {
      FUN_004fea50(&local_3c);
    }
    local_4 = CONCAT31(local_4._1_3_,2);
    *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 0x30;
  }
  FUN_004fd5b0(param_2);
  local_4 = 4;
  if ((local_20 != (undefined4 *)0x0) && (local_18 - (int)local_20 != 0)) {
    FUN_00402e90(local_20,local_18 - (int)local_20);
  }
  local_4 = 0xffffffff;
  FUN_00402bd0();
  ExceptionList = local_c;
  return;
}

