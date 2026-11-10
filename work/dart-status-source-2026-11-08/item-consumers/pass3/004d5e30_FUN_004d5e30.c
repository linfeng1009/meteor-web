/* Original Meteor.exe static read-only export; sample not executed. */

void * __thiscall FUN_004d5e30(int *param_1,int param_2,void *param_3)

{
  byte *pbVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  
  param_3 = (void *)(**(code **)(*param_1 + 0x30))(param_1,param_2,param_3);
  iVar4 = param_1[0xf];
  if (iVar4 != 0) {
    pbVar1 = *(byte **)(iVar4 + 0x40);
    iVar5 = 0;
    for (pbVar6 = *(byte **)(iVar4 + 0x3c); pbVar6 != pbVar1; pbVar6 = pbVar6 + 0x28) {
      if ((((*(int *)(pbVar6 + 8) == param_2) && (*(int *)(pbVar6 + 0x10) == -1)) &&
          ((*pbVar6 & 2) != 0)) && (*(int *)(pbVar6 + 4) == 0)) {
        if (*(int *)(pbVar6 + 0x14) == 0) {
          iVar4 = *(int *)(pbVar6 + 0x18);
        }
        else {
          if (*(int *)(pbVar6 + 0x14) != 1) goto LAB_004d5ebe;
          iVar4 = __ftol();
        }
        iVar5 = iVar5 + iVar4;
      }
LAB_004d5ebe:
    }
    param_3 = (void *)(iVar5 + (int)param_3);
  }
  puVar2 = (undefined4 *)param_1[0x14];
  puVar3 = (undefined4 *)*puVar2;
  do {
    if (puVar3 == puVar2) {
      if ((int)param_3 < 0) {
        param_3 = (void *)0x0;
      }
      return param_3;
    }
    pbVar1 = (byte *)puVar3[0x12];
    iVar4 = 0;
    for (pbVar6 = (byte *)puVar3[0x11]; pbVar6 != pbVar1; pbVar6 = pbVar6 + 0x28) {
      if (((*(int *)(pbVar6 + 8) == param_2) && (*(int *)(pbVar6 + 0x10) == -1)) &&
         (((*pbVar6 & 2) != 0 && (*(int *)(pbVar6 + 4) == 0)))) {
        if (*(int *)(pbVar6 + 0x14) == 0) {
          iVar5 = *(int *)(pbVar6 + 0x18);
        }
        else {
          if (*(int *)(pbVar6 + 0x14) != 1) goto LAB_004d5f3f;
          iVar5 = __ftol();
        }
        iVar4 = iVar4 + iVar5;
      }
LAB_004d5f3f:
    }
    puVar3 = (undefined4 *)*puVar3;
    param_3 = (void *)((int)param_3 + iVar4);
  } while( true );
}

