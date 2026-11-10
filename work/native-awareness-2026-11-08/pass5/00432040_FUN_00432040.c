/* Original Meteor.exe static export @ 00432040; original sample not executed. */
/* XREF 00404ba3 UNCONDITIONAL_CALL */
/* XREF 00404bd0 UNCONDITIONAL_CALL */
/* XREF 00404c9f UNCONDITIONAL_CALL */
/* XREF 00404e28 UNCONDITIONAL_CALL */
/* XREF 00404e55 UNCONDITIONAL_CALL */
/* XREF 00404d65 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00432040(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x18);
  *(float *)(param_1 + 0x84) = -*(float *)(param_1 + 0x1c);
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0x3f800000;
  if (*(int *)(param_1 + 4) == 1) {
    fVar1 = *(float *)(param_1 + 0x10) * _DAT_005a8434;
    *(undefined4 *)(param_1 + 0x98) = 0;
    fVar1 = (*(float *)(param_1 + 0x18) / fVar1) * *(float *)(param_1 + 0x14);
    fVar2 = -fVar1;
    fVar3 = fVar1 / *(float *)(param_1 + 8);
    fVar5 = -fVar3;
    fVar4 = (*(float *)(param_1 + 100) + _DAT_005a83f4) * (fVar1 - fVar2) * _DAT_005a83e8;
    fVar1 = (*(float *)(param_1 + 0x6c) + *(float *)(param_1 + 100) + _DAT_005a83f4) *
            (fVar1 - fVar2) * _DAT_005a83e8;
    fVar3 = fVar3 - fVar5;
    fVar6 = (*(float *)(param_1 + 0x68) + _DAT_005a83f4) * fVar3 * _DAT_005a83e8;
    *(float *)(param_1 + 0x9c) = -*(float *)(param_1 + 0x18);
    *(float *)(param_1 + 0xa0) =
         -((*(float *)(param_1 + 0x70) + *(float *)(param_1 + 0x68) + _DAT_005a83f4) * fVar3 *
           _DAT_005a83e8 + fVar5);
    FUN_00431a20((undefined4 *)(param_1 + 0x98));
    *(undefined4 *)(extraout_EDX + 0xac) = *(undefined4 *)(extraout_EDX + 0x18);
    *(undefined4 *)(extraout_EDX + 0x94) = 0;
    *(undefined4 *)(extraout_EDX + 0xa8) = 0;
    *(float *)(extraout_EDX + 0xb0) = fVar6 + fVar5;
    FUN_00431a20((undefined4 *)(extraout_EDX + 0xa8));
    *(undefined4 *)(extraout_EDX_00 + 0xa4) = 0;
    *(undefined4 *)(extraout_EDX_00 + 0xb8) = *(undefined4 *)(extraout_EDX_00 + 0x18);
    *(undefined4 *)(extraout_EDX_00 + 0xbc) = 0;
    *(float *)(extraout_EDX_00 + 0xc0) = fVar4 + fVar2;
    FUN_00431a20((undefined4 *)(extraout_EDX_00 + 0xb8));
    *(undefined4 *)(extraout_EDX_01 + 0xb4) = 0;
    *(undefined4 *)(extraout_EDX_01 + 0xcc) = 0;
    *(float *)(extraout_EDX_01 + 200) = -*(float *)(extraout_EDX_01 + 0x18);
    *(float *)(extraout_EDX_01 + 0xd0) = -(fVar1 + fVar2);
    FUN_00431a20((float *)(extraout_EDX_01 + 200));
    *(undefined4 *)(extraout_EDX_02 + 0xc4) = 0;
    return;
  }
  fVar1 = _DAT_005a83e8 / *(float *)(param_1 + 8);
  *(undefined4 *)(param_1 + 0xac) = 0x3f800000;
  *(undefined4 *)(param_1 + 0xb8) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  *(undefined4 *)(param_1 + 0xbc) = 0;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0xbf800000;
  *(undefined4 *)(param_1 + 0xb4) = 0xbf000000;
  *(undefined4 *)(param_1 + 200) = 0xbf800000;
  *(undefined4 *)(param_1 + 0xc4) = 0xbf000000;
  fVar1 = -fVar1;
  *(float *)(param_1 + 0x94) = fVar1;
  *(float *)(param_1 + 0xa4) = fVar1;
  return;
}

