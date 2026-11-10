/* Original Meteor.exe static export @ 00529960; original sample not executed. */
/* XREF 005063a3 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00529960(int param_1,float param_2)

{
  int iVar1;
  
  iVar1 = FUN_00525980();
  FUN_00525610(iVar1);
  if (param_1 != 0x100a) {
    FUN_005255b0(0xa004);
    FUN_00525620(iVar1);
    return;
  }
  if (_DAT_005a83e4 <= param_2) {
    *(float *)(iVar1 + 0x30) = param_2;
    *(uint *)(iVar1 + 0x34) = *(uint *)(iVar1 + 0x34) | 1;
    FUN_005260b0(iVar1,2,0);
    FUN_00525620(iVar1);
    return;
  }
  FUN_005255b0(0xa003);
  FUN_00525620(iVar1);
  return;
}

