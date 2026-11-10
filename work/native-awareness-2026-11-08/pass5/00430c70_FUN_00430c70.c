/* Original Meteor.exe static export @ 00430c70; original sample not executed. */
/* XREF 00404b94 UNCONDITIONAL_CALL */
/* XREF 00404c93 UNCONDITIONAL_CALL */
/* XREF 00404e19 UNCONDITIONAL_CALL */
/* XREF 00405bd9 UNCONDITIONAL_CALL */
/* XREF 00404d59 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00430c70(float *param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,float param_7,float param_8,float param_9,float param_10)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar1 = (param_4 / (param_3 * _DAT_005a8434)) * param_5;
  fVar2 = -fVar1;
  fVar4 = -(fVar1 / param_2);
  fVar3 = (param_7 + _DAT_005a83f4) * (fVar1 - fVar2) * _DAT_005a83e8 + fVar2;
  fVar2 = (param_7 + param_9 + _DAT_005a83f4) * (fVar1 - fVar2) * _DAT_005a83e8 + fVar2;
  fVar1 = fVar1 / param_2 - fVar4;
  fVar6 = (param_8 + _DAT_005a83f4) * fVar1 * _DAT_005a83e8 + fVar4;
  fVar4 = (param_8 + param_10 + _DAT_005a83f4) * fVar1 * _DAT_005a83e8 + fVar4;
  fVar1 = _DAT_005a83f4 / (fVar2 - fVar3);
  *param_1 = fVar1 * (param_5 + param_5);
  fVar5 = _DAT_005a83f4 / (fVar4 - fVar6);
  param_1[5] = (param_5 + param_5) * fVar5;
  param_1[8] = (fVar2 + fVar3) * fVar1;
  param_1[0xb] = -1.0;
  param_1[0xf] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xc] = 0.0;
  param_1[7] = 0.0;
  param_1[9] = (fVar4 + fVar6) * fVar5;
  param_1[6] = 0.0;
  param_1[4] = 0.0;
  fVar1 = _DAT_005a83f4 / (param_5 - param_6);
  param_1[3] = 0.0;
  param_1[2] = 0.0;
  param_1[1] = 0.0;
  param_1[10] = param_6 * fVar1;
  param_1[0xe] = fVar1 * param_5 * param_6;
  return;
}

