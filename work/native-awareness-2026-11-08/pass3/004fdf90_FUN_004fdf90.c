/* Original Meteor.exe static export @ 004fdf90; original sample not executed. */
/* XREF 005039cd UNCONDITIONAL_CALL */
/* XREF 00503a22 UNCONDITIONAL_CALL */
/* XREF 00503b75 UNCONDITIONAL_CALL */
/* XREF 00503d24 UNCONDITIONAL_CALL */
/* XREF 0050469a UNCONDITIONAL_CALL */
/* XREF 00503fd0 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004fdf90(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar2 = *(uint *)(param_1 + 0x84) & 0x80000003;
  if ((int)uVar2 < 0) {
    uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
  }
  if (((uVar2 == 3) &&
      (iVar3 = _rand(), iVar3 % 100 <= (int)*(short *)(*(int *)(param_1 + 0x10) + 0x10))) &&
     (cVar1 = FUN_004fc2b0(param_2), cVar1 != '\0')) {
    cVar1 = FUN_004fbaa0(param_1 + 0xe8);
    if (cVar1 == '\0') {
      iVar3 = *(int *)(param_1 + 0xf4);
    }
    else {
      fVar4 = (float10)FUN_0047ed20();
      iVar3 = *(int *)(param_1 + 0xf4);
      if (fVar4 <= (float10)_DAT_005ab874) {
        if (iVar3 == 1) {
          if (*(int *)(param_1 + 0xf8) == *(int *)(param_1 + 0x50)) {
            return 0;
          }
          if (*(int *)(param_1 + 0xf8) == *(int *)(param_1 + 0x54)) {
            return 0;
          }
          if (-1 < *(int *)(param_1 + 0x54)) {
            uVar2 = _rand();
            uVar2 = uVar2 & 0x80000001;
            if ((int)uVar2 < 0) {
              uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
            }
            if (uVar2 != 0) {
              return 0;
            }
            FUN_00501280();
          }
        }
        FUN_004fd630(&LAB_005048f0);
        return 1;
      }
    }
    if (iVar3 == 4) {
      *(undefined4 *)(param_1 + 0xe4) = 0xffffffff;
    }
  }
  return 0;
}

