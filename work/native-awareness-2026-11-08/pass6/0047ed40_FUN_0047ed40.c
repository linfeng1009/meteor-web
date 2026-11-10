/* Original Meteor.exe static export @ 0047ed40; original sample not executed. */
/* XREF 0057f92f UNCONDITIONAL_CALL */
/* XREF 0058e37b UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0047ed40(float *param_1)

{
  float fVar1;
  
  fVar1 = param_1[3] * param_1[3] +
          param_1[2] * param_1[2] + param_1[1] * param_1[1] + *param_1 * *param_1;
  if ((fVar1 != _DAT_005a83f4) && (fVar1 != _DAT_005a83e4)) {
    fVar1 = _DAT_005a83f4 / SQRT(fVar1);
    *param_1 = fVar1 * *param_1;
    param_1[1] = fVar1 * param_1[1];
    param_1[2] = fVar1 * param_1[2];
    param_1[3] = fVar1 * param_1[3];
  }
  return;
}

