/* Original Meteor.exe read-only export. Sample not executed. */

void FUN_00502000(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_80 [64];
  undefined1 local_40 [64];
  
  if (DAT_00667564 == 0) {
    FUN_00477e10(param_1);
    puVar1 = (undefined4 *)FUN_00476f00(local_40,local_80,&DAT_00666ce8);
    puVar3 = &DAT_00666ce8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}

