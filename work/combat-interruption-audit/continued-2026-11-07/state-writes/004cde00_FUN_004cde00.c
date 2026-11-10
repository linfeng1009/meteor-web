/* Original Meteor.exe static export; sample not executed. */
/* XREF 005aa794 DATA */

undefined4 __thiscall FUN_004cde00(int *param_1,double param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0055c300();
  if (iVar1 != 4) {
    uVar2 = (**(code **)(*param_1 + 200))((float)param_2,param_1 + 0x34,0x3f800000);
    return uVar2;
  }
  iVar1 = (**(code **)(*param_1 + 0xc))(0xf,0,0);
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 300))(1);
    return 0;
  }
  iVar1 = (**(code **)(*param_1 + 0xc))(0x15,0,0);
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 300))(9);
  }
  return 0;
}

