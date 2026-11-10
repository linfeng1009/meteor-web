/* Original Meteor.exe static export @ 00431b00; original sample not executed. */
/* XREF 00431a97 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00431b00(undefined4 param_1,float *param_2,float *param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int extraout_EDX;
  undefined4 extraout_EDX_00;
  float10 fVar4;
  float10 fVar5;
  unkbyte10 extraout_ST1;
  float local_c0;
  float local_bc;
  float local_b8;
  undefined4 local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  undefined4 local_a4;
  float local_a0;
  undefined4 local_9c;
  float local_98;
  undefined4 local_94;
  float local_90;
  float local_8c;
  float local_88;
  undefined4 local_84;
  float local_80;
  float local_7c;
  float local_78;
  undefined4 local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;
  float local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined1 local_40 [20];
  float local_2c;
  float local_28;
  float local_1c;
  float local_18;
  
  if ((*param_3 != _DAT_005a83e4) || (param_3[1] != _DAT_005a83e4)) {
    fsin((float10)param_4 * (float10)_DAT_005a8420);
    fVar4 = (float10)FUN_00430c40(local_40);
    local_b4 = 0;
    local_a4 = 0;
    local_9c = 0;
    local_94 = 0;
    fVar5 = (float10)fcos(extraout_ST1);
    local_18 = (float)fVar5;
    local_2c = (float)fVar5;
    local_28 = (float)fVar4;
    local_1c = (float)-fVar4;
    fVar2 = param_3[1] * param_3[1];
    fVar3 = *param_3 * *param_3;
    fVar1 = SQRT(fVar3 + fVar2);
    local_a0 = _DAT_005a83f4 / SQRT(param_3[2] * param_3[2] + fVar3 + fVar2);
    local_98 = local_a0 * fVar1;
    local_a0 = local_a0 * param_3[2];
    fVar1 = _DAT_005a83f4 / fVar1;
    local_ac = fVar1 * *param_3;
    fVar1 = fVar1 * param_3[1];
    local_c0 = local_ac * local_98;
    local_bc = -fVar1;
    local_b8 = -(local_ac * local_a0);
    local_b0 = fVar1 * local_98;
    local_a8 = -(fVar1 * local_a0);
    local_50 = *param_2;
    local_4c = param_2[1];
    local_90 = (-(local_ac * *param_2 * local_98) - fVar1 * param_2[1] * local_98) -
               local_a0 * param_2[2];
    local_84 = 0x3f800000;
    local_74 = 0;
    local_68 = 0;
    local_64 = 0;
    local_54 = 0;
    local_44 = 0x3f800000;
    local_8c = fVar1 * *param_2 - local_ac * param_2[1];
    local_48 = param_2[2];
    local_88 = (fVar1 * param_2[1] + local_ac * *param_2) * local_a0 - local_98 * param_2[2];
    local_80 = local_c0;
    local_7c = local_b0;
    local_78 = local_a0;
    local_70 = local_bc;
    local_6c = local_ac;
    local_60 = local_b8;
    local_5c = local_a8;
    local_58 = local_98;
    FUN_004312e0(param_1,&local_c0,local_40);
    FUN_004312e0(extraout_EDX_00,extraout_EDX_00,&local_80);
    return;
  }
  FUN_00430c40(&local_c0);
  local_90 = -*param_2;
  local_8c = -param_2[1];
  local_88 = -param_2[2];
  if (param_3[2] <= _DAT_005a83e4) {
    if (_DAT_005a83e4 <= param_3[2]) goto LAB_00431bb9;
    param_4 = -param_4;
  }
  FUN_00431e20(local_40,2,param_4);
LAB_00431bb9:
  FUN_004312e0(param_1,&local_c0,local_40);
  *(float *)(extraout_EDX + 0x30) = *param_2 + *(float *)(extraout_EDX + 0x30);
  *(float *)(extraout_EDX + 0x34) = param_2[1] + *(float *)(extraout_EDX + 0x34);
  *(float *)(extraout_EDX + 0x38) = param_2[2] + *(float *)(extraout_EDX + 0x38);
  return;
}

