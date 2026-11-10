/* Original Meteor.exe static export @ 0042dcc0; original sample not executed. */
/* XREF 00411573 UNCONDITIONAL_CALL */
/* XREF 004117d3 UNCONDITIONAL_CALL */
/* XREF 004118dd UNCONDITIONAL_CALL */
/* XREF 004119c9 UNCONDITIONAL_CALL */
/* XREF 00411ad9 UNCONDITIONAL_CALL */
/* XREF 00411bd1 UNCONDITIONAL_CALL */
/* XREF 0042edc0 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042dcc0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  char cVar1;
  undefined1 *puVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int *piVar15;
  int *piVar16;
  int *piVar17;
  char *pcVar18;
  undefined4 uVar19;
  
  iVar6 = param_1;
  if (DAT_005d5a0c == 0) {
    return;
  }
  if (param_1 == 0) {
    return;
  }
  if (param_6 == 1) {
    switch(*(undefined4 *)(param_1 + 0x44)) {
    case 2:
    case 4:
      *(uint *)(param_1 + 0x84) = (uint)(*(int *)(param_1 + 0x84) == 0);
      FUN_0042f0c0(param_1);
      return;
    case 3:
    case 10:
      *(undefined4 *)(param_1 + 0x84) = 1;
      FUN_0042f0c0(param_1);
      return;
    default:
      return;
    case 7:
      goto switchD_0042dd00_caseD_7;
    case 8:
      puVar2 = *(undefined1 **)(param_1 + 0xc0);
      iVar12 = *(int *)(puVar2 + 0x40) + *(int *)(param_1 + 0x4c);
      if (param_4 <= iVar12) {
        return;
      }
      if (*(int *)(puVar2 + 0x50) + iVar12 <= param_4) {
        return;
      }
      iVar12 = (((param_5 - *(int *)(puVar2 + 0x44)) - *(int *)(param_1 + 0x50)) + -1) /
               (DAT_005c71e8 + 2) + *(int *)(puVar2 + 0x5c);
      if ((iVar12 < 0) || (*(int *)(puVar2 + 100) <= iVar12)) {
        *(undefined4 *)(puVar2 + 0x60) = 0xffffffff;
        *puVar2 = 0;
        FUN_0042f0c0(param_1);
        return;
      }
      pcVar7 = *(char **)(puVar2 + 0x70);
      iVar8 = 0;
      *(int *)(puVar2 + 0x60) = iVar12;
      if (0 < iVar12) {
        do {
          if (pcVar7 == (char *)0x0) goto LAB_0042ed57;
          pcVar7 = *(char **)(pcVar7 + 0x40);
          iVar8 = iVar8 + 1;
        } while (iVar8 < iVar12);
      }
      if (pcVar7 != (char *)0x0) {
        iVar6 = (int)puVar2 - (int)pcVar7;
        do {
          cVar1 = *pcVar7;
          pcVar7[iVar6] = cVar1;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        FUN_0042f0c0(param_1);
        return;
      }
      goto LAB_0042ed57;
    }
  }
  if (param_6 == 2) {
    switch(*(undefined4 *)(param_1 + 0x44)) {
    case 2:
    case 4:
      if (*(int *)(param_1 + 0xb8) == 0) {
        return;
      }
      if (param_1 == param_3) {
        return;
      }
      *(uint *)(param_1 + 0x84) = (uint)(*(int *)(param_1 + 0x84) == 0);
      FUN_0042f0c0(param_1);
      return;
    case 3:
      *(undefined4 *)(param_1 + 0x84) = 0;
      FUN_0042f0c0(param_1);
      return;
    case 5:
      if (DAT_005d5b28 != 0) {
        DAT_005d5b28 = 0;
        return;
      }
      piVar15 = *(int **)(param_1 + 0xc0);
      if ((DAT_005d5b18 != 0) && (DAT_005d5b18 != param_1)) {
        *(undefined4 *)(*(int *)(DAT_005d5b18 + 0xc0) + 0x1c) = 1;
        FUN_0042f0c0(DAT_005d5b18);
      }
      piVar17 = piVar15 + 8;
      iVar6 = -1;
      piVar16 = piVar17;
      break;
    default:
      return;
    case 7:
      FUN_00404460(5,0x40a00000,0,1);
      *(undefined4 *)(*(int *)(param_1 + 0xc0) + 0x1c) = 0xffffffff;
      DAT_005d5b14 = 0;
      return;
    case 10:
      if (param_3 == 0) {
        return;
      }
      if (*(int *)(param_3 + 0x44) != 10) {
        return;
      }
      FUN_0042edd0(param_3,param_4,param_5);
      *(undefined4 *)(param_3 + 0x84) = 0;
      FUN_0042f050();
      return;
    }
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      iVar12 = *piVar16;
      piVar16 = (int *)((int)piVar16 + 1);
    } while ((char)iVar12 != '\0');
    if (iVar6 == -2) {
      piVar15[7] = 2;
      piVar15[4] = 0;
      piVar15[0x1c] = 0;
      piVar15[0x1d] = 0;
      DAT_005d5b18 = param_1;
      FUN_0042f0c0(param_1);
      return;
    }
    iVar6 = piVar15[7];
    if (iVar6 == 1) {
      uVar10 = 0xffffffff;
      piVar15[7] = 0;
      piVar16 = piVar17;
      do {
        if (uVar10 == 0) break;
        uVar10 = uVar10 - 1;
        iVar6 = *piVar16;
        piVar16 = (int *)((int)piVar16 + 1);
      } while ((char)iVar6 != '\0');
      piVar15[4] = ~uVar10 - 1;
      uVar10 = 0xffffffff;
      piVar16 = piVar17;
      do {
        if (uVar10 == 0) break;
        uVar10 = uVar10 - 1;
        iVar6 = *piVar16;
        piVar16 = (int *)((int)piVar16 + 1);
      } while ((char)iVar6 != '\0');
      uVar9 = piVar15[6];
      if (~uVar10 - 1 <= uVar9) {
        uVar10 = 0xffffffff;
        piVar15[0x1c] = 0;
        do {
          if (uVar10 == 0) break;
          uVar10 = uVar10 - 1;
          iVar6 = *piVar17;
          piVar17 = (int *)((int)piVar17 + 1);
        } while ((char)iVar6 != '\0');
        piVar15[0x1d] = ~uVar10 - 1;
        DAT_005d5b18 = param_1;
        FUN_0042f0c0(param_1);
        return;
      }
      uVar10 = 0xffffffff;
      do {
        if (uVar10 == 0) break;
        uVar10 = uVar10 - 1;
        iVar6 = *piVar17;
        piVar17 = (int *)((int)piVar17 + 1);
      } while ((char)iVar6 != '\0');
      piVar15[0x1c] = 0;
      piVar15[0x1d] = uVar9;
      piVar15[5] = (~uVar10 - 1) - uVar9;
      DAT_005d5b18 = param_1;
      FUN_0042f0c0(param_1);
      return;
    }
    if (iVar6 != 2) {
      if (iVar6 != 0) goto LAB_0042e4c7;
      piVar15[7] = 2;
    }
    uVar10 = 0xffffffff;
    uVar9 = piVar15[5] +
            ((param_4 - *(int *)(param_1 + 0x4c)) - *piVar15) / (DAT_005c71e4 + DAT_005c71ec);
    piVar15[4] = uVar9;
    piVar16 = piVar17;
    do {
      if (uVar10 == 0) break;
      uVar10 = uVar10 - 1;
      iVar6 = *piVar16;
      piVar16 = (int *)((int)piVar16 + 1);
    } while ((char)iVar6 != '\0');
    if (~uVar10 - 1 < uVar9) {
      uVar10 = 0xffffffff;
      do {
        if (uVar10 == 0) break;
        uVar10 = uVar10 - 1;
        iVar6 = *piVar17;
        piVar17 = (int *)((int)piVar17 + 1);
      } while ((char)iVar6 != '\0');
      piVar15[4] = ~uVar10 - 1;
    }
LAB_0042e4c7:
    DAT_005d5b18 = param_1;
    FUN_0042f0c0(param_1);
    return;
  }
  if (param_6 == 4) {
    if (*(int *)(param_1 + 0x44) == 5) {
      iVar6 = *(int *)(param_1 + 0xc0);
      if ((DAT_005d5b18 != 0) && (DAT_005d5b18 != param_1)) {
        *(undefined4 *)(*(int *)(DAT_005d5b18 + 0xc0) + 0x1c) = 1;
        FUN_0042f0c0(DAT_005d5b18);
      }
      pcVar7 = (char *)(iVar6 + 0x20);
      iVar12 = -1;
      pcVar18 = pcVar7;
      do {
        if (iVar12 == 0) break;
        iVar12 = iVar12 + -1;
        cVar1 = *pcVar18;
        pcVar18 = pcVar18 + 1;
      } while (cVar1 != '\0');
      if (iVar12 == -2) {
        *(undefined4 *)(iVar6 + 0x1c) = 2;
        *(undefined4 *)(iVar6 + 0x10) = 0;
        *(undefined4 *)(iVar6 + 0x70) = 0;
        *(undefined4 *)(iVar6 + 0x74) = 0;
      }
      else {
        uVar9 = 0xffffffff;
        *(undefined4 *)(iVar6 + 0x1c) = 0;
        uVar10 = *(uint *)(iVar6 + 0x18);
        pcVar18 = pcVar7;
        do {
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          cVar1 = *pcVar18;
          pcVar18 = pcVar18 + 1;
        } while (cVar1 != '\0');
        *(uint *)(iVar6 + 0x10) = ~uVar9 - 1;
        uVar9 = 0xffffffff;
        pcVar18 = pcVar7;
        do {
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          cVar1 = *pcVar18;
          pcVar18 = pcVar18 + 1;
        } while (cVar1 != '\0');
        if (uVar10 < ~uVar9 - 1) {
          uVar9 = 0xffffffff;
          do {
            if (uVar9 == 0) break;
            uVar9 = uVar9 - 1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          *(undefined4 *)(iVar6 + 0x70) = 0;
          *(uint *)(iVar6 + 0x74) = uVar10;
          *(uint *)(iVar6 + 0x14) = (~uVar9 - 1) - uVar10;
        }
        else {
          uVar10 = 0xffffffff;
          *(undefined4 *)(iVar6 + 0x70) = 0;
          do {
            if (uVar10 == 0) break;
            uVar10 = uVar10 - 1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          *(uint *)(iVar6 + 0x74) = ~uVar10 - 1;
        }
      }
      DAT_005d5b18 = param_1;
      FUN_0042f0c0(param_1);
      DAT_005d5b28 = 1;
      return;
    }
    if (*(int *)(param_1 + 0x44) != 8) {
      return;
    }
    puVar2 = *(undefined1 **)(param_1 + 0xc0);
    iVar6 = *(int *)(puVar2 + 0x40) + *(int *)(param_1 + 0x4c);
    if (param_4 <= iVar6) {
      return;
    }
    if (*(int *)(puVar2 + 0x50) + iVar6 <= param_4) {
      return;
    }
    iVar6 = (((param_5 - *(int *)(puVar2 + 0x44)) - *(int *)(param_1 + 0x50)) + -1) /
            (DAT_005c71e8 + 2) + *(int *)(puVar2 + 0x5c);
    if ((iVar6 < 0) || (*(int *)(puVar2 + 100) <= iVar6)) {
      *puVar2 = 0;
    }
    else {
      pcVar7 = *(char **)(puVar2 + 0x70);
      iVar12 = 0;
      if (0 < iVar6) {
        do {
          if (pcVar7 == (char *)0x0) goto LAB_0042e5b2;
          pcVar7 = *(char **)(pcVar7 + 0x40);
          iVar12 = iVar12 + 1;
        } while (iVar12 < iVar6);
      }
      if (pcVar7 != (char *)0x0) {
        iVar6 = (int)puVar2 - (int)pcVar7;
        do {
          cVar1 = *pcVar7;
          pcVar7[iVar6] = cVar1;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        *(undefined4 *)(puVar2 + 0x60) = 0xffffffff;
        FUN_0042f0c0(param_1);
        return;
      }
    }
LAB_0042e5b2:
    *(undefined4 *)(puVar2 + 0x60) = 0xffffffff;
    FUN_0042f0c0(param_1);
    return;
  }
  if (param_6 == 3) {
    if (*(int *)(param_1 + 0x44) != 7) {
      if (*(int *)(param_1 + 0x44) != 10) {
        return;
      }
      if (((param_3 != param_2) && (param_2 != 0)) && (*(int *)(param_2 + 0x44) == 10)) {
        *(undefined4 *)(param_2 + 0x84) = 0;
        *(undefined4 *)(param_2 + 100) = 0;
        FUN_0042f050();
      }
      if (param_3 == 0) {
        return;
      }
      if (*(int *)(param_3 + 0x44) != 10) {
        return;
      }
      FUN_0042edd0(param_3,param_4,param_5);
      *(undefined4 *)(param_3 + 0x84) = 1;
      FUN_0042f0c0(param_3);
      return;
    }
    piVar15 = *(int **)(param_1 + 0xc0);
    if (*piVar15 == 1) {
      iVar6 = piVar15[6];
      iVar12 = *(int *)(param_1 + 0x50);
      param_3 = iVar12 + iVar6;
      iVar8 = __ftol();
      iVar14 = iVar8 + iVar12 + iVar6;
      iVar8 = __ftol();
      param_6 = piVar15[1];
      iVar8 = iVar8 + iVar12 + iVar6;
      iVar6 = (iVar12 - iVar6) + param_6;
      if (param_5 < iVar12) {
        if (param_3 <= param_5) goto LAB_0042e767;
        if (iVar14 <= param_5) goto LAB_0042e776;
        if (iVar8 <= param_5) goto LAB_0042e785;
        if (iVar6 <= param_5) goto LAB_0042e794;
LAB_0042e7a1:
        iVar6 = -1;
      }
      else if (param_5 < param_3) {
        iVar6 = 1;
      }
      else {
LAB_0042e767:
        if (param_5 < iVar14) {
          iVar6 = 2;
        }
        else {
LAB_0042e776:
          if (param_5 < iVar8) {
            iVar6 = 3;
          }
          else {
LAB_0042e785:
            if (param_5 < iVar6) {
              iVar6 = 4;
            }
            else {
LAB_0042e794:
              if (iVar12 + param_6 <= param_5) goto LAB_0042e7a1;
              iVar6 = 5;
            }
          }
        }
      }
      if ((*(int *)(param_1 + 0x4c) < param_4) && (param_4 < piVar15[5] + *(int *)(param_1 + 0x4c)))
      {
        iVar12 = piVar15[6];
        bVar5 = false;
      }
      else {
        iVar12 = piVar15[6];
        bVar5 = true;
      }
    }
    else {
      iVar6 = piVar15[5];
      iVar12 = *(int *)(param_1 + 0x4c);
      param_3 = iVar12 + iVar6;
      iVar8 = __ftol();
      iVar14 = iVar8 + iVar12 + iVar6;
      iVar8 = __ftol();
      param_6 = piVar15[1];
      iVar8 = iVar8 + iVar12 + iVar6;
      iVar6 = (iVar12 - iVar6) + param_6;
      if (param_4 < iVar12) {
        if (param_3 <= param_4) goto LAB_0042e829;
        if (iVar14 <= param_4) goto LAB_0042e838;
        if (iVar8 <= param_4) goto LAB_0042e847;
        if (iVar6 <= param_4) goto LAB_0042e856;
LAB_0042e863:
        iVar6 = -1;
      }
      else if (param_4 < param_3) {
        iVar6 = 1;
      }
      else {
LAB_0042e829:
        if (param_4 < iVar14) {
          iVar6 = 2;
        }
        else {
LAB_0042e838:
          if (param_4 < iVar8) {
            iVar6 = 3;
          }
          else {
LAB_0042e847:
            if (param_4 < iVar6) {
              iVar6 = 4;
            }
            else {
LAB_0042e856:
              if (iVar12 + param_6 <= param_4) goto LAB_0042e863;
              iVar6 = 5;
            }
          }
        }
      }
      if ((*(int *)(param_1 + 0x50) < param_5) && (param_5 < piVar15[6] + *(int *)(param_1 + 0x50)))
      {
        bVar5 = false;
      }
      else {
        bVar5 = true;
      }
      iVar12 = piVar15[5];
    }
    iVar8 = piVar15[7];
    if ((iVar6 != iVar8) && (iVar8 != 3)) {
LAB_0042eb12:
      FUN_00404460(5,0x40a00000,0,1);
      piVar15[7] = -1;
      DAT_005d5b14 = 0;
      return;
    }
    if (bVar5) {
      if (iVar8 == 3) {
        return;
      }
      goto LAB_0042eb12;
    }
    if (iVar8 == 1) {
      if (piVar15[8] == 0) {
        fVar3 = (float)piVar15[2] - _DAT_005a83f4;
        piVar15[2] = (int)fVar3;
        if (fVar3 < _DAT_005a83e4) {
          piVar15[2] = 0;
        }
        FUN_0042f0c0(param_1);
        return;
      }
      iVar6 = *(int *)(piVar15[8] + 0xc0);
      if (*piVar15 == 1) {
        iVar12 = *(int *)(iVar6 + 0x5c) + -1;
        *(int *)(iVar6 + 0x5c) = iVar12;
        if (iVar12 < 0) {
          *(undefined4 *)(iVar6 + 0x5c) = 0;
        }
      }
      else {
        iVar12 = *(int *)(iVar6 + 0x58) + -1;
        *(int *)(iVar6 + 0x58) = iVar12;
        if (iVar12 < 0) {
          *(undefined4 *)(iVar6 + 0x58) = 0;
        }
      }
      goto LAB_0042ec9b;
    }
    if (iVar8 == 2) {
      if (piVar15[8] == 0) {
        fVar3 = (float)piVar15[2] - _DAT_005a84ac;
        piVar15[2] = (int)fVar3;
        if (fVar3 < _DAT_005a83e4) {
          piVar15[2] = 0;
        }
        FUN_0042f0c0(param_1);
        return;
      }
      iVar6 = *(int *)(piVar15[8] + 0xc0);
      if (*piVar15 == 1) {
        iVar12 = *(int *)(iVar6 + 0x5c) + -10;
        *(int *)(iVar6 + 0x5c) = iVar12;
        if (iVar12 < 0) {
          *(undefined4 *)(iVar6 + 0x5c) = 0;
        }
      }
      else {
        iVar12 = *(int *)(iVar6 + 0x58) + -10;
        *(int *)(iVar6 + 0x58) = iVar12;
        if (iVar12 < 0) {
          *(undefined4 *)(iVar6 + 0x58) = 0;
        }
      }
      FUN_0042d230(piVar15[8],*piVar15);
      FUN_0042f0c0(piVar15[8]);
      return;
    }
    if (iVar8 == 3) {
      if (*piVar15 == 1) {
        param_3 = (param_5 - piVar15[4]) - param_3;
      }
      else {
        param_3 = (param_4 - piVar15[4]) - param_3;
      }
      piVar15[2] = (int)(float)param_3;
      if ((float)piVar15[2] < _DAT_005a83e4) {
        piVar15[2] = 0;
      }
      fVar3 = (float)(param_6 + iVar12 * -2);
      if (fVar3 < (float)piVar15[3] + (float)piVar15[2] !=
          (fVar3 == (float)piVar15[3] + (float)piVar15[2])) {
        piVar15[2] = (int)(((float)param_6 - (float)piVar15[3]) - (float)(iVar12 * 2));
      }
      FUN_0042f0c0(param_1);
      if (piVar15[8] == 0) {
        return;
      }
      FUN_0042d1b0(param_1);
      return;
    }
    if (iVar8 == 4) {
      iVar8 = piVar15[8];
      if (iVar8 == 0) {
        fVar3 = (float)piVar15[2] + _DAT_005a84ac;
        piVar15[2] = (int)fVar3;
        fVar3 = fVar3 + (float)piVar15[3];
        fVar4 = (float)(param_6 + iVar12 * -2);
        if (fVar4 < fVar3 != (fVar4 == fVar3)) {
          piVar15[2] = (int)(((float)param_6 - (float)piVar15[3]) - (float)(iVar12 * 2));
          FUN_0042f0c0(param_1);
          return;
        }
LAB_0042eaf6:
        FUN_0042f0c0(param_1);
        return;
      }
      iVar12 = *piVar15;
      goto LAB_0042ec59;
    }
    if (iVar8 != 5) {
      return;
    }
    iVar8 = piVar15[8];
    if (iVar8 == 0) {
      fVar3 = (float)piVar15[2] + _DAT_005a83f4;
      piVar15[2] = (int)fVar3;
      fVar3 = fVar3 + (float)piVar15[3];
      fVar4 = (float)(param_6 + iVar12 * -2);
      if (fVar4 < fVar3 != (fVar4 == fVar3)) {
        piVar15[2] = (int)(((float)param_6 - (float)piVar15[3]) - (float)(iVar12 * 2));
      }
      goto LAB_0042eaf6;
    }
    iVar12 = *piVar15;
LAB_0042ecec:
    iVar6 = *(int *)(iVar8 + 0xc0);
    if (iVar12 == 1) {
      iVar12 = *(int *)(iVar6 + 0x5c) + 1;
      *(int *)(iVar6 + 0x5c) = iVar12;
      if (*(int *)(iVar6 + 100) <= iVar12 + *(int *)(iVar6 + 0x4c)) {
        *(int *)(iVar6 + 0x5c) = *(int *)(iVar6 + 100) - *(int *)(iVar6 + 0x4c);
      }
      goto LAB_0042ec9b;
    }
    iVar12 = *(int *)(iVar6 + 0x58) + 1;
  }
  else {
    if (param_6 != 5) {
      return;
    }
    if (*(int *)(param_1 + 0x44) != 7) {
      return;
    }
    piVar15 = *(int **)(param_1 + 0xc0);
    iVar12 = *piVar15;
    if (iVar12 == 1) {
      iVar14 = piVar15[6];
    }
    else {
      iVar14 = piVar15[5];
    }
    iVar8 = piVar15[7];
    if (iVar8 == 1) {
      if (piVar15[8] != 0) {
        iVar6 = *(int *)(piVar15[8] + 0xc0);
        if (iVar12 == 1) {
          iVar12 = *(int *)(iVar6 + 0x5c) + -1;
          *(int *)(iVar6 + 0x5c) = iVar12;
          if (iVar12 < 0) {
            *(undefined4 *)(iVar6 + 0x5c) = 0;
          }
        }
        else {
          iVar12 = *(int *)(iVar6 + 0x58) + -1;
          *(int *)(iVar6 + 0x58) = iVar12;
          if (iVar12 < 0) {
            *(undefined4 *)(iVar6 + 0x58) = 0;
          }
        }
        goto LAB_0042ec9b;
      }
      fVar3 = (float)piVar15[2] - _DAT_005a83f4;
      piVar15[2] = (int)fVar3;
      if (fVar3 < _DAT_005a83e4) {
        piVar15[2] = 0;
        FUN_0042f0c0(param_1);
        return;
      }
      goto LAB_0042ed57;
    }
    if (iVar8 == 2) {
      if (piVar15[8] != 0) {
        iVar6 = *(int *)(piVar15[8] + 0xc0);
        if (iVar12 == 1) {
          iVar12 = *(int *)(iVar6 + 0x5c) + -10;
          *(int *)(iVar6 + 0x5c) = iVar12;
          if (iVar12 < 0) {
            *(undefined4 *)(iVar6 + 0x5c) = 0;
          }
        }
        else {
          iVar12 = *(int *)(iVar6 + 0x58) + -10;
          *(int *)(iVar6 + 0x58) = iVar12;
          if (iVar12 < 0) {
            *(undefined4 *)(iVar6 + 0x58) = 0;
          }
        }
        goto LAB_0042ec9b;
      }
      fVar3 = (float)piVar15[2] - _DAT_005a84ac;
      piVar15[2] = (int)fVar3;
      if (fVar3 < _DAT_005a83e4) {
        piVar15[2] = 0;
        FUN_0042f0c0(param_1);
        return;
      }
      goto LAB_0042ed57;
    }
    if (iVar8 != 4) {
      if (iVar8 != 5) {
        return;
      }
      iVar8 = piVar15[8];
      if (iVar8 == 0) {
        fVar3 = (float)piVar15[2] + _DAT_005a83f4;
        param_1 = piVar15[1];
        iVar12 = param_1 + iVar14 * -2;
        piVar15[2] = (int)fVar3;
        fVar3 = fVar3 + (float)piVar15[3];
LAB_0042ed3c:
        if ((float)iVar12 < fVar3 != ((float)iVar12 == fVar3)) {
          piVar15[2] = (int)(((float)param_1 - (float)piVar15[3]) - (float)(iVar14 * 2));
        }
LAB_0042ed57:
        FUN_0042f0c0(iVar6);
        return;
      }
      goto LAB_0042ecec;
    }
    iVar8 = piVar15[8];
    if (iVar8 == 0) {
      fVar3 = (float)piVar15[2] + _DAT_005a84ac;
      param_1 = piVar15[1];
      iVar12 = param_1 + iVar14 * -2;
      piVar15[2] = (int)fVar3;
      fVar3 = fVar3 + (float)piVar15[3];
      goto LAB_0042ed3c;
    }
LAB_0042ec59:
    iVar6 = *(int *)(iVar8 + 0xc0);
    if (iVar12 == 1) {
      iVar12 = *(int *)(iVar6 + 0x5c) + 10;
      *(int *)(iVar6 + 0x5c) = iVar12;
      if (*(int *)(iVar6 + 100) <= iVar12 + *(int *)(iVar6 + 0x4c)) {
        *(int *)(iVar6 + 0x5c) = *(int *)(iVar6 + 100) - *(int *)(iVar6 + 0x4c);
      }
      goto LAB_0042ec9b;
    }
    iVar12 = *(int *)(iVar6 + 0x58) + 10;
  }
  *(int *)(iVar6 + 0x58) = iVar12;
  if (*(int *)(iVar6 + 0x68) <= iVar12 + *(int *)(iVar6 + 0x48)) {
    *(int *)(iVar6 + 0x58) = *(int *)(iVar6 + 0x68) - *(int *)(iVar6 + 0x48);
  }
LAB_0042ec9b:
  FUN_0042d230(piVar15[8],*piVar15);
  FUN_0042f0c0(piVar15[8]);
  return;
switchD_0042dd00_caseD_7:
  piVar15 = *(int **)(param_1 + 0xc0);
  if (*piVar15 == 1) {
    if ((*(int *)(param_1 + 0x4c) < param_4) && (param_4 < piVar15[5] + *(int *)(param_1 + 0x4c))) {
      iVar6 = piVar15[6];
      iVar12 = *(int *)(param_1 + 0x50);
      iVar8 = __ftol();
      iVar13 = iVar8 + iVar6 + iVar12;
      iVar14 = __ftol();
      iVar8 = piVar15[1];
      iVar14 = iVar14 + iVar6 + iVar12;
      iVar11 = (iVar8 - iVar6) + iVar12;
      if (param_5 < iVar12) {
        if (iVar12 + iVar6 <= param_5) goto LAB_0042de8e;
        if (iVar13 <= param_5) goto LAB_0042debe;
        if (iVar14 <= param_5) goto LAB_0042dedb;
        if (param_5 < iVar11) goto LAB_0042e2a1;
      }
      else {
        if (param_5 < iVar12 + iVar6) {
          if (piVar15[8] != 0) {
            iVar6 = *(int *)(piVar15[8] + 0xc0);
            iVar12 = *(int *)(iVar6 + 0x5c) + -1;
            *(int *)(iVar6 + 0x5c) = iVar12;
            if (iVar12 < 0) {
              *(undefined4 *)(iVar6 + 0x5c) = 0;
            }
            uVar19 = 1;
LAB_0042e08d:
            FUN_0042d230(piVar15[8],uVar19);
            FUN_0042f0c0(piVar15[8]);
            piVar15[7] = 1;
            goto LAB_0042e2a8;
          }
LAB_0042e0ae:
          fVar3 = (float)piVar15[2] - _DAT_005a83f4;
          piVar15[2] = (int)fVar3;
          if (fVar3 < _DAT_005a83e4) {
            piVar15[2] = 0;
          }
          FUN_0042f0c0(param_1);
          piVar15[7] = 1;
          goto LAB_0042e2a8;
        }
LAB_0042de8e:
        if (param_5 < iVar13) {
          if (piVar15[8] == 0) {
LAB_0042e12b:
            fVar3 = (float)piVar15[2] - _DAT_005a84ac;
            piVar15[2] = (int)fVar3;
            if (fVar3 < _DAT_005a83e4) {
              piVar15[2] = 0;
            }
            FUN_0042f0c0(param_1);
            piVar15[7] = 2;
            goto LAB_0042e2a8;
          }
          iVar6 = *(int *)(piVar15[8] + 0xc0);
          iVar12 = *(int *)(iVar6 + 0x5c) + -10;
          *(int *)(iVar6 + 0x5c) = iVar12;
          if (iVar12 < 0) {
            *(undefined4 *)(iVar6 + 0x5c) = 0;
          }
          uVar19 = 1;
LAB_0042e10a:
          FUN_0042d230(piVar15[8],uVar19);
          FUN_0042f0c0(piVar15[8]);
          piVar15[7] = 2;
          goto LAB_0042e2a8;
        }
LAB_0042debe:
        if (param_5 < iVar14) {
          piVar15[7] = 3;
          piVar15[4] = param_5 - iVar13;
          goto LAB_0042e2a8;
        }
LAB_0042dedb:
        if (param_5 < iVar11) {
          if (piVar15[8] == 0) {
            fVar3 = (float)piVar15[2] + _DAT_005a84ac;
            piVar15[2] = (int)fVar3;
            fVar3 = fVar3 + (float)piVar15[3];
            fVar4 = (float)(iVar8 + iVar6 * -2);
            if (fVar4 < fVar3 != (fVar4 == fVar3)) {
              fVar3 = ((float)iVar8 - (float)piVar15[3]) - (float)(iVar6 * 2);
LAB_0042e1ee:
              piVar15[2] = (int)fVar3;
            }
LAB_0042e1f1:
            FUN_0042f0c0(param_1);
            piVar15[7] = 4;
            goto LAB_0042e2a8;
          }
          iVar6 = *(int *)(piVar15[8] + 0xc0);
          iVar12 = *(int *)(iVar6 + 0x5c) + 10;
          *(int *)(iVar6 + 0x5c) = iVar12;
          if (*(int *)(iVar6 + 100) <= iVar12 + *(int *)(iVar6 + 0x4c)) {
            *(int *)(iVar6 + 0x5c) = *(int *)(iVar6 + 100) - *(int *)(iVar6 + 0x4c);
          }
          uVar19 = 1;
          goto LAB_0042df10;
        }
      }
      if (param_5 < iVar8 + iVar12) {
        if (piVar15[8] == 0) {
          fVar3 = (float)piVar15[2] + _DAT_005a83f4;
          piVar15[2] = (int)fVar3;
          fVar3 = fVar3 + (float)piVar15[3];
          fVar4 = (float)(iVar8 + iVar6 * -2);
          if (fVar4 < fVar3 != (fVar4 == fVar3)) {
            fVar3 = ((float)iVar8 - (float)piVar15[3]) - (float)(iVar6 * 2);
LAB_0042dfe2:
            piVar15[2] = (int)fVar3;
          }
LAB_0042dfe5:
          FUN_0042f0c0(param_1);
          piVar15[7] = 5;
          goto LAB_0042e2a8;
        }
        iVar6 = *(int *)(piVar15[8] + 0xc0);
        iVar12 = *(int *)(iVar6 + 0x5c) + 1;
        *(int *)(iVar6 + 0x5c) = iVar12;
        if (*(int *)(iVar6 + 100) <= iVar12 + *(int *)(iVar6 + 0x4c)) {
          *(int *)(iVar6 + 0x5c) = *(int *)(iVar6 + 100) - *(int *)(iVar6 + 0x4c);
        }
        uVar19 = 1;
        goto LAB_0042e247;
      }
    }
LAB_0042e2a1:
    piVar15[7] = -1;
  }
  else {
    if ((param_5 <= *(int *)(param_1 + 0x50)) || (piVar15[6] + *(int *)(param_1 + 0x50) <= param_5))
    goto LAB_0042e2a1;
    iVar6 = piVar15[5];
    iVar12 = *(int *)(param_1 + 0x4c);
    iVar8 = __ftol();
    iVar13 = iVar8 + iVar6 + iVar12;
    iVar14 = __ftol();
    iVar8 = piVar15[1];
    iVar14 = iVar14 + iVar6 + iVar12;
    iVar11 = (iVar8 - iVar6) + iVar12;
    if (iVar12 <= param_4) {
      if (param_4 < iVar12 + iVar6) {
        if (piVar15[8] != 0) {
          iVar6 = *(int *)(piVar15[8] + 0xc0);
          iVar12 = *(int *)(iVar6 + 0x58) + -1;
          *(int *)(iVar6 + 0x58) = iVar12;
          if (iVar12 < 0) {
            *(undefined4 *)(iVar6 + 0x58) = 0;
          }
          uVar19 = 2;
          goto LAB_0042e08d;
        }
        goto LAB_0042e0ae;
      }
LAB_0042e0e7:
      if (param_4 < iVar13) {
        if (piVar15[8] == 0) goto LAB_0042e12b;
        iVar6 = *(int *)(piVar15[8] + 0xc0);
        iVar12 = *(int *)(iVar6 + 0x58) + -10;
        *(int *)(iVar6 + 0x58) = iVar12;
        if (iVar12 < 0) {
          *(undefined4 *)(iVar6 + 0x58) = 0;
        }
        uVar19 = 2;
        goto LAB_0042e10a;
      }
LAB_0042e164:
      if (param_4 < iVar14) {
        piVar15[7] = 3;
        piVar15[4] = param_4 - iVar13;
        goto LAB_0042e2a8;
      }
LAB_0042e181:
      if (iVar11 <= param_4) goto LAB_0042e214;
      if (piVar15[8] == 0) {
        fVar3 = (float)piVar15[2] + _DAT_005a84ac;
        piVar15[2] = (int)fVar3;
        fVar3 = fVar3 + (float)piVar15[3];
        fVar4 = (float)(iVar8 + iVar6 * -2);
        if (fVar4 < fVar3 != (fVar4 == fVar3)) {
          fVar3 = ((float)iVar8 - (float)piVar15[3]) - (float)(iVar6 * 2);
          goto LAB_0042e1ee;
        }
        goto LAB_0042e1f1;
      }
      iVar6 = *(int *)(piVar15[8] + 0xc0);
      iVar12 = *(int *)(iVar6 + 0x58) + 10;
      *(int *)(iVar6 + 0x58) = iVar12;
      if (*(int *)(iVar6 + 0x68) <= iVar12 + *(int *)(iVar6 + 0x48)) {
        *(int *)(iVar6 + 0x58) = *(int *)(iVar6 + 0x68) - *(int *)(iVar6 + 0x48);
      }
      uVar19 = 2;
LAB_0042df10:
      FUN_0042d230(piVar15[8],uVar19);
      FUN_0042f0c0(piVar15[8]);
      piVar15[7] = 4;
      goto LAB_0042e2a8;
    }
    if (iVar12 + iVar6 <= param_4) goto LAB_0042e0e7;
    if (iVar13 <= param_4) goto LAB_0042e164;
    if (iVar14 <= param_4) goto LAB_0042e181;
    if (param_4 < iVar11) goto LAB_0042e2a1;
LAB_0042e214:
    if (iVar8 + iVar12 <= param_4) goto LAB_0042e2a1;
    if (piVar15[8] == 0) {
      fVar3 = (float)piVar15[2] + _DAT_005a83f4;
      piVar15[2] = (int)fVar3;
      fVar3 = fVar3 + (float)piVar15[3];
      fVar4 = (float)(iVar8 + iVar6 * -2);
      if (fVar4 < fVar3 != (fVar4 == fVar3)) {
        fVar3 = ((float)iVar8 - (float)piVar15[3]) - (float)(iVar6 * 2);
        goto LAB_0042dfe2;
      }
      goto LAB_0042dfe5;
    }
    iVar6 = *(int *)(piVar15[8] + 0xc0);
    iVar12 = *(int *)(iVar6 + 0x58) + 1;
    *(int *)(iVar6 + 0x58) = iVar12;
    if (*(int *)(iVar6 + 0x68) <= iVar12 + *(int *)(iVar6 + 0x48)) {
      *(int *)(iVar6 + 0x58) = *(int *)(iVar6 + 0x68) - *(int *)(iVar6 + 0x48);
    }
    uVar19 = 2;
LAB_0042e247:
    FUN_0042d230(piVar15[8],uVar19);
    FUN_0042f0c0(piVar15[8]);
    piVar15[7] = 5;
  }
LAB_0042e2a8:
  if (piVar15[7] < 1) {
    return;
  }
  DAT_005d5b14 = param_1;
  FUN_00404460(5,0x41200000,&LAB_0042edb0,1);
  return;
}

