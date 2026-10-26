/* Original Meteor.exe static export @ 0056e050; original sample not executed. */
/* XREF 0056e519 UNCONDITIONAL_CALL */
/* XREF 0056e82f UNCONDITIONAL_CALL */

/* WARNING: Removing unreachable block (ram,0x0056e094) */
/* WARNING: Removing unreachable block (ram,0x0056e099) */
/* WARNING: Removing unreachable block (ram,0x0056e0a4) */

void __fastcall FUN_0056e050(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x40)) {
    do {
      piVar1 = *(int **)(*(int *)(param_1 + 0x4c) + iVar2 * 4);
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x24))(1);
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 * 4) = 0;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(param_1 + 0x40));
  }
  *(int *)(param_1 + 0x50) =
       *(int *)(param_1 + 0x50) + (*(int *)(param_1 + 0x50) - *(int *)(param_1 + 0x4c) >> 2) * -4;
  *(undefined4 *)(param_1 + 0x40) = 0;
  DAT_0072b730 = 0;
  return;
}

