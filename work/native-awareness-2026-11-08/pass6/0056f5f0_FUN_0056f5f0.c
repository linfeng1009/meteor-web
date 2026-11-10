/* Original Meteor.exe static export @ 0056f5f0; original sample not executed. */
/* XREF 005645d9 UNCONDITIONAL_CALL */
/* XREF 0056480a UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_0056f5f0(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
            float *param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_24 = *param_4 - *param_3;
  local_20 = param_4[1] - param_3[1];
  local_1c = param_4[2] - param_3[2];
  local_18 = *param_5 - *param_3;
  local_14 = param_5[1] - param_3[1];
  local_10 = param_5[2] - param_3[2];
  local_54 = *param_2 - *param_1;
  local_50 = param_2[1] - param_1[1];
  local_4c = param_2[2] - param_1[2];
  local_30 = local_54;
  local_2c = local_50;
  local_28 = local_4c;
  FUN_00529c40(&local_54,&local_18,&local_3c);
  fVar1 = local_3c * local_24 + local_38 * local_20 + local_34 * local_1c;
  local_48 = *param_1 - *param_3;
  local_44 = param_1[1] - param_3[1];
  local_40 = param_1[2] - param_3[2];
  fVar3 = _DAT_005a83f4 / fVar1;
  local_c = local_48;
  local_8 = local_44;
  local_4 = local_40;
  FUN_00529c40(&local_48,&local_24,&local_30);
  if (fVar1 <= _DAT_005a8408) {
    if (_DAT_005ae240 <= fVar1) {
      return 0;
    }
    fVar2 = local_48 * local_3c + local_44 * local_38 + local_40 * local_34;
    if (_DAT_005a83e4 < fVar2) {
      return 0;
    }
    if (fVar2 < fVar1) {
      return 0;
    }
    fVar4 = local_30 * local_54 + local_2c * local_50 + local_28 * local_4c;
    if (_DAT_005a83e4 < fVar4) {
      return 0;
    }
    if (fVar2 + fVar4 < fVar1) {
      return 0;
    }
  }
  else {
    fVar2 = local_48 * local_3c + local_44 * local_38 + local_40 * local_34;
    if (fVar2 < _DAT_005a83e4) {
      return 0;
    }
    if (fVar1 < fVar2) {
      return 0;
    }
    fVar4 = local_30 * local_54 + local_2c * local_50 + local_28 * local_4c;
    if (fVar4 < _DAT_005a83e4) {
      return 0;
    }
    if (fVar1 < fVar2 + fVar4) {
      return 0;
    }
  }
  fVar3 = (local_18 * local_30 + local_14 * local_2c + local_10 * local_28) * fVar3;
  if ((_DAT_005a83e4 <= fVar3) && (fVar3 < _DAT_005a83f4)) {
    fVar1 = param_1[1];
    fVar2 = param_1[2];
    *param_6 = local_54 * fVar3 + *param_1;
    param_6[1] = local_50 * fVar3 + fVar1;
    param_6[2] = local_4c * fVar3 + fVar2;
    return 1;
  }
  return 0;
}

