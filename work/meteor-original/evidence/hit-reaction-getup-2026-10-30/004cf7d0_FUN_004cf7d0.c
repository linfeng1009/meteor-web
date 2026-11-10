/* Original Meteor.exe static export @ 004cf7d0; original sample not executed. */
/* XREF 005aa714 DATA */

void __fastcall FUN_004cf7d0(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  (**(code **)(*param_1 + 0x94))();
  iVar1 = FUN_0055c4e0();
  if ((((iVar1 != 0x98) && (iVar1 != 0x9a)) && (iVar1 != 0x9c)) &&
     ((iVar1 != 0x9e && (iVar1 != 0xb4)))) {
    uVar2 = 0x98;
    if (iVar1 == 0x99) {
      uVar2 = 0x9a;
    }
    else {
      if (iVar1 == 0x9b) {
        (**(code **)(*param_1 + 0x74))(0x9c,1,1,0xbf800000);
        return;
      }
      if (iVar1 == 0x9d) {
        (**(code **)(*param_1 + 0x74))(0x9e,1,1,0xbf800000);
        return;
      }
    }
    (**(code **)(*param_1 + 0x74))(uVar2,1,1,0xbf800000);
  }
  return;
}

