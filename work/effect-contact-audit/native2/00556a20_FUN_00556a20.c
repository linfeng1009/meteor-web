/* Original Meteor.exe static export @ 00556a20; original sample not executed. */
/* XREF 004dbdc2 UNCONDITIONAL_CALL */
/* XREF 00583e83 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_00556a20(int *param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  void *pvVar5;
  LONG LVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  uint uVar12;
  int *piVar13;
  uint uVar14;
  char *pcVar15;
  int *piVar16;
  char *pcVar17;
  undefined4 *puVar18;
  bool bVar19;
  int local_124;
  int *local_120;
  undefined4 *local_11c;
  int *local_118;
  int *local_114;
  undefined4 *local_110;
  undefined1 auStack_10c [64];
  undefined1 auStack_cc [64];
  undefined1 local_8c [128];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a4f67;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar3 = FUN_00509f8f(param_2,&DAT_005ca380);
  uVar4 = 0;
  if (iVar3 != 0) {
    iVar8 = param_1[0xd4];
    if (iVar8 != 0) {
      FUN_0050ace3(iVar8,0x334,*(undefined4 *)(iVar8 + -4),&LAB_00573790);
      FUN_00507850(iVar8 + -4);
      param_1[0xd4] = 0;
    }
    iVar8 = param_1[0xd5];
    if (iVar8 != 0) {
      FUN_0050ace3(iVar8,0x2f0,*(undefined4 *)(iVar8 + -4),FUN_005722c0);
      FUN_00507850(iVar8 + -4);
      param_1[0xd5] = 0;
    }
    if (param_1[0xc9] != 0) {
      FUN_00507850(param_1[0xc9]);
      param_1[0xc9] = 0;
    }
    FUN_00571c70(iVar3,2);
    iVar8 = 0xb4 - (int)param_2;
    do {
      cVar2 = *param_2;
      param_2[(int)param_1 + iVar8] = cVar2;
      param_2 = param_2 + 1;
    } while (cVar2 != '\0');
    piVar16 = param_1 + 7;
    FUN_0050b600(iVar3,s__s__d__s__d_005d12d0,local_8c,piVar16,local_8c,param_1 + 8);
    iVar8 = *piVar16;
    local_120 = operator_new(iVar8 * 0x334 + 4);
    local_4 = 0;
    if (local_120 == (int *)0x0) {
      piVar13 = (int *)0x0;
    }
    else {
      piVar13 = local_120 + 1;
      *local_120 = iVar8;
      FUN_0050ac61(piVar13,0x334,iVar8,FUN_00573710,&LAB_00573790);
    }
    param_1[0xd4] = (int)piVar13;
    if (piVar13 == (int *)0x0) {
      uVar4 = 0;
    }
    else {
      local_11c = (undefined4 *)0x0;
      local_118 = (int *)0x0;
      local_114 = (int *)0x0;
      local_4 = 1;
      local_124 = 0;
      if (0 < *piVar16) {
        piVar13 = piVar13 + 10;
        do {
          piVar13[2] = local_124;
          *piVar13 = (int)param_1;
          FUN_005566d0(iVar3,piVar13 + -10);
          if (*(char *)((int)piVar13 + -0x27) == 'a') {
            if (local_118 == local_114) {
              FUN_0046ecb0(local_118,&local_124);
            }
            else {
              if (local_118 != (int *)0x0) {
                *local_118 = local_124;
              }
              local_118 = local_118 + 1;
            }
          }
          local_124 = local_124 + 1;
          piVar13 = piVar13 + 0xcd;
        } while (local_124 < *piVar16);
      }
      iVar8 = (int)local_118 - (int)local_11c >> 2;
      param_1[200] = iVar8;
      if (iVar8 != 0) {
        pvVar5 = operator_new(iVar8 << 2);
        param_1[0xc9] = (int)pvVar5;
      }
      puVar11 = local_11c;
      puVar7 = (undefined4 *)param_1[0xc9];
      for (uVar9 = param_1[200] & 0x3fffffff; uVar9 != 0; uVar9 = uVar9 - 1) {
        *puVar7 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar7 = puVar7 + 1;
      }
      for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined1 *)puVar7 = *(undefined1 *)puVar11;
        puVar11 = (undefined4 *)((int)puVar11 + 1);
        puVar7 = (undefined4 *)((int)puVar7 + 1);
      }
      iVar8 = param_1[8];
      local_120 = operator_new(iVar8 * 0x2f0 + 4);
      local_4._0_1_ = 2;
      if (local_120 == (int *)0x0) {
        piVar16 = (int *)0x0;
      }
      else {
        piVar16 = local_120 + 1;
        *local_120 = iVar8;
        FUN_0050ac61(piVar16,0x2f0,iVar8,FUN_00572130,FUN_005722c0);
      }
      local_4 = CONCAT31(local_4._1_3_,1);
      param_1[0xd5] = (int)piVar16;
      if (piVar16 == (int *)0x0) {
        iVar3 = (int)local_114 - (int)local_11c >> 2;
        if (iVar3 != 0) {
          uVar9 = iVar3 * 4;
          if (0x80 < uVar9) {
            FUN_005089fd(local_11c);
            ExceptionList = local_c;
            return 0;
          }
          local_110 = (undefined4 *)(&DAT_005d59a4 + (uVar9 + 7 >> 3) * 4);
          local_120 = local_11c;
          LVar6 = InterlockedExchange(&DAT_005d59e8,1);
          uVar9 = DAT_005c4248;
          if (LVar6 != 0) {
            uVar14 = 0;
            if (DAT_005c4248 != 0) {
              uVar12 = DAT_005d59ec >> 1;
              do {
                if (((uVar12 <= uVar14) && (DAT_005d59e8 == 0)) &&
                   (LVar6 = InterlockedExchange(&DAT_005d59e8,1), LVar6 == 0)) {
                  DAT_005c4248 = 1000;
                  DAT_005d59ec = uVar14;
                  goto LAB_00556df4;
                }
                uVar14 = uVar14 + 1;
              } while (uVar14 < uVar9);
            }
            DAT_005c4248 = 0x1e;
            iVar3 = 6;
            while( true ) {
              iVar8 = iVar3;
              if (0x1b < iVar3) {
                iVar8 = 0x1b;
              }
              LVar6 = InterlockedExchange(&DAT_005d59e8,1);
              if (LVar6 == 0) break;
              if (iVar8 < 0x15) {
                Sleep(0);
                iVar3 = iVar3 + 1;
              }
              else {
                Sleep(1 << ((char)iVar8 - 0x14U & 0x1f));
                iVar3 = iVar3 + 1;
              }
            }
          }
LAB_00556df4:
          *local_120 = *local_110;
          *local_110 = local_120;
          DAT_005d59e8 = 0;
        }
        uVar4 = 0;
      }
      else {
        param_1[9] = -1;
        param_1[0xe1] = 0;
        local_124 = 0;
        if (0 < param_1[8]) {
          piVar16 = piVar16 + 8;
          do {
            piVar16[3] = local_124;
            *piVar16 = (int)param_1;
            FUN_005567d0(iVar3,piVar16 + -8);
            local_124 = local_124 + 1;
            piVar16 = piVar16 + 0xbc;
          } while (local_124 < param_1[8]);
        }
        if (param_1[7] != 0) {
          param_1[0x176] = 0;
          FUN_00557260(param_1[0xd4],0);
          iVar8 = param_1[0xd4];
          iVar10 = 5;
          bVar19 = true;
          pcVar1 = (char *)(iVar8 + 0x10);
          pcVar15 = pcVar1;
          pcVar17 = (char *)&DAT_005c44b8;
          do {
            if (iVar10 == 0) break;
            iVar10 = iVar10 + -1;
            bVar19 = *pcVar15 == *pcVar17;
            pcVar15 = pcVar15 + 1;
            pcVar17 = pcVar17 + 1;
          } while (bVar19);
          if ((!bVar19) && (iVar10 = FUN_005569b0(pcVar1), -1 < iVar10)) {
            *(int *)(iVar8 + 0x24) = iVar10 * 0x2f0 + param_1[0xd5];
          }
        }
        (**(code **)(*param_1 + 0x14))(0xffffffff);
        local_124 = 0;
        if (0 < param_1[7]) {
          puVar11 = (undefined4 *)(param_1[0xd4] + 0x204);
          do {
            puVar7 = (undefined4 *)FUN_00477ad0(auStack_10c);
            puVar18 = puVar11;
            for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
              *puVar18 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar18 = puVar18 + 1;
            }
            puVar7 = (undefined4 *)FUN_00476f00(auStack_cc,puVar11,puVar11 + -0x20);
            puVar18 = puVar11 + 0x10;
            for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
              *puVar18 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar18 = puVar18 + 1;
            }
            local_124 = local_124 + 1;
            puVar11 = puVar11 + 0xcd;
          } while (local_124 < param_1[7]);
        }
        param_1[0x10] = 1;
        if (param_1[0x11] != 0) {
          FUN_00558600();
        }
        iVar8 = FUN_00556910(s_bau_Head_005d12c4);
        param_1[0x174] = iVar8;
        iVar8 = FUN_00556910(s_bau_Spine_005d12b8);
        param_1[0x175] = iVar8;
        FUN_00509e57(iVar3);
        iVar3 = (int)local_114 - (int)local_11c >> 2;
        if (iVar3 != 0) {
          uVar9 = iVar3 * 4;
          if (uVar9 < 0x81) {
            local_120 = (int *)(&DAT_005d59a4 + (uVar9 + 7 >> 3) * 4);
            local_110 = local_11c;
            LVar6 = InterlockedExchange(&DAT_005d59e8,1);
            uVar9 = DAT_005c4248;
            if (LVar6 != 0) {
              uVar14 = 0;
              if (DAT_005c4248 != 0) {
                uVar12 = DAT_005d59ec >> 1;
                do {
                  if (((uVar12 <= uVar14) && (DAT_005d59e8 == 0)) &&
                     (LVar6 = InterlockedExchange(&DAT_005d59e8,1), LVar6 == 0)) {
                    DAT_005c4248 = 1000;
                    DAT_005d59ec = uVar14;
                    goto LAB_005570a2;
                  }
                  uVar14 = uVar14 + 1;
                } while (uVar14 < uVar9);
              }
              DAT_005c4248 = 0x1e;
              iVar3 = 6;
              while( true ) {
                iVar8 = iVar3;
                if (0x1b < iVar3) {
                  iVar8 = 0x1b;
                }
                LVar6 = InterlockedExchange(&DAT_005d59e8,1);
                if (LVar6 == 0) break;
                if (iVar8 < 0x15) {
                  Sleep(0);
                  iVar3 = iVar3 + 1;
                }
                else {
                  Sleep(1 << ((char)iVar8 - 0x14U & 0x1f));
                  iVar3 = iVar3 + 1;
                }
              }
            }
LAB_005570a2:
            *local_110 = *local_120;
            *local_120 = (int)local_110;
            DAT_005d59e8 = 0;
          }
          else {
            FUN_005089fd(local_11c);
          }
        }
        uVar4 = 1;
      }
    }
  }
  ExceptionList = local_c;
  return uVar4;
}

