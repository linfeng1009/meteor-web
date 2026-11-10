/* Original Meteor.exe static export @ 004ece9d; original sample not executed. */

void __fastcall FUN_004ece9d(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int *unaff_ESI;
  
  (**(code **)(param_2 + 0x114))(0x62);
  (**(code **)(*unaff_ESI + 0x14c))();
  iVar1 = FUN_005499a0(0);
  if (iVar1 != 0) {
    (**(code **)(*unaff_ESI + 0x88))();
  }
  piVar2 = (int *)(**(code **)(*unaff_ESI + 0x44))();
  iVar1 = (**(code **)(*piVar2 + 0x130))();
  if (iVar1 == 4) {
    (**(code **)(*unaff_ESI + 0x198))(2);
  }
  return;
}

