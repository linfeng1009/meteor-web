/* Original Meteor.exe static export @ 004ed450; original sample not executed. */
/* XREF 004b99cb UNCONDITIONAL_CALL */
/* XREF 004ecc41 UNCONDITIONAL_CALL */
/* XREF 005a0c73 UNCONDITIONAL_CALL */
/* XREF 005a0cd3 UNCONDITIONAL_CALL */
/* XREF 005a3193 UNCONDITIONAL_CALL */
/* XREF 005a31b3 UNCONDITIONAL_CALL */
/* XREF 004ed343 UNCONDITIONAL_CALL */

void __fastcall FUN_004ed450(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  int *piVar4;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a32c7;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005ab468;
  param_1[4] = &PTR_LAB_005ab434;
  local_4 = 5;
  if (param_1[0x96] != 0) {
    FUN_00507850(param_1[0x96]);
  }
  param_1[0x96] = 0;
  FUN_004f2570();
  FUN_004ee340();
  piVar4 = (int *)param_1[0xde];
  uVar3 = param_1[0xe0] - (int)piVar4;
  local_4._0_1_ = 4;
  if ((piVar4 != (int *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
      FUN_00402330();
      *piVar4 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar4;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar4);
    }
  }
  piVar4 = (int *)param_1[0x91];
  uVar3 = param_1[0x93] - (int)piVar4;
  local_4._0_1_ = 3;
  if (uVar3 != 0) {
    if (uVar3 < 0x81) {
      FUN_00402330();
      *piVar4 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar4;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar4);
    }
  }
  local_4._0_1_ = 2;
  piVar4 = *(int **)param_1[0x90];
  if (piVar4 != (int *)param_1[0x90]) {
    do {
      piVar1 = (int *)*piVar4;
      FUN_00402e90(piVar4,0xc);
      piVar4 = piVar1;
    } while (piVar1 != (int *)param_1[0x90]);
  }
  *(undefined4 *)param_1[0x90] = param_1[0x90];
  *(undefined4 *)(param_1[0x90] + 4) = param_1[0x90];
  puVar2 = (undefined4 *)param_1[0x90];
  FUN_00402330();
  local_4._0_1_ = 1;
  *puVar2 = DAT_005d59ac;
  DAT_005d59e8 = 0;
  piVar4 = *(int **)param_1[0x8f];
  DAT_005d59ac = puVar2;
  if (piVar4 != (int *)param_1[0x8f]) {
    do {
      piVar1 = (int *)*piVar4;
      FUN_00402e90(piVar4,0xc);
      piVar4 = piVar1;
    } while (piVar1 != (int *)param_1[0x8f]);
  }
  *(undefined4 *)param_1[0x8f] = param_1[0x8f];
  *(undefined4 *)(param_1[0x8f] + 4) = param_1[0x8f];
  puVar2 = (undefined4 *)param_1[0x8f];
  FUN_00402330();
  *puVar2 = DAT_005d59ac;
  DAT_005d59e8 = 0;
  local_4 = (uint)local_4._1_3_ << 8;
  DAT_005d59ac = puVar2;
  FUN_004b29c0();
  local_4 = 0xffffffff;
  FUN_004a9190();
  ExceptionList = local_c;
  return;
}

