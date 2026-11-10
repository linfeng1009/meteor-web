/* Original Meteor.exe static export @ 00409b80; original sample not executed. */
/* XREF 00408ee0 UNCONDITIONAL_JUMP */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00409b80(uint *param_1,uint *param_2)

{
  uint uVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int *piVar6;
  undefined1 *puVar7;
  uint *puVar8;
  int iVar9;
  int *piVar10;
  float10 fVar11;
  float local_17c;
  float local_178;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  uint local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  undefined1 local_dc [12];
  int local_d0;
  undefined1 local_cc [12];
  float local_c0 [5];
  float afStack_ac [19];
  undefined1 local_60 [96];
  
  FUN_00406ed0(*param_1 | 0x2000000,local_cc,local_c0,0);
  local_178 = 0.0;
  pfVar5 = local_c0;
  iVar9 = 8;
  do {
    fVar11 = (float10)FUN_00431fd0(local_cc,pfVar5);
    if ((float10)local_178 < fVar11) {
      local_178 = (float)fVar11;
    }
    pfVar5 = pfVar5 + 3;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  local_178 = SQRT(local_178);
  FUN_00406ed0(*param_2 | 0x2000000,&local_f4,local_60,0);
  local_17c = 0.0;
  puVar7 = local_60;
  iVar9 = 8;
  do {
    fVar11 = (float10)FUN_00431fd0(&local_f4,puVar7);
    if ((float10)local_17c < fVar11) {
      local_17c = (float)fVar11;
    }
    puVar7 = puVar7 + 0xc;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  fVar11 = (float10)FUN_00431fd0(local_cc,&local_f4);
  if (fVar11 <= (float10)(SQRT(local_17c) + local_178) * (float10)(SQRT(local_17c) + local_178)) {
    FUN_00430c20(&local_12c);
    puVar8 = param_2;
    do {
      if (puVar8[0x22] != 0) {
        FUN_00431180(&local_12c,&local_12c,puVar8 + 2);
      }
      puVar8 = (uint *)puVar8[0x49];
    } while (puVar8 != (uint *)0x0);
    uVar1 = param_2[0x27];
    local_d0 = DAT_007eac64;
    local_160 = 0;
    piVar6 = *(int **)(uVar1 + 0x40);
    iVar9 = *(int *)(uVar1 + 0x1c);
    iVar4 = DAT_007eac64;
    if (0 < *(int *)(uVar1 + 0x34)) {
LAB_00409d07:
      if (*piVar6 == 1) {
        iVar3 = piVar6[3] * iVar4;
        local_150 = local_12c * *(float *)(iVar9 + iVar3 * 4) +
                    local_114 * *(float *)(iVar9 + 8 + iVar3 * 4) +
                    local_120 * *(float *)(iVar9 + 4 + iVar3 * 4) + local_108;
        local_14c = local_128 * *(float *)(iVar9 + iVar3 * 4) +
                    local_110 * *(float *)(iVar9 + 8 + iVar3 * 4) +
                    local_11c * *(float *)(iVar9 + 4 + iVar3 * 4) + local_104;
        local_148 = local_124 * *(float *)(iVar9 + iVar3 * 4) +
                    local_10c * *(float *)(iVar9 + 8 + iVar3 * 4) +
                    local_118 * *(float *)(iVar9 + 4 + iVar3 * 4) + local_100;
        iVar3 = piVar6[4] * iVar4;
        local_144 = local_12c * *(float *)(iVar9 + iVar3 * 4) +
                    local_114 * *(float *)(iVar9 + 8 + iVar3 * 4) +
                    local_120 * *(float *)(iVar9 + 4 + iVar3 * 4) + local_108;
        local_140 = local_128 * *(float *)(iVar9 + iVar3 * 4) +
                    local_110 * *(float *)(iVar9 + 8 + iVar3 * 4) +
                    local_11c * *(float *)(iVar9 + 4 + iVar3 * 4) + local_104;
        local_13c = local_124 * *(float *)(iVar9 + iVar3 * 4) +
                    local_10c * *(float *)(iVar9 + 8 + iVar3 * 4) +
                    local_118 * *(float *)(iVar9 + 4 + iVar3 * 4) + local_100;
        iVar4 = piVar6[5] * iVar4;
        local_138 = local_12c * *(float *)(iVar9 + iVar4 * 4) +
                    local_114 * *(float *)(iVar9 + 8 + iVar4 * 4) +
                    local_120 * *(float *)(iVar9 + 4 + iVar4 * 4) + local_108;
        local_17c = 0.0;
        pfVar5 = &local_150;
        iVar3 = 3;
        local_134 = local_128 * *(float *)(iVar9 + iVar4 * 4) +
                    local_110 * *(float *)(iVar9 + 8 + iVar4 * 4) +
                    local_11c * *(float *)(iVar9 + 4 + iVar4 * 4) + local_104;
        local_130 = local_124 * *(float *)(iVar9 + iVar4 * 4) +
                    local_10c * *(float *)(iVar9 + 8 + iVar4 * 4) +
                    local_118 * *(float *)(iVar9 + 4 + iVar4 * 4) + local_100;
        local_f4 = (local_138 + local_144 + local_150) * _DAT_005a8428;
        local_f0 = (local_134 + local_140 + local_14c) * _DAT_005a8428;
        local_ec = (local_130 + local_13c + local_148) * _DAT_005a8428;
        do {
          fVar11 = (float10)FUN_00431fd0(&local_f4,pfVar5);
          if ((float10)local_17c < fVar11) {
            local_17c = (float)fVar11;
          }
          pfVar5 = pfVar5 + 3;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        fVar11 = (float10)FUN_00431fd0(local_cc,&local_f4);
        if (fVar11 <= (float10)(SQRT(local_17c) + local_178) *
                      (float10)(SQRT(local_17c) + local_178)) {
          FUN_00430f30(&local_170,&local_150,&local_144,&local_138);
          iVar4 = 0;
          pfVar5 = local_c0;
          local_164 = (-(local_170 * local_150) - local_16c * local_14c) - local_168 * local_148;
          do {
            iVar3 = iVar4 + 5;
            iVar4 = iVar4 + 1;
            fVar2 = local_170 * *pfVar5 + local_16c * pfVar5[1] + local_168 * local_c0[iVar3] +
                    local_164;
            if (fVar2 != _DAT_005a83e4) {
              if (7 < iVar4) goto LAB_0040a012;
              pfVar5 = local_c0 + iVar4 * 3 + 1;
              goto LAB_00409fd9;
            }
            pfVar5 = pfVar5 + 3;
          } while (iVar4 < 8);
          goto LAB_0040a018;
        }
        goto LAB_0040a233;
      }
      if (*piVar6 == 2) {
        piVar6 = piVar6 + piVar6[2] * 2 + 3;
      }
      goto LAB_0040a258;
    }
  }
  return 0;
  while( true ) {
    iVar4 = iVar4 + 1;
    pfVar5 = pfVar5 + 3;
    if (7 < iVar4) break;
LAB_00409fd9:
    if ((local_16c * *pfVar5 + local_170 * pfVar5[-1] + local_168 * pfVar5[1] + local_164) * fVar2 <
        _DAT_005a83e4) break;
  }
LAB_0040a012:
  if (iVar4 != 8) {
LAB_0040a018:
    piVar10 = &DAT_005c43bc;
    do {
      iVar4 = piVar10[-1];
      local_15c = local_c0[iVar4 * 3];
      local_158 = local_c0[iVar4 * 3 + 1];
      local_154 = local_c0[iVar4 * 3 + 2];
      iVar4 = *piVar10;
      local_f8 = local_c0[iVar4 * 3 + 2] - local_154;
      local_fc = local_c0[iVar4 * 3 + 1] - local_158;
      local_178 = local_f8 * local_168 +
                  local_fc * local_16c + (local_c0[iVar4 * 3] - local_15c) * local_170;
      fVar2 = local_178;
      if (local_178 <= _DAT_005a83e4) {
        fVar2 = -local_178;
      }
      if (((_DAT_005a8408 < fVar2) &&
          (fVar2 = -((local_15c * local_170 + local_158 * local_16c + local_154 * local_168 +
                     local_164) / local_178), _DAT_005a83e4 <= fVar2)) &&
         (fVar2 < _DAT_005a83f4 != (fVar2 == _DAT_005a83f4))) {
        local_e8 = (local_c0[iVar4 * 3] - local_15c) * fVar2 + local_15c;
        local_e4 = local_fc * fVar2 + local_158;
        local_e0 = local_f8 * fVar2 + local_154;
        FUN_00430f30(local_dc,&local_138,&local_150,&local_e8);
        fVar11 = (float10)FUN_00529c80(local_dc,&local_170);
        if ((float10)_DAT_005a83e4 <= fVar11) {
          FUN_00430f30(local_dc,&local_150,&local_144,&local_e8);
          fVar11 = (float10)FUN_00529c80(local_dc,&local_170);
          if ((float10)_DAT_005a83e4 <= fVar11) {
            FUN_00430f30(local_dc,&local_144,&local_138,&local_e8);
            fVar11 = (float10)FUN_00529c80(local_dc,&local_170);
            if ((float10)_DAT_005a83e4 <= fVar11) {
              param_1[0x57] = local_160;
              return 1;
            }
          }
        }
      }
      piVar10 = piVar10 + 2;
    } while ((int)piVar10 < 0x5c441c);
  }
LAB_0040a233:
  piVar6 = piVar6 + DAT_005c4314;
  iVar4 = local_d0;
LAB_0040a258:
  local_160 = local_160 + 1;
  if (*(int *)(param_2[0x27] + 0x34) <= (int)local_160) {
    return 0;
  }
  goto LAB_00409d07;
}

