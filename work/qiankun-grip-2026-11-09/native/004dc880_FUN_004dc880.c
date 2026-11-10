/* Original Meteor.exe static export @ 004dc880; original sample not executed. */
/* XREF 005aaa5c DATA */

undefined4 __fastcall FUN_004dc880(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x820) == 0) {
    uVar1 = FUN_005569b0(s_d_wpnR_005c92cc);
    uVar1 = FUN_005598c0(uVar1);
    *(undefined4 *)(param_1 + 0x820) = uVar1;
  }
  if (*(int *)(param_1 + 0x81c) == 0) {
    uVar1 = FUN_005569b0(s_d_wpnL_005c93b8);
    uVar1 = FUN_005598c0(uVar1);
    *(undefined4 *)(param_1 + 0x81c) = uVar1;
  }
  return 1;
}

