/* Original Meteor.exe read-only export. Sample not executed. */

int __fastcall FUN_00503d00(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(undefined4 *)(param_1 + 0x80) = 0x3e99999a;
  iVar1 = FUN_004fdd70();
  if ((char)iVar1 == '\0') {
    iVar1 = FUN_004fdf90(0x44fa0000);
    if ((char)iVar1 == '\0') {
      iVar1 = FUN_004fdf00();
      if (((char)iVar1 == '\0') &&
         ((*(int *)(param_1 + 0xc4) == -1 ||
          (iVar1 = *(int *)(param_1 + 0x84) / 0x28, *(int *)(param_1 + 0x84) % 0x28 == 0x14)))) {
        iVar1 = _rand();
        if (iVar1 % 7 == 0) {
          iVar1 = *(int *)(DAT_0066629c + 0x500) - *(int *)(DAT_0066629c + 0x4fc);
          iVar2 = iVar1 / 0x24;
          iVar1 = -(iVar1 >> 0x1f);
          if (0 < iVar2) {
            iVar1 = _rand();
            iVar1 = FUN_004c2bf0(iVar1 % iVar2);
            iVar1 = FUN_004fbaa0(iVar1 + 4);
            return iVar1;
          }
        }
        else {
          iVar2 = _rand();
          iVar1 = *(int *)(param_1 + 0x10);
          if (iVar2 % 100 < (int)*(short *)(iVar1 + 10)) {
            iVar2 = _rand();
            iVar1 = iVar2 / 0x168;
            *(float *)(param_1 + 0xe0) = (float)(iVar2 % 0x168);
          }
        }
      }
    }
  }
  return iVar1;
}

