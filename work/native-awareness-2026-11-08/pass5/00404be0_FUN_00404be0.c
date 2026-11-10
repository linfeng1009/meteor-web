/* Original Meteor.exe static export @ 00404be0; original sample not executed. */
/* XREF 00404aed UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404be0(undefined4 param_1,undefined4 param_2,float param_3,float param_4)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  
  if (DAT_005d5a00 != 0) {
    iVar2 = FUN_00410a70(param_1);
    if (((iVar2 != 0) && (*(int *)(iVar2 + 4) == 4)) && (*(int *)(iVar2 + 0x9c) != 0)) {
      fVar3 = (float10)_DAT_005a83fc;
      *(undefined4 *)(*(int *)(iVar2 + 0x9c) + 8) = param_2;
      *(float *)(*(int *)(iVar2 + 0x9c) + 0x10) = param_3;
      *(float *)(*(int *)(iVar2 + 0x9c) + 0x14) = param_4;
      fVar3 = (float10)fpatan(((float10)param_4 / ((float10)param_3 * fVar3)) *
                              (float10)_DAT_005a83e8,(float10)1);
      *(float *)(*(int *)(iVar2 + 0x9c) + 0xc) = (float)(fVar3 * (float10)_DAT_005a83f8);
      iVar1 = *(int *)(iVar2 + 0x9c);
      FUN_00430c70(iVar1 + 0x24,*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0x10),
                   *(undefined4 *)(iVar1 + 0x14),*(undefined4 *)(iVar1 + 0x18),
                   *(undefined4 *)(iVar1 + 0x1c),*(undefined4 *)(iVar1 + 100),
                   *(undefined4 *)(iVar1 + 0x68),*(undefined4 *)(iVar1 + 0x6c),
                   *(undefined4 *)(iVar1 + 0x70));
      FUN_00432040(*(undefined4 *)(iVar2 + 0x9c));
    }
  }
  return;
}

