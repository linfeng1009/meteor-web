/* Original Meteor.exe static read-only export; sample not executed. */

int __thiscall FUN_004d61c0(int *param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined ***pppuVar7;
  undefined1 local_69;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_65;
  undefined1 *local_64;
  undefined1 local_60 [4];
  int iStack_5c;
  undefined4 uStack_58;
  undefined **local_54;
  undefined1 local_50 [36];
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int iStack_20;
  int *local_18;
  int *piStack_14;
  int iStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a1f10;
  pvStack_c = ExceptionList;
  local_64 = local_50;
  ExceptionList = &pvStack_c;
  FUN_00402b70(&local_69,8);
  local_4 = 0;
  FUN_00402a70();
  local_4 = 1;
  FUN_004024a0(&local_68);
  local_4._0_1_ = 2;
  FUN_004024a0(&local_67);
  local_4 = CONCAT31(local_4._1_3_,3);
  FUN_005005b0(&local_66);
  local_54 = &PTR_FUN_005a94e4;
  local_28 = 0;
  local_2c = 0;
  local_4 = 4;
  FUN_005005b0(&local_65);
  local_54 = &PTR_FUN_005a9488;
  local_4 = 5;
  local_64 = (undefined1 *)(**(code **)(*param_1 + 0x34))(param_1,3,local_60);
  pppuVar7 = &local_54;
  uVar6 = 3;
  FUN_004d6570(3,param_2,pppuVar7);
  iVar2 = FUN_004d65c0(uVar6,param_2,pppuVar7);
  if (iVar2 != 0) {
    iVar2 = 0;
    if (local_18 != piStack_14) {
      piVar5 = local_18 + 4;
      do {
        if ((((piVar5[-2] == 3) && (*piVar5 == -1)) && ((*(byte *)(piVar5 + -4) & 2) != 0)) &&
           (piVar5[-3] == 0)) {
          if (piVar5[1] == 0) {
            iVar3 = piVar5[2];
          }
          else {
            if (piVar5[1] != 1) goto LAB_004d6301;
            iStack_5c = piVar5[2];
            uStack_58 = 0;
            iVar3 = __ftol();
          }
          iVar2 = iVar2 + iVar3;
        }
LAB_004d6301:
        piVar1 = piVar5 + 6;
        piVar5 = piVar5 + 10;
      } while (piVar1 != piStack_14);
    }
    local_64 = (undefined1 *)((int)local_64 + iVar2);
  }
  iVar2 = (iStack_10 - (int)local_18) / 0x28;
  if (iVar2 != 0) {
    uVar4 = iVar2 * 0x28;
    if (uVar4 < 0x81) {
      FUN_00402330();
      *local_18 = *(int *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = local_18;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(local_18);
    }
  }
  local_54 = &PTR_FUN_005a94e4;
  local_4._0_1_ = 9;
  local_4._1_3_ = 0;
  for (iVar2 = local_24; iVar2 != iStack_20; iVar2 = iVar2 + 0xc) {
    FUN_004d4a40(iVar2);
  }
  local_4._0_1_ = 8;
  FUN_0049b270();
  local_4._0_1_ = 7;
  FUN_00402bd0();
  local_4 = CONCAT31(local_4._1_3_,6);
  FUN_004026e0();
  local_4 = 0xffffffff;
  FUN_004026e0();
  ExceptionList = pvStack_c;
  return (int)local_64;
}

