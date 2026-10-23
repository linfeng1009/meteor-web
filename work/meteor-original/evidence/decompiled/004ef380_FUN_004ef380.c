/* Meteor.exe original x86 @ 004ef380 */
/* Caller: 005aa09c */
/* Caller: 005ab524 */
/* Caller: 005ab964 */
/* Caller: 005ab2e4 */

undefined4 __fastcall FUN_004ef380(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined ***pppuVar5;
  uint *puVar6;
  uint local_114;
  int local_110 [3];
  undefined1 auStack_104 [12];
  undefined1 auStack_f8 [12];
  undefined1 auStack_ec [8];
  undefined4 uStack_e4;
  int iStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined1 auStack_cc [8];
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined **ppuStack_b4;
  undefined4 uStack_b0;
  undefined **appuStack_9c [9];
  int iStack_78;
  undefined4 uStack_74;
  int iStack_70;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined **local_54 [12];
  int *local_24;
  int *local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a355f;
  local_c = ExceptionList;
  local_114 = param_1[0x95];
  ExceptionList = &local_c;
  FUN_00487830();
  FUN_0049d3c0(local_110,&local_114);
  iVar2 = FUN_00487830();
  if (local_110[0] == *(int *)(iVar2 + 0x22ec)) {
    ExceptionList = local_c;
    return 0;
  }
  local_114 = 0;
  FUN_0046ef50(**(undefined4 **)(local_110[0] + 200),*(undefined4 **)(local_110[0] + 200),&local_114
              );
  if (local_114 < 2) {
    local_114 = 0;
    FUN_00492000();
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    local_54[0] = &PTR_FUN_005a9488;
    pppuVar5 = local_54;
    local_4 = 0;
    uVar4 = *(undefined4 *)(*(int *)(local_110[0] + 0xc4) + 0x28);
    uVar3 = 1;
    FUN_004d6570(1,uVar4,pppuVar5);
    iVar2 = FUN_004d65c0(uVar3,uVar4,pppuVar5);
    piVar1 = local_24;
    if (iVar2 != 0) {
      for (; piVar1 != local_20; piVar1 = piVar1 + 3) {
        if (*piVar1 == 0xb) {
          if ((piVar1 != local_20) && (piVar1 != (int *)0x0)) {
            iVar2 = piVar1[1];
            puVar6 = &local_114;
            uVar4 = 0;
            FUN_004d6570(iVar2,0,puVar6);
            FUN_004d68f0(iVar2,uVar4,puVar6);
          }
          break;
        }
      }
    }
    (**(code **)(*param_1 + 0xa8))(local_114,1);
    local_4 = 1;
    FUN_0049b240();
    local_4 = 0xffffffff;
    FUN_004920f0();
  }
  else {
    (**(code **)(*param_1 + 0xa4))();
  }
  FUN_00492000();
  uStack_60 = 0;
  uStack_5c = 0;
  uStack_58 = 0;
  appuStack_9c[0] = &PTR_FUN_005a9488;
  local_4 = 2;
  iVar2 = (**(code **)(*(int *)(local_110[0] + 0x88) + 0x18))(appuStack_9c);
  if (iVar2 == 0) {
    uStack_c0 = *(undefined4 *)(*(int *)(local_114 + 0xc4) + 0x28);
    uStack_bc = *(undefined4 *)(*(int *)(local_114 + 0xc4) + 0x2c);
    (**(code **)(*param_1 + 0x5c))(local_110,auStack_ec,0);
    uStack_c4 = __ftol();
    uStack_c0 = __ftol();
    uStack_bc = __ftol();
    uStack_b8 = __ftol();
    ppuStack_b4 = (undefined **)__ftol();
    uStack_b0 = __ftol();
    FUN_0054a6c0(0x13,auStack_cc,0x20,1);
    (**(code **)(*param_1 + 0xe0))(auStack_cc,0x20);
    iVar2 = (iStack_70 - iStack_78) / 0x28;
    uStack_1c = 4;
    if (iVar2 != 0) {
      FUN_00402e90(iStack_78,iVar2 * 0x28);
    }
    ppuStack_b4 = &PTR_FUN_005a94e4;
    uStack_1c = 7;
    FUN_00575570();
    uStack_1c._0_1_ = 6;
    FUN_004026e0();
    uStack_1c = CONCAT31(uStack_1c._1_3_,5);
    FUN_004026e0();
    uStack_1c = 0xffffffff;
    FUN_004026e0();
    ExceptionList = local_24;
    return 1;
  }
  iStack_e0 = iStack_78;
  uStack_dc = uStack_74;
  (**(code **)(*param_1 + 0x5c))(auStack_104,auStack_f8);
  uStack_e4 = __ftol();
  iStack_e0 = __ftol();
  uStack_dc = __ftol();
  uStack_d8 = __ftol();
  uStack_d4 = __ftol();
  uStack_d0 = __ftol();
  FUN_0054a6c0(0x13,auStack_ec,0x20,1);
  (**(code **)(*param_1 + 0xe0))(auStack_ec,0x20);
  uStack_1c = 3;
  FUN_0049b240();
  uStack_1c = 0xffffffff;
  FUN_004920f0();
  ExceptionList = local_24;
  return 1;
}

