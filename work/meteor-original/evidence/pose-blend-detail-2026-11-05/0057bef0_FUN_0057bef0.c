/* Original Meteor.exe static export @ 0057bef0; original sample not executed. */
/* XREF 0057b058 UNCONDITIONAL_CALL */

void FUN_0057bef0(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x18);
  piVar4 = *(int **)(param_1 + 0x88);
  uVar3 = 0;
  iVar2 = *(int *)(param_1 + 0x8c) - (int)piVar4;
  iVar1 = iVar2 >> 0x1f;
  if (iVar2 / 0xc + iVar1 != iVar1) {
    do {
      if (*piVar4 < *(int *)(param_1 + 0x40)) {
        *(int *)(param_1 + 0x40) = *piVar4;
      }
      uVar3 = uVar3 + 1;
      piVar4 = piVar4 + 3;
    } while (uVar3 < (uint)((*(int *)(param_1 + 0x8c) - *(int *)(param_1 + 0x88)) / 0xc));
  }
  if (*(int *)(param_1 + 0x40) == *(int *)(param_1 + 0x18)) {
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x14);
  }
  return;
}

