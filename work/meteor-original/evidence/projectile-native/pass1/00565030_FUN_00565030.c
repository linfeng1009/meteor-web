/* Original Meteor.exe static export @ 00565030; original sample not executed. */
/* XREF 0049466d UNCONDITIONAL_CALL */

undefined4 FUN_00565030(undefined4 param_1,undefined4 *param_2)

{
  undefined2 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar2 = (undefined4 *)FUN_00564f90(param_1);
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  puVar5 = puVar2;
  puVar6 = param_2;
  for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  if (puVar2[0xb] != 0) {
    uVar1 = FUN_00569560();
    *(undefined2 *)((int)param_2 + 0xe) = uVar1;
    uVar1 = FUN_00569570();
    *(undefined2 *)(param_2 + 4) = uVar1;
    uVar3 = FUN_0056ad10();
    param_2[1] = uVar3;
  }
  return 1;
}

