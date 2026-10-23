/* Meteor.exe original x86 @ 004d4dd0; function boundary recovered from direct vtable/code reference */
/* Caller: 005a94d4 */

undefined4 __thiscall FUN_004d4dd0(int *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *unaff_EDI;
  
  if (param_2 == 2) {
    uVar1 = 1;
  }
  else {
    if (param_2 != 6) {
      return 0;
    }
    uVar1 = 7;
  }
  uVar1 = (**(code **)(*param_1 + 0x34))(uVar1,0);
  (**(code **)(*param_1 + 0x28))(param_2,uVar1);
  if (unaff_EDI != (undefined4 *)0x0) {
    uVar1 = (**(code **)(*param_1 + 0x34))(param_2,0);
    *unaff_EDI = uVar1;
  }
  return 1;
}

