/* Original Meteor.exe static export @ 004fcbd0; original sample not executed. */
/* XREF 004fdd76 UNCONDITIONAL_CALL */
/* XREF 00503f31 UNCONDITIONAL_CALL */

undefined4 __fastcall FUN_004fcbd0(int param_1)

{
  if (*(int *)(param_1 + 0x118) < 0) {
    FUN_004fcc00();
  }
  return CONCAT31((int3)((uint)*(int *)(param_1 + 0x48) >> 8),
                  *(int *)(param_1 + 0x48) < *(int *)(param_1 + 0x118));
}

