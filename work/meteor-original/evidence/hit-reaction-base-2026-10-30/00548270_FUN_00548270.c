/* Original Meteor.exe static export @ 00548270; original sample not executed. */
/* XREF 004f3639 UNCONDITIONAL_CALL */
/* XREF 005489eb UNCONDITIONAL_CALL */
/* XREF 00549342 UNCONDITIONAL_CALL */
/* XREF 004cd13a UNCONDITIONAL_CALL */
/* XREF 004ce7ab UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00548270(float *param_1,float *param_2,double *param_3,int param_4)

{
  float fVar1;
  float10 fVar2;
  
  if ((param_1 == (float *)0x0) || (param_2 == (float *)0x0)) {
    return 0;
  }
  fVar1 = SQRT((param_1[1] * param_1[1] + *param_1 * *param_1) *
               (param_2[1] * param_2[1] + *param_2 * *param_2));
  if ((((float)_DAT_005a9b28 <= fVar1) || (fVar1 <= (float)_DAT_005adf90)) &&
     (fVar1 = (*param_1 * *param_2 + param_2[1] * param_1[1]) / fVar1, fVar1 < (float)_DAT_005a8418)
     ) {
    if (fVar1 < (float)_DAT_005aa908 != (fVar1 == (float)_DAT_005aa908)) {
      *(undefined4 *)param_3 = 0x4d12d84a;
      *(undefined4 *)((int)param_3 + 4) = 0x400921fb;
      return 1;
    }
    fVar2 = (float10)FUN_00509d10();
    *param_3 = (double)fVar2;
    if ((param_4 != 0) && (param_2[1] * *param_1 - param_1[1] * *param_2 < _DAT_005a83e4)) {
      *param_3 = (double)-fVar2;
      return 1;
    }
    return 1;
  }
  *(undefined4 *)param_3 = 0;
  *(undefined4 *)((int)param_3 + 4) = 0;
  return 1;
}

