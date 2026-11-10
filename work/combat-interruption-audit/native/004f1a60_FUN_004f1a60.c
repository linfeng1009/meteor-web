/* Original Meteor.exe static export @ 004f1a60; original sample not executed. */
/* XREF 005aa10c DATA */
/* XREF 005ab594 DATA */
/* XREF 005ab9d4 DATA */
/* XREF 005ab354 DATA */

void __fastcall FUN_004f1a60(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)FUN_00487830();
  iVar2 = (**(code **)(*piVar1 + 0x14c))(*(undefined4 *)(param_1 + 0x254));
  piVar1 = (int *)FUN_00487830();
  if (iVar2 != 0) {
    (**(code **)(*piVar1 + 0x1ec))(param_1,*(undefined4 *)(iVar2 + 0x1f0));
    return;
  }
  (**(code **)(*piVar1 + 0x1ec))(param_1,0,0xffffffff);
  return;
}

