/* Original Meteor.exe static export @ 00406b70; original sample not executed. */
/* XREF 004a7330 UNCONDITIONAL_CALL */
/* XREF 004a744f UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00406b70(undefined4 param_1)

{
  float fVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  void *pvVar9;
  float *pfVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  
  if (((DAT_005d5a00 != 0) && (iVar8 = FUN_00410a70(param_1), iVar8 != 0)) &&
     (*(int *)(iVar8 + 4) == 6)) {
    puVar2 = *(undefined4 **)(iVar8 + 0xa0);
    iVar8 = *(int *)(iVar8 + 0x9c);
    if (puVar2[0xd] == 0) {
      pvVar9 = _malloc(*(int *)(iVar8 + 0x2c) * 0x24);
      puVar2[0xd] = pvVar9;
    }
    iVar5 = DAT_007eac64;
    if (*(int *)(iVar8 + 0x18) == 0) {
      puVar2[2] = 0;
      puVar2[1] = 0;
      *puVar2 = 0;
      puVar2[4] = 0xbf800000;
      puVar2[5] = 0x3f800000;
      puVar2[6] = 0xbf800000;
      puVar2[7] = 0x3f800000;
      puVar2[8] = 0xbf800000;
      puVar2[9] = 0x3f800000;
      return;
    }
    iVar13 = 0;
    pfVar10 = (float *)puVar2[0xd];
    if (0 < *(int *)(iVar8 + 0x2c)) {
      do {
        iVar12 = 0;
        iVar3 = *(int *)(iVar8 + 0x20);
        iVar4 = *(int *)(iVar8 + 0x18);
        pfVar10[2] = 0.0;
        pfVar10[1] = 0.0;
        pfVar11 = (float *)(iVar3 + iVar13 * iVar5 * iVar4 * 4);
        pfVar10[7] = 1e+10;
        pfVar10[5] = 1e+10;
        pfVar10[3] = 1e+10;
        *pfVar10 = 0.0;
        pfVar10[8] = -1e+10;
        pfVar10[6] = -1e+10;
        pfVar10[4] = -1e+10;
        if (0 < *(int *)(iVar8 + 0x18)) {
          do {
            *pfVar10 = *pfVar10 + *pfVar11;
            pfVar10[1] = pfVar11[1] + pfVar10[1];
            pfVar10[2] = pfVar10[2] + pfVar11[2];
            if (*pfVar11 <= pfVar10[3]) {
              fVar1 = *pfVar11;
            }
            else {
              fVar1 = pfVar10[3];
            }
            pfVar10[3] = fVar1;
            if (*pfVar11 <= pfVar10[4]) {
              fVar1 = pfVar10[4];
            }
            else {
              fVar1 = *pfVar11;
            }
            pfVar10[4] = fVar1;
            if (pfVar11[1] <= pfVar10[5]) {
              fVar1 = pfVar11[1];
            }
            else {
              fVar1 = pfVar10[5];
            }
            pfVar10[5] = fVar1;
            if (pfVar11[1] <= pfVar10[6]) {
              fVar1 = pfVar10[6];
            }
            else {
              fVar1 = pfVar11[1];
            }
            pfVar10[6] = fVar1;
            if (pfVar11[2] <= pfVar10[7]) {
              fVar1 = pfVar11[2];
            }
            else {
              fVar1 = pfVar10[7];
            }
            pfVar10[7] = fVar1;
            if (pfVar11[2] <= pfVar10[8]) {
              fVar1 = pfVar10[8];
            }
            else {
              fVar1 = pfVar11[2];
            }
            pfVar10[8] = fVar1;
            pfVar11 = pfVar11 + iVar5;
            iVar12 = iVar12 + 1;
          } while (iVar12 < *(int *)(iVar8 + 0x18));
        }
        iVar13 = iVar13 + 1;
        *pfVar10 = *pfVar10 / (float)*(int *)(iVar8 + 0x18);
        pfVar10[1] = pfVar10[1] / (float)*(int *)(iVar8 + 0x18);
        pfVar10[2] = pfVar10[2] / (float)*(int *)(iVar8 + 0x18);
        pfVar10 = pfVar10 + 9;
      } while (iVar13 < *(int *)(iVar8 + 0x2c));
    }
    iVar5 = puVar2[0xd];
    *puVar2 = *(undefined4 *)(iVar5 + *(int *)(iVar8 + 0x28) * 0x24);
    puVar2[1] = *(undefined4 *)(iVar5 + 4 + *(int *)(iVar8 + 0x28) * 0x24);
    puVar2[2] = *(undefined4 *)(iVar5 + 8 + *(int *)(iVar8 + 0x28) * 0x24);
    puVar2[4] = *(undefined4 *)(iVar5 + 0xc + *(int *)(iVar8 + 0x28) * 0x24);
    puVar2[5] = *(undefined4 *)(iVar5 + 0x10 + *(int *)(iVar8 + 0x28) * 0x24);
    puVar2[6] = *(undefined4 *)(iVar5 + 0x14 + *(int *)(iVar8 + 0x28) * 0x24);
    puVar2[7] = *(undefined4 *)(iVar5 + 0x18 + *(int *)(iVar8 + 0x28) * 0x24);
    puVar2[8] = *(undefined4 *)(iVar5 + 0x1c + *(int *)(iVar8 + 0x28) * 0x24);
    fVar1 = *(float *)(iVar5 + 0x20 + *(int *)(iVar8 + 0x28) * 0x24);
    puVar2[9] = fVar1;
    fVar6 = (float)puVar2[7] - (float)puVar2[6];
    fVar1 = fVar1 - (float)puVar2[8];
    fVar7 = fVar1;
    if (fVar1 < fVar6) {
      fVar7 = fVar6;
    }
    if (fVar7 < (float)puVar2[5] - (float)puVar2[4]) {
      fVar1 = ((float)puVar2[5] - (float)puVar2[4]) * _DAT_005a83e8;
      puVar2[3] = fVar1 * fVar1;
      return;
    }
    if (fVar1 < fVar6) {
      fVar1 = fVar6;
    }
    puVar2[3] = fVar1 * _DAT_005a83e8 * fVar1 * _DAT_005a83e8;
  }
  return;
}

