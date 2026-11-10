/* Original Meteor.exe static export @ 005706c0; original sample not executed. */
/* XREF 005706a6 UNCONDITIONAL_CALL */

float * FUN_005706c0(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                    int param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float *pfVar12;
  float *pfVar13;
  undefined2 uVar15;
  float *pfVar14;
  float *pfVar16;
  float *pfVar17;
  int iVar18;
  int iVar19;
  float local_30 [12];
  
  fVar1 = *param_5 - *param_2;
  fVar3 = param_5[1] - param_2[1];
  fVar2 = param_5[2] - param_2[2];
  pfVar16 = local_30 + 3;
  pfVar14 = param_3 + 1;
  iVar18 = 3;
  local_30[0] = fVar1 * *param_3 + fVar3 * *pfVar14 + fVar2 * param_3[2];
  local_30[1] = fVar1 * param_3[3] + fVar3 * param_3[4] + fVar2 * param_3[5];
  local_30[2] = fVar1 * param_3[6] + fVar3 * param_3[7] + fVar2 * param_3[8];
  do {
    iVar19 = 3;
    pfVar12 = (float *)(param_6 + 4);
    pfVar17 = pfVar16;
    do {
      pfVar16 = pfVar17 + 1;
      pfVar13 = pfVar12 + 3;
      iVar19 = iVar19 + -1;
      *pfVar17 = *pfVar14 * *pfVar12 + pfVar12[1] * pfVar14[1] + pfVar12[-1] * pfVar14[-1];
      pfVar12 = pfVar13;
      pfVar17 = pfVar16;
    } while (iVar19 != 0);
    pfVar14 = pfVar14 + 3;
    iVar18 = iVar18 + -1;
  } while (iVar18 != 0);
  iVar18 = 0;
  pfVar14 = local_30 + 4;
  pfVar16 = param_1;
  do {
    fVar1 = ABS(*(float *)((int)pfVar16 + ((int)local_30 - (int)param_1)));
    fVar2 = *pfVar16 +
            ABS(*pfVar14) * param_4[1] + ABS(pfVar14[-1]) * *param_4 + ABS(pfVar14[1]) * param_4[2];
    pfVar13 = (float *)CONCAT22((short)((uint)pfVar13 >> 0x10),
                                (ushort)(fVar2 < fVar1) << 8 |
                                (ushort)(NAN(fVar2) || NAN(fVar1)) << 10 |
                                (ushort)(fVar2 == fVar1) << 0xe);
    if (fVar2 < fVar1) {
      return pfVar13;
    }
    iVar18 = iVar18 + 1;
    pfVar14 = pfVar14 + 3;
    pfVar16 = pfVar16 + 1;
  } while (iVar18 < 3);
  iVar18 = 0;
  do {
    iVar19 = (int)param_4 + (iVar18 * 4 - (int)(local_30 + 6));
    fVar1 = ABS(local_30[0] * local_30[iVar18 + 3] +
                local_30[1] * local_30[iVar18 + 6] + local_30[2] * local_30[iVar18 + 9]);
    fVar2 = *(float *)((int)local_30 + iVar19 + 0x18) +
            ABS(local_30[iVar18 + 3]) * *param_1 +
            ABS(local_30[iVar18 + 9]) * param_1[2] + ABS(local_30[iVar18 + 6]) * param_1[1];
    uVar15 = (undefined2)((uint)iVar19 >> 0x10);
    if (fVar2 < fVar1) {
      return (float *)CONCAT22(uVar15,(ushort)(fVar2 < fVar1) << 8 |
                                      (ushort)(NAN(fVar2) || NAN(fVar1)) << 10 |
                                      (ushort)(fVar2 == fVar1) << 0xe);
    }
    iVar18 = iVar18 + 1;
  } while (iVar18 < 3);
  fVar1 = ABS(local_30[6]);
  fVar2 = ABS(local_30[9]);
  fVar3 = ABS(local_30[4]);
  fVar4 = ABS(local_30[5]);
  fVar5 = ABS(local_30[2] * local_30[6] - local_30[1] * local_30[9]);
  fVar6 = param_4[2] * fVar3 + param_4[1] * fVar4 + param_1[1] * fVar2 + param_1[2] * fVar1;
  if (fVar6 < fVar5) {
    return (float *)CONCAT22(uVar15,(ushort)(fVar6 < fVar5) << 8 |
                                    (ushort)(NAN(fVar6) || NAN(fVar5)) << 10 |
                                    (ushort)(fVar6 == fVar5) << 0xe);
  }
  fVar5 = ABS(local_30[7]);
  fVar6 = ABS(local_30[10]);
  fVar7 = ABS(local_30[3]);
  fVar8 = ABS(local_30[2] * local_30[7] - local_30[1] * local_30[10]);
  fVar9 = param_4[2] * fVar7 + *param_4 * fVar4 + param_1[1] * fVar6 + param_1[2] * fVar5;
  if (fVar9 < fVar8) {
    return (float *)CONCAT22(uVar15,(ushort)(fVar9 < fVar8) << 8 |
                                    (ushort)(NAN(fVar9) || NAN(fVar8)) << 10 |
                                    (ushort)(fVar9 == fVar8) << 0xe);
  }
  fVar8 = ABS(local_30[8]);
  fVar9 = ABS(local_30[0xb]);
  fVar11 = ABS(local_30[2] * local_30[8] - local_30[1] * local_30[0xb]);
  fVar10 = param_1[2] * fVar8 + param_1[1] * fVar9 + *param_4 * fVar3 + param_4[1] * fVar7;
  if (fVar10 < fVar11) {
    return (float *)CONCAT22(uVar15,(ushort)(fVar10 < fVar11) << 8 |
                                    (ushort)(NAN(fVar10) || NAN(fVar11)) << 10 |
                                    (ushort)(fVar10 == fVar11) << 0xe);
  }
  fVar10 = ABS(local_30[0] * local_30[9] - local_30[2] * local_30[3]);
  fVar11 = param_4[2] * fVar5 + param_4[1] * fVar8 + *param_1 * fVar2 + param_1[2] * fVar7;
  if (fVar11 < fVar10) {
    return (float *)CONCAT22(uVar15,(ushort)(fVar11 < fVar10) << 8 |
                                    (ushort)(NAN(fVar11) || NAN(fVar10)) << 10 |
                                    (ushort)(fVar11 == fVar10) << 0xe);
  }
  fVar10 = ABS(local_30[0] * local_30[10] - local_30[2] * local_30[4]);
  fVar11 = param_1[2] * fVar3 + *param_1 * fVar6 + param_4[2] * fVar1 + *param_4 * fVar8;
  if (fVar11 < fVar10) {
    return (float *)CONCAT22(uVar15,(ushort)(fVar11 < fVar10) << 8 |
                                    (ushort)(NAN(fVar11) || NAN(fVar10)) << 10 |
                                    (ushort)(fVar11 == fVar10) << 0xe);
  }
  fVar11 = ABS(local_30[0] * local_30[0xb] - local_30[2] * local_30[5]);
  fVar10 = *param_4 * fVar5 + param_4[1] * fVar1 + *param_1 * fVar9 + param_1[2] * fVar4;
  if (fVar10 < fVar11) {
    return (float *)CONCAT22(uVar15,(ushort)(fVar10 < fVar11) << 8 |
                                    (ushort)(NAN(fVar10) || NAN(fVar11)) << 10 |
                                    (ushort)(fVar10 == fVar11) << 0xe);
  }
  fVar10 = ABS(local_30[1] * local_30[3] - local_30[0] * local_30[6]);
  fVar1 = param_4[2] * fVar6 + param_4[1] * fVar9 + param_1[1] * fVar7 + *param_1 * fVar1;
  if (fVar1 >= fVar10) {
    fVar7 = ABS(local_30[1] * local_30[4] - local_30[0] * local_30[7]);
    fVar1 = param_1[1] * fVar3 + *param_1 * fVar5 + param_4[2] * fVar2 + *param_4 * fVar9;
    if (fVar1 < fVar7) {
      return (float *)CONCAT22(uVar15,(ushort)(fVar1 < fVar7) << 8 |
                                      (ushort)(NAN(fVar1) || NAN(fVar7)) << 10 |
                                      (ushort)(fVar1 == fVar7) << 0xe);
    }
    fVar1 = ABS(local_30[1] * local_30[5] - local_30[0] * local_30[8]);
    fVar2 = *param_1 * fVar8 + param_1[1] * fVar4 + *param_4 * fVar6 + param_4[1] * fVar2;
    pfVar14 = (float *)CONCAT22(uVar15,(ushort)(fVar2 < fVar1) << 8 |
                                       (ushort)(NAN(fVar2) || NAN(fVar1)) << 10 |
                                       (ushort)(fVar2 == fVar1) << 0xe);
    if (fVar2 < fVar1) {
      return pfVar14;
    }
    return (float *)CONCAT31((int3)((uint)pfVar14 >> 8),1);
  }
  return (float *)CONCAT22(uVar15,(ushort)(fVar1 < fVar10) << 8 |
                                  (ushort)(NAN(fVar1) || NAN(fVar10)) << 10 |
                                  (ushort)(fVar1 == fVar10) << 0xe);
}

