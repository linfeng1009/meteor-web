/* Original Meteor.exe static export @ 00492690; original sample not executed. */
/* XREF 00494cc6 UNCONDITIONAL_CALL */
/* XREF 004ac1af UNCONDITIONAL_CALL */
/* XREF 004bd4d8 UNCONDITIONAL_CALL */
/* XREF 0048ba60 UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_00492690(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined4 *local_14;
  undefined4 *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059e88a;
  local_c = ExceptionList;
  local_10 = param_1 + 1;
  ExceptionList = &local_c;
  local_14 = param_1;
  FUN_00402b70(&local_18,8);
  local_4 = 0;
  FUN_00402a70();
  local_10 = param_1 + 4;
  local_4 = 1;
  FUN_00402b70(&local_17,8);
  local_4._0_1_ = 2;
  FUN_00402a70();
  local_10 = param_1 + 7;
  local_4._0_1_ = 3;
  FUN_00402b70(&local_16,8);
  local_4._0_1_ = 4;
  FUN_00402a70();
  local_4 = CONCAT31(local_4._1_3_,5);
  FUN_005005b0(&local_15);
  *param_1 = &PTR_FUN_005a94e4;
  param_1[0xb] = 0;
  param_1[10] = 0;
  local_4 = 6;
  uVar1 = FUN_00402bf0(0x50);
  param_1[0x10] = uVar1;
  *(undefined4 *)uVar1 = uVar1;
  *(undefined4 *)(param_1[0x10] + 4) = param_1[0x10];
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  FUN_00402330();
  local_4._0_1_ = 9;
  if (DAT_005d59cc == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_00403290(0x50);
  }
  else {
    puVar2 = DAT_005d59cc;
    DAT_005d59cc = (undefined4 *)*DAT_005d59cc;
  }
  DAT_005d59e8 = 0;
  param_1[0x14] = puVar2;
  *puVar2 = puVar2;
  *(undefined4 *)(param_1[0x14] + 4) = param_1[0x14];
  local_4 = CONCAT31(local_4._1_3_,10);
  *param_1 = &PTR_FUN_005a9490;
  FUN_004d4a50();
  ExceptionList = local_c;
  return param_1;
}

