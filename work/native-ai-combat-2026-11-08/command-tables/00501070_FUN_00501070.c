/* Original Meteor.exe static export @ 00501070; original sample not executed. */
/* XREF 004fd075 UNCONDITIONAL_CALL */
/* XREF 00500ce3 UNCONDITIONAL_CALL */
/* XREF 00503fa3 UNCONDITIONAL_CALL */

bool __fastcall FUN_00501070(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 == (int *)0x0) {
    return false;
  }
  iVar2 = (**(code **)(*piVar1 + 0x130))();
  return iVar2 == 0;
}

