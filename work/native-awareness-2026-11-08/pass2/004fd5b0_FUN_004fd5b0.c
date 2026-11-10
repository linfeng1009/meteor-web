/* Original Meteor.exe static export @ 004fd5b0; original sample not executed. */
/* XREF 004f900d UNCONDITIONAL_CALL */
/* XREF 004f904e UNCONDITIONAL_CALL */
/* XREF 004f908a UNCONDITIONAL_CALL */
/* XREF 004f9100 UNCONDITIONAL_CALL */
/* XREF 004f916a UNCONDITIONAL_CALL */
/* XREF 004f9202 UNCONDITIONAL_CALL */
/* XREF 004fd818 UNCONDITIONAL_CALL */
/* XREF 004fd9ba UNCONDITIONAL_CALL */

void __thiscall FUN_004fd5b0(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0xc) == 0) {
    *(undefined4 *)(param_1 + 0x84) = 0xffffffff;
    *(undefined4 *)(param_1 + 100) = param_2;
    return;
  }
  FUN_004fd580();
  FUN_004fdd10();
  FUN_00500fa0();
  if (*(undefined **)(param_1 + 100) != &DAT_00504be0) {
    FUN_00500c60(0);
    FUN_005012a0(0);
    *(undefined4 *)(param_1 + 0x84) = 0xffffffff;
    *(undefined4 *)(param_1 + 100) = param_2;
    return;
  }
  *(undefined4 *)(param_1 + 0x84) = 0xffffffff;
  *(undefined4 *)(param_1 + 100) = param_2;
  return;
}

