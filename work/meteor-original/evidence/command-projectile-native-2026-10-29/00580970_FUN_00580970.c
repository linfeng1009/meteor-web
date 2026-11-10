/* Original Meteor.exe static export @ 00580970; original sample not executed. */
/* XREF 005812e2 UNCONDITIONAL_CALL */

undefined4 * __thiscall FUN_00580970(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a669d;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  FUN_0058e430();
  param_1[0x3a] = 0;
  param_1[0x3b] = 0;
  param_1[0x3c] = 0;
  local_4._0_1_ = 1;
  local_4._1_3_ = 0;
  param_1[0x3d] = 0;
  param_1[0x3e] = 0;
  param_1[0x3f] = 0;
  FUN_00402330();
  local_4._0_1_ = 2;
  if (DAT_005d59a8 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_00403290(8);
  }
  else {
    puVar1 = DAT_005d59a8;
    DAT_005d59a8 = (undefined4 *)*DAT_005d59a8;
  }
  DAT_005d59e8 = 0;
  param_1[0x3d] = puVar1;
  param_1[0x3e] = puVar1;
  param_1[0x3f] = puVar1 + 2;
  local_4._0_1_ = 4;
  FUN_00402a70();
  local_4._0_1_ = 5;
  param_1[0x40] = 0;
  param_1[0x41] = 0;
  param_1[0x42] = 0;
  iVar2 = FUN_00402bf0(8);
  param_1[0x40] = iVar2;
  param_1[0x41] = iVar2;
  param_1[0x42] = iVar2 + 8;
  local_4._0_1_ = 8;
  FUN_00402a70();
  local_4 = CONCAT31(local_4._1_3_,9);
  FUN_0047bfd0();
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  param_1[9] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0x39] = 0;
  param_1[0x7f] = 0;
  param_1[0x80] = 0;
  param_1[0x81] = param_2;
  param_1[8] = 1;
  *(undefined1 *)(param_1 + 10) = 1;
  *(undefined1 *)((int)param_1 + 0x29) = 1;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

