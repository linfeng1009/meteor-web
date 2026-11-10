/* Original Meteor.exe static export @ 00501730; original sample not executed. */
/* XREF 004fcf28 UNCONDITIONAL_CALL */
/* XREF 004fcf34 UNCONDITIONAL_CALL */
/* XREF 004fd3cd UNCONDITIONAL_CALL */
/* XREF 004fd49f UNCONDITIONAL_CALL */
/* XREF 004fd4a5 UNCONDITIONAL_CALL */
/* XREF 005016ef UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00501730(float *param_1)

{
  bool bVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = __ftol();
  fVar2 = (*param_1 - (float)iVar3) + (float)(iVar3 % 0x168);
  bVar1 = fVar2 < _DAT_005a83e4;
  *param_1 = fVar2;
  if (bVar1) {
    *param_1 = fVar2 + _DAT_005a84a8;
    return;
  }
  return;
}

