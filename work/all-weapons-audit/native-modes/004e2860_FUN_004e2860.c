/* Original Meteor.exe static export @ 004e2860; original sample not executed. */
/* XREF 005aaf18 DATA */

undefined4 FUN_004e2860(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    iVar1 = (**(code **)(*param_1 + 0x138))();
    if (iVar1 != 0) {
      iVar1 = (**(code **)(*param_1 + 0x1d8))();
      if (iVar1 == 0) {
        return 0x191;
      }
      if (iVar1 == 1) {
        return 0x192;
      }
      if (iVar1 == 2) {
        return 0x193;
      }
    }
    break;
  case 0xa4:
    return 0x1f9;
  case 0xa7:
    return 0x1fa;
  case 0xaa:
    return 0x1fb;
  case 0xad:
    param_2 = 0x1fc;
  }
  return param_2;
}

