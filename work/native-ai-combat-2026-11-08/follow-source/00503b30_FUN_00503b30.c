/* Original Meteor.exe static export @ 00503b30; original sample not executed. */
/* XREF 004f90f9 DATA */
/* XREF 004f9163 DATA */
/* XREF 004fb981 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __fastcall FUN_00503b30(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  
  *(undefined4 *)(param_1 + 0x80) = 0x3e99999a;
  if ((*(int *)(param_1 + 0x78) == 0) && (FUN_004fc270(), *(int *)(param_1 + 0x78) == 0)) {
    uVar2 = FUN_00503d00();
    return uVar2;
  }
  uVar2 = FUN_004fdd70();
  if (((char)uVar2 == '\0') && (uVar2 = FUN_004fdf90(0x43480000), (char)uVar2 == '\0')) {
    fVar5 = (float10)FUN_0047ed20();
    iVar3 = FUN_004fc0b0(*(int *)(param_1 + 0x78) + 0x18,0x43480000);
    if ((iVar3 != 0) && ((float)fVar5 < _DAT_005abb10)) {
      uVar2 = FUN_004fd630(&LAB_00503e00);
      return uVar2;
    }
    if (*(int *)(param_1 + 0xc4) != -1) {
      iVar3 = *(int *)(param_1 + 0xa4);
      iVar1 = *(int *)(param_1 + 0xa8);
      uVar2 = _rand();
      uVar4 = (iVar1 - iVar3 >> 2) + 10;
      if (uVar2 % uVar4 != 0) {
        return uVar2 / uVar4;
      }
    }
    if ((float)fVar5 <= _DAT_005a84c4) {
      iVar3 = _rand();
      if (iVar3 % 6 == 0) {
        FUN_00500fa0();
        uVar2 = FUN_004fd530(*(undefined4 *)(param_1 + 0x78));
        return uVar2;
      }
      iVar3 = _rand();
      uVar2 = *(uint *)(param_1 + 0x10);
      if (iVar3 % 100 < (int)*(short *)(uVar2 + 10)) {
        iVar3 = _rand();
        uVar2 = iVar3 / 0x168;
        *(float *)(param_1 + 0xe0) = (float)(iVar3 % 0x168);
      }
    }
    else {
      uVar2 = FUN_004fbcc0(*(undefined4 *)(param_1 + 0x78));
      if ((char)uVar2 == '\0') {
        FUN_004fd530(*(undefined4 *)(param_1 + 0x78));
        iVar3 = _rand();
        uVar2 = iVar3 / 6;
        if ((iVar3 % 6 == 0) && (uVar2 = FUN_004fced0(0x40a00000), (char)uVar2 != '\0')) {
          uVar2 = FUN_005012d0();
        }
        *(undefined4 *)(param_1 + 0x80) = 0x3f000000;
        return uVar2;
      }
    }
  }
  return uVar2;
}

