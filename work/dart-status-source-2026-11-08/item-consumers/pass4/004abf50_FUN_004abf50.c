/* Original Meteor.exe static read-only export; sample not executed. */

void __fastcall FUN_004abf50(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0059ffd0;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005a9bf8;
  param_1[4] = &PTR_LAB_005a9bd8;
  local_4 = 5;
  if (param_1[0x41] != 0) {
    FUN_00507850(param_1[0x41]);
  }
  param_1[0x41] = 0;
  if (param_1[0xdf] != 0) {
    FUN_00509e57(param_1[0xdf]);
  }
  FUN_004b3420();
  FUN_0054da60();
  param_1[0xe9] = &PTR_FUN_005a9444;
  local_4._0_1_ = 7;
  FUN_004b48d0();
  local_4._0_1_ = 6;
  FUN_00402e90(param_1[0xed],0x78);
  piVar2 = param_1 + 0xea;
  local_4._0_1_ = 8;
  if (param_1[0xeb] != 0) {
    FUN_0049d200(*(undefined4 *)(*piVar2 + 4));
    *(int *)(*piVar2 + 8) = *piVar2;
    *(undefined4 *)(*piVar2 + 4) = 0;
    *(int *)(*piVar2 + 0xc) = *piVar2;
    param_1[0xeb] = 0;
  }
  local_4._0_1_ = 4;
  FUN_00402e90(*piVar2,0x2b8);
  piVar2 = param_1 + 0xe5;
  local_4._0_1_ = 9;
  if (param_1[0xe6] != 0) {
    FUN_0049d4a0(*(undefined4 *)(*piVar2 + 4));
    *(int *)(*piVar2 + 8) = *piVar2;
    *(undefined4 *)(*piVar2 + 4) = 0;
    *(int *)(*piVar2 + 0xc) = *piVar2;
    param_1[0xe6] = 0;
  }
  puVar1 = (undefined4 *)*piVar2;
  FUN_00402330();
  *puVar1 = DAT_005d59b0;
  piVar2 = param_1 + 0xe2;
  DAT_005d59e8 = 0;
  local_4._0_1_ = 10;
  DAT_005d59b0 = puVar1;
  if (param_1[0xe3] != 0) {
    FUN_004b4c80(*(undefined4 *)(*piVar2 + 4));
    *(int *)(*piVar2 + 8) = *piVar2;
    *(undefined4 *)(*piVar2 + 4) = 0;
    *(int *)(*piVar2 + 0xc) = *piVar2;
    param_1[0xe3] = 0;
  }
  puVar1 = (undefined4 *)*piVar2;
  FUN_00402330();
  *puVar1 = DAT_005d59b4;
  DAT_005d59e8 = 0;
  local_4._0_1_ = 0xd;
  DAT_005d59b4 = puVar1;
  FUN_004998a0();
  local_4._0_1_ = 0xc;
  FUN_00402bd0();
  local_4._0_1_ = 0xb;
  FUN_00402bd0();
  local_4._0_1_ = 1;
  FUN_00402bd0();
  local_4 = (uint)local_4._1_3_ << 8;
  FUN_0054e3d0();
  local_4 = 0xffffffff;
  FUN_004a9190();
  ExceptionList = local_c;
  return;
}

