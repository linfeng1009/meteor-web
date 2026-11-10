/* Original Meteor.exe static export @ 0040ff40; original sample not executed. */
/* XREF 00408d4c UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040ff40(int param_1,int *param_2,int param_3,int param_4,float param_5)

{
  float fVar1;
  
  fVar1 = *(float *)(param_1 + 8 + *param_2 * param_4 * 4) - *(float *)(param_3 + 8);
  if (fVar1 <= _DAT_005a83e4) {
    fVar1 = -fVar1;
  }
  if (fVar1 < param_5) {
    return 1;
  }
  fVar1 = *(float *)(param_1 + 8 + param_2[1] * param_4 * 4) - *(float *)(param_3 + 8);
  if (fVar1 <= _DAT_005a83e4) {
    fVar1 = -fVar1;
  }
  if (fVar1 < param_5) {
    return 1;
  }
  fVar1 = *(float *)(param_1 + 8 + param_2[2] * param_4 * 4) - *(float *)(param_3 + 8);
  if (fVar1 <= _DAT_005a83e4) {
    fVar1 = -fVar1;
  }
  if (fVar1 < param_5) {
    return 1;
  }
  return 0;
}

