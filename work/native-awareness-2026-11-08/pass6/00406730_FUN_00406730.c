/* Original Meteor.exe static export @ 00406730; original sample not executed. */
/* XREF 00406639 UNCONDITIONAL_CALL */
/* XREF 004066e1 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00406730(int param_1,int param_2,int *param_3,int param_4,int param_5,int param_6,
                 int param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  float *pfVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar6 = param_6;
  param_4 = param_4 / param_7;
  iVar7 = param_4 * param_6;
  if (0 < param_7) {
    param_6 = param_7;
    iVar13 = param_2;
    do {
      if (0 < param_5) {
        param_2 = param_5;
        iVar10 = param_1;
        piVar8 = param_3;
        do {
          if (*piVar8 == 1) {
            local_c = *(float *)(iVar13 + piVar8[4] * iVar6 * 4) -
                      *(float *)(iVar13 + piVar8[3] * iVar6 * 4);
            local_8 = *(float *)(iVar13 + 4 + piVar8[4] * iVar6 * 4) -
                      *(float *)(iVar13 + 4 + piVar8[3] * iVar6 * 4);
            local_4 = *(float *)(iVar13 + 8 + piVar8[4] * iVar6 * 4) -
                      *(float *)(iVar13 + 8 + piVar8[3] * iVar6 * 4);
            local_18 = *(float *)(iVar13 + piVar8[5] * iVar6 * 4) -
                       *(float *)(iVar13 + piVar8[3] * iVar6 * 4);
            local_14 = *(float *)(iVar13 + 4 + piVar8[5] * iVar6 * 4) -
                       *(float *)(iVar13 + 4 + piVar8[3] * iVar6 * 4);
            local_10 = *(float *)(iVar13 + 8 + piVar8[5] * iVar6 * 4) -
                       *(float *)(iVar13 + 8 + piVar8[3] * iVar6 * 4);
            FUN_00430e80(iVar10,&local_c,&local_18);
            iVar12 = DAT_005c4314;
          }
          else {
            iVar12 = piVar8[2] * 2 + 3;
          }
          piVar8 = piVar8 + iVar12;
          iVar10 = iVar10 + 0xc;
          param_2 = param_2 + -1;
        } while (param_2 != 0);
      }
      iVar12 = 0;
      iVar10 = iVar13;
      if (0 < param_4) {
        do {
          param_2 = 0;
          if (param_5 < 1) {
LAB_0040690d:
            *(undefined4 *)(iVar10 + 0x14) = 0x3f800000;
            *(undefined4 *)(iVar10 + 0xc) = 0;
            *(undefined4 *)(iVar10 + 0x10) = 0;
          }
          else {
            pfVar9 = (float *)(param_1 + 8);
            piVar8 = param_3;
            iVar11 = param_5;
            fVar1 = _DAT_005a83e4;
            fVar2 = _DAT_005a83e4;
            fVar3 = _DAT_005a83e4;
            do {
              if (*piVar8 == 1) {
                iVar5 = DAT_005c4314;
                if (((piVar8[3] == iVar12) || (piVar8[4] == iVar12)) || (piVar8[5] == iVar12)) {
                  fVar3 = fVar3 + pfVar9[-2];
                  fVar2 = fVar2 + pfVar9[-1];
                  fVar1 = fVar1 + *pfVar9;
                  param_2 = param_2 + 1;
                }
              }
              else {
                iVar5 = piVar8[2] * 2 + 3;
              }
              piVar8 = piVar8 + iVar5;
              pfVar9 = pfVar9 + 3;
              iVar11 = iVar11 + -1;
            } while (iVar11 != 0);
            if (param_2 < 1) goto LAB_0040690d;
            fVar4 = _DAT_005a83f4 / (float)param_2;
            *(float *)(iVar10 + 0xc) = fVar4 * fVar3;
            *(float *)(iVar10 + 0x10) = fVar4 * fVar2;
            *(float *)(iVar10 + 0x14) = fVar4 * fVar1;
          }
          iVar10 = iVar10 + iVar6 * 4;
          iVar12 = iVar12 + 1;
        } while (iVar12 < param_4);
      }
      iVar13 = iVar13 + iVar7 * 4;
      param_6 = param_6 + -1;
    } while (param_6 != 0);
  }
  return;
}

