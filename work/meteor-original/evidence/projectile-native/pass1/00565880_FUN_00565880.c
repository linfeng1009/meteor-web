/* Original Meteor.exe static export @ 00565880; original sample not executed. */
/* XREF 0048c553 UNCONDITIONAL_CALL */
/* XREF 0048cc80 UNCONDITIONAL_CALL */
/* XREF 0048ce2a UNCONDITIONAL_CALL */
/* XREF 0048cfd1 UNCONDITIONAL_CALL */
/* XREF 0048d03c UNCONDITIONAL_CALL */

void __thiscall FUN_00565880(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined1 local_50 [20];
  undefined **local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 *local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  undefined **local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a5728;
  local_c = ExceptionList;
  if (*(int *)(param_1 + 0x6d4) != 0) {
    ExceptionList = &local_c;
    FUN_005783a0();
    local_4 = 0;
    local_30 = (undefined4 *)0x0;
    local_2c = (undefined4 *)0x0;
    local_28 = (undefined4 *)0x0;
    local_30 = (undefined4 *)FUN_00402bf0(8);
    local_28 = local_30 + 2;
    local_4._0_1_ = 1;
    local_2c = local_30;
    FUN_00402a70();
    local_38 = 0;
    local_3c = &PTR_LAB_005ab82c;
    local_34 = 0;
    local_4._0_1_ = 2;
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    local_18 = FUN_00402bf0(8);
    local_10 = local_18 + 8;
    local_4._0_1_ = 3;
    local_14 = local_18;
    FUN_00402a70();
    local_24 = &PTR_LAB_005ab82c;
    local_20 = 0;
    local_4._0_1_ = 4;
    local_34 = param_2;
    local_1c = param_3;
    FUN_005785c0(&local_3c);
    FUN_005785c0(&local_24);
    FUN_00570fc0(local_50);
    (**(code **)(**(int **)(param_1 + 0x6d4) + 4))();
    local_4 = CONCAT31(local_4._1_3_,2);
    local_24 = &PTR_LAB_005ab82c;
    if ((local_18 != 0) && (local_10 - local_18 != 0)) {
      FUN_00402e90(local_18,local_10 - local_18);
    }
    puVar1 = local_30;
    uVar2 = (int)local_28 - (int)local_30;
    local_3c = &PTR_LAB_005ab82c;
    if ((local_30 != (undefined4 *)0x0) && (uVar2 != 0)) {
      if (uVar2 < 0x81) {
        FUN_00402330();
        *puVar1 = *(undefined4 *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = puVar1;
        FUN_00443330();
      }
      else {
        FUN_005089fd(local_30);
      }
    }
    local_4 = 0xffffffff;
    FUN_005783c0();
  }
  ExceptionList = local_c;
  return;
}

