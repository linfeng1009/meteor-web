/* Original Meteor.exe static export @ 00421da0; original sample not executed. */
/* XREF 00404a03 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00421da0(int param_1)

{
  float *pfVar1;
  float *pfVar2;
  int *piVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  bool bVar11;
  int iVar12;
  int iVar13;
  void *pvVar14;
  float fVar15;
  undefined4 uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  undefined4 *puVar24;
  undefined4 *puVar25;
  float10 fVar26;
  int unaff_retaddr;
  bool bVar27;
  float fStack_234;
  float fStack_21c;
  float fStack_218;
  int *piStack_214;
  int iStack_204;
  float fStack_1f8;
  int iStack_1f4;
  int iStack_1f0;
  uint uStack_1ec;
  int *piStack_1e8;
  int iStack_1e0;
  int iStack_1dc;
  float fStack_1d4;
  float **ppfStack_1cc;
  float fStack_1c8;
  float fStack_1c4;
  float fStack_1c0;
  float fStack_1bc;
  float fStack_1b8;
  float fStack_1b4;
  float fStack_1b0;
  float fStack_1ac;
  float fStack_1a8;
  float fStack_1a4;
  float fStack_1a0;
  float fStack_19c;
  int iStack_198;
  int iStack_194;
  float *pfStack_190;
  float *pfStack_18c;
  float *pfStack_188;
  undefined1 auStack_184 [64];
  undefined4 auStack_144 [4];
  int iStack_134;
  undefined4 uStack_120;
  undefined1 auStack_c8 [64];
  undefined1 auStack_88 [64];
  undefined1 auStack_48 [68];
  int iStack_4;
  
  if (((((DAT_005d5a0c != 0) &&
        (iVar12 = (**(code **)(**(int **)(DAT_005d5a0c + 0x6f0) + 0x60))
                            (*(int **)(DAT_005d5a0c + 0x6f0)), iVar12 != -0x7789fe3e)) &&
       (iVar12 = (**(code **)(**(int **)(DAT_005d5a0c + 0x6f4) + 0x60))
                           (*(int **)(DAT_005d5a0c + 0x6f4)), iVar12 != -0x7789fe3e)) &&
      ((*(int *)(iStack_4 + 4) < *(int *)(DAT_005d5a0c + 0x68c) &&
       (*(int *)(iStack_4 + 8) < *(int *)(DAT_005d5a0c + 0x690))))) &&
     (((-1 < *(int *)(iStack_4 + 4) + *(int *)(iStack_4 + 0xc) &&
       ((-1 < *(int *)(iStack_4 + 8) + *(int *)(iStack_4 + 0x10) && (*(int *)(iStack_4 + 0xc) != 0))
       )) && (*(int *)(iStack_4 + 0x10) != 0)))) {
    DAT_007e3340 = 0;
    DAT_007e32a4 = 0;
    _DAT_007e333c = 0;
    _DAT_007e28ac = 0;
    DAT_007e3344 = 0;
    _DAT_007e0eb0 = 0;
    DAT_007e28a4 = iStack_4;
    iVar12 = *(int *)(iStack_4 + 0x14);
    if (iVar12 == 0) {
      if (unaff_retaddr != 0) {
        FUN_00423330();
        return;
      }
    }
    else if ((*(int *)(iVar12 + 0x88) != 0) && (iVar12 = *(int *)(iVar12 + 0x9c), iVar12 != 0)) {
      if (**(int **)(DAT_005d5a0c + 0x69c) == 0) {
        if (unaff_retaddr != 0) {
          FUN_00423330();
        }
        iVar22 = 0;
        iVar21 = 0x98;
        iVar12 = DAT_007e28a4;
        do {
          if (*(int *)(iVar21 + iVar12) != 0) {
            FUN_0041ae90(iVar12,iVar22);
            iVar12 = DAT_007e28a4;
          }
          iVar21 = iVar21 + 4;
          iVar22 = iVar22 + 1;
        } while (iVar21 < 200);
        return;
      }
      FUN_00430c20(&fStack_1c8);
      for (iVar21 = *(int *)(DAT_007e28a4 + 0x14); iVar21 != 0; iVar21 = *(int *)(iVar21 + 0x124)) {
        if (*(int *)(iVar21 + 0x88) != 0) {
          FUN_00431180(&fStack_1c8,&fStack_1c8,iVar21 + 8);
        }
      }
      FUN_00431520(&fStack_1c8,auStack_c8);
      FUN_004315e0(auStack_c8,auStack_184);
      for (piVar3 = *(int **)(DAT_005d5a0c + 0x6d4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[6]
          ) {
        if (*piVar3 != 0) {
          FUN_00417850(piVar3,auStack_184);
        }
      }
      for (iVar21 = *(int *)(DAT_005d5a0c + 0x6dc); iVar21 != 0; iVar21 = *(int *)(iVar21 + 0x1c)) {
        if (*(int *)(iVar21 + 4) != 0) {
          FUN_00417960(iVar21,auStack_184);
        }
      }
      DAT_007e0e94 = *(int *)(*(int *)(DAT_007e28a4 + 0x14) + 0x9c) + 0x24;
      FUN_004312e0(auStack_48,auStack_184,DAT_007e0e94);
      iVar21 = 0;
      iStack_1f0 = 0;
      if (0 < DAT_007e5bc0) {
        iVar22 = 0x584;
        do {
          iVar23 = (&DAT_007ead80)[iVar21];
          if ((iVar23 != 0) && (*(int *)(iVar23 + 4) != 4)) {
            if (*(int *)(iVar23 + 0x124) == 0) {
              FUN_00430fb0(iVar23 + 0x38,iVar23 + 8,auStack_184);
            }
            else {
              FUN_00430c20(&fStack_1c8);
              iVar13 = iVar23;
              do {
                if (*(int *)(iVar13 + 0x78) != 0) {
                  FUN_00430fb0(iVar23 + 0x38,&fStack_1c8,iVar13 + 0x38);
                  goto LAB_004220bf;
                }
                FUN_00431180(&fStack_1c8,&fStack_1c8,iVar13 + 8);
                iVar13 = *(int *)(iVar13 + 0x124);
              } while (iVar13 != 0);
              iVar13 = iVar23 + 0x38;
              FUN_00431520(&fStack_1c8,iVar13);
              FUN_004312e0(iVar13,iVar13,auStack_184);
            }
LAB_004220bf:
            *(undefined4 *)(iVar23 + 0x78) = 1;
            if (((*(int *)(iVar23 + 4) == 3) && (*(int *)(iVar23 + 0x8c) != 0)) && (iVar22 != 0x684)
               ) {
              **(undefined4 **)(iVar22 + DAT_005d5a0c) = *(undefined4 *)(iVar23 + 0x9c);
              *(undefined4 *)(*(int *)(iVar22 + DAT_005d5a0c) + 4) = *(undefined4 *)(iVar23 + 0x68);
              *(undefined4 *)(*(int *)(iVar22 + DAT_005d5a0c) + 8) = *(undefined4 *)(iVar23 + 0x6c);
              *(undefined4 *)(*(int *)(iVar22 + DAT_005d5a0c) + 0xc) =
                   *(undefined4 *)(iVar23 + 0x70);
              *(float *)(*(int *)(iVar22 + DAT_005d5a0c) + 0x10) = -*(float *)(iVar23 + 0x58);
              *(float *)(*(int *)(iVar22 + DAT_005d5a0c) + 0x14) = -*(float *)(iVar23 + 0x5c);
              *(float *)(*(int *)(iVar22 + DAT_005d5a0c) + 0x18) = -*(float *)(iVar23 + 0x60);
              FUN_00431a20(*(int *)(iVar22 + DAT_005d5a0c) + 0x10);
              iStack_1f0 = iStack_1f0 + 1;
              iVar22 = iVar22 + 4;
            }
          }
          iVar21 = iVar21 + 1;
        } while (iVar21 < DAT_007e5bc0);
      }
      if ((DAT_005c45ac != 0) && (*(int *)(DAT_007e28a4 + 0x18) != 0)) {
        iVar21 = **(int **)(DAT_005d5a0c + 0x69c);
        iVar22 = 0;
        if (iVar21 != 0) {
          do {
            iVar23 = iVar22;
            if (*(int *)(iVar21 + 0x8c) == 0) {
              *(undefined4 *)(iVar21 + 0x140) = *(undefined4 *)(iVar21 + 0x70);
            }
            else if (*(int *)(iVar21 + 4) == 7) {
              *(undefined4 *)(iVar21 + 0x140) = *(undefined4 *)(iVar21 + 0x70);
            }
            else if (*(int *)(iVar21 + 4) == 6) {
              if ((*(byte *)(*(int *)(iVar21 + 0x9c) + 4) & 0x10) == 0) {
                iVar22 = *(int *)(iVar21 + 0xa0);
                fVar15 = *(float *)(iVar22 + 0x10) * *(float *)(iVar21 + 0x40);
                fVar4 = *(float *)(iVar22 + 0x14) * *(float *)(iVar21 + 0x40);
                if (fVar4 < fVar15) {
                  fVar4 = fVar15;
                }
                fVar5 = *(float *)(iVar22 + 0x18) * *(float *)(iVar21 + 0x50);
                fVar15 = *(float *)(iVar22 + 0x1c) * *(float *)(iVar21 + 0x50);
                if (fVar15 < fVar5) {
                  fVar15 = fVar5;
                }
                fVar6 = *(float *)(iVar22 + 0x20) * *(float *)(iVar21 + 0x60) +
                        *(float *)(iVar21 + 0x70);
                fVar5 = *(float *)(iVar22 + 0x24) * *(float *)(iVar21 + 0x60) +
                        *(float *)(iVar21 + 0x70);
                if (fVar5 < fVar6) {
                  fVar5 = fVar6;
                }
                *(float *)(iVar21 + 0x140) = fVar5 + fVar15 + fVar4;
              }
              else {
                *(float *)(iVar21 + 0x140) =
                     (*(float *)(iVar12 + 0x1c) - *(float *)(iVar12 + 0x18)) *
                     *(float *)(*(int *)(iVar21 + 0xa0) + 8) + *(float *)(iVar12 + 0x18);
              }
            }
            else {
              *(undefined4 *)(iVar21 + 0x140) = 0;
            }
            iVar21 = *(int *)(iVar21 + 0x130);
            iVar22 = iVar23 + 1;
          } while (iVar21 != 0);
          if ((1 < iVar23 + 1) && (0 < iVar23)) {
            while( true ) {
              bVar27 = true;
              iVar21 = **(int **)(DAT_005d5a0c + 0x69c);
              iVar22 = iVar23;
              if (iVar23 < 1) break;
              do {
                iVar13 = *(int *)(iVar21 + 0x130);
                if (*(float *)(iVar21 + 0x140) < *(float *)(iVar13 + 0x140)) {
                  FUN_0040aee0(iVar21,1);
                  bVar27 = false;
                  iVar13 = iVar21;
                }
                iVar22 = iVar22 + -1;
                iVar21 = iVar13;
              } while (iVar22 != 0);
              if ((bVar27) || (iVar23 = iVar23 + -1, iVar23 < 1)) break;
            }
          }
        }
      }
      FUN_00524120();
      if (unaff_retaddr != 0) {
        FUN_00423330();
      }
      iVar23 = 0;
      iVar22 = 0x98;
      iVar21 = DAT_007e28a4;
      do {
        if (*(int *)(iVar22 + iVar21) != 0) {
          FUN_0041ae90(iVar21,iVar23);
          iVar21 = DAT_007e28a4;
        }
        iVar22 = iVar22 + 4;
        iVar23 = iVar23 + 1;
      } while (iVar22 < 200);
      if ((param_1 != 0) && (*(int *)(DAT_005d5a0c + 0x730) != 0)) {
        FUN_00423410();
      }
      DAT_007e2768 = -0x7789fde4;
      puVar24 = auStack_144;
      for (iVar21 = 0x1f; iVar21 != 0; iVar21 = iVar21 + -1) {
        *puVar24 = 0;
        puVar24 = puVar24 + 1;
      }
      auStack_144[0] = 0x7c;
      iVar21 = 0;
      do {
        DAT_007e2768 = (**(code **)(**(int **)(DAT_005d5a0c + 0x6f4) + 100))
                                 (*(int **)(DAT_005d5a0c + 0x6f4),0,auStack_144,0,0);
        iVar22 = DAT_005d5a0c;
        iVar21 = iVar21 + 1;
        if (3000 < iVar21) break;
      } while (DAT_007e2768 == -0x7789fde4);
      if (DAT_007e2768 == 0) {
        if (DAT_005c431c == 0) {
          DAT_007e28b0 = iStack_134 * 2;
        }
        else {
          DAT_007e28b0 = iStack_134;
        }
        DAT_007e2c88 = uStack_120;
        iVar23 = -1;
        iStack_204 = -1;
        _DAT_007e24dc = (float)*(int *)(DAT_007e28a4 + 0xc) * _DAT_005a83e8;
        _DAT_007e32a0 = (float)*(int *)(DAT_007e28a4 + 0x10) * _DAT_005a83e8;
        _DAT_007e0408 = (float)DAT_007e2338 + _DAT_007e24dc + _DAT_005a83e8;
        _DAT_007e040c = (float)DAT_007e2340 + _DAT_007e32a0 + _DAT_005a83e8;
        iVar21 = **(int **)(DAT_005d5a0c + 0x69c);
        fStack_1d4 = (float)__ftol();
        DAT_007e0410 = 0;
        for (; iVar21 != 0; iVar21 = *(int *)(iVar21 + 0x130)) {
          *(undefined4 *)(iVar21 + 0x11c) = 0;
          if ((*(int *)(iVar21 + 0x88) != 0) && (*(int *)(iVar21 + 0x8c) != 0)) {
            fVar15 = *(float *)(iVar21 + 0x114);
            if (*(float *)(iVar21 + 0x114) <= _DAT_005a83e4) {
              fVar15 = -fVar15;
            }
            if (_DAT_005a8408 <= fVar15) {
              if (*(int *)(iVar21 + 4) == 6) {
                iVar22 = *(int *)(iVar21 + 0x9c);
                if ((((iVar22 != 0) && (*(int *)(iVar22 + 0x1c) != 0)) &&
                    (*(int *)(iVar22 + 0x3c) != 0)) && (*(int *)(iVar22 + 0x18) != 0)) {
                  bVar27 = true;
                  if (*(int *)(iVar21 + 0x90) != 0) {
                    uStack_1ec = *(uint *)(iVar22 + 4) & 0x10;
                    if (uStack_1ec != 0) goto LAB_004232f7;
                    FUN_004312e0(auStack_88,iVar21 + 0x38,DAT_007e0e94);
                    iVar13 = FUN_00523960(iVar21,auStack_88);
                    if (iVar13 == 1) {
                      bVar27 = true;
                    }
                    else {
                      if (iVar13 != 2) {
                        _DAT_007e0eb0 = _DAT_007e0eb0 + 1;
                        goto LAB_004232f7;
                      }
                      bVar27 = false;
                    }
                  }
                  *(undefined4 *)(iVar21 + 0x11c) = 1;
                  iStack_194 = *(int *)(iVar22 + 0x1c);
                  piStack_214 = *(int **)(iVar22 + 0x40);
                  iVar13 = *(int *)(iVar22 + 0x30);
                  if (*(int *)(iVar21 + 0x178) == 0) {
                    *(int *)(iVar21 + 0x174) = iVar13;
                    pvVar14 = _malloc(iVar13 * DAT_005c4318 * 4);
LAB_00422623:
                    *(void **)(iVar21 + 0x178) = pvVar14;
                  }
                  else if (*(int *)(iVar21 + 0x174) < iVar13) {
                    *(int *)(iVar21 + 0x174) = iVar13;
                    pvVar14 = (void *)FUN_005099a7(*(int *)(iVar21 + 0x178),
                                                   iVar13 * DAT_005c4318 * 4);
                    goto LAB_00422623;
                  }
                  iStack_198 = *(int *)(iVar21 + 0x178);
                  uVar18 = *(uint *)(iVar22 + 0x18);
                  puVar24 = *(undefined4 **)(iVar22 + 0x48);
                  puVar25 = puVar24;
                  for (uVar17 = (uVar18 & 0x7fffffff) >> 1; uVar17 != 0; uVar17 = uVar17 - 1) {
                    *puVar25 = 0;
                    puVar25 = puVar25 + 1;
                  }
                  for (uVar18 = uVar18 * 2 & 3; uVar18 != 0; uVar18 = uVar18 - 1) {
                    *(undefined1 *)puVar25 = 0;
                    puVar25 = (undefined4 *)((int)puVar25 + 1);
                  }
                  FUN_00431590(iVar21 + 0x38,&fStack_1c8);
                  if ((*(int *)(DAT_005d5a0c + 0x730) == 0) ||
                     (DAT_007e24e4 = 1, *(int *)(iVar21 + 0xc4) == 0)) {
                    DAT_007e24e4 = 0;
                  }
                  if ((*(int *)(DAT_005d5a0c + 0x730) == 0) ||
                     (DAT_007e276c = 1, *(int *)(iVar21 + 200) == 0)) {
                    DAT_007e276c = 0;
                  }
                  DAT_007e2700 = *(int *)(iVar21 + 0xd0);
                  DAT_007e0410 = (uint)(*(int *)(iVar21 + 0x118) != 0xff);
                  iStack_1dc = *(int *)(iVar22 + 0x38);
                  iVar13 = DAT_007e3380;
                  do {
                    iVar20 = piStack_214[1];
                    if (iVar23 != iVar20) {
                      if (((0x13ff < iVar20) || (iVar20 < 0)) ||
                         (DAT_007e32ac = (&DAT_007e5be0)[iVar20], (&DAT_007e5be0)[iVar20] == 0)) {
                        DAT_007e32ac = iVar13;
                      }
                      _DAT_007e22c0 = *(undefined4 *)(*(int *)(DAT_007e32ac + 0x3c) + 0x10);
                      fStack_1d4 = (float)__ftol();
                      iVar23 = iVar20;
                      iStack_204 = iVar20;
                    }
                    DAT_007e32a4 = DAT_007e32a4 + 1;
                    if (*piStack_214 == 2) {
                      iVar20 = piStack_214[2] * 2 + 3;
                    }
                    else {
                      ppfStack_1cc = &pfStack_188;
                      piStack_1e8 = piStack_214 + 5;
                      iStack_1e0 = 0;
                      iStack_1f4 = 3;
                      do {
                        iVar23 = *piStack_1e8;
                        pfVar1 = (float *)(iStack_198 + DAT_005c4318 * iVar23 * 4);
                        if (*(short *)((int)puVar24 + iVar23 * 2) == 0) {
                          pfVar2 = (float *)(iStack_194 + DAT_007eac64 * iVar23 * 4);
                          if (uStack_1ec == 0) {
                            fStack_218 = fStack_1c4 * pfVar2[1] +
                                         fStack_1c0 * pfVar2[2] + fStack_1c8 * *pfVar2 + fStack_1bc;
                            fStack_21c = fStack_1b4 * pfVar2[1] +
                                         fStack_1b0 * pfVar2[2] + fStack_1b8 * *pfVar2 + fStack_1ac;
                            fStack_234 = fStack_1a4 * pfVar2[1] +
                                         fStack_1a0 * pfVar2[2] + fStack_1a8 * *pfVar2 + fStack_19c;
                            *pfVar1 = fStack_218;
                            pfVar1[1] = fStack_21c;
                            pfVar1[2] = fStack_234;
                          }
                          else {
                            *pfVar1 = 0.0;
                            pfVar1[1] = 0.0;
                            pfVar1[2] = 0.0;
                          }
                          if (*(int *)(DAT_007e32ac + 0x34) != 0) {
                            pfVar1[6] = pfVar2[6];
                            pfVar1[7] = pfVar2[7];
                            fVar15 = (float)__ftol();
                            pfVar1[8] = fVar15;
                            fVar15 = (float)__ftol();
                            pfVar1[9] = fVar15;
                          }
                          if (uStack_1ec == 0) {
                            if (_DAT_005a83e4 <
                                fStack_234 * *(float *)(DAT_007e0e94 + 0x2c) +
                                *(float *)(DAT_007e0e94 + 0x3c)) {
                              fVar15 = (float)__ftol();
                              pfVar1[3] = fVar15;
                              fVar15 = (float)__ftol();
                              pfVar1[4] = fVar15;
                              goto LAB_0042297f;
                            }
                            pfVar1[5] = 2.3509886e-38;
LAB_00422cc8:
                            pfVar1[10] = 3.57331e-43;
                          }
                          else {
                            fVar15 = (float)__ftol();
                            pfVar1[3] = fVar15;
                            fVar15 = (float)__ftol();
                            pfVar1[4] = fVar15;
LAB_0042297f:
                            fVar15 = (float)__ftol();
                            pfVar1[5] = fVar15;
                            if ((*(int *)(iVar21 + 0x104) == 0) ||
                               ((*(byte *)(iVar22 + 4) & 1) != 0)) goto LAB_00422cc8;
                            pfVar1[10] = fStack_1d4;
                            iVar13 = 0;
                            fStack_1f8 = 0.0;
                            fVar15 = fStack_1c4 * pfVar2[4] +
                                     fStack_1c0 * pfVar2[5] + fStack_1c8 * pfVar2[3];
                            fVar4 = fStack_1b4 * pfVar2[4] +
                                    fStack_1b0 * pfVar2[5] + fStack_1b8 * pfVar2[3];
                            fVar5 = fStack_1a4 * pfVar2[4] +
                                    fStack_1a0 * pfVar2[5] + fStack_1a8 * pfVar2[3];
                            if (0 < iStack_1f0) {
                              iVar20 = 0x584;
                              do {
                                piVar3 = *(int **)(DAT_005d5a0c + iVar20);
                                iVar19 = *piVar3;
                                if (*(int *)(iVar19 + 4) == 2) {
                                  fVar6 = (float)piVar3[1] - fStack_218;
                                  fVar7 = (float)piVar3[2] - fStack_21c;
                                  fVar8 = (float)piVar3[3] - fStack_234;
                                  fVar9 = SQRT(fVar6 * fVar6 + fVar7 * fVar7 + fVar8 * fVar8);
                                  if (((fVar9 != _DAT_005a83e4) &&
                                      (fVar9 <= *(float *)(iVar19 + 0x18))) &&
                                     (fVar26 = (float10)fVar6 * (float10)fVar15 +
                                               (float10)fVar7 * (float10)fVar4 +
                                               (float10)fVar8 * (float10)fVar5,
                                     fVar26 < (float10)_DAT_005a83e4 ==
                                     (fVar26 == (float10)_DAT_005a83e4))) {
                                    fVar26 = (fVar26 / (float10)fVar9) *
                                             (((float10)*(float *)(iVar19 + 0x18) - (float10)fVar9)
                                             / (float10)*(float *)(iVar19 + 0x18));
LAB_00422c62:
                                    fVar26 = fVar26 * (float10)*(float *)(iVar19 + 0x14) +
                                             (float10)fStack_1f8;
                                    fStack_1f8 = (float)fVar26;
                                    if ((float10)_DAT_005a83f4 < fVar26) break;
                                  }
                                }
                                else if (*(int *)(iVar19 + 4) == 3) {
                                  fVar6 = (float)piVar3[1] - fStack_218;
                                  fVar7 = (float)piVar3[2] - fStack_21c;
                                  fVar8 = (float)piVar3[3] - fStack_234;
                                  fVar9 = SQRT(fVar6 * fVar6 + fVar7 * fVar7 + fVar8 * fVar8);
                                  if ((fVar9 != _DAT_005a83e4) &&
                                     (fVar9 <= *(float *)(iVar19 + 0x18))) {
                                    fVar10 = (fVar6 * fVar15 + fVar7 * fVar4 + fVar8 * fVar5) *
                                             (_DAT_005a83f4 / fVar9);
                                    if ((fVar10 < _DAT_005a83e4 == (fVar10 == _DAT_005a83e4)) &&
                                       (fVar6 = -((fVar6 * (float)piVar3[4] +
                                                  fVar7 * (float)piVar3[5] +
                                                  fVar8 * (float)piVar3[6]) *
                                                 (_DAT_005a83f4 / fVar9)),
                                       *(float *)(iVar19 + 0x20) <= fVar6)) {
                                      if ((*(float *)(iVar19 + 0x1c) < fVar6) ||
                                         (*(float *)(iVar19 + 0x24) == _DAT_005a83e4)) {
                                        fVar26 = (float10)_DAT_005a83f4;
                                      }
                                      else {
                                        fVar26 = (float10)FUN_00432000((fVar6 - *(float *)(iVar19 + 
                                                  0x20)) / (*(float *)(iVar19 + 0x1c) -
                                                           *(float *)(iVar19 + 0x20)),
                                                  *(undefined4 *)(iVar19 + 0x24));
                                      }
                                      iVar19 = *piVar3;
                                      fVar26 = (((float10)*(float *)(iVar19 + 0x18) - (float10)fVar9
                                                ) / (float10)*(float *)(iVar19 + 0x18)) *
                                               (float10)fVar10 * fVar26;
                                      goto LAB_00422c62;
                                    }
                                  }
                                }
                                else {
                                  fVar26 = (-((float10)fVar15 * (float10)(float)piVar3[4]) -
                                           (float10)fVar4 * (float10)(float)piVar3[5]) -
                                           (float10)fVar5 * (float10)(float)piVar3[6];
                                  if (fVar26 < (float10)_DAT_005a83e4 ==
                                      (fVar26 == (float10)_DAT_005a83e4)) goto LAB_00422c62;
                                }
                                iVar13 = iVar13 + 1;
                                iVar20 = iVar20 + 4;
                              } while (iVar13 < iStack_1f0);
                            }
                            iVar13 = __ftol();
                            fVar15 = pfVar1[10];
                            pfVar1[10] = (float)((int)fVar15 + iVar13);
                            if (0xff < (int)fVar15 + iVar13) {
                              pfVar1[10] = 3.57331e-43;
                            }
                          }
                          *(undefined2 *)((int)puVar24 + iVar23 * 2) = 1;
                          DAT_007e3344 = DAT_007e3344 + 1;
                        }
                        fVar15 = pfVar1[5];
                        *ppfStack_1cc = pfVar1;
                        ppfStack_1cc = ppfStack_1cc + -1;
                        iStack_1e0 = iStack_1e0 + (int)fVar15;
                        piStack_1e8 = piStack_1e8 + -1;
                        iStack_1f4 = iStack_1f4 + -1;
                      } while (iStack_1f4 != 0);
                      iVar23 = iStack_204;
                      iVar13 = DAT_007e3380;
                      iVar20 = DAT_005c4314;
                      if (iStack_1e0 != 0x2fffffd) {
                        if ((piStack_214[2] == 0) && (uStack_1ec == 0)) {
                          fStack_218 = (pfStack_18c[1] - pfStack_190[1]) *
                                       (pfStack_188[2] - pfStack_190[2]) -
                                       (pfStack_18c[2] - pfStack_190[2]) *
                                       (pfStack_188[1] - pfStack_190[1]);
                          fStack_21c = (pfStack_18c[2] - pfStack_190[2]) *
                                       (*pfStack_188 - *pfStack_190) -
                                       (*pfStack_18c - *pfStack_190) *
                                       (pfStack_188[2] - pfStack_190[2]);
                          fStack_234 = (*pfStack_18c - *pfStack_190) *
                                       (pfStack_188[1] - pfStack_190[1]) -
                                       (pfStack_18c[1] - pfStack_190[1]) *
                                       (*pfStack_188 - *pfStack_190);
                          if (_DAT_005a83e4 <=
                              fStack_21c * pfStack_190[1] +
                              fStack_218 * *pfStack_190 + fStack_234 * pfStack_190[2])
                          goto LAB_00422f95;
                        }
                        bVar11 = false;
                        if (bVar27) {
                          if (((((((int)pfStack_190[5] < 0x10000) && (-1 < (int)pfStack_190[5])) &&
                                (((int)pfStack_18c[5] < 0x10000 &&
                                 (((((-1 < (int)pfStack_18c[5] && ((int)pfStack_188[5] < 0x10000))
                                    && (-1 < (int)pfStack_188[5])) &&
                                   ((DAT_007e2338 <= (int)pfStack_190[3] &&
                                    ((int)pfStack_190[3] <= DAT_007e233c)))) &&
                                  (DAT_007e2340 <= (int)pfStack_190[4])))))) &&
                               (((int)pfStack_190[4] <= DAT_007e2328 &&
                                (DAT_007e2338 <= (int)pfStack_18c[3])))) &&
                              ((int)pfStack_18c[3] <= DAT_007e233c)) &&
                             ((((DAT_007e2340 <= (int)pfStack_18c[4] &&
                                ((int)pfStack_18c[4] <= DAT_007e2328)) &&
                               (DAT_007e2338 <= (int)pfStack_188[3])) &&
                              ((((int)pfStack_188[3] <= DAT_007e233c &&
                                (DAT_007e2340 <= (int)pfStack_188[4])) &&
                               ((int)pfStack_188[4] <= DAT_007e2328)))))) {
                            bVar11 = false;
                          }
                          else {
                            bVar11 = true;
                          }
                        }
                        DAT_005c4628 = *(undefined4 *)(iVar21 + 0xc4);
                        if (bVar11) {
                          if ((*(int *)(DAT_007e32ac + 0x34) == 0) || (*(int *)(iVar21 + 0x94) == 1)
                             ) {
                            FUN_00423910(iVar12,pfStack_190,pfStack_18c,pfStack_188);
                            iVar13 = DAT_007e3380;
                            iVar20 = DAT_005c4314;
                          }
                          else {
                            FUN_00423440(iVar12,pfStack_190,pfStack_18c,pfStack_188);
                            iVar13 = DAT_007e3380;
                            iVar20 = DAT_005c4314;
                          }
                        }
                        else if ((*(int *)(DAT_007e32ac + 0x34) == 0) ||
                                (*(int *)(iVar21 + 0x94) == 1)) {
                          if (DAT_007e0410 == 0) {
                            FUN_00427bb0(pfStack_190,pfStack_18c,pfStack_188);
                            iVar13 = DAT_007e3380;
                            iVar20 = DAT_005c4314;
                          }
                          else {
                            FUN_00428240();
                            iVar13 = DAT_007e3380;
                            iVar20 = DAT_005c4314;
                          }
                        }
                        else {
                          iVar13 = *(int *)(*(int *)(DAT_007e32ac + 0x34) + 0x2c);
                          if (DAT_007e2700 == 0) {
                            if (iVar13 == -1) {
                              if (DAT_007e0410 == 0) {
                                FUN_00425970(pfStack_190,pfStack_18c,pfStack_188);
                                iVar13 = DAT_007e3380;
                                iVar20 = DAT_005c4314;
                              }
                              else {
                                FUN_004261e0();
                                iVar13 = DAT_007e3380;
                                iVar20 = DAT_005c4314;
                              }
                            }
                            else if (DAT_007e0410 == 0) {
                              FUN_00426a80();
                              iVar13 = DAT_007e3380;
                              iVar20 = DAT_005c4314;
                            }
                            else {
                              FUN_00427300();
                              iVar13 = DAT_007e3380;
                              iVar20 = DAT_005c4314;
                            }
                          }
                          else if (iVar13 == -1) {
                            if (DAT_007e0410 == 0) {
                              FUN_00423c30();
                              iVar13 = DAT_007e3380;
                              iVar20 = DAT_005c4314;
                            }
                            else {
                              FUN_00424360();
                              iVar13 = DAT_007e3380;
                              iVar20 = DAT_005c4314;
                            }
                          }
                          else if (DAT_007e0410 == 0) {
                            FUN_00424ac0();
                            iVar13 = DAT_007e3380;
                            iVar20 = DAT_005c4314;
                          }
                          else {
                            FUN_00425200();
                            iVar13 = DAT_007e3380;
                            iVar20 = DAT_005c4314;
                          }
                        }
                      }
                    }
LAB_00422f95:
                    piStack_214 = piStack_214 + iVar20;
                    iStack_1dc = iStack_1dc + -1;
                  } while (iStack_1dc != 0);
                  _DAT_007e333c = _DAT_007e333c + 1;
                }
              }
              else if ((*(int *)(iVar21 + 4) == 7) &&
                      (iVar22 = *(int *)(iVar21 + 0x9c), iVar22 != 0)) {
                DAT_007e2700 = 0;
                DAT_005c4628 = *(undefined4 *)(iVar21 + 0xc4);
                iVar23 = *(int *)(iVar22 + 4);
                if ((0x13ff < iVar23) ||
                   ((iVar23 < 0 ||
                    (DAT_007e32ac = (&DAT_007e5be0)[iVar23], (&DAT_007e5be0)[iVar23] == 0)))) {
                  DAT_007e32ac = DAT_007e3380;
                }
                _DAT_007e22c0 = *(undefined4 *)(*(int *)(DAT_007e32ac + 0x3c) + 0x10);
                DAT_007e0410 = (uint)(*(int *)(iVar21 + 0x118) != 0xff);
                iStack_204 = iVar23;
                if ((-*(float *)(iVar12 + 0x18) < *(float *)(iVar21 + 0x70) ==
                     (-*(float *)(iVar12 + 0x18) == *(float *)(iVar21 + 0x70))) &&
                   (-*(float *)(iVar12 + 0x1c) < *(float *)(iVar21 + 0x70))) {
                  *(undefined4 *)(iVar21 + 0x11c) = 1;
                  _DAT_007e0de0 = *(float *)(iVar22 + 8) + *(float *)(iVar21 + 0x68);
                  _DAT_007e0de4 = *(float *)(iVar22 + 0xc) + *(float *)(iVar21 + 0x6c);
                  _DAT_007e0de8 = *(undefined4 *)(iVar21 + 0x70);
                  _DAT_007e0dec = __ftol();
                  _DAT_007e0df0 = __ftol();
                  uVar16 = __ftol();
                  _DAT_007e0e0c = *(float *)(iVar21 + 0x68) - *(float *)(iVar22 + 8);
                  _DAT_007e0e10 = *(float *)(iVar22 + 0xc) + *(float *)(iVar21 + 0x6c);
                  _DAT_007e0e14 = *(undefined4 *)(iVar21 + 0x70);
                  _DAT_007e0df4 = uVar16;
                  _DAT_007e0e18 = __ftol();
                  _DAT_007e0e1c = __ftol();
                  _DAT_007e0e38 = *(float *)(iVar21 + 0x68) - *(float *)(iVar22 + 8);
                  _DAT_007e0e3c = *(float *)(iVar21 + 0x6c) - *(float *)(iVar22 + 0xc);
                  _DAT_007e0e40 = *(undefined4 *)(iVar21 + 0x70);
                  _DAT_007e0e20 = uVar16;
                  _DAT_007e0e44 = __ftol();
                  _DAT_007e0e48 = __ftol();
                  _DAT_007e0e64 = *(float *)(iVar22 + 8) + *(float *)(iVar21 + 0x68);
                  _DAT_007e0e68 = *(float *)(iVar21 + 0x6c) - *(float *)(iVar22 + 0xc);
                  _DAT_007e0e6c = *(undefined4 *)(iVar21 + 0x70);
                  _DAT_007e0e4c = uVar16;
                  _DAT_007e0e70 = __ftol();
                  _DAT_007e0e74 = __ftol();
                  _DAT_007e0e78 = uVar16;
                  FUN_00423440(iVar12,&DAT_007e0de0,&DAT_007e0e0c,&DAT_007e0e38);
                  FUN_00423440(iVar12,&DAT_007e0de0,&DAT_007e0e38,&DAT_007e0e64);
                }
              }
            }
          }
LAB_004232f7:
          iVar22 = DAT_005d5a0c;
        }
        (**(code **)(**(int **)(iVar22 + 0x6f4) + 0x80))(*(int **)(iVar22 + 0x6f4),0);
      }
    }
  }
  return;
}

