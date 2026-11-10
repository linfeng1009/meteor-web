/* Original Meteor.exe static export @ 004e1710; original sample not executed. */
/* XREF 004e1553 UNCONDITIONAL_CALL */
/* XREF 004e1905 UNCONDITIONAL_CALL */

void __fastcall FUN_004e1710(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int *piVar3;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a2c75;
  local_c = ExceptionList;
  piVar3 = param_1 + 0x1e;
  local_4._0_1_ = 5;
  local_4._1_3_ = 0;
  ExceptionList = &local_c;
  if (param_1[0x1f] != 0) {
    ExceptionList = &local_c;
    FUN_004e42b0(*(undefined4 *)(*piVar3 + 4));
    *(int *)(*piVar3 + 8) = *piVar3;
    *(undefined4 *)(*piVar3 + 4) = 0;
    *(int *)(*piVar3 + 0xc) = *piVar3;
    param_1[0x1f] = 0;
  }
  puVar2 = (undefined4 *)*piVar3;
  FUN_00402330();
  *puVar2 = DAT_005d59b0;
  piVar3 = param_1 + 0x1b;
  DAT_005d59e8 = 0;
  local_4._0_1_ = 6;
  DAT_005d59b0 = puVar2;
  if (param_1[0x1c] != 0) {
    FUN_004e42b0(*(undefined4 *)(*piVar3 + 4));
    *(int *)(*piVar3 + 8) = *piVar3;
    *(undefined4 *)(*piVar3 + 4) = 0;
    *(int *)(*piVar3 + 0xc) = *piVar3;
    param_1[0x1c] = 0;
  }
  piVar3 = (int *)*piVar3;
  FUN_00402330();
  *piVar3 = (int)DAT_005d59b0;
  piVar1 = param_1 + 0x18;
  DAT_005d59e8 = 0;
  local_4._0_1_ = 7;
  DAT_005d59b0 = piVar3;
  if (param_1[0x19] != 0) {
    FUN_0049c2f0(*(undefined4 *)(*piVar1 + 4));
    *(int *)(*piVar1 + 8) = *piVar1;
    *(undefined4 *)(*piVar1 + 4) = 0;
    *(int *)(*piVar1 + 0xc) = *piVar1;
    param_1[0x19] = 0;
  }
  puVar2 = (undefined4 *)*piVar1;
  FUN_00402330();
  *puVar2 = DAT_005d59b0;
  DAT_005d59e8 = 0;
  local_4._0_1_ = 1;
  DAT_005d59b0 = puVar2;
  FUN_00503280();
  local_4 = (uint)local_4._1_3_ << 8;
  FUN_00503280();
  *param_1 = &PTR_FUN_005aaa78;
  local_4._0_1_ = 0xb;
  local_4._1_3_ = 0;
  FUN_004e3ea0();
  local_4._0_1_ = 10;
  FUN_00402e90(param_1[0xd],0x18);
  local_4._0_1_ = 9;
  FUN_004fe380();
  local_4 = CONCAT31(local_4._1_3_,8);
  FUN_004fe380();
  local_4 = 0xffffffff;
  FUN_00503280();
  ExceptionList = local_c;
  return;
}

