/* Meteor.exe original x86 @ 004ef7f0 */
/* Caller: 004bc164 */
/* Caller: 005ab520 */
/* Caller: 005ab960 */
/* Caller: 005ab2e0 */

undefined4 __fastcall FUN_004ef7f0(int *param_1)

{
  int iVar1;
  undefined1 local_99;
  undefined1 local_98;
  undefined1 local_97;
  undefined1 local_96;
  undefined1 local_95;
  int local_94;
  int local_90;
  undefined **local_8c [10];
  int local_64;
  undefined4 local_60;
  int local_5c;
  int local_50;
  int iStack_48;
  undefined1 auStack_44 [12];
  undefined1 auStack_38 [8];
  undefined4 uStack_30;
  int iStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  void *pvStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a35ed;
  local_c = ExceptionList;
  local_90 = param_1[0x95];
  ExceptionList = &local_c;
  FUN_00487830();
  FUN_0049d3c0(&local_94,&local_90);
  iVar1 = FUN_00487830();
  if (local_94 != *(int *)(iVar1 + 0x22ec)) {
    FUN_004024a0(&local_98);
    local_4 = 0;
    FUN_004024a0(&local_96);
    local_4._0_1_ = 1;
    FUN_004024a0(&local_99);
    local_4 = CONCAT31(local_4._1_3_,2);
    FUN_005005b0(&local_97);
    local_8c[0] = &PTR_FUN_005a94e4;
    local_60 = 0;
    local_64 = 0;
    local_4 = 3;
    FUN_005005b0(&local_95);
    local_8c[0] = &PTR_FUN_005a9488;
    local_4 = 4;
    iVar1 = (**(code **)(*(int *)(local_94 + 0x88) + 0x18))(local_8c);
    if (iVar1 != 0) {
      iStack_2c = local_64;
      uStack_28 = local_60;
      (**(code **)(*param_1 + 0x5c))(auStack_38,auStack_44,0);
      uStack_30 = __ftol();
      iStack_2c = __ftol();
      uStack_28 = __ftol();
      uStack_24 = __ftol();
      pvStack_20 = (void *)__ftol();
      uStack_1c = __ftol();
      FUN_0054a6c0(0x13,auStack_38,0x20,1);
      (**(code **)(*param_1 + 0xe0))(auStack_38,0x20);
      iVar1 = (local_5c - local_64) / 0x28;
      uStack_18 = 5;
      if (iVar1 != 0) {
        FUN_00402e90(local_64,iVar1 * 0x28);
      }
      uStack_18 = 8;
      FUN_00575570();
      uStack_18._0_1_ = 7;
      FUN_004026e0();
      uStack_18 = CONCAT31(uStack_18._1_3_,6);
      FUN_004026e0();
      uStack_18 = 0xffffffff;
      FUN_004026e0();
      ExceptionList = pvStack_20;
      return 1;
    }
    iVar1 = (iStack_48 - local_50) / 0x28;
    local_4 = 9;
    if (iVar1 != 0) {
      FUN_00402e90(local_50,iVar1 * 0x28);
    }
    local_8c[0] = &PTR_FUN_005a94e4;
    local_4 = 0xc;
    FUN_00575570();
    local_4._0_1_ = 0xb;
    FUN_004026e0();
    local_4 = CONCAT31(local_4._1_3_,10);
    FUN_004026e0();
    local_4 = 0xffffffff;
    FUN_004026e0();
  }
  ExceptionList = local_c;
  return 0;
}

