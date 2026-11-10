/* Original Meteor.exe static export @ 004cc730; original sample not executed. */
/* XREF 005aa738 DATA */

undefined4 __thiscall FUN_004cc730(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(**(int **)(param_1 + 0x348) + 0x28))(param_1,param_2);
  if (*(int *)(param_1 + 0x80) != 0) {
    switch(uVar1) {
    case 0:
      return 10;
    case 0x8c:
    case 0x90:
      return 0x91;
    case 0x8d:
      return 0x92;
    case 0x8e:
      uVar1 = 0x93;
      break;
    case 0x8f:
      return 0x94;
    }
  }
  return uVar1;
}

