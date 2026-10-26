/* Original Meteor.exe static export @ 0058a6d0; original sample not executed. */
/* XREF 00584dd7 UNCONDITIONAL_CALL */
/* XREF 005853b7 UNCONDITIONAL_CALL */
/* XREF 0058570c UNCONDITIONAL_CALL */
/* XREF 0058599a UNCONDITIONAL_CALL */
/* XREF 00587aab UNCONDITIONAL_CALL */
/* XREF 00588127 UNCONDITIONAL_CALL */
/* XREF 0058876b UNCONDITIONAL_CALL */
/* XREF 00588e67 UNCONDITIONAL_CALL */
/* XREF 00589387 UNCONDITIONAL_CALL */
/* XREF 005899c7 UNCONDITIONAL_CALL */
/* XREF 0058a246 UNCONDITIONAL_CALL */

undefined1 * FUN_0058a6d0(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_005d2f88;
  do {
    if (*piVar1 == param_1) {
      return &DAT_005d2f8c + iVar2 * 0x14;
    }
    piVar1 = piVar1 + 5;
    iVar2 = iVar2 + 1;
  } while ((int)piVar1 < 0x5d3078);
  return (undefined1 *)0x0;
}

