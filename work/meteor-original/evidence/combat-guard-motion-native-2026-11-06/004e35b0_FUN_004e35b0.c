/* Original Meteor.exe static export @ 004e35b0; original sample not executed. */
/* XREF 004e3593 UNCONDITIONAL_CALL */
/* XREF 004e3765 UNCONDITIONAL_CALL */

void __fastcall FUN_004e35b0(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a2d49;
  local_c = ExceptionList;
  piVar1 = (int *)param_1[0x10];
  iVar2 = param_1[0x12] - (int)piVar1 >> 2;
  ExceptionList = &local_c;
  if (iVar2 != 0) {
    uVar3 = iVar2 * 4;
    if (uVar3 < 0x81) {
      ExceptionList = &local_c;
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      ExceptionList = &local_c;
      FUN_005089fd(piVar1);
    }
  }
  *param_1 = &PTR_FUN_005aaa78;
  piVar1 = param_1 + 0xd;
  local_4._0_1_ = 3;
  local_4._1_3_ = 0;
  if (param_1[0xe] != 0) {
    FUN_004e40f0(*(undefined4 *)(*piVar1 + 4));
    *(int *)(*piVar1 + 8) = *piVar1;
    *(undefined4 *)(*piVar1 + 4) = 0;
    *(int *)(*piVar1 + 0xc) = *piVar1;
    param_1[0xe] = 0;
  }
  local_4 = CONCAT31(local_4._1_3_,2);
  FUN_00402e90(*piVar1,0x18);
  piVar1 = (int *)param_1[10];
  iVar2 = param_1[0xc] - (int)piVar1 >> 2;
  if (iVar2 != 0) {
    uVar3 = iVar2 * 4;
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
  piVar1 = (int *)param_1[7];
  iVar2 = param_1[9] - (int)piVar1 >> 2;
  if (iVar2 != 0) {
    uVar3 = iVar2 * 4;
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
  local_4 = 0xffffffff;
  FUN_00503280();
  ExceptionList = local_c;
  return;
}

