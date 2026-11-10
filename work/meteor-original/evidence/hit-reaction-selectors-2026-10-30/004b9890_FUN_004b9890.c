/* Original Meteor.exe static export @ 004b9890; original sample not executed. */
/* XREF 0059d898 UNCONDITIONAL_CALL */
/* XREF 0059db57 UNCONDITIONAL_CALL */
/* XREF 00487a91 UNCONDITIONAL_CALL */
/* XREF 004b97e3 UNCONDITIONAL_CALL */

void __fastcall FUN_004b9890(undefined4 *param_1)

{
  int *piVar1;
  uint uVar2;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a0d02;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005a9fe0;
  param_1[4] = &PTR_LAB_005a9fac;
  local_4 = 3;
  FUN_004ee340();
  piVar1 = (int *)param_1[0x132];
  uVar2 = param_1[0x134] - (int)piVar1;
  local_4._0_1_ = 2;
  if ((piVar1 != (int *)0x0) && (uVar2 != 0)) {
    if (uVar2 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  piVar1 = (int *)param_1[0x12f];
  uVar2 = param_1[0x131] - (int)piVar1;
  local_4._0_1_ = 1;
  if ((piVar1 != (int *)0x0) && (uVar2 != 0)) {
    if (uVar2 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  piVar1 = (int *)param_1[0x127];
  uVar2 = param_1[0x129] - (int)piVar1;
  local_4 = (uint)local_4._1_3_ << 8;
  if ((piVar1 != (int *)0x0) && (uVar2 != 0)) {
    if (uVar2 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  local_4 = 0xffffffff;
  FUN_004ed450();
  ExceptionList = local_c;
  return;
}

