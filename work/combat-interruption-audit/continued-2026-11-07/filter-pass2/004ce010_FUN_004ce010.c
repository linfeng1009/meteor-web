/* Original Meteor.exe static export @ 004ce010; original sample not executed. */
/* XREF 005aa784 DATA */

undefined4 __fastcall FUN_004ce010(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_0055c300();
  if (iVar1 == 4) {
    (**(code **)(*param_1 + 0xc))(0x1e,0,0);
    (**(code **)(*param_1 + 300))(1);
    return 0;
  }
  return 1;
}

