/* Original Meteor.exe static export @ 005656f0; original sample not executed. */
/* XREF 0048b5fa UNCONDITIONAL_CALL */

undefined4 FUN_005656f0(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = FUN_00564f90(*param_1);
  if (iVar1 == 0) {
    return 0;
  }
  switch(param_1[1]) {
  case 1:
    FUN_00560940(param_1[2],param_1[3]);
    return 1;
  case 2:
    if (*(int *)(iVar1 + 0x2c) != 0) {
      FUN_00569330(param_1[2]);
      return 1;
    }
    break;
  case 3:
    *(bool *)(iVar1 + 10) = param_1[2] != 0;
    return 1;
  case 4:
    *(bool *)(iVar1 + 9) = param_1[2] != 0;
    return 1;
  case 5:
    *(bool *)(iVar1 + 0xb) = param_1[2] != 0;
    return 1;
  case 6:
    *(bool *)(iVar1 + 8) = param_1[2] != 0;
    return 1;
  case 7:
    *(undefined1 *)(iVar1 + 0xc) = *(undefined1 *)(param_1 + 2);
    return 1;
  case 8:
    iVar2 = FUN_00567250(param_1[2],0);
    if (iVar2 != 0) {
      puVar3 = (undefined4 *)FUN_0047b740();
      puVar4 = (undefined4 *)(*(int *)(iVar1 + 0x28) + 0x98);
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar3 = puVar3 + 1;
      }
      FUN_0047b750();
    }
  }
  return 1;
}

