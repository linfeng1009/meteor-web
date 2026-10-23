/* Meteor.exe original x86 @ 004d5d30; function boundary recovered from direct vtable/code reference */
/* Caller: 005a94b8 */

undefined4 __thiscall FUN_004d5d30(int param_1,int param_2,int param_3)

{
  int *piVar1;
  
  for (piVar1 = *(int **)(param_1 + 0x30);
      (piVar1 != *(int **)(param_1 + 0x34) && (*piVar1 != param_2)); piVar1 = piVar1 + 3) {
  }
  if ((piVar1 != *(int **)(param_1 + 0x34)) && (piVar1 != (int *)0x0)) {
    piVar1[2] = 0;
    piVar1[1] = param_3;
    return 0;
  }
  return 0xffffffff;
}

