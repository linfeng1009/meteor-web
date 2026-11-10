/* Original Meteor.exe static export @ 004acb00; original sample not executed. */
/* XREF 0048b405 UNCONDITIONAL_CALL */
/* XREF 0048b4d1 UNCONDITIONAL_CALL */
/* XREF 004b266a UNCONDITIONAL_CALL */
/* XREF 004ad607 UNCONDITIONAL_CALL */
/* XREF 004ad6ce UNCONDITIONAL_CALL */
/* XREF 004ad70c UNCONDITIONAL_CALL */
/* XREF 004ad743 UNCONDITIONAL_CALL */
/* XREF 004ad78f UNCONDITIONAL_CALL */
/* XREF 004ad92a UNCONDITIONAL_CALL */
/* XREF 004ad975 UNCONDITIONAL_CALL */
/* XREF 004ad9a1 UNCONDITIONAL_CALL */
/* XREF 004ad9d2 UNCONDITIONAL_CALL */
/* XREF 004ad9f5 UNCONDITIONAL_CALL */
/* XREF 004ada26 UNCONDITIONAL_CALL */
/* XREF 004ada57 UNCONDITIONAL_CALL */
/* XREF 004add57 UNCONDITIONAL_CALL */
/* XREF 004addeb UNCONDITIONAL_CALL */
/* XREF 004adf1c UNCONDITIONAL_CALL */
/* XREF 004ae00f UNCONDITIONAL_CALL */
/* XREF 004ae088 UNCONDITIONAL_CALL */
/* XREF 004ae567 UNCONDITIONAL_CALL */

void __thiscall
FUN_004acb00(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  int *piVar2;
  undefined4 unaff_retaddr;
  
  iVar1 = (**(code **)(*param_1 + 0x120))(param_2);
  if (iVar1 == 0) {
    FUN_0054e7c0(unaff_retaddr,param_2,param_3,param_4,param_5);
  }
  else {
    FUN_0054e6f0(param_2,param_3,param_4,param_5);
  }
  piVar2 = (int *)FUN_00487830();
  iVar1 = (**(code **)(*piVar2 + 0x368))();
  if (iVar1 != 0) {
    iVar1 = FUN_00487830();
    iVar1 = (**(code **)(*(int *)(iVar1 + 0x2488) + 0x1d0))(unaff_retaddr);
    if ((iVar1 != 0) && ((short)param_2 == 0x38)) {
      iVar1 = FUN_00487830();
      (**(code **)(**(int **)(iVar1 + 0x2410) + 0x24))(param_2,param_3,param_4);
    }
  }
  return;
}

