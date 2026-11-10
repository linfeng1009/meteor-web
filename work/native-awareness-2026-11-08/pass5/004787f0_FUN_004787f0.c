/* Original Meteor.exe static export @ 004787f0; original sample not executed. */
/* XREF 005732be UNCONDITIONAL_CALL */
/* XREF 00572fcd UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004787f0(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  float local_50 [4];
  float local_40 [16];
  
  local_50[0] = 1.4013e-45;
  local_50[1] = 2.8026e-45;
  local_50[2] = 0.0;
  FUN_00477f20(local_40);
  fVar1 = local_40[10] + local_40[5] + local_40[0];
  if ((float)_DAT_005a84b8 < fVar1) {
    fVar1 = SQRT(fVar1 + _DAT_005a83f4);
    param_1[3] = _DAT_005a83e8 * fVar1;
    fVar1 = _DAT_005a83e8 / fVar1;
    *param_1 = (local_40[6] - local_40[9]) * fVar1;
    param_1[1] = (local_40[8] - local_40[2]) * fVar1;
    param_1[2] = (local_40[1] - local_40[4]) * fVar1;
    return;
  }
  uVar4 = (uint)(local_40[0] < local_40[5]);
  if (local_40[uVar4 * 5] < local_40[10]) {
    uVar4 = 2;
  }
  fVar1 = local_50[uVar4];
  fVar2 = local_50[(int)fVar1];
  fVar3 = SQRT((local_40[uVar4 * 5] - (local_40[(int)fVar2 * 5] + local_40[(int)fVar1 * 5])) +
               (float)_DAT_005a8418);
  local_50[uVar4] = _DAT_005a83e8 * fVar3;
  if (fVar3 != _DAT_005a83e4) {
    fVar3 = _DAT_005a83e8 / fVar3;
  }
  local_50[3] = (local_40[(int)fVar2 + (int)fVar1 * 4] - local_40[(int)fVar1 + (int)fVar2 * 4]) *
                fVar3;
  local_50[(int)fVar1] =
       (local_40[uVar4 + (int)fVar1 * 4] + local_40[(int)fVar1 + uVar4 * 4]) * fVar3;
  local_50[(int)fVar2] =
       (local_40[uVar4 + (int)fVar2 * 4] + local_40[(int)fVar2 + uVar4 * 4]) * fVar3;
  param_1[1] = local_50[1];
  *param_1 = local_50[0];
  param_1[2] = local_50[2];
  param_1[3] = local_50[3];
  return;
}

