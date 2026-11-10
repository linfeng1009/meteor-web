/* Original Meteor.exe static export @ 004d01f0; original sample not executed. */
/* XREF 005aa7a0 DATA */

undefined4 __fastcall FUN_004d01f0(int *param_1)

{
  int iVar1;
  
  if ((param_1[4] == 0) || (param_1[4] == 0x65c)) {
    return 0;
  }
  iVar1 = FUN_0055c4e0();
  if (iVar1 == 0x71) {
    (**(code **)(*param_1 + 0x48))(0x78,0x3f800000,0,0xbf800000);
    return 1;
  }
  if (iVar1 != 0x75) {
    (**(code **)(*param_1 + 0x48))(0x77);
    return 1;
  }
  (**(code **)(*param_1 + 0x48))(0x23);
  return 1;
}

