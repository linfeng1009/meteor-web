/* Original Meteor.exe static read-only export; sample not executed. */

/* WARNING: Removing unreachable block (ram,0x004d64a5) */
/* WARNING: Removing unreachable block (ram,0x004d64b2) */
/* WARNING: Removing unreachable block (ram,0x004d650c) */

void __thiscall FUN_004d6400(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  
  piVar6 = (int *)**(int **)(param_1 + 0x50);
  if (piVar6 != *(int **)(param_1 + 0x50)) {
    do {
      piVar1 = (int *)*piVar6;
      (**(code **)piVar6[2])(0);
      FUN_00402e90(piVar6,0x50);
      piVar6 = piVar1;
    } while (piVar1 != (int *)*(int *)(param_1 + 0x50));
  }
  *(undefined4 *)*(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x50);
  *(int *)(*(int *)(param_1 + 0x50) + 4) = *(int *)(param_1 + 0x50);
  if (param_2 == 0) {
    piVar6 = (int *)**(int **)(param_1 + 0x40);
    if (piVar6 != *(int **)(param_1 + 0x40)) {
      do {
        piVar1 = (int *)*piVar6;
        (**(code **)piVar6[2])(0);
        FUN_00402e90(piVar6,0x50);
        piVar6 = piVar1;
      } while (piVar1 != (int *)*(int *)(param_1 + 0x40));
    }
    *(undefined4 *)*(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x40);
    *(int *)(*(int *)(param_1 + 0x40) + 4) = *(int *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  iVar4 = *(int *)(param_1 + 0x48);
  puVar3 = *(undefined4 **)(param_1 + 0x48);
  puVar2 = *(undefined4 **)(param_1 + 0x44);
  for (puVar5 = puVar2; puVar5 != puVar3; puVar5 = puVar5 + 0x12) {
    (**(code **)*puVar5)(0);
  }
  iVar4 = (int)((ulonglong)((longlong)(iVar4 - (int)puVar2) * -0x38e38e39) >> 0x20);
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + ((iVar4 >> 4) - (iVar4 >> 0x1f)) * 0x48;
  FUN_004d4a70(param_3);
  return;
}

