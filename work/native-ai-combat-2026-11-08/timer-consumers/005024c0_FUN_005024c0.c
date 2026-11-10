/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall FUN_005024c0(int *param_1,undefined4 *param_2,undefined4 *param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  LONG LVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 local_40 [6];
  int local_28;
  int *local_24;
  uint local_20;
  int local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a3fb0;
  local_10 = ExceptionList;
  puVar2 = (undefined4 *)param_1[1];
  local_14 = &stack0xffffffb4;
  if (puVar2 != (undefined4 *)param_1[2]) {
    if (puVar2 != (undefined4 *)0x0) {
      puVar7 = puVar2 + -6;
      for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar2 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar2 = puVar2 + 1;
      }
    }
    puVar2 = (undefined4 *)param_1[1];
    param_1[1] = (int)(puVar2 + 6);
    puVar7 = local_40;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *param_3;
      param_3 = param_3 + 1;
      puVar7 = puVar7 + 1;
    }
    puVar7 = puVar2 + -6;
    iVar5 = ((int)puVar7 - (int)param_2) / 0x18;
    if (0 < iVar5) {
      do {
        puVar7 = puVar7 + -6;
        puVar2 = puVar2 + -6;
        iVar5 = iVar5 + -1;
        puVar8 = puVar7;
        puVar11 = puVar2;
        for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar11 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar11 = puVar11 + 1;
        }
      } while (iVar5 != 0);
    }
    puVar2 = local_40;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *param_2 = *puVar2;
      puVar2 = puVar2 + 1;
      param_2 = param_2 + 1;
    }
    ExceptionList = local_10;
    return;
  }
  iVar5 = ((int)puVar2 - *param_1) / 0x18;
  if (iVar5 == 0) {
    local_18 = 1;
  }
  else {
    iVar5 = iVar5 * 2;
    local_18 = iVar5;
    if (iVar5 == 0) {
      local_1c = 0;
      ExceptionList = &local_10;
      goto LAB_005025b5;
    }
  }
  iVar5 = local_18;
  ExceptionList = &local_10;
  local_1c = FUN_00402bf0(local_18 * 0x18);
LAB_005025b5:
  local_8 = 0;
  puVar2 = (undefined4 *)FUN_00560120(*param_1,param_2,local_1c,param_2);
  if (puVar2 != (undefined4 *)0x0) {
    puVar7 = puVar2;
    for (iVar6 = 6; iVar5 = local_18, iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *param_3;
      param_3 = param_3 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  local_28 = FUN_00560120(param_2,param_1[1],puVar2 + 6,param_2);
  for (iVar6 = *param_1; iVar6 != param_1[1]; iVar6 = iVar6 + 0x18) {
  }
  piVar1 = (int *)*param_1;
  iVar6 = (param_1[2] - (int)piVar1) / 0x18;
  if (iVar6 != 0) {
    uVar3 = iVar6 * 0x18;
    if (uVar3 < 0x81) {
      local_24 = (int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      LVar4 = InterlockedExchange(&DAT_005d59e8,1);
      uVar3 = DAT_005c4248;
      if (LVar4 != 0) {
        uVar9 = 0;
        local_20 = DAT_005d59ec;
        if (DAT_005c4248 != 0) {
          do {
            if (((local_20 >> 1 <= uVar9) && (DAT_005d59e8 == 0)) &&
               (LVar4 = InterlockedExchange(&DAT_005d59e8,1), LVar4 == 0)) {
              DAT_005c4248 = 1000;
              iVar5 = local_18;
              DAT_005d59ec = uVar9;
              goto LAB_0050274c;
            }
            uVar9 = uVar9 + 1;
          } while (uVar9 < uVar3);
        }
        DAT_005c4248 = 0x1e;
        iVar6 = 0;
        while( true ) {
          iVar10 = iVar6 + 6;
          if (0x1b < iVar10) {
            iVar10 = 0x1b;
          }
          LVar4 = InterlockedExchange(&DAT_005d59e8,1);
          iVar5 = local_18;
          if (LVar4 == 0) break;
          if (iVar10 < 0x15) {
            Sleep(0);
            iVar6 = iVar6 + 1;
          }
          else {
            Sleep(1 << ((char)iVar10 - 0x14U & 0x1f));
            iVar6 = iVar6 + 1;
          }
        }
      }
LAB_0050274c:
      *piVar1 = *local_24;
      *local_24 = (int)piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  param_1[1] = local_28;
  *param_1 = local_1c;
  param_1[2] = local_1c + iVar5 * 0x18;
  ExceptionList = local_10;
  return;
}

