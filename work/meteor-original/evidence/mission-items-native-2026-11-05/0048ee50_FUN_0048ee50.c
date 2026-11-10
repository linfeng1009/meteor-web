/* Original Meteor.exe static export @ 0048ee50; original sample not executed. */
/* XREF 0059e093 UNCONDITIONAL_CALL */
/* XREF 0059ea43 UNCONDITIONAL_CALL */
/* XREF 0059fd1c UNCONDITIONAL_CALL */
/* XREF 005a0033 UNCONDITIONAL_CALL */
/* XREF 005a10b3 UNCONDITIONAL_CALL */
/* XREF 0049515e UNCONDITIONAL_CALL */
/* XREF 00495275 UNCONDITIONAL_CALL */
/* XREF 004ac4cc UNCONDITIONAL_CALL */
/* XREF 004ac729 UNCONDITIONAL_CALL */
/* XREF 004bd7c9 UNCONDITIONAL_CALL */
/* XREF 004bd7dd UNCONDITIONAL_CALL */
/* XREF 004aa314 UNCONDITIONAL_CALL */
/* XREF 004aa328 UNCONDITIONAL_CALL */
/* XREF 0048be1c UNCONDITIONAL_CALL */

void __fastcall FUN_0048ee50(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  void *pvStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0059e4a4;
  pvStack_c = ExceptionList;
  piVar1 = (int *)(param_1 + 0x294);
  local_4._0_1_ = 6;
  local_4._1_3_ = 0;
  ExceptionList = &pvStack_c;
  if (*(int *)(param_1 + 0x298) != 0) {
    ExceptionList = &pvStack_c;
    FUN_0049c2f0();
    *(int *)(*piVar1 + 8) = *piVar1;
    *(undefined4 *)(*piVar1 + 4) = 0;
    *(int *)(*piVar1 + 0xc) = *piVar1;
    *(undefined4 *)(param_1 + 0x298) = 0;
  }
  local_4._0_1_ = 5;
  FUN_00402e90();
  local_4._0_1_ = 4;
  if ((*(int *)(param_1 + 0x250) != 0) && (*(int *)(param_1 + 600) != *(int *)(param_1 + 0x250))) {
    FUN_00402e90();
  }
  local_4 = CONCAT31(local_4._1_3_,3);
  if ((*(int *)(param_1 + 0x244) != 0) && (*(int *)(param_1 + 0x24c) != *(int *)(param_1 + 0x244)))
  {
    FUN_00402e90();
  }
  piVar1 = *(int **)(param_1 + 0x220);
  uVar3 = *(int *)(param_1 + 0x228) - (int)piVar1;
  if ((piVar1 != (int *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd();
    }
  }
  local_4._0_1_ = 1;
  if ((*(int *)(param_1 + 0x214) != 0) && (*(int *)(param_1 + 0x21c) != *(int *)(param_1 + 0x214)))
  {
    FUN_00402e90();
  }
  *(undefined ***)(param_1 + 0x70) = &PTR_FUN_005a9490;
  local_4._0_1_ = 9;
  FUN_0049b380();
  puVar2 = *(undefined4 **)(param_1 + 0xb8);
  puVar4 = *(undefined4 **)(param_1 + 0xb4);
  local_4._0_1_ = 10;
  for (; puVar4 != puVar2; puVar4 = puVar4 + 0x12) {
    (**(code **)*puVar4)();
  }
  local_4._0_1_ = 8;
  FUN_0049b3d0();
  local_4._0_1_ = 7;
  FUN_0049b380();
  local_4 = (uint)local_4._1_3_ << 8;
  FUN_004920f0();
  local_4 = 0xb;
  FUN_004e6050(param_1 + 0x4c);
  FUN_0049e030();
  local_4 = 0xffffffff;
  FUN_004fe690();
  ExceptionList = pvStack_c;
  return;
}

