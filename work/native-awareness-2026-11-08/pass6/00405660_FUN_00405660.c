/* Original Meteor.exe static export @ 00405660; original sample not executed. */
/* XREF 00466916 UNCONDITIONAL_CALL */
/* XREF 004e98c3 UNCONDITIONAL_CALL */
/* XREF 004eaf3e UNCONDITIONAL_CALL */
/* XREF 004eb6dd UNCONDITIONAL_CALL */
/* XREF 004ebb5c UNCONDITIONAL_CALL */
/* XREF 004662de UNCONDITIONAL_CALL */
/* XREF 0046f9b0 UNCONDITIONAL_CALL */
/* XREF 0046fa33 UNCONDITIONAL_CALL */
/* XREF 004052b9 UNCONDITIONAL_CALL */
/* XREF 00405300 UNCONDITIONAL_CALL */
/* XREF 004658c0 UNCONDITIONAL_CALL */
/* XREF 004a8276 UNCONDITIONAL_CALL */
/* XREF 004a6077 UNCONDITIONAL_CALL */
/* XREF 004a60c6 UNCONDITIONAL_CALL */
/* XREF 004a610f UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00405660(int param_1,float param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (DAT_005d5a00 != 0) {
    iVar1 = FUN_00410a70(param_1);
    if (iVar1 != 0) {
      if (_DAT_005a83e4 <= param_2) {
        if (_DAT_005a83f4 < param_2) {
          param_2 = 1.0;
        }
      }
      else {
        param_2 = 0.0;
      }
      FUN_00405560(iVar1,param_2,param_1 != 0);
      iVar2 = *(int *)(iVar1 + 0x164);
      if (((iVar2 != 0) && (*(int *)(iVar1 + 0x160) == 0)) && (iVar3 = 0, 0 < *(int *)(iVar2 + 0xc))
         ) {
        do {
          iVar2 = *(int *)(*(int *)(iVar2 + 0x14) + iVar3 * 4);
          if (iVar2 != 0) {
            FUN_00405560(iVar2,param_2,param_1 != 0);
          }
          iVar2 = *(int *)(iVar1 + 0x164);
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(iVar2 + 0xc));
      }
    }
  }
  return;
}

