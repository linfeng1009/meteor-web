/* Original Meteor.exe static export @ 004cdd60; original sample not executed. */
/* XREF 005aa778 DATA */

undefined4 __thiscall FUN_004cdd60(int *param_1,double param_2)

{
  int iVar1;
  
  (**(code **)(*param_1 + 200))((float)param_2,param_1 + 0x34,param_1[0xdf]);
  if (param_1[0xdd] != 0) {
    (**(code **)(*param_1 + 0xc))(0x2d,0,0);
  }
  iVar1 = FUN_0055c4e0();
  if ((iVar1 < 0x70) || (0x71 < iVar1)) {
    iVar1 = FUN_0055c300();
    if (iVar1 == 4) {
      (**(code **)(*param_1 + 300))(1);
    }
  }
  else {
    iVar1 = FUN_0055c300();
    if (iVar1 == 4) {
      (**(code **)(*param_1 + 300))(0xb);
      return 0;
    }
  }
  return 0;
}

