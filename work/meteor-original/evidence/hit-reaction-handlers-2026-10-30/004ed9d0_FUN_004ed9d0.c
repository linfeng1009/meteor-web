/* Original Meteor.exe static export @ 004ed9d0; original sample not executed. */
/* XREF 005ab4c0 DATA */
/* XREF 004ecd68 UNCONDITIONAL_JUMP */

int * __thiscall FUN_004ed9d0(int *param_1,uint param_2,int *param_3,int param_4)

{
  short sVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int unaff_EBX;
  int unaff_ESI;
  int *piVar8;
  int iVar9;
  undefined ***pppuVar10;
  undefined1 uStack_88;
  undefined1 uStack_87;
  undefined1 uStack_86;
  undefined1 uStack_85;
  int iStack_84;
  int **ppiStack_80;
  int iStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [12];
  undefined **ppuStack_54;
  int *apiStack_50 [9];
  undefined4 uStack_2c;
  undefined4 uStack_28;
  int *piStack_24;
  int *piStack_20;
  undefined4 *puStack_18;
  undefined4 uStack_14;
  int iStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a3390;
  pvStack_c = ExceptionList;
  piVar4 = (int *)((param_2 & 0xffff) - 0xb);
  switch(param_2 & 0xffff) {
  case 0xb:
    ExceptionList = &pvStack_c;
    piVar4 = (int *)(**(code **)(*param_1 + 0x4c))();
    if ((int *)param_3[4] == piVar4) {
      piVar4 = (int *)(**(code **)(*param_1 + 0xf4))(param_3);
    }
    break;
  case 0xe:
    ExceptionList = &pvStack_c;
    piVar4 = (int *)(**(code **)(*param_1 + 0x4c))();
    if ((int *)param_3[4] == piVar4) {
      piVar4 = (int *)(**(code **)(*param_1 + 0xf8))(param_3);
    }
    break;
  case 0x17:
    iStack_84 = param_3[1];
    ExceptionList = &pvStack_c;
    if (*param_3 == param_1[0x95]) {
      ExceptionList = &pvStack_c;
      FUN_00487830();
      FUN_0049d3c0(&ppiStack_80,&iStack_84);
      puVar2 = (undefined1 *)param_1[0x92];
      if (puVar2 != (undefined1 *)param_1[0x93]) {
        if (puVar2 != (undefined1 *)0x0) {
          *puVar2 = *(undefined1 *)((int)ppiStack_80 + 0x229);
        }
        param_1[0x92] = param_1[0x92] + 1;
        piVar4 = (int *)(**(code **)(*param_1 + 0xd4))(iStack_84);
        ExceptionList = pvStack_c;
        return piVar4;
      }
      FUN_004bcaa0(puVar2,(undefined1 *)((int)ppiStack_80 + 0x229));
    }
    piVar4 = (int *)(**(code **)(*param_1 + 0xd4))(iStack_84);
    break;
  case 0x18:
    ExceptionList = &pvStack_c;
    (**(code **)(*param_1 + 0xdc))();
    (**(code **)(*param_1 + 0xbc))();
    piVar4 = (int *)(**(code **)(*param_1 + 0xc0))();
    break;
  case 0x19:
    iStack_7c = param_1[0x95];
    ExceptionList = &pvStack_c;
    FUN_00487830();
    FUN_0049d3c0(&iStack_84,&iStack_7c);
    iVar6 = FUN_00487830();
    piVar4 = (int *)(iVar6 + 0x22ec);
    if (iStack_84 != *(int *)(iVar6 + 0x22ec)) {
      iVar6 = param_3[1];
      iVar9 = *param_3;
      sVar1 = *(short *)((int)param_3 + 2);
      (**(code **)(*(int *)(iStack_84 + 0x88) + 0x28))(6,(int)(short)iVar6);
      (**(code **)(*(int *)(unaff_EBX + 0x88) + 0x28))(2,(int)(short)iVar9);
      piVar4 = (int *)(**(code **)(*(int *)(unaff_ESI + 0x88) + 0x28))(1,(int)sVar1);
      if ((uint)(int)(short)iVar6 < 100) {
        param_1[0xc2] = 0;
      }
      else {
        param_1[0xc2] = 1;
      }
    }
    break;
  case 0x1b:
    ExceptionList = &pvStack_c;
    piVar4 = (int *)(**(code **)(*param_1 + 0x104))();
    break;
  case 0x1c:
  case 0x3c:
    ExceptionList = &pvStack_c;
    if (0 < param_4) {
      ExceptionList = &pvStack_c;
      (**(code **)(*param_1 + 0x130))(*param_3,param_3[1]);
    }
    piVar4 = (int *)(**(code **)(*param_1 + 0x44))();
    piVar4 = (int *)(**(code **)(*piVar4 + 300))(1);
    break;
  case 0x20:
    iVar6 = param_3[2];
    iVar9 = param_3[3];
    piVar4 = (int *)param_1[0x95];
    if ((int *)*param_3 == piVar4) {
      ExceptionList = &pvStack_c;
      (**(code **)(*param_1 + 0x134))();
      FUN_00492000();
      ppuStack_54 = &PTR_FUN_005a9488;
      puStack_18 = (undefined4 *)0x0;
      uStack_14 = 0;
      iStack_10 = 0;
      pppuVar10 = &ppuStack_54;
      uStack_4 = 0;
      FUN_004d6570(iVar6,iVar9,pppuVar10);
      iVar6 = FUN_004d65c0(iVar6,iVar9,pppuVar10);
      if (iVar6 != 0) {
        for (; piStack_24 != piStack_20; piStack_24 = piStack_24 + 3) {
          if (*piStack_24 == 0x11) {
            if ((piStack_24 != piStack_20) && (piStack_24 != (int *)0x0)) {
              (**(code **)(*param_1 + 400))(piStack_24[1]);
            }
            break;
          }
        }
      }
      uStack_4 = 1;
      FUN_0049b240();
      uStack_4 = 0xffffffff;
      piVar4 = (int *)FUN_004920f0();
    }
    break;
  case 0x28:
    ExceptionList = &pvStack_c;
    piVar4 = (int *)(**(code **)(*param_1 + 0x108))();
    break;
  case 0x29:
    ExceptionList = &pvStack_c;
    piVar4 = (int *)(**(code **)(*param_1 + 0x44))();
    iVar6 = *param_3;
    (**(code **)(*piVar4 + 0x94))(iVar6);
    FUN_005598f0(iVar6);
    iVar6 = (**(code **)(*param_1 + 0x134))();
    *(int *)(iVar6 + 0x1f0) = *param_3;
    iVar6 = FUN_00487830();
    piVar4 = (int *)(**(code **)(*param_1 + 0x80))(*(undefined4 *)(*(int *)(iVar6 + 0x2448) + 0x30))
    ;
    break;
  case 0x2d:
    piVar4 = param_3;
    if (param_1[0x95] == *param_3) {
      iVar6 = param_3[1];
      iVar9 = param_3[2];
      ppiStack_80 = apiStack_50;
      ExceptionList = &pvStack_c;
      FUN_00402b70(&uStack_88,8);
      uStack_4 = 2;
      FUN_00402a70();
      uStack_4 = 3;
      FUN_004024a0(&uStack_87);
      uStack_4._0_1_ = 4;
      FUN_004024a0(&uStack_86);
      uStack_4 = CONCAT31(uStack_4._1_3_,5);
      FUN_005005b0(&uStack_85);
      ppuStack_54 = &PTR_FUN_005a9488;
      uStack_28 = 0;
      uStack_2c = 0;
      puStack_18 = (undefined4 *)0x0;
      uStack_14 = 0;
      iStack_10 = 0;
      pppuVar10 = &ppuStack_54;
      uStack_4 = 6;
      FUN_004d6570(iVar6,iVar9,pppuVar10);
      iVar6 = FUN_004d65c0(iVar6,iVar9,pppuVar10);
      piVar4 = piStack_24;
      if (iVar6 != 0) {
        for (; piVar4 != piStack_20; piVar4 = piVar4 + 3) {
          if (*piVar4 == 0x11) {
            if ((piVar4 != piStack_20) && (piVar4 != (int *)0x0)) {
              (**(code **)(*param_1 + 400))(piVar4[1]);
            }
            break;
          }
        }
      }
      puVar3 = puStack_18;
      iVar6 = (iStack_10 - (int)puStack_18) / 0x28;
      uStack_4 = 7;
      piVar4 = piStack_20;
      if (iVar6 != 0) {
        uVar7 = iVar6 * 0x28;
        if (uVar7 < 0x81) {
          FUN_00402330();
          *puVar3 = *(undefined4 *)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4);
          *(undefined4 **)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4) = puVar3;
          DAT_005d59e8 = 0;
          piVar4 = piStack_20;
        }
        else {
          FUN_005089fd(puStack_18);
          piVar4 = piStack_20;
        }
      }
      ppuStack_54 = &PTR_FUN_005a94e4;
      ppiStack_80 = &piStack_24;
      uStack_4._0_1_ = 0xb;
      uStack_4._1_3_ = 0;
      for (piVar8 = piStack_24; piVar8 != piVar4; piVar8 = piVar8 + 3) {
        FUN_004d4a40(piVar8);
      }
      uStack_4._0_1_ = 10;
      FUN_0049b270();
      uStack_4._0_1_ = 9;
      FUN_004026e0();
      uStack_4 = CONCAT31(uStack_4._1_3_,8);
      FUN_004026e0();
      uStack_4 = 0xffffffff;
      piVar4 = (int *)FUN_004026e0();
    }
    break;
  case 0x39:
    ExceptionList = &pvStack_c;
    piVar4 = (int *)(**(code **)(*param_1 + 0x44))();
    (**(code **)(*piVar4 + 0x48))(0x5a,0x3f800000,0,0xbf800000);
    piVar4 = (int *)FUN_00487830();
    iVar6 = *piVar4;
    uVar5 = (**(code **)(*param_1 + 0x4c))(s_RobotHit_005c9a24,0,0);
    piVar4 = (int *)(**(code **)(iVar6 + 0x204))(uVar5);
    break;
  case 0x43:
    param_1[0xd7] = 1;
    break;
  case 0x4b:
    ExceptionList = &pvStack_c;
    piVar4 = (int *)(**(code **)(*param_1 + 0x4c))();
    if (piVar4 == (int *)param_3[1]) {
      ppiStack_80 = apiStack_50;
      FUN_00402b70(&uStack_85,8);
      uStack_4 = 0xc;
      FUN_00402a70();
      uStack_4 = 0xd;
      FUN_004024a0(&uStack_86);
      uStack_4._0_1_ = 0xe;
      FUN_004024a0(&uStack_87);
      uStack_4 = CONCAT31(uStack_4._1_3_,0xf);
      FUN_005005b0(&uStack_88);
      ppuStack_54 = &PTR_FUN_005a9488;
      uStack_28 = 0;
      uStack_2c = 0;
      puStack_18 = (undefined4 *)0x0;
      uStack_14 = 0;
      iStack_10 = 0;
      uStack_4 = 0x10;
      FUN_004d6570();
      iVar6 = FUN_004d65c0(1,*param_3,&ppuStack_54);
      piVar4 = piStack_24;
      if (iVar6 != 0) {
        for (; piVar4 != piStack_20; piVar4 = piVar4 + 3) {
          if (*piVar4 == 0xb) {
            if ((piVar4 != piStack_20) && (piVar4 != (int *)0x0)) {
              (**(code **)(*param_1 + 0x54))(piVar4[1]);
            }
            break;
          }
        }
      }
      puVar3 = puStack_18;
      iVar6 = (iStack_10 - (int)puStack_18) / 0x28;
      uStack_4 = 0x11;
      piVar4 = piStack_20;
      if (iVar6 != 0) {
        uVar7 = iVar6 * 0x28;
        if (uVar7 < 0x81) {
          FUN_00402330();
          *puVar3 = *(undefined4 *)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4);
          *(undefined4 **)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4) = puVar3;
          DAT_005d59e8 = 0;
          piVar4 = piStack_20;
        }
        else {
          FUN_005089fd(puStack_18);
          piVar4 = piStack_20;
        }
      }
      ppuStack_54 = &PTR_FUN_005a94e4;
      ppiStack_80 = &piStack_24;
      uStack_4._0_1_ = 0x15;
      uStack_4._1_3_ = 0;
      for (piVar8 = piStack_24; piVar8 != piVar4; piVar8 = piVar8 + 3) {
        FUN_004d4a40(piVar8);
      }
      uStack_4._0_1_ = 0x14;
      FUN_0049b270();
      uStack_4._0_1_ = 0x13;
      FUN_00402bd0();
      uStack_4 = CONCAT31(uStack_4._1_3_,0x12);
      FUN_00402bd0();
      uStack_4 = 0xffffffff;
      piVar4 = (int *)FUN_00402bd0();
    }
    break;
  case 0x4d:
    ExceptionList = &pvStack_c;
    FUN_00477c90(3,auStack_60);
    piVar4 = (int *)FUN_00477c90(1,&fStack_78);
    fStack_78 = -fStack_78;
    uStack_6c = 0;
    fStack_74 = -fStack_74;
    fStack_70 = -fStack_70;
    uStack_68 = 0;
    uStack_64 = 0x3f800000;
    if ((int *)param_1[0x69] != (int *)0x0) {
      piVar4 = (int *)(**(code **)(*(int *)param_1[0x69] + 0x40))(auStack_60,&fStack_78,&uStack_6c);
    }
  }
  ExceptionList = pvStack_c;
  return piVar4;
}

