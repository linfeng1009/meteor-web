/* Original Meteor.exe static export @ 004fdf00; original sample not executed. */
/* XREF 00503a31 UNCONDITIONAL_CALL */
/* XREF 00503d33 UNCONDITIONAL_CALL */
/* XREF 005039dc UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004fdf00(int param_1)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  
  iVar1 = *(int *)(param_1 + 0x74);
  iVar2 = FUN_004fc0a0();
  if (iVar2 != 0) {
    FUN_004fd630(&LAB_00503e00);
    return 1;
  }
  if (iVar1 != 0) {
    fVar3 = (float10)FUN_0047ed20();
    if (fVar3 < (float10)_DAT_005a94fc) {
      *(int *)(param_1 + 0x74) = iVar1;
      return 1;
    }
  }
  return 0;
}

