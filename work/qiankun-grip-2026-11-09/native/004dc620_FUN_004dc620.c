/* Original Meteor.exe static export @ 004dc620; original sample not executed. */
/* XREF 005aaa38 DATA */

void __fastcall FUN_004dc620(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = param_1[0x228];
  if (iVar3 != 0) {
    iVar1 = *param_1;
    uVar2 = FUN_005569b0(s_d_wpnR_005c92cc);
    (**(code **)(iVar1 + 0x18))(uVar2,iVar3);
    param_1[0x228] = 0;
  }
  return;
}

