/* Original Meteor.exe static export @ 004e2a40; original sample not executed. */
/* XREF 005aaf28 DATA */

void __thiscall FUN_004e2a40(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = (**(code **)(*param_2 + 0x94))();
  if (iVar1 != 0) {
    iVar3 = *param_1;
    uVar2 = FUN_0055c4e0();
    iVar3 = (**(code **)(iVar3 + 0x74))(uVar2);
    if (iVar3 != 0) {
      (**(code **)(*param_1 + 0x78))(iVar1,*(undefined4 *)(iVar1 + 0x8b4));
      FUN_004dd0a0(param_2);
      return;
    }
    (**(code **)(*param_1 + 0x78))(iVar1,0,*(undefined4 *)(iVar1 + 0x8b8));
  }
  FUN_004dd0a0(param_2);
  return;
}

