/* Original Meteor.exe static export @ 00571cf0; original sample not executed. */
/* XREF 00557792 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00571cf0(int param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  
  iVar2 = *(int *)(param_1 + 0x20);
  fVar3 = _DAT_005a83e4;
  if (0 < iVar2) {
    pfVar4 = *(float **)(param_1 + 0x28);
    iVar5 = iVar2;
    do {
      fVar3 = fVar3 + *pfVar4;
      pfVar4 = pfVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  iVar5 = 0;
  if (0 < iVar2) {
    fVar3 = _DAT_005a83f4 / fVar3;
    do {
      iVar2 = iVar5 * 4;
      iVar1 = iVar5 * 4;
      iVar5 = iVar5 + 1;
      *(float *)(*(int *)(param_1 + 0x28) + iVar1) =
           fVar3 * *(float *)(*(int *)(param_1 + 0x28) + iVar2);
    } while (iVar5 < *(int *)(param_1 + 0x20));
  }
  return;
}

