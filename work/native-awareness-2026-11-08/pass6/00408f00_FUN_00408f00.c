/* Original Meteor.exe static export @ 00408f00; original sample not executed. */
/* XREF 00408ed0 UNCONDITIONAL_JUMP */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00408f00(uint *param_1,uint *param_2)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  float *pfVar10;
  uint *puVar11;
  int iVar12;
  float10 fVar13;
  int local_17c;
  float local_178;
  float local_174;
  uint local_170;
  int *local_160;
  int *local_15c;
  uint local_158;
  float local_154 [4];
  float local_144;
  float local_140;
  float local_13c;
  float local_138 [11];
  undefined1 local_10c [12];
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  int local_68;
  int local_64;
  float local_60;
  float local_5c;
  float local_58;
  
  FUN_00406ed0(*param_1 | 0x2000000,&local_74,&local_60,0);
  local_178 = 0.0;
  pfVar10 = &local_60;
  iVar12 = 8;
  do {
    fVar13 = (float10)FUN_00431fd0(&local_74,pfVar10);
    if ((float10)local_178 < fVar13) {
      local_178 = (float)fVar13;
    }
    pfVar10 = pfVar10 + 3;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  FUN_00406ed0(*param_2 | 0x2000000,&local_80,&local_60,0);
  local_174 = 0.0;
  pfVar10 = &local_60;
  iVar12 = 8;
  do {
    fVar13 = (float10)FUN_00431fd0(&local_80,pfVar10);
    if ((float10)local_174 < fVar13) {
      local_174 = (float)fVar13;
    }
    pfVar10 = pfVar10 + 3;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  fVar13 = (float10)FUN_00431fd0(&local_74,&local_80);
  if (fVar13 <= (float10)(SQRT(local_174) + SQRT(local_178)) *
                (float10)(SQRT(local_174) + SQRT(local_178))) {
    FUN_00430c20(&local_b0);
    puVar11 = param_1;
    do {
      if (puVar11[0x22] != 0) {
        FUN_00431180(&local_b0,&local_b0,puVar11 + 2);
      }
      puVar11 = (uint *)puVar11[0x49];
    } while (puVar11 != (uint *)0x0);
    FUN_00430c20(&local_e0);
    puVar11 = param_2;
    do {
      if (puVar11[0x22] != 0) {
        FUN_00431180(&local_e0,&local_e0,puVar11 + 2);
      }
      puVar11 = (uint *)puVar11[0x49];
    } while (puVar11 != (uint *)0x0);
    uVar2 = param_1[0x27];
    local_158 = 0;
    iVar12 = *(int *)(param_2[0x27] + 0x1c);
    piVar9 = *(int **)(uVar2 + 0x40);
    iVar3 = *(int *)(uVar2 + 0x1c);
    local_64 = DAT_007eac64;
    local_68 = DAT_007eac64;
    iVar7 = DAT_007eac64;
    iVar8 = DAT_007eac64;
    local_160 = piVar9;
    if (0 < *(int *)(uVar2 + 0x34)) {
      do {
        if (*piVar9 == 1) {
          iVar6 = piVar9[3] * iVar7;
          local_154[0] = local_a4 * *(float *)(iVar3 + 4 + iVar6 * 4) +
                         local_b0 * *(float *)(iVar3 + iVar6 * 4) +
                         local_98 * *(float *)(iVar3 + 8 + iVar6 * 4) + local_8c;
          local_154[1] = local_a0 * *(float *)(iVar3 + 4 + iVar6 * 4) +
                         local_ac * *(float *)(iVar3 + iVar6 * 4) +
                         local_94 * *(float *)(iVar3 + 8 + iVar6 * 4) + local_88;
          local_154[2] = local_9c * *(float *)(iVar3 + 4 + iVar6 * 4) +
                         local_a8 * *(float *)(iVar3 + iVar6 * 4) +
                         local_90 * *(float *)(iVar3 + 8 + iVar6 * 4) + local_84;
          iVar6 = piVar9[4] * iVar7;
          local_154[3] = local_a4 * *(float *)(iVar3 + 4 + iVar6 * 4) +
                         local_b0 * *(float *)(iVar3 + iVar6 * 4) +
                         local_98 * *(float *)(iVar3 + 8 + iVar6 * 4) + local_8c;
          local_144 = local_a0 * *(float *)(iVar3 + 4 + iVar6 * 4) +
                      local_ac * *(float *)(iVar3 + iVar6 * 4) +
                      local_94 * *(float *)(iVar3 + 8 + iVar6 * 4) + local_88;
          local_140 = local_9c * *(float *)(iVar3 + 4 + iVar6 * 4) +
                      local_a8 * *(float *)(iVar3 + iVar6 * 4) +
                      local_90 * *(float *)(iVar3 + 8 + iVar6 * 4) + local_84;
          iVar7 = piVar9[5] * iVar7;
          local_13c = local_a4 * *(float *)(iVar3 + 4 + iVar7 * 4) +
                      local_b0 * *(float *)(iVar3 + iVar7 * 4) +
                      local_98 * *(float *)(iVar3 + 8 + iVar7 * 4) + local_8c;
          local_178 = 0.0;
          pfVar10 = local_154;
          local_170 = 3;
          local_138[0] = local_a0 * *(float *)(iVar3 + 4 + iVar7 * 4) +
                         local_ac * *(float *)(iVar3 + iVar7 * 4) +
                         local_94 * *(float *)(iVar3 + 8 + iVar7 * 4) + local_88;
          local_138[1] = local_9c * *(float *)(iVar3 + 4 + iVar7 * 4) +
                         local_a8 * *(float *)(iVar3 + iVar7 * 4) +
                         local_90 * *(float *)(iVar3 + 8 + iVar7 * 4) + local_84;
          local_74 = (local_13c + local_154[3] + local_154[0]) * _DAT_005a8428;
          local_70 = (local_138[0] + local_144 + local_154[1]) * _DAT_005a8428;
          local_6c = (local_138[1] + local_140 + local_154[2]) * _DAT_005a8428;
          do {
            fVar13 = (float10)FUN_00431fd0(&local_74,pfVar10);
            if ((float10)local_178 < fVar13) {
              local_178 = (float)fVar13;
            }
            pfVar10 = pfVar10 + 3;
            local_170 = local_170 + -1;
          } while (local_170 != 0);
          FUN_00430f30(&local_100,local_154,local_154 + 3,&local_13c);
          local_170 = 0;
          local_f4 = (-(local_100 * local_154[0]) - local_fc * local_154[1]) -
                     local_f8 * local_154[2];
          piVar9 = *(int **)(param_2[0x27] + 0x40);
          local_15c = piVar9;
          if (0 < *(int *)(param_2[0x27] + 0x34)) {
            do {
              if (*piVar9 == 1) {
                iVar7 = piVar9[3] * iVar8;
                local_138[2] = local_d4 * *(float *)(iVar12 + 4 + iVar7 * 4) +
                               local_c8 * *(float *)(iVar12 + 8 + iVar7 * 4) +
                               local_e0 * *(float *)(iVar12 + iVar7 * 4) + local_bc;
                local_138[3] = local_d0 * *(float *)(iVar12 + 4 + iVar7 * 4) +
                               local_c4 * *(float *)(iVar12 + 8 + iVar7 * 4) +
                               local_dc * *(float *)(iVar12 + iVar7 * 4) + local_b8;
                local_138[4] = local_d8 * *(float *)(iVar12 + iVar7 * 4) +
                               local_cc * *(float *)(iVar12 + 4 + iVar7 * 4) +
                               local_c0 * *(float *)(iVar12 + 8 + iVar7 * 4) + local_b4;
                iVar7 = piVar9[4] * iVar8;
                local_138[5] = local_d4 * *(float *)(iVar12 + 4 + iVar7 * 4) +
                               local_c8 * *(float *)(iVar12 + 8 + iVar7 * 4) +
                               local_e0 * *(float *)(iVar12 + iVar7 * 4) + local_bc;
                local_138[6] = local_d0 * *(float *)(iVar12 + 4 + iVar7 * 4) +
                               local_c4 * *(float *)(iVar12 + 8 + iVar7 * 4) +
                               local_dc * *(float *)(iVar12 + iVar7 * 4) + local_b8;
                local_138[7] = local_d8 * *(float *)(iVar12 + iVar7 * 4) +
                               local_cc * *(float *)(iVar12 + 4 + iVar7 * 4) +
                               local_c0 * *(float *)(iVar12 + 8 + iVar7 * 4) + local_b4;
                iVar8 = piVar9[5] * iVar8;
                local_138[8] = local_d4 * *(float *)(iVar12 + 4 + iVar8 * 4) +
                               local_c8 * *(float *)(iVar12 + 8 + iVar8 * 4) +
                               local_e0 * *(float *)(iVar12 + iVar8 * 4) + local_bc;
                local_174 = 0.0;
                pfVar10 = local_138 + 2;
                local_17c = 3;
                local_138[9] = local_d0 * *(float *)(iVar12 + 4 + iVar8 * 4) +
                               local_c4 * *(float *)(iVar12 + 8 + iVar8 * 4) +
                               local_dc * *(float *)(iVar12 + iVar8 * 4) + local_b8;
                local_138[10] =
                     local_d8 * *(float *)(iVar12 + iVar8 * 4) +
                     local_cc * *(float *)(iVar12 + 4 + iVar8 * 4) +
                     local_c0 * *(float *)(iVar12 + 8 + iVar8 * 4) + local_b4;
                local_80 = (local_138[8] + local_138[5] + local_138[2]) * _DAT_005a8428;
                local_7c = (local_138[9] + local_138[6] + local_138[3]) * _DAT_005a8428;
                local_78 = (local_138[10] + local_138[7] + local_138[4]) * _DAT_005a8428;
                do {
                  fVar13 = (float10)FUN_00431fd0(&local_80,pfVar10);
                  if ((float10)local_174 < fVar13) {
                    local_174 = (float)fVar13;
                  }
                  pfVar10 = pfVar10 + 3;
                  local_17c = local_17c + -1;
                } while (local_17c != 0);
                fVar13 = (float10)FUN_00431fd0(&local_74,&local_80);
                if (fVar13 <= (float10)(SQRT(local_174) + SQRT(local_178)) *
                              (float10)(SQRT(local_174) + SQRT(local_178))) {
                  FUN_00430f30(&local_f0,local_138 + 2,local_138 + 5,local_138 + 8);
                  iVar7 = 0;
                  local_e4 = (-(local_f0 * local_138[2]) - local_ec * local_138[3]) -
                             local_e8 * local_138[4];
                  do {
                    iVar8 = 6;
                    if (iVar7 != 0) {
                      iVar8 = iVar7 + -3;
                    }
                    pfVar10 = local_154 + iVar8 + 1;
                    pfVar1 = local_154 + iVar8;
                    fVar4 = (local_154[iVar7 + 2] - local_154[iVar8 + 2]) * local_e8 +
                            (local_154[iVar7 + 1] - *pfVar10) * local_ec +
                            (local_154[iVar7] - *pfVar1) * local_f0;
                    fVar5 = fVar4;
                    if (fVar4 <= _DAT_005a83e4) {
                      fVar5 = -fVar4;
                    }
                    if (((_DAT_005a8408 < fVar5) &&
                        (fVar4 = -((local_e8 * local_154[iVar8 + 2] +
                                    local_ec * *pfVar10 + local_f0 * *pfVar1 + local_e4) / fVar4),
                        _DAT_005a83e4 <= fVar4)) &&
                       (fVar4 < _DAT_005a83f4 != (fVar4 == _DAT_005a83f4))) {
                      local_60 = (local_154[iVar7] - *pfVar1) * fVar4 + *pfVar1;
                      local_5c = (local_154[iVar7 + 1] - *pfVar10) * fVar4 + *pfVar10;
                      local_58 = (local_154[iVar7 + 2] - local_154[iVar8 + 2]) * fVar4 +
                                 local_154[iVar8 + 2];
                      FUN_00430f30(local_10c,local_138 + 8,local_138 + 2,&local_60);
                      fVar13 = (float10)FUN_00529c80(local_10c,&local_f0);
                      if ((float10)_DAT_005a83e4 <= fVar13) {
                        FUN_00430f30(local_10c,local_138 + 2,local_138 + 5,&local_60);
                        fVar13 = (float10)FUN_00529c80(local_10c,&local_f0);
                        if ((float10)_DAT_005a83e4 <= fVar13) {
                          FUN_00430f30(local_10c,local_138 + 5,local_138 + 8,&local_60);
                          fVar13 = (float10)FUN_00529c80(local_10c,&local_f0);
                          if ((float10)_DAT_005a83e4 <= fVar13) {
                            param_1[0x57] = local_170;
                            param_2[0x57] = local_158;
                            return 1;
                          }
                        }
                      }
                    }
                    iVar7 = iVar7 + 3;
                  } while (iVar7 < 0xc);
                  iVar7 = 0;
                  do {
                    iVar8 = 6;
                    if (iVar7 != 0) {
                      iVar8 = iVar7 + -3;
                    }
                    pfVar10 = local_138 + iVar8 + 3;
                    pfVar1 = local_138 + iVar8 + 2;
                    fVar4 = (local_138[iVar7 + 4] - local_138[iVar8 + 4]) * local_f8 +
                            (local_138[iVar7 + 3] - *pfVar10) * local_fc +
                            (local_138[iVar7 + 2] - *pfVar1) * local_100;
                    fVar5 = fVar4;
                    if (fVar4 <= _DAT_005a83e4) {
                      fVar5 = -fVar4;
                    }
                    if (((_DAT_005a8408 < fVar5) &&
                        (fVar4 = -((local_100 * *pfVar1 +
                                    local_f8 * local_138[iVar8 + 4] + local_fc * *pfVar10 + local_f4
                                   ) / fVar4), _DAT_005a83e4 <= fVar4)) &&
                       (fVar4 < _DAT_005a83f4 != (fVar4 == _DAT_005a83f4))) {
                      local_60 = (local_138[iVar7 + 2] - *pfVar1) * fVar4 + *pfVar1;
                      local_5c = (local_138[iVar7 + 3] - *pfVar10) * fVar4 + *pfVar10;
                      local_58 = (local_138[iVar7 + 4] - local_138[iVar8 + 4]) * fVar4 +
                                 local_138[iVar8 + 4];
                      FUN_00430f30(local_10c,&local_13c,local_154,&local_60);
                      fVar13 = (float10)FUN_00529c80(local_10c,&local_100);
                      if ((float10)_DAT_005a83e4 <= fVar13) {
                        FUN_00430f30(local_10c,local_154,local_154 + 3,&local_60);
                        fVar13 = (float10)FUN_00529c80(local_10c,&local_100);
                        if ((float10)_DAT_005a83e4 <= fVar13) {
                          FUN_00430f30(local_10c,local_154 + 3,&local_13c,&local_60);
                          fVar13 = (float10)FUN_00529c80(local_10c,&local_100);
                          if ((float10)_DAT_005a83e4 <= fVar13) {
                            param_1[0x57] = local_170;
                            param_2[0x57] = local_158;
                            return 1;
                          }
                        }
                      }
                    }
                    iVar7 = iVar7 + 1;
                    piVar9 = local_15c;
                  } while (iVar7 < 3);
                }
                piVar9 = piVar9 + DAT_005c4314;
                iVar8 = local_68;
                local_15c = piVar9;
              }
              else if (*piVar9 == 2) {
                piVar9 = piVar9 + piVar9[2] * 2 + 3;
                local_15c = piVar9;
              }
              local_170 = local_170 + 1;
            } while ((int)local_170 < *(int *)(param_2[0x27] + 0x34));
          }
          piVar9 = local_160 + DAT_005c4314;
          iVar7 = local_64;
          local_160 = piVar9;
        }
        else if (*piVar9 == 2) {
          piVar9 = piVar9 + piVar9[2] * 2 + 3;
          local_160 = piVar9;
        }
        local_158 = local_158 + 1;
      } while ((int)local_158 < *(int *)(param_1[0x27] + 0x34));
    }
  }
  return 0;
}

