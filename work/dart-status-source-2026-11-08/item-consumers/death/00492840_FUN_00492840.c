/* Original Meteor.exe static export @ 00492840; original sample not executed. */
/* XREF 0059e051 UNCONDITIONAL_CALL */
/* XREF 0059e0e0 UNCONDITIONAL_CALL */
/* XREF 0059e431 UNCONDITIONAL_CALL */
/* XREF 0059e4c1 UNCONDITIONAL_CALL */
/* XREF 0059ea01 UNCONDITIONAL_CALL */
/* XREF 0059f06f UNCONDITIONAL_CALL */
/* XREF 0059fff1 UNCONDITIONAL_CALL */
/* XREF 005a07ba UNCONDITIONAL_CALL */
/* XREF 005a1071 UNCONDITIONAL_CALL */
/* XREF 00492a83 UNCONDITIONAL_CALL */
/* XREF 0048bfd9 UNCONDITIONAL_CALL */

void __fastcall FUN_00492840(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int *piVar6;
  void *pvStack_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_0059e8c6;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  *param_1 = &PTR_FUN_005a9490;
  local_4 = 2;
  piVar6 = *(int **)param_1[0x14];
  if (piVar6 != (int *)param_1[0x14]) {
    do {
      piVar1 = (int *)*piVar6;
      (**(code **)piVar6[2])(0);
      FUN_00402e90(piVar6,0x50);
      piVar6 = piVar1;
    } while (piVar1 != (int *)param_1[0x14]);
  }
  *(undefined4 *)param_1[0x14] = param_1[0x14];
  *(undefined4 *)(param_1[0x14] + 4) = param_1[0x14];
  FUN_00402e90(param_1[0x14],0x50);
  puVar2 = (undefined4 *)param_1[0x12];
  puVar5 = (undefined4 *)param_1[0x11];
  local_4 = CONCAT31(local_4._1_3_,3);
  for (; puVar5 != puVar2; puVar5 = puVar5 + 0x12) {
    (**(code **)*puVar5)(0);
  }
  piVar6 = (int *)param_1[0x11];
  iVar3 = (param_1[0x13] - (int)piVar6) / 0x48;
  if (iVar3 != 0) {
    uVar4 = iVar3 * 0x48;
    if (uVar4 < 0x81) {
      FUN_00402330();
      *piVar6 = *(int *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = piVar6;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar6);
    }
  }
  local_4 = local_4 & 0xffffff00;
  piVar6 = *(int **)param_1[0x10];
  if (piVar6 != (int *)param_1[0x10]) {
    do {
      piVar1 = (int *)*piVar6;
      (**(code **)piVar6[2])(0);
      FUN_00402e90(piVar6,0x50);
      piVar6 = piVar1;
    } while (piVar1 != (int *)param_1[0x10]);
  }
  *(undefined4 *)param_1[0x10] = param_1[0x10];
  *(undefined4 *)(param_1[0x10] + 4) = param_1[0x10];
  puVar2 = (undefined4 *)param_1[0x10];
  FUN_00402330();
  local_4 = 0xffffffff;
  *puVar2 = DAT_005d59cc;
  DAT_005d59e8 = 0;
  DAT_005d59cc = puVar2;
  *param_1 = &PTR_FUN_005a94e4;
  iVar3 = (int)(param_1[0xe] - param_1[0xc]) / 0xc;
  if (iVar3 != 0) {
    FUN_00402e90(param_1[0xc],iVar3 * 0xc);
  }
  FUN_00402bd0();
  FUN_00402bd0();
  FUN_00402bd0();
  ExceptionList = pvStack_c;
  return;
}

