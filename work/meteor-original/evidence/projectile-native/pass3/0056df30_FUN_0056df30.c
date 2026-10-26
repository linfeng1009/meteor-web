/* Original Meteor.exe static export @ 0056df30; original sample not executed. */
/* XREF 0056e027 UNCONDITIONAL_CALL */
/* XREF 0056e03d UNCONDITIONAL_CALL */
/* XREF 0056e7ef UNCONDITIONAL_CALL */

void __fastcall FUN_0056df30(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = 0;
  if (*(int *)(param_1 + 0x128) == 0) {
    iVar1 = *(int *)(*(int *)(param_1 + 300) + 0x1ec);
  }
  if ((*(char *)(param_1 + 0x58) == '\0') || (iVar1 == 0)) {
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(iVar1 + 0x14);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(iVar1 + 0x18);
  }
  iVar2 = 0;
  iVar1 = *(int *)(param_1 + 0x50) - *(int *)(param_1 + 0x4c) >> 2;
  *(int *)(param_1 + 0x40) = iVar1;
  if (0 < iVar1) {
    piVar3 = *(int **)(param_1 + 0x4c);
    do {
      iVar1 = *(int *)(*piVar3 + 0x1ec);
      if (*(float *)(iVar1 + 0x14) < *(float *)(param_1 + 0x18)) {
        *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(iVar1 + 0x14);
      }
      if (*(float *)(param_1 + 0x1c) < *(float *)(iVar1 + 0x18)) {
        *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(iVar1 + 0x18);
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 < *(int *)(param_1 + 0x40));
  }
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x1c);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x1c) - *(float *)(param_1 + 0x18);
  return;
}

