/* Original Meteor.exe static export @ 004cc650; original sample not executed. */
/* XREF 005aa730 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004cc650(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  float unaff_retaddr;
  
  if ((param_1[0x18] != 0) || (param_1[0x19] != 0)) {
    return 0;
  }
  iVar1 = (**(code **)(*param_1 + 0x134))();
  iVar2 = (**(code **)(*param_1 + 0x90))(0);
  if ((iVar1 != iVar2) &&
     ((iVar2 = (**(code **)(*param_1 + 0x90))(0x8e), iVar1 != iVar2 &&
      (iVar2 = (**(code **)(*param_1 + 0x90))(0x8d), iVar1 != iVar2)))) {
    return 0;
  }
  FUN_00549a90(0,0);
  if (unaff_retaddr <= _DAT_005a83f4) {
    if (unaff_retaddr < _DAT_005a8430) {
      iVar1 = *param_1;
      uVar3 = (**(code **)(*(int *)param_1[0xd2] + 0x28))(param_1,0x8e);
      (**(code **)(iVar1 + 0x70))(uVar3);
    }
    return 1;
  }
  iVar1 = *param_1;
  uVar3 = (**(code **)(*(int *)param_1[0xd2] + 0x28))(param_1,0x8d);
  (**(code **)(iVar1 + 0x70))(uVar3);
  return 1;
}

