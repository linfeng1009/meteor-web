/* Original Meteor.exe static export @ 004c2040; original sample not executed. */
/* XREF 004c1a23 UNCONDITIONAL_CALL */
/* XREF 004c1a49 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __thiscall FUN_004c2040(int param_1,int param_2,int param_3)

{
  int iVar1;
  float10 fVar2;
  float fVar3;
  uint uVar4;
  ushort uVar5;
  float10 fVar6;
  
  iVar1 = *(int *)(param_1 + 0x4fc);
  fVar3 = *(float *)(iVar1 + param_2 * 0x24 + 0xc) - *(float *)(iVar1 + param_3 * 0x24 + 0xc);
  uVar4 = CONCAT22((short)((uint)*(undefined4 *)(iVar1 + 4 + param_3 * 0x24) >> 0x10),
                   (ushort)(fVar3 < _DAT_005a83e4) << 8 |
                   (ushort)(NAN(fVar3) || NAN(_DAT_005a83e4)) << 10 |
                   (ushort)(fVar3 == _DAT_005a83e4) << 0xe);
  if ((fVar3 >= _DAT_005a83e4) &&
     (uVar4 = (uint)(ushort)((ushort)(fVar3 < _DAT_005a8f7c) << 8 |
                            (ushort)(fVar3 == _DAT_005a8f7c) << 0xe),
     fVar3 < _DAT_005a8f7c || (fVar3 == _DAT_005a8f7c) != 0)) {
    fVar6 = (float10)FUN_0047ecf0();
    fVar2 = (float10)_DAT_005a84c8;
    uVar5 = (ushort)(fVar6 < fVar2) << 8 | (ushort)(fVar6 == fVar2) << 0xe;
    uVar4 = (uint)uVar5;
    if (fVar6 < fVar2 || (fVar6 == fVar2) != 0) {
      return CONCAT31((uint3)(byte)(uVar5 >> 8),1);
    }
  }
  return uVar4;
}

