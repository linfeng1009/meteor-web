/* Original Meteor.exe static export @ 004fc270; original sample not executed. */
/* XREF 00503b47 UNCONDITIONAL_CALL */

undefined4 __fastcall FUN_004fc270(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004c33e0(*(undefined4 *)(param_1 + 0xfc),*(undefined4 *)(param_1 + 0x4c));
  *(int *)(param_1 + 0x78) = iVar1;
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x48) < 1)) {
    *(undefined4 *)(param_1 + 0x78) = 0;
  }
  return *(undefined4 *)(param_1 + 0x78);
}

