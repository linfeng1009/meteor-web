/* Original Meteor.exe static read-only export; sample not executed. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004af110(int *param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  LONG LVar6;
  int iVar7;
  int unaff_EBX;
  uint uVar8;
  code *pcVar9;
  int unaff_ESI;
  int *piVar10;
  int *piVar11;
  uint uVar12;
  uint unaff_EDI;
  float *pfVar13;
  undefined4 uVar14;
  undefined4 uStack_80;
  int iVar15;
  int iVar16;
  int iStack_60;
  int local_5c;
  int local_4c;
  float local_3c;
  uint local_38;
  uint local_34;
  int *piStack_30;
  int *local_2c;
  undefined4 uStack_20;
  int *piStack_18;
  int iStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a0298;
  pvStack_c = ExceptionList;
  local_3c = (float)param_1[0x8f] * _DAT_005a8410;
  ExceptionList = &pvStack_c;
  local_2c = param_1;
  FUN_00487830();
  uVar1 = FUN_0056d800();
  local_38 = uVar1;
  uVar2 = FUN_0056d800();
  local_34 = uVar2;
  uVar3 = FUN_0056d800();
  puVar4 = operator_new(uVar1 * 4);
  for (uVar1 = uVar1 & 0x3fffffff; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
    *(undefined1 *)puVar4 = 0;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  puVar4 = operator_new(uVar2 * 4);
  for (uVar2 = uVar2 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
    *(undefined1 *)puVar4 = 0;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  uStack_80 = 0x4af1d2;
  puVar4 = operator_new(uVar3 * 4);
  for (uVar1 = uVar3 & 0x3fffffff; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
    *(undefined1 *)puVar4 = 0;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  local_4c = 0;
  if (0 < param_3) {
    do {
      uVar1 = (uint)*(char *)(local_4c + param_2);
      FUN_0049d3c0();
      if (local_5c != param_1[0xea]) {
        iVar15 = 1;
        (**(code **)(*(int *)(local_5c + 0x88) + 0xc))();
        uStack_80 = 2;
        local_38 = (**(code **)(*(int *)(unaff_EBX + 0x88) + 0x34))();
        local_34 = 0;
        iVar7 = *(int *)(unaff_ESI + 0x88);
        uVar5 = __ftol(0);
        (**(code **)(iVar7 + 0x2c))(2,uVar5);
        *(undefined1 *)(iVar15 + 0x228) = 0;
        iVar7 = unaff_EBX;
        if ((*(int *)(iVar15 + 0x208) != 1) &&
           (iVar7 = iStack_60, uVar1 = uVar3, *(int *)(iVar15 + 0x208) == 2)) {
          iVar7 = local_5c;
          uVar1 = unaff_EDI;
        }
        piVar10 = (int *)0x0;
        local_34 = 0;
        piStack_30 = (int *)0x0;
        local_2c = (int *)0x0;
        uStack_20 = 0;
        iVar16 = 0;
        if (0 < (int)uVar1) {
          do {
            if (*(int *)(iVar7 + iVar16 * 4) == 0) {
              if (piVar10 == local_2c) {
                FUN_0046ecb0(piVar10,&stack0xffffff8c);
                piVar10 = piStack_30;
              }
              else {
                piVar11 = (int *)0x0;
                if (piVar10 != (int *)0x0) {
                  *piVar10 = iVar16;
                  piVar11 = piStack_30;
                }
                piStack_30 = piVar11 + 1;
                piVar10 = piStack_30;
              }
            }
            iVar16 = iVar16 + 1;
          } while (iVar16 < (int)uVar1);
        }
        if (((int)piVar10 - local_34 & 0xfffffffc) == 0) {
          uVar14 = 0;
          pfVar13 = (float *)0x0;
          uVar5 = *(undefined4 *)(iVar15 + 0x10);
        }
        else {
          iVar16 = _rand();
          uVar14 = 8;
          local_38 = *(uint *)(local_34 +
                              ((uint)(iVar16 * ((int)((int)piVar10 - local_34) >> 2)) / 0x7fff) * 4)
          ;
          *(undefined4 *)(iVar7 + local_38 * 4) = 1;
          local_3c = *(float *)(iVar15 + 0x208);
          pfVar13 = &local_3c;
          uVar5 = *(undefined4 *)(iVar15 + 0x10);
        }
        FUN_004acae0(uVar5,0x3c,pfVar13,uVar14,1);
        (**(code **)(*param_1 + 0x40))(0x2e,&uStack_80,4,1);
        if (*(int *)(local_5c + 0x200) != 0) {
          *(undefined4 *)(local_5c + 0x200) = 1;
        }
        pcVar9 = InterlockedExchange_exref;
        uStack_4 = 0xffffffff;
        iVar7 = iStack_10 - (int)piStack_18 >> 2;
        if (iVar7 != 0) {
          uVar1 = iVar7 * 4;
          if (uVar1 < 0x81) {
            piStack_30 = piStack_18;
            LVar6 = InterlockedExchange(&DAT_005d59e8,1);
            uVar2 = DAT_005c4248;
            if (LVar6 != 0) {
              uVar12 = 0;
              iStack_60 = 0x11;
              if (DAT_005c4248 != 0) {
                uVar8 = DAT_005d59ec >> 1;
                do {
                  if ((uVar12 < uVar8) || (DAT_005d59e8 != 0)) {
                    iVar7 = iStack_60 * iStack_60 * iStack_60 * iStack_60;
                    iVar7 = iVar7 * iVar7;
                    iStack_60 = iVar7 * iVar7;
                  }
                  else {
                    LVar6 = InterlockedExchange(&DAT_005d59e8,1);
                    if (LVar6 == 0) {
                      DAT_005c4248 = 1000;
                      DAT_005d59ec = uVar12;
                      goto LAB_004af503;
                    }
                  }
                  uVar12 = uVar12 + 1;
                  pcVar9 = InterlockedExchange_exref;
                } while (uVar12 < uVar2);
              }
              DAT_005c4248 = 0x1e;
              iVar7 = 6;
              while( true ) {
                iVar15 = iVar7;
                if (0x1b < iVar7) {
                  iVar15 = 0x1b;
                }
                iVar16 = (*pcVar9)();
                if (iVar16 == 0) break;
                if (iVar15 < 0x15) {
                  Sleep(0);
                  iVar7 = iVar7 + 1;
                }
                else {
                  Sleep(1 << ((char)iVar15 - 0x14U & 0x1f));
                  iVar7 = iVar7 + 1;
                }
              }
            }
LAB_004af503:
            *piStack_30 = *(int *)(&DAT_005d59a4 + (uVar1 + 7 >> 3) * 4);
            *(int **)(&DAT_005d59a4 + (uVar1 + 7 >> 3) * 4) = piStack_30;
            DAT_005d59e8 = 0;
            param_1 = local_2c;
          }
          else {
            FUN_005089fd();
          }
        }
      }
      local_4c = local_4c + 1;
    } while (local_4c < param_3);
  }
  FUN_00507850();
  FUN_00507850();
  uStack_80 = 0x4af54e;
  FUN_00507850();
  ExceptionList = pvStack_c;
  return;
}

