/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall FUN_004fa240(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 local_3c [12];
  undefined1 local_30 [12];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a3aca;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffb8;
  local_20 = param_1[1];
  if (local_20 != param_1[2]) {
    local_8 = 0;
    ExceptionList = &local_10;
    local_1c = local_20;
    local_14 = &stack0xffffffb8;
    if (local_20 != 0) {
      ExceptionList = &local_10;
      local_14 = &stack0xffffffb8;
      FUN_004fa650(local_20 + -0x1c);
    }
    param_1[1] = param_1[1] + 0x1c;
    local_8 = 0xffffffff;
    FUN_0047a270(param_3);
    local_8 = 1;
    FUN_0047a270(param_3 + 0xc);
    local_24 = *(undefined4 *)(param_3 + 0x18);
    local_8 = 2;
    FUN_004fa810(param_2,param_1[1] + -0x38,param_1[1] + -0x1c,param_2,0);
    FUN_00473340(local_3c);
    FUN_00473340(local_30);
    *(undefined4 *)(param_2 + 0x18) = local_24;
    local_8 = 3;
    FUN_00402bd0();
    FUN_004026e0();
    ExceptionList = local_10;
    return;
  }
  local_1c = (local_20 - *param_1) / 0x1c;
  if (local_1c == 0) {
    local_1c = 1;
  }
  else {
    local_1c = local_1c * 2;
    if (local_1c == 0) {
      local_20 = 0;
      ExceptionList = &local_10;
      local_14 = &stack0xffffffb8;
      goto LAB_004fa377;
    }
  }
  ExceptionList = &local_10;
  local_20 = FUN_00402bf0(local_1c * 0x1c);
LAB_004fa377:
  local_8 = 4;
  local_18 = local_20;
  iVar2 = FUN_004fa980(*param_1,param_2,local_20,param_2);
  local_8._0_1_ = 5;
  if (iVar2 != 0) {
    local_20 = iVar2;
    FUN_004fa650(param_3);
  }
  local_20 = iVar2 + 0x1c;
  local_8 = CONCAT31(local_8._1_3_,4);
  iVar3 = FUN_004fa980(param_2,param_1[1],local_20,iVar2);
  iVar2 = param_1[1];
  for (iVar5 = *param_1; iVar5 != iVar2; iVar5 = iVar5 + 0x1c) {
    FUN_004026e0();
    FUN_004026e0();
  }
  piVar1 = (int *)*param_1;
  iVar2 = (param_1[2] - (int)piVar1) / 0x1c;
  if (iVar2 != 0) {
    uVar4 = iVar2 * 0x1c;
    if (uVar4 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  param_1[1] = iVar3;
  *param_1 = local_18;
  param_1[2] = local_18 + local_1c * 0x1c;
  ExceptionList = local_10;
  return;
}

