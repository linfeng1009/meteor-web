/* Original Meteor.exe static export @ 004cff40; original sample not executed. */
/* XREF 005aa748 DATA */

int __fastcall FUN_004cff40(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined ***pppuVar6;
  undefined1 uStack_64;
  undefined1 uStack_63;
  undefined1 uStack_62;
  undefined1 uStack_61;
  int iStack_60;
  int **ppiStack_5c;
  undefined **appuStack_58 [7];
  int iStack_3c;
  int iStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int *piStack_28;
  int *piStack_24;
  int iStack_20;
  undefined4 *puStack_1c;
  int iStack_14;
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a1a58;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  iVar1 = (**(code **)(*param_1 + 0x130))();
  if ((((iVar1 != 1) && (iVar1 != 0)) && (iVar1 != 3)) && (iVar1 != 6)) {
    if (iVar1 == 0xb) {
      (**(code **)(*param_1 + 0xf8))();
    }
    ExceptionList = pvStack_c;
    return 0;
  }
  iStack_60 = (**(code **)(*(int *)param_1[0xd2] + 0x20))(param_1);
  if (iStack_60 != 0) {
    FUN_004024a0(&stack0xffffff9b);
    puStack_8 = (undefined1 *)0x0;
    FUN_004024a0(&uStack_64);
    puStack_8._0_1_ = 1;
    FUN_004024a0(&uStack_63);
    puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,2);
    FUN_005005b0(&uStack_62);
    appuStack_58[0] = &PTR_FUN_005a94e4;
    uStack_2c = 0;
    uStack_30 = 0;
    puStack_8 = (undefined1 *)0x3;
    FUN_005005b0(&uStack_61);
    appuStack_58[0] = &PTR_FUN_005a9488;
    puStack_8 = (undefined1 *)0x4;
    (**(code **)(*param_1 + 0x94))();
    iVar1 = FUN_0055c300();
    if (iVar1 == 2) {
      if (param_1[0x149] != 0) {
        (**(code **)(*param_1 + 0xc))(0x30,0,0);
      }
      iVar1 = (**(code **)(*param_1 + 0x94))();
      uVar2 = *(undefined4 *)(iVar1 + 0x624);
    }
    else {
      (**(code **)(*param_1 + 0x94))();
      uVar2 = FUN_0055c4e0();
    }
    pppuVar6 = appuStack_58;
    uVar5 = 3;
    FUN_004d6570(3,uVar2,pppuVar6);
    iVar1 = FUN_004d65c0(uVar5,uVar2,pppuVar6);
    piVar4 = piStack_28;
    if (iVar1 != 0) {
      for (; piVar4 != piStack_24; piVar4 = piVar4 + 3) {
        if (*piVar4 == 0x12) {
          if ((piVar4 != piStack_24) && (piVar4 != (int *)0x0)) {
            param_1[0x149] = piVar4[1];
          }
          break;
        }
      }
    }
    (**(code **)(*param_1 + 0xc))(0x35,0,0);
    iVar1 = (iStack_14 - (int)puStack_1c) / 0x28;
    if (iVar1 != 0) {
      uVar3 = iVar1 * 0x28;
      if (uVar3 < 0x81) {
        FUN_00402330();
        *puStack_1c = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puStack_1c;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(puStack_1c);
      }
    }
    appuStack_58[0] = &PTR_FUN_005a94e4;
    ppiStack_5c = &piStack_28;
    puStack_8._0_1_ = 8;
    puStack_8._1_3_ = 0;
    for (piVar4 = piStack_28; piVar4 != piStack_24; piVar4 = piVar4 + 3) {
      FUN_004d4a40(piVar4);
    }
    puStack_8._0_1_ = 7;
    iVar1 = (iStack_20 - (int)piStack_28) / 0xc;
    if (iVar1 != 0) {
      FUN_00402e90(piStack_28,iVar1 * 0xc);
    }
    puStack_8._0_1_ = 6;
    if ((iStack_3c != 0) && (iStack_34 - iStack_3c != 0)) {
      FUN_00402e90(iStack_3c,iStack_34 - iStack_3c);
    }
    puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,5);
    FUN_00402bd0();
    puStack_8 = (undefined1 *)0xffffffff;
    FUN_00402bd0();
  }
  ExceptionList = pvStack_10;
  return iStack_60;
}

