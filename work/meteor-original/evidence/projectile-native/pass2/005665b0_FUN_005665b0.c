/* Original Meteor.exe static export @ 005665b0; original sample not executed. */
/* XREF 005a2696 UNCONDITIONAL_CALL */
/* XREF 005a26e2 UNCONDITIONAL_CALL */
/* XREF 004db709 UNCONDITIONAL_CALL */

void __fastcall FUN_005665b0(int *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  void **ppvVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  void *pvStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a5831;
  pvStack_c = ExceptionList;
  iVar6 = 0;
  local_4 = 2;
  ExceptionList = &pvStack_c;
  ppvVar3 = &pvStack_c;
  if (0 < *param_1) {
    do {
      piVar7 = *(int **)(param_1[1] + iVar6 * 4);
      iVar4 = FUN_0056f310();
      if (iVar4 != 0) {
        FUN_0055df80(piVar7);
      }
      (**(code **)(*piVar7 + 8))(1);
      iVar6 = iVar6 + 1;
      ppvVar3 = ExceptionList;
    } while (iVar6 < *param_1);
  }
  ExceptionList = ppvVar3;
  iVar6 = param_1[1];
  iVar4 = param_1[2];
  FUN_0049f3d0(iVar4,iVar4,iVar6,param_1,0);
  param_1[2] = param_1[2] + (iVar4 - iVar6 >> 2) * -4;
  piVar7 = (int *)param_1[5];
  local_4._0_1_ = 1;
  uVar5 = param_1[7] - (int)piVar7;
  if ((piVar7 != (int *)0x0) && (uVar5 != 0)) {
    if (uVar5 < 0x81) {
      FUN_00402330();
      *piVar7 = *(int *)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4) = piVar7;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar7);
    }
  }
  local_4 = (uint)local_4._1_3_ << 8;
  piVar7 = *(int **)param_1[4];
  if (piVar7 != (int *)param_1[4]) {
    do {
      piVar1 = (int *)*piVar7;
      FUN_00402e90(piVar7,0xc);
      piVar7 = piVar1;
    } while (piVar1 != (int *)param_1[4]);
  }
  *(int *)param_1[4] = param_1[4];
  *(int *)(param_1[4] + 4) = param_1[4];
  puVar2 = (undefined4 *)param_1[4];
  FUN_00402330();
  local_4 = 0xffffffff;
  *puVar2 = DAT_005d59ac;
  DAT_005d59e8 = 0;
  piVar7 = (int *)param_1[1];
  iVar6 = param_1[3] - (int)piVar7 >> 2;
  DAT_005d59ac = puVar2;
  if (iVar6 != 0) {
    uVar5 = iVar6 * 4;
    if (0x80 < uVar5) {
      FUN_005089fd(piVar7);
      ExceptionList = pvStack_c;
      return;
    }
    FUN_00402330();
    *piVar7 = *(int *)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4);
    *(int **)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4) = piVar7;
  }
  DAT_005d59e8 = 0;
  ExceptionList = pvStack_c;
  return;
}

