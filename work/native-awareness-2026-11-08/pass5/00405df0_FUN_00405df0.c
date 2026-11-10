/* Original Meteor.exe static export @ 00405df0; original sample not executed. */
/* XREF 00404ebc UNCONDITIONAL_CALL */
/* XREF 00404b08 UNCONDITIONAL_CALL */
/* XREF 004e98a9 UNCONDITIONAL_CALL */
/* XREF 004eaf6e UNCONDITIONAL_CALL */
/* XREF 004eb716 UNCONDITIONAL_CALL */
/* XREF 004e8ed2 UNCONDITIONAL_CALL */
/* XREF 004e908b UNCONDITIONAL_CALL */
/* XREF 005481f2 UNCONDITIONAL_CALL */
/* XREF 00405027 UNCONDITIONAL_CALL */
/* XREF 004dbeea UNCONDITIONAL_CALL */
/* XREF 0040ba98 UNCONDITIONAL_CALL */
/* XREF 004f58b8 UNCONDITIONAL_CALL */
/* XREF 004f5cce UNCONDITIONAL_CALL */
/* XREF 004f5cde UNCONDITIONAL_CALL */
/* XREF 004f5cf8 UNCONDITIONAL_CALL */
/* XREF 004f727c UNCONDITIONAL_CALL */
/* XREF 0048a2d1 UNCONDITIONAL_CALL */
/* XREF 00547f4e UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00405df0(uint param_1)

{
  float fVar1;
  undefined4 *puVar2;
  int iVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  bool bVar8;
  uint *puVar9;
  float *pfVar10;
  int *piVar11;
  undefined4 uVar12;
  uint uVar13;
  int iVar14;
  float *pfVar15;
  int iVar16;
  int local_810;
  uint local_808;
  int aiStack_800 [512];
  
  iVar3 = DAT_007eac64;
  if (DAT_005d5a00 == 0) {
    return 0;
  }
  if (param_1 == 0) {
    local_808 = 0;
  }
  else if ((param_1 & 0xffffff) < 0x1400) {
    local_808 = (&DAT_007ead80)[param_1 & 0xffffff];
  }
  else {
    local_808 = 0;
  }
  puVar2 = (undefined4 *)DAT_007f1688[0x28];
  if (DAT_007f1688[1] == 5) {
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
    fVar1 = *(float *)(DAT_007f1688[0x27] + 4) * _DAT_005a83e8;
    puVar2[5] = fVar1;
    puVar2[4] = -fVar1;
    fVar1 = *(float *)(DAT_007f1688[0x27] + 8) * _DAT_005a83e8;
    puVar2[7] = fVar1;
    puVar2[6] = -fVar1;
    fVar1 = *(float *)(DAT_007f1688[0x27] + 0xc) * _DAT_005a83e8;
    puVar2[9] = fVar1;
    puVar2[8] = -fVar1;
  }
  else if (DAT_007f1688[1] == 6) {
    uVar13 = DAT_007f1688[0x27];
    pfVar10 = _malloc(*(int *)(uVar13 + 0x2c) * 0x24);
    puVar2[0xd] = pfVar10;
    if (*(int *)(uVar13 + 0x18) < 1) {
      *puVar2 = 0;
      puVar2[8] = 0xbf800000;
      puVar2[6] = 0xbf800000;
      puVar2[4] = 0xbf800000;
      puVar2[1] = 0;
      puVar2[2] = 0;
      puVar2[9] = 0x3f800000;
      puVar2[7] = 0x3f800000;
      puVar2[5] = 0x3f800000;
    }
    else {
      local_810 = 0;
      if (0 < *(int *)(uVar13 + 0x2c)) {
        do {
          pfVar15 = (float *)(*(int *)(uVar13 + 0x20) +
                             *(int *)(uVar13 + 0x18) * local_810 * iVar3 * 4);
          iVar16 = 0;
          pfVar10[2] = 0.0;
          pfVar10[1] = 0.0;
          *pfVar10 = 0.0;
          pfVar10[7] = 1e+10;
          pfVar10[5] = 1e+10;
          pfVar10[3] = 1e+10;
          pfVar10[8] = -1e+10;
          pfVar10[6] = -1e+10;
          pfVar10[4] = -1e+10;
          if (0 < *(int *)(uVar13 + 0x18)) {
            do {
              *pfVar10 = *pfVar10 + *pfVar15;
              pfVar10[1] = pfVar15[1] + pfVar10[1];
              pfVar10[2] = pfVar10[2] + pfVar15[2];
              if (*pfVar15 <= pfVar10[3]) {
                fVar1 = *pfVar15;
              }
              else {
                fVar1 = pfVar10[3];
              }
              pfVar10[3] = fVar1;
              if (*pfVar15 <= pfVar10[4]) {
                fVar1 = pfVar10[4];
              }
              else {
                fVar1 = *pfVar15;
              }
              pfVar10[4] = fVar1;
              if (pfVar15[1] <= pfVar10[5]) {
                fVar1 = pfVar15[1];
              }
              else {
                fVar1 = pfVar10[5];
              }
              pfVar10[5] = fVar1;
              if (pfVar15[1] <= pfVar10[6]) {
                fVar1 = pfVar10[6];
              }
              else {
                fVar1 = pfVar15[1];
              }
              pfVar10[6] = fVar1;
              if (pfVar15[2] <= pfVar10[7]) {
                fVar1 = pfVar15[2];
              }
              else {
                fVar1 = pfVar10[7];
              }
              pfVar10[7] = fVar1;
              if (pfVar15[2] <= pfVar10[8]) {
                fVar1 = pfVar10[8];
              }
              else {
                fVar1 = pfVar15[2];
              }
              pfVar10[8] = fVar1;
              pfVar15 = pfVar15 + iVar3;
              iVar16 = iVar16 + 1;
            } while (iVar16 < *(int *)(uVar13 + 0x18));
          }
          local_810 = local_810 + 1;
          *pfVar10 = *pfVar10 / (float)*(int *)(uVar13 + 0x18);
          pfVar10[1] = pfVar10[1] / (float)*(int *)(uVar13 + 0x18);
          pfVar10[2] = pfVar10[2] / (float)*(int *)(uVar13 + 0x18);
          pfVar10 = pfVar10 + 9;
        } while (local_810 < *(int *)(uVar13 + 0x2c));
      }
      iVar16 = puVar2[0xd];
      *puVar2 = *(undefined4 *)(iVar16 + *(int *)(uVar13 + 0x28) * 0x24);
      puVar2[1] = *(undefined4 *)(iVar16 + 4 + *(int *)(uVar13 + 0x28) * 0x24);
      puVar2[2] = *(undefined4 *)(iVar16 + 8 + *(int *)(uVar13 + 0x28) * 0x24);
      puVar2[4] = *(undefined4 *)(iVar16 + 0xc + *(int *)(uVar13 + 0x28) * 0x24);
      puVar2[5] = *(undefined4 *)(iVar16 + 0x10 + *(int *)(uVar13 + 0x28) * 0x24);
      puVar2[6] = *(undefined4 *)(iVar16 + 0x14 + *(int *)(uVar13 + 0x28) * 0x24);
      puVar2[7] = *(undefined4 *)(iVar16 + 0x18 + *(int *)(uVar13 + 0x28) * 0x24);
      puVar2[8] = *(undefined4 *)(iVar16 + 0x1c + *(int *)(uVar13 + 0x28) * 0x24);
      puVar2[9] = *(undefined4 *)(iVar16 + 0x20 + *(int *)(uVar13 + 0x28) * 0x24);
    }
    local_810 = *(int *)(uVar13 + 0x34);
    piVar11 = *(int **)(uVar13 + 0x40);
    iVar16 = 0;
    bVar4 = false;
    bVar8 = false;
    if (0 < local_810) {
      do {
        iVar14 = 0;
        if (0 < iVar16) {
          do {
            if (piVar11[1] == aiStack_800[iVar14]) break;
            iVar14 = iVar14 + 1;
          } while (iVar14 < iVar16);
        }
        if (iVar14 == iVar16) {
          iVar16 = iVar16 + 1;
          aiStack_800[iVar14] = piVar11[1];
        }
        if (*piVar11 == 1) {
          bVar4 = true;
          piVar11 = piVar11 + DAT_005c4314;
        }
        else if (*piVar11 == 2) {
          bVar8 = true;
          piVar11 = piVar11 + piVar11[2] * 2 + 3;
        }
        local_810 = local_810 + -1;
      } while (local_810 != 0);
      if (bVar8) {
        if (bVar4) {
          *(undefined4 *)(uVar13 + 8) = 2;
        }
        else {
          *(undefined4 *)(uVar13 + 8) = 1;
        }
      }
      else if (bVar4) {
        *(undefined4 *)(uVar13 + 8) = 0;
      }
    }
    iVar14 = *(int *)(uVar13 + 0x18);
    *(int *)(uVar13 + 0xc) = iVar16;
    if ((*(int *)(uVar13 + 0x30) != iVar14) && (iVar14 != 0)) {
      *(int *)(uVar13 + 0x30) = iVar14;
      iVar16 = FUN_005099a7(*(undefined4 *)(uVar13 + 0x20),
                            *(int *)(uVar13 + 0x2c) * iVar14 * iVar3 * 4);
      *(int *)(uVar13 + 0x20) = iVar16;
      *(int *)(uVar13 + 0x1c) =
           iVar16 + *(int *)(uVar13 + 0x28) * *(int *)(uVar13 + 0x18) * iVar3 * 4;
      if (DAT_005c4308 == 0) {
        uVar12 = FUN_005099a7(*(undefined4 *)(uVar13 + 0x48),*(int *)(uVar13 + 0x30) * 2);
        *(undefined4 *)(uVar13 + 0x48) = uVar12;
      }
      else {
        *(undefined4 *)(uVar13 + 0x48) = 0;
      }
    }
    iVar3 = *(int *)(uVar13 + 0x3c);
    if ((*(int *)(uVar13 + 0x44) != iVar3) && (iVar3 != 0)) {
      *(int *)(uVar13 + 0x44) = iVar3;
      uVar12 = FUN_005099a7(*(undefined4 *)(uVar13 + 0x40),iVar3 << 2);
      *(undefined4 *)(uVar13 + 0x40) = uVar12;
    }
  }
  else {
    *puVar2 = 0;
    puVar2[8] = 0xbf800000;
    puVar2[6] = 0xbf800000;
    puVar2[4] = 0xbf800000;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[9] = 0x3f800000;
    puVar2[7] = 0x3f800000;
    puVar2[5] = 0x3f800000;
  }
  fVar5 = (float)puVar2[7] - (float)puVar2[6];
  fVar1 = (float)puVar2[9] - (float)puVar2[8];
  fVar6 = fVar1;
  if (fVar1 < fVar5) {
    fVar6 = fVar5;
  }
  fVar7 = (float)puVar2[5] - (float)puVar2[4];
  if ((fVar7 <= fVar6) && (fVar7 = fVar5, fVar5 <= fVar1)) {
    fVar7 = fVar1;
  }
  puVar2[3] = fVar7 * _DAT_005a83e8 * fVar7 * _DAT_005a83e8;
  if (4 < DAT_007f1688[1]) {
    if ((int)DAT_007f1688[0x46] < 0xff) {
      FUN_0040aee0(DAT_007f1688,0);
    }
    else {
      FUN_0040afd0();
    }
  }
  DAT_007f1688[0x49] = local_808;
  if (local_808 != 0) {
    iVar3 = *(int *)(local_808 + 300);
    if (iVar3 == 0) {
      *(uint **)(local_808 + 300) = DAT_007f1688;
    }
    else {
      for (iVar16 = *(int *)(iVar3 + 0x128); iVar16 != 0; iVar16 = *(int *)(iVar16 + 0x128)) {
        iVar3 = iVar16;
      }
      *(uint **)(iVar3 + 0x128) = DAT_007f1688;
    }
  }
  puVar9 = DAT_007f1688;
  uVar13 = 0;
  if (0 < (int)DAT_007e5bc0) {
    do {
      if ((&DAT_007ead80)[uVar13] == 0) break;
      uVar13 = uVar13 + 1;
    } while ((int)uVar13 < (int)DAT_007e5bc0);
  }
  if (uVar13 == DAT_007e5bc0) {
    if (0x13ff < (int)DAT_007e5bc0) {
      FUN_00410c20(s_No_more_node_available___N01__005c446c);
      return 0;
    }
    DAT_007e5bc0 = DAT_007e5bc0 + 1;
  }
  (&DAT_007ead80)[uVar13] = DAT_007f1688;
  *puVar9 = uVar13;
  puVar9 = DAT_007f1688;
  DAT_007f1688 = (uint *)0x0;
  FUN_00406380(*puVar9 | 0x2000000);
  return *puVar9 | 0x2000000;
}

