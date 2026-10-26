/* Original Meteor.exe static export @ 00566f10; original sample not executed. */
/* XREF 0048fbcc UNCONDITIONAL_CALL */

void __fastcall FUN_00566f10(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)**(int **)(param_1 + 0x10);
  if (piVar3 != *(int **)(param_1 + 0x10)) {
    do {
      piVar1 = (int *)piVar3[2];
      iVar2 = FUN_0056f310();
      if (iVar2 != 0) {
        FUN_0055df80(piVar1);
      }
      (**(code **)(*piVar1 + 8))(1);
      piVar3 = (int *)*piVar3;
    } while (piVar3 != (int *)*(int *)(param_1 + 0x10));
  }
  piVar3 = (int *)**(int **)(param_1 + 0x10);
  if (piVar3 != *(int **)(param_1 + 0x10)) {
    do {
      piVar1 = (int *)*piVar3;
      FUN_00402e90(piVar3,0xc);
      piVar3 = piVar1;
    } while (piVar1 != (int *)*(int *)(param_1 + 0x10));
  }
  *(undefined4 *)*(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x10);
  *(int *)(*(int *)(param_1 + 0x10) + 4) = *(int *)(param_1 + 0x10);
  return;
}

