/* Original Meteor.exe static export @ 00407260; original sample not executed. */
/* XREF 00407250 UNCONDITIONAL_JUMP */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407260(undefined4 param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  undefined4 *puVar9;
  float *pfVar10;
  undefined4 *puVar11;
  float local_1dc;
  float local_1d8;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0 [5];
  float local_1ac;
  float local_1a8;
  float local_19c;
  float local_198;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  float local_150;
  float local_14c;
  float local_148;
  float local_140 [4];
  float local_130;
  float local_128;
  float local_120;
  float local_118;
  float local_100 [2];
  float local_f8;
  float local_e0;
  float local_d8;
  float local_c0;
  float local_bc;
  float local_b0;
  float local_ac;
  undefined1 local_80 [64];
  undefined1 local_40 [64];
  
  if (DAT_005d5a00 != 0) {
    iVar4 = FUN_00410a70(param_1);
    if (iVar4 != 0) {
      if (param_3 == (float *)0x0) {
        local_1dc = 0.0;
        local_1d8 = -1.0;
        fVar1 = _DAT_005a83e4;
      }
      else {
        fVar1 = _DAT_005a83f4 /
                SQRT(param_3[2] * param_3[2] + param_3[1] * param_3[1] + *param_3 * *param_3);
        local_1dc = fVar1 * param_3[1];
        local_1d8 = fVar1 * param_3[2];
        fVar1 = fVar1 * *param_3;
      }
      if (param_4 != (float *)0x0) {
        fVar2 = _DAT_005a83f4 /
                SQRT(param_4[2] * param_4[2] + param_4[1] * param_4[1] + *param_4 * *param_4);
        local_1cc = fVar2 * *param_4;
        local_1c8 = fVar2 * param_4[1];
        local_1c4 = fVar2 * param_4[2];
      }
      fVar2 = SQRT(fVar1 * fVar1 + local_1dc * local_1dc);
      fVar3 = fVar2;
      if (fVar2 <= _DAT_005a83e4) {
        fVar3 = -fVar2;
      }
      if (fVar3 <= _DAT_005a8408) {
        FUN_00430c40(local_1c0);
        local_198 = _DAT_005a83e4;
        local_1ac = _DAT_005a83e4;
        if (local_1d8 <= _DAT_005a83e4) {
          local_1a8 = -1.0;
          local_19c = 1.0;
        }
        else {
          local_1a8 = 1.0;
          local_19c = -1.0;
        }
        pfVar8 = local_1c0;
        pfVar10 = local_140;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *pfVar10 = *pfVar8;
          pfVar8 = pfVar8 + 1;
          pfVar10 = pfVar10 + 1;
        }
      }
      else {
        fVar3 = _DAT_005a83f4 / fVar2;
        fVar1 = fVar3 * fVar1;
        FUN_00430c40(&local_c0);
        local_c0 = -(fVar3 * local_1dc);
        local_bc = -fVar1;
        local_b0 = fVar1;
        local_ac = local_c0;
        FUN_00430c40(local_1c0);
        local_1a8 = local_1d8;
        local_19c = -local_1d8;
        local_1ac = fVar2;
        local_198 = fVar2;
        FUN_004312e0(local_140,&local_c0,local_1c0);
      }
      if (param_4 == (float *)0x0) {
        FUN_00430c40(local_100);
      }
      else {
        fVar1 = local_140[0] * local_1cc + local_130 * local_1c8 + local_120 * local_1c4;
        fVar2 = local_140[2] * local_1cc + local_128 * local_1c8 + local_118 * local_1c4;
        FUN_00430c40(local_100);
        local_e0 = -fVar1;
        local_100[0] = fVar2;
        local_f8 = fVar1;
        local_d8 = fVar2;
      }
      FUN_004312e0(local_80,local_140,local_100);
      FUN_004315e0(local_80,local_40);
      FUN_00407670(&local_180,*(undefined4 *)(iVar4 + 0xb8),*(undefined4 *)(iVar4 + 0xb4),4,2);
      FUN_004312e0(&local_180,&local_180,local_40);
      *(undefined4 *)(iVar4 + 8) = local_180;
      *(undefined4 *)(iVar4 + 0xc) = local_17c;
      *(undefined4 *)(iVar4 + 0x10) = local_178;
      *(undefined4 *)(iVar4 + 0x14) = local_170;
      *(undefined4 *)(iVar4 + 0x18) = local_16c;
      *(undefined4 *)(iVar4 + 0x1c) = local_168;
      *(undefined4 *)(iVar4 + 0x20) = local_160;
      *(undefined4 *)(iVar4 + 0x24) = local_15c;
      *(undefined4 *)(iVar4 + 0x28) = local_158;
      *(float *)(iVar4 + 0x2c) = local_150 + *param_2;
      *(float *)(iVar4 + 0x30) = local_14c + param_2[1];
      *(float *)(iVar4 + 0x34) = local_148 + param_2[2];
      iVar5 = *(int *)(iVar4 + 0x164);
      if (((iVar5 != 0) && (*(int *)(iVar4 + 0x160) == 0)) && (iVar7 = 0, 0 < *(int *)(iVar5 + 0xc))
         ) {
        do {
          iVar5 = *(int *)(*(int *)(iVar5 + 0x14) + iVar7 * 4);
          if (iVar5 != 0) {
            puVar9 = (undefined4 *)(iVar4 + 8);
            puVar11 = (undefined4 *)(iVar5 + 8);
            for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
          }
          iVar5 = *(int *)(iVar4 + 0x164);
          iVar7 = iVar7 + 1;
        } while (iVar7 < *(int *)(iVar5 + 0xc));
      }
    }
  }
  return;
}

