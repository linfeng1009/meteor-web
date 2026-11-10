/* Original Meteor.exe static export @ 004edd27; original sample not executed. */

void __fastcall FUN_004edd27(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int *unaff_ESI;
  void *in_stack_00000078;
  
  (**(code **)(param_2 + 0x48))(0x5a);
  piVar2 = (int *)FUN_00487830();
  iVar1 = *piVar2;
  uVar3 = (**(code **)(*unaff_ESI + 0x4c))(s_RobotHit_005c9a24);
  (**(code **)(iVar1 + 0x204))(uVar3);
  ExceptionList = in_stack_00000078;
  return;
}

