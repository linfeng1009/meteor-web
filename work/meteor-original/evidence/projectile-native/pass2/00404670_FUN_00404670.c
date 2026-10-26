/* Original Meteor.exe static export @ 00404670; original sample not executed. */
/* XREF 00404447 UNCONDITIONAL_CALL */
/* XREF 00412a4c UNCONDITIONAL_CALL */

void FUN_00404670(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((DAT_005d5a00 != 0) && (DAT_005d5a0c != 0)) {
    iVar3 = 0x50;
    iVar1 = DAT_005d5a0c;
    do {
      if (*(int *)(iVar3 + iVar1) != 0) {
        FUN_005089fd(*(int *)(iVar3 + iVar1));
        *(undefined4 *)(iVar3 + DAT_005d5a0c) = 0;
        iVar1 = DAT_005d5a0c;
      }
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x450);
    if (*(int *)(iVar1 + 0x720) != 0) {
      FUN_005089fd(*(int *)(iVar1 + 0x720));
      *(undefined4 *)(DAT_005d5a0c + 0x720) = 0;
      iVar1 = DAT_005d5a0c;
    }
    FUN_005089fd(*(undefined4 *)(iVar1 + 0x69c));
    *(undefined4 *)(DAT_005d5a0c + 0x69c) = 0;
    if (*(int *)(DAT_005d5a0c + 0x6c8) != 0) {
      FUN_00415650(*(int *)(DAT_005d5a0c + 0x6c8));
      *(undefined4 *)(*(int *)(DAT_005d5a0c + 0x6c8) + 0x14) = 0;
      iVar1 = 0x98;
      do {
        iVar2 = iVar1 + 4;
        *(undefined4 *)(iVar1 + *(int *)(DAT_005d5a0c + 0x6c8)) = 0;
        iVar3 = DAT_005d5a0c;
        iVar1 = iVar2;
      } while (iVar2 < 200);
      (&DAT_007f0620)[**(int **)(DAT_005d5a0c + 0x6c8)] = 0;
      FUN_005089fd(*(undefined4 *)(iVar3 + 0x6c8));
      *(undefined4 *)(DAT_005d5a0c + 0x6c8) = 0;
    }
    FUN_00414c00(DAT_005d5a0c);
    if (param_1 != 0) {
      FUN_00414f30(DAT_005d5a0c);
    }
    FUN_005089fd(DAT_005d5a0c);
    DAT_005d5a0c = 0;
  }
  return;
}

