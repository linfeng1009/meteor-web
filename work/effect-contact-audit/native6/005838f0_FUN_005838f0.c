/* Original Meteor.exe static export @ 005838f0; original sample not executed. */
/* XREF 0056dbde UNCONDITIONAL_CALL */

undefined4 * __thiscall FUN_005838f0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a688e;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  FUN_005811c0(param_2,param_3);
  local_4 = 0;
  param_1[0x9a] = 0;
  param_1[0x9b] = 0;
  param_1[0x9c] = 0;
  FUN_00402330();
  local_4._0_1_ = 1;
  if (DAT_005d59a8 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_00403290(8);
  }
  else {
    puVar1 = DAT_005d59a8;
    DAT_005d59a8 = (undefined4 *)*DAT_005d59a8;
  }
  DAT_005d59e8 = 0;
  param_1[0x9a] = puVar1;
  param_1[0x9b] = puVar1;
  param_1[0x9c] = puVar1 + 2;
  local_4._0_1_ = 4;
  FUN_00402a70();
  local_4._0_1_ = 5;
  FUN_0050ac61(param_1 + 0x238,0xc,5,&LAB_00583a20,FUN_004026e0);
  local_4 = CONCAT31(local_4._1_3_,6);
  *param_1 = &PTR_FUN_005b0ea0;
  FUN_00581a70(s_Character_005d1884);
  param_1[0x9d] = 0;
  param_1[0x9e] = 0;
  param_1[0x9f] = 0;
  param_1[0xa0] = 0;
  param_1[0xa1] = 0;
  param_1[0xa2] = 0;
  param_1[0x247] = 0;
  param_1[0x249] = 0;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

