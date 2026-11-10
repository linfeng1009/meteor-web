/* Original Meteor.exe static export @ 00408ad0; original sample not executed. */
/* XREF 0040834e UNCONDITIONAL_CALL */
/* XREF 00408650 UNCONDITIONAL_CALL */
/* XREF 00408a6d UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00408ad0(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float10 fVar1;
  undefined1 local_3c [12];
  undefined1 local_30 [48];
  
  fVar1 = (float10)FUN_00529c80(param_3,param_4);
  fVar1 = fVar1 - (float10)_DAT_005a83f4;
  if (fVar1 <= (float10)_DAT_005a83e4) {
    fVar1 = -fVar1;
  }
  if ((float10)_DAT_005a8408 < fVar1) {
    FUN_00430e80(local_3c,param_3,param_4);
    fVar1 = (float10)FUN_00509d10();
    FUN_00431a80(local_30,param_2,local_3c,(float)(fVar1 * (float10)_DAT_005a8424));
    thunk_FUN_0040c620(*param_1 | 0x2000000,local_30,2);
  }
  return;
}

