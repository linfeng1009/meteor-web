/* Original Meteor.exe static export @ 00565b30; original sample not executed. */
/* XREF 005618f0 UNCONDITIONAL_CALL */

void __thiscall FUN_00565b30(int *param_1,uint *param_2,uint param_3,uint *param_4)

{
  uint *puVar1;
  int *piVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  LONG LVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  uint *puVar11;
  uint uVar12;
  int iVar13;
  uint local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  uVar10 = param_3;
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a5760;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffd0;
  if (param_3 != 0) {
    iVar8 = param_1[1];
    if ((uint)(param_1[2] - iVar8 >> 2) < param_3) {
      local_1c = iVar8 - *param_1 >> 2;
      puVar9 = &param_3;
      if (param_3 <= local_1c) {
        puVar9 = &local_1c;
      }
      uVar10 = *puVar9 + local_1c;
      local_1c = uVar10;
      if (uVar10 == 0) {
        local_18 = 0;
        ExceptionList = &local_10;
      }
      else {
        ExceptionList = &local_10;
        local_18 = FUN_00402bf0(uVar10 * 4);
      }
      local_8 = 0;
      uVar4 = FUN_004b62d0(*param_1,param_2,local_18,param_3);
      uVar4 = FUN_00565eb0(uVar4,param_3,param_4,param_3);
      iVar5 = FUN_004b62d0(param_2,param_1[1],uVar4,param_3);
      for (iVar8 = *param_1; iVar8 != param_1[1]; iVar8 = iVar8 + 4) {
      }
      piVar2 = (int *)*param_1;
      iVar8 = param_1[2] - (int)piVar2 >> 2;
      if (iVar8 != 0) {
        uVar6 = iVar8 * 4;
        if (uVar6 < 0x81) {
          LVar7 = InterlockedExchange(&DAT_005d59e8,1);
          uVar3 = DAT_005c4248;
          if (LVar7 != 0) {
            uVar12 = 0;
            param_4 = (uint *)DAT_005d59ec;
            param_3 = 0x11;
            if (DAT_005c4248 != 0) {
              do {
                if ((uVar12 < (uint)param_4 >> 1) || (DAT_005d59e8 != 0)) {
                  iVar8 = param_3 * param_3 * param_3 * param_3;
                  iVar8 = iVar8 * iVar8;
                  param_3 = iVar8 * iVar8;
                }
                else {
                  LVar7 = InterlockedExchange(&DAT_005d59e8,1);
                  if (LVar7 == 0) {
                    DAT_005c4248 = 1000;
                    uVar10 = local_1c;
                    DAT_005d59ec = uVar12;
                    goto LAB_00565e18;
                  }
                }
                uVar12 = uVar12 + 1;
              } while (uVar12 < uVar3);
            }
            DAT_005c4248 = 0x1e;
            iVar8 = 0;
            while( true ) {
              iVar13 = iVar8 + 6;
              if (0x1b < iVar13) {
                iVar13 = 0x1b;
              }
              LVar7 = InterlockedExchange(&DAT_005d59e8,1);
              uVar10 = local_1c;
              if (LVar7 == 0) break;
              if (iVar13 < 0x15) {
                Sleep(0);
                iVar8 = iVar8 + 1;
              }
              else {
                Sleep(1 << ((char)iVar13 - 0x14U & 0x1f));
                iVar8 = iVar8 + 1;
              }
            }
          }
LAB_00565e18:
          *piVar2 = *(int *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
          *(int **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = piVar2;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(piVar2);
        }
      }
      *param_1 = local_18;
      param_1[1] = iVar5;
      param_1[2] = local_18 + uVar10 * 4;
      ExceptionList = local_10;
      return;
    }
    puVar9 = (uint *)param_1[1];
    uVar6 = *param_4;
    param_4 = (uint *)(iVar8 - (int)param_2 >> 2);
    if (param_3 < param_4) {
      iVar8 = param_3 * 4;
      param_4 = puVar9 + -param_3;
      ExceptionList = &local_10;
      param_3 = uVar6;
      FUN_004b62d0(param_4,puVar9,puVar9,uVar6);
      param_1[1] = param_1[1] + iVar8;
      iVar8 = (int)param_4 - (int)param_2 >> 2;
      if (0 < iVar8) {
        puVar11 = puVar9;
        do {
          puVar1 = (uint *)((int)param_4 + (-4 - (int)puVar9) + (int)puVar11);
          puVar11 = puVar11 + -1;
          iVar8 = iVar8 + -1;
          *puVar11 = *puVar1;
        } while (iVar8 != 0);
      }
      puVar9 = param_2 + uVar10;
      for (; param_2 != puVar9; param_2 = param_2 + 1) {
        *param_2 = param_3;
      }
    }
    else {
      iVar8 = param_3 - (int)param_4;
      ExceptionList = &local_10;
      param_3 = uVar6;
      FUN_00565eb0(puVar9,iVar8,&param_3,uVar6);
      iVar8 = param_1[1] + iVar8 * 4;
      param_1[1] = iVar8;
      FUN_004b62d0(param_2,puVar9,iVar8,param_3);
      param_1[1] = param_1[1] + (int)param_4 * 4;
      if (param_2 != puVar9) {
        do {
          *param_2 = param_3;
          param_2 = param_2 + 1;
        } while (param_2 != puVar9);
        ExceptionList = local_10;
        return;
      }
    }
  }
  ExceptionList = local_10;
  return;
}

