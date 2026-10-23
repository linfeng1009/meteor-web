/* Meteor.exe original x86 @ 004d3690 */
/* Caller: 004d2bcc */
/* Caller: 004d50e9 */
/* Caller: 004d5155 */
/* Caller: 004d5a3c */

void __thiscall FUN_004d3690(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined **local_68 [15];
  undefined1 local_2c [12];
  int local_20;
  int local_1c;
  int local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a1cba;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_14 = &stack0xffffff8c;
  local_20 = param_1[1];
  if (local_20 != param_1[2]) {
    local_8 = 0;
    local_1c = local_20;
    local_14 = &stack0xffffff8c;
    if (local_20 != 0) {
      local_14 = &stack0xffffff8c;
      FUN_004d3b70(local_20 + -0x48);
    }
    local_8 = 0xffffffff;
    param_1[1] = param_1[1] + 0x48;
    FUN_0049ab40(param_3);
    local_8 = 1;
    FUN_0049f4c0(param_3 + 0x3c);
    local_68[0] = &PTR_FUN_005a9488;
    local_8 = 2;
    FUN_004d4640(param_2,param_1[1] + -0x90,param_1[1] + -0x48,param_2,0);
    FUN_004d3cd0(local_68);
    FUN_004d3e60(local_2c);
    local_8 = 3;
    FUN_0049b240();
    local_8 = 0xffffffff;
    FUN_004920f0();
    *unaff_FS_OFFSET = local_10;
    return;
  }
  local_1c = (local_20 - *param_1) / 0x48;
  if (local_1c == 0) {
    local_1c = 1;
  }
  else {
    local_1c = local_1c * 2;
    if (local_1c == 0) {
      local_20 = 0;
      local_14 = &stack0xffffff8c;
      goto LAB_004d37bf;
    }
  }
  local_20 = FUN_00402bf0(local_1c * 0x48);
LAB_004d37bf:
  local_8 = 4;
  local_18 = local_20;
  iVar4 = FUN_004d48f0(*param_1,param_2,local_20,param_2);
  local_8._0_1_ = 5;
  if (iVar4 != 0) {
    local_20 = iVar4;
    FUN_004d3b70(param_3);
  }
  local_20 = iVar4 + 0x48;
  local_8 = CONCAT31(local_8._1_3_,4);
  iVar4 = FUN_004d48f0(param_2,param_1[1],local_20,iVar4);
  puVar1 = (undefined4 *)param_1[1];
  puVar6 = (undefined4 *)*param_1;
  local_8 = 0xffffffff;
  for (; puVar6 != puVar1; puVar6 = puVar6 + 0x12) {
    (**(code **)*puVar6)(0);
  }
  piVar2 = (int *)*param_1;
  iVar3 = (param_1[2] - (int)piVar2) / 0x48;
  if (iVar3 != 0) {
    uVar5 = iVar3 * 0x48;
    if (uVar5 < 0x81) {
      FUN_00402330();
      *piVar2 = *(int *)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4) = piVar2;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar2);
    }
  }
  *param_1 = local_18;
  param_1[1] = iVar4;
  param_1[2] = local_18 + local_1c * 0x48;
  *unaff_FS_OFFSET = local_10;
  return;
}

