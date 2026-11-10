/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall FUN_005005c0(uint *param_1,uint *param_2,uint param_3,uint *param_4)

{
  uint *puVar1;
  int *piVar2;
  void **ppvVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  uint uVar10;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  uVar10 = param_3;
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a3ee0;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffdc;
  if (param_3 != 0) {
    uVar7 = param_1[1];
    if ((uint)((int)(param_1[2] - uVar7) >> 2) < param_3) {
      puVar5 = &param_3;
      local_18 = (int)(uVar7 - *param_1) >> 2;
      if (param_3 <= local_18) {
        puVar5 = &local_18;
      }
      local_18 = *puVar5 + local_18;
      if (local_18 == 0) {
        param_3 = 0;
        ExceptionList = &local_10;
      }
      else {
        ExceptionList = &local_10;
        param_3 = FUN_00402bf0(local_18 * 4);
      }
      local_8 = 0;
      puVar5 = (uint *)FUN_0049f3d0(*param_1,param_2,param_3,param_2,0);
      for (; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar5 = *param_4;
        puVar5 = puVar5 + 1;
      }
      uVar10 = FUN_0049f3d0(param_2,param_1[1],puVar5,param_2,0);
      piVar2 = (int *)*param_1;
      local_8 = 0xffffffff;
      iVar4 = (int)(param_1[2] - (int)piVar2) >> 2;
      if (iVar4 != 0) {
        uVar7 = iVar4 * 4;
        if (uVar7 < 0x81) {
          FUN_00402330();
          *piVar2 = *(int *)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4);
          *(int **)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4) = piVar2;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(piVar2);
        }
      }
      *param_1 = param_3;
      param_1[1] = uVar10;
      param_1[2] = param_3 + local_18 * 4;
      ExceptionList = local_10;
      return;
    }
    puVar5 = (uint *)param_1[1];
    uVar10 = *param_4;
    param_4 = (uint *)((int)(uVar7 - (int)param_2) >> 2);
    if (param_3 < param_4) {
      param_4 = (uint *)(param_3 * 4);
      puVar9 = puVar5 + -param_3;
      ExceptionList = &local_10;
      param_3 = uVar10;
      FUN_0049f3d0(puVar9,puVar5,puVar5,param_2,0);
      param_1[1] = param_1[1] + (int)param_4;
      iVar4 = (int)puVar9 - (int)param_2 >> 2;
      if (0 < iVar4) {
        puVar8 = puVar5;
        do {
          puVar1 = (uint *)((int)puVar9 + (-4 - (int)puVar5) + (int)puVar8);
          puVar8 = puVar8 + -1;
          iVar4 = iVar4 + -1;
          *puVar8 = *puVar1;
        } while (iVar4 != 0);
      }
      param_4 = (uint *)((int)param_4 + (int)param_2);
      for (; param_2 != param_4; param_2 = param_2 + 1) {
        *param_2 = param_3;
      }
    }
    else {
      iVar6 = param_3 - (int)param_4;
      iVar4 = iVar6;
      puVar9 = puVar5;
      ExceptionList = &local_10;
      ppvVar3 = &local_10;
      if (iVar6 != 0) {
        for (; ppvVar3 = ExceptionList, iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar9 = uVar10;
          puVar9 = puVar9 + 1;
        }
      }
      ExceptionList = ppvVar3;
      uVar7 = param_1[1] + iVar6 * 4;
      param_1[1] = uVar7;
      param_3 = uVar10;
      FUN_0049f3d0(param_2,puVar5,uVar7,param_2,0);
      param_1[1] = param_1[1] + (int)param_4 * 4;
      if (param_2 != puVar5) {
        do {
          *param_2 = param_3;
          param_2 = param_2 + 1;
        } while (param_2 != puVar5);
        ExceptionList = local_10;
        return;
      }
    }
  }
  ExceptionList = local_10;
  return;
}

