/* Original Meteor.exe static export @ 004dc9a0; original sample not executed. */
/* XREF 004dd18d UNCONDITIONAL_CALL */
/* XREF 004dd8dd UNCONDITIONAL_CALL */
/* XREF 004de03d UNCONDITIONAL_CALL */
/* XREF 004de78d UNCONDITIONAL_CALL */
/* XREF 004defad UNCONDITIONAL_CALL */
/* XREF 004df74d UNCONDITIONAL_CALL */
/* XREF 004dfe9d UNCONDITIONAL_CALL */
/* XREF 004e05dd UNCONDITIONAL_CALL */
/* XREF 004e0ced UNCONDITIONAL_CALL */
/* XREF 004e1441 UNCONDITIONAL_CALL */
/* XREF 004e2ccd UNCONDITIONAL_CALL */
/* XREF 004e354d UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004dc9a0(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_11;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a27d9;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  uVar1 = FUN_00402bf0(0xc);
  param_1[4] = uVar1;
  *(undefined4 *)uVar1 = uVar1;
  *(undefined4 *)(param_1[4] + 4) = param_1[4];
  param_1[1] = &PTR_FUN_005aaae8;
  param_1[3] = 99999;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  local_4._0_1_ = 2;
  local_4._1_3_ = 0;
  param_1[0xd] = 0;
  FUN_00402330();
  local_4 = CONCAT31(local_4._1_3_,3);
  if (DAT_005d59b0 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_00403290(0x18);
  }
  else {
    puVar2 = DAT_005d59b0;
    DAT_005d59b0 = (undefined4 *)*DAT_005d59b0;
  }
  DAT_005d59e8 = 0;
  param_1[0xd] = puVar2;
  param_1[0xe] = 0;
  *(undefined1 *)(param_1 + 0xf) = local_11;
  *(undefined1 *)puVar2 = 0;
  *(undefined4 *)(param_1[0xd] + 4) = 0;
  *(undefined4 *)(param_1[0xd] + 8) = param_1[0xd];
  *(undefined4 *)(param_1[0xd] + 0xc) = param_1[0xd];
  *param_1 = &PTR_FUN_005aaa78;
  param_1[6] = 0;
  ExceptionList = local_c;
  return param_1;
}

