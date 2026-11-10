/* Original Meteor.exe static read-only export; sample not executed. */

void FUN_005452d0(int *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = (undefined4 *)(**(code **)param_1[1])(param_1,1,param_2 << 5);
  iVar3 = 0;
  *puVar1 = 0;
  puVar1[1] = 0x1f;
  puVar1[2] = 0;
  puVar1[3] = 0x3f;
  puVar1[4] = 0;
  puVar1[5] = 0x1f;
  FUN_00545360(param_1,puVar1);
  iVar2 = FUN_00545720(param_1,puVar1,1,param_2);
  if (0 < iVar2) {
    do {
      FUN_005458d0(param_1,puVar1,iVar3);
      iVar3 = iVar3 + 1;
      puVar1 = puVar1 + 8;
    } while (iVar3 < iVar2);
  }
  param_1[0x1c] = iVar2;
  *(undefined4 *)(*param_1 + 0x14) = 0x60;
  *(int *)(*param_1 + 0x18) = iVar2;
  (**(code **)(*param_1 + 4))(param_1,1);
  return;
}

