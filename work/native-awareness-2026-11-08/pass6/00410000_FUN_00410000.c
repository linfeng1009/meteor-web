/* Original Meteor.exe static export @ 00410000; original sample not executed. */
/* XREF 00408c70 UNCONDITIONAL_CALL */
/* XREF 00408cc8 UNCONDITIONAL_CALL */
/* XREF 00408d21 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00410000(int param_1,int *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  
  iVar1 = param_1 + param_2[1] * param_4 * 4;
  iVar2 = param_1 + *param_2 * param_4 * 4;
  fVar3 = (float10)FUN_00431ea0(param_3,iVar2,iVar1);
  if (fVar3 < (float10)_DAT_005a83e4) {
    return 0;
  }
  param_1 = param_1 + param_2[2] * param_4 * 4;
  fVar3 = (float10)FUN_00431ea0(param_3,iVar1,param_1);
  if (fVar3 < (float10)_DAT_005a83e4) {
    return 0;
  }
  fVar3 = (float10)FUN_00431ea0(param_3,param_1,iVar2);
  if (fVar3 < (float10)_DAT_005a83e4) {
    return 0;
  }
  return 1;
}

