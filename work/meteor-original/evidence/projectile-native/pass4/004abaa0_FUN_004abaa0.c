/* Original Meteor.exe static export @ 004abaa0; original sample not executed. */
/* XREF 004bd333 UNCONDITIONAL_CALL */
/* XREF 004bea33 UNCONDITIONAL_CALL */
/* XREF 00488be0 UNCONDITIONAL_CALL */
/* XREF 00489e1d UNCONDITIONAL_CALL */
/* XREF 004b6bae UNCONDITIONAL_CALL */
/* XREF 004b702c UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004abaa0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined4 *local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059feec;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_14 = param_1;
  FUN_004a9010();
  local_4 = 0;
  FUN_0054e150();
  local_4._0_1_ = 1;
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  local_10 = param_1 + 0x7b;
  FUN_00402b70(&local_1c,8);
  local_4._0_1_ = 2;
  FUN_00402a70();
  local_18 = param_1 + 0x7e;
  local_4._0_1_ = 3;
  FUN_00402b70(&local_1b,8);
  local_4._0_1_ = 4;
  FUN_00402a70();
  local_18 = param_1 + 0x81;
  local_4._0_1_ = 5;
  FUN_00402b70(&local_1a,8);
  local_4._0_1_ = 6;
  FUN_00402a70();
  local_4._0_1_ = 7;
  FUN_00499700();
  param_1[0x89] = 0;
  param_1[0x90] = 0;
  param_1[0x8e] = 0;
  param_1[0x8d] = 0;
  param_1[0x8c] = 0;
  param_1[0x8b] = 0;
  param_1[0x8a] = 0;
  param_1[0x8f] = 100;
  param_1[0x86] = 2;
  param_1[0x87] = 300;
  param_1[0x88] = 3;
  local_4._0_1_ = 8;
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  puVar1 = param_1 + 0xe2;
  *puVar1 = 0;
  local_10 = puVar1;
  uVar2 = FUN_00402bf0(0x1c);
  *puVar1 = uVar2;
  local_4._0_1_ = 9;
  *(undefined1 *)(param_1 + 0xe4) = local_1a;
  param_1[0xe3] = 0;
  FUN_004b4a30();
  puVar1 = param_1 + 0xe5;
  local_4._0_1_ = 10;
  *puVar1 = 0;
  local_10 = puVar1;
  uVar2 = FUN_00402bf0(0x14);
  *puVar1 = uVar2;
  local_4._0_1_ = 0xb;
  param_1[0xe6] = 0;
  *(undefined1 *)(param_1 + 0xe7) = local_1a;
  FUN_004b4a30();
  local_4._0_1_ = 0xc;
  local_10 = param_1 + 0xe9;
  FUN_004b4790(&local_1b,&local_1a);
  local_4._0_1_ = 0xd;
  FUN_004b47f0(&local_19,&local_1c);
  param_1[0xe9] = &PTR_FUN_005a9444;
  param_1[0xf2] = 0;
  param_1[0xf1] = 0;
  param_1[0xf0] = 0;
  local_4 = CONCAT31(local_4._1_3_,0xe);
  *param_1 = &PTR_FUN_005a9bf8;
  param_1[4] = &PTR_LAB_005a9bd8;
  FUN_004abe80();
  ExceptionList = local_c;
  return param_1;
}

