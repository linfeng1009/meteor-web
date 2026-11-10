/* Original Meteor.exe static export @ 0048f050; original sample not executed. */
/* XREF 0049d21e UNCONDITIONAL_CALL */
/* XREF 0049fc63 UNCONDITIONAL_CALL */
/* XREF 0059e09e UNCONDITIONAL_CALL */
/* XREF 0059ea4e UNCONDITIONAL_CALL */
/* XREF 0059fd27 UNCONDITIONAL_CALL */
/* XREF 005a003e UNCONDITIONAL_CALL */
/* XREF 005a10be UNCONDITIONAL_CALL */
/* XREF 0049b5a6 UNCONDITIONAL_CALL */
/* XREF 004941d7 UNCONDITIONAL_CALL */
/* XREF 004aa566 UNCONDITIONAL_CALL */
/* XREF 004ac83c UNCONDITIONAL_CALL */
/* XREF 004bd46b UNCONDITIONAL_CALL */

void __fastcall FUN_0048f050(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0059e534;
  local_c = ExceptionList;
  local_4._0_1_ = 6;
  local_4._1_3_ = 0;
  ExceptionList = &local_c;
  FUN_0049aff0();
  local_4._0_1_ = 5;
  FUN_00402e90();
  local_4._0_1_ = 4;
  if ((*(int *)(param_1 + 600) != 0) && (*(int *)(param_1 + 0x260) != *(int *)(param_1 + 600))) {
    FUN_00402e90();
  }
  local_4._0_1_ = 3;
  if ((*(int *)(param_1 + 0x24c) != 0) && (*(int *)(param_1 + 0x254) != *(int *)(param_1 + 0x24c)))
  {
    FUN_00402e90();
  }
  local_4 = CONCAT31(local_4._1_3_,2);
  if ((*(int *)(param_1 + 0x228) != 0) && (*(int *)(param_1 + 0x230) != *(int *)(param_1 + 0x228)))
  {
    FUN_00402e90();
  }
  piVar1 = *(int **)(param_1 + 0x21c);
  uVar3 = *(int *)(param_1 + 0x224) - (int)piVar1;
  if ((piVar1 != (int *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      FUN_00443330();
    }
    else {
      FUN_005089fd();
    }
  }
  *(undefined ***)(param_1 + 0x78) = &PTR_FUN_005a9490;
  local_4._0_1_ = 9;
  FUN_0049b380();
  iVar2 = *(int *)(param_1 + 0xc0);
  iVar4 = *(int *)(param_1 + 0xbc);
  local_4._0_1_ = 10;
  for (; iVar4 != iVar2; iVar4 = iVar4 + 0x48) {
    FUN_0049eb00();
  }
  local_4._0_1_ = 8;
  FUN_0049b3d0();
  local_4._0_1_ = 7;
  FUN_0049b380();
  local_4 = (uint)local_4._1_3_ << 8;
  FUN_004920f0();
  local_4 = 0xb;
  FUN_004e6050(param_1 + 0x54);
  FUN_0049e030();
  local_4 = 0xffffffff;
  FUN_004fe690();
  ExceptionList = local_c;
  return;
}

