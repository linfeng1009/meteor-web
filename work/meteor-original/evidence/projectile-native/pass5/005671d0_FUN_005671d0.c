/* Original Meteor.exe static export @ 005671d0; original sample not executed. */
/* XREF 004b8a83 UNCONDITIONAL_CALL */

void __fastcall FUN_005671d0(int param_1)

{
  int *piVar1;
  
  piVar1 = (int *)**(int **)(param_1 + 0x10);
  if (piVar1 != *(int **)(param_1 + 0x10)) {
    do {
      (**(code **)(*(int *)piVar1[2] + 0x14))();
      piVar1 = (int *)*piVar1;
    } while (piVar1 != (int *)*(int *)(param_1 + 0x10));
  }
  FUN_00566f80();
  return;
}

