/* Original Meteor.exe static export @ 004fc9f0; original sample not executed. */
/* XREF 00503fe3 UNCONDITIONAL_CALL */
/* XREF 0050401e UNCONDITIONAL_CALL */
/* XREF 0050422b UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __thiscall FUN_004fc9f0(int param_1,uint param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  char cVar5;
  float10 fVar6;
  
  if (param_2 == 0) {
    return 0;
  }
  iVar3 = *(int *)(param_1 + 0x58);
  if (iVar3 < 0) {
    return param_2 & 0xffffff00;
  }
  fVar1 = *(float *)(param_1 + 0x20);
  fVar2 = *(float *)(param_2 + 0x20);
  fVar6 = (float10)FUN_0047ed20();
  fVar4 = *(float *)(&DAT_00666a04 + iVar3 * 0x38) * *(float *)(&DAT_00666a04 + iVar3 * 0x38);
  cVar5 = FUN_004fcf70();
  if (cVar5 == '\0') {
    cVar5 = FUN_00501030();
    if (cVar5 == '\0') {
      fVar6 = (float10)FUN_0047ed20();
      if ((float10)fVar4 * (float10)_DAT_005a8e84 <= fVar6) {
        return 0;
      }
      return 1;
    }
    fVar1 = ABS(fVar1 - fVar2);
    fVar2 = (float)_DAT_005ab858;
    if (fVar1 >= fVar2 && (fVar1 == fVar2) == 0) {
      return (uint)(ushort)((ushort)(fVar1 < fVar2) << 8 | (ushort)(fVar1 == fVar2) << 0xe);
    }
  }
  if (fVar4 <= (float)fVar6) {
    return 0;
  }
  return 1;
}

