/* Original Meteor.exe static export @ 004e3f20; original sample not executed. */
/* XREF 005a2823 UNCONDITIONAL_CALL */
/* XREF 005a2883 UNCONDITIONAL_CALL */
/* XREF 005a28e3 UNCONDITIONAL_CALL */
/* XREF 005a2943 UNCONDITIONAL_CALL */
/* XREF 005a29a3 UNCONDITIONAL_CALL */
/* XREF 005a2a03 UNCONDITIONAL_CALL */
/* XREF 005a2a63 UNCONDITIONAL_CALL */
/* XREF 005a2ac3 UNCONDITIONAL_CALL */
/* XREF 005a2b23 UNCONDITIONAL_CALL */
/* XREF 005a2b83 UNCONDITIONAL_CALL */
/* XREF 005a2c03 UNCONDITIONAL_CALL */
/* XREF 005a2ca3 UNCONDITIONAL_CALL */
/* XREF 005a2d03 UNCONDITIONAL_CALL */
/* XREF 004e40b3 UNCONDITIONAL_CALL */

void __fastcall FUN_004e3f20(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = ExceptionList;
  puStack_8 = &LAB_005a2d89;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005aaa78;
  iVar5 = 0;
  piVar2 = param_1 + 0xd;
  local_4 = 3;
  if (param_1[0xe] != 0) {
    iVar3 = *(int *)(*piVar2 + 4);
    while (iVar3 != 0) {
      FUN_004e40f0(*(undefined4 *)(iVar3 + 0xc));
      iVar5 = *(int *)(iVar3 + 8);
      FUN_00402e90(iVar3,0x18);
      iVar3 = iVar5;
    }
    *(int *)(*piVar2 + 8) = *piVar2;
    *(int *)(*piVar2 + 4) = iVar5;
    *(int *)(*piVar2 + 0xc) = *piVar2;
    param_1[0xe] = iVar5;
  }
  puVar1 = (undefined4 *)*piVar2;
  FUN_00402330();
  *puVar1 = DAT_005d59b0;
  piVar2 = (int *)param_1[10];
  iVar3 = param_1[0xc] - (int)piVar2 >> 2;
  DAT_005d59b0 = puVar1;
  DAT_005d59e8 = iVar5;
  if (iVar3 != 0) {
    uVar4 = iVar3 * 4;
    if (uVar4 < 0x81) {
      FUN_00402330();
      *piVar2 = *(int *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = piVar2;
      DAT_005d59e8 = iVar5;
    }
    else {
      FUN_005089fd(piVar2);
    }
  }
  piVar2 = (int *)param_1[7];
  iVar3 = param_1[9] - (int)piVar2 >> 2;
  if (iVar3 != 0) {
    uVar4 = iVar3 * 4;
    if (uVar4 < 0x81) {
      FUN_00402330();
      *piVar2 = *(int *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = piVar2;
      DAT_005d59e8 = iVar5;
    }
    else {
      FUN_005089fd(piVar2);
    }
  }
  local_4 = 0xffffffff;
  FUN_00503280();
  ExceptionList = local_c;
  return;
}

