/* Original Meteor.exe static export @ 0047d2f0; original sample not executed. */
/* XREF 0047d94f UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0047d2f0(int param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
                 float param_7,int param_8,int param_9)

{
  int iVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  int local_16c;
  int local_168;
  float local_164;
  float local_160;
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
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
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
  double local_f4;
  float local_ec;
  float local_e8;
  float local_e4;
  double local_e0;
  float local_d8;
  float local_d4;
  float local_d0;
  undefined4 local_cc;
  float local_c8;
  float local_c4;
  undefined4 local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  undefined1 local_b0 [12];
  float local_a4;
  float local_a0;
  float local_9c;
  undefined1 local_98 [64];
  undefined1 local_58 [64];
  undefined1 local_18 [12];
  undefined1 local_c [12];
  
  local_cc = 0;
  local_c0 = 0;
  local_d8 = ((param_7 - param_6) * _DAT_005a8fec) / (float)DAT_005c8128;
  local_128 = 0;
  local_124 = 0;
  local_120 = 0x3f800000;
  local_12c = 0.0;
  local_138 = 0.0;
  local_164 = param_7 * _DAT_005a8fec;
  fVar6 = (float10)fcos((float10)param_4);
  local_d4 = (float)fVar6;
  fVar7 = (float10)fsin((float10)param_4);
  local_d0 = (float)fVar7;
  fVar8 = (float10)fcos((float10)param_5);
  local_f4 = (double)fVar8;
  local_c8 = (float)fVar8;
  fVar9 = (float10)fsin((float10)param_5);
  local_e0 = (double)fVar9;
  local_c4 = (float)fVar9;
  fVar2 = (param_3 - param_2) * _DAT_005a83e8;
  fVar10 = ((float10)param_2 + (float10)param_3) * (float10)_DAT_005a83e8;
  local_13c = (float)fVar10;
  local_134 = (float)(fVar10 * fVar6);
  local_130 = (float)((float10)local_13c * fVar7);
  local_140 = local_13c * (float)fVar8;
  local_13c = local_13c * (float)fVar9;
  FUN_00477200();
  FUN_00477200();
  FUN_00529c40(&local_d4,&local_128,local_b0);
  FUN_00477b90(0,&local_d4);
  FUN_00477b90(1,&local_128);
  FUN_00477b90(2,local_b0);
  FUN_00477b90(3,&local_134);
  FUN_00529c40(&local_c8,&local_128,local_b0);
  FUN_00477b90(0,&local_c8);
  FUN_00477b90(1,&local_128);
  FUN_00477b90(2,local_b0);
  FUN_00477b90(3,&local_140);
  FUN_00481b30();
  local_16c = 0;
  if (-1 < DAT_005c8128) {
    local_104 = (float)param_1;
    local_144 = fVar2 * _DAT_005a83e4;
    local_f4 = (double)CONCAT44(local_f4._4_4_,(float)(param_1 + 1));
    local_e4 = local_144;
    do {
      fVar6 = (float10)fcos((float10)local_164);
      local_108 = local_144;
      local_9c = local_144;
      local_154 = (float)fVar6;
      fVar7 = (float10)fsin((float10)local_164);
      local_e0 = (double)CONCAT44(local_e0._4_4_,(float)fVar7);
      local_110 = (float)(fVar6 * (float10)fVar2);
      local_10c = (float)(fVar7 * (float10)fVar2);
      local_a4 = local_110;
      local_a0 = local_10c;
      pfVar3 = (float *)FUN_00476e80(local_18,&local_a4,local_58);
      local_160 = *pfVar3;
      local_15c = pfVar3[1];
      local_150 = local_160 - local_134;
      local_158 = pfVar3[2];
      local_14c = local_15c - local_130;
      local_148 = local_158 - local_12c;
      local_100 = local_150;
      local_fc = local_14c;
      local_f8 = local_148;
      FUN_0047ec40();
      FUN_00481bd0(param_8,&local_160);
      FUN_00481c60(param_8,&local_150);
      FUN_00481d00(param_8,0xffffffff);
      FUN_00481d40(param_8,local_104 / (float)DAT_005c8124,(float)local_16c / (float)DAT_005c8128,
                   0xffffffff);
      local_ec = local_154 * fVar2;
      iVar4 = param_8 + 1;
      local_e8 = local_e0._0_4_ * fVar2;
      local_b4 = local_e4;
      local_bc = local_ec;
      local_b8 = local_e8;
      pfVar3 = (float *)FUN_00476e80(local_c,&local_bc,local_98);
      local_160 = *pfVar3;
      local_15c = pfVar3[1];
      local_150 = local_160 - local_140;
      local_158 = pfVar3[2];
      local_14c = local_15c - local_13c;
      local_148 = local_158 - local_138;
      local_11c = local_150;
      local_118 = local_14c;
      local_114 = local_148;
      FUN_0047ec40();
      FUN_00481bd0(iVar4,&local_160);
      FUN_00481c60(iVar4,&local_150);
      FUN_00481d00(iVar4,0xffffffff);
      FUN_00481d40(iVar4,local_f4._0_4_ / (float)DAT_005c8124,(float)local_16c / (float)DAT_005c8128
                   ,0xffffffff);
      local_164 = local_164 + local_d8;
      param_8 = param_8 + 2;
      local_16c = local_16c + 1;
    } while (local_16c <= DAT_005c8128);
  }
  FUN_00481b90();
  iVar4 = DAT_005c8128 * param_1 * 2;
  FUN_00481b30();
  local_16c = 0;
  if (0 < DAT_005c8128) {
    local_168 = iVar4 + 1;
    iVar1 = iVar4;
    do {
      FUN_00481ee0(param_9,iVar4);
      FUN_00481ee0(param_9 + 1,local_168);
      FUN_00481ee0(param_9 + 2,iVar1 + 2);
      FUN_00481ee0(param_9 + 3,iVar4 + 1);
      iVar5 = param_9 + 5;
      FUN_00481ee0(param_9 + 4,iVar1 + 3);
      param_9 = param_9 + 6;
      FUN_00481ee0(iVar5,local_168 + 1);
      iVar4 = iVar4 + 2;
      local_168 = local_168 + 2;
      local_16c = local_16c + 1;
      iVar1 = iVar1 + 2;
    } while (local_16c < DAT_005c8128);
  }
  FUN_00481b90();
  return;
}

