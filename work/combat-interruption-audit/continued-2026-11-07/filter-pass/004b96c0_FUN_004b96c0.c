/* Original Meteor.exe static export @ 004b96c0; original sample not executed. */
/* XREF 00486a32 UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004b96c0(undefined4 *param_1)

{
  int iVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a0cba;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004ed1e0();
  local_4 = 0;
  FUN_005498c0();
  FUN_005498c0();
  param_1[0x127] = 0;
  param_1[0x128] = 0;
  param_1[0x129] = 0;
  iVar1 = FUN_00402bf0(8);
  param_1[0x127] = iVar1;
  param_1[0x128] = iVar1;
  param_1[0x129] = iVar1 + 8;
  local_4._0_1_ = 3;
  FUN_00402a70();
  local_4._0_1_ = 4;
  param_1[0x12f] = 0;
  param_1[0x130] = 0;
  param_1[0x131] = 0;
  iVar1 = FUN_00402bf0(8);
  param_1[0x12f] = iVar1;
  param_1[0x130] = iVar1;
  param_1[0x131] = iVar1 + 8;
  local_4._0_1_ = 6;
  FUN_00402a70();
  local_4._0_1_ = 7;
  param_1[0x132] = 0;
  param_1[0x133] = 0;
  param_1[0x134] = 0;
  iVar1 = FUN_00402bf0(8);
  param_1[0x132] = iVar1;
  param_1[0x133] = iVar1;
  param_1[0x134] = iVar1 + 8;
  local_4._0_1_ = 9;
  FUN_00402a70();
  local_4 = CONCAT31(local_4._1_3_,10);
  *param_1 = &PTR_FUN_005a9fe0;
  param_1[4] = &PTR_LAB_005a9fac;
  FUN_004b9800();
  ExceptionList = local_c;
  return param_1;
}

