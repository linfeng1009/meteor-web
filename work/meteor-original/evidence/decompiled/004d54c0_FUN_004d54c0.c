/* Meteor.exe original x86 @ 004d54c0 */
/* Caller: 005a94a0 */

undefined4 __fastcall FUN_004d54c0(int param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  undefined1 local_5d;
  int local_5c;
  int *local_58;
  undefined **local_54 [12];
  int local_24;
  int local_20;
  int local_18;
  undefined4 local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a1e60;
  local_c = ExceptionList;
  local_58 = (int *)0x0;
  puVar1 = (undefined4 *)(param_1 + 0x40);
  ExceptionList = &local_c;
  FUN_0046ef50(**(undefined4 **)(param_1 + 0x40),*(undefined4 **)(param_1 + 0x40),&local_58,0);
  if (local_58 < (int *)0x2) {
    ExceptionList = local_c;
    return 0;
  }
  iVar3 = *(int *)*puVar1;
  FUN_0049ab40(iVar3 + 8);
  local_58 = &local_18;
  local_4 = 0;
  FUN_0049fb80((*(int *)(iVar3 + 0x48) - *(int *)(iVar3 + 0x44)) / 0x28,&local_5d);
  local_4 = CONCAT31(local_4._1_3_,1);
  local_14 = FUN_0049fe20(*(undefined4 *)(iVar3 + 0x44),*(undefined4 *)(iVar3 + 0x48),local_18,
                          local_58);
  local_54[0] = &PTR_FUN_005a9488;
  local_4 = 2;
  FUN_004d6ab0(&local_58,*(undefined4 *)*puVar1);
  FUN_004db820(&local_5c);
  piVar2 = (int *)FUN_0049e220(local_54);
  *piVar2 = local_5c;
  piVar2[1] = *(int *)(local_5c + 4);
  **(int **)(local_5c + 4) = (int)piVar2;
  *(int **)(local_5c + 4) = piVar2;
  *(int *)(param_1 + 0x3c) = *(int *)*puVar1 + 8;
  local_4 = 3;
  iVar3 = (local_10 - local_18) / 0x28;
  if (iVar3 != 0) {
    FUN_00402e90(local_18,iVar3 * 0x28);
  }
  local_54[0] = &PTR_FUN_005a94e4;
  local_58 = &local_24;
  local_4._0_1_ = 7;
  local_4._1_3_ = 0;
  for (iVar3 = local_24; iVar3 != local_20; iVar3 = iVar3 + 0xc) {
    FUN_004d4a40(iVar3);
  }
  local_4._0_1_ = 6;
  FUN_0049b270();
  local_4._0_1_ = 5;
  FUN_004026e0();
  local_4 = CONCAT31(local_4._1_3_,4);
  FUN_004026e0();
  local_4 = 0xffffffff;
  FUN_004026e0();
  ExceptionList = local_c;
  return 1;
}

