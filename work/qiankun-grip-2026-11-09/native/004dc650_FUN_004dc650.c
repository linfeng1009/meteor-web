/* Original Meteor.exe static export @ 004dc650; original sample not executed. */
/* XREF 005aaa3c DATA */

int __fastcall FUN_004dc650(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1[0x228] != 0) {
    return 0;
  }
  uVar1 = FUN_005569b0(s_d_wpnR_005c92cc);
  iVar2 = FUN_005598c0(uVar1);
  param_1[0x228] = iVar2;
  if (iVar2 != 0) {
    iVar2 = *param_1;
    uVar1 = FUN_005569b0(s_d_wpnR_005c92cc);
    (**(code **)(iVar2 + 0x1c))(uVar1);
  }
  return param_1[0x228];
}

