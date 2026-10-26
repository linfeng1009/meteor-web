/* Original Meteor.exe static export @ 00565ee0; original sample not executed. */
/* XREF 00566ae4 UNCONDITIONAL_CALL */
/* XREF 005669d4 UNCONDITIONAL_CALL */

undefined4 * __thiscall FUN_00565ee0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a5788;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_14 = param_1;
  FUN_0047b350();
  puVar1 = param_1 + 0x48;
  local_4 = 0;
  *puVar1 = 0;
  param_1[0x49] = 0;
  param_1[0x4a] = 0;
  local_10 = puVar1;
  FUN_00402330();
  local_4._0_1_ = 1;
  if (DAT_005d59a8 == (undefined4 *)0x0) {
    local_18 = 0x14;
    puVar3 = (undefined4 *)FUN_004036c0(8,&local_18);
    iVar5 = 1;
    if (local_18 != 1) {
      puVar4 = puVar3 + 2;
      puVar2 = puVar4;
      DAT_005d59a8 = puVar4;
      if (local_18 != 2) {
        do {
          puVar4 = puVar2 + 2;
          *puVar2 = puVar4;
          iVar5 = iVar5 + 1;
          puVar2 = puVar4;
        } while (local_18 + -1 != iVar5);
      }
      *puVar4 = 0;
    }
  }
  else {
    puVar3 = DAT_005d59a8;
    DAT_005d59a8 = (undefined4 *)*DAT_005d59a8;
  }
  DAT_005d59e8 = 0;
  *puVar1 = puVar3;
  param_1[0x49] = puVar3;
  param_1[0x4a] = puVar3 + 2;
  local_4 = CONCAT31(local_4._1_3_,4);
  FUN_00402a70();
  *param_1 = &PTR_LAB_005ae1f4;
  param_1[0x4c] = param_2;
  param_1[0x4b] = 0;
  param_1[0x50] = 0;
  param_1[0x4d] = 0;
  *(undefined1 *)(param_1 + 0x4e) = 0;
  *(undefined1 *)((int)param_1 + 0x139) = 1;
  ExceptionList = local_c;
  return param_1;
}

