/* Original Meteor.exe static export @ 004cabd0; original sample not executed. */
/* XREF 004f1dd2 UNCONDITIONAL_CALL */
/* XREF 0048a379 UNCONDITIONAL_CALL */
/* XREF 004f1b51 UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004cabd0(undefined4 *param_1)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined1 local_19;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a195b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_00502d80();
  local_4 = 0;
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  param_1[0xba] = 0;
  param_1[0xbb] = 0;
  param_1[0xbc] = 0;
  FUN_004608a0(8);
  local_4._0_1_ = 1;
  FUN_00402a70();
  local_4._0_1_ = 2;
  param_1[0xbd] = 0;
  param_1[0xbe] = 0;
  param_1[0xbf] = 0;
  FUN_004608a0(8);
  local_4._0_1_ = 3;
  FUN_00402a70();
  local_4._0_1_ = 4;
  FUN_005498c0();
  param_1[0xf6] = 0;
  puVar1 = (undefined1 *)FUN_00402bf0(0x18);
  param_1[0xf6] = puVar1;
  param_1[0xf7] = 0;
  *(undefined1 *)(param_1 + 0xf8) = local_19;
  *puVar1 = 0;
  *(undefined4 *)(param_1[0xf6] + 4) = 0;
  *(undefined4 *)(param_1[0xf6] + 8) = param_1[0xf6];
  *(undefined4 *)(param_1[0xf6] + 0xc) = param_1[0xf6];
  local_4._0_1_ = 5;
  param_1[0xf9] = 0;
  uVar2 = FUN_00402bf0(0x18);
  param_1[0xf9] = uVar2;
  local_4._0_1_ = 6;
  param_1[0xfa] = 0;
  *(undefined1 *)(param_1 + 0xfb) = local_19;
  FUN_004b4a30();
  local_4._0_1_ = 7;
  param_1[0xfc] = 0;
  param_1[0xfd] = 0;
  FUN_00502330();
  FUN_00502330();
  FUN_004d21e0(0);
  local_4._0_1_ = 8;
  param_1[0xf5] = &PTR_LAB_005aa88c;
  FUN_004d0e10();
  local_4 = CONCAT31(local_4._1_3_,9);
  *param_1 = &PTR_FUN_005aa6a8;
  FUN_004cafb0();
  ExceptionList = local_c;
  return param_1;
}

