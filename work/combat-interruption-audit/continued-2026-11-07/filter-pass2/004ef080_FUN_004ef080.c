/* Original Meteor.exe static export @ 004ef080; original sample not executed. */
/* XREF 004bc184 UNCONDITIONAL_CALL */
/* XREF 005ab528 DATA */
/* XREF 005ab968 DATA */
/* XREF 005ab2e8 DATA */

undefined4 __fastcall FUN_004ef080(int *param_1)

{
  int iVar1;
  int *piVar2;
  undefined1 local_99;
  undefined1 local_98;
  undefined1 local_97;
  undefined1 local_96;
  undefined1 local_95;
  int local_94;
  int local_90;
  undefined1 auStack_8c [12];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  int iStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined **ppuStack_68;
  undefined4 uStack_64;
  undefined **local_54 [10];
  int local_2c;
  undefined4 local_28;
  int local_24;
  void *pvStack_20;
  int local_18;
  int iStack_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a3500;
  local_c = ExceptionList;
  local_94 = param_1[0x95];
  ExceptionList = &local_c;
  FUN_00487830();
  FUN_0049d3c0(&local_90,&local_94);
  iVar1 = FUN_00487830();
  if (local_90 != *(int *)(iVar1 + 0x22ec)) {
    FUN_004024a0(&local_98);
    local_4 = 0;
    FUN_004024a0(&local_96);
    local_4._0_1_ = 1;
    FUN_004024a0(&local_99);
    local_4 = CONCAT31(local_4._1_3_,2);
    FUN_005005b0(&local_97);
    local_54[0] = &PTR_FUN_005a94e4;
    local_28 = 0;
    local_2c = 0;
    local_4 = 3;
    FUN_005005b0(&local_95);
    local_54[0] = &PTR_FUN_005a9488;
    local_4 = 4;
    piVar2 = (int *)FUN_00487830();
    iVar1 = (**(code **)(*piVar2 + 0x150))(param_1[0x95],local_54);
    if (iVar1 != 0) {
      uStack_70 = local_28;
      iStack_74 = local_2c;
      (**(code **)(*param_1 + 0x5c))(auStack_80,auStack_8c,0);
      uStack_78 = __ftol();
      iStack_74 = __ftol();
      uStack_70 = __ftol();
      uStack_6c = __ftol();
      ppuStack_68 = (undefined **)__ftol();
      uStack_64 = __ftol();
      FUN_0054a6c0(0x13,auStack_80,0x20,1);
      FUN_0054a6c0(0x1c,0,0,1);
      (**(code **)(*param_1 + 0xe0))(auStack_80,0x20);
      iVar1 = (local_24 - local_2c) / 0x28;
      local_18 = 5;
      if (iVar1 != 0) {
        FUN_00402e90(local_2c,iVar1 * 0x28);
      }
      ppuStack_68 = &PTR_FUN_005a94e4;
      local_18 = 8;
      FUN_00575570();
      local_18._0_1_ = 7;
      FUN_004026e0();
      local_18 = CONCAT31(local_18._1_3_,6);
      FUN_004026e0();
      local_18 = 0xffffffff;
      FUN_004026e0();
      ExceptionList = pvStack_20;
      return 1;
    }
    iVar1 = (iStack_10 - local_18) / 0x28;
    local_4 = 9;
    if (iVar1 != 0) {
      FUN_00402e90(local_18,iVar1 * 0x28);
    }
    local_4 = 0xffffffff;
    FUN_004920f0();
  }
  ExceptionList = local_c;
  return 0;
}

