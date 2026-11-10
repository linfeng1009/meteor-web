/* Original Meteor.exe static export @ 00558600; original sample not executed. */
/* XREF 00556f3e UNCONDITIONAL_CALL */
/* XREF 005571d6 UNCONDITIONAL_CALL */
/* XREF 00557e6b UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __fastcall FUN_00558600(int param_1)

{
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  int *piVar10;
  float *pfVar11;
  int iVar12;
  float *pfVar13;
  int local_80;
  undefined1 local_c [12];
  
  iVar7 = 0;
  iVar12 = *(int *)(param_1 + 0x380);
  if (iVar12 == 0) {
    return iVar7;
  }
  if (*(int *)(param_1 + 0x350) != 0) {
    iVar9 = 0;
    if (0 < *(int *)(param_1 + 0x1c)) {
      do {
        iVar2 = *(int *)(param_1 + 0x350);
        *(undefined4 *)(iVar7 + 0x50 + iVar2) = 0x501502f9;
        *(undefined4 *)(iVar7 + 0x4c + iVar2) = 0x501502f9;
        *(undefined4 *)(iVar7 + 0x48 + iVar2) = 0x501502f9;
        iVar9 = iVar9 + 1;
        iVar2 = *(int *)(param_1 + 0x350);
        *(undefined4 *)(iVar7 + 0x5c + iVar2) = 0xd01502f9;
        *(undefined4 *)(iVar7 + 0x58 + iVar2) = 0xd01502f9;
        *(undefined4 *)(iVar7 + 0x54 + iVar2) = 0xd01502f9;
        *(undefined4 *)(iVar7 + 0x2c + *(int *)(param_1 + 0x350)) = 0;
        iVar7 = iVar7 + 0x334;
      } while (iVar9 < *(int *)(param_1 + 0x1c));
    }
    local_80 = 0;
    if (0 < *(int *)(param_1 + 4)) {
      piVar10 = (int *)(iVar12 + 0x10);
      do {
        pfVar11 = (float *)piVar10[4];
        iVar12 = 0;
        if (0 < *piVar10) {
          do {
            iVar7 = 0;
            if (0 < (int)pfVar11[8]) {
              do {
                if ((iVar7 == 0) || (_DAT_005a83f0 < *(float *)((int)pfVar11[10] + iVar7 * 4))) {
                  iVar9 = *(int *)((int)pfVar11[9] + iVar7 * 4);
                  fVar1 = *(float *)(*(int *)(param_1 + 0x350) + 0x54 + iVar9 * 0x334);
                  iVar9 = *(int *)(param_1 + 0x350) + iVar9 * 0x334;
                  *(undefined4 *)(iVar9 + 0x2c) = 1;
                  if (fVar1 < *pfVar11) {
                    *(float *)(iVar9 + 0x54) = *pfVar11;
                  }
                  if (*pfVar11 < *(float *)(iVar9 + 0x48)) {
                    *(float *)(iVar9 + 0x48) = *pfVar11;
                  }
                  if (*(float *)(iVar9 + 0x58) < pfVar11[1]) {
                    *(float *)(iVar9 + 0x58) = pfVar11[1];
                  }
                  if (pfVar11[1] < *(float *)(iVar9 + 0x4c)) {
                    *(float *)(iVar9 + 0x4c) = pfVar11[1];
                  }
                  if (*(float *)(iVar9 + 0x5c) < pfVar11[2]) {
                    *(float *)(iVar9 + 0x5c) = pfVar11[2];
                  }
                  if (pfVar11[2] < *(float *)(iVar9 + 0x50)) {
                    *(float *)(iVar9 + 0x50) = pfVar11[2];
                  }
                }
                iVar7 = iVar7 + 1;
              } while (iVar7 < (int)pfVar11[8]);
            }
            iVar12 = iVar12 + 1;
            pfVar11 = pfVar11 + 0xb;
          } while (iVar12 < *piVar10);
        }
        local_80 = local_80 + 1;
        piVar10 = piVar10 + 0xf;
      } while (local_80 < *(int *)(param_1 + 4));
    }
    local_80 = 0;
    if (0 < *(int *)(param_1 + 0x1c)) {
      pfVar11 = (float *)(*(int *)(param_1 + 0x350) + 0x94);
      do {
        if (pfVar11[-0x1a] == 0.0) {
          pfVar11[-0xb] = 0.0;
          pfVar11[-0xc] = 0.0;
          pfVar11[-0xd] = 0.0;
          pfVar11[-8] = 0.0;
          pfVar11[-9] = 0.0;
          pfVar11[-10] = 0.0;
          pfVar11[-0xe] = 0.0;
          pfVar11[-0xf] = 0.0;
          pfVar11[-0x10] = 0.0;
          pfVar11[-0x11] = 0.0;
          pfVar11[-0x12] = 0.0;
          pfVar11[-0x13] = 0.0;
          pfVar13 = pfVar11 + -4;
          for (iVar12 = 0x18; iVar12 != 0; iVar12 = iVar12 + -1) {
            *pfVar13 = 0.0;
            pfVar13 = pfVar13 + 1;
          }
          pfVar13 = pfVar11 + 0x24;
          for (iVar12 = 0x18; iVar12 != 0; iVar12 = iVar12 + -1) {
            *pfVar13 = 0.0;
            pfVar13 = pfVar13 + 1;
          }
        }
        else {
          fVar1 = pfVar11[-0x10] - pfVar11[-0x13];
          pfVar13 = pfVar11 + -0x13;
          fVar3 = pfVar11[-0xf] - pfVar11[-0x12];
          fVar4 = pfVar11[-0xe] - pfVar11[-0x11];
          pfVar11[-0xd] = fVar1;
          pfVar11[-0xc] = fVar3;
          fVar5 = fVar1 * _DAT_005a83e8;
          pfVar11[-0xb] = fVar4;
          fVar6 = fVar3 * _DAT_005a83e8;
          pfVar11[-10] = fVar5;
          fVar5 = fVar4 * _DAT_005a83e8;
          pfVar11[-9] = fVar6;
          pfVar11[-8] = fVar5;
          pfVar11[-4] = *pfVar13;
          pfVar11[-3] = pfVar11[-0x12];
          pfVar11[-2] = pfVar11[-0x11];
          pfVar8 = pfVar11 + -1;
          *pfVar8 = fVar1 + *pfVar13;
          *pfVar11 = pfVar11[-0x12];
          pfVar11[1] = pfVar11[-0x11];
          pfVar11[2] = *pfVar8;
          pfVar11[3] = *pfVar11;
          pfVar11[4] = fVar4 + pfVar11[1];
          pfVar11[5] = *pfVar13;
          pfVar11[6] = pfVar11[-0x12];
          pfVar11[7] = fVar4 + pfVar11[-0x11];
          pfVar11[8] = pfVar11[-4];
          pfVar11[9] = fVar3 + pfVar11[-3];
          pfVar11[10] = pfVar11[-2];
          iVar12 = 8;
          pfVar11[0xb] = *pfVar8;
          pfVar11[0xc] = fVar3 + *pfVar11;
          pfVar11[0xd] = pfVar11[1];
          pfVar11[0xe] = pfVar11[2];
          pfVar11[0xf] = fVar3 + pfVar11[3];
          pfVar11[0x10] = pfVar11[4];
          pfVar11[0x11] = pfVar11[5];
          pfVar11[0x12] = fVar3 + pfVar11[6];
          pfVar11[0x13] = pfVar11[7];
          pfVar13 = pfVar11 + 0x24;
          do {
            pfVar8 = (float *)FUN_00476e80(local_c,pfVar13 + -0x28,pfVar11 + 0x5c);
            *pfVar13 = *pfVar8;
            iVar12 = iVar12 + -1;
            pfVar13[1] = pfVar8[1];
            pfVar13[2] = pfVar8[2];
            pfVar13 = pfVar13 + 3;
          } while (iVar12 != 0);
        }
        local_80 = local_80 + 1;
        pfVar11 = pfVar11 + 0xcd;
      } while (local_80 < *(int *)(param_1 + 0x1c));
    }
    return 1;
  }
  return 0;
}

