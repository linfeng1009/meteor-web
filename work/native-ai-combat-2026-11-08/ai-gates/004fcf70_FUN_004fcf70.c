/* Original Meteor.exe static export @ 004fcf70; original sample not executed. */
/* XREF 004fde9a UNCONDITIONAL_CALL */
/* XREF 00504b86 UNCONDITIONAL_CALL */
/* XREF 005042e2 UNCONDITIONAL_CALL */
/* XREF 005043b7 UNCONDITIONAL_CALL */
/* XREF 004fca79 UNCONDITIONAL_CALL */

undefined4 __fastcall FUN_004fcf70(int param_1)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 0x58) < 0) ||
     (uVar1 = 1, *(int *)(&DAT_00666a34 + *(int *)(param_1 + 0x58) * 0x38) != 1)) {
    uVar1 = 0;
  }
  return uVar1;
}

