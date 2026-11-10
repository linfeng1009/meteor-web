/* Original Meteor.exe read-only export. Sample not executed. */

undefined4 * __fastcall FUN_00500840(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a3f37;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  FUN_004ecb80();
  local_4 = 0;
  param_1[0x106] = 0;
  param_1[0x107] = 0;
  param_1[0x108] = 0;
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
  param_1[0x106] = puVar1;
  param_1[0x107] = puVar1;
  param_1[0x108] = puVar1 + 2;
  local_4._0_1_ = 4;
  FUN_00402a70();
  local_4._0_1_ = 5;
  param_1[0x109] = 0;
  param_1[0x10a] = 0;
  param_1[0x10b] = 0;
  FUN_00402330();
  local_4._0_1_ = 6;
  if (DAT_005d59a8 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_00403290(8);
  }
  else {
    puVar1 = DAT_005d59a8;
    DAT_005d59a8 = (undefined4 *)*DAT_005d59a8;
  }
  DAT_005d59e8 = 0;
  param_1[0x109] = puVar1;
  param_1[0x10a] = puVar1;
  param_1[0x10b] = puVar1 + 2;
  local_4._0_1_ = 9;
  FUN_00402a70();
  local_4 = CONCAT31(local_4._1_3_,10);
  FUN_004fe1a0();
  FUN_004f88e0();
  *param_1 = &PTR_FUN_005ab8a8;
  param_1[4] = &PTR_LAB_005ab878;
  param_1[0x127] = 0;
  param_1[0x128] = 0;
  param_1[0x129] = 0;
  param_1[0x12a] = 0;
  param_1[0xda] = 1;
  param_1[0xdb] = 0;
  param_1[0xdc] = 1;
  *(undefined1 *)(param_1 + 0x126) = 1;
  param_1[0x102] = 0xffffffff;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

