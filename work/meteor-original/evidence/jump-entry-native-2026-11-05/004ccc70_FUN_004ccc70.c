/* Original Meteor.exe static export @ 004ccc70; original sample not executed. */
/* XREF 005aa72c DATA */

undefined4 __fastcall FUN_004ccc70(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x134))();
  if (iVar1 == 0xa1) {
    return 0x9d;
  }
  if (iVar1 != 0xa2) {
    if (iVar1 == 0xa3) {
      return 0xa0;
    }
    return 0x97;
  }
  return 0x9f;
}

