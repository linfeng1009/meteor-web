/* Original Meteor.exe read-only export. Sample not executed. */

undefined4 FUN_004ddef0(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    iVar1 = (**(code **)(*param_1 + 0x138))();
    if (iVar1 != 0) {
      return 7;
    }
    break;
  case 0xa4:
    return 0xa6;
  case 0xa7:
    return 0xa9;
  case 0xaa:
    return 0xac;
  case 0xad:
    param_2 = 0xaf;
  }
  return param_2;
}

