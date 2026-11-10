/* Original Meteor.exe static export @ 004afcf0; original sample not executed. */
/* XREF 005a9cf4 DATA */
/* XREF 005aa464 DATA */
/* XREF 005aa5bc DATA */

undefined4 __thiscall FUN_004afcf0(int *param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined ***pppuVar6;
  undefined1 uStack_69;
  undefined1 uStack_68;
  undefined1 uStack_67;
  undefined1 uStack_66;
  undefined1 uStack_65;
  undefined **ppuStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined **appuStack_54 [8];
  int iStack_34;
  int iStack_30;
  undefined4 uStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  void *pvStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  int *piStack_4;
  
  piStack_4 = (int *)0xffffffff;
  puStack_8 = &LAB_005a03a8;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_0049d3c0(&ppuStack_64,&param_2);
  if (ppuStack_64 != (undefined **)param_1[0xea]) {
    FUN_004024a0(&uStack_69);
    piStack_4 = (int *)0x0;
    FUN_004024a0(&uStack_68);
    piStack_4._0_1_ = 1;
    FUN_004024a0(&uStack_67);
    piStack_4 = (int *)CONCAT31(piStack_4._1_3_,2);
    FUN_005005b0(&uStack_66);
    appuStack_54[0] = &PTR_FUN_005a94e4;
    iStack_28 = 0;
    uStack_2c = 0;
    piStack_4 = (int *)0x3;
    FUN_005005b0(&uStack_65);
    uVar2 = param_4;
    uVar1 = param_3;
    appuStack_54[0] = &PTR_FUN_005a9488;
    pppuVar6 = appuStack_54;
    piStack_4 = (int *)0x4;
    uVar4 = param_3;
    uVar5 = param_4;
    FUN_004d6570(param_3,param_4,pppuVar6);
    iVar3 = FUN_004d65c0(uVar4,uVar5,pppuVar6);
    if ((iVar3 != 0) &&
       (iVar3 = (**(code **)(ppuStack_64[0x22] + 0x24))(appuStack_54,0), iVar3 != 0)) {
      uStack_60 = param_2;
      uStack_5c = uVar1;
      uStack_58 = uVar2;
      (**(code **)(*param_1 + 0x40))(0x3d,&uStack_60,0xc,1);
      iVar3 = (iStack_20 - iStack_28) / 0x28;
      uStack_14 = 5;
      if (iVar3 != 0) {
        FUN_00402e90(iStack_28,iVar3 * 0x28);
      }
      ppuStack_64 = &PTR_FUN_005a94e4;
      piStack_4 = &iStack_34;
      uStack_14._0_1_ = 9;
      uStack_14._1_3_ = 0;
      for (iVar3 = iStack_34; iVar3 != iStack_30; iVar3 = iVar3 + 0xc) {
        FUN_004d4a40(iVar3);
      }
      uStack_14._0_1_ = 8;
      FUN_0049b270();
      uStack_14._0_1_ = 7;
      FUN_00402bd0();
      uStack_14 = CONCAT31(uStack_14._1_3_,6);
      FUN_004026e0();
      uStack_14 = 0xffffffff;
      FUN_004026e0();
      ExceptionList = pvStack_1c;
      return 1;
    }
    iVar3 = (iStack_10 - iStack_18) / 0x28;
    piStack_4 = (int *)0xa;
    if (iVar3 != 0) {
      FUN_00402e90(iStack_18,iVar3 * 0x28);
    }
    appuStack_54[0] = &PTR_FUN_005a94e4;
    param_4 = &iStack_24;
    piStack_4._0_1_ = 0xe;
    piStack_4._1_3_ = 0;
    for (iVar3 = iStack_24; iVar3 != iStack_20; iVar3 = iVar3 + 0xc) {
      FUN_004d4a40(iVar3);
    }
    piStack_4._0_1_ = 0xd;
    FUN_0049b270();
    piStack_4._0_1_ = 0xc;
    FUN_004026e0();
    piStack_4 = (int *)CONCAT31(piStack_4._1_3_,0xb);
    FUN_004026e0();
    piStack_4 = (int *)0xffffffff;
    FUN_004026e0();
  }
  ExceptionList = pvStack_c;
  return 0;
}

