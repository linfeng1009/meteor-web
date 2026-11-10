/* Original Meteor.exe read-only export. Sample not executed. */

void FUN_00501f70(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_80 [5];
  undefined4 local_6c;
  undefined4 local_58;
  undefined1 local_40 [64];
  
  if (DAT_00667564 == 0) {
    FUN_00477200();
    local_80[0] = param_1;
    local_6c = param_2;
    local_58 = param_3;
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

