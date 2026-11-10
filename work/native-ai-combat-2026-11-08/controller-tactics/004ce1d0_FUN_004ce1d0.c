/* Original Meteor.exe static export @ 004ce1d0; original sample not executed. */
/* XREF 005aa754 DATA */

undefined4 __thiscall FUN_004ce1d0(int *param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    param_1[0x20] = 0;
    return 1;
  }
  iVar1 = (**(code **)(*param_1 + 0x184))();
  if (iVar1 == 0) {
    param_1[0x20] = 1;
    return 1;
  }
  return 0;
}

