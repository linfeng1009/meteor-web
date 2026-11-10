/* Original Meteor.exe static export @ 00406960; original sample not executed. */
/* XREF 00406667 UNCONDITIONAL_CALL */
/* XREF 0040670f UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00406960(float *param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
                 int param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  undefined4 *puVar14;
  float *pfVar15;
  int local_8;
  
  uVar7 = param_3 / param_6;
  puVar8 = _malloc(uVar7 * 4);
  if (0 < param_6) {
    local_8 = param_6;
    iVar13 = (int)param_1;
    do {
      puVar14 = puVar8;
      for (uVar9 = uVar7 & 0x3fffffff; uVar9 != 0; uVar9 = uVar9 - 1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      for (iVar10 = 0; iVar10 != 0; iVar10 = iVar10 + -1) {
        *(undefined1 *)puVar14 = 0;
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      param_3 = 0;
      if (0 < (int)uVar7) {
        pfVar15 = (float *)(iVar13 + 4);
        param_1 = (float *)(iVar13 + 0x10);
        pfVar11 = (float *)(iVar13 + 8 + param_5 * 4);
        do {
          if (puVar8[param_3] == 0) {
            fVar1 = pfVar15[2];
            fVar2 = pfVar15[3];
            fVar3 = pfVar15[4];
            iVar10 = param_3 + 1;
            param_6 = 1;
            puVar8[param_3] = 1;
            pfVar12 = pfVar11;
            pfVar5 = param_1;
            iVar6 = param_3;
            if (iVar10 < (int)uVar7) {
              do {
                if (puVar8[iVar10] == 0) {
                  fVar4 = pfVar15[-1] - pfVar12[-2];
                  if (fVar4 <= _DAT_005a83e4) {
                    fVar4 = -fVar4;
                  }
                  if (fVar4 < _DAT_005a8410) {
                    fVar4 = *pfVar15 - pfVar12[-1];
                    if (fVar4 <= _DAT_005a83e4) {
                      fVar4 = -fVar4;
                    }
                    if (fVar4 < _DAT_005a8410) {
                      fVar4 = pfVar15[1] - *pfVar12;
                      if (fVar4 <= _DAT_005a83e4) {
                        fVar4 = -fVar4;
                      }
                      if (fVar4 < _DAT_005a8410) {
                        fVar1 = fVar1 + pfVar12[1];
                        fVar2 = fVar2 + pfVar12[2];
                        fVar3 = fVar3 + pfVar12[3];
                        param_6 = param_6 + 1;
                        puVar8[iVar10] = 1;
                      }
                    }
                  }
                }
                iVar10 = iVar10 + 1;
                pfVar12 = pfVar12 + param_5;
              } while (iVar10 < (int)uVar7);
              if (1 < param_6) {
                fVar4 = _DAT_005a83f4 / (float)param_6;
                fVar1 = fVar4 * fVar1;
                fVar2 = fVar4 * fVar2;
                fVar3 = fVar4 * fVar3;
              }
            }
            for (; iVar6 < (int)uVar7; iVar6 = iVar6 + 1) {
              if (puVar8[iVar6] == 1) {
                puVar8[iVar6] = 2;
                pfVar5[-1] = fVar1;
                *pfVar5 = fVar2;
                pfVar5[1] = fVar3;
              }
              pfVar5 = pfVar5 + param_5;
            }
          }
          pfVar15 = pfVar15 + param_5;
          param_3 = param_3 + 1;
          pfVar11 = pfVar11 + param_5;
          param_1 = param_1 + param_5;
        } while (param_3 < (int)uVar7);
      }
      iVar13 = iVar13 + uVar7 * param_5 * 4;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
  }
  FUN_005089fd(puVar8);
  return;
}

