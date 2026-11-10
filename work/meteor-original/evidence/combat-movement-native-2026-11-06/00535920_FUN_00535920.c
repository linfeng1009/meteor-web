/* Original Meteor.exe static export @ 00535920; original sample not executed. */
/* XREF 005360da UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_00535920(uint *param_1,uint *param_2,code *param_3,undefined4 param_4,undefined4 param_5)

{
  char cVar1;
  double dVar2;
  double dVar3;
  bool bVar4;
  undefined1 uVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int *piVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  float10 fVar16;
  int local_54;
  undefined8 local_38;
  int local_30;
  undefined8 local_20;
  undefined8 local_18;
  double local_10;
  
  iVar6 = FUN_00530d80();
  if (iVar6 == 0) {
    return 0;
  }
  local_20 = (double)(ulonglong)*param_1;
  local_18 = (double)(longlong)local_20;
  local_20 = (double)(ulonglong)*param_2;
  local_18 = local_18 / (double)(longlong)local_20;
  piVar7 = (int *)FUN_00530dc0(param_1[1],8);
  if (piVar7 == (int *)0x0) {
    FUN_00530db0();
    return 0xffffffff;
  }
  uVar11 = param_1[1];
  local_20 = (double)(ulonglong)uVar11;
  local_54 = 0;
  dVar2 = (double)(longlong)local_20;
  local_20 = (double)(ulonglong)param_2[1];
  local_20 = dVar2 / (double)(longlong)local_20;
  if (_DAT_005a8418 <= local_20) {
    if (0 < (int)uVar11) {
      uVar8 = __ftol();
      piVar12 = piVar7;
      do {
        *piVar12 = 0;
        iVar9 = FUN_00530dc0(uVar8,0x10);
        piVar12[1] = iVar9;
        if (iVar9 == 0) goto LAB_00535d73;
        FUN_00593946((double)local_54 / local_20 - (double)CONCAT44(param_5,param_4));
        fVar16 = (float10)FUN_00593877();
        local_38 = (double)fVar16;
        iVar9 = __ftol();
        if ((double)iVar9 < local_38 != ((double)iVar9 == local_38)) {
          iVar14 = -iVar9;
          do {
            fVar16 = (float10)(*param_3)();
            iVar13 = iVar14;
            if ((-1 < iVar9) && (iVar13 = iVar9, (int)param_2[1] <= iVar9)) {
              iVar13 = (param_2[1] * 2 - iVar9) + -1;
            }
            iVar10 = *piVar12;
            *piVar12 = iVar10 + 1;
            iVar10 = iVar10 * 0x10;
            iVar9 = iVar9 + 1;
            iVar14 = iVar14 + -1;
            *(int *)(iVar10 + piVar12[1]) = iVar13;
            *(double *)(iVar10 + 8 + piVar12[1]) = (double)fVar16;
          } while ((double)iVar9 < local_38 != ((double)iVar9 == local_38));
        }
        local_54 = local_54 + 1;
        piVar12 = piVar12 + 2;
      } while (local_54 < (int)param_1[1]);
    }
  }
  else {
    dVar2 = _DAT_005a8418 / local_20;
    local_20 = (double)CONCAT44(param_5,param_4) * dVar2;
    local_10 = dVar2;
    if (0 < (int)uVar11) {
      uVar8 = __ftol();
      piVar12 = piVar7;
      do {
        *piVar12 = 0;
        iVar9 = FUN_00530dc0(uVar8,0x10);
        piVar12[1] = iVar9;
        if (iVar9 == 0) {
LAB_00535d73:
          FUN_00530db0();
          FUN_00530db0(iVar6);
          return 0xffffffff;
        }
        FUN_00593946((double)local_54 * dVar2 - local_20);
        fVar16 = (float10)FUN_00593877();
        local_38 = (double)fVar16;
        iVar9 = __ftol();
        if ((double)iVar9 < local_38 != ((double)iVar9 == local_38)) {
          dVar3 = _DAT_005a8418 / local_10;
          iVar14 = -iVar9;
          do {
            fVar16 = (float10)(*param_3)();
            iVar13 = iVar14;
            if ((-1 < iVar9) && (iVar13 = iVar9, (int)param_2[1] <= iVar9)) {
              iVar13 = (param_2[1] * 2 - iVar9) + -1;
            }
            iVar10 = *piVar12;
            *piVar12 = iVar10 + 1;
            iVar10 = iVar10 * 0x10;
            iVar9 = iVar9 + 1;
            iVar14 = iVar14 + -1;
            *(int *)(iVar10 + piVar12[1]) = iVar13;
            *(double *)(iVar10 + 8 + piVar12[1]) = (double)(fVar16 * (float10)dVar3);
          } while ((double)iVar9 < local_38 != ((double)iVar9 == local_38));
        }
        local_54 = local_54 + 1;
        piVar12 = piVar12 + 2;
      } while (local_54 < (int)param_1[1]);
    }
  }
  uVar11 = *param_1;
  iVar9 = 0;
  if (0 < (int)uVar11) {
    do {
      iVar14 = FUN_005356f0(&local_20,(undefined4)local_18,local_18._4_4_,param_4,param_5,uVar11,
                            *param_2,param_3,iVar9);
      if (iVar14 != 0) break;
      iVar14 = 0;
      if (0 < (int)param_2[1]) {
        do {
          bVar4 = false;
          if (0 < (int)local_20) {
            local_30 = (int)local_20;
            piVar12 = local_20._4_4_;
            do {
              cVar1 = *(char *)(*piVar12 * (uint)(byte)param_2[3] + param_2[5] + param_2[4] * iVar14
                               + DAT_007dc820);
              local_38 = (double)CONCAT71(local_38._1_7_,cVar1);
              if (cVar1 != *(char *)(*local_20._4_4_ * (uint)(byte)param_2[3] + param_2[5] +
                                     param_2[4] * iVar14 + DAT_007dc820)) {
                bVar4 = true;
              }
              piVar12 = piVar12 + 4;
              local_30 = local_30 + -1;
            } while (local_30 != 0);
            if (bVar4) {
              __ftol();
            }
          }
          uVar5 = __ftol();
          *(undefined1 *)(iVar14 + iVar6) = uVar5;
          iVar14 = iVar14 + 1;
        } while (iVar14 < (int)param_2[1]);
      }
      FUN_00530db0();
      iVar14 = 0;
      if (0 < (int)param_1[1]) {
        do {
          piVar12 = (int *)piVar7[iVar14 * 2 + 1];
          iVar13 = piVar7[iVar14 * 2];
          iVar10 = *piVar12;
          bVar4 = false;
          if (0 < iVar13) {
            do {
              local_38 = (double)CONCAT71(local_38._1_7_,*(char *)(iVar6 + *piVar12));
              if (*(char *)(iVar6 + *piVar12) != *(char *)(iVar6 + iVar10)) {
                bVar4 = true;
              }
              piVar12 = piVar12 + 4;
              iVar13 = iVar13 + -1;
            } while (iVar13 != 0);
            if (bVar4) {
              __ftol();
            }
          }
          uVar5 = __ftol();
          iVar13 = param_1[4] * iVar14;
          iVar14 = iVar14 + 1;
          *(undefined1 *)((uint)(byte)param_1[3] * iVar9 + iVar13 + param_1[5] + DAT_007dc820) =
               uVar5;
        } while (iVar14 < (int)param_1[1]);
      }
      iVar9 = iVar9 + 1;
      uVar11 = *param_1;
    } while (iVar9 < (int)uVar11);
  }
  FUN_00530db0();
  iVar9 = 0;
  if (0 < (int)param_1[1]) {
    puVar15 = (undefined4 *)(iVar6 + 4);
    do {
      FUN_00530db0(*puVar15);
      iVar9 = iVar9 + 1;
      puVar15 = puVar15 + 2;
    } while (iVar9 < (int)param_1[1]);
  }
  FUN_00530db0(iVar6);
  return local_38._4_4_;
}

