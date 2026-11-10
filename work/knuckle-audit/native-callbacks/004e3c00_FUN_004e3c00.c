/* Original Meteor.exe static export @ 004e3c00; original sample not executed. */
/* XREF 005ab010 DATA */

undefined4 FUN_004e3c00(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    iVar1 = (**(code **)(*param_1 + 0x138))();
    if (iVar1 != 0) {
      return 400;
    }
    break;
  case 0xa4:
    return 0x1fd;
  case 0xa7:
    return 0x1fe;
  case 0xaa:
    return 0x1ff;
  case 0xad:
    param_2 = 0x200;
  }
  return param_2;
}

