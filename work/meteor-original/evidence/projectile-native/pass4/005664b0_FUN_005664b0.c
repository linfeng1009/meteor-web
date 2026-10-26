/* Original Meteor.exe static export @ 005664b0; original sample not executed. */
/* XREF 004db496 UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_005664b0(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int local_18;
  undefined4 *local_14;
  int *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005a5806;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  local_4 = 0;
  local_14 = param_1;
  FUN_00402330();
  local_4._0_1_ = 1;
  if (DAT_005d59ac == (undefined4 *)0x0) {
    local_18 = 0x14;
    puVar3 = (undefined4 *)FUN_004036c0(0x10,&local_18);
    if (local_18 != 1) {
      puVar4 = puVar3 + 4;
      iVar5 = 1;
      puVar2 = puVar4;
      DAT_005d59ac = puVar4;
      if (local_18 != 2) {
        do {
          puVar4 = puVar2 + 4;
          *puVar2 = puVar4;
          iVar5 = iVar5 + 1;
          puVar2 = puVar4;
        } while (local_18 + -1 != iVar5);
      }
      *puVar4 = 0;
    }
  }
  else {
    puVar3 = DAT_005d59ac;
    DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
  }
  DAT_005d59e8 = 0;
  param_1[4] = puVar3;
  *puVar3 = puVar3;
  *(undefined4 *)(param_1[4] + 4) = param_1[4];
  piVar1 = param_1 + 5;
  local_4._0_1_ = 2;
  *piVar1 = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  local_10 = piVar1;
  iVar5 = FUN_00402bf0(8);
  *piVar1 = iVar5;
  param_1[6] = iVar5;
  param_1[7] = iVar5 + 8;
  local_4 = CONCAT31(local_4._1_3_,5);
  FUN_00402a70();
  param_1[8] = 0;
  *param_1 = 0;
  ExceptionList = local_c;
  return param_1;
}

