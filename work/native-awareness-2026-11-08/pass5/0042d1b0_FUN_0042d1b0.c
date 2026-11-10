/* Original Meteor.exe static export @ 0042d1b0; original sample not executed. */
/* XREF 0042ea33 UNCONDITIONAL_CALL */

void FUN_0042d1b0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (*(int **)(param_1 + 0xc0))[8];
  if (iVar1 == 0) {
    return;
  }
  iVar1 = *(int *)(iVar1 + 0xc0);
  if (**(int **)(param_1 + 0xc0) == 1) {
    uVar2 = __ftol();
    *(undefined4 *)(iVar1 + 0x5c) = uVar2;
    FUN_0042f0c0();
    return;
  }
  uVar2 = __ftol();
  *(undefined4 *)(iVar1 + 0x58) = uVar2;
  FUN_0042f0c0();
  return;
}

