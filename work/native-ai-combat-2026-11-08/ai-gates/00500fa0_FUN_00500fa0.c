/* Original Meteor.exe static export @ 00500fa0; original sample not executed. */
/* XREF 004fd5c7 UNCONDITIONAL_CALL */
/* XREF 004fc5e6 UNCONDITIONAL_CALL */
/* XREF 0050125a UNCONDITIONAL_CALL */
/* XREF 00503cb3 UNCONDITIONAL_CALL */
/* XREF 00504069 UNCONDITIONAL_CALL */

void __fastcall FUN_00500fa0(int *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x1c0))();
    (**(code **)(*piVar1 + 0x4c))(0);
  }
  return;
}

