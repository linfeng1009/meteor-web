/* Original Meteor.exe static export @ 004d02f0; original sample not executed. */
/* XREF 005aa810 DATA */

undefined4 __fastcall FUN_004d02f0(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(*param_1 + 0x130))();
  if (iVar1 == 4) {
    if ((int *)param_1[0xd2] != (int *)0x0) {
      iVar1 = *(int *)param_1[0xd2];
      (**(code **)(*param_1 + 0x94))();
      uVar2 = FUN_0055c4d0();
      iVar1 = (**(code **)(iVar1 + 0x50))(uVar2);
      if (iVar1 != 0) {
        return 1;
      }
    }
  }
  else if (iVar1 == 5) {
    return 1;
  }
  return 0;
}

