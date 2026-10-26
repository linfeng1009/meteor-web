/* Meteor.exe original x86 @ 004f25b0; function boundary recovered from direct vtable/code reference */
/* Caller: 005aa104 */
/* Caller: 005ab58c */
/* Caller: 005ab9cc */
/* Caller: 005ab34c */

void __thiscall FUN_004f25b0(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iStack_c;
  int iStack_8;
  undefined4 uStack_4;
  
  iVar3 = FUN_00487830();
  iVar3 = *(int *)(*(int *)(iVar3 + 0x2188) + 8);
  iVar4 = (**(code **)(*param_1 + 0x48))();
  iVar5 = FUN_00487830();
  if (iVar3 != *(int *)(iVar5 + 0x2188)) {
    do {
      if (iVar4 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = iVar4 + 0x65c;
      }
      iVar1 = *(int *)(iVar3 + 0x14);
      if (iVar1 != iVar5) {
        if (iVar1 == 0) {
          iStack_c = 0;
        }
        else {
          iStack_c = iVar1 + -0x65c;
        }
        iStack_8 = *(int *)(iVar3 + 0x10);
        piVar2 = *(int **)(param_2 + 4);
        uStack_4 = 0x41200000;
        if (piVar2 == *(int **)(param_2 + 8)) {
          FUN_004f4260(piVar2,&iStack_c);
        }
        else {
          if (piVar2 != (int *)0x0) {
            *piVar2 = iStack_c;
            piVar2[1] = iStack_8;
            piVar2[2] = 0x41200000;
          }
          *(int *)(param_2 + 4) = *(int *)(param_2 + 4) + 0xc;
        }
      }
      iVar5 = *(int *)(iVar3 + 0xc);
      if (iVar5 == 0) {
        iVar5 = *(int *)(iVar3 + 4);
        if (iVar3 == *(int *)(iVar5 + 0xc)) {
          do {
            iVar3 = iVar5;
            iVar5 = *(int *)(iVar3 + 4);
          } while (iVar3 == *(int *)(iVar5 + 0xc));
        }
        if (*(int *)(iVar3 + 0xc) != iVar5) {
          iVar3 = iVar5;
        }
      }
      else {
        for (iVar1 = *(int *)(iVar5 + 8); iVar3 = iVar5, iVar1 != 0; iVar1 = *(int *)(iVar1 + 8)) {
          iVar5 = iVar1;
        }
      }
      iVar5 = FUN_00487830();
    } while (iVar3 != *(int *)(iVar5 + 0x2188));
  }
  return;
}

