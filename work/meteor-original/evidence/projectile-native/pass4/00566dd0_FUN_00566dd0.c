/* Original Meteor.exe static export @ 00566dd0; original sample not executed. */
/* XREF 00566d1e UNCONDITIONAL_CALL */
/* XREF 004db75f UNCONDITIONAL_CALL */

void __thiscall FUN_00566dd0(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int *piVar5;
  int local_4;
  
  puVar1 = *(undefined4 **)(param_1 + 0x10);
  puVar2 = (undefined4 *)*puVar1;
  local_4 = param_1;
  while (puVar4 = puVar2, puVar4 != puVar1) {
    puVar2 = (undefined4 *)*puVar4;
    if (puVar4[2] == param_2) {
      puVar3 = (undefined4 *)puVar4[1];
      *puVar3 = puVar2;
      puVar2[1] = puVar3;
      FUN_00402e90(puVar4,0xc);
    }
  }
  FUN_004db820(&local_4);
  piVar5 = (int *)FUN_0055e2b0(&param_2);
  *piVar5 = local_4;
  piVar5[1] = *(int *)(local_4 + 4);
  **(int **)(local_4 + 4) = (int)piVar5;
  *(int **)(local_4 + 4) = piVar5;
  return;
}

