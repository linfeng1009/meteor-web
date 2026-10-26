/* Meteor.exe original x86 @ 004f2ad0; function boundary recovered from direct vtable/code reference */
/* Caller: 005aa108 */
/* Caller: 005ab590 */
/* Caller: 005ab9d0 */
/* Caller: 005ab350 */

undefined4 __thiscall FUN_004f2ad0(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00487830();
  if (*(int *)(iVar1 + 0x2278) != 0) {
    return 1;
  }
  uVar2 = (**(code **)(*param_1 + 0x170))(param_2);
  return uVar2;
}

