/* Original Meteor.exe static export @ 0055a9f0; original sample not executed. */
/* XREF 0049129f UNCONDITIONAL_CALL */
/* XREF 0048aa31 UNCONDITIONAL_CALL */
/* XREF 0055a893 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0055a9f0(int param_1,int param_2,int param_3)

{
  float *pfVar1;
  
  if (param_3 < param_2) {
    param_2 = param_3;
  }
  if (param_2 < 0) {
    param_2 = 0;
  }
  *(int *)(param_1 + 0x10) = param_3;
  *(int *)(param_1 + 8) = param_2;
  *(float *)(param_1 + 0x1664) = (float)param_2 / (float)param_3;
  pfVar1 = (float *)FUN_00481b30();
  *pfVar1 = *(float *)(param_1 + 0x1664) * *(float *)(param_1 + 0x28) * _DAT_005a8ff0;
  pfVar1[1] = *(float *)(param_1 + 0x2c) * _DAT_005a8ff0;
  pfVar1[6] = *(float *)(param_1 + 0x1664) * *(float *)(param_1 + 0x28) * _DAT_005a83e8;
  pfVar1[7] = *(float *)(param_1 + 0x2c) * _DAT_005a8ff0;
  pfVar1[0xc] = *(float *)(param_1 + 0x1664) * *(float *)(param_1 + 0x28) * _DAT_005a83e8;
  pfVar1[0xd] = *(float *)(param_1 + 0x2c) * _DAT_005a83e8;
  pfVar1[0x12] = *(float *)(param_1 + 0x1664) * *(float *)(param_1 + 0x28) * _DAT_005a8ff0;
  pfVar1[0x13] = *(float *)(param_1 + 0x2c) * _DAT_005a83e8;
  FUN_00481b90();
  return;
}

