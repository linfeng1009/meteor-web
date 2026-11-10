/* Original Meteor.exe static export @ 004ce820; original sample not executed. */
/* XREF 005aa6e4 DATA */

void __thiscall FUN_004ce820(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  if ((param_2 != (undefined4 *)0x0) && (iVar1 = *(int *)(param_1 + 0x10), iVar1 != 0)) {
    *param_2 = *(undefined4 *)(iVar1 + 0x1d0);
    param_2[1] = *(undefined4 *)(iVar1 + 0x1d4);
    param_2[2] = *(undefined4 *)(iVar1 + 0x1d8);
  }
  return;
}

