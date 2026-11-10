/* Original Meteor.exe static export @ 0055c310; original sample not executed. */
/* XREF 005aaa0c DATA */
/* XREF 005ae1c4 DATA */

undefined4 __thiscall FUN_0055c310(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_00558d80(param_2);
  if (iVar1 != 0) {
    iVar1 = FUN_0055c4f0(param_2);
    *(int *)(param_1 + 0x63c) = iVar1;
    if (iVar1 != 0) {
      *(int *)(param_1 + 0x5e0) = (int)*(short *)(iVar1 + 2);
      *(int *)(param_1 + 0x638) = *(int *)(param_1 + 0x62c) + *(short *)(iVar1 + 2) * 0xac;
    }
    return 1;
  }
  return 0;
}

