/* Original Meteor.exe static export @ 00432000; original sample not executed. */
/* XREF 00422c16 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00432000(float param_1,float param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  if (param_1 == _DAT_005a83e4) {
    return (float10)_DAT_005a83e4;
  }
  fVar1 = (float10)log2((float10)param_1);
  fVar2 = (float10)1.4426950408889634 * (float10)0.6931471805599453 * fVar1 * (float10)param_2;
  fVar1 = ROUND(fVar2);
  fVar2 = (float10)f2xm1(fVar2 - fVar1);
  fVar1 = (float10)fscale((float10)1 + fVar2,fVar1);
  return fVar1;
}

