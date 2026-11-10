/* Original Meteor.exe static export @ 00585ff0; original sample not executed. */
/* XREF 005876cb UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00585ff0(int param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float *pfVar11;
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
  float *local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  int local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  int local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  int local_a0;
  float local_98;
  float local_94;
  float local_8c;
  float local_88;
  float local_80;
  float local_7c;
  float local_74;
  float local_70;
  float local_68;
  float local_64;
  float local_5c;
  float local_58;
  float local_50;
  float local_4c;
  float local_44;
  float local_40;
  float local_38;
  float local_34;
  float local_2c;
  float local_28;
  float local_20;
  float local_1c;
  float local_14;
  float local_10;
  float local_4;
  
  iVar1 = *(int *)(param_1 + 0x28c);
  if (iVar1 != 0) {
    local_a0 = param_1;
    FUN_00481b30();
    pfVar11 = DAT_0072bc00;
    local_10c = DAT_0072bc00;
    iVar2 = *(int *)(*(int *)(param_1 + 0x1ec) + 0x10);
    local_128 = *(float *)(iVar2 + 0x24);
    local_124 = *(float *)(iVar2 + 0x28);
    local_120 = *(float *)(iVar2 + 0x2c);
    if (*(int *)(param_1 + 0x318) == 0) {
      pfVar5 = (float *)FUN_00476090(0);
      local_140 = -*pfVar5;
      local_13c = -pfVar5[1];
      local_138 = -pfVar5[2];
      pfVar5 = (float *)FUN_00476090(1);
      local_134 = *pfVar5;
      local_140 = local_128 * local_140;
      local_130 = local_124 * pfVar5[1];
      local_12c = local_120 * pfVar5[2];
    }
    local_e4 = *(int *)(*(int *)(param_1 + 0x1ec) + 0x10);
    local_c8 = 0;
    if (0 < *(int *)(param_1 + 0x268)) {
      pfVar11 = pfVar11 + 0xc;
      pfVar5 = (float *)(iVar1 + 0x10);
      do {
        if (*(int *)(param_1 + 0x318) != 0) {
          FUN_00477d30(0,&local_140);
          FUN_00477d30(1,&local_134);
        }
        iVar2 = local_a0;
        iVar1 = local_e4;
        fVar7 = pfVar5[0x1e] * _DAT_005a83e8;
        fVar3 = local_134 * fVar7;
        if (*(int *)(param_1 + 0x31c) == 0) {
          local_14 = fVar7 * local_130;
          local_10 = fVar7 * local_12c;
          fVar7 = pfVar5[0x1d] * _DAT_005a83e8;
          local_5c = local_13c * fVar7;
          local_58 = local_138 * fVar7;
          local_74 = pfVar5[-1] - local_5c;
          local_70 = *pfVar5 - local_58;
          fVar6 = (pfVar5[-2] - local_140 * fVar7) - fVar3;
          fVar8 = local_74 - local_14;
          fVar9 = local_70 - local_10;
          fVar7 = pfVar5[0x1d];
          local_8c = local_13c * fVar7;
          local_88 = local_138 * fVar7;
          fVar10 = local_140 * fVar7 + fVar6;
          local_d0 = local_8c + fVar8;
          local_cc = local_88 + fVar9;
          fVar7 = pfVar5[0x1e];
          local_2c = fVar7 * local_130;
          local_28 = fVar7 * local_12c;
          local_e0 = local_134 * fVar7 + fVar10;
          local_dc = local_2c + local_d0;
          local_d8 = local_28 + local_cc;
          fVar7 = pfVar5[0x1e];
          local_44 = fVar7 * local_130;
          local_40 = fVar7 * local_12c;
          local_128 = local_134 * fVar7 + fVar6;
          local_124 = local_44 + fVar8;
          local_120 = local_40 + fVar9;
          local_118 = fVar6;
          local_114 = fVar8;
          local_110 = fVar9;
          local_d4 = fVar10;
          local_c4 = local_e0;
          local_c0 = local_dc;
          local_bc = local_d8;
          local_b8 = local_128;
          local_b4 = local_124;
          local_b0 = local_120;
          local_98 = local_d0;
          local_94 = local_cc;
        }
        else {
          local_a8 = local_130 * fVar7;
          local_a4 = fVar7 * local_12c;
          fVar4 = pfVar5[0x1d] * _DAT_005a83e8;
          local_80 = local_13c * fVar4;
          local_7c = local_138 * fVar4;
          local_4 = *pfVar5 - local_7c;
          fVar6 = (pfVar5[-2] - local_140 * fVar4) - fVar3;
          fVar8 = (pfVar5[-1] - local_80) - local_a8;
          fVar9 = local_4 - local_a4;
          fVar7 = pfVar5[0x1d];
          local_68 = local_13c * fVar7;
          local_64 = local_138 * fVar7;
          fVar10 = local_140 * fVar7 + fVar6;
          local_f8 = local_68 + fVar8;
          local_f4 = local_64 + fVar9;
          local_20 = local_13c * fVar4;
          local_1c = local_138 * fVar4;
          fVar7 = pfVar5[0x1e];
          local_50 = fVar7 * local_130;
          local_4c = fVar7 * local_12c;
          local_38 = local_50 + local_f8;
          local_34 = local_4c + local_f4;
          local_128 = (local_134 * fVar7 + fVar10) - local_140 * fVar4;
          local_124 = local_38 - local_20;
          local_120 = local_34 - local_1c;
          local_108 = fVar6;
          local_104 = fVar8;
          local_100 = fVar9;
          local_fc = fVar10;
          local_f0 = local_128;
          local_ec = local_124;
          local_e8 = local_120;
          local_e0 = local_128;
          local_dc = local_124;
          local_d8 = local_120;
          local_ac = fVar3;
          local_98 = local_f8;
          local_94 = local_f4;
        }
        *local_10c = fVar6;
        local_10c[1] = fVar8;
        local_10c[2] = fVar9;
        pfVar11[-6] = fVar10;
        pfVar11[-5] = local_98;
        pfVar11[-4] = local_94;
        *pfVar11 = local_e0;
        pfVar11[1] = local_dc;
        pfVar11[2] = local_d8;
        pfVar11[6] = local_128;
        pfVar11[7] = local_124;
        pfVar11[8] = local_120;
        local_11c = pfVar5[0x21] / pfVar5[0x23];
        if ((*(int *)(local_a0 + 0x280) != 0) && (local_11c < *(float *)(local_a0 + 0x278))) {
          fVar7 = (float)FUN_00475c00(*(undefined4 *)(local_e4 + 0x40),
                                      *(undefined4 *)(local_e4 + 0x44),
                                      *(undefined4 *)(local_e4 + 0x48),
                                      (_DAT_005a83f4 -
                                      (*(float *)(local_a0 + 0x278) - local_11c) /
                                      *(float *)(local_a0 + 0x278)) * *(float *)(local_e4 + 0x70));
          pfVar11[-9] = fVar7;
          pfVar11[-3] = fVar7;
          pfVar11[3] = fVar7;
          pfVar11[9] = fVar7;
        }
        if ((*(int *)(iVar2 + 0x284) != 0) && (*(float *)(iVar2 + 0x27c) < local_11c)) {
          fVar7 = (float)FUN_00475c00(*(undefined4 *)(iVar1 + 0x40),*(undefined4 *)(iVar1 + 0x44),
                                      *(undefined4 *)(iVar1 + 0x48),
                                      (_DAT_005a83f4 -
                                      (local_11c - *(float *)(iVar2 + 0x27c)) /
                                      (_DAT_005a83f4 - *(float *)(iVar2 + 0x27c))) *
                                      *(float *)(iVar1 + 0x70));
          pfVar11[-9] = fVar7;
          pfVar11[-3] = fVar7;
          pfVar11[3] = fVar7;
          pfVar11[9] = fVar7;
        }
        local_10c = local_10c + 0x18;
        pfVar11 = pfVar11 + 0x18;
        local_c8 = local_c8 + 1;
        pfVar5 = pfVar5 + 0x2b;
        param_1 = iVar2;
      } while (local_c8 < *(int *)(iVar2 + 0x268));
    }
    FUN_00481b90();
  }
  return;
}

