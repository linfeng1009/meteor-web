/* Original Meteor.exe static export @ 00515f4b; original sample not executed. */
/* XREF 005cda54 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00515f4b(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                 float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar5 = _DAT_005a83e8;
  fVar1 = param_6 * param_6;
  fVar2 = param_6 * fVar1;
  fVar4 = (fVar1 * _DAT_005a8b80 - fVar2) - param_6;
  fVar3 = (fVar2 * _DAT_005a8e84 - fVar1 * _DAT_005a8f74) + _DAT_005a8b80;
  param_6 = (fVar1 * _DAT_005a8cf0 - fVar2 * _DAT_005a8e84) + param_6;
  fVar2 = fVar2 - fVar1;
  *param_1 = (fVar2 * *param_5 + param_6 * *param_4 + fVar3 * *param_3 + fVar4 * *param_2) *
             _DAT_005a83e8;
  param_1[1] = (fVar4 * param_2[1] + fVar3 * param_3[1] + param_6 * param_4[1] + fVar2 * param_5[1])
               * fVar5;
  param_1[2] = (fVar4 * param_2[2] + fVar3 * param_3[2] + param_6 * param_4[2] + fVar2 * param_5[2])
               * fVar5;
  param_1[3] = (fVar4 * param_2[3] + fVar3 * param_3[3] + param_6 * param_4[3] + fVar2 * param_5[3])
               * fVar5;
  return;
}

