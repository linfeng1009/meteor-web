/* Original Meteor.exe static export @ 00469840; original sample not executed. */
/* XREF 004539fc UNCONDITIONAL_CALL */
/* XREF 00453a2d UNCONDITIONAL_CALL */
/* XREF 00453a5e UNCONDITIONAL_CALL */
/* XREF 00453a8f UNCONDITIONAL_CALL */
/* XREF 00457fcb UNCONDITIONAL_CALL */
/* XREF 00453da8 UNCONDITIONAL_CALL */
/* XREF 00457db2 UNCONDITIONAL_CALL */
/* XREF 00457de3 UNCONDITIONAL_CALL */
/* XREF 00457e14 UNCONDITIONAL_CALL */
/* XREF 00457e45 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00469840(int param_1,float param_2)

{
  if ((param_2 < _DAT_005a83e4) && (_DAT_005a83f4 < param_2)) {
    return 0;
  }
  if (*(int *)(param_1 + 0x38) == 2) {
    FUN_00469f50(*(undefined4 *)(param_1 + 0x10),
                 (*(float *)(param_1 + 0x1c) - *(float *)(param_1 + 0x18)) * param_2 +
                 *(float *)(param_1 + 0x14));
    return 1;
  }
  FUN_00469f50((*(float *)(param_1 + 0x18) - *(float *)(param_1 + 0x1c)) * param_2 +
               *(float *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14));
  return 1;
}

