/* Original Meteor.exe static export @ 005318a0; original sample not executed. */
/* XREF 0052e90a UNCONDITIONAL_CALL */
/* XREF 0052eaf4 UNCONDITIONAL_CALL */
/* XREF 0052d8f9 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double * FUN_005318a0(uint param_1,uint param_2,uint param_3,undefined4 param_4,undefined4 param_5,
                     double *param_6)

{
  float fVar1;
  float fVar2;
  double dVar3;
  ulonglong uVar4;
  double dVar5;
  byte bVar6;
  undefined1 uVar7;
  undefined2 uVar8;
  double *pdVar9;
  uint uVar10;
  undefined1 *puVar11;
  int iVar12;
  double *pdVar13;
  double *pdVar14;
  float fVar15;
  uint uVar16;
  undefined1 *puVar17;
  undefined2 *puVar18;
  float *pfVar19;
  undefined2 *puVar20;
  uint uVar21;
  undefined1 *puVar22;
  double *pdVar23;
  float *pfVar24;
  undefined1 *puVar25;
  int iVar26;
  double *pdVar27;
  uint local_18;
  int local_14;
  
  pdVar27 = (double *)0x0;
  if ((param_1 == 0) || (param_6 == (double *)0x0)) {
    FUN_00530d00(0x509);
    return (double *)0x0;
  }
  pdVar9 = (double *)FUN_005347d0(param_1,param_4,param_5,param_6);
  if (pdVar9 == (double *)0x0) {
    return (double *)0x0;
  }
  uVar10 = FUN_00530f00(param_5);
  uVar10 = uVar10 & 0xff;
  bVar6 = FUN_00530f00(param_4);
  uVar4 = (ulonglong)param_1 / (ulonglong)bVar6;
  puVar11 = (undefined1 *)uVar4;
  if (param_3 == param_2) {
    uVar10 = (int)puVar11 * uVar10;
    pdVar27 = (double *)FUN_00530d80(uVar10);
    if (pdVar27 == (double *)0x0) {
      return (double *)0x0;
    }
    pdVar23 = pdVar9;
    pdVar14 = pdVar27;
    for (uVar21 = uVar10 >> 2; uVar21 != 0; uVar21 = uVar21 - 1) {
      *(float *)pdVar14 = *(float *)pdVar23;
      pdVar23 = (double *)((int)pdVar23 + 4);
      pdVar14 = (double *)((int)pdVar14 + 4);
    }
    for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined1 *)pdVar14 = *(undefined1 *)pdVar23;
      pdVar23 = (double *)((int)pdVar23 + 1);
      pdVar14 = (double *)((int)pdVar14 + 1);
    }
    if (pdVar9 != param_6) {
      FUN_00530db0(pdVar9);
    }
    return pdVar27;
  }
  if (param_2 < 0x190b) {
    if (param_2 == 0x190a) {
      if (param_3 < 0x190a) {
        if (param_3 == 0x1909) {
          pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 >> 1);
          if (pdVar27 == (double *)0x0) goto LAB_00534216;
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar27;
            if (puVar11 != (undefined1 *)0x0) {
              do {
                puVar25 = puVar22 + (int)pdVar9;
                puVar22 = puVar22 + 2;
                *(undefined1 *)pdVar23 = *puVar25;
                pdVar23 = (double *)((int)pdVar23 + 1);
              } while (puVar22 < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar27;
            if (puVar11 != (undefined1 *)0x0) {
              do {
                iVar12 = (int)puVar22 * 2;
                puVar22 = puVar22 + 2;
                *(undefined2 *)pdVar23 = *(undefined2 *)((int)pdVar9 + iVar12);
                pdVar23 = (double *)((int)pdVar23 + 2);
              } while (puVar22 < puVar11);
            }
            break;
          case 0x1404:
          case 0x1405:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar27;
            if (puVar11 != (undefined1 *)0x0) {
              do {
                iVar12 = (int)puVar22 * 4;
                puVar22 = puVar22 + 2;
                *(float *)pdVar23 = *(float *)((int)pdVar9 + iVar12);
                pdVar23 = (double *)((int)pdVar23 + 4);
              } while (puVar22 < puVar11);
            }
            break;
          case 0x1406:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar27;
            if (puVar11 != (undefined1 *)0x0) {
              do {
                iVar12 = (int)puVar22 * 4;
                puVar22 = puVar22 + 2;
                *(float *)pdVar23 = *(float *)((int)pdVar9 + iVar12);
                pdVar23 = (double *)((int)pdVar23 + 4);
              } while (puVar22 < puVar11);
            }
            break;
          case 0x140a:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar27;
            if (puVar11 != (undefined1 *)0x0) {
              do {
                pdVar14 = pdVar9 + (int)puVar22;
                puVar22 = puVar22 + 2;
                *(float *)pdVar23 = *(float *)pdVar14;
                *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar9 + (int)puVar22 * 8 + -0xc);
                pdVar23 = pdVar23 + 1;
              } while (puVar22 < puVar11);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        iVar12 = param_3 - 0x1907;
      }
      else {
        iVar12 = param_3 - 0x80e0;
      }
      if (iVar12 == 0) {
        pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10 >> 1) * 3);
        if (pdVar27 != (double *)0x0) {
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar27;
            if (puVar11 != (undefined1 *)0x0) {
              do {
                uVar10 = 0;
                do {
                  uVar21 = uVar10 + 1;
                  *(undefined1 *)((int)pdVar23 + uVar10) = puVar22[(int)pdVar9];
                  uVar10 = uVar21;
                } while (uVar21 < 3);
                puVar22 = puVar22 + 2;
                pdVar23 = (double *)((int)pdVar23 + 3);
              } while (puVar22 < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            if (puVar11 != (undefined1 *)0x0) {
              iVar12 = ((uint)(puVar11 + -1) >> 1) + 1;
              pdVar23 = pdVar27;
              pdVar14 = pdVar9;
              do {
                iVar26 = 3;
                do {
                  *(undefined2 *)pdVar23 = *(undefined2 *)pdVar14;
                  pdVar23 = (double *)((int)pdVar23 + 2);
                  iVar26 = iVar26 + -1;
                } while (iVar26 != 0);
                pdVar14 = (double *)((int)pdVar14 + 4);
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
            break;
          case 0x1404:
          case 0x1405:
            if (puVar11 != (undefined1 *)0x0) {
              iVar12 = ((uint)(puVar11 + -1) >> 1) + 1;
              pdVar23 = pdVar27;
              pdVar14 = pdVar9;
              do {
                iVar26 = 3;
                do {
                  *(float *)pdVar23 = *(float *)pdVar14;
                  pdVar23 = (double *)((int)pdVar23 + 4);
                  iVar26 = iVar26 + -1;
                } while (iVar26 != 0);
                pdVar14 = pdVar14 + 1;
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
            break;
          case 0x1406:
            if (puVar11 != (undefined1 *)0x0) {
              iVar12 = ((uint)(puVar11 + -1) >> 1) + 1;
              pdVar23 = pdVar27;
              pdVar14 = pdVar9;
              do {
                iVar26 = 3;
                do {
                  *(float *)pdVar23 = *(float *)pdVar14;
                  pdVar23 = (double *)((int)pdVar23 + 4);
                  iVar26 = iVar26 + -1;
                } while (iVar26 != 0);
                pdVar14 = pdVar14 + 1;
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
            break;
          case 0x140a:
            if (puVar11 != (undefined1 *)0x0) {
              iVar12 = ((uint)(puVar11 + -1) >> 1) + 1;
              pdVar23 = pdVar27;
              pdVar14 = pdVar9;
              do {
                iVar26 = 3;
                do {
                  *(float *)pdVar23 = *(float *)pdVar14;
                  *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + 4);
                  pdVar23 = pdVar23 + 1;
                  iVar26 = iVar26 + -1;
                } while (iVar26 != 0);
                pdVar14 = pdVar14 + 2;
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
      }
      else if (iVar12 == 1) {
        pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10 >> 1) << 2);
        if (pdVar27 != (double *)0x0) {
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            if (puVar11 != (undefined1 *)0x0) {
              puVar22 = (undefined1 *)((int)pdVar27 + 3);
              puVar25 = (undefined1 *)((int)pdVar9 + 1);
              do {
                uVar10 = 0;
                do {
                  puVar22[uVar10 - 3] = puVar25[-1];
                  uVar10 = uVar10 + 1;
                } while (uVar10 < 3);
                uVar7 = *puVar25;
                puVar25 = puVar25 + 2;
                *puVar22 = uVar7;
                puVar22 = puVar22 + 4;
              } while (puVar25 + (-1 - (int)pdVar9) < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            if (puVar11 != (undefined1 *)0x0) {
              local_14 = ((uint)(puVar11 + -1) >> 1) + 1;
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              do {
                iVar12 = 3;
                pdVar13 = pdVar14;
                do {
                  *(undefined2 *)pdVar13 = *(undefined2 *)pdVar23;
                  pdVar13 = (double *)((int)pdVar13 + 2);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                puVar20 = (undefined2 *)((int)pdVar23 + 2);
                pdVar23 = (double *)((int)pdVar23 + 4);
                *(undefined2 *)((int)pdVar14 + 6) = *puVar20;
                pdVar14 = pdVar14 + 1;
                local_14 = local_14 + -1;
              } while (local_14 != 0);
            }
            break;
          case 0x1404:
          case 0x1405:
            if (puVar11 != (undefined1 *)0x0) {
              local_14 = ((uint)(puVar11 + -1) >> 1) + 1;
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              do {
                iVar12 = 3;
                pdVar13 = pdVar14;
                do {
                  *(float *)pdVar13 = *(float *)pdVar23;
                  pdVar13 = (double *)((int)pdVar13 + 4);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                pfVar24 = (float *)((int)pdVar23 + 4);
                pdVar23 = pdVar23 + 1;
                *(float *)((int)pdVar14 + 0xc) = *pfVar24;
                pdVar14 = pdVar14 + 2;
                local_14 = local_14 + -1;
              } while (local_14 != 0);
            }
            break;
          case 0x1406:
            if (puVar11 != (undefined1 *)0x0) {
              local_14 = ((uint)(puVar11 + -1) >> 1) + 1;
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              do {
                iVar12 = 3;
                pdVar13 = pdVar14;
                do {
                  *(float *)pdVar13 = *(float *)pdVar23;
                  pdVar13 = (double *)((int)pdVar13 + 4);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                pfVar24 = (float *)((int)pdVar23 + 4);
                pdVar23 = pdVar23 + 1;
                *(float *)((int)pdVar14 + 0xc) = *pfVar24;
                pdVar14 = pdVar14 + 2;
                local_14 = local_14 + -1;
              } while (local_14 != 0);
            }
            break;
          case 0x140a:
            if (puVar11 != (undefined1 *)0x0) {
              local_14 = ((uint)(puVar11 + -1) >> 1) + 1;
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              do {
                iVar12 = 3;
                pdVar13 = pdVar14;
                do {
                  *(float *)pdVar13 = *(float *)pdVar23;
                  *(float *)((int)pdVar13 + 4) = *(float *)((int)pdVar23 + 4);
                  pdVar13 = pdVar13 + 1;
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                *(float *)(pdVar14 + 3) = *(float *)(pdVar23 + 1);
                *(float *)((int)pdVar14 + 0x1c) = *(float *)((int)pdVar23 + 0xc);
                pdVar14 = pdVar14 + 4;
                local_14 = local_14 + -1;
                pdVar23 = pdVar23 + 2;
              } while (local_14 != 0);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
      }
      else {
        FUN_00530d00(0x510);
      }
      goto LAB_00534216;
    }
    if (param_2 != 0x1907) {
      if (param_2 != 0x1908) {
        if (param_2 != 0x1909) {
switchD_00531aeb_caseD_1407:
          if (pdVar9 != param_6) {
            FUN_00530db0(pdVar9);
          }
          return pdVar27;
        }
        if (param_3 < 0x190b) {
          if (param_3 == 0x190a) {
            pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 * 2);
            if (pdVar27 == (double *)0x0) goto LAB_00534216;
            switch(param_5) {
            case 0x1400:
            case 0x1401:
              puVar22 = (undefined1 *)0x0;
              if (puVar11 != (undefined1 *)0x0) {
                do {
                  uVar7 = puVar22[(int)pdVar9];
                  *(undefined1 *)((int)pdVar27 + (int)puVar22 * 2 + 1) = 0xff;
                  *(undefined1 *)((int)pdVar27 + (int)puVar22 * 2) = uVar7;
                  puVar22 = puVar22 + 1;
                } while (puVar22 < puVar11);
              }
              break;
            case 0x1402:
            case 0x1403:
              puVar22 = (undefined1 *)0x0;
              if (puVar11 != (undefined1 *)0x0) {
                do {
                  uVar8 = *(undefined2 *)((int)pdVar9 + (int)puVar22 * 2);
                  *(undefined2 *)((int)pdVar27 + (int)puVar22 * 4 + 2) = 0xffff;
                  *(undefined2 *)((int)pdVar27 + (int)puVar22 * 4) = uVar8;
                  puVar22 = puVar22 + 1;
                } while (puVar22 < puVar11);
              }
              break;
            case 0x1404:
            case 0x1405:
              puVar22 = (undefined1 *)0x0;
              if (puVar11 != (undefined1 *)0x0) {
                do {
                  fVar15 = *(float *)((int)pdVar9 + (int)puVar22 * 4);
                  *(undefined4 *)((int)pdVar27 + (int)puVar22 * 8 + 4) = 0xffffffff;
                  *(float *)(pdVar27 + (int)puVar22) = fVar15;
                  puVar22 = puVar22 + 1;
                } while (puVar22 < puVar11);
              }
              break;
            case 0x1406:
              puVar22 = (undefined1 *)0x0;
              if (puVar11 != (undefined1 *)0x0) {
                do {
                  fVar15 = *(float *)((int)pdVar9 + (int)puVar22 * 4);
                  *(undefined4 *)((int)pdVar27 + (int)puVar22 * 8 + 4) = 0x3f800000;
                  *(float *)(pdVar27 + (int)puVar22) = fVar15;
                  puVar22 = puVar22 + 1;
                } while (puVar22 < puVar11);
              }
              break;
            case 0x140a:
              puVar22 = (undefined1 *)0x0;
              pdVar23 = pdVar27;
              if (puVar11 != (undefined1 *)0x0) {
                do {
                  pdVar14 = pdVar9 + (int)puVar22;
                  puVar22 = puVar22 + 1;
                  *(float *)pdVar23 = *(float *)pdVar14;
                  *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar9 + (int)puVar22 * 8 + -4);
                  *(float *)(pdVar23 + 1) = 0.0;
                  *(float *)((int)pdVar23 + 0xc) = 1.875;
                  pdVar23 = pdVar23 + 2;
                } while (puVar22 < puVar11);
              }
            }
            goto switchD_00531aeb_caseD_1407;
          }
          iVar12 = param_3 - 0x1907;
        }
        else {
          iVar12 = param_3 - 0x80e0;
        }
        if (iVar12 == 0) {
          pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 * 3);
          if (pdVar27 != (double *)0x0) {
            switch(param_5) {
            case 0x1400:
            case 0x1401:
              puVar22 = (undefined1 *)0x0;
              pdVar23 = pdVar27;
              if (puVar11 != (undefined1 *)0x0) {
                do {
                  uVar10 = 0;
                  do {
                    uVar21 = uVar10 + 1;
                    *(undefined1 *)((int)pdVar23 + uVar10) = puVar22[(int)pdVar9];
                    uVar10 = uVar21;
                  } while (uVar21 < 3);
                  puVar22 = puVar22 + 1;
                  pdVar23 = (double *)((int)pdVar23 + 3);
                } while (puVar22 < puVar11);
              }
              break;
            case 0x1402:
            case 0x1403:
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              for (; puVar11 != (undefined1 *)0x0; puVar11 = puVar11 + -1) {
                iVar12 = 3;
                do {
                  *(undefined2 *)pdVar14 = *(undefined2 *)pdVar23;
                  pdVar14 = (double *)((int)pdVar14 + 2);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                pdVar23 = (double *)((int)pdVar23 + 2);
              }
              break;
            case 0x1404:
            case 0x1405:
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              for (; puVar11 != (undefined1 *)0x0; puVar11 = puVar11 + -1) {
                iVar12 = 3;
                do {
                  *(float *)pdVar14 = *(float *)pdVar23;
                  pdVar14 = (double *)((int)pdVar14 + 4);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                pdVar23 = (double *)((int)pdVar23 + 4);
              }
              break;
            case 0x1406:
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              for (; puVar11 != (undefined1 *)0x0; puVar11 = puVar11 + -1) {
                iVar12 = 3;
                do {
                  *(float *)pdVar14 = *(float *)pdVar23;
                  pdVar14 = (double *)((int)pdVar14 + 4);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                pdVar23 = (double *)((int)pdVar23 + 4);
              }
              break;
            case 0x140a:
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              for (; puVar11 != (undefined1 *)0x0; puVar11 = puVar11 + -1) {
                iVar12 = 3;
                do {
                  *(float *)pdVar14 = *(float *)pdVar23;
                  *(float *)((int)pdVar14 + 4) = *(float *)((int)pdVar23 + 4);
                  pdVar14 = pdVar14 + 1;
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                pdVar23 = pdVar23 + 1;
              }
            }
            goto switchD_00531aeb_caseD_1407;
          }
        }
        else if (iVar12 == 1) {
          pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 * 4);
          if (pdVar27 != (double *)0x0) {
            switch(param_5) {
            case 0x1400:
            case 0x1401:
              puVar22 = (undefined1 *)0x0;
              if (puVar11 != (undefined1 *)0x0) {
                puVar25 = (undefined1 *)((int)pdVar27 + 3);
                do {
                  uVar10 = 0;
                  do {
                    uVar21 = uVar10 + 1;
                    puVar25[uVar10 - 3] = puVar22[(int)pdVar9];
                    uVar10 = uVar21;
                  } while (uVar21 < 3);
                  *puVar25 = 0xff;
                  puVar22 = puVar22 + 1;
                  puVar25 = puVar25 + 4;
                } while (puVar22 < puVar11);
              }
              break;
            case 0x1402:
            case 0x1403:
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              for (; puVar11 != (undefined1 *)0x0; puVar11 = puVar11 + -1) {
                iVar12 = 3;
                pdVar13 = pdVar14;
                do {
                  *(undefined2 *)pdVar13 = *(undefined2 *)pdVar23;
                  pdVar13 = (double *)((int)pdVar13 + 2);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                *(undefined2 *)((int)pdVar14 + 6) = 0xffff;
                pdVar23 = (double *)((int)pdVar23 + 2);
                pdVar14 = pdVar14 + 1;
              }
              break;
            case 0x1404:
            case 0x1405:
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              for (; puVar11 != (undefined1 *)0x0; puVar11 = puVar11 + -1) {
                iVar12 = 3;
                pdVar13 = pdVar14;
                do {
                  *(float *)pdVar13 = *(float *)pdVar23;
                  pdVar13 = (double *)((int)pdVar13 + 4);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                *(float *)((int)pdVar14 + 0xc) = -NAN;
                pdVar23 = (double *)((int)pdVar23 + 4);
                pdVar14 = pdVar14 + 2;
              }
              break;
            case 0x1406:
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              for (; puVar11 != (undefined1 *)0x0; puVar11 = puVar11 + -1) {
                iVar12 = 3;
                pdVar13 = pdVar14;
                do {
                  *(float *)pdVar13 = *(float *)pdVar23;
                  pdVar13 = (double *)((int)pdVar13 + 4);
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                *(float *)((int)pdVar14 + 0xc) = 1.0;
                pdVar23 = (double *)((int)pdVar23 + 4);
                pdVar14 = pdVar14 + 2;
              }
              break;
            case 0x140a:
              pdVar23 = pdVar9;
              pdVar14 = pdVar27;
              for (; puVar11 != (undefined1 *)0x0; puVar11 = puVar11 + -1) {
                iVar12 = 3;
                pdVar13 = pdVar14;
                do {
                  *(float *)pdVar13 = *(float *)pdVar23;
                  *(float *)((int)pdVar13 + 4) = *(float *)((int)pdVar23 + 4);
                  pdVar13 = pdVar13 + 1;
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                *(float *)(pdVar14 + 3) = 0.0;
                *(float *)((int)pdVar14 + 0x1c) = 1.875;
                pdVar23 = pdVar23 + 1;
                pdVar14 = pdVar14 + 4;
              }
            }
            goto switchD_00531aeb_caseD_1407;
          }
        }
        else {
          FUN_00530d00(0x510);
        }
        goto LAB_00534216;
      }
      if (param_3 < 0x190b) {
        if (param_3 == 0x190a) {
          pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10 >> 2) * 2);
          if (pdVar27 != (double *)0x0) {
            uVar10 = (uint)puVar11 >> 2;
            puVar11 = (undefined1 *)(uVar10 * 2);
            switch(param_5) {
            case 0x1400:
            case 0x1401:
              if (uVar10 != 0) {
                pdVar23 = pdVar9;
                puVar22 = (undefined1 *)((int)pdVar27 + 1);
                do {
                  uVar10 = 0;
                  do {
                    uVar10 = uVar10 + 4;
                  } while (uVar10 < 0xc);
                  uVar7 = __ftol();
                  puVar22[-1] = uVar7;
                  puVar25 = puVar22 + 2;
                  *puVar22 = *(undefined1 *)((int)pdVar23 + 3);
                  pdVar23 = (double *)((int)pdVar23 + 4);
                  puVar22 = puVar25;
                } while (puVar25 + (-1 - (int)pdVar27) < puVar11);
              }
              break;
            case 0x1402:
            case 0x1403:
              puVar22 = (undefined1 *)0x0;
              pdVar23 = pdVar9;
              if (uVar10 != 0) {
                do {
                  uVar10 = 0;
                  do {
                    uVar10 = uVar10 + 4;
                  } while (uVar10 < 0xc);
                  uVar8 = __ftol();
                  *(undefined2 *)((int)pdVar27 + (int)puVar22 * 2) = uVar8;
                  *(undefined2 *)((int)pdVar27 + (int)puVar22 * 2 + 2) =
                       *(undefined2 *)((int)pdVar23 + 6);
                  puVar22 = puVar22 + 2;
                  pdVar23 = pdVar23 + 1;
                } while (puVar22 < puVar11);
              }
              break;
            case 0x1404:
            case 0x1405:
              puVar22 = (undefined1 *)0x0;
              pdVar23 = pdVar9;
              if (uVar10 != 0) {
                do {
                  uVar10 = 0;
                  do {
                    uVar10 = uVar10 + 4;
                  } while (uVar10 < 0xc);
                  fVar15 = (float)__ftol();
                  *(float *)((int)pdVar27 + (int)puVar22 * 4) = fVar15;
                  *(float *)((int)pdVar27 + (int)puVar22 * 4 + 4) = *(float *)((int)pdVar23 + 0xc);
                  puVar22 = puVar22 + 2;
                  pdVar23 = pdVar23 + 2;
                } while (puVar22 < puVar11);
              }
              break;
            case 0x1406:
              puVar22 = (undefined1 *)0x0;
              pdVar23 = pdVar9;
              if (uVar10 != 0) {
                do {
                  fVar15 = (float)_DAT_005a84b8;
                  uVar10 = 0;
                  pdVar14 = pdVar23;
                  do {
                    pfVar24 = (float *)((int)&DAT_005ad460 + uVar10);
                    fVar1 = *(float *)pdVar14;
                    uVar10 = uVar10 + 4;
                    pdVar14 = (double *)((int)pdVar14 + 4);
                    fVar15 = *pfVar24 * fVar1 + fVar15;
                  } while (uVar10 < 0xc);
                  *(float *)((int)pdVar27 + (int)puVar22 * 4) = fVar15;
                  *(float *)((int)pdVar27 + (int)puVar22 * 4 + 4) = *(float *)((int)pdVar23 + 0xc);
                  puVar22 = puVar22 + 2;
                  pdVar23 = pdVar23 + 2;
                } while (puVar22 < puVar11);
              }
              break;
            case 0x140a:
              puVar22 = (undefined1 *)0x0;
              pdVar23 = pdVar9;
              if (uVar10 != 0) {
                do {
                  uVar10 = 0;
                  pdVar14 = pdVar23;
                  dVar5 = _DAT_005a84b8;
                  do {
                    pfVar24 = (float *)((int)&DAT_005ad460 + uVar10);
                    dVar3 = *pdVar14;
                    uVar10 = uVar10 + 4;
                    pdVar14 = pdVar14 + 1;
                    dVar5 = (double)*pfVar24 * dVar3 + dVar5;
                  } while (uVar10 < 0xc);
                  pdVar27[(int)puVar22] = dVar5;
                  *(float *)(pdVar27 + (int)(puVar22 + 1)) = *(float *)(pdVar23 + 3);
                  *(float *)((int)pdVar27 + (int)puVar22 * 8 + 0xc) =
                       *(float *)((int)pdVar23 + 0x1c);
                  puVar22 = puVar22 + 2;
                  pdVar23 = pdVar23 + 4;
                } while (puVar22 < puVar11);
              }
            }
            goto switchD_00531aeb_caseD_1407;
          }
          goto LAB_00534216;
        }
        if (param_3 == 0x1907) {
          pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 * 3 >> 2);
          if (pdVar27 != (double *)0x0) {
            switch(param_5) {
            case 0x1400:
            case 0x1401:
              if (puVar11 != (undefined1 *)0x0) {
                puVar22 = (undefined1 *)((int)pdVar27 + 1);
                puVar25 = (undefined1 *)((int)pdVar9 + 1);
                do {
                  puVar17 = puVar25 + 4;
                  puVar22[-1] = puVar25[-1];
                  *puVar22 = *puVar25;
                  puVar22[1] = puVar25[1];
                  puVar22 = puVar22 + 3;
                  puVar25 = puVar17;
                } while (puVar17 + (-1 - (int)pdVar9) < puVar11);
              }
              break;
            case 0x1402:
            case 0x1403:
              if (puVar11 != (undefined1 *)0x0) {
                pfVar24 = (float *)((int)pdVar27 + 4);
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pfVar19 = (float *)((int)pdVar9 + 4);
                do {
                  *(undefined2 *)(pfVar24 + -1) = *(undefined2 *)(pfVar19 + -1);
                  *(undefined2 *)((int)pfVar24 + -2) = *(undefined2 *)((int)pfVar19 + -2);
                  *(undefined2 *)pfVar24 = *(undefined2 *)pfVar19;
                  pfVar24 = (float *)((int)pfVar24 + 6);
                  iVar12 = iVar12 + -1;
                  pfVar19 = pfVar19 + 2;
                } while (iVar12 != 0);
              }
              break;
            case 0x1404:
            case 0x1405:
              if (puVar11 != (undefined1 *)0x0) {
                pdVar23 = pdVar27 + 1;
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pdVar14 = pdVar9 + 1;
                do {
                  *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                  *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                  *(float *)pdVar23 = *(float *)pdVar14;
                  pdVar23 = (double *)((int)pdVar23 + 0xc);
                  iVar12 = iVar12 + -1;
                  pdVar14 = pdVar14 + 2;
                } while (iVar12 != 0);
              }
              break;
            case 0x1406:
              if (puVar11 != (undefined1 *)0x0) {
                pdVar23 = pdVar27 + 1;
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pdVar14 = pdVar9 + 1;
                do {
                  *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                  *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                  *(float *)pdVar23 = *(float *)pdVar14;
                  pdVar23 = (double *)((int)pdVar23 + 0xc);
                  iVar12 = iVar12 + -1;
                  pdVar14 = pdVar14 + 2;
                } while (iVar12 != 0);
              }
              break;
            case 0x140a:
              if (puVar11 != (undefined1 *)0x0) {
                pdVar23 = pdVar27 + 2;
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pdVar14 = pdVar9 + 2;
                do {
                  *(float *)(pdVar23 + -2) = *(float *)(pdVar14 + -2);
                  *(float *)((int)pdVar23 + -0xc) = *(float *)((int)pdVar14 + -0xc);
                  *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                  *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                  *(float *)pdVar23 = *(float *)pdVar14;
                  *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + 4);
                  pdVar23 = pdVar23 + 3;
                  iVar12 = iVar12 + -1;
                  pdVar14 = pdVar14 + 4;
                } while (iVar12 != 0);
              }
            }
            goto switchD_00531aeb_caseD_1407;
          }
          goto LAB_00534216;
        }
        if (param_3 == 0x1909) {
          pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 >> 2);
          if (pdVar27 != (double *)0x0) {
            uVar10 = (uint)puVar11 >> 2;
            switch(param_5) {
            case 0x1400:
            case 0x1401:
              uVar21 = 0;
              if (uVar10 != 0) {
                do {
                  uVar16 = 0;
                  do {
                    uVar16 = uVar16 + 4;
                  } while (uVar16 < 0xc);
                  uVar7 = __ftol();
                  *(undefined1 *)(uVar21 + (int)pdVar27) = uVar7;
                  uVar21 = uVar21 + 1;
                } while (uVar21 < uVar10);
              }
              break;
            case 0x1402:
            case 0x1403:
              uVar21 = 0;
              if (uVar10 != 0) {
                do {
                  uVar16 = 0;
                  do {
                    uVar16 = uVar16 + 4;
                  } while (uVar16 < 0xc);
                  uVar8 = __ftol();
                  *(undefined2 *)((int)pdVar27 + uVar21 * 2) = uVar8;
                  uVar21 = uVar21 + 1;
                } while (uVar21 < uVar10);
              }
              break;
            case 0x1404:
            case 0x1405:
              uVar21 = 0;
              if (uVar10 != 0) {
                do {
                  uVar16 = 0;
                  do {
                    uVar16 = uVar16 + 4;
                  } while (uVar16 < 0xc);
                  fVar15 = (float)__ftol();
                  *(float *)((int)pdVar27 + uVar21 * 4) = fVar15;
                  uVar21 = uVar21 + 1;
                } while (uVar21 < uVar10);
              }
              break;
            case 0x1406:
              uVar21 = 0;
              pdVar23 = pdVar9;
              if (uVar10 != 0) {
                do {
                  fVar15 = (float)_DAT_005a84b8;
                  uVar16 = 0;
                  pdVar14 = pdVar23;
                  do {
                    pfVar24 = (float *)((int)&DAT_005ad460 + uVar16);
                    fVar1 = *(float *)pdVar14;
                    uVar16 = uVar16 + 4;
                    pdVar14 = (double *)((int)pdVar14 + 4);
                    fVar15 = *pfVar24 * fVar1 + fVar15;
                  } while (uVar16 < 0xc);
                  *(float *)((int)pdVar27 + uVar21 * 4) = fVar15;
                  uVar21 = uVar21 + 1;
                  pdVar23 = pdVar23 + 2;
                } while (uVar21 < uVar10);
              }
              break;
            case 0x140a:
              uVar21 = 0;
              pdVar23 = pdVar9;
              if (uVar10 != 0) {
                do {
                  uVar16 = 0;
                  pdVar14 = pdVar23;
                  dVar5 = _DAT_005a84b8;
                  do {
                    pfVar24 = (float *)((int)&DAT_005ad460 + uVar16);
                    dVar3 = *pdVar14;
                    uVar16 = uVar16 + 4;
                    pdVar14 = pdVar14 + 1;
                    dVar5 = (double)*pfVar24 * dVar3 + dVar5;
                  } while (uVar16 < 0xc);
                  pdVar27[uVar21] = dVar5;
                  uVar21 = uVar21 + 1;
                  pdVar23 = pdVar23 + 4;
                } while (uVar21 < uVar10);
              }
            }
            goto switchD_00531aeb_caseD_1407;
          }
          goto LAB_00534216;
        }
      }
      else {
        if (param_3 == 0x80e0) {
          pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 * 3 >> 2);
          if (pdVar27 != (double *)0x0) {
            switch(param_5) {
            case 0x1400:
            case 0x1401:
              if (puVar11 != (undefined1 *)0x0) {
                puVar22 = (undefined1 *)((int)pdVar27 + 1);
                puVar25 = (undefined1 *)((int)pdVar9 + 1);
                do {
                  puVar17 = puVar25 + 4;
                  puVar22[-1] = puVar25[1];
                  *puVar22 = *puVar25;
                  puVar22[1] = puVar25[-1];
                  puVar22 = puVar22 + 3;
                  puVar25 = puVar17;
                } while (puVar17 + (-1 - (int)pdVar9) < puVar11);
              }
              break;
            case 0x1402:
            case 0x1403:
              if (puVar11 != (undefined1 *)0x0) {
                pfVar24 = (float *)((int)pdVar27 + 4);
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                puVar20 = (undefined2 *)((int)pdVar9 + 2);
                do {
                  *(undefined2 *)(pfVar24 + -1) = puVar20[1];
                  *(undefined2 *)((int)pfVar24 + -2) = *puVar20;
                  *(undefined2 *)pfVar24 = puVar20[-1];
                  pfVar24 = (float *)((int)pfVar24 + 6);
                  iVar12 = iVar12 + -1;
                  puVar20 = puVar20 + 4;
                } while (iVar12 != 0);
              }
              break;
            case 0x1404:
            case 0x1405:
              if (puVar11 != (undefined1 *)0x0) {
                pdVar23 = pdVar27 + 1;
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pfVar24 = (float *)((int)pdVar9 + 4);
                do {
                  *(float *)(pdVar23 + -1) = pfVar24[1];
                  *(float *)((int)pdVar23 + -4) = *pfVar24;
                  *(float *)pdVar23 = pfVar24[-1];
                  pdVar23 = (double *)((int)pdVar23 + 0xc);
                  iVar12 = iVar12 + -1;
                  pfVar24 = pfVar24 + 4;
                } while (iVar12 != 0);
              }
              break;
            case 0x1406:
              if (puVar11 != (undefined1 *)0x0) {
                pdVar23 = pdVar27 + 1;
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pfVar24 = (float *)((int)pdVar9 + 4);
                do {
                  *(float *)(pdVar23 + -1) = pfVar24[1];
                  *(float *)((int)pdVar23 + -4) = *pfVar24;
                  *(float *)pdVar23 = pfVar24[-1];
                  pdVar23 = (double *)((int)pdVar23 + 0xc);
                  iVar12 = iVar12 + -1;
                  pfVar24 = pfVar24 + 4;
                } while (iVar12 != 0);
              }
              break;
            case 0x140a:
              if (puVar11 != (undefined1 *)0x0) {
                pdVar23 = pdVar27 + 2;
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pdVar14 = pdVar9 + 1;
                do {
                  *(float *)(pdVar23 + -2) = *(float *)(pdVar14 + 1);
                  *(float *)((int)pdVar23 + -0xc) = *(float *)((int)pdVar14 + 0xc);
                  *(float *)(pdVar23 + -1) = *(float *)pdVar14;
                  *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + 4);
                  *(float *)pdVar23 = *(float *)(pdVar14 + -1);
                  *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + -4);
                  pdVar23 = pdVar23 + 3;
                  iVar12 = iVar12 + -1;
                  pdVar14 = pdVar14 + 4;
                } while (iVar12 != 0);
              }
            }
            goto switchD_00531aeb_caseD_1407;
          }
          goto LAB_00534216;
        }
        if (param_3 == 0x80e1) {
          pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10);
          if (pdVar27 != (double *)0x0) {
            switch(param_5) {
            case 0x1400:
            case 0x1401:
              if (puVar11 != (undefined1 *)0x0) {
                puVar22 = (undefined1 *)((int)pdVar27 + 1);
                puVar25 = (undefined1 *)((int)pdVar9 + 3);
                do {
                  puVar22[-1] = puVar22[((int)pdVar9 - (int)pdVar27) + 1];
                  *puVar22 = puVar22[(int)pdVar9 - (int)pdVar27];
                  puVar22[1] = puVar25[-3];
                  puVar22[2] = *puVar25;
                  puVar22 = puVar22 + 4;
                  puVar25 = puVar25 + 4;
                } while (puVar22 + (-1 - (int)pdVar27) < puVar11);
              }
              break;
            case 0x1402:
            case 0x1403:
              if (puVar11 != (undefined1 *)0x0) {
                puVar20 = (undefined2 *)((int)pdVar27 + 6);
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                puVar18 = (undefined2 *)((int)pdVar9 + 2);
                do {
                  puVar20[-3] = puVar18[1];
                  *(undefined2 *)((int)pdVar27 + (-8 - (int)pdVar9) + (int)(puVar18 + 4)) = *puVar18
                  ;
                  puVar20[-1] = puVar18[-1];
                  *puVar20 = puVar18[2];
                  puVar20 = puVar20 + 4;
                  iVar12 = iVar12 + -1;
                  puVar18 = puVar18 + 4;
                } while (iVar12 != 0);
              }
              break;
            case 0x1404:
            case 0x1405:
              if (puVar11 != (undefined1 *)0x0) {
                pfVar24 = (float *)((int)pdVar27 + 0xc);
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pfVar19 = (float *)((int)pdVar9 + 4);
                do {
                  pfVar24[-3] = pfVar19[1];
                  *(float *)((int)pdVar27 + (-0x10 - (int)pdVar9) + (int)(pfVar19 + 4)) = *pfVar19;
                  pfVar24[-1] = pfVar19[-1];
                  *pfVar24 = pfVar19[2];
                  pfVar24 = pfVar24 + 4;
                  iVar12 = iVar12 + -1;
                  pfVar19 = pfVar19 + 4;
                } while (iVar12 != 0);
              }
              break;
            case 0x1406:
              if (puVar11 != (undefined1 *)0x0) {
                pfVar24 = (float *)((int)pdVar27 + 0xc);
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pfVar19 = (float *)((int)pdVar9 + 4);
                do {
                  pfVar24[-3] = pfVar19[1];
                  *(float *)((int)pdVar27 + (-0x10 - (int)pdVar9) + (int)(pfVar19 + 4)) = *pfVar19;
                  pfVar24[-1] = pfVar19[-1];
                  *pfVar24 = pfVar19[2];
                  pfVar24 = pfVar24 + 4;
                  iVar12 = iVar12 + -1;
                  pfVar19 = pfVar19 + 4;
                } while (iVar12 != 0);
              }
              break;
            case 0x140a:
              if (puVar11 != (undefined1 *)0x0) {
                pdVar23 = pdVar27 + 3;
                iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
                pdVar14 = pdVar9 + 1;
                do {
                  pdVar13 = pdVar14 + 4;
                  *(float *)(pdVar23 + -3) = *(float *)(pdVar14 + 1);
                  *(float *)((int)pdVar23 + -0x14) = *(float *)((int)pdVar14 + 0xc);
                  *(float *)((int)pdVar27 + (-0x20 - (int)pdVar9) + (int)pdVar13) =
                       *(float *)pdVar14;
                  *(float *)((int)pdVar27 + (-0x1c - (int)pdVar9) + (int)pdVar13) =
                       *(float *)((int)pdVar14 + 4);
                  *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                  *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                  *(float *)pdVar23 = *(float *)(pdVar14 + 2);
                  *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + 0x14);
                  pdVar23 = pdVar23 + 4;
                  iVar12 = iVar12 + -1;
                  pdVar14 = pdVar13;
                } while (iVar12 != 0);
              }
            }
            goto switchD_00531aeb_caseD_1407;
          }
          goto LAB_00534216;
        }
      }
      FUN_00530d00(0x510);
      goto LAB_00534216;
    }
    if (param_3 < 0x190b) {
      if (param_3 == 0x190a) {
        pdVar27 = (double *)
                  FUN_00530d80((uint)((ulonglong)((int)puVar11 * uVar10) * 0xaaaaaaab >> 0x20) &
                               0xfffffffe);
        if (pdVar27 != (double *)0x0) {
          uVar10 = (uint)(uVar4 / 3);
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            local_18 = 0;
            if (uVar10 != 0) {
              do {
                uVar21 = 0;
                do {
                  uVar21 = uVar21 + 4;
                } while (uVar21 < 0xc);
                uVar7 = __ftol();
                *(undefined1 *)((int)pdVar27 + local_18 * 2) = uVar7;
                *(undefined1 *)((int)pdVar27 + local_18 * 2 + 1) = 0xff;
                local_18 = local_18 + 1;
              } while (local_18 < uVar10);
            }
            break;
          case 0x1402:
          case 0x1403:
            uVar21 = 0;
            if (uVar10 != 0) {
              do {
                uVar16 = 0;
                do {
                  uVar16 = uVar16 + 4;
                } while (uVar16 < 0xc);
                uVar8 = __ftol();
                *(undefined2 *)((int)pdVar27 + uVar21 * 4) = uVar8;
                *(undefined2 *)((int)pdVar27 + uVar21 * 4 + 2) = 0xffff;
                uVar21 = uVar21 + 1;
              } while (uVar21 < uVar10);
            }
            break;
          case 0x1404:
          case 0x1405:
            uVar21 = 0;
            if (uVar10 != 0) {
              do {
                uVar16 = 0;
                do {
                  uVar16 = uVar16 + 4;
                } while (uVar16 < 0xc);
                fVar15 = (float)__ftol();
                *(float *)(pdVar27 + uVar21) = fVar15;
                *(undefined4 *)((int)pdVar27 + uVar21 * 8 + 4) = 0xffffffff;
                uVar21 = uVar21 + 1;
              } while (uVar21 < uVar10);
            }
            break;
          case 0x1406:
            uVar21 = 0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                uVar16 = 0;
                fVar15 = _DAT_005a83e4;
                do {
                  pfVar24 = (float *)((int)&DAT_005ad460 + uVar16);
                  fVar1 = *(float *)pdVar23;
                  uVar16 = uVar16 + 4;
                  pdVar23 = (double *)((int)pdVar23 + 4);
                  fVar15 = *pfVar24 * fVar1 + fVar15;
                } while (uVar16 < 0xc);
                *(float *)(pdVar27 + uVar21) = fVar15;
                *(undefined4 *)((int)pdVar27 + uVar21 * 8 + 4) = 0x3f800000;
                uVar21 = uVar21 + 1;
              } while (uVar21 < uVar10);
            }
            break;
          case 0x140a:
            pdVar23 = pdVar9;
            pdVar14 = pdVar27;
            for (; uVar10 != 0; uVar10 = uVar10 - 1) {
              uVar21 = 0;
              dVar5 = _DAT_005a84b8;
              do {
                pfVar24 = (float *)((int)&DAT_005ad460 + uVar21);
                dVar3 = *pdVar23;
                uVar21 = uVar21 + 4;
                pdVar23 = pdVar23 + 1;
                dVar5 = (double)*pfVar24 * dVar3 + dVar5;
              } while (uVar21 < 0xc);
              *pdVar14 = dVar5;
              *(float *)(pdVar14 + 1) = 0.0;
              *(float *)((int)pdVar14 + 0xc) = 1.875;
              pdVar14 = pdVar14 + 2;
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
      if (param_3 == 0x1908) {
        pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10 * 4) / 3);
        if (pdVar27 != (double *)0x0) {
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            if (puVar11 != (undefined1 *)0x0) {
              puVar22 = (undefined1 *)((int)pdVar27 + 1);
              puVar25 = (undefined1 *)((int)pdVar9 + 1);
              do {
                puVar17 = puVar25 + 3;
                puVar22[-1] = puVar25[-1];
                *puVar22 = *puVar25;
                puVar22[1] = puVar25[1];
                puVar22[2] = 0xff;
                puVar22 = puVar22 + 4;
                puVar25 = puVar17;
              } while (puVar17 + (-1 - (int)pdVar9) < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            if (puVar11 != (undefined1 *)0x0) {
              pfVar24 = (float *)((int)pdVar27 + 4);
              iVar12 = (uint)(puVar11 + -1) / 3 + 1;
              pfVar19 = (float *)((int)pdVar9 + 4);
              do {
                *(undefined2 *)(pfVar24 + -1) = *(undefined2 *)(pfVar19 + -1);
                *(undefined2 *)((int)pfVar24 + -2) = *(undefined2 *)((int)pfVar19 + -2);
                *(undefined2 *)pfVar24 = *(undefined2 *)pfVar19;
                *(undefined2 *)((int)pfVar24 + 2) = 0xffff;
                pfVar24 = pfVar24 + 2;
                iVar12 = iVar12 + -1;
                pfVar19 = (float *)((int)pfVar19 + 6);
              } while (iVar12 != 0);
            }
            break;
          case 0x1404:
          case 0x1405:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 1;
              iVar12 = (uint)(puVar11 + -1) / 3 + 1;
              pdVar14 = pdVar9 + 1;
              do {
                *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                *(float *)pdVar23 = *(float *)pdVar14;
                *(float *)((int)pdVar23 + 4) = -NAN;
                pdVar23 = pdVar23 + 2;
                iVar12 = iVar12 + -1;
                pdVar14 = (double *)((int)pdVar14 + 0xc);
              } while (iVar12 != 0);
            }
            break;
          case 0x1406:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 1;
              iVar12 = (uint)(puVar11 + -1) / 3 + 1;
              pdVar14 = pdVar9 + 1;
              do {
                *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                *(float *)pdVar23 = *(float *)pdVar14;
                *(float *)((int)pdVar23 + 4) = 1.0;
                pdVar23 = pdVar23 + 2;
                iVar12 = iVar12 + -1;
                pdVar14 = (double *)((int)pdVar14 + 0xc);
              } while (iVar12 != 0);
            }
            break;
          case 0x140a:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 2;
              iVar12 = (uint)(puVar11 + -1) / 3 + 1;
              pdVar14 = pdVar9 + 2;
              do {
                *(float *)(pdVar23 + -2) = *(float *)(pdVar14 + -2);
                *(float *)((int)pdVar23 + -0xc) = *(float *)((int)pdVar14 + -0xc);
                *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                *(float *)pdVar23 = *(float *)pdVar14;
                *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + 4);
                *(float *)(pdVar23 + 1) = 0.0;
                *(float *)((int)pdVar23 + 0xc) = 1.875;
                pdVar23 = pdVar23 + 4;
                iVar12 = iVar12 + -1;
                pdVar14 = pdVar14 + 3;
              } while (iVar12 != 0);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
      if (param_3 == 0x1909) {
        pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10) / 3);
        if (pdVar27 != (double *)0x0) {
          uVar10 = (uint)(uVar4 / 3);
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            local_18 = 0;
            if (uVar10 != 0) {
              do {
                uVar21 = 0;
                do {
                  uVar21 = uVar21 + 4;
                } while (uVar21 < 0xc);
                uVar7 = __ftol();
                *(undefined1 *)(local_18 + (int)pdVar27) = uVar7;
                local_18 = local_18 + 1;
              } while (local_18 < uVar10);
            }
            break;
          case 0x1402:
          case 0x1403:
            local_18 = 0;
            if (uVar10 != 0) {
              do {
                uVar21 = 0;
                do {
                  uVar21 = uVar21 + 4;
                } while (uVar21 < 0xc);
                uVar8 = __ftol();
                *(undefined2 *)((int)pdVar27 + local_18 * 2) = uVar8;
                local_18 = local_18 + 1;
              } while (local_18 < uVar10);
            }
            break;
          case 0x1404:
          case 0x1405:
            local_18 = 0;
            if (uVar10 != 0) {
              do {
                uVar21 = 0;
                do {
                  uVar21 = uVar21 + 4;
                } while (uVar21 < 0xc);
                fVar15 = (float)__ftol();
                *(float *)((int)pdVar27 + local_18 * 4) = fVar15;
                local_18 = local_18 + 1;
              } while (local_18 < uVar10);
            }
            break;
          case 0x1406:
            uVar21 = 0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                uVar16 = 0;
                fVar15 = _DAT_005a83e4;
                do {
                  pfVar24 = (float *)((int)&DAT_005ad460 + uVar16);
                  fVar1 = *(float *)pdVar23;
                  uVar16 = uVar16 + 4;
                  pdVar23 = (double *)((int)pdVar23 + 4);
                  fVar15 = *pfVar24 * fVar1 + fVar15;
                } while (uVar16 < 0xc);
                *(float *)((int)pdVar27 + uVar21 * 4) = fVar15;
                uVar21 = uVar21 + 1;
              } while (uVar21 < uVar10);
            }
            break;
          case 0x140a:
            uVar21 = 0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                uVar16 = 0;
                dVar5 = _DAT_005a84b8;
                do {
                  pfVar24 = (float *)((int)&DAT_005ad460 + uVar16);
                  dVar3 = *pdVar23;
                  uVar16 = uVar16 + 4;
                  pdVar23 = pdVar23 + 1;
                  dVar5 = (double)*pfVar24 * dVar3 + dVar5;
                } while (uVar16 < 0xc);
                pdVar27[uVar21] = dVar5;
                uVar21 = uVar21 + 1;
              } while (uVar21 < uVar10);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
    }
    else {
      if (param_3 == 0x80e0) {
        pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10);
        if (pdVar27 != (double *)0x0) {
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            if (puVar11 != (undefined1 *)0x0) {
              puVar22 = (undefined1 *)((int)pdVar27 + 1);
              pdVar23 = pdVar9;
              do {
                puVar22[-1] = puVar22[((int)pdVar9 - (int)pdVar27) + 1];
                *puVar22 = puVar22[(int)pdVar9 - (int)pdVar27];
                puVar22[1] = *(undefined1 *)pdVar23;
                puVar22 = puVar22 + 3;
                pdVar23 = (double *)((int)pdVar23 + 3);
              } while (puVar22 + (-1 - (int)pdVar27) < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            puVar22 = (undefined1 *)0x0;
            if (puVar11 != (undefined1 *)0x0) {
              puVar20 = (undefined2 *)((int)pdVar9 + 2);
              do {
                *(undefined2 *)((int)pdVar27 + (int)puVar22 * 2) = puVar20[1];
                *(undefined2 *)((int)pdVar27 + (-6 - (int)pdVar9) + (int)(puVar20 + 3)) = *puVar20;
                *(undefined2 *)((int)pdVar27 + (int)puVar22 * 2 + 4) = puVar20[-1];
                puVar22 = puVar22 + 3;
                puVar20 = puVar20 + 3;
              } while (puVar22 < puVar11);
            }
            break;
          case 0x1404:
          case 0x1405:
            puVar22 = (undefined1 *)0x0;
            if (puVar11 != (undefined1 *)0x0) {
              pfVar24 = (float *)((int)pdVar9 + 4);
              do {
                *(float *)((int)pdVar27 + (int)puVar22 * 4) = pfVar24[1];
                *(float *)((int)pdVar27 + (-0xc - (int)pdVar9) + (int)(pfVar24 + 3)) = *pfVar24;
                *(float *)((int)pdVar27 + (int)puVar22 * 4 + 8) = pfVar24[-1];
                puVar22 = puVar22 + 3;
                pfVar24 = pfVar24 + 3;
              } while (puVar22 < puVar11);
            }
            break;
          case 0x1406:
            puVar22 = (undefined1 *)0x0;
            if (puVar11 != (undefined1 *)0x0) {
              pfVar24 = (float *)((int)pdVar9 + 4);
              do {
                *(float *)((int)pdVar27 + (int)puVar22 * 4) = pfVar24[1];
                *(float *)((int)pdVar27 + (-0xc - (int)pdVar9) + (int)(pfVar24 + 3)) = *pfVar24;
                *(float *)((int)pdVar27 + (int)puVar22 * 4 + 8) = pfVar24[-1];
                puVar22 = puVar22 + 3;
                pfVar24 = pfVar24 + 3;
              } while (puVar22 < puVar11);
            }
            break;
          case 0x140a:
            puVar22 = (undefined1 *)0x0;
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar9 + 1;
              do {
                pdVar14 = pdVar23 + 3;
                *(float *)(pdVar27 + (int)puVar22) = *(float *)(pdVar23 + 1);
                *(float *)((int)pdVar27 + (int)puVar22 * 8 + 4) = *(float *)((int)pdVar23 + 0xc);
                *(float *)((int)pdVar27 + (-0x18 - (int)pdVar9) + (int)pdVar14) = *(float *)pdVar23;
                *(float *)((int)pdVar27 + (-0x14 - (int)pdVar9) + (int)pdVar14) =
                     *(float *)((int)pdVar23 + 4);
                *(float *)(pdVar27 + (int)(puVar22 + 2)) = *(float *)(pdVar23 + -1);
                *(float *)((int)pdVar27 + (int)puVar22 * 8 + 0x14) = *(float *)((int)pdVar23 + -4);
                puVar22 = puVar22 + 3;
                pdVar23 = pdVar14;
              } while (puVar22 < puVar11);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
      if (param_3 == 0x80e1) {
        pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10 * 4) / 3);
        if (pdVar27 != (double *)0x0) {
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            if (puVar11 != (undefined1 *)0x0) {
              puVar22 = (undefined1 *)((int)pdVar27 + 1);
              puVar25 = (undefined1 *)((int)pdVar9 + 1);
              do {
                puVar17 = puVar25 + 3;
                puVar22[-1] = puVar25[1];
                *puVar22 = *puVar25;
                puVar22[1] = puVar25[-1];
                puVar22[2] = 0xff;
                puVar22 = puVar22 + 4;
                puVar25 = puVar17;
              } while (puVar17 + (-1 - (int)pdVar9) < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            if (puVar11 != (undefined1 *)0x0) {
              pfVar24 = (float *)((int)pdVar27 + 4);
              iVar12 = (uint)(puVar11 + -1) / 3 + 1;
              puVar20 = (undefined2 *)((int)pdVar9 + 2);
              do {
                *(undefined2 *)(pfVar24 + -1) = puVar20[1];
                *(undefined2 *)((int)pfVar24 + -2) = *puVar20;
                *(undefined2 *)pfVar24 = puVar20[-1];
                *(undefined2 *)((int)pfVar24 + 2) = 0xffff;
                pfVar24 = pfVar24 + 2;
                iVar12 = iVar12 + -1;
                puVar20 = puVar20 + 3;
              } while (iVar12 != 0);
            }
            break;
          case 0x1404:
          case 0x1405:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 1;
              iVar12 = (uint)(puVar11 + -1) / 3 + 1;
              pfVar24 = (float *)((int)pdVar9 + 4);
              do {
                *(float *)(pdVar23 + -1) = pfVar24[1];
                *(float *)((int)pdVar23 + -4) = *pfVar24;
                *(float *)pdVar23 = pfVar24[-1];
                *(float *)((int)pdVar23 + 4) = -NAN;
                pdVar23 = pdVar23 + 2;
                iVar12 = iVar12 + -1;
                pfVar24 = pfVar24 + 3;
              } while (iVar12 != 0);
            }
            break;
          case 0x1406:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 1;
              iVar12 = (uint)(puVar11 + -1) / 3 + 1;
              pfVar24 = (float *)((int)pdVar9 + 4);
              do {
                *(float *)(pdVar23 + -1) = pfVar24[1];
                *(float *)((int)pdVar23 + -4) = *pfVar24;
                *(float *)pdVar23 = pfVar24[-1];
                *(float *)((int)pdVar23 + 4) = 1.0;
                pdVar23 = pdVar23 + 2;
                iVar12 = iVar12 + -1;
                pfVar24 = pfVar24 + 3;
              } while (iVar12 != 0);
            }
            break;
          case 0x140a:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 2;
              iVar12 = (uint)(puVar11 + -1) / 3 + 1;
              pdVar14 = pdVar9 + 1;
              do {
                *(float *)(pdVar23 + -2) = *(float *)(pdVar14 + 1);
                *(float *)((int)pdVar23 + -0xc) = *(float *)((int)pdVar14 + 0xc);
                *(float *)(pdVar23 + -1) = *(float *)pdVar14;
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + 4);
                *(float *)pdVar23 = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + -4);
                *(float *)(pdVar23 + 1) = 0.0;
                *(float *)((int)pdVar23 + 0xc) = 1.875;
                pdVar23 = pdVar23 + 4;
                iVar12 = iVar12 + -1;
                pdVar14 = pdVar14 + 3;
              } while (iVar12 != 0);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
    }
    FUN_00530d00(0x510);
    goto LAB_00534216;
  }
  if (param_2 != 0x80e0) {
    if (param_2 != 0x80e1) goto switchD_00531aeb_caseD_1407;
    if (param_3 < 0x190a) {
      if (param_3 == 0x1909) {
        pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 >> 2);
        if (pdVar27 != (double *)0x0) {
          uVar10 = (uint)puVar11 >> 2;
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            local_18 = 0;
            if (uVar10 != 0) {
              do {
                uVar21 = 0;
                do {
                  uVar21 = uVar21 + 1;
                } while (uVar21 < 3);
                uVar7 = __ftol();
                *(undefined1 *)(local_18 + (int)pdVar27) = uVar7;
                local_18 = local_18 + 1;
              } while (local_18 < uVar10);
            }
            break;
          case 0x1402:
          case 0x1403:
            uVar21 = 0;
            if (uVar10 != 0) {
              do {
                iVar12 = 3;
                do {
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                uVar8 = __ftol();
                *(undefined2 *)((int)pdVar27 + uVar21 * 2) = uVar8;
                uVar21 = uVar21 + 1;
              } while (uVar21 < uVar10);
            }
            break;
          case 0x1404:
          case 0x1405:
            uVar21 = 0;
            if (uVar10 != 0) {
              do {
                iVar12 = 3;
                do {
                  iVar12 = iVar12 + -1;
                } while (iVar12 != 0);
                fVar15 = (float)__ftol();
                *(float *)((int)pdVar27 + uVar21 * 4) = fVar15;
                uVar21 = uVar21 + 1;
              } while (uVar21 < uVar10);
            }
            break;
          case 0x1406:
            uVar21 = 0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                fVar15 = (float)_DAT_005a84b8;
                pfVar24 = (float *)&DAT_005ad468;
                iVar12 = 3;
                pdVar14 = pdVar23;
                do {
                  fVar1 = *(float *)pdVar14;
                  fVar2 = *pfVar24;
                  pdVar14 = (double *)((int)pdVar14 + 4);
                  pfVar24 = pfVar24 + -1;
                  iVar12 = iVar12 + -1;
                  fVar15 = fVar1 * fVar2 + fVar15;
                } while (iVar12 != 0);
                *(float *)((int)pdVar27 + uVar21 * 4) = fVar15;
                uVar21 = uVar21 + 1;
                pdVar23 = pdVar23 + 2;
              } while (uVar21 < uVar10);
            }
            break;
          case 0x140a:
            uVar21 = 0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                pfVar24 = (float *)&DAT_005ad468;
                iVar12 = 3;
                pdVar14 = pdVar23;
                dVar5 = _DAT_005a84b8;
                do {
                  fVar15 = *pfVar24;
                  dVar3 = *pdVar14;
                  pdVar14 = pdVar14 + 1;
                  pfVar24 = pfVar24 + -1;
                  iVar12 = iVar12 + -1;
                  dVar5 = (double)fVar15 * dVar3 + dVar5;
                } while (iVar12 != 0);
                pdVar27[uVar21] = dVar5;
                uVar21 = uVar21 + 1;
                pdVar23 = pdVar23 + 4;
              } while (uVar21 < uVar10);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
      if (param_3 == 0x1907) {
        pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 * 3 >> 2);
        if (pdVar27 != (double *)0x0) {
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            if (puVar11 != (undefined1 *)0x0) {
              puVar22 = (undefined1 *)((int)pdVar27 + 1);
              puVar25 = (undefined1 *)((int)pdVar9 + 1);
              do {
                puVar17 = puVar25 + 4;
                puVar22[-1] = puVar25[1];
                *puVar22 = *puVar25;
                puVar22[1] = puVar25[-1];
                puVar22 = puVar22 + 3;
                puVar25 = puVar17;
              } while (puVar17 + (-1 - (int)pdVar9) < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            if (puVar11 != (undefined1 *)0x0) {
              pfVar24 = (float *)((int)pdVar27 + 4);
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              puVar20 = (undefined2 *)((int)pdVar9 + 2);
              do {
                *(undefined2 *)(pfVar24 + -1) = puVar20[1];
                *(undefined2 *)((int)pfVar24 + -2) = *puVar20;
                *(undefined2 *)pfVar24 = puVar20[-1];
                pfVar24 = (float *)((int)pfVar24 + 6);
                iVar12 = iVar12 + -1;
                puVar20 = puVar20 + 4;
              } while (iVar12 != 0);
            }
            break;
          case 0x1404:
          case 0x1405:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 1;
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pfVar24 = (float *)((int)pdVar9 + 4);
              do {
                *(float *)(pdVar23 + -1) = pfVar24[1];
                *(float *)((int)pdVar23 + -4) = *pfVar24;
                *(float *)pdVar23 = pfVar24[-1];
                pdVar23 = (double *)((int)pdVar23 + 0xc);
                iVar12 = iVar12 + -1;
                pfVar24 = pfVar24 + 4;
              } while (iVar12 != 0);
            }
            break;
          case 0x1406:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 1;
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pfVar24 = (float *)((int)pdVar9 + 4);
              do {
                *(float *)(pdVar23 + -1) = pfVar24[1];
                *(float *)((int)pdVar23 + -4) = *pfVar24;
                *(float *)pdVar23 = pfVar24[-1];
                pdVar23 = (double *)((int)pdVar23 + 0xc);
                iVar12 = iVar12 + -1;
                pfVar24 = pfVar24 + 4;
              } while (iVar12 != 0);
            }
            break;
          case 0x140a:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 2;
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pdVar14 = pdVar9 + 1;
              do {
                *(float *)(pdVar23 + -2) = *(float *)(pdVar14 + 1);
                *(float *)((int)pdVar23 + -0xc) = *(float *)((int)pdVar14 + 0xc);
                *(float *)(pdVar23 + -1) = *(float *)pdVar14;
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + 4);
                *(float *)pdVar23 = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + -4);
                pdVar23 = pdVar23 + 3;
                iVar12 = iVar12 + -1;
                pdVar14 = pdVar14 + 4;
              } while (iVar12 != 0);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
      if (param_3 == 0x1908) {
        pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10);
        if (pdVar27 != (double *)0x0) {
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            if (puVar11 != (undefined1 *)0x0) {
              puVar22 = (undefined1 *)((int)pdVar27 + 1);
              puVar25 = (undefined1 *)((int)pdVar9 + 3);
              do {
                puVar22[-1] = puVar22[((int)pdVar9 - (int)pdVar27) + 1];
                *puVar22 = puVar22[(int)pdVar9 - (int)pdVar27];
                puVar22[1] = puVar25[-3];
                puVar22[2] = *puVar25;
                puVar22 = puVar22 + 4;
                puVar25 = puVar25 + 4;
              } while (puVar22 + (-1 - (int)pdVar27) < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            if (puVar11 != (undefined1 *)0x0) {
              puVar20 = (undefined2 *)((int)pdVar27 + 6);
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              puVar18 = (undefined2 *)((int)pdVar9 + 2);
              do {
                puVar20[-3] = puVar18[1];
                *(undefined2 *)((int)pdVar27 + (-8 - (int)pdVar9) + (int)(puVar18 + 4)) = *puVar18;
                puVar20[-1] = puVar18[-1];
                *puVar20 = puVar18[2];
                puVar20 = puVar20 + 4;
                iVar12 = iVar12 + -1;
                puVar18 = puVar18 + 4;
              } while (iVar12 != 0);
            }
            break;
          case 0x1404:
          case 0x1405:
            if (puVar11 != (undefined1 *)0x0) {
              pfVar24 = (float *)((int)pdVar27 + 0xc);
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pfVar19 = (float *)((int)pdVar9 + 4);
              do {
                pfVar24[-3] = pfVar19[1];
                *(float *)((int)pdVar27 + (-0x10 - (int)pdVar9) + (int)(pfVar19 + 4)) = *pfVar19;
                pfVar24[-1] = pfVar19[-1];
                *pfVar24 = pfVar19[2];
                pfVar24 = pfVar24 + 4;
                iVar12 = iVar12 + -1;
                pfVar19 = pfVar19 + 4;
              } while (iVar12 != 0);
            }
            break;
          case 0x1406:
            if (puVar11 != (undefined1 *)0x0) {
              pfVar24 = (float *)((int)pdVar27 + 0xc);
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pfVar19 = (float *)((int)pdVar9 + 4);
              do {
                pfVar24[-3] = pfVar19[1];
                *(float *)((int)pdVar27 + (-0x10 - (int)pdVar9) + (int)(pfVar19 + 4)) = *pfVar19;
                pfVar24[-1] = pfVar19[-1];
                *pfVar24 = pfVar19[2];
                pfVar24 = pfVar24 + 4;
                iVar12 = iVar12 + -1;
                pfVar19 = pfVar19 + 4;
              } while (iVar12 != 0);
            }
            break;
          case 0x140a:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 3;
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pdVar14 = pdVar9 + 1;
              do {
                pdVar13 = pdVar14 + 4;
                *(float *)(pdVar23 + -3) = *(float *)(pdVar14 + 1);
                *(float *)((int)pdVar23 + -0x14) = *(float *)((int)pdVar14 + 0xc);
                *(float *)((int)pdVar27 + (-0x20 - (int)pdVar9) + (int)pdVar13) = *(float *)pdVar14;
                *(float *)((int)pdVar27 + (-0x1c - (int)pdVar9) + (int)pdVar13) =
                     *(float *)((int)pdVar14 + 4);
                *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                *(float *)pdVar23 = *(float *)(pdVar14 + 2);
                *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + 0x14);
                pdVar23 = pdVar23 + 4;
                iVar12 = iVar12 + -1;
                pdVar14 = pdVar13;
              } while (iVar12 != 0);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
    }
    else {
      if (param_3 == 0x190a) {
        pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10 >> 2) * 2);
        if (pdVar27 != (double *)0x0) {
          uVar10 = (uint)puVar11 >> 2;
          puVar11 = (undefined1 *)(uVar10 * 2);
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            if (uVar10 != 0) {
              pdVar23 = pdVar9;
              puVar22 = (undefined1 *)((int)pdVar27 + 1);
              do {
                uVar10 = 0;
                do {
                  uVar10 = uVar10 + 4;
                } while (uVar10 < 0xc);
                uVar7 = __ftol();
                puVar22[-1] = uVar7;
                puVar17 = puVar22 + 2;
                puVar25 = (undefined1 *)((int)pdVar23 + 3);
                pdVar23 = (double *)((int)pdVar23 + 4);
                *puVar22 = *puVar25;
                puVar22 = puVar17;
              } while (puVar17 + (-1 - (int)pdVar27) < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                uVar10 = 0;
                do {
                  uVar10 = uVar10 + 4;
                } while (uVar10 < 0xc);
                uVar8 = __ftol();
                *(undefined2 *)((int)pdVar27 + (int)puVar22 * 2) = uVar8;
                *(undefined2 *)((int)pdVar27 + (int)puVar22 * 2 + 2) =
                     *(undefined2 *)((int)pdVar23 + 6);
                puVar22 = puVar22 + 2;
                pdVar23 = pdVar23 + 1;
              } while (puVar22 < puVar11);
            }
            break;
          case 0x1404:
          case 0x1405:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                uVar10 = 0;
                do {
                  uVar10 = uVar10 + 4;
                } while (uVar10 < 0xc);
                fVar15 = (float)__ftol();
                *(float *)((int)pdVar27 + (int)puVar22 * 4) = fVar15;
                *(float *)((int)pdVar27 + (int)puVar22 * 4 + 4) = *(float *)((int)pdVar23 + 0xc);
                puVar22 = puVar22 + 2;
                pdVar23 = pdVar23 + 2;
              } while (puVar22 < puVar11);
            }
            break;
          case 0x1406:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                fVar15 = (float)_DAT_005a84b8;
                uVar10 = 0;
                pdVar14 = pdVar23;
                do {
                  pfVar24 = (float *)((int)&DAT_005ad460 + uVar10);
                  fVar1 = *(float *)pdVar14;
                  uVar10 = uVar10 + 4;
                  pdVar14 = (double *)((int)pdVar14 + 4);
                  fVar15 = *pfVar24 * fVar1 + fVar15;
                } while (uVar10 < 0xc);
                *(float *)((int)pdVar27 + (int)puVar22 * 4) = fVar15;
                *(float *)((int)pdVar27 + (int)puVar22 * 4 + 4) = *(float *)((int)pdVar23 + 0xc);
                puVar22 = puVar22 + 2;
                pdVar23 = pdVar23 + 2;
              } while (puVar22 < puVar11);
            }
            break;
          case 0x140a:
            puVar22 = (undefined1 *)0x0;
            pdVar23 = pdVar9;
            if (uVar10 != 0) {
              do {
                uVar10 = 0;
                pdVar14 = pdVar23;
                dVar5 = _DAT_005a84b8;
                do {
                  pfVar24 = (float *)((int)&DAT_005ad460 + uVar10);
                  dVar3 = *pdVar14;
                  uVar10 = uVar10 + 4;
                  pdVar14 = pdVar14 + 1;
                  dVar5 = (double)*pfVar24 * dVar3 + dVar5;
                } while (uVar10 < 0xc);
                pdVar27[(int)puVar22] = dVar5;
                *(float *)(pdVar27 + (int)(puVar22 + 1)) = *(float *)(pdVar23 + 3);
                *(float *)((int)pdVar27 + (int)puVar22 * 8 + 0xc) = *(float *)((int)pdVar23 + 0x1c);
                puVar22 = puVar22 + 2;
                pdVar23 = pdVar23 + 4;
              } while (puVar22 < puVar11);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
      if (param_3 == 0x80e0) {
        pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10 * 3 >> 2);
        if (pdVar27 != (double *)0x0) {
          switch(param_5) {
          case 0x1400:
          case 0x1401:
            if (puVar11 != (undefined1 *)0x0) {
              puVar22 = (undefined1 *)((int)pdVar27 + 1);
              puVar25 = (undefined1 *)((int)pdVar9 + 1);
              do {
                puVar17 = puVar25 + 4;
                puVar22[-1] = puVar25[-1];
                *puVar22 = *puVar25;
                puVar22[1] = puVar25[1];
                puVar22 = puVar22 + 3;
                puVar25 = puVar17;
              } while (puVar17 + (-1 - (int)pdVar9) < puVar11);
            }
            break;
          case 0x1402:
          case 0x1403:
            if (puVar11 != (undefined1 *)0x0) {
              pfVar24 = (float *)((int)pdVar27 + 4);
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pfVar19 = (float *)((int)pdVar9 + 4);
              do {
                *(undefined2 *)(pfVar24 + -1) = *(undefined2 *)(pfVar19 + -1);
                *(undefined2 *)((int)pfVar24 + -2) = *(undefined2 *)((int)pfVar19 + -2);
                *(undefined2 *)pfVar24 = *(undefined2 *)pfVar19;
                pfVar24 = (float *)((int)pfVar24 + 6);
                iVar12 = iVar12 + -1;
                pfVar19 = pfVar19 + 2;
              } while (iVar12 != 0);
            }
            break;
          case 0x1404:
          case 0x1405:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 1;
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pdVar14 = pdVar9 + 1;
              do {
                *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                *(float *)pdVar23 = *(float *)pdVar14;
                pdVar23 = (double *)((int)pdVar23 + 0xc);
                iVar12 = iVar12 + -1;
                pdVar14 = pdVar14 + 2;
              } while (iVar12 != 0);
            }
            break;
          case 0x1406:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 1;
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pdVar14 = pdVar9 + 1;
              do {
                *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                *(float *)pdVar23 = *(float *)pdVar14;
                pdVar23 = (double *)((int)pdVar23 + 0xc);
                iVar12 = iVar12 + -1;
                pdVar14 = pdVar14 + 2;
              } while (iVar12 != 0);
            }
            break;
          case 0x140a:
            if (puVar11 != (undefined1 *)0x0) {
              pdVar23 = pdVar27 + 2;
              iVar12 = ((uint)(puVar11 + -1) >> 2) + 1;
              pdVar14 = pdVar9 + 2;
              do {
                *(float *)(pdVar23 + -2) = *(float *)(pdVar14 + -2);
                *(float *)((int)pdVar23 + -0xc) = *(float *)((int)pdVar14 + -0xc);
                *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
                *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
                *(float *)pdVar23 = *(float *)pdVar14;
                *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + 4);
                pdVar23 = pdVar23 + 3;
                iVar12 = iVar12 + -1;
                pdVar14 = pdVar14 + 4;
              } while (iVar12 != 0);
            }
          }
          goto switchD_00531aeb_caseD_1407;
        }
        goto LAB_00534216;
      }
    }
    FUN_00530d00(0x510);
    goto LAB_00534216;
  }
  if (param_3 < 0x190a) {
    if (param_3 == 0x1909) {
      pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10) / 3);
      if (pdVar27 != (double *)0x0) {
        uVar10 = (uint)(uVar4 / 3);
        switch(param_5) {
        case 0x1400:
        case 0x1401:
          local_18 = 0;
          if (uVar10 != 0) {
            do {
              uVar21 = 0;
              do {
                uVar21 = uVar21 + 1;
              } while (uVar21 < 3);
              uVar7 = __ftol();
              *(undefined1 *)(local_18 + (int)pdVar27) = uVar7;
              local_18 = local_18 + 1;
            } while (local_18 < uVar10);
          }
          break;
        case 0x1402:
        case 0x1403:
          local_18 = 0;
          if (uVar10 != 0) {
            do {
              iVar12 = 3;
              do {
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
              uVar8 = __ftol();
              *(undefined2 *)((int)pdVar27 + local_18 * 2) = uVar8;
              local_18 = local_18 + 1;
            } while (local_18 < uVar10);
          }
          break;
        case 0x1404:
        case 0x1405:
          uVar21 = 0;
          if (uVar10 != 0) {
            do {
              iVar12 = 3;
              do {
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
              fVar15 = (float)__ftol();
              *(float *)((int)pdVar27 + uVar21 * 4) = fVar15;
              uVar21 = uVar21 + 1;
            } while (uVar21 < uVar10);
          }
          break;
        case 0x1406:
          uVar21 = 0;
          pdVar23 = pdVar9;
          if (uVar10 != 0) {
            do {
              fVar15 = (float)_DAT_005a84b8;
              pfVar24 = (float *)&DAT_005ad468;
              iVar12 = 3;
              do {
                fVar1 = *(float *)pdVar23;
                fVar2 = *pfVar24;
                pdVar23 = (double *)((int)pdVar23 + 4);
                pfVar24 = pfVar24 + -1;
                iVar12 = iVar12 + -1;
                fVar15 = fVar1 * fVar2 + fVar15;
              } while (iVar12 != 0);
              *(float *)((int)pdVar27 + uVar21 * 4) = fVar15;
              uVar21 = uVar21 + 1;
            } while (uVar21 < uVar10);
          }
          break;
        case 0x140a:
          uVar21 = 0;
          pdVar23 = pdVar9;
          if (uVar10 != 0) {
            do {
              pfVar24 = (float *)&DAT_005ad468;
              iVar12 = 3;
              dVar5 = _DAT_005a84b8;
              do {
                fVar15 = *pfVar24;
                dVar3 = *pdVar23;
                pdVar23 = pdVar23 + 1;
                pfVar24 = pfVar24 + -1;
                iVar12 = iVar12 + -1;
                dVar5 = (double)fVar15 * dVar3 + dVar5;
              } while (iVar12 != 0);
              pdVar27[uVar21] = dVar5;
              uVar21 = uVar21 + 1;
            } while (uVar21 < uVar10);
          }
        }
        goto switchD_00531aeb_caseD_1407;
      }
      goto LAB_00534216;
    }
    if (param_3 == 0x1907) {
      pdVar27 = (double *)FUN_00530d80((int)puVar11 * uVar10);
      if (pdVar27 != (double *)0x0) {
        switch(param_5) {
        case 0x1400:
        case 0x1401:
          if (puVar11 != (undefined1 *)0x0) {
            puVar22 = (undefined1 *)((int)pdVar27 + 1);
            pdVar23 = pdVar9;
            do {
              puVar22[-1] = puVar22[((int)pdVar9 - (int)pdVar27) + 1];
              *puVar22 = puVar22[(int)pdVar9 - (int)pdVar27];
              puVar22[1] = *(undefined1 *)pdVar23;
              puVar22 = puVar22 + 3;
              pdVar23 = (double *)((int)pdVar23 + 3);
            } while (puVar22 + (-1 - (int)pdVar27) < puVar11);
          }
          break;
        case 0x1402:
        case 0x1403:
          puVar22 = (undefined1 *)0x0;
          if (puVar11 != (undefined1 *)0x0) {
            puVar20 = (undefined2 *)((int)pdVar9 + 2);
            do {
              *(undefined2 *)((int)pdVar27 + (int)puVar22 * 2) = puVar20[1];
              *(undefined2 *)((int)pdVar27 + (-6 - (int)pdVar9) + (int)(puVar20 + 3)) = *puVar20;
              *(undefined2 *)((int)pdVar27 + (int)puVar22 * 2 + 4) = puVar20[-1];
              puVar22 = puVar22 + 3;
              puVar20 = puVar20 + 3;
            } while (puVar22 < puVar11);
          }
          break;
        case 0x1404:
        case 0x1405:
          puVar22 = (undefined1 *)0x0;
          if (puVar11 != (undefined1 *)0x0) {
            pfVar24 = (float *)((int)pdVar9 + 4);
            do {
              *(float *)((int)pdVar27 + (int)puVar22 * 4) = pfVar24[1];
              *(float *)((int)pdVar27 + (-0xc - (int)pdVar9) + (int)(pfVar24 + 3)) = *pfVar24;
              *(float *)((int)pdVar27 + (int)puVar22 * 4 + 8) = pfVar24[-1];
              puVar22 = puVar22 + 3;
              pfVar24 = pfVar24 + 3;
            } while (puVar22 < puVar11);
          }
          break;
        case 0x1406:
          puVar22 = (undefined1 *)0x0;
          if (puVar11 != (undefined1 *)0x0) {
            pfVar24 = (float *)((int)pdVar9 + 4);
            do {
              *(float *)((int)pdVar27 + (int)puVar22 * 4) = pfVar24[1];
              *(float *)((int)pdVar27 + (-0xc - (int)pdVar9) + (int)(pfVar24 + 3)) = *pfVar24;
              *(float *)((int)pdVar27 + (int)puVar22 * 4 + 8) = pfVar24[-1];
              puVar22 = puVar22 + 3;
              pfVar24 = pfVar24 + 3;
            } while (puVar22 < puVar11);
          }
          break;
        case 0x140a:
          puVar22 = (undefined1 *)0x0;
          if (puVar11 != (undefined1 *)0x0) {
            pdVar23 = pdVar9 + 1;
            do {
              pdVar14 = pdVar23 + 3;
              *(float *)(pdVar27 + (int)puVar22) = *(float *)(pdVar23 + 1);
              *(float *)((int)pdVar27 + (int)puVar22 * 8 + 4) = *(float *)((int)pdVar23 + 0xc);
              *(float *)((int)pdVar27 + (-0x18 - (int)pdVar9) + (int)pdVar14) = *(float *)pdVar23;
              *(float *)((int)pdVar27 + (-0x14 - (int)pdVar9) + (int)pdVar14) =
                   *(float *)((int)pdVar23 + 4);
              *(float *)(pdVar27 + (int)(puVar22 + 2)) = *(float *)(pdVar23 + -1);
              *(float *)((int)pdVar27 + (int)puVar22 * 8 + 0x14) = *(float *)((int)pdVar23 + -4);
              puVar22 = puVar22 + 3;
              pdVar23 = pdVar14;
            } while (puVar22 < puVar11);
          }
        }
        goto switchD_00531aeb_caseD_1407;
      }
      goto LAB_00534216;
    }
    if (param_3 == 0x1908) {
      pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10 * 4) / 3);
      if (pdVar27 != (double *)0x0) {
        switch(param_5) {
        case 0x1400:
        case 0x1401:
          if (puVar11 != (undefined1 *)0x0) {
            puVar22 = (undefined1 *)((int)pdVar27 + 1);
            puVar25 = (undefined1 *)((int)pdVar9 + 1);
            do {
              puVar17 = puVar25 + 3;
              puVar22[-1] = puVar25[1];
              *puVar22 = *puVar25;
              puVar22[1] = puVar25[-1];
              puVar22[2] = 0xff;
              puVar22 = puVar22 + 4;
              puVar25 = puVar17;
            } while (puVar17 + (-1 - (int)pdVar9) < puVar11);
          }
          break;
        case 0x1402:
        case 0x1403:
          if (puVar11 != (undefined1 *)0x0) {
            pfVar24 = (float *)((int)pdVar27 + 4);
            iVar12 = (uint)(puVar11 + -1) / 3 + 1;
            puVar20 = (undefined2 *)((int)pdVar9 + 2);
            do {
              *(undefined2 *)(pfVar24 + -1) = puVar20[1];
              *(undefined2 *)((int)pfVar24 + -2) = *puVar20;
              *(undefined2 *)pfVar24 = puVar20[-1];
              *(undefined2 *)((int)pfVar24 + 2) = 0xffff;
              pfVar24 = pfVar24 + 2;
              iVar12 = iVar12 + -1;
              puVar20 = puVar20 + 3;
            } while (iVar12 != 0);
          }
          break;
        case 0x1404:
        case 0x1405:
          if (puVar11 != (undefined1 *)0x0) {
            pdVar23 = pdVar27 + 1;
            iVar12 = (uint)(puVar11 + -1) / 3 + 1;
            pfVar24 = (float *)((int)pdVar9 + 4);
            do {
              *(float *)(pdVar23 + -1) = pfVar24[1];
              *(float *)((int)pdVar23 + -4) = *pfVar24;
              *(float *)pdVar23 = pfVar24[-1];
              *(float *)((int)pdVar23 + 4) = -NAN;
              pdVar23 = pdVar23 + 2;
              iVar12 = iVar12 + -1;
              pfVar24 = pfVar24 + 3;
            } while (iVar12 != 0);
          }
          break;
        case 0x1406:
          if (puVar11 != (undefined1 *)0x0) {
            pdVar23 = pdVar27 + 1;
            iVar12 = (uint)(puVar11 + -1) / 3 + 1;
            pfVar24 = (float *)((int)pdVar9 + 4);
            do {
              *(float *)(pdVar23 + -1) = pfVar24[1];
              *(float *)((int)pdVar23 + -4) = *pfVar24;
              *(float *)pdVar23 = pfVar24[-1];
              *(float *)((int)pdVar23 + 4) = 1.0;
              pdVar23 = pdVar23 + 2;
              iVar12 = iVar12 + -1;
              pfVar24 = pfVar24 + 3;
            } while (iVar12 != 0);
          }
          break;
        case 0x140a:
          if (puVar11 != (undefined1 *)0x0) {
            pdVar23 = pdVar27 + 2;
            iVar12 = (uint)(puVar11 + -1) / 3 + 1;
            pdVar14 = pdVar9 + 1;
            do {
              *(float *)(pdVar23 + -2) = *(float *)(pdVar14 + 1);
              *(float *)((int)pdVar23 + -0xc) = *(float *)((int)pdVar14 + 0xc);
              *(float *)(pdVar23 + -1) = *(float *)pdVar14;
              *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + 4);
              *(float *)pdVar23 = *(float *)(pdVar14 + -1);
              *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + -4);
              *(float *)(pdVar23 + 1) = 0.0;
              *(float *)((int)pdVar23 + 0xc) = 1.875;
              pdVar23 = pdVar23 + 4;
              iVar12 = iVar12 + -1;
              pdVar14 = pdVar14 + 3;
            } while (iVar12 != 0);
          }
        }
        goto switchD_00531aeb_caseD_1407;
      }
      goto LAB_00534216;
    }
  }
  else {
    if (param_3 == 0x190a) {
      pdVar27 = (double *)
                FUN_00530d80((uint)((ulonglong)((int)puVar11 * uVar10) * 0xaaaaaaab >> 0x20) &
                             0xfffffffe);
      if (pdVar27 != (double *)0x0) {
        uVar10 = (uint)(uVar4 / 3);
        switch(param_5) {
        case 0x1400:
        case 0x1401:
          local_18 = 0;
          if (uVar10 != 0) {
            do {
              uVar21 = 0;
              do {
                uVar21 = uVar21 + 4;
              } while (uVar21 < 0xc);
              uVar7 = __ftol();
              *(undefined1 *)((int)pdVar27 + local_18 * 2) = uVar7;
              *(undefined1 *)((int)pdVar27 + local_18 * 2 + 1) = 0xff;
              local_18 = local_18 + 1;
            } while (local_18 < uVar10);
          }
          break;
        case 0x1402:
        case 0x1403:
          uVar21 = 0;
          if (uVar10 != 0) {
            do {
              uVar16 = 0;
              do {
                uVar16 = uVar16 + 4;
              } while (uVar16 < 0xc);
              uVar8 = __ftol();
              *(undefined2 *)((int)pdVar27 + uVar21 * 4) = uVar8;
              *(undefined2 *)((int)pdVar27 + uVar21 * 4 + 2) = 0xffff;
              uVar21 = uVar21 + 1;
            } while (uVar21 < uVar10);
          }
          break;
        case 0x1404:
        case 0x1405:
          uVar21 = 0;
          if (uVar10 != 0) {
            do {
              uVar16 = 0;
              do {
                uVar16 = uVar16 + 4;
              } while (uVar16 < 0xc);
              fVar15 = (float)__ftol();
              *(float *)(pdVar27 + uVar21) = fVar15;
              *(undefined4 *)((int)pdVar27 + uVar21 * 8 + 4) = 0xffffffff;
              uVar21 = uVar21 + 1;
            } while (uVar21 < uVar10);
          }
          break;
        case 0x1406:
          uVar21 = 0;
          pdVar23 = pdVar9;
          if (uVar10 != 0) {
            do {
              uVar16 = 0;
              fVar15 = _DAT_005a83e4;
              do {
                pfVar24 = (float *)((int)&DAT_005ad460 + uVar16);
                fVar1 = *(float *)pdVar23;
                uVar16 = uVar16 + 4;
                pdVar23 = (double *)((int)pdVar23 + 4);
                fVar15 = *pfVar24 * fVar1 + fVar15;
              } while (uVar16 < 0xc);
              *(float *)(pdVar27 + uVar21) = fVar15;
              *(undefined4 *)((int)pdVar27 + uVar21 * 8 + 4) = 0x3f800000;
              uVar21 = uVar21 + 1;
            } while (uVar21 < uVar10);
          }
          break;
        case 0x140a:
          pdVar23 = pdVar9;
          pdVar14 = pdVar27;
          for (; uVar10 != 0; uVar10 = uVar10 - 1) {
            uVar21 = 0;
            dVar5 = _DAT_005a84b8;
            do {
              pfVar24 = (float *)((int)&DAT_005ad460 + uVar21);
              dVar3 = *pdVar23;
              uVar21 = uVar21 + 4;
              pdVar23 = pdVar23 + 1;
              dVar5 = (double)*pfVar24 * dVar3 + dVar5;
            } while (uVar21 < 0xc);
            *pdVar14 = dVar5;
            *(float *)(pdVar14 + 1) = 0.0;
            *(float *)((int)pdVar14 + 0xc) = 1.875;
            pdVar14 = pdVar14 + 2;
          }
        }
        goto switchD_00531aeb_caseD_1407;
      }
      goto LAB_00534216;
    }
    if (param_3 == 0x80e1) {
      pdVar27 = (double *)FUN_00530d80(((int)puVar11 * uVar10 * 4) / 3);
      if (pdVar27 != (double *)0x0) {
        switch(param_5) {
        case 0x1400:
        case 0x1401:
          if (puVar11 != (undefined1 *)0x0) {
            puVar22 = (undefined1 *)((int)pdVar27 + 1);
            puVar25 = (undefined1 *)((int)pdVar9 + 1);
            do {
              puVar17 = puVar25 + 3;
              puVar22[-1] = puVar25[-1];
              *puVar22 = *puVar25;
              puVar22[1] = puVar25[1];
              puVar22[2] = 0xff;
              puVar22 = puVar22 + 4;
              puVar25 = puVar17;
            } while (puVar17 + (-1 - (int)pdVar9) < puVar11);
          }
          break;
        case 0x1402:
        case 0x1403:
          if (puVar11 != (undefined1 *)0x0) {
            pfVar24 = (float *)((int)pdVar27 + 4);
            iVar12 = (uint)(puVar11 + -1) / 3 + 1;
            pfVar19 = (float *)((int)pdVar9 + 4);
            do {
              *(undefined2 *)(pfVar24 + -1) = *(undefined2 *)(pfVar19 + -1);
              *(undefined2 *)((int)pfVar24 + -2) = *(undefined2 *)((int)pfVar19 + -2);
              *(undefined2 *)pfVar24 = *(undefined2 *)pfVar19;
              *(undefined2 *)((int)pfVar24 + 2) = 0xffff;
              pfVar24 = pfVar24 + 2;
              iVar12 = iVar12 + -1;
              pfVar19 = (float *)((int)pfVar19 + 6);
            } while (iVar12 != 0);
          }
          break;
        case 0x1404:
        case 0x1405:
          if (puVar11 != (undefined1 *)0x0) {
            pdVar23 = pdVar27 + 1;
            iVar12 = (uint)(puVar11 + -1) / 3 + 1;
            pdVar14 = pdVar9 + 1;
            do {
              *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
              *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
              *(float *)pdVar23 = *(float *)pdVar14;
              *(float *)((int)pdVar23 + 4) = -NAN;
              pdVar23 = pdVar23 + 2;
              iVar12 = iVar12 + -1;
              pdVar14 = (double *)((int)pdVar14 + 0xc);
            } while (iVar12 != 0);
          }
          break;
        case 0x1406:
          if (puVar11 != (undefined1 *)0x0) {
            pdVar23 = pdVar27 + 1;
            iVar12 = (uint)(puVar11 + -1) / 3 + 1;
            pdVar14 = pdVar9 + 1;
            do {
              *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
              *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
              *(float *)pdVar23 = *(float *)pdVar14;
              *(float *)((int)pdVar23 + 4) = 1.0;
              pdVar23 = pdVar23 + 2;
              iVar12 = iVar12 + -1;
              pdVar14 = (double *)((int)pdVar14 + 0xc);
            } while (iVar12 != 0);
          }
          break;
        case 0x140a:
          if (puVar11 != (undefined1 *)0x0) {
            pdVar23 = pdVar27 + 2;
            iVar12 = (uint)(puVar11 + -1) / 3 + 1;
            pdVar14 = pdVar9 + 2;
            do {
              *(float *)(pdVar23 + -2) = *(float *)(pdVar14 + -2);
              *(float *)((int)pdVar23 + -0xc) = *(float *)((int)pdVar14 + -0xc);
              *(float *)(pdVar23 + -1) = *(float *)(pdVar14 + -1);
              *(float *)((int)pdVar23 + -4) = *(float *)((int)pdVar14 + -4);
              *(float *)pdVar23 = *(float *)pdVar14;
              *(float *)((int)pdVar23 + 4) = *(float *)((int)pdVar14 + 4);
              *(float *)(pdVar23 + 1) = 0.0;
              *(float *)((int)pdVar23 + 0xc) = 1.875;
              pdVar23 = pdVar23 + 4;
              iVar12 = iVar12 + -1;
              pdVar14 = pdVar14 + 3;
            } while (iVar12 != 0);
          }
        }
        goto switchD_00531aeb_caseD_1407;
      }
      goto LAB_00534216;
    }
  }
  FUN_00530d00(0x510);
LAB_00534216:
  if (pdVar9 == param_6) {
    return (double *)0x0;
  }
  FUN_00530db0(pdVar9);
  return (double *)0x0;
}

