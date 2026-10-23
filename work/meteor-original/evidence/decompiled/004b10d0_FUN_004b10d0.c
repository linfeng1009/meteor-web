/* Meteor.exe original x86 @ 004b10d0; function boundary recovered from direct vtable/code reference */
/* Caller: 005a9c4c */
/* Caller: 005aa3bc */
/* Caller: 005aa514 */

void __fastcall FUN_004b10d0(int param_1)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  iVar4 = *(int *)(*(int *)(param_1 + 0x3a8) + 8);
  if (iVar4 != *(int *)(param_1 + 0x3a8)) {
    do {
      uStack_18 = 0;
      uStack_1c = 2;
      uStack_20 = 0x4b10fe;
      (**(code **)(*(int *)(iVar4 + 0x88) + 0x34))();
      uStack_20 = 0;
      uVar2 = (**(code **)(*(int *)(iVar4 + 0x88) + 0x34))(1);
      uStack_18 = CONCAT22(uVar2,(undefined2)uStack_18);
      uVar2 = (**(code **)(*(int *)(iVar4 + 0x88) + 0x34))(6,0);
      uStack_1c = CONCAT22(uStack_1c._2_2_,uVar2);
      FUN_004acae0(*(undefined4 *)(iVar4 + 0x10),0x19,&uStack_20,6,0);
      iVar3 = *(int *)(iVar4 + 0xc);
      if (iVar3 == 0) {
        iVar3 = *(int *)(iVar4 + 4);
        if (iVar4 == *(int *)(iVar3 + 0xc)) {
          do {
            iVar4 = iVar3;
            iVar3 = *(int *)(iVar4 + 4);
          } while (iVar4 == *(int *)(iVar3 + 0xc));
        }
        if (*(int *)(iVar4 + 0xc) != iVar3) {
          iVar4 = iVar3;
        }
      }
      else {
        for (iVar1 = *(int *)(iVar3 + 8); iVar4 = iVar3, iVar1 != 0; iVar1 = *(int *)(iVar1 + 8)) {
          iVar3 = iVar1;
        }
      }
    } while (iVar4 != *(int *)(param_1 + 0x3a8));
  }
  return;
}

