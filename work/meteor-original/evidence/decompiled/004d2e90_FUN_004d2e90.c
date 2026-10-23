/* Meteor.exe original x86 @ 004d2e90 */
/* Caller: 004d2dc2 */

void __thiscall FUN_004d2e90(int *param_1,undefined4 *param_2,undefined4 *param_3,int *param_4)

{
  undefined4 *puVar1;
  undefined4 **ppuVar2;
  undefined4 uVar3;
  uint uVar4;
  LONG LVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint uVar10;
  int *piVar11;
  undefined4 *puVar12;
  undefined4 local_4c [10];
  int local_24;
  int *local_20;
  uint local_1c;
  undefined4 *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puVar8 = param_3;
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a1c60;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffa8;
  if (param_3 != (undefined4 *)0x0) {
    iVar7 = param_1[1];
    if ((undefined4 *)((param_1[2] - iVar7) / 0x28) < param_3) {
      local_18 = (undefined4 *)((iVar7 - *param_1) / 0x28);
      ppuVar2 = &param_3;
      if (param_3 <= local_18) {
        ppuVar2 = &local_18;
      }
      local_18 = (undefined4 *)((int)*ppuVar2 + (int)local_18);
      if (local_18 == (undefined4 *)0x0) {
        param_3 = (undefined4 *)0x0;
        ExceptionList = &local_10;
      }
      else {
        ExceptionList = &local_10;
        param_3 = (undefined4 *)FUN_00402bf0((int)local_18 * 0x28);
      }
      local_8 = 0;
      uVar3 = FUN_0049fe20(*param_1,param_2,param_3,param_2);
      uVar3 = FUN_004d4880(uVar3,puVar8,param_4,param_2);
      local_24 = FUN_0049fe20(param_2,param_1[1],uVar3,param_2);
      for (iVar7 = *param_1; iVar7 != param_1[1]; iVar7 = iVar7 + 0x28) {
      }
      piVar11 = (int *)*param_1;
      iVar7 = (param_1[2] - (int)piVar11) / 0x28;
      if (iVar7 != 0) {
        uVar4 = iVar7 * 0x28;
        param_4 = piVar11;
        if (uVar4 < 0x81) {
          local_20 = (int *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
          LVar5 = InterlockedExchange(&DAT_005d59e8,1);
          uVar4 = DAT_005c4248;
          if (LVar5 != 0) {
            uVar10 = 0;
            local_1c = DAT_005d59ec;
            if (DAT_005c4248 != 0) {
              do {
                if (((local_1c >> 1 <= uVar10) && (DAT_005d59e8 == 0)) &&
                   (LVar5 = InterlockedExchange(&DAT_005d59e8,1), LVar5 == 0)) {
                  DAT_005c4248 = 1000;
                  piVar11 = param_4;
                  DAT_005d59ec = uVar10;
                  goto LAB_004d31f2;
                }
                uVar10 = uVar10 + 1;
              } while (uVar10 < uVar4);
            }
            DAT_005c4248 = 0x1e;
            iVar7 = 0;
            while( true ) {
              iVar6 = iVar7 + 6;
              if (0x1b < iVar6) {
                iVar6 = 0x1b;
              }
              LVar5 = InterlockedExchange(&DAT_005d59e8,1);
              piVar11 = param_4;
              if (LVar5 == 0) break;
              if (iVar6 < 0x15) {
                Sleep(0);
                iVar7 = iVar7 + 1;
              }
              else {
                Sleep(1 << ((char)iVar6 - 0x14U & 0x1f));
                iVar7 = iVar7 + 1;
              }
            }
          }
LAB_004d31f2:
          *piVar11 = *local_20;
          *local_20 = (int)piVar11;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(piVar11);
        }
      }
      param_1[1] = local_24;
      *param_1 = (int)param_3;
      param_1[2] = (int)(param_3 + (int)local_18 * 10);
      ExceptionList = local_10;
      return;
    }
    puVar8 = param_4;
    puVar9 = local_4c;
    for (iVar6 = 10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar9 = puVar9 + 1;
    }
    puVar8 = (undefined4 *)param_1[1];
    puVar9 = (undefined4 *)((iVar7 - (int)param_2) / 0x28);
    local_18 = puVar8;
    if (param_3 < puVar9) {
      iVar6 = (int)param_3 * 0x28;
      param_3 = puVar8 + (int)param_3 * -10;
      ExceptionList = &local_10;
      param_4 = (int *)iVar6;
      FUN_0049fe20(param_3,puVar8,puVar8,param_2);
      param_1[1] = param_1[1] + iVar6;
      iVar7 = ((int)param_3 - (int)param_2) / 0x28;
      if (0 < iVar7) {
        do {
          puVar8 = puVar8 + -10;
          param_3 = param_3 + -10;
          iVar7 = iVar7 + -1;
          puVar9 = param_3;
          puVar12 = puVar8;
          for (iVar6 = 10; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar12 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar12 = puVar12 + 1;
          }
          iVar6 = (int)param_4;
        } while (iVar7 != 0);
      }
      puVar8 = param_2;
      while (puVar8 != (undefined4 *)(iVar6 + (int)param_2)) {
        puVar1 = puVar8 + 10;
        puVar9 = local_4c;
        puVar12 = puVar8;
        for (iVar7 = 10; puVar8 = puVar1, iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar12 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar12 = puVar12 + 1;
        }
      }
    }
    else {
      param_3 = (undefined4 *)((int)param_3 - (int)puVar9);
      ExceptionList = &local_10;
      FUN_004d4880(puVar8,param_3,local_4c,param_2);
      iVar7 = param_1[1] + (int)param_3 * 0x28;
      param_1[1] = iVar7;
      FUN_0049fe20(param_2,puVar8,iVar7,param_2);
      param_1[1] = param_1[1] + (int)puVar9 * 0x28;
      if (param_2 != puVar8) {
        do {
          puVar9 = param_2 + 10;
          puVar8 = local_4c;
          for (iVar7 = 10; iVar7 != 0; iVar7 = iVar7 + -1) {
            *param_2 = *puVar8;
            puVar8 = puVar8 + 1;
            param_2 = param_2 + 1;
          }
          param_2 = puVar9;
        } while (puVar9 != local_18);
        ExceptionList = local_10;
        return;
      }
    }
  }
  ExceptionList = local_10;
  return;
}

