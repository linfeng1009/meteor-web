/* Original Meteor.exe static export @ 004ce1a0; original sample not executed. */
/* XREF 005aa758 DATA */

undefined4 __fastcall FUN_004ce1a0(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x130))();
  if (iVar1 == 1) {
    (**(code **)(*param_1 + 0x48))(0x20,0x3f800000,0,0xbf800000);
    return 1;
  }
  return 0;
}

