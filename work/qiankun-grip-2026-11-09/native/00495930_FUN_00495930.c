/* Original Meteor.exe static export @ 00495930; original sample not executed. */
/* XREF 005a91d0 DATA */

undefined4 __thiscall FUN_00495930(int *param_1,int param_2,void *param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 unaff_EBP;
  int *piVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 uStack_60;
  void *pvStack_5c;
  int **local_58;
  undefined **appuStack_54 [10];
  undefined4 uStack_2c;
  undefined4 uStack_28;
  int *piStack_24;
  int *piStack_20;
  int iStack_1c;
  undefined4 *puStack_18;
  int iStack_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0059eb86;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_58 = (int **)param_1;
  iVar2 = FUN_00493de0(param_2);
  uVar1 = param_3;
  if (iVar2 != 0) {
    param_2 = (**(code **)(*param_1 + 0x138))(param_3);
    if (param_2 == 0) {
      ExceptionList = local_c;
      return 0;
    }
    piVar4 = (int *)(iVar2 + -0x65c);
    iVar2 = FUN_005569b0(s_d_wpnR_005c92cc);
    pvStack_5c = (void *)FUN_005569b0(s_d_wpnL_005c93b8);
    if (-1 < iVar2) {
      param_3 = operator_new(0x1d0);
      uVar6 = 0;
      uStack_4 = 0;
      if (param_3 != (void *)0x0) {
        uVar6 = FUN_005678a0();
      }
      uStack_4 = 0xffffffff;
      FUN_0056b230(uVar6);
      (**(code **)(*piVar4 + 0x54))(iVar2,uVar1,uVar6);
      (**(code **)(*piVar4 + 0x54))(unaff_EBP,0,0);
      FUN_004024a0(&param_2);
      uStack_4 = 1;
      FUN_004024a0(&param_3);
      uStack_4._0_1_ = 2;
      FUN_004024a0((int)&uStack_60 + 1);
      uStack_4 = CONCAT31(uStack_4._1_3_,3);
      FUN_005005b0((int)&uStack_60 + 2);
      appuStack_54[0] = &PTR_FUN_005a94e4;
      uStack_28 = 0;
      uStack_2c = 0;
      uStack_4 = 4;
      FUN_005005b0((int)&uStack_60 + 3);
      appuStack_54[0] = &PTR_FUN_005a9488;
      uStack_4 = 5;
      FUN_004d6570();
      iVar2 = FUN_004d65c0(1,uVar1,appuStack_54);
      piVar5 = piStack_24;
      if (iVar2 != 0) {
        for (; piVar5 != piStack_20; piVar5 = piVar5 + 3) {
          if (*piVar5 == 0xb) {
            if (((piVar5 != piStack_20) && (piVar5 != (int *)0x0)) &&
               ((iVar2 = piVar5[1], iVar2 == 8 || ((iVar2 == 9 || (iVar2 == 10)))))) {
              (**(code **)((int)*local_58 + 0x13c))(uVar1);
              pvStack_5c = operator_new(0x1d0);
              puStack_8._0_1_ = 6;
              if (pvStack_5c == (void *)0x0) {
                uVar6 = 0;
              }
              else {
                uVar6 = FUN_005678a0();
              }
              puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,5);
              FUN_0056b230(uVar6);
              (**(code **)(*piVar4 + 0x54))(uStack_60,uVar1,uVar6);
            }
            break;
          }
        }
      }
      iVar2 = (iStack_10 - (int)puStack_18) / 0x28;
      piVar4 = piStack_20;
      if (iVar2 != 0) {
        uVar3 = iVar2 * 0x28;
        if (uVar3 < 0x81) {
          FUN_00402330();
          *puStack_18 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
          *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puStack_18;
          DAT_005d59e8 = 0;
          piVar4 = piStack_20;
        }
        else {
          FUN_005089fd(puStack_18);
          piVar4 = piStack_20;
        }
      }
      local_58 = &piStack_24;
      appuStack_54[0] = &PTR_FUN_005a94e4;
      uStack_4 = 7;
      for (piVar5 = piStack_24; piVar5 != piVar4; piVar5 = piVar5 + 3) {
        FUN_004d4a40(piVar5);
      }
      uStack_4 = 0xffffffff;
      iVar2 = (iStack_1c - (int)piStack_24) / 0xc;
      if (iVar2 != 0) {
        FUN_00402e90(piStack_24,iVar2 * 0xc);
      }
      FUN_00402bd0();
      FUN_00402bd0();
      FUN_00402bd0();
      ExceptionList = local_c;
      return 0;
    }
  }
  ExceptionList = local_c;
  return 0xffffffff;
}

