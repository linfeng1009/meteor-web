/* Original Meteor.exe static export @ 004e1420; original sample not executed. */
/* XREF 004e18db UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004e1420(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 local_15;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a2bcf;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004dc9a0();
  local_4 = 0;
  uVar1 = FUN_00402bf0(0xc);
  param_1[0x13] = uVar1;
  *(undefined4 *)uVar1 = uVar1;
  *(undefined4 *)(param_1[0x13] + 4) = param_1[0x13];
  param_1[0x10] = &PTR_FUN_005aaae8;
  param_1[0x12] = 99999;
  local_4._0_1_ = 1;
  uVar1 = FUN_00402bf0(0xc);
  param_1[0x17] = uVar1;
  *(undefined4 *)uVar1 = uVar1;
  *(undefined4 *)(param_1[0x17] + 4) = param_1[0x17];
  param_1[0x14] = &PTR_FUN_005aaae8;
  param_1[0x16] = 99999;
  local_4._0_1_ = 2;
  param_1[0x18] = 0;
  uVar1 = FUN_00402bf0(0x18);
  param_1[0x18] = uVar1;
  local_4._0_1_ = 3;
  param_1[0x19] = 0;
  *(undefined1 *)(param_1 + 0x1a) = local_15;
  FUN_004b4a30();
  local_4._0_1_ = 4;
  param_1[0x1b] = 0;
  puVar2 = (undefined1 *)FUN_00402bf0(0x14);
  param_1[0x1b] = puVar2;
  param_1[0x1c] = 0;
  *(undefined1 *)(param_1 + 0x1d) = local_15;
  *puVar2 = 0;
  *(undefined4 *)(param_1[0x1b] + 4) = 0;
  *(undefined4 *)(param_1[0x1b] + 8) = param_1[0x1b];
  *(undefined4 *)(param_1[0x1b] + 0xc) = param_1[0x1b];
  local_4._0_1_ = 5;
  param_1[0x1e] = 0;
  uVar1 = FUN_00402bf0(0x14);
  param_1[0x1e] = uVar1;
  local_4._0_1_ = 6;
  param_1[0x1f] = 0;
  *(undefined1 *)(param_1 + 0x20) = local_15;
  FUN_004b4a30();
  local_4 = CONCAT31(local_4._1_3_,7);
  *param_1 = &PTR_FUN_005aaef0;
  FUN_004e1910();
  ExceptionList = local_c;
  return param_1;
}

