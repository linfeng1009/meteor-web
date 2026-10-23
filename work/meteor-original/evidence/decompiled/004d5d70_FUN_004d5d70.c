/* Meteor.exe original x86 @ 004d5d70; function boundary recovered from direct vtable/code reference */
/* Caller: 005a94bc */

undefined4 __thiscall FUN_004d5d70(int param_1,int param_2,int param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = param_2;
  piVar1 = *(int **)(param_1 + 0x34);
  piVar3 = *(int **)(param_1 + 0x30);
  if (piVar3 != piVar1) {
    do {
      if (*piVar3 == param_2) break;
      piVar3 = piVar3 + 3;
    } while (piVar3 != piVar1);
    if ((piVar3 != piVar1) && (piVar3 != (int *)0x0)) {
      param_2 = param_3;
      FUN_004d4d30(iVar2,param_3,&param_2);
      iVar2 = piVar3[2];
      piVar3[2] = iVar2 + param_2;
      if (param_4 != (int *)0x0) {
        *param_4 = piVar3[1] + iVar2 + param_2;
      }
      return 0;
    }
  }
  return 0xffffffff;
}

