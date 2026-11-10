/* Original Meteor.exe static export @ 00501130; original sample not executed. */
/* XREF 004fe0c6 UNCONDITIONAL_CALL */
/* XREF 00501051 UNCONDITIONAL_CALL */
/* XREF 005010a6 UNCONDITIONAL_CALL */

bool __fastcall FUN_00501130(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 == (int *)0x0) {
    return false;
  }
  iVar2 = (**(code **)(*piVar1 + 0x130))();
  return iVar2 == 0xb;
}

