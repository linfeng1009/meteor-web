/* Original Meteor.exe static export @ 00536a30; original sample not executed. */
/* XREF 0052dc94 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00536a30(int *param_1,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  char cVar2;
  byte bVar3;
  undefined1 uVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  float10 fVar15;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float10 extraout_ST0_03;
  float10 extraout_ST0_04;
  float10 extraout_ST0_05;
  float10 extraout_ST0_06;
  float10 extraout_ST0_07;
  float10 extraout_ST0_08;
  float10 extraout_ST0_09;
  float10 extraout_ST0_10;
  float10 extraout_ST0_11;
  float10 extraout_ST0_12;
  float10 extraout_ST0_13;
  float10 extraout_ST0_14;
  float10 extraout_ST0_15;
  float10 extraout_ST0_16;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  float10 extraout_ST1_01;
  float10 extraout_ST1_02;
  float10 extraout_ST1_03;
  float10 extraout_ST1_04;
  
  if (param_1 == (int *)0x0) {
    FUN_00530d00(0x506);
    return 0;
  }
  _DAT_007dc7e8 = (double)param_3 / (double)*param_1;
  _DAT_007dc7d8 = (double)param_4 / (double)param_1[1];
  if (DAT_005cfe18 != 0x2601) {
    if (DAT_005cfe18 == 0x2602) {
      DAT_007dc780 = (uint)param_1[4] / (uint)*(byte *)((int)param_1 + 0xd);
      DAT_007dc810 = *(uint *)(param_2 + 0x10) / (uint)*(byte *)(param_2 + 0xd);
      cVar2 = *(char *)((int)param_1 + 0xd);
      if (cVar2 == '\x01') {
        DAT_007dc794 = 0;
        if (param_4 != 0) {
          do {
            iVar6 = __ftol();
            DAT_007dc800 = iVar6 * DAT_007dc780;
            DAT_007dc790 = 0;
            if (param_3 != 0) {
              fVar15 = (float10)param_3;
              do {
                uVar10 = DAT_007dc790;
                _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
                _DAT_007dc7b8 = (double)(((float10)DAT_007dc790 / fVar15) * fVar15);
                uVar8 = __ftol();
                _DAT_007dc7b0 = _DAT_007dc7b8 - (double)uVar8;
                _DAT_007dc7c8 = (double)((float10)_DAT_005cfe98 * (float10)_DAT_007dc7b0);
                fVar15 = (float10)fcos((float10)_DAT_005cfe98 * (float10)_DAT_007dc7b0);
                _DAT_007dc788 = (double)(((float10)_DAT_005a8418 - fVar15) * (float10)_DAT_005a8460)
                ;
                iVar6 = __ftol();
                DAT_007dc7f8 = (uint)*(byte *)(param_1 + 3) * iVar6;
                DAT_007dc7fc = (iVar6 + 1) * (uint)*(byte *)(param_1 + 3);
                DAT_007dc814 = *(byte *)(param_2 + 0xc) * uVar10 + DAT_007dc794 * DAT_007dc810;
                DAT_007dc820 = 0;
                fVar15 = extraout_ST0_03;
                if (*(char *)(param_2 + 0xc) != '\0') {
                  do {
                    uVar10 = DAT_007dc820;
                    iVar6 = DAT_007dc814;
                    _DAT_007dc7d0 =
                         (uint)*(byte *)(DAT_007dc820 + DAT_007dc7f8 + DAT_007dc800 + param_1[5]);
                    _DAT_007dc7e0 =
                         (uint)*(byte *)(DAT_007dc820 + DAT_007dc7fc + DAT_007dc800 + param_1[5]);
                    uVar4 = __ftol();
                    *(undefined1 *)(*(int *)(param_2 + 0x14) + uVar10 + iVar6) = uVar4;
                    DAT_007dc820 = DAT_007dc820 + 1;
                    fVar15 = extraout_ST0_04;
                  } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
                }
                DAT_007dc790 = DAT_007dc790 + 1;
              } while (DAT_007dc790 < param_3);
            }
            DAT_007dc794 = DAT_007dc794 + 1;
          } while (DAT_007dc794 < param_4);
        }
      }
      else if (cVar2 == '\x02') {
        DAT_007dc81c = param_1[5];
        DAT_007dc7a0 = *(int *)(param_2 + 0x14);
        DAT_007dc794 = 0;
        if (param_4 != 0) {
          do {
            iVar6 = __ftol();
            DAT_007dc800 = iVar6 * DAT_007dc780;
            DAT_007dc790 = 0;
            if (param_3 != 0) {
              fVar15 = (float10)param_3;
              do {
                uVar10 = DAT_007dc790;
                _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
                _DAT_007dc7b8 = (double)(((float10)DAT_007dc790 / fVar15) * fVar15);
                uVar8 = __ftol();
                _DAT_007dc7b0 = _DAT_007dc7b8 - (double)uVar8;
                _DAT_007dc7c8 = (double)((float10)_DAT_005cfe98 * (float10)_DAT_007dc7b0);
                fVar15 = (float10)fcos((float10)_DAT_005cfe98 * (float10)_DAT_007dc7b0);
                _DAT_007dc788 = (double)(((float10)_DAT_005a8418 - fVar15) * (float10)_DAT_005a8460)
                ;
                iVar6 = __ftol();
                DAT_007dc7f8 = (uint)*(byte *)(param_1 + 3) * iVar6;
                DAT_007dc7fc = (iVar6 + 1) * (uint)*(byte *)(param_1 + 3);
                DAT_007dc814 = *(byte *)(param_2 + 0xc) * uVar10 + DAT_007dc794 * DAT_007dc810;
                DAT_007dc820 = 0;
                fVar15 = extraout_ST0_01;
                if (*(char *)(param_2 + 0xc) != '\0') {
                  do {
                    uVar10 = DAT_007dc820;
                    iVar6 = DAT_007dc814;
                    _DAT_007dc7d0 =
                         (uint)*(ushort *)
                                (DAT_007dc81c + (DAT_007dc7f8 + DAT_007dc820 + DAT_007dc800) * 2);
                    _DAT_007dc7e0 =
                         (uint)*(ushort *)
                                (DAT_007dc81c + (DAT_007dc7fc + DAT_007dc820 + DAT_007dc800) * 2);
                    uVar5 = __ftol();
                    *(undefined2 *)(DAT_007dc7a0 + (uVar10 + iVar6) * 2) = uVar5;
                    DAT_007dc820 = DAT_007dc820 + 1;
                    fVar15 = extraout_ST0_02;
                  } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
                }
                DAT_007dc790 = DAT_007dc790 + 1;
              } while (DAT_007dc790 < param_3);
            }
            DAT_007dc794 = DAT_007dc794 + 1;
          } while (DAT_007dc794 < param_4);
          return param_2;
        }
      }
      else if (cVar2 == '\x04') {
        DAT_007dc7a4 = param_1[5];
        DAT_007dc7c0 = *(int *)(param_2 + 0x14);
        DAT_007dc794 = 0;
        if (param_4 != 0) {
          do {
            iVar6 = __ftol();
            DAT_007dc800 = iVar6 * DAT_007dc780;
            DAT_007dc790 = 0;
            if (param_3 != 0) {
              fVar15 = (float10)param_3;
              do {
                uVar10 = DAT_007dc790;
                _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
                _DAT_007dc7b8 = (double)(((float10)DAT_007dc790 / fVar15) * fVar15);
                uVar8 = __ftol();
                _DAT_007dc7b0 = _DAT_007dc7b8 - (double)uVar8;
                _DAT_007dc7c8 = (double)((float10)_DAT_005cfe98 * (float10)_DAT_007dc7b0);
                fVar15 = (float10)fcos((float10)_DAT_005cfe98 * (float10)_DAT_007dc7b0);
                _DAT_007dc788 = (double)(((float10)_DAT_005a8418 - fVar15) * (float10)_DAT_005a8460)
                ;
                iVar6 = __ftol();
                DAT_007dc7f8 = (uint)*(byte *)(param_1 + 3) * iVar6;
                DAT_007dc7fc = (iVar6 + 1) * (uint)*(byte *)(param_1 + 3);
                DAT_007dc814 = *(byte *)(param_2 + 0xc) * uVar10 + DAT_007dc794 * DAT_007dc810;
                DAT_007dc820 = 0;
                fVar15 = extraout_ST0;
                if (*(char *)(param_2 + 0xc) != '\0') {
                  do {
                    uVar10 = DAT_007dc820;
                    iVar6 = DAT_007dc814;
                    _DAT_007dc7d0 =
                         *(uint *)(DAT_007dc7a4 + (DAT_007dc7f8 + DAT_007dc820 + DAT_007dc800) * 4);
                    _DAT_007dc7e0 =
                         *(uint *)(DAT_007dc7a4 + (DAT_007dc7fc + DAT_007dc820 + DAT_007dc800) * 4);
                    uVar9 = __ftol();
                    *(undefined4 *)(DAT_007dc7c0 + (uVar10 + iVar6) * 4) = uVar9;
                    DAT_007dc820 = DAT_007dc820 + 1;
                    fVar15 = extraout_ST0_00;
                  } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
                }
                DAT_007dc790 = DAT_007dc790 + 1;
              } while (DAT_007dc790 < param_3);
            }
            DAT_007dc794 = DAT_007dc794 + 1;
          } while (DAT_007dc794 < param_4);
          return param_2;
        }
      }
      return param_2;
    }
    DAT_007dc780 = (uint)param_1[4] / (uint)*(byte *)((int)param_1 + 0xd);
    DAT_007dc810 = *(uint *)(param_2 + 0x10) / (uint)*(byte *)(param_2 + 0xd);
    cVar2 = *(char *)((int)param_1 + 0xd);
    if (cVar2 == '\x01') {
      param_4 = param_4 - 1;
      DAT_007dc794 = 0;
      if (param_4 != 0) {
        do {
          iVar6 = __ftol();
          uVar10 = DAT_007dc780;
          iVar6 = iVar6 * DAT_007dc780;
          DAT_007dc800 = iVar6;
          iVar7 = __ftol();
          DAT_007dc804 = iVar7 * uVar10;
          DAT_007dc790 = 0;
          if (param_3 != 0) {
            fVar15 = (float10)param_3;
            do {
              _DAT_007dc730 = (double)(fVar15 / (float10)_DAT_007dc7e8);
              _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
              uVar10 = __ftol();
              _DAT_007dc7b0 = (double)(extraout_ST0_13 - (float10)uVar10);
              _DAT_007dc738 = _DAT_005a8418 - _DAT_007dc7b0;
              _DAT_007dc7b8 = _DAT_007dc7a8 * _DAT_007dc730;
              bVar3 = *(byte *)(param_1 + 3);
              iVar7 = __ftol();
              iVar7 = (uint)bVar3 * iVar7;
              DAT_007dc7f8 = iVar7;
              iVar11 = __ftol();
              uVar10 = 0;
              iVar11 = iVar11 * (uint)*(byte *)(param_1 + 3);
              DAT_007dc7fc = iVar11;
              if (*(char *)(param_2 + 0xc) != '\0') {
                do {
                  iVar13 = DAT_007dc804;
                  (&DAT_007dc740)[uVar10] =
                       (double)*(byte *)(param_1[5] + uVar10 + iVar7 + iVar6) * _DAT_007dc738 +
                       (double)*(byte *)(param_1[5] + uVar10 + iVar11 + iVar6) * _DAT_007dc7b0;
                  iVar6 = DAT_007dc800;
                  iVar14 = param_1[5] + uVar10;
                  uVar10 = uVar10 + 1;
                  *(double *)(uVar10 * 8 + 0x7dc758) =
                       (double)*(byte *)(iVar14 + iVar7 + iVar13) * _DAT_007dc738 +
                       (double)*(byte *)(iVar14 + iVar11 + iVar13) * _DAT_007dc7b0;
                } while (uVar10 < *(byte *)(param_2 + 0xc));
              }
              _DAT_007dc7a8 = (double)((float10)DAT_007dc794 / extraout_ST0_14);
              _DAT_007dc738 = _DAT_005a8418 - _DAT_007dc7a8;
              DAT_007dc820 = 0;
              DAT_007dc814 = *(byte *)(param_2 + 0xc) * DAT_007dc790 + DAT_007dc794 * DAT_007dc810;
              fVar15 = extraout_ST1_03;
              if (*(char *)(param_2 + 0xc) != '\0') {
                do {
                  uVar10 = DAT_007dc820;
                  iVar6 = DAT_007dc814;
                  uVar4 = __ftol();
                  *(undefined1 *)(*(int *)(param_2 + 0x14) + iVar6 + uVar10) = uVar4;
                  DAT_007dc820 = DAT_007dc820 + 1;
                  iVar6 = DAT_007dc800;
                  fVar15 = extraout_ST1_04;
                } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
              }
              DAT_007dc790 = DAT_007dc790 + 1;
            } while (DAT_007dc790 < param_3);
          }
          DAT_007dc794 = DAT_007dc794 + 1;
        } while (DAT_007dc794 < param_4);
      }
      iVar6 = __ftol();
      DAT_007dc800 = iVar6 * DAT_007dc780;
      DAT_007dc790 = 0;
      if (param_3 != 0) {
        fVar15 = (float10)param_3;
        do {
          uVar10 = DAT_007dc790;
          _DAT_007dc730 = (double)(fVar15 / (float10)_DAT_007dc7e8);
          _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
          _DAT_007dc7b8 = (double)(((float10)DAT_007dc790 / fVar15) * fVar15);
          uVar8 = __ftol();
          fVar15 = ((float10)_DAT_007dc7b8 - (float10)uVar8) * (float10)_DAT_005cfe98;
          _DAT_007dc7c8 = (double)fVar15;
          fVar15 = (float10)fcos(fVar15);
          _DAT_007dc788 = (double)(((float10)_DAT_005a8418 - fVar15) * (float10)_DAT_005a8460);
          bVar3 = *(byte *)(param_1 + 3);
          iVar6 = __ftol();
          DAT_007dc7f8 = (uint)bVar3 * iVar6;
          iVar6 = __ftol();
          DAT_007dc7fc = iVar6 * (uint)*(byte *)(param_1 + 3);
          DAT_007dc814 = *(byte *)(param_1 + 3) * uVar10 + DAT_007dc810 * param_4;
          DAT_007dc820 = 0;
          fVar15 = extraout_ST0_15;
          if (*(char *)(param_2 + 0xc) != '\0') {
            do {
              uVar10 = DAT_007dc820;
              iVar6 = DAT_007dc814;
              uVar4 = __ftol();
              *(undefined1 *)(*(int *)(param_2 + 0x14) + iVar6 + uVar10) = uVar4;
              DAT_007dc820 = DAT_007dc820 + 1;
              fVar15 = extraout_ST0_16;
            } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
          }
          DAT_007dc790 = DAT_007dc790 + 1;
        } while (DAT_007dc790 < param_3);
      }
    }
    else if (cVar2 == '\x02') {
      iVar6 = param_1[5];
      DAT_007dc7a0 = *(int *)(param_2 + 0x14);
      param_4 = param_4 - 1;
      DAT_007dc794 = 0;
      DAT_007dc81c = iVar6;
      if (param_4 != 0) {
        do {
          iVar7 = __ftol();
          uVar10 = DAT_007dc780;
          DAT_007dc800 = iVar7 * DAT_007dc780;
          iVar7 = __ftol();
          DAT_007dc804 = iVar7 * uVar10;
          DAT_007dc790 = 0;
          if (param_3 != 0) {
            fVar15 = (float10)param_3;
            do {
              _DAT_007dc730 = (double)(fVar15 / (float10)_DAT_007dc7e8);
              _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
              uVar10 = __ftol();
              _DAT_007dc7b0 = (double)(extraout_ST0_09 - (float10)uVar10);
              _DAT_007dc738 = _DAT_005a8418 - _DAT_007dc7b0;
              _DAT_007dc7b8 = _DAT_007dc7a8 * _DAT_007dc730;
              bVar3 = *(byte *)(param_1 + 3);
              iVar7 = __ftol();
              iVar7 = (uint)bVar3 * iVar7;
              DAT_007dc7f8 = iVar7;
              iVar11 = __ftol();
              DAT_007dc7fc = iVar11 * (uint)*(byte *)(param_1 + 3);
              uVar10 = 0;
              if (*(char *)(param_2 + 0xc) != '\0') {
                iVar11 = iVar7 + DAT_007dc800;
                iVar14 = DAT_007dc800 + DAT_007dc7fc;
                iVar7 = DAT_007dc804 + iVar7;
                iVar13 = DAT_007dc7fc + DAT_007dc804;
                do {
                  iVar12 = iVar13 + uVar10;
                  (&DAT_007dc740)[uVar10] =
                       (double)*(ushort *)(iVar6 + (iVar11 + uVar10) * 2) * _DAT_007dc738 +
                       (double)*(ushort *)(iVar6 + (iVar14 + uVar10) * 2) * _DAT_007dc7b0;
                  iVar1 = uVar10 + iVar7;
                  uVar10 = uVar10 + 1;
                  *(double *)(uVar10 * 8 + 0x7dc758) =
                       (double)*(ushort *)(iVar6 + iVar1 * 2) * _DAT_007dc738 +
                       (double)*(ushort *)(iVar6 + iVar12 * 2) * _DAT_007dc7b0;
                } while (uVar10 < *(byte *)(param_2 + 0xc));
              }
              _DAT_007dc7a8 = (double)((float10)DAT_007dc794 / extraout_ST0_10);
              _DAT_007dc738 = _DAT_005a8418 - _DAT_007dc7a8;
              DAT_007dc820 = 0;
              DAT_007dc814 = *(byte *)(param_2 + 0xc) * DAT_007dc790 + DAT_007dc794 * DAT_007dc810;
              fVar15 = extraout_ST1_01;
              if (*(char *)(param_2 + 0xc) != '\0') {
                do {
                  uVar10 = DAT_007dc820;
                  iVar6 = DAT_007dc814;
                  uVar5 = __ftol();
                  *(undefined2 *)(DAT_007dc7a0 + (iVar6 + uVar10) * 2) = uVar5;
                  DAT_007dc820 = DAT_007dc820 + 1;
                  iVar6 = DAT_007dc81c;
                  fVar15 = extraout_ST1_02;
                } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
              }
              DAT_007dc790 = DAT_007dc790 + 1;
            } while (DAT_007dc790 < param_3);
          }
          DAT_007dc794 = DAT_007dc794 + 1;
        } while (DAT_007dc794 < param_4);
      }
      iVar6 = __ftol();
      DAT_007dc800 = iVar6 * DAT_007dc780;
      DAT_007dc790 = 0;
      if (param_3 != 0) {
        fVar15 = (float10)param_3;
        do {
          _DAT_007dc730 = (double)(fVar15 / (float10)_DAT_007dc7e8);
          _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
          _DAT_007dc7b8 = (double)(((float10)DAT_007dc790 / fVar15) * fVar15);
          uVar10 = __ftol();
          fVar15 = ((float10)_DAT_007dc7b8 - (float10)uVar10) * (float10)_DAT_005cfe98;
          _DAT_007dc7c8 = (double)fVar15;
          fVar15 = (float10)fcos(fVar15);
          _DAT_007dc788 = (double)(((float10)_DAT_005a8418 - fVar15) * (float10)_DAT_005a8460);
          bVar3 = *(byte *)(param_1 + 3);
          iVar6 = __ftol();
          DAT_007dc7f8 = (uint)bVar3 * iVar6;
          iVar6 = __ftol();
          DAT_007dc7fc = iVar6 * (uint)*(byte *)(param_1 + 3);
          DAT_007dc814 = *(byte *)(param_1 + 3) * DAT_007dc790 + DAT_007dc810 * param_4;
          DAT_007dc820 = 0;
          fVar15 = extraout_ST0_11;
          if (*(char *)(param_2 + 0xc) != '\0') {
            do {
              uVar10 = DAT_007dc820;
              iVar6 = DAT_007dc814;
              uVar5 = __ftol();
              *(undefined2 *)(DAT_007dc7a0 + (iVar6 + uVar10) * 2) = uVar5;
              DAT_007dc820 = DAT_007dc820 + 1;
              fVar15 = extraout_ST0_12;
            } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
          }
          DAT_007dc790 = DAT_007dc790 + 1;
        } while (DAT_007dc790 < param_3);
        return param_2;
      }
    }
    else if (cVar2 == '\x04') {
      iVar6 = param_1[5];
      DAT_007dc7c0 = *(int *)(param_2 + 0x14);
      param_4 = param_4 - 1;
      DAT_007dc794 = 0;
      DAT_007dc7a4 = iVar6;
      if (param_4 != 0) {
        do {
          iVar7 = __ftol();
          uVar10 = DAT_007dc780;
          DAT_007dc800 = iVar7 * DAT_007dc780;
          iVar7 = __ftol();
          DAT_007dc804 = iVar7 * uVar10;
          DAT_007dc790 = 0;
          if (param_3 != 0) {
            fVar15 = (float10)param_3;
            do {
              _DAT_007dc730 = (double)(fVar15 / (float10)_DAT_007dc7e8);
              _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
              uVar10 = __ftol();
              _DAT_007dc7b0 = (double)(extraout_ST0_05 - (float10)uVar10);
              _DAT_007dc738 = _DAT_005a8418 - _DAT_007dc7b0;
              _DAT_007dc7b8 = _DAT_007dc7a8 * _DAT_007dc730;
              bVar3 = *(byte *)(param_1 + 3);
              iVar7 = __ftol();
              iVar7 = (uint)bVar3 * iVar7;
              DAT_007dc7f8 = iVar7;
              iVar11 = __ftol();
              DAT_007dc7fc = iVar11 * (uint)*(byte *)(param_1 + 3);
              uVar10 = 0;
              if (*(char *)(param_2 + 0xc) != '\0') {
                iVar13 = DAT_007dc800 + iVar7;
                iVar14 = DAT_007dc800 + DAT_007dc7fc;
                iVar7 = iVar7 + DAT_007dc804;
                iVar11 = DAT_007dc7fc + DAT_007dc804;
                do {
                  iVar1 = iVar11 + uVar10;
                  (&DAT_007dc740)[uVar10] =
                       (double)*(uint *)(iVar6 + (iVar13 + uVar10) * 4) * _DAT_007dc738 +
                       (double)*(uint *)(iVar6 + (iVar14 + uVar10) * 4) * _DAT_007dc7b0;
                  iVar12 = iVar7 + uVar10;
                  uVar10 = uVar10 + 1;
                  *(double *)(uVar10 * 8 + 0x7dc758) =
                       (double)*(uint *)(iVar6 + iVar12 * 4) * _DAT_007dc738 +
                       (double)*(uint *)(iVar6 + iVar1 * 4) * _DAT_007dc7b0;
                } while (uVar10 < *(byte *)(param_2 + 0xc));
              }
              _DAT_007dc7a8 = (double)((float10)DAT_007dc794 / extraout_ST0_06);
              _DAT_007dc738 = _DAT_005a8418 - _DAT_007dc7a8;
              DAT_007dc820 = 0;
              DAT_007dc814 = *(byte *)(param_2 + 0xc) * DAT_007dc790 + DAT_007dc794 * DAT_007dc810;
              fVar15 = extraout_ST1;
              if (*(char *)(param_2 + 0xc) != '\0') {
                do {
                  uVar10 = DAT_007dc820;
                  iVar6 = DAT_007dc814;
                  uVar9 = __ftol();
                  *(undefined4 *)(DAT_007dc7c0 + (iVar6 + uVar10) * 4) = uVar9;
                  DAT_007dc820 = DAT_007dc820 + 1;
                  iVar6 = DAT_007dc7a4;
                  fVar15 = extraout_ST1_00;
                } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
              }
              DAT_007dc790 = DAT_007dc790 + 1;
            } while (DAT_007dc790 < param_3);
          }
          DAT_007dc794 = DAT_007dc794 + 1;
        } while (DAT_007dc794 < param_4);
      }
      iVar6 = __ftol();
      DAT_007dc800 = iVar6 * DAT_007dc780;
      DAT_007dc790 = 0;
      if (param_3 != 0) {
        fVar15 = (float10)param_3;
        do {
          _DAT_007dc730 = (double)(fVar15 / (float10)_DAT_007dc7e8);
          _DAT_007dc7a8 = (double)((float10)DAT_007dc790 / fVar15);
          _DAT_007dc7b8 = (double)(((float10)DAT_007dc790 / fVar15) * fVar15);
          uVar10 = __ftol();
          fVar15 = ((float10)_DAT_007dc7b8 - (float10)uVar10) * (float10)_DAT_005cfe98;
          _DAT_007dc7c8 = (double)fVar15;
          fVar15 = (float10)fcos(fVar15);
          _DAT_007dc788 = (double)(((float10)_DAT_005a8418 - fVar15) * (float10)_DAT_005a8460);
          bVar3 = *(byte *)(param_1 + 3);
          iVar6 = __ftol();
          DAT_007dc7f8 = (uint)bVar3 * iVar6;
          iVar6 = __ftol();
          DAT_007dc7fc = iVar6 * (uint)*(byte *)(param_1 + 3);
          DAT_007dc814 = *(byte *)(param_1 + 3) * DAT_007dc790 + DAT_007dc810 * param_4;
          DAT_007dc820 = 0;
          fVar15 = extraout_ST0_07;
          if (*(char *)(param_2 + 0xc) != '\0') {
            do {
              uVar10 = DAT_007dc820;
              iVar6 = DAT_007dc814;
              uVar9 = __ftol();
              *(undefined4 *)(DAT_007dc7c0 + (iVar6 + uVar10) * 4) = uVar9;
              DAT_007dc820 = DAT_007dc820 + 1;
              fVar15 = extraout_ST0_08;
            } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
          }
          DAT_007dc790 = DAT_007dc790 + 1;
        } while (DAT_007dc790 < param_3);
        return param_2;
      }
    }
    return param_2;
  }
  DAT_007dc780 = (uint)param_1[4] / (uint)*(byte *)((int)param_1 + 0xd);
  DAT_007dc810 = *(uint *)(param_2 + 0x10) / (uint)*(byte *)(param_2 + 0xd);
  cVar2 = *(char *)((int)param_1 + 0xd);
  if (cVar2 == '\x01') {
    DAT_007dc794 = 0;
    if (param_4 != 0) {
      do {
        uVar10 = DAT_007dc794;
        DAT_007dc800 = DAT_007dc794 * DAT_007dc810;
        iVar6 = __ftol();
        DAT_007dc804 = iVar6 * DAT_007dc780;
        DAT_007dc790 = 0;
        if (param_3 != 0) {
          do {
            uVar10 = DAT_007dc790;
            iVar6 = *(byte *)(param_2 + 0xc) * DAT_007dc790;
            DAT_007dc7f8 = iVar6;
            iVar7 = __ftol();
            DAT_007dc7fc = iVar7 * (uint)*(byte *)(param_1 + 3);
            DAT_007dc820 = 0;
            if (*(char *)(param_2 + 0xc) != '\0') {
              do {
                *(undefined1 *)(DAT_007dc800 + *(int *)(param_2 + 0x14) + DAT_007dc820 + iVar6) =
                     *(undefined1 *)(DAT_007dc820 + DAT_007dc7fc + DAT_007dc804 + param_1[5]);
                DAT_007dc820 = DAT_007dc820 + 1;
                _DAT_007dc7d0 = 0;
                uVar10 = DAT_007dc790;
                iVar6 = DAT_007dc7f8;
              } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
            }
            DAT_007dc790 = uVar10 + 1;
            uVar10 = DAT_007dc794;
          } while (DAT_007dc790 < param_3);
        }
        DAT_007dc794 = uVar10 + 1;
      } while (DAT_007dc794 < param_4);
    }
  }
  else if (cVar2 == '\x02') {
    DAT_007dc81c = param_1[5];
    DAT_007dc7a0 = *(int *)(param_2 + 0x14);
    DAT_007dc794 = 0;
    if (param_4 != 0) {
      do {
        uVar10 = DAT_007dc794;
        DAT_007dc800 = DAT_007dc794 * DAT_007dc810;
        iVar6 = __ftol();
        DAT_007dc804 = iVar6 * DAT_007dc780;
        DAT_007dc790 = 0;
        if (param_3 != 0) {
          do {
            uVar10 = DAT_007dc790;
            iVar6 = *(byte *)(param_2 + 0xc) * DAT_007dc790;
            DAT_007dc7f8 = iVar6;
            iVar7 = __ftol();
            DAT_007dc7fc = iVar7 * (uint)*(byte *)(param_1 + 3);
            DAT_007dc820 = 0;
            if (*(char *)(param_2 + 0xc) != '\0') {
              do {
                *(undefined2 *)(DAT_007dc7a0 + (DAT_007dc820 + iVar6 + DAT_007dc800) * 2) =
                     *(undefined2 *)
                      (DAT_007dc81c + (DAT_007dc7fc + DAT_007dc820 + DAT_007dc804) * 2);
                DAT_007dc820 = DAT_007dc820 + 1;
                _DAT_007dc7d0 = 0;
                uVar10 = DAT_007dc790;
                iVar6 = DAT_007dc7f8;
              } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
            }
            DAT_007dc790 = uVar10 + 1;
            uVar10 = DAT_007dc794;
          } while (DAT_007dc790 < param_3);
        }
        DAT_007dc794 = uVar10 + 1;
      } while (DAT_007dc794 < param_4);
      return param_2;
    }
  }
  else if (cVar2 == '\x04') {
    DAT_007dc7a4 = param_1[5];
    DAT_007dc7c0 = *(int *)(param_2 + 0x14);
    DAT_007dc794 = 0;
    if (param_4 != 0) {
      do {
        uVar10 = DAT_007dc794;
        DAT_007dc800 = DAT_007dc794 * DAT_007dc810;
        iVar6 = __ftol();
        DAT_007dc804 = iVar6 * DAT_007dc780;
        DAT_007dc790 = 0;
        if (param_3 != 0) {
          do {
            uVar10 = DAT_007dc790;
            iVar6 = *(byte *)(param_2 + 0xc) * DAT_007dc790;
            DAT_007dc7f8 = iVar6;
            iVar7 = __ftol();
            DAT_007dc7fc = iVar7 * (uint)*(byte *)(param_1 + 3);
            DAT_007dc820 = 0;
            if (*(char *)(param_2 + 0xc) != '\0') {
              do {
                *(undefined4 *)(DAT_007dc7c0 + (DAT_007dc820 + iVar6 + DAT_007dc800) * 4) =
                     *(undefined4 *)
                      (DAT_007dc7a4 + (DAT_007dc820 + DAT_007dc7fc + DAT_007dc804) * 4);
                DAT_007dc820 = DAT_007dc820 + 1;
                _DAT_007dc7d0 = 0;
                uVar10 = DAT_007dc790;
                iVar6 = DAT_007dc7f8;
              } while (DAT_007dc820 < *(byte *)(param_2 + 0xc));
            }
            DAT_007dc790 = uVar10 + 1;
            uVar10 = DAT_007dc794;
          } while (DAT_007dc790 < param_3);
        }
        DAT_007dc794 = uVar10 + 1;
      } while (DAT_007dc794 < param_4);
      return param_2;
    }
  }
  return param_2;
}

