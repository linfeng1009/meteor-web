/* Original Meteor.exe static export @ 00405030; original sample not executed. */
/* XREF 0040501d UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00405030(undefined4 param_1,int param_2,undefined4 param_3,float param_4,float param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9)

{
  int iVar1;
  uint uVar2;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (DAT_005d5a00 != 0) {
    iVar1 = FUN_00410a70(param_1);
    if ((iVar1 != 0) && (*(int *)(iVar1 + 4) == 7)) {
      *(float *)(*(int *)(iVar1 + 0x9c) + 8) = param_4 * _DAT_005a83e8;
      *(float *)(*(int *)(iVar1 + 0x9c) + 0xc) = param_5 * _DAT_005a83e8;
      if (param_2 != 0) {
        uVar2 = *(uint *)(*(int *)(iVar1 + 0x9c) + 4);
        if (uVar2 != 0xffffffff) {
          FUN_0040f870(uVar2 | 0x3000000);
        }
        local_4 = 0x3f333333;
        local_8 = 0x3f333333;
        local_c = 0x3f333333;
        local_10 = 0x3f800000;
        local_14 = 0x3f800000;
        local_18 = 0x3f800000;
        local_1c = 0;
        local_20 = 0;
        local_24 = 0;
        local_28 = 0x3f800000;
        local_2c = 0x3f800000;
        local_30 = 0x3f800000;
        uVar2 = FUN_0040f090(&local_c,&local_18,&local_24,&local_30,0x42200000,param_2,param_3,0,0,
                             param_6,param_7,param_8,param_9);
        if (uVar2 != 0) {
          *(uint *)(*(int *)(iVar1 + 0x9c) + 4) = uVar2 & 0xffffff;
          FUN_004054e0(0,10,2);
          return;
        }
        *(undefined4 *)(*(int *)(iVar1 + 0x9c) + 4) = 0xffffffff;
        FUN_004054e0(0,10,2);
      }
    }
  }
  return;
}

