/* Original Meteor.exe static export @ 0055d1e0; original sample not executed. */
/* XREF 0055d309 UNCONDITIONAL_CALL */
/* XREF 0055d8ca UNCONDITIONAL_CALL */

void __thiscall FUN_0055d1e0(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if (((param_2 != 0) && (iVar1 = FUN_00567220(), iVar1 != 0)) &&
     (uVar2 = 0, *(int *)(param_2 + 0x2c) - *(int *)(param_2 + 0x28) >> 2 != 0)) {
    do {
      iVar1 = FUN_00566a90(*(undefined4 *)(*(int *)(param_2 + 0x28) + uVar2 * 4),param_1);
      if (iVar1 != 0) {
        FUN_00566220(1);
        if (*(int *)(param_1 + 0x63c) != 0) {
          FUN_00566370(*(undefined4 *)(*(int *)(param_1 + 0x63c) + 0xc));
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < (uint)(*(int *)(param_2 + 0x2c) - *(int *)(param_2 + 0x28) >> 2));
  }
  return;
}

