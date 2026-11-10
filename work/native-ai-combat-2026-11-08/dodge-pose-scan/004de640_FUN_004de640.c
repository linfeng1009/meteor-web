/* Original Meteor.exe read-only export. Sample not executed. */

undefined4 FUN_004de640(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    iVar1 = (**(code **)(*param_1 + 0x138))();
    if (iVar1 != 0) {
      return 8;
    }
    break;
  case 0xa4:
    return 0xa5;
  case 0xa7:
    return 0xa8;
  case 0xaa:
    return 0xab;
  case 0xad:
    param_2 = 0xae;
  }
  return param_2;
}

