/* Original Meteor.exe static export @ 0055a280; original sample not executed. */
/* XREF 0048aa82 UNCONDITIONAL_CALL */
/* XREF 0055a53b UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0055a280(int param_1,float param_2)

{
  float fVar1;
  
  fVar1 = _DAT_005a83f4;
  if ((param_2 <= _DAT_005a83f4) && (fVar1 = param_2, param_2 < _DAT_005a83e4)) {
    fVar1 = _DAT_005a83e4;
  }
  *(float *)(param_1 + 0x50) = fVar1;
  FUN_0047dd50(_DAT_005a83f4 - fVar1,fVar1,0,0x3f800000);
  return;
}

