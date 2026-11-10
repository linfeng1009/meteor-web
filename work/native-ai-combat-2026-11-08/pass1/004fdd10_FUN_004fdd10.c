/* Original Meteor.exe static export @ 004fdd10; original sample not executed. */
/* XREF 004fdb93 UNCONDITIONAL_CALL */
/* XREF 004fd5bf UNCONDITIONAL_CALL */
/* XREF 004fd08e UNCONDITIONAL_CALL */

/* WARNING: Removing unreachable block (ram,0x004fdd2b) */
/* WARNING: Removing unreachable block (ram,0x004fdd31) */
/* WARNING: Removing unreachable block (ram,0x004fdd3c) */

void __fastcall FUN_004fdd10(int param_1)

{
  *(int *)(param_1 + 0xa8) =
       *(int *)(param_1 + 0xa8) + (*(int *)(param_1 + 0xa8) - *(int *)(param_1 + 0xa4) >> 2) * -4;
  *(undefined4 *)(param_1 + 0xc4) = 0xffffffff;
  return;
}

