/* Meteor.exe original x86 @ 004d5790; function boundary recovered from direct vtable/code reference */
/* Caller: 005a94ac */

undefined4 __thiscall FUN_004d5790(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_1 + 0x44);
  if (iVar2 != *(int *)(param_1 + 0x48)) {
    if ((undefined4 *)(iVar2 + 4) != (undefined4 *)(param_2 + 4)) {
      FUN_00403200(*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8));
    }
    if ((undefined4 *)(iVar2 + 0x10) != (undefined4 *)(param_2 + 0x10)) {
      FUN_00403200(*(undefined4 *)(iVar2 + 0x10),*(undefined4 *)(iVar2 + 0x14));
    }
    if ((undefined4 *)(iVar2 + 0x1c) != (undefined4 *)(param_2 + 0x1c)) {
      FUN_00403200(*(undefined4 *)(iVar2 + 0x1c),*(undefined4 *)(iVar2 + 0x20));
    }
    *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(iVar2 + 0x28);
    *(undefined4 *)(param_2 + 0x2c) = *(undefined4 *)(iVar2 + 0x2c);
    FUN_004d4000(iVar2 + 0x30);
    FUN_004d3e60(iVar2 + 0x3c);
    if (iVar2 + 0x48 != *(int *)(param_1 + 0x48)) {
      iVar3 = (*(int *)(param_1 + 0x48) - (iVar2 + 0x48)) / 0x48;
      if (0 < iVar3) {
        iVar2 = iVar2 + 0x58;
        do {
          FUN_00473340(iVar2 + -0xc);
          FUN_00473340(iVar2);
          FUN_00473340(iVar2 + 0xc);
          *(undefined4 *)(iVar2 + -0x30) = *(undefined4 *)(iVar2 + 0x18);
          *(undefined4 *)(iVar2 + -0x2c) = *(undefined4 *)(iVar2 + 0x1c);
          FUN_004d4000(iVar2 + 0x20);
          FUN_004d3e60(iVar2 + 0x2c);
          iVar2 = iVar2 + 0x48;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
    puVar1 = (undefined4 *)(*(int *)(param_1 + 0x48) + -0x48);
    *(undefined4 **)(param_1 + 0x48) = puVar1;
    (**(code **)*puVar1)(0);
    return 1;
  }
  return 0;
}

