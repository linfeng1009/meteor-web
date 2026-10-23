/* Meteor.exe original x86 @ 004d48f0 */
/* Caller: 004d37d5 */
/* Caller: 004d380c */

undefined4 * FUN_004d48f0(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_005a1dba;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uStack_7 = 0;
  puVar3 = param_3;
  for (iVar2 = param_1; local_8 = 0, iVar2 != param_2; iVar2 = iVar2 + 0x48) {
    if (puVar3 != (undefined4 *)0x0) {
      FUN_005005b0((int)&param_3 + 3);
      local_8 = 2;
      FUN_00402ac0(*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8));
      local_8 = 3;
      FUN_0047a270(iVar2 + 0x10);
      local_8 = 4;
      FUN_0047a270(iVar2 + 0x1c);
      puVar3[10] = *(undefined4 *)(iVar2 + 0x28);
      puVar3[0xb] = *(undefined4 *)(iVar2 + 0x2c);
      local_8 = 5;
      FUN_0049e380(iVar2 + 0x30);
      *puVar3 = &PTR_FUN_005a94e4;
      param_1 = CONCAT13(param_3._3_1_,(undefined3)param_1);
      local_8 = 6;
      FUN_0049fb80((*(int *)(iVar2 + 0x40) - *(int *)(iVar2 + 0x3c)) / 0x28,(int)&param_1 + 3);
      local_8 = 7;
      uVar1 = FUN_0049fe20(*(undefined4 *)(iVar2 + 0x3c),*(undefined4 *)(iVar2 + 0x40),puVar3[0xf],
                           param_3);
      puVar3[0x10] = uVar1;
      *puVar3 = &PTR_FUN_005a9488;
    }
    puVar3 = puVar3 + 0x12;
  }
  *unaff_FS_OFFSET = local_10;
  return puVar3;
}

