/* Original Meteor.exe static export @ 0053e160; original sample not executed. */
/* XREF 0053e116 DATA */

void FUN_0053e160(int *param_1)

{
  int *unaff_retaddr;
  undefined1 auStack_cc [188];
  undefined4 uStack_10;
  int *piStack_c;
  int *piStack_8;
  
  piStack_8 = param_1;
  piStack_c = (int *)0x53e16b;
  (**(code **)(*param_1 + 8))();
  piStack_c = param_1;
  uStack_10 = 0x53e171;
  FUN_0053e300();
  piStack_8 = (int *)0x1;
  piStack_c = (int *)0x53e17b;
  FUN_0050c728();
  (**(code **)(*unaff_retaddr + 0xc))(unaff_retaddr,auStack_cc);
  FUN_00509f22(&DAT_005ca980,&DAT_005d1138,auStack_cc);
  return;
}

