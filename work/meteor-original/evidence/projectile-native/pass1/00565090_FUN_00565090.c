/* Original Meteor.exe static export @ 00565090; original sample not executed. */
/* XREF 004945ae UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00565090(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)FUN_00564f90(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  puVar4 = puVar1;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *param_2;
    param_2 = param_2 + 1;
    puVar4 = puVar4 + 1;
  }
  if (puVar1[0xb] != 0) {
    FUN_005694e0((int)*(short *)((int)puVar1 + 0xe),0);
    FUN_005693f0((float)(int)*(short *)(puVar1 + 4));
    FUN_0056ad20(puVar1[1]);
    iVar3 = (*(code *)PTR_FUN_005d186c)(0xb,0,0);
    iVar2 = (*(code *)PTR_FUN_005d186c)(10,0,0);
    FUN_00569580((float)(iVar2 - iVar3) * _DAT_005a8414);
  }
  return 1;
}

