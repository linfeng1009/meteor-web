/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall FUN_004fe3e0(int *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined1 local_40 [12];
  undefined1 local_34 [12];
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a3df2;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffa4;
  local_20 = param_1[1];
  if (local_20 != param_1[2]) {
    local_8 = 0;
    ExceptionList = &local_10;
    local_1c = local_20;
    local_14 = &stack0xffffffa4;
    if (local_20 != 0) {
      ExceptionList = &local_10;
      local_14 = &stack0xffffffa4;
      FUN_004fea50(local_20 + -0x30);
    }
    local_8 = 0xffffffff;
    param_1[1] = param_1[1] + 0x30;
    uVar1 = *param_3;
    uVar2 = param_3[3];
    uVar3 = param_3[1];
    uVar4 = param_3[2];
    FUN_0047a270(param_3 + 4);
    local_8 = 1;
    FUN_0047a270(param_3 + 7);
    local_28 = param_3[10];
    local_24 = param_3[0xb];
    local_8 = 2;
    FUN_004fee70(param_2,param_1[1] + -0x60,param_1[1] + -0x30,param_2,0);
    *param_2 = uVar1;
    param_2[1] = uVar3;
    param_2[3] = uVar2;
    param_2[2] = uVar4;
    FUN_00473340(local_40);
    FUN_00473340(local_34);
    param_2[10] = local_28;
    param_2[0xb] = local_24;
    FUN_004026e0();
    FUN_004026e0();
    ExceptionList = local_10;
    return;
  }
  local_1c = (local_20 - *param_1) / 0x30;
  if (local_1c == 0) {
    local_1c = 1;
  }
  else {
    local_1c = local_1c * 2;
    if (local_1c == 0) {
      local_20 = 0;
      ExceptionList = &local_10;
      local_14 = &stack0xffffffa4;
      goto LAB_004fe54a;
    }
  }
  ExceptionList = &local_10;
  local_20 = FUN_00402bf0(local_1c * 0x30);
LAB_004fe54a:
  local_8 = 3;
  local_18 = local_20;
  iVar6 = FUN_004ff000(*param_1,param_2,local_20,param_2);
  local_8._0_1_ = 4;
  if (iVar6 != 0) {
    local_20 = iVar6;
    FUN_004fea50(param_3);
  }
  local_20 = iVar6 + 0x30;
  local_8 = CONCAT31(local_8._1_3_,3);
  iVar7 = FUN_004ff000(param_2,param_1[1],local_20,iVar6);
  iVar6 = param_1[1];
  for (iVar9 = *param_1; iVar9 != iVar6; iVar9 = iVar9 + 0x30) {
    FUN_004026e0();
    FUN_004026e0();
  }
  piVar5 = (int *)*param_1;
  iVar6 = (param_1[2] - (int)piVar5) / 0x30;
  if (iVar6 != 0) {
    uVar8 = iVar6 * 0x30;
    if (uVar8 < 0x81) {
      FUN_00402330();
      *piVar5 = *(int *)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4) = piVar5;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar5);
    }
  }
  *param_1 = local_18;
  param_1[1] = iVar7;
  param_1[2] = local_1c * 0x30 + local_18;
  ExceptionList = local_10;
  return;
}

