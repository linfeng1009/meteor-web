/* Original Meteor.exe static export @ 004100b0; original sample not executed. */
/* XREF 0040842c UNCONDITIONAL_CALL */
/* XREF 00408495 UNCONDITIONAL_CALL */
/* XREF 004084e5 UNCONDITIONAL_CALL */
/* XREF 00408823 UNCONDITIONAL_CALL */
/* XREF 0040888c UNCONDITIONAL_CALL */
/* XREF 004088dc UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_004100b0(int param_1,int *param_2,undefined4 param_3,float param_4,float *param_5,int param_6)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  
  iVar1 = param_1 + param_2[1] * param_6 * 4;
  iVar2 = param_1 + *param_2 * param_6 * 4;
  fVar4 = (float10)FUN_00431ea0(param_3,iVar2,iVar1);
  if (fVar4 < (float10)_DAT_005a83e4) {
    return 0;
  }
  param_1 = param_1 + param_2[2] * param_6 * 4;
  fVar5 = (float10)FUN_00431ea0(param_3,iVar1,param_1);
  if (fVar5 < (float10)_DAT_005a83e4) {
    return 0;
  }
  fVar6 = (float10)FUN_00431ea0(param_3,param_1,iVar2);
  if (fVar6 < (float10)_DAT_005a83e4) {
    return 0;
  }
  if (param_5 != (float *)0x0) {
    fVar3 = param_4;
    if (param_4 <= _DAT_005a83e4) {
      fVar3 = -param_4;
    }
    if (fVar3 < _DAT_005a8408) {
      *param_5 = 0.0;
      return 1;
    }
    *param_5 = ((float)fVar4 * *(float *)(param_1 + 8) +
               (float)fVar5 * *(float *)(iVar2 + 8) + (float)fVar6 * *(float *)(iVar1 + 8)) *
               param_4;
  }
  return 1;
}

