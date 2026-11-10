/* Original Meteor.exe static export @ 00501030; original sample not executed. */
/* XREF 004fcc19 UNCONDITIONAL_CALL */
/* XREF 00504d59 UNCONDITIONAL_CALL */
/* XREF 0050402a UNCONDITIONAL_CALL */
/* XREF 0050410f UNCONDITIONAL_CALL */
/* XREF 00504237 UNCONDITIONAL_CALL */
/* XREF 004fca9e UNCONDITIONAL_CALL */

undefined4 __fastcall FUN_00501030(int *param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar2 == (int *)0x0) {
    return 0;
  }
  iVar3 = (**(code **)(*piVar2 + 0x130))();
  if (iVar3 != 1) {
    cVar1 = FUN_00501130();
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}

