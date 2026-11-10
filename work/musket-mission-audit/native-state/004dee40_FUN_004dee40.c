/* Original Meteor.exe static export @ 004dee40; original sample not executed. */
/* XREF 005aac78 DATA */

undefined4 FUN_004dee40(int param_1,undefined4 param_2)

{
  switch(param_2) {
  case 0:
  case 0x8f:
  case 0x90:
    if (*(int *)(param_1 + 0x36c) != 0) {
      return 0xd5;
    }
    break;
  case 0x8d:
    if (*(int *)(param_1 + 0x36c) != 0) {
      return 0x92;
    }
    break;
  case 0x8e:
    if (*(int *)(param_1 + 0x36c) != 0) {
      param_2 = 0x93;
    }
    break;
  case 0xa4:
    return 0xa4;
  case 0xa7:
    return 0xa7;
  case 0xaa:
    return 0xaa;
  case 0xad:
    return 0xad;
  }
  return param_2;
}

