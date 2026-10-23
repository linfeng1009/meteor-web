/* Meteor.exe original x86 @ 004d56c0; function boundary recovered from direct vtable/code reference */
/* Caller: 005a94a8 */

undefined4 __thiscall FUN_004d56c0(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  
  uVar4 = 0;
  piVar3 = *(int **)(param_1 + 0x40);
  piVar2 = (int *)*piVar3;
  if (piVar2 != piVar3) {
    do {
      piVar2 = (int *)*piVar2;
      uVar4 = uVar4 + 1;
    } while (piVar2 != piVar3);
    if (1 < uVar4) {
      iVar1 = *(int *)(*(int *)(param_1 + 0x40) + 4);
      if ((undefined4 *)(iVar1 + 0xc) != (undefined4 *)(param_2 + 4)) {
        FUN_00403200(*(undefined4 *)(iVar1 + 0xc),*(undefined4 *)(iVar1 + 0x10));
      }
      if ((undefined4 *)(iVar1 + 0x18) != (undefined4 *)(param_2 + 0x10)) {
        FUN_00403200(*(undefined4 *)(iVar1 + 0x18),*(undefined4 *)(iVar1 + 0x1c));
      }
      FUN_00473340(iVar1 + 0x24);
      *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(iVar1 + 0x30);
      *(undefined4 *)(param_2 + 0x2c) = *(undefined4 *)(iVar1 + 0x34);
      FUN_004d4000(iVar1 + 0x38);
      FUN_004d3e60(iVar1 + 0x44);
      piVar3 = (int *)FUN_004d6b10();
      piVar3 = (int *)*piVar3;
      piVar2 = (int *)piVar3[1];
      iVar1 = *piVar3;
      *piVar2 = iVar1;
      *(int **)(iVar1 + 4) = piVar2;
      (**(code **)piVar3[2])(0);
      FUN_00402e90(piVar3,0x50);
      return 1;
    }
  }
  return 0;
}

