/* Meteor.exe original x86 @ 004d5fc0; function boundary recovered from direct vtable/code reference */
/* Caller: 005a94d8 */

undefined4 FUN_004d5fc0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined ***pppuVar3;
  undefined **local_9c [15];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined **local_54 [12];
  int *local_24;
  int *local_20;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a1ea9;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_00492000();
  local_54[0] = &PTR_FUN_005a9488;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  pppuVar3 = local_54;
  local_4 = 0;
  FUN_004d6570(param_1,param_2,pppuVar3);
  iVar1 = FUN_004d65c0(param_1,param_2,pppuVar3);
  if (iVar1 != 0) {
    for (; local_24 != local_20; local_24 = local_24 + 3) {
      if (*local_24 == 0x10) {
        if ((local_24 != local_20) && (local_24 != (int *)0x0)) {
          FUN_00492000();
          local_60 = 0;
          local_5c = 0;
          local_58 = 0;
          local_9c[0] = &PTR_FUN_005a9488;
          iVar1 = local_24[1];
          pppuVar3 = local_9c;
          uVar2 = 2;
          local_4._0_1_ = 1;
          FUN_004d6570(2,iVar1,pppuVar3);
          iVar1 = FUN_004d65c0(uVar2,iVar1,pppuVar3);
          if (iVar1 != 0) {
            FUN_004d3cd0(local_9c);
            FUN_004d3e60(&local_60);
            local_4._0_1_ = 2;
            FUN_0049b240();
            local_4 = (uint)local_4._1_3_ << 8;
            FUN_004920f0();
            local_4 = 3;
            FUN_0049b240();
            local_4 = 0xffffffff;
            FUN_004920f0();
            ExceptionList = local_c;
            return 1;
          }
          local_4._0_1_ = 4;
          FUN_0049b240();
          local_4 = (uint)local_4._1_3_ << 8;
          FUN_004920f0();
        }
        break;
      }
    }
  }
  local_4 = 5;
  FUN_0049b240();
  local_4 = 0xffffffff;
  FUN_004920f0();
  ExceptionList = local_c;
  return 0;
}

