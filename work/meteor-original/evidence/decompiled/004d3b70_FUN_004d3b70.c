/* Meteor.exe original x86 @ 004d3b70 */
/* Caller: 004d2bac */
/* Caller: 004d36d8 */
/* Caller: 004d37f3 */

undefined4 * __thiscall FUN_004d3b70(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar4 = (int)param_2;
  puStack_8 = &LAB_005a1d19;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  puVar1 = (undefined4 *)((int)param_2 + 8);
  puVar2 = (undefined4 *)((int)param_2 + 4);
  local_4 = 0;
  param_2 = param_1 + 1;
  FUN_00402ac0(*puVar2,*puVar1);
  param_2 = param_1 + 4;
  *param_2 = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  local_4._0_1_ = 2;
  local_4._1_3_ = 0;
  FUN_00402ac0(*(undefined4 *)(iVar4 + 0x10),*(undefined4 *)(iVar4 + 0x14));
  local_4._0_1_ = 3;
  FUN_005005b0(&param_2);
  local_4._0_1_ = 4;
  FUN_00402ac0(*(undefined4 *)(iVar4 + 0x1c),*(undefined4 *)(iVar4 + 0x20));
  param_1[10] = *(undefined4 *)(iVar4 + 0x28);
  local_4 = CONCAT31(local_4._1_3_,5);
  param_1[0xb] = *(undefined4 *)(iVar4 + 0x2c);
  FUN_0049e380(iVar4 + 0x30);
  *param_1 = &PTR_FUN_005a94e4;
  iVar3 = (*(int *)(iVar4 + 0x40) - *(int *)(iVar4 + 0x3c)) / 0x28;
  local_4 = 6;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  if (iVar3 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = FUN_00402bf0(iVar3 * 0x28);
  }
  param_1[0xf] = iVar5;
  param_1[0x10] = iVar5;
  param_1[0x11] = iVar5 + iVar3 * 0x28;
  local_4 = CONCAT31(local_4._1_3_,7);
  uVar6 = FUN_0049fe20(*(undefined4 *)(iVar4 + 0x3c),*(undefined4 *)(iVar4 + 0x40),iVar5,param_2);
  param_1[0x10] = uVar6;
  *param_1 = &PTR_FUN_005a9488;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

