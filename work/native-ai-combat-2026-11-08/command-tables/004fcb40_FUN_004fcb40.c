/* Original Meteor.exe static export @ 004fcb40; original sample not executed. */
/* XREF 005041c7 UNCONDITIONAL_CALL */
/* XREF 0050421c UNCONDITIONAL_CALL */

uint __thiscall FUN_004fcb40(int param_1,uint param_2)

{
  int iVar1;
  float10 fVar2;
  
  if (param_2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x58);
  if (iVar1 < 0) {
    return param_2 & 0xffffff00;
  }
  fVar2 = (float10)FUN_0047ecf0();
  if (fVar2 < (float10)*(float *)(&DAT_00666a00 + iVar1 * 0x38)) {
    return 1;
  }
  return 0;
}

