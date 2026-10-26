/* Original Meteor.exe static export @ 005607f0; original sample not executed. */
/* XREF 005637b1 UNCONDITIONAL_CALL */

undefined4 __fastcall FUN_005607f0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined1 local_38 [20];
  undefined **local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a5548;
  local_c = ExceptionList;
  if (*(int *)(param_1 + 0x44) != 0) {
    ExceptionList = &local_c;
    FUN_005783a0();
    local_4 = 0;
    local_18 = (undefined4 *)0x0;
    local_14 = (undefined4 *)0x0;
    local_10 = (undefined4 *)0x0;
    local_18 = (undefined4 *)FUN_00402bf0(8);
    local_10 = local_18 + 2;
    local_4._0_1_ = 3;
    local_14 = local_18;
    FUN_00402a70();
    local_20 = 0;
    local_24 = &PTR_LAB_005ab82c;
    local_1c = *(undefined4 *)(param_1 + 0x20);
    local_4._0_1_ = 4;
    FUN_005785c0(&local_24);
    FUN_00570fc0(local_38);
    (**(code **)(**(int **)(param_1 + 0x44) + 4))();
    puVar2 = local_18;
    local_4 = (uint)local_4._1_3_ << 8;
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x44) + 8);
    uVar3 = (int)local_10 - (int)local_18;
    local_24 = &PTR_LAB_005ab82c;
    if ((local_18 != (undefined4 *)0x0) && (uVar3 != 0)) {
      if (uVar3 < 0x81) {
        FUN_00402330();
        *puVar2 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puVar2;
        FUN_00443330();
      }
      else {
        FUN_005089fd(local_18);
      }
    }
    local_4 = 0xffffffff;
    FUN_005783c0();
    ExceptionList = local_c;
    return uVar1;
  }
  return 0;
}

