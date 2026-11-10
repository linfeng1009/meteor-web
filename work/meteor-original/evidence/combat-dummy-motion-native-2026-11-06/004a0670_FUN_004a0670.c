/* Original Meteor.exe static export @ 004a0670; original sample not executed. */
/* XREF 005a9598 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004a0670(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_1 + 0x14) != *(int *)(param_1 + 0x10)) {
    iVar2 = FUN_005499a0(0);
    if ((iVar2 != 0) &&
       (fVar1 = (float)*(int *)(param_1 + 0x78) + *(float *)(param_1 + 0x1c),
       *(float *)(param_1 + 0x1c) = fVar1,
       fVar1 <= (float)*(int *)(param_1 + 0x74) * (float)_DAT_005a9808 - (float)_DAT_005a9800)) {
      *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x70);
    }
    uVar3 = __ftol(*(undefined4 *)(param_1 + 0x10),0xff,0xff,0xff);
    uVar3 = __ftol(uVar3);
    FUN_00421d00(uVar3);
  }
  return;
}

