/* Original Meteor.exe static export @ 004cc0a0; original sample not executed. */
/* XREF 005aa814 DATA */

undefined4 __fastcall FUN_004cc0a0(int *param_1)

{
  int *piVar1;
  
  if (param_1[4] == 0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = (int *)(param_1[4] + -0x65c);
  }
  (**(code **)(*piVar1 + 0x40))();
  (**(code **)(*param_1 + 0x74))(0x75,0,0,0xbf800000);
  (**(code **)(*param_1 + 300))(7);
  return 0;
}

