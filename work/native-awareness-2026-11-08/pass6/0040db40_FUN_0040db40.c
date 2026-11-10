/* Original Meteor.exe static export @ 0040db40; original sample not executed. */
/* XREF 0040db30 UNCONDITIONAL_JUMP */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_0040db40(int param_1,undefined4 *param_2,int param_3,uint param_4,int param_5,int param_6,
            uint *param_7,int param_8,float *param_9,float *param_10)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int *piVar6;
  uint *puVar7;
  int iVar8;
  float *pfVar9;
  bool bVar10;
  float10 fVar11;
  float10 fVar12;
  float *pfVar13;
  float *pfVar14;
  uint *local_e34;
  int *local_e30;
  float local_e2c;
  float local_e28;
  float local_e24;
  float local_e20;
  uint local_e1c;
  float local_e18;
  float local_e14;
  float local_e10;
  float local_e0c;
  int local_e08;
  float local_e04;
  float local_e00;
  float local_dfc;
  float local_df8;
  float *local_df4;
  float local_df0;
  float local_dec;
  float local_de8;
  float local_de4;
  float local_de0;
  float local_ddc;
  int local_dd8;
  int local_dd4;
  int local_dd0;
  int local_dcc [4];
  float local_dbc;
  float local_db8;
  float local_db4;
  float local_db0;
  float local_dac;
  float local_da8;
  float local_da0;
  float local_d9c;
  float local_d98;
  float local_d90;
  float local_d8c;
  float local_d88;
  undefined1 local_d70 [48];
  float local_d40 [24];
  undefined1 local_ce0 [64];
  undefined1 local_ca0 [64];
  undefined1 local_c60 [84];
  float afStack_c0c [4];
  float local_bfc;
  float local_bf8;
  float local_bf4 [765];
  
  if (DAT_005d5a00 == 0) {
    return 0;
  }
  if (DAT_005d5a0c == 0) {
    return 0;
  }
  if (param_1 == 0) {
    iVar5 = *(int *)(DAT_005d5a0c + 0x6c8);
  }
  else {
    iVar5 = FUN_00410b30(param_1);
    if (iVar5 == 0) {
      return 0;
    }
  }
  if (*(int *)(iVar5 + 0x14) == 0) {
    return 0;
  }
  iVar8 = *(int *)(*(int *)(iVar5 + 0x14) + 0x9c);
  if (iVar8 == 0) {
    return 0;
  }
  if ((DAT_005c4308 == 0) && (DAT_005c431c == 0)) {
    param_6 = param_6 / 2;
  }
  FUN_00430c20(local_d70);
  for (iVar1 = *(int *)(iVar5 + 0x14); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x124)) {
    if (*(int *)(iVar1 + 0x88) != 0) {
      FUN_00431180(local_d70,local_d70,iVar1 + 8);
    }
  }
  FUN_00431520(local_d70,&local_db0);
  FUN_004315e0(&local_db0,local_ca0);
  local_e18 = (*(float *)(iVar8 + 0x18) / (*(float *)(iVar8 + 0x10) * _DAT_005a8434)) *
              *(float *)(iVar8 + 0x14);
  fVar2 = -local_e18;
  fVar3 = local_e18 / *(float *)(iVar8 + 8);
  fVar4 = -fVar3;
  local_e18 = local_e18 - fVar2;
  local_de4 = (*(float *)(iVar8 + 100) + _DAT_005a83f4) * local_e18 * _DAT_005a83e8 + fVar2;
  fVar3 = fVar3 - fVar4;
  local_de0 = (*(float *)(iVar8 + 0x68) + _DAT_005a83f4) * fVar3 * _DAT_005a83e8 + fVar4;
  local_de4 = ((((*(float *)(iVar8 + 0x6c) + *(float *)(iVar8 + 100) + _DAT_005a83f4) * local_e18 *
                 _DAT_005a83e8 + fVar2) - local_de4) * (float)(param_5 - *(int *)(iVar5 + 4))) /
              (float)*(int *)(iVar5 + 0xc) + local_de4;
  local_e08 = *(int *)(iVar5 + 0x10);
  local_e04 = -NAN;
  local_e20 = 1e+10;
  local_de0 = ((((*(float *)(iVar8 + 0x70) + *(float *)(iVar8 + 0x68) + _DAT_005a83f4) * fVar3 *
                 _DAT_005a83e8 + fVar4) - local_de0) *
              (float)((*(int *)(iVar5 + 8) - param_6) + local_e08)) / (float)local_e08 + local_de0;
  local_ddc = -*(float *)(iVar8 + 0x18);
  local_e1c = 0;
  if (param_2 == (undefined4 *)0x0) {
    local_e34 = (uint *)**(undefined4 **)(DAT_005d5a0c + 0x69c);
  }
  else {
    local_e34 = (uint *)FUN_00410a70(*param_2);
    local_e08 = 0;
  }
  if (local_e34 != (uint *)0x0) {
    do {
      if (local_e34[0x59] == 0) {
        bVar10 = local_e34[0x23] != param_4;
      }
      else if (local_e34[0x58] == 0) {
        bVar10 = *(uint *)(*(int *)(local_e34[0x59] + 8) + 0x8c) != param_4;
      }
      else {
        bVar10 = false;
      }
      if (((local_e34[1] == 6) && ((*(byte *)(local_e34[0x27] + 4) & 0x10) == 0)) && (bVar10)) {
        local_dd0 = DAT_007eac64;
        FUN_00406ed0(*local_e34 | 0x2000000,0,local_c60,0);
        iVar5 = 0;
        do {
          FUN_00476e20((int)local_d40 + iVar5,local_c60 + iVar5,local_ca0);
          iVar5 = iVar5 + 0xc;
        } while (iVar5 < 0x60);
        piVar6 = &DAT_005c435c;
LAB_0040de61:
        iVar5 = piVar6[-1];
        local_dcc[0] = iVar5 * 3;
        local_dcc[1] = *piVar6 * 3;
        local_dcc[2] = piVar6[1] * 3;
        iVar8 = piVar6[2];
        local_dcc[3] = iVar8 * 3;
        FUN_00430f30(&local_e2c,local_d40 + iVar5 * 3,local_d40 + *piVar6 * 3,
                     local_d40 + piVar6[1] * 3);
        fVar11 = (float10)FUN_00529c80(&local_e2c,&local_de4);
        fVar12 = fVar11;
        if (fVar11 <= (float10)_DAT_005a83e4) {
          fVar12 = -fVar11;
        }
        if (fVar12 <= (float10)_DAT_005a8408) goto LAB_0040e064;
        local_df4 = local_d40 + iVar8 * 3;
        fVar12 = ((float10)_DAT_005a8430 / fVar11) *
                 ((-((float10)local_e2c * (float10)local_d40[iVar8 * 3]) -
                  (float10)local_e28 * (float10)local_d40[iVar8 * 3 + 1]) -
                 (float10)local_e24 * (float10)local_d40[iVar8 * 3 + 2]);
        if (fVar12 <= (float10)_DAT_005a83f4) goto LAB_0040e064;
        iVar8 = 0;
        local_e14 = (float)((float10)local_de4 * fVar12);
        local_e10 = (float)((float10)local_de0 * fVar12);
        local_e0c = (float)(fVar12 * (float10)local_ddc);
        do {
          pfVar9 = local_d40 + iVar5 * 3;
          pfVar14 = local_df4;
          if (iVar8 != 3) {
            pfVar9 = local_d40 + local_dcc[iVar8 + 1];
            pfVar14 = local_d40 + local_dcc[iVar8];
          }
          FUN_00430f30(&local_e00,pfVar9,&local_e14,pfVar14);
          fVar12 = (float10)FUN_00529c80(&local_e00,&local_e2c);
        } while ((fVar12 < (float10)_DAT_005a83e4 == (fVar12 == (float10)_DAT_005a83e4)) &&
                (iVar8 = iVar8 + 1, iVar8 < 4));
        if (iVar8 != 4) goto LAB_0040e064;
        FUN_00430c20(local_d70);
        puVar7 = local_e34;
        do {
          if (puVar7[0x22] != 0) {
            FUN_00431180(local_d70,local_d70,puVar7 + 2);
          }
          puVar7 = (uint *)puVar7[0x49];
        } while (puVar7 != (uint *)0x0);
        FUN_00431520(local_d70,local_ce0);
        FUN_004312e0(local_ce0,local_ce0,local_ca0);
        local_df4 = (float *)local_e34[0x27];
        local_e30 = (int *)local_df4[0x10];
        local_e18 = 0.0;
        if (0 < (int)local_df4[0xd]) {
          local_e18 = 0.0;
          iVar5 = local_dd4;
          do {
            if (*local_e30 == 1) {
              iVar5 = 3;
              local_dd4 = 3;
              pfVar9 = afStack_c0c;
              piVar6 = local_e30 + 3;
              iVar8 = 3;
              do {
                pfVar9 = pfVar9 + 3;
                FUN_00476e20(pfVar9,(int)local_df4[7] + *piVar6 * local_dd0 * 4,local_ce0);
                piVar6 = piVar6 + 1;
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              local_dd8 = 1;
              local_e30 = local_e30 + DAT_005c4314;
LAB_0040e10c:
              iVar8 = 0;
              if (0 < iVar5) {
                while( true ) {
                  if (iVar8 == 0) {
                    pfVar13 = local_bf4;
                    pfVar14 = afStack_c0c + 3;
                    pfVar9 = afStack_c0c + iVar5 * 3;
                  }
                  else {
                    pfVar14 = afStack_c0c + iVar8 * 3 + 3;
                    pfVar13 = local_bf4 + iVar8 * 3;
                    pfVar9 = afStack_c0c + iVar8 * 3;
                  }
                  FUN_00430f30(&local_e2c,pfVar9,pfVar14,pfVar13);
                  fVar2 = local_e2c;
                  if (local_e2c <= _DAT_005a83e4) {
                    fVar2 = -local_e2c;
                  }
                  if (_DAT_005a8408 < fVar2) break;
                  fVar2 = local_e28;
                  if (local_e28 <= _DAT_005a83e4) {
                    fVar2 = -local_e28;
                  }
                  if (_DAT_005a8408 < fVar2) break;
                  fVar2 = local_e24;
                  if (local_e24 <= _DAT_005a83e4) {
                    fVar2 = -local_e24;
                  }
                  if ((_DAT_005a8408 < fVar2) || (iVar8 = iVar8 + 1, iVar5 <= iVar8)) break;
                }
              }
              fVar12 = (float10)FUN_00529c80(&local_e2c,&local_de4);
              if ((fVar12 < (float10)_DAT_005a83e4) &&
                 (fVar12 = ((float10)_DAT_005a8430 / fVar12) *
                           ((-((float10)afStack_c0c[3] * (float10)local_e2c) -
                            (float10)local_bfc * (float10)local_e28) -
                           (float10)local_bf8 * (float10)local_e24), (float10)_DAT_005a83f4 < fVar12
                 )) {
                iVar8 = 0;
                local_e14 = (float)((float10)local_de4 * fVar12);
                local_e10 = (float)((float10)local_de0 * fVar12);
                local_e0c = (float)(fVar12 * (float10)local_ddc);
                if (0 < iVar5) {
                  pfVar9 = local_bf4;
                  do {
                    if (iVar8 == iVar5 + -1) {
                      pfVar14 = afStack_c0c + iVar5 * 3;
                      pfVar13 = afStack_c0c + 3;
                    }
                    else {
                      pfVar14 = pfVar9 + -3;
                      pfVar13 = pfVar9;
                    }
                    FUN_00430f30(&local_e00,pfVar13,&local_e14,pfVar14);
                    fVar2 = local_e00;
                    if (local_e00 <= _DAT_005a83e4) {
                      fVar2 = -local_e00;
                    }
                    if (fVar2 <= _DAT_005a8408) {
                      fVar2 = local_dfc;
                      if (local_dfc <= _DAT_005a83e4) {
                        fVar2 = -local_dfc;
                      }
                      if (fVar2 <= _DAT_005a8408) {
                        fVar2 = local_df8;
                        if (local_df8 <= _DAT_005a83e4) {
                          fVar2 = -local_df8;
                        }
                        if (fVar2 <= _DAT_005a8408) break;
                      }
                    }
                    fVar12 = (float10)FUN_00529c80(&local_e00,&local_e2c);
                    if (fVar12 < (float10)_DAT_005a83e4) break;
                    iVar8 = iVar8 + 1;
                    pfVar9 = pfVar9 + 3;
                  } while (iVar8 < iVar5);
                }
                if (iVar8 == iVar5) {
                  fVar2 = local_e0c;
                  if (local_e0c <= _DAT_005a83e4) {
                    fVar2 = -local_e0c;
                  }
                  if (fVar2 < local_e20) {
                    local_e04 = local_e18;
                    if (local_e0c <= _DAT_005a83e4) {
                      local_e20 = -local_e0c;
                    }
                    else {
                      local_e20 = local_e0c;
                    }
                    local_e1c = *local_e34 | 0x2000000;
                    local_dbc = local_e14;
                    local_db4 = local_e0c;
                    local_db8 = local_e10;
                    local_df0 = local_e2c;
                    local_dec = local_e28;
                    local_de8 = local_e24;
                  }
                }
              }
            }
            else if (*local_e30 == 2) {
              local_dd8 = 0;
              local_e30 = local_e30 + local_e30[2] * 2 + 3;
            }
            else if (local_dd8 != 0) goto LAB_0040e10c;
            local_e18 = (float)((int)local_e18 + 1);
          } while ((int)local_e18 < (int)local_df4[0xd]);
        }
      }
LAB_0040e414:
      if (param_2 == (undefined4 *)0x0) {
        local_e34 = (uint *)local_e34[0x4c];
      }
      else {
        local_e08 = local_e08 + 1;
        if (param_3 <= local_e08) break;
        local_e34 = (uint *)FUN_00410a70(param_2[local_e08]);
      }
    } while (local_e34 != (uint *)0x0);
    if (local_e04 != -NAN) {
      if (param_7 != (uint *)0x0) {
        *param_7 = local_e1c;
      }
      if (param_9 != (float *)0x0) {
        *param_9 = local_e04;
      }
      if (param_8 != 0) {
        FUN_00476e20(param_8,&local_dbc,&local_db0);
      }
      if (param_10 != (float *)0x0) {
        *param_10 = local_db0 * local_df0 + local_da0 * local_dec + local_d90 * local_de8;
        param_10[1] = local_dac * local_df0 + local_d9c * local_dec + local_d8c * local_de8;
        param_10[2] = local_da8 * local_df0 + local_d98 * local_dec + local_d88 * local_de8;
      }
      return 1;
    }
  }
  return 0;
LAB_0040e064:
  piVar6 = piVar6 + 4;
  if (0x5c43bb < (int)piVar6) goto LAB_0040e414;
  goto LAB_0040de61;
}

