/* Original Meteor.exe static export @ 00567360; original sample not executed. */
/* XREF 005623b4 UNCONDITIONAL_CALL */
/* XREF 0057ee16 UNCONDITIONAL_CALL */
/* XREF 0057ef08 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00567360(undefined4 param_1,float *param_2,byte param_3)

{
  float fVar1;
  float10 fVar2;
  
  if ((param_3 & 8) != 0) {
    fVar2 = (float10)FUN_0047ecf0();
    return fVar2;
  }
  if ((param_3 & 0x10) != 0) {
    fVar2 = (float10)FUN_0047ecf0();
    return fVar2;
  }
  fVar1 = _DAT_005a83e4;
  if ((param_3 & 1) != 0) {
    fVar1 = *param_2;
  }
  fVar2 = (float10)fVar1;
  if ((param_3 & 2) != 0) {
    fVar2 = fVar2 + (float10)param_2[1];
  }
  if ((param_3 & 4) != 0) {
    fVar2 = fVar2 + (float10)param_2[2];
  }
  return fVar2;
}

