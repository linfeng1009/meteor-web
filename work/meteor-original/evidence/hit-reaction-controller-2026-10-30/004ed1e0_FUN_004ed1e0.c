/* Original Meteor.exe static export @ 004ed1e0; original sample not executed. */
/* XREF 004b96e1 UNCONDITIONAL_CALL */
/* XREF 004ecb9d UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004ed1e0(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a322b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004a9010();
  local_4 = 0;
  FUN_004b2900();
  local_4._0_1_ = 1;
  FUN_005498c0();
  FUN_005498c0();
  uVar1 = FUN_00402bf0(0xc);
  param_1[0x8f] = uVar1;
  *(undefined4 *)uVar1 = uVar1;
  *(undefined4 *)(param_1[0x8f] + 4) = param_1[0x8f];
  local_4._0_1_ = 2;
  uVar1 = FUN_00402bf0(0xc);
  param_1[0x90] = uVar1;
  *(undefined4 *)uVar1 = uVar1;
  *(undefined4 *)(param_1[0x90] + 4) = param_1[0x90];
  param_1[0x91] = 0;
  param_1[0x92] = 0;
  param_1[0x93] = 0;
  local_4._0_1_ = 4;
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  param_1[0xde] = 0;
  param_1[0xdf] = 0;
  param_1[0xe0] = 0;
  FUN_00402330();
  local_4._0_1_ = 5;
  if (DAT_005d59a8 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_00403290(8);
  }
  else {
    puVar2 = DAT_005d59a8;
    DAT_005d59a8 = (undefined4 *)*DAT_005d59a8;
  }
  DAT_005d59e8 = 0;
  param_1[0xde] = puVar2;
  param_1[0xdf] = puVar2;
  param_1[0xe0] = puVar2 + 2;
  local_4._0_1_ = 8;
  FUN_00402a70();
  local_4 = CONCAT31(local_4._1_3_,9);
  FUN_005519d0();
  *param_1 = &PTR_FUN_005ab468;
  param_1[4] = &PTR_LAB_005ab434;
  FUN_004ed360();
  ExceptionList = local_c;
  return param_1;
}

