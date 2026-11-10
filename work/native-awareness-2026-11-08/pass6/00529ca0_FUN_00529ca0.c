/* Original Meteor.exe static export @ 00529ca0; original sample not executed. */
/* XREF 00529f28 UNCONDITIONAL_CALL */
/* XREF 00529f49 UNCONDITIONAL_CALL */
/* XREF 00529f7a UNCONDITIONAL_CALL */
/* XREF 0052a0f2 UNCONDITIONAL_CALL */
/* XREF 0052a0fc UNCONDITIONAL_CALL */
/* XREF 0052a25e UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00529ca0(undefined4 param_1)

{
  float *extraout_EDX;
  float10 fVar1;
  
  fVar1 = (float10)FUN_00529c80(param_1,param_1);
  if (SQRT(fVar1) != (float10)_DAT_005a83e4) {
    fVar1 = (float10)_DAT_005a83f4 / SQRT(fVar1);
    *extraout_EDX = (float)(fVar1 * (float10)*extraout_EDX);
    extraout_EDX[1] = (float)(fVar1 * (float10)extraout_EDX[1]);
    extraout_EDX[2] = (float)(fVar1 * (float10)extraout_EDX[2]);
    return;
  }
  return;
}

