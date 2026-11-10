/* Original Meteor.exe read-only export. Sample not executed. */

undefined4 FUN_004df600(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    iVar1 = (**(code **)(*param_1 + 0x138))();
    if (iVar1 != 0) {
      return 1;
    }
    break;
  case 0xa4:
    return 0xa4;
  case 0xa7:
    return 0xa7;
  case 0xaa:
    return 0xaa;
  case 0xad:
    param_2 = 0xad;
  }
  return param_2;
}

