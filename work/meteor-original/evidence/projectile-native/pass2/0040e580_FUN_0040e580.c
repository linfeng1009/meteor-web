/* Original Meteor.exe static export @ 0040e580; original sample not executed. */
/* XREF 004043dc UNCONDITIONAL_CALL */
/* XREF 00430936 UNCONDITIONAL_CALL */
/* XREF 00430956 UNCONDITIONAL_CALL */

void FUN_0040e580(uint param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  if (DAT_005d5a00 != 0) {
    iVar1 = FUN_00410ab0(param_1);
    if (iVar1 != 0) {
      iVar4 = 0;
      if (0 < DAT_007f18d8) {
        piVar3 = &DAT_007f0620;
        do {
          if (*piVar3 != 0) {
            iVar2 = 0x98;
            do {
              if (*(int *)(*piVar3 + iVar2) == iVar1) {
                *(int *)(*piVar3 + iVar2) = 0;
              }
              iVar2 = iVar2 + 4;
            } while (iVar2 < 200);
          }
          iVar4 = iVar4 + 1;
          piVar3 = piVar3 + 1;
        } while (iVar4 < DAT_007f18d8);
      }
      iVar4 = 0;
      if (0 < DAT_007f0604) {
        do {
          iVar2 = (&DAT_007e53c0)[iVar4];
          if ((iVar2 != 0) && (*(int *)(iVar2 + 0x88) == iVar1)) {
            *(undefined4 *)(iVar2 + 0x88) = 0;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < DAT_007f0604);
      }
      do {
        iVar4 = *(int *)(iVar1 + 0x20);
        if (*(int *)(iVar1 + 0x14) != 0) {
          FUN_005089fd(*(int *)(iVar1 + 0x14));
          *(undefined4 *)(iVar1 + 0x14) = 0;
        }
        if (*(int *)(iVar1 + 0x18) != 0) {
          FUN_005089fd(*(int *)(iVar1 + 0x18));
          *(undefined4 *)(iVar1 + 0x18) = 0;
        }
        FUN_005089fd(iVar1);
        iVar1 = iVar4;
      } while (iVar4 != 0);
      (&DAT_007e33c0)[param_1 & 0xffffff] = 0;
    }
  }
  return;
}

