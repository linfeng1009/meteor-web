/* Original Meteor.exe read-only export. Sample not executed. */

int __fastcall FUN_004fb550(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a3d1b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005aa65c;
  piVar1 = (int *)param_1[0x42];
  local_4 = 4;
  iVar2 = param_1[0x44] - (int)piVar1 >> 1;
  if (iVar2 != 0) {
    uVar3 = iVar2 * 2;
    if (uVar3 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  piVar1 = (int *)param_1[0x3f];
  uVar3 = param_1[0x41] - (int)piVar1;
  local_4._0_1_ = 3;
  if ((piVar1 != (int *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  local_4._0_1_ = 2;
  iVar2 = (int)(param_1[0x2b] - param_1[0x29]) >> 2;
  if (iVar2 != 0) {
    FUN_00402e90(param_1[0x29],iVar2 * 4);
  }
  piVar1 = (int *)param_1[0x26];
  uVar3 = param_1[0x28] - (int)piVar1;
  local_4._0_1_ = 1;
  if ((piVar1 != (int *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  iVar2 = param_1[0x23];
  local_4 = (uint)local_4._1_3_ << 8;
  if ((iVar2 != 0) && (param_1[0x25] - iVar2 != 0)) {
    FUN_00402e90(iVar2,param_1[0x25] - iVar2);
  }
  iVar2 = param_1[0x1b];
  iVar5 = param_1[0x1a];
  local_4 = 5;
  for (; iVar5 != iVar2; iVar5 = iVar5 + 0x30) {
    FUN_004c82d0();
  }
  iVar2 = param_1[0x1a];
  iVar4 = param_1[0x1c] - iVar2;
  iVar5 = iVar4 * 0x2aaaaaab;
  iVar4 = iVar4 / 0x30;
  local_4 = 0xffffffff;
  if (iVar4 != 0) {
    iVar5 = FUN_00402e90(iVar2,iVar4 * 0x30);
  }
  ExceptionList = local_c;
  return iVar5;
}

