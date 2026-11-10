/* Original Meteor.exe static export @ 004e2770; original sample not executed. */
/* XREF 005aaef4 DATA */

void __thiscall FUN_004e2770(int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_2 + 0x1d8))();
  if (iVar1 == 0) {
    FUN_0047a270(param_3);
    (**(code **)(*(int *)(param_1 + 4) + 4))();
  }
  else {
    if (iVar1 == 1) {
      FUN_0047a270(param_3);
      (**(code **)(*(int *)(param_1 + 0x40) + 4))();
      return;
    }
    if (iVar1 == 2) {
      FUN_0047a270(param_3);
      (**(code **)(*(int *)(param_1 + 0x50) + 4))();
      return;
    }
  }
  return;
}

