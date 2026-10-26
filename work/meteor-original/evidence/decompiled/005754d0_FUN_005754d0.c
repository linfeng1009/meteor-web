/* Meteor.exe original x86 @ 005754d0; function boundary recovered from direct vtable/code reference */
/* Caller: 0057b53c */
/* Caller: 0057b75d */

void __thiscall FUN_005754d0(int param_1,int param_2)

{
  if (*(int *)(param_2 + 0x4c) == -1) {
    *(undefined4 *)(param_2 + 0x4c) = *(undefined4 *)(param_2 + 0x48);
  }
  if (*(int *)(param_2 + 0x50) == -1) {
    *(undefined4 *)(param_2 + 0x50) = *(undefined4 *)(param_2 + 0x48);
  }
  if (*(int *)(param_2 + 0x58) == -1) {
    *(undefined4 *)(param_2 + 0x58) = *(undefined4 *)(param_2 + 0x48);
  }
  if (*(int *)(param_2 + 0x54) == -1) {
    *(undefined4 *)(param_2 + 0x54) = *(undefined4 *)(param_2 + 0x48);
  }
  *(int *)(param_2 + 8) = (*(int *)(param_1 + 0x98) - *(int *)(param_1 + 0x94)) / 0x68;
  if (*(int *)(param_1 + 0x98) != *(int *)(param_1 + 0x9c)) {
    FUN_00577050();
    *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x98) + 0x68;
    *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
    return;
  }
  FUN_00575e10(*(int *)(param_1 + 0x98),param_2);
  *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
  return;
}

