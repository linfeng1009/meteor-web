/* Meteor.exe original x86 @ 00452af0 */
/* Caller: 0046211c */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00452af0(int param_1,int param_2,int param_3,int param_4,int *param_5)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  byte *pbVar6;
  int *piVar7;
  undefined4 uVar8;
  char *pcVar9;
  undefined2 *puVar10;
  undefined4 *puVar11;
  undefined1 *puVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  int *piVar16;
  byte *pbVar17;
  char *pcVar18;
  int **ppiVar19;
  int **ppiVar20;
  int **ppiVar21;
  int ***pppiVar22;
  undefined4 *puVar23;
  bool bVar24;
  float10 fVar25;
  int **appiStackY_2f8 [3];
  int iStackY_2ec;
  int **ppiStackY_2e8;
  int **ppiStackY_2e4;
  int **ppiStackY_2e0;
  int *local_2c8;
  int *local_2c4;
  int *local_2c0;
  undefined4 local_2bc;
  uint local_2b8;
  int local_2b4;
  int *local_2b0;
  int *local_2ac;
  int *local_2a8;
  int *local_2a4;
  int *local_2a0;
  undefined4 local_29c;
  undefined4 local_298;
  int *local_294;
  void *pvStack_290;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 uStack_248;
  int iStack_244;
  byte local_240 [52];
  char local_20c [256];
  char local_10c [256];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059c769;
  local_c = ExceptionList;
  ppiStackY_2e0 = (int **)0x452b1e;
  ExceptionList = &local_c;
  iVar5 = FUN_0044f180();
  if (iVar5 == 0) {
    ExceptionList = local_c;
    return 0;
  }
  switch(param_2) {
  case 2:
    *(undefined4 *)(param_1 + 0x2dc) = 2;
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x4559e4;
    FUN_00505f60();
    break;
  case 3:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x453308;
    FUN_00505f60();
    local_2c8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2a8 = (int *)0x0;
    local_2a4 = (int *)0x0;
    local_2a0 = (int *)0x0;
    local_4 = 0xc;
    piVar16 = local_2c8;
    if (*(code **)(param_1 + 0x10) != (code *)0x0) {
      ppiStackY_2e0 = &local_2c8;
      ppiStackY_2e4 = (int **)0x6;
      ppiStackY_2e8 = (int **)0x453351;
      (**(code **)(param_1 + 0x10))();
      piVar16 = local_2c8;
    }
    for (; piVar16 != local_2c4; piVar16 = piVar16 + 1) {
    }
    local_2ac = (int *)0x0;
    local_2b0 = local_2a8;
    if (local_2a8 != local_2a4) {
      local_2b4 = 0x7d;
      do {
        ppiStackY_2e0 = (int **)0x453390;
        pvStack_290 = operator_new(0x50);
        local_4._0_1_ = 0xd;
        if (pvStack_290 != (void *)0x0) {
          FUN_00465610();
        }
        DAT_005ddd68 = DAT_005c7b60 * _DAT_005a8b10;
        local_4 = CONCAT31(local_4._1_3_,0xc);
        appiStackY_2f8[1] = (int **)0x2;
        appiStackY_2f8[0] = (int **)0x1;
        DAT_005ddd6c = (void *)((float)local_2b4 * DAT_005c7b60);
        _DAT_005ddd70 = DAT_005c7b60 * _DAT_005a8b0c;
        _DAT_005ddd74 = DAT_005c7b60 * _DAT_005a8b08;
        puVar11 = &DAT_005ddd68;
        pppiVar22 = appiStackY_2f8 + 2;
        for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
          *pppiVar22 = (int **)*puVar11;
          puVar11 = puVar11 + 1;
          pppiVar22 = pppiVar22 + 1;
        }
        FUN_00466720();
        ppiStackY_2e0 = (int **)0x0;
        ppiStackY_2e4 = (int **)0x0;
        puVar11 = &DAT_005ddd68;
        pppiVar22 = appiStackY_2f8;
        for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
          *pppiVar22 = (int **)*puVar11;
          puVar11 = puVar11 + 1;
          pppiVar22 = pppiVar22 + 1;
        }
        FUN_00466a10();
        piVar16 = local_2b0;
        ppiStackY_2e0 = (int **)0xff;
        ppiStackY_2e4 = (int **)0xff;
        iStackY_2ec = *local_2b0;
        ppiStackY_2e8 = (int **)0x0;
        appiStackY_2f8[2] = (int **)0x453459;
        FUN_00466340();
        ppiStackY_2e0 = (int **)0x453465;
        FUN_00467950();
        local_2b0 = piVar16 + 3;
        local_2ac = (int *)((int)local_2ac + 1);
        local_2b4 = local_2b4 + 0x14;
      } while (local_2b0 != local_2a4);
    }
    ppiStackY_2e0 = (int **)0x45349c;
    FUN_00465f10();
    ppiStackY_2e0 = (int **)0x4534a9;
    (**(code **)(**(int **)(param_1 + 0x26c) + 0xc))();
    local_2b0 = (int *)(*(int **)(param_1 + 0x2f0))[2];
    if (local_2b0 != *(int **)(param_1 + 0x2f0)) {
      do {
        piVar16 = local_2b0;
        ppiStackY_2e0 = (int **)0x4534cf;
        (**(code **)(*(int *)local_2b0[5] + 0xc))();
        if (*(int *)(*(int *)(piVar16[5] + 4) + 8) != 2) {
          *(undefined4 *)(*(int *)(piVar16[5] + 4) + 8) = 3;
        }
        FUN_0043c6c0();
      } while (local_2b0 != *(int **)(param_1 + 0x2f0));
    }
    iStack_244 = local_2c8[(int)local_2ac + -1];
    ppiStackY_2e0 = &local_294;
    ppiStackY_2e4 = (int **)0x45351b;
    FUN_00460d90();
    piVar16 = local_2a4;
    if (*(int *)(*(int *)(local_294[5] + 4) + 8) != 2) {
      *(undefined4 *)(*(int *)(local_294[5] + 4) + 8) = 0;
    }
    local_4._0_1_ = 0xe;
    for (piVar7 = local_2a8; piVar7 != piVar16; piVar7 = piVar7 + 3) {
      FUN_004026e0();
    }
    local_4 = CONCAT31(local_4._1_3_,0xb);
    if (((int)local_2a0 - (int)local_2a8) / 0xc != 0) {
      ppiStackY_2e4 = (int **)0x453584;
      ppiStackY_2e0 = (int **)local_2a8;
      FUN_00402e90();
    }
    local_4 = 0xffffffff;
    if ((int)local_2c0 - (int)local_2c8 >> 2 != 0) {
      ppiStackY_2e0 = (int **)local_2c8;
      ppiStackY_2e4 = (int **)0x4535af;
      FUN_00402e90();
    }
    *(undefined4 *)(param_1 + 0x2dc) = 0xc;
    break;
  case 4:
    ppiStackY_2e0 = (int **)DAT_005e0078;
    ppiStackY_2e4 = (int **)0x456fb5;
    FUN_00505f60();
    puVar11 = (undefined4 *)FUN_00458200();
    puVar23 = (undefined4 *)(param_1 + 0xec);
    for (iVar5 = 0x1a; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar23 = *puVar11;
      puVar11 = puVar11 + 1;
      puVar23 = puVar23 + 1;
    }
    iVar5 = FUN_00458200();
    *(undefined1 *)(param_1 + 0xee) = *(undefined1 *)(iVar5 + 2);
    iVar5 = FUN_00458200();
    pcVar9 = (char *)(iVar5 + 0x10);
    iVar5 = param_1 - (int)pcVar9;
    do {
      cVar1 = *pcVar9;
      pcVar9[iVar5 + 0xfc] = cVar1;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    iVar5 = FUN_00458200();
    *(undefined1 *)(param_1 + 0xef) = *(undefined1 *)(iVar5 + 3);
    iVar5 = FUN_00458200();
    *(undefined1 *)(param_1 + 0xf2) = *(undefined1 *)(iVar5 + 6);
    iVar5 = FUN_00458200();
    *(undefined1 *)(param_1 + 0xf1) = *(undefined1 *)(iVar5 + 5);
    iVar5 = FUN_00458200();
    pcVar9 = (char *)(iVar5 + 0x50);
    iVar5 = param_1 - (int)pcVar9;
    do {
      cVar1 = *pcVar9;
      pcVar9[iVar5 + 0x13c] = cVar1;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    puVar12 = (undefined1 *)FUN_00458200();
    *(undefined1 *)(param_1 + 0xec) = *puVar12;
    iVar5 = FUN_00458200();
    *(undefined1 *)(param_1 + 0xf0) = *(undefined1 *)(iVar5 + 4);
    iVar5 = FUN_00458200();
    *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)(iVar5 + 8);
    iVar5 = FUN_00458200();
    *(undefined2 *)(param_1 + 0xf8) = *(undefined2 *)(iVar5 + 0xc);
    break;
  case 5:
    if (param_4 != 0) {
      ExceptionList = local_c;
      return 1;
    }
    ppiStackY_2e0 = (int **)0x456406;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x45640d;
    FUN_004630b0();
    FUN_005565e0();
    iVar5 = FUN_00458210();
    if (iVar5 == 0) {
      ExceptionList = local_c;
      return 0;
    }
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x456432;
    FUN_00463010();
    ppiStackY_2e0 = (int **)0x456439;
    FUN_00570fd0();
    pbVar17 = local_240;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      pbVar17[0] = 0;
      pbVar17[1] = 0;
      pbVar17[2] = 0;
      pbVar17[3] = 0;
      pbVar17 = pbVar17 + 4;
    }
    ppiStackY_2e0 = (int **)local_240;
    ppiStackY_2e4 = (int **)s_serverlist_005c73b4;
    pbVar17[0] = 0;
    pbVar17[1] = 0;
    ppiStackY_2e8 = (int **)0x456461;
    FUN_00462d40();
    ppiStackY_2e8 = (int **)0x456468;
    FUN_004630b0();
    ppiStackY_2e4 = (int **)0x45646f;
    FUN_005565e0();
    ppiStackY_2e4 = (int **)0x456476;
    FUN_00458210();
    ppiStackY_2e4 = (int **)0x45647d;
    FUN_004663c0();
    pbVar6 = &DAT_005deddc;
    pbVar17 = local_240;
    do {
      bVar2 = *pbVar17;
      bVar24 = bVar2 < *pbVar6;
      if (bVar2 != *pbVar6) {
LAB_004564ad:
        iVar5 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
        goto LAB_004564b2;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar17[1];
      bVar24 = bVar2 < pbVar6[1];
      if (bVar2 != pbVar6[1]) goto LAB_004564ad;
      pbVar17 = pbVar17 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar2 != 0);
    iVar5 = 0;
LAB_004564b2:
    ppiStackY_2e0 = (int **)0x0;
    if (iVar5 != 0) {
      ppiStackY_2e4 = (int **)param_3;
      ppiStackY_2e8 = (int **)param_2;
      iStackY_2ec = 0x4564d4;
      FUN_0044f0e0();
      ppiStackY_2e0 = (int **)0x4564e5;
      FUN_00463070();
      ppiStackY_2e0 = (int **)0x4564f2;
      (**(code **)(**(int **)(param_1 + 0x2c4) + 0x58))();
      ppiStackY_2e0 = (int **)0x456504;
      FUN_00461e50();
      ppiStackY_2e0 = (int **)0x456516;
      FUN_004618c0();
      ppiStackY_2e0 = (int **)0x456523;
      FUN_0046bc80();
      ppiStackY_2e0 = (int **)0x456530;
      FUN_0046b560();
      ppiStackY_2e0 = (int **)0x456540;
      FUN_0046b860();
      if (DAT_005e0324 != 0) {
        ppiStackY_2e0 = (int **)0x0;
        ppiStackY_2e4 = (int **)param_3;
        ppiStackY_2e8 = (int **)0x4c;
        iStackY_2ec = 0x456555;
        FUN_004620e0();
      }
      ExceptionList = local_c;
      return 0;
    }
    goto LAB_00456a65;
  case 6:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x456f7b;
    FUN_00505f60();
  case 0x48:
    FUN_004582e0();
    break;
  case 7:
    if (param_4 == 0) {
      ppiStackY_2e0 = (int **)DAT_005e0068;
      ppiStackY_2e4 = (int **)0x457b0d;
      FUN_00505f60();
      ppiStackY_2e0 = (int **)0x0;
      ppiStackY_2e4 = (int **)param_3;
      ppiStackY_2e8 = (int **)param_2;
      iStackY_2ec = 0x457b2a;
      FUN_0044f0e0();
      ppiStackY_2e0 = (int **)0x457b3b;
      FUN_00463070();
      ppiStackY_2e0 = (int **)0x457b48;
      (**(code **)(**(int **)(param_1 + 0x300) + 0x58))();
      ppiStackY_2e0 = (int **)0x457b5a;
      FUN_00461e50();
      ppiStackY_2e0 = (int **)0x457b6c;
      FUN_004618c0();
      if (*(int *)(param_1 + 0x20) != 0) {
        ppiStackY_2e0 = (int **)0x457b85;
        FUN_004024a0();
        local_4 = 0x2a;
        ppiStackY_2e0 = (int **)0x457b9f;
        FUN_004024a0();
        ppiStackY_2e0 = &local_2c8;
        ppiStackY_2e4 = &local_2a8;
        local_4._0_1_ = 0x2b;
        ppiStackY_2e8 = (int **)0x457bb6;
        (**(code **)(param_1 + 0x20))();
        FUN_004606f0();
        ppiStackY_2e0 = (int **)0x457bce;
        FUN_0046db10();
        FUN_004606f0();
        ppiStackY_2e0 = (int **)0x457be3;
        FUN_0046db30();
        local_4 = CONCAT31(local_4._1_3_,0x2a);
        FUN_004026e0();
        local_4 = 0xffffffff;
        FUN_004026e0();
      }
      ExceptionList = local_c;
      return 0;
    }
    break;
  case 8:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x457d30;
    FUN_00505f60();
    *(undefined4 *)(param_1 + 0x2dc) = 5;
    ppiStackY_2e0 = (int **)s_user_name_005c756c;
    ppiStackY_2e4 = (int **)0x457d55;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457d5c;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457d63;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457d6a;
    FUN_00464240();
    break;
  case 9:
    *(undefined4 *)(param_1 + 0x2dc) = 7;
    if ((*(int *)(param_1 + 0x274) != 0) && (FUN_00468f20(), *(int *)(param_1 + 0x10) != 0)) {
      ppiStackY_2e0 = (int **)0x455dcf;
      FUN_005005b0();
      local_4 = 0x23;
      ppiStackY_2e0 = (int **)0x455de8;
      FUN_005005b0();
      local_4 = CONCAT31(local_4._1_3_,0x24);
      ppiStackY_2e0 = (int **)0x455dfc;
      FUN_00463010();
      ppiStackY_2e0 = (int **)0x455e03;
      FUN_004630b0();
      FUN_005565e0();
      FUN_0046b260();
      ppiStackY_2e0 = (int **)0x1;
      ppiStackY_2e4 = (int **)0x455e19;
      iStackY_2ec = FUN_004601b0();
      ppiStackY_2e4 = &local_2a8;
      ppiStackY_2e8 = &local_2c8;
      appiStackY_2f8[2] = (int **)0x455e27;
      (**(code **)(param_1 + 0x10))();
      piVar16 = (int *)FUN_004606f0();
      local_2ac = (int *)0x0;
      local_2b0 = piVar16;
      piVar7 = (int *)FUN_00460710();
      if (piVar16 != piVar7) {
        local_2b4 = 0x6f;
        do {
          ppiStackY_2e0 = (int **)0x455e61;
          pvStack_290 = operator_new(0x50);
          local_4 = CONCAT31(local_4._1_3_,0x25);
          if (pvStack_290 == (void *)0x0) {
            piVar16 = (int *)0x0;
          }
          else {
            piVar16 = (int *)FUN_00465610();
          }
          DAT_005ddd6c = (void *)(float)local_2b4;
          _DAT_005ddd70 = 172.0;
          _DAT_005ddd74 = 24.0;
          DAT_005ddd68 = 433.0;
          puVar11 = &DAT_005ddd68;
          pppiVar22 = appiStackY_2f8 + 2;
          pvStack_290 = DAT_005ddd6c;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pppiVar22 = (int **)*puVar11;
            puVar11 = puVar11 + 1;
            pppiVar22 = pppiVar22 + 1;
          }
          appiStackY_2f8[1] = (int **)0x1;
          appiStackY_2f8[0] = (int **)0x1;
          local_4 = CONCAT31(local_4._1_3_,0x24);
          FUN_00466720();
          ppiStackY_2e0 = (int **)0x0;
          ppiStackY_2e4 = (int **)0x0;
          _DAT_005ddd70 = 142.0;
          _DAT_005ddd74 = 24.0;
          DAT_005ddd68 = 448.0;
          DAT_005ddd6c = pvStack_290;
          puVar11 = &DAT_005ddd68;
          pppiVar22 = appiStackY_2f8;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pppiVar22 = (int **)*puVar11;
            puVar11 = puVar11 + 1;
            pppiVar22 = pppiVar22 + 1;
          }
          FUN_00466a10();
          piVar7 = local_2ac;
          ppiStackY_2e0 = (int **)0xff;
          ppiStackY_2e4 = (int **)0xff;
          ppiStackY_2e8 = (int **)0x0;
          iStackY_2ec = (int)local_2ac;
          appiStackY_2f8[2] = (int **)0x455f38;
          FUN_00460720();
          iStackY_2ec = 0x455f3f;
          iStackY_2ec = FUN_004606f0();
          appiStackY_2f8[2] = (int **)0x455f47;
          FUN_00466340();
          ppiStackY_2e0 = (int **)0x455f55;
          (**(code **)(*piVar16 + 0x54))();
          ppiStackY_2e0 = (int **)0x455f61;
          FUN_00467950();
          ppiStackY_2e0 = (int **)0x455f6d;
          FUN_00469170();
          ppiStackY_2e0 = (int **)0x455f74;
          FUN_00469760();
          local_2ac = (int *)((int)piVar7 + 1);
          local_2b4 = local_2b4 + 0x18;
          piVar7 = local_2b0 + 1;
          local_2b0 = piVar7;
          piVar16 = (int *)FUN_00460710();
        } while (piVar7 != piVar16);
        if (0 < (int)local_2ac) {
          ppiStackY_2e0 = (int **)0x455fb5;
          FUN_00465f10();
          ppiStackY_2e0 = (int **)0xff;
          ppiStackY_2e4 = (int **)0x0;
          ppiStackY_2e8 = (int **)0x455fcc;
          FUN_00458210();
          ppiStackY_2e8 = (int **)0x455fd3;
          FUN_004666a0();
          *(undefined4 *)(*(int *)(param_1 + 0x274) + 0x74) = 1;
        }
      }
      local_4 = CONCAT31(local_4._1_3_,0x23);
      FUN_00402890();
      local_4 = 0xffffffff;
      FUN_004f8350();
    }
    ppiStackY_2e0 = (int **)s_game_name_005c7518;
    ppiStackY_2e4 = (int **)0x45601f;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x456026;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x45602d;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x456034;
    FUN_00464240();
    ppiStackY_2e0 = (int **)s_autoswitch_005c74e8;
    ppiStackY_2e4 = (int **)0x45604d;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x456054;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x45605b;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x456062;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_friendfire_005c74f4;
    ppiStackY_2e4 = (int **)0x45607b;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x456082;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x456089;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x456090;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_healthitem_005c74dc;
    ppiStackY_2e4 = (int **)0x4560ac;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x4560b3;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x4560ba;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x4560c1;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_hideitem_005c7500;
    ppiStackY_2e4 = (int **)0x4560da;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x4560e1;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x4560e8;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x4560ef;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_specialitem_005c74c4;
    ppiStackY_2e4 = (int **)0x45610b;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x456112;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x456119;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x456120;
    FUN_00458230();
    goto LAB_00456132;
  case 10:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x457ad8;
    FUN_00505f60();
    *(undefined4 *)(param_1 + 0x2dc) = 3;
    FUN_004582e0();
    break;
  case 0xb:
    ppiStackY_2e0 = (int **)0x45656f;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x456576;
    FUN_004630b0();
    FUN_005565e0();
    iVar5 = FUN_00458210();
    if (iVar5 == 0) {
      ExceptionList = local_c;
      return 0;
    }
    *(undefined4 *)(param_1 + 0x2dc) = 0xb;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4565a5;
    FUN_00463010();
    ppiStackY_2e0 = (int **)0x4565ac;
    FUN_00570fd0();
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4565c1;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x7c) = uVar8;
    ppiStackY_2e0 = (int **)0x4565de;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x78) = uVar8;
    ppiStackY_2e0 = (int **)0x4565fb;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x84) = uVar8;
    ppiStackY_2e0 = (int **)0x45661b;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x74) = uVar8;
    ppiStackY_2e0 = (int **)0x456638;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x8c) = uVar8;
    ppiStackY_2e0 = (int **)0x456658;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    pbVar17 = (byte *)(param_1 + 0x40);
    ppiStackY_2e0 = (int **)s_game_name_005c7518;
    *(undefined4 *)(param_1 + 0x88) = uVar8;
    ppiStackY_2e4 = (int **)0x45667c;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x456683;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x45668a;
    FUN_00464220();
    pbVar6 = (byte *)&DAT_005d5a24;
    do {
      bVar2 = *pbVar17;
      bVar24 = bVar2 < *pbVar6;
      if (bVar2 != *pbVar6) {
LAB_004566b7:
        iVar5 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
        goto LAB_004566bc;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar17[1];
      bVar24 = bVar2 < pbVar6[1];
      if (bVar2 != pbVar6[1]) goto LAB_004566b7;
      pbVar17 = pbVar17 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar2 != 0);
    iVar5 = 0;
LAB_004566bc:
    if (iVar5 == 0) {
      pcVar9 = s_unname_005c7820;
      do {
        cVar1 = *pcVar9;
        pcVar9[param_1 + -0x5c77e0] = cVar1;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
    }
    ppiStackY_2e0 = (int **)s_password_005c4218;
    ppiStackY_2e4 = (int **)0x4566e4;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x4566eb;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x4566f2;
    FUN_00464220();
    ppiStackY_2e0 = (int **)0x456703;
    FUN_004630b0();
    FUN_005565e0();
    pcVar9 = (char *)FUN_0046b260();
    iVar5 = 3;
    bVar24 = true;
    pcVar18 = &DAT_005c7458;
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar24 = *pcVar9 == *pcVar18;
      pcVar9 = pcVar9 + 1;
      pcVar18 = pcVar18 + 1;
    } while (bVar24);
    if (bVar24) {
      *(undefined2 *)(param_1 + 0x6c) = 9999;
    }
    else {
      ppiStackY_2e0 = (int **)0x45672a;
      FUN_004630b0();
      FUN_005565e0();
      FUN_0046b260();
      ppiStackY_2e0 = (int **)0x45673e;
      uVar4 = FUN_0050915b();
      *(undefined2 *)(param_1 + 0x6c) = uVar4;
    }
    ppiStackY_2e0 = (int **)0x456759;
    FUN_004630b0();
    FUN_005565e0();
    FUN_0046b260();
    ppiStackY_2e0 = (int **)0x45676d;
    uVar4 = FUN_0050915b();
    *(undefined2 *)(param_1 + 0x6e) = uVar4;
    ppiStackY_2e0 = (int **)0x456780;
    FUN_004630b0();
    FUN_005565e0();
    FUN_0046b260();
    ppiStackY_2e0 = (int **)0x1;
    ppiStackY_2e4 = (int **)0x456796;
    uVar4 = FUN_004601b0();
    *(undefined2 *)(param_1 + 0x68) = uVar4;
    ppiStackY_2e0 = (int **)0x4567a9;
    FUN_004630b0();
    FUN_005565e0();
    FUN_0046b260();
    ppiStackY_2e0 = (int **)0x4567bd;
    uVar4 = FUN_0050915b();
    *(undefined2 *)(param_1 + 0x6a) = uVar4;
    ppiStackY_2e0 = (int **)0x4567d0;
    FUN_004630b0();
    FUN_005565e0();
    FUN_0046b260();
    ppiStackY_2e0 = (int **)0x4567e4;
    FUN_0050a69a();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x70) = uVar8;
    ppiStackY_2e0 = (int **)0x4567fb;
    FUN_004630b0();
    FUN_005565e0();
    iVar5 = FUN_00458210();
    pbVar17 = local_240;
    for (iVar15 = 0xc; iVar15 != 0; iVar15 = iVar15 + -1) {
      pbVar17[0] = 0;
      pbVar17[1] = 0;
      pbVar17[2] = 0;
      pbVar17[3] = 0;
      pbVar17 = pbVar17 + 4;
    }
    pbVar17[0] = 0;
    pbVar17[1] = 0;
    if (*(int *)(param_1 + 0x10) != 0) {
      ppiStackY_2e0 = (int **)0x456836;
      FUN_005005b0();
      local_4 = 0x26;
      ppiStackY_2e0 = (int **)0x45684f;
      FUN_005005b0();
      local_4._0_1_ = 0x27;
      if (iVar5 != 0) {
        ppiStackY_2e0 = (int **)local_240;
        ppiStackY_2e4 = (int **)0x456870;
        FUN_004663c0();
        ppiStackY_2e4 = (int **)(int)*(short *)(param_1 + 0x68);
        ppiStackY_2e0 = &local_2a8;
        ppiStackY_2e8 = (int **)0x456882;
        (**(code **)(param_1 + 0x10))();
        iVar5 = FUN_004606f0();
        iVar15 = FUN_00460710();
        if (iVar5 != iVar15) {
          do {
            pbVar6 = (byte *)FUN_004606f0();
            pbVar17 = local_240;
            do {
              bVar2 = *pbVar17;
              bVar24 = bVar2 < *pbVar6;
              if (bVar2 != *pbVar6) {
LAB_004568d3:
                iVar15 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
                goto LAB_004568d8;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar17[1];
              bVar24 = bVar2 < pbVar6[1];
              if (bVar2 != pbVar6[1]) goto LAB_004568d3;
              pbVar17 = pbVar17 + 2;
              pbVar6 = pbVar6 + 2;
            } while (bVar2 != 0);
            iVar15 = 0;
LAB_004568d8:
            if (iVar15 == 0) {
              ppiStackY_2e0 = (int **)0x4568f9;
              puVar10 = (undefined2 *)FUN_00460700();
              *(undefined2 *)(param_1 + 0x90) = *puVar10;
              break;
            }
            iVar5 = iVar5 + 0xc;
            iVar15 = FUN_00460710();
          } while (iVar5 != iVar15);
        }
      }
      local_4 = CONCAT31(local_4._1_3_,0x26);
      FUN_00402890();
      local_4 = 0xffffffff;
      FUN_004f8350();
    }
    FUN_0045a840();
    *(int *)(param_1 + 0x2e0) = (int)*(short *)(param_1 + 0x68);
    if (*(short *)(param_1 + 0x68) == 1) {
      ppiStackY_2e0 = (int **)0x456951;
      FUN_00570fc0();
    }
    else {
LAB_0045695a:
      ppiStackY_2e0 = (int **)0x45696d;
      FUN_00570fc0();
    }
    goto LAB_00456974;
  case 0xc:
    *(undefined4 *)(param_1 + 0x2dc) = 3;
  case 0x59:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x45618e;
    FUN_00505f60();
    break;
  case 0xd:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x457156;
    FUN_00505f60();
    *(undefined4 *)(param_1 + 0x2dc) = 1;
    ppiStackY_2e0 = (int **)s_user_name_005c756c;
    ppiStackY_2e4 = (int **)0x45717b;
    FUN_00462d40();
    ppiStackY_2e4 = (int **)0x457182;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457189;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457190;
    FUN_00464220();
    FUN_0045b280();
    break;
  case 0xe:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x457e72;
    FUN_00505f60();
    ppiStackY_2e0 = (int **)s_autocamera_005c7664;
    ppiStackY_2e4 = (int **)0x457e98;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457e9f;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457ea6;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457ead;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_lockflag_005c7658;
    ppiStackY_2e4 = (int **)0x457ec9;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457ed0;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457ed7;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457ede;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_showname_005c764c;
    ppiStackY_2e4 = (int **)0x457efa;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457f01;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457f08;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457f0f;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_record_005c7644;
    ppiStackY_2e4 = (int **)0x457f2b;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457f32;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457f39;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457f40;
    FUN_00458230();
  case 0x83:
    FUN_0045a0a0();
    break;
  case 0xf:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x457d7d;
    FUN_00505f60();
    ppiStackY_2e0 = (int **)s_bright_005c75e8;
    ppiStackY_2e4 = (int **)0x457da2;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457da9;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457db0;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457db7;
    FUN_00469840();
    ppiStackY_2e0 = (int **)&DAT_005c75d8;
    ppiStackY_2e4 = (int **)0x457dd3;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457dda;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457de1;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457de8;
    FUN_00469840();
    ppiStackY_2e0 = (int **)s_balance_005c75e0;
    ppiStackY_2e4 = (int **)0x457e04;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457e0b;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457e12;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457e19;
    FUN_00469840();
    ppiStackY_2e0 = (int **)s_musicvol_005c75c0;
    ppiStackY_2e4 = (int **)0x457e35;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457e3c;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457e43;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457e4a;
    FUN_00469840();
    ppiStackY_2e0 = (int **)s_audiovol_005c75cc;
    goto LAB_00457fb4;
  case 0x10:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x457f59;
    FUN_00505f60();
    FUN_004581e0();
    ppiStackY_2e0 = (int **)s_reversemouse_005c76a0;
    ppiStackY_2e4 = (int **)0x457f8a;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x457f91;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457f98;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457f9f;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_mousespeed_005c767c;
LAB_00457fb4:
    ppiStackY_2e4 = (int **)0x457fbb;
    FUN_00463010();
LAB_00457fbb:
    ppiStackY_2e4 = (int **)0x457fc2;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x457fc9;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x457fd0;
    FUN_00469840();
    break;
  case 0x11:
    ppiStackY_2e0 = (int **)0x4573b2;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4573b9;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x154) = uVar8;
    ppiStackY_2e0 = (int **)0x4573e4;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4573eb;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x15c) = uVar8;
    ppiStackY_2e0 = (int **)0x457416;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x45741d;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x158) = uVar8;
    ppiStackY_2e0 = (int **)0x457448;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x45744f;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x164) = uVar8;
    ppiStackY_2e0 = (int **)0x45747a;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x457481;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x160) = uVar8;
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x4574ad;
    FUN_00505f60();
    break;
  case 0x12:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x453090;
    FUN_00505f60();
    break;
  case 0x13:
    *(undefined4 *)(param_1 + 0x158) = 100;
    *(undefined4 *)(param_1 + 0x154) = 100;
    ppiStackY_2e0 = (int **)s_bright_005c75e8;
    *(undefined4 *)(param_1 + 0x160) = 0x32;
    *(undefined4 *)(param_1 + 0x15c) = 0x32;
    *(undefined4 *)(param_1 + 0x164) = 0x32;
    ppiStackY_2e4 = (int **)0x4539ec;
    FUN_00462d40();
    ppiStackY_2e4 = (int **)0x4539f3;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x4539fa;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x453a01;
    FUN_00469840();
    ppiStackY_2e0 = (int **)&DAT_005c75d8;
    ppiStackY_2e4 = (int **)0x453a1d;
    FUN_00462d40();
    ppiStackY_2e4 = (int **)0x453a24;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x453a2b;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x453a32;
    FUN_00469840();
    ppiStackY_2e0 = (int **)s_balance_005c75e0;
    ppiStackY_2e4 = (int **)0x453a4e;
    FUN_00462d40();
    ppiStackY_2e4 = (int **)0x453a55;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x453a5c;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x453a63;
    FUN_00469840();
    ppiStackY_2e0 = (int **)s_musicvol_005c75c0;
    ppiStackY_2e4 = (int **)0x453a7f;
    FUN_00462d40();
    ppiStackY_2e4 = (int **)0x453a86;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x453a8d;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x453a94;
    FUN_00469840();
    ppiStackY_2e0 = (int **)s_audiovol_005c75cc;
    ppiStackY_2e4 = (int **)0x453ab0;
    FUN_00462d40();
    goto LAB_00457fbb;
  case 0x14:
    ppiStackY_2e0 = (int **)0x4574c8;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4574cf;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0xc4) = uVar8;
    ppiStackY_2e0 = (int **)0x4574ef;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4574f6;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0xcc) = uVar8;
    ppiStackY_2e0 = (int **)0x457516;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x45751d;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0xd0) = uVar8;
    ppiStackY_2e0 = (int **)0x45753d;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x457544;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x248) = uVar8;
  case 0x3f:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x457566;
    FUN_00505f60();
    break;
  case 0x15:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x4530a5;
    FUN_00505f60();
    break;
  case 0x16:
    *(undefined4 *)(param_1 + 0xc4) = 1;
    *(undefined4 *)(param_1 + 200) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 1;
    *(undefined4 *)(param_1 + 0xd0) = 1;
    *(undefined4 *)(param_1 + 0x248) = 0;
    ppiStackY_2e0 = (int **)0x453aed;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x453af4;
    FUN_004630b0();
    iVar5 = FUN_005565e0();
    ppiStackY_2e0 = &local_294;
    ppiStackY_2e8 = *(int ***)(iVar5 + 8);
    ppiStackY_2e4 = (int **)&local_2b4;
    local_2b4 = 0;
    local_294 = (int *)0x1;
    local_2b0 = (int *)0x2;
    iStackY_2ec = 0x453b29;
    FUN_00429e00();
    *(undefined4 *)(iVar5 + 0x20) = 1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      ppiStackY_2e0 = (int **)0x453b96;
      FUN_00462d40();
      ppiStackY_2e0 = (int **)0x453b9d;
      FUN_004630b0();
      iVar5 = FUN_005565e0();
      ppiStackY_2e0 = &local_294;
      ppiStackY_2e8 = *(int ***)(iVar5 + 8);
      ppiStackY_2e4 = (int **)&local_2b4;
      local_2b4 = 0;
      local_294 = (int *)0x1;
      local_2b0 = (int *)0x0;
      iStackY_2ec = 0x453bce;
      FUN_00429e00();
      *(undefined4 *)(iVar5 + 0x20) = 0;
    }
    else {
      ppiStackY_2e0 = (int **)0x453b49;
      FUN_00462d40();
      ppiStackY_2e0 = (int **)0x453b50;
      FUN_004630b0();
      local_2ac = (int *)FUN_005565e0();
      ppiStackY_2e0 = &local_294;
      ppiStackY_2e8 = *(int ***)((int)local_2ac + 8);
      ppiStackY_2e4 = (int **)&local_2b4;
      local_2b4 = 0;
      local_294 = (int *)0x1;
      local_2b0 = (int *)0x2;
      iStackY_2ec = 0x453b88;
      FUN_00429e00();
      *(undefined4 *)((int)local_2ac + 0x20) = 1;
    }
    if (*(int *)(param_1 + 0xd0) == 0) {
      ppiStackY_2e0 = (int **)0x453c37;
      FUN_00462d40();
      ppiStackY_2e0 = (int **)0x453c3e;
      FUN_004630b0();
      local_2ac = (int *)FUN_005565e0();
      ppiStackY_2e0 = &local_294;
      ppiStackY_2e8 = *(int ***)((int)local_2ac + 8);
      ppiStackY_2e4 = (int **)&local_2b4;
      local_2b4 = 0;
      local_294 = (int *)0x1;
      local_2b0 = (int *)0x0;
      iStackY_2ec = 0x453c6d;
      FUN_00429e00();
      *(undefined4 *)((int)local_2ac + 0x20) = 0;
    }
    else {
      ppiStackY_2e0 = (int **)0x453bef;
      FUN_00462d40();
      ppiStackY_2e0 = (int **)0x453bf6;
      FUN_004630b0();
      local_2ac = (int *)FUN_005565e0();
      ppiStackY_2e0 = &local_294;
      ppiStackY_2e8 = *(int ***)((int)local_2ac + 8);
      ppiStackY_2e4 = (int **)&local_2b4;
      local_2b4 = 0;
      local_294 = (int *)0x1;
      local_2b0 = (int *)0x2;
      iStackY_2ec = 0x453c29;
      FUN_00429e00();
      *(undefined4 *)((int)local_2ac + 0x20) = 1;
    }
    if (*(int *)(param_1 + 0x248) == 0) {
      ppiStackY_2e0 = (int **)0x453cd5;
      FUN_00462d40();
      ppiStackY_2e0 = (int **)0x453cdc;
      FUN_004630b0();
      iVar5 = FUN_005565e0();
      ppiStackY_2e0 = &local_294;
      ppiStackY_2e8 = *(int ***)(iVar5 + 8);
      ppiStackY_2e4 = (int **)&local_2b4;
      local_2b4 = 0;
      local_294 = (int *)0x1;
      local_2b0 = (int *)0x0;
      iStackY_2ec = 0x453d09;
      FUN_00429e00();
      *(undefined4 *)(iVar5 + 0x20) = 0;
    }
    else {
      ppiStackY_2e0 = (int **)0x453c8d;
      FUN_00462d40();
      ppiStackY_2e0 = (int **)0x453c94;
      FUN_004630b0();
      iVar5 = FUN_005565e0();
      ppiStackY_2e0 = &local_294;
      ppiStackY_2e8 = *(int ***)(iVar5 + 8);
      ppiStackY_2e4 = (int **)&local_2b4;
      local_2b4 = 0;
      local_294 = (int *)0x1;
      local_2b0 = (int *)0x2;
      iStackY_2ec = 0x453cc5;
      FUN_00429e00();
      *(undefined4 *)(iVar5 + 0x20) = 1;
    }
    break;
  case 0x17:
    FUN_004581e0();
    ppiStackY_2e0 = (int **)0x45758c;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x457593;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0xd4) = uVar8;
    ppiStackY_2e0 = (int **)0x4575b3;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4575ba;
    FUN_004630b0();
    FUN_005565e0();
    fVar25 = (float10)FUN_004697f0();
    *(float *)(param_1 + 0xdc) = (float)(fVar25 * (float10)_DAT_005a84c8);
    goto LAB_004575d4;
  case 0x18:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x4530bb;
    FUN_00505f60();
    break;
  case 0x19:
    *(undefined4 *)(param_1 + 0xd8) = 0;
    *(undefined4 *)(param_1 + 0xd4) = 0;
    *(undefined4 *)(param_1 + 0xdc) = 0x42480000;
    ppiStackY_2e0 = (int **)0x453d3f;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x453d46;
    FUN_004630b0();
    iVar5 = FUN_005565e0();
    ppiStackY_2e0 = &local_294;
    ppiStackY_2e8 = *(int ***)(iVar5 + 8);
    ppiStackY_2e4 = (int **)&local_2b4;
    local_2b4 = 0;
    local_294 = (int *)0x1;
    local_2b0 = (int *)0x0;
    iStackY_2ec = 0x453d77;
    FUN_00429e00();
    *(undefined4 *)(iVar5 + 0x20) = 0;
    ppiStackY_2e0 = (int **)s_mousespeed_005c767c;
    ppiStackY_2e4 = (int **)0x453d98;
    FUN_00462d40();
    ppiStackY_2e4 = (int **)0x453d9f;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x453da6;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x453dad;
    FUN_00469840();
    *(undefined4 *)(param_1 + 0x170) = 0x53;
    *(undefined4 *)(param_1 + 0x174) = 0x53;
    *(undefined4 *)(param_1 + 0x168) = 0x57;
    *(undefined4 *)(param_1 + 0x178) = 0x44;
    *(undefined4 *)(param_1 + 0x17c) = 0x44;
    *(undefined4 *)(param_1 + 0x16c) = 0x57;
    *(undefined4 *)(param_1 + 0x180) = 0x41;
    *(undefined4 *)(param_1 + 0x184) = 0x41;
    *(undefined4 *)(param_1 + 0x188) = 0x27;
    *(undefined4 *)(param_1 + 0x18c) = 0x27;
    *(undefined4 *)(param_1 + 400) = 0x25;
    *(undefined4 *)(param_1 + 0x194) = 0x25;
    *(undefined4 *)(param_1 + 0x198) = 0x26;
    *(undefined4 *)(param_1 + 0x19c) = 0x26;
    *(undefined4 *)(param_1 + 0x1a0) = 0x28;
    *(undefined4 *)(param_1 + 0x1a4) = 0x28;
    *(undefined4 *)(param_1 + 0x1a8) = 0x51;
    *(undefined4 *)(param_1 + 0x1ac) = 0x51;
    *(undefined4 *)(param_1 + 0x1b0) = 0x45;
    *(undefined4 *)(param_1 + 0x1b4) = 0x45;
    *(undefined4 *)(param_1 + 0x1b8) = 0x47;
    *(undefined4 *)(param_1 + 0x1bc) = 0x47;
    *(undefined4 *)(param_1 + 0x1c0) = 0x48;
    *(undefined4 *)(param_1 + 0x1c4) = 0x48;
    *(undefined4 *)(param_1 + 0x1c8) = 0x52;
    *(undefined4 *)(param_1 + 0x1cc) = 0x52;
    *(undefined4 *)(param_1 + 0x1d0) = 0x54;
    *(undefined4 *)(param_1 + 0x1d4) = 0x54;
    *(undefined4 *)(param_1 + 0x1d8) = 0x50;
    *(undefined4 *)(param_1 + 0x1dc) = 0x50;
    *(undefined4 *)(param_1 + 0x1e0) = 0x20;
    *(undefined4 *)(param_1 + 0x1e4) = 0x20;
    *(undefined4 *)(param_1 + 0x1e8) = 0x1b;
    *(undefined4 *)(param_1 + 0x1ec) = 0x1b;
    *(undefined4 *)(param_1 + 0x218) = 0x43;
    *(undefined4 *)(param_1 + 0x1f0) = 9;
    *(undefined4 *)(param_1 + 500) = 9;
    *(undefined4 *)(param_1 + 0x21c) = 0x43;
    *(undefined4 *)(param_1 + 0x1f8) = 0x56;
    *(undefined4 *)(param_1 + 0x1fc) = 0x56;
    *(undefined4 *)(param_1 + 0x200) = 0x42;
    *(undefined4 *)(param_1 + 0x204) = 0x42;
    *(undefined4 *)(param_1 + 0x208) = 0x1000;
    *(undefined4 *)(param_1 + 0x20c) = 0x1000;
    *(undefined4 *)(param_1 + 0x210) = 0x1200;
    *(undefined4 *)(param_1 + 0x214) = 0x1200;
    *(undefined4 *)(param_1 + 0x220) = 0x46;
    *(undefined4 *)(param_1 + 0x224) = 0x46;
    *(undefined4 *)(param_1 + 0x228) = 0x4f;
    *(undefined4 *)(param_1 + 0x22c) = 0x4f;
    *(undefined4 *)(param_1 + 0x230) = 0x49;
    *(undefined4 *)(param_1 + 0x234) = 0x49;
    *(undefined4 *)(param_1 + 0x238) = 0x59;
    *(undefined4 *)(param_1 + 0x23c) = 0x59;
    ppiStackY_2e0 = (int **)0x453f84;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x453f8b;
    FUN_004630b0();
    FUN_005565e0();
    local_2c8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    iVar5 = 0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x57) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x453fd3;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005e0220;
    appiStackY_2f8[0] = (int **)0x453ff7;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x453ffe;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x43) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x454041;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005e02f0;
    appiStackY_2f8[0] = (int **)0x454065;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x45406c;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x53) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4540af;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005e02bc;
    appiStackY_2f8[0] = (int **)0x4540d3;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x4540da;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x44) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x45411d;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd7b8;
    appiStackY_2f8[0] = (int **)0x454141;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454148;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x41) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x45418b;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005de434;
    appiStackY_2f8[0] = (int **)0x4541af;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x4541b6;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x27) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4541f9;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005e0254;
    appiStackY_2f8[0] = (int **)0x45421d;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454224;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x25) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x454267;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dbb80;
    appiStackY_2f8[0] = (int **)0x45428b;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454292;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x26) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4542d5;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005de1c4;
    appiStackY_2f8[0] = (int **)0x4542f9;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454300;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x28) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x454343;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd444;
    appiStackY_2f8[0] = (int **)0x454367;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x45436e;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x51) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4543b1;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005de0bc;
    appiStackY_2f8[0] = (int **)0x4543d5;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x4543dc;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x45) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x45441f;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd4e0;
    appiStackY_2f8[0] = (int **)0x454443;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x45444a;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x47) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x45448d;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd9c0;
    appiStackY_2f8[0] = (int **)0x4544b1;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x4544b8;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x48) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4544fb;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005de5a0;
    appiStackY_2f8[0] = (int **)0x45451f;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454526;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x52) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x454569;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005ddb2c;
    appiStackY_2f8[0] = (int **)0x45458d;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454594;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x54) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4545d7;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005ddc98;
    appiStackY_2f8[0] = (int **)0x4545fb;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454602;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x50) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x454645;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005ddfec;
    appiStackY_2f8[0] = (int **)0x454669;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454670;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x20) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4546b3;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005de6d8;
    appiStackY_2f8[0] = (int **)0x4546d7;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x4546de;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x1b) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x45471c;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005de740;
    appiStackY_2f8[0] = (int **)0x454740;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454747;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 9) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x45478a;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd618;
    appiStackY_2f8[0] = (int **)0x4547ae;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x4547b5;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x1000) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4547f8;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd784;
    appiStackY_2f8[0] = (int **)0x45481c;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454823;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x1200) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x454866;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005de878;
    appiStackY_2f8[0] = (int **)0x45488a;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454891;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x46) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4548d4;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005de6a4;
    appiStackY_2f8[0] = (int **)0x4548f8;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x4548ff;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x49) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x454942;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd958;
    appiStackY_2f8[0] = (int **)0x454966;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x45496d;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x4f) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x4549b0;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd71c;
    appiStackY_2f8[0] = (int **)0x4549d4;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x4549db;
    FUN_00466340();
    local_2c8 = (int *)0x0;
    iVar5 = 0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2bc = 0;
    local_2b8 = 0;
    do {
      if (*(int *)(param_1 + 0x168 + iVar5 * 8) == 0x59) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x1b);
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = (int **)0x454a1e;
    FUN_0044f720();
    ppiStackY_2e0 = (int **)0xff;
    ppiStackY_2e4 = (int **)0xff;
    iStackY_2ec = (int)&local_2c8;
    ppiStackY_2e8 = (int **)0x1;
    appiStackY_2f8[2] = (int **)0x0;
    appiStackY_2f8[1] = (int **)&DAT_005dd3a8;
    appiStackY_2f8[0] = (int **)0x454a42;
    FUN_00467270();
    appiStackY_2f8[2] = (int **)0x454a49;
    FUN_00466340();
    break;
  case 0x1a:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x4530d1;
    FUN_00505f60();
    break;
  case 0x1b:
    *(undefined4 *)(param_1 + 0x2dc) = 1;
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x4559c4;
    FUN_00505f60();
    break;
  case 0x1d:
    if (param_4 != 0) {
      ExceptionList = local_c;
      return 1;
    }
    ppiStackY_2e0 = (int **)0x4569b2;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4569b9;
    FUN_004630b0();
    FUN_005565e0();
    iVar5 = FUN_00458210();
    if (iVar5 == 0) {
      ExceptionList = local_c;
      return 0;
    }
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4569de;
    FUN_00463010();
    ppiStackY_2e0 = (int **)0x4569e5;
    FUN_00570fd0();
    pbVar17 = local_240;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      pbVar17[0] = 0;
      pbVar17[1] = 0;
      pbVar17[2] = 0;
      pbVar17[3] = 0;
      pbVar17 = pbVar17 + 4;
    }
    pbVar17[0] = 0;
    pbVar17[1] = 0;
    ppiStackY_2e0 = (int **)local_240;
    ppiStackY_2e4 = (int **)s_serverlist_005c73b4;
    ppiStackY_2e8 = (int **)0x456a0d;
    FUN_00462d40();
    ppiStackY_2e8 = (int **)0x456a14;
    FUN_004630b0();
    ppiStackY_2e4 = (int **)0x456a1b;
    FUN_005565e0();
    ppiStackY_2e4 = (int **)0x456a22;
    FUN_00458210();
    ppiStackY_2e4 = (int **)0x456a29;
    FUN_004663c0();
    pbVar6 = &DAT_005deddc;
    pbVar17 = local_240;
    do {
      bVar2 = *pbVar17;
      bVar24 = bVar2 < *pbVar6;
      if (bVar2 != *pbVar6) {
LAB_00456a59:
        iVar5 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
        goto LAB_00456a5e;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar17[1];
      bVar24 = bVar2 < pbVar6[1];
      if (bVar2 != pbVar6[1]) goto LAB_00456a59;
      pbVar17 = pbVar17 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar2 != 0);
    iVar5 = 0;
LAB_00456a5e:
    ppiStackY_2e0 = (int **)0x0;
    if (iVar5 != 0) {
      ppiStackY_2e4 = (int **)param_3;
      ppiStackY_2e8 = (int **)param_2;
      iStackY_2ec = 0x456acb;
      FUN_0044f0e0();
      ppiStackY_2e0 = (int **)0x456adc;
      FUN_00463070();
      ppiStackY_2e0 = (int **)0x456ae9;
      (**(code **)(**(int **)(param_1 + 0x2c4) + 0x58))();
      ppiStackY_2e0 = (int **)0x456afb;
      FUN_00461e50();
      ppiStackY_2e0 = (int **)0x456b0d;
      FUN_004618c0();
      ppiStackY_2e0 = (int **)0x456b1a;
      FUN_0046bc80();
      ppiStackY_2e0 = (int **)0x456b27;
      FUN_0046b560();
      ppiStackY_2e0 = (int **)0x456b37;
      FUN_0046b860();
      if (DAT_005e0324 != 0) {
        ppiStackY_2e0 = (int **)0x0;
        ppiStackY_2e4 = (int **)param_3;
        ppiStackY_2e8 = (int **)0x4d;
        iStackY_2ec = 0x456b4c;
        FUN_004620e0();
      }
      ExceptionList = local_c;
      return 0;
    }
LAB_00456a65:
    ppiStackY_2e0 = (int **)0x0;
    ppiStackY_2e4 = (int **)param_3;
    ppiStackY_2e8 = (int **)param_2;
    iStackY_2ec = 0x456a7c;
    FUN_0044f0e0();
    ppiStackY_2e0 = (int **)0x456a89;
    (**(code **)(**(int **)(param_1 + 0x2d0) + 0x58))();
    ppiStackY_2e0 = (int **)0x456a9b;
    FUN_00461e50();
    ppiStackY_2e0 = (int **)0x456aad;
    FUN_004618c0();
    ExceptionList = local_c;
    return 0;
  case 0x1e:
    *(undefined4 *)(param_1 + 0x2dc) = 6;
    if ((*(int *)(param_1 + 0x278) != 0) && (FUN_00468f20(), *(int *)(param_1 + 0x10) != 0)) {
      ppiStackY_2e0 = (int **)0x455a29;
      FUN_005005b0();
      local_4 = 0x20;
      ppiStackY_2e0 = (int **)0x455a42;
      FUN_005005b0();
      local_4 = CONCAT31(local_4._1_3_,0x21);
      ppiStackY_2e0 = (int **)0x455a56;
      FUN_00463010();
      ppiStackY_2e0 = (int **)0x455a5d;
      FUN_004630b0();
      FUN_005565e0();
      FUN_0046b260();
      ppiStackY_2e0 = (int **)0x1;
      ppiStackY_2e4 = (int **)0x455a73;
      sVar3 = FUN_004601b0();
      iStackY_2ec = (int)sVar3;
      ppiStackY_2e4 = &local_2a8;
      ppiStackY_2e8 = &local_2c8;
      appiStackY_2f8[2] = (int **)0x455a84;
      (**(code **)(param_1 + 0x10))();
      piVar16 = (int *)FUN_004606f0();
      local_2ac = (int *)0x0;
      local_2b0 = piVar16;
      piVar7 = (int *)FUN_00460710();
      if (piVar16 != piVar7) {
        local_2b4 = 0x6f;
        do {
          ppiStackY_2e0 = (int **)0x455abe;
          pvStack_290 = operator_new(0x50);
          local_4 = CONCAT31(local_4._1_3_,0x22);
          if (pvStack_290 == (void *)0x0) {
            piVar16 = (int *)0x0;
          }
          else {
            piVar16 = (int *)FUN_00465610();
          }
          DAT_005ddd6c = (void *)(float)local_2b4;
          _DAT_005ddd70 = 172.0;
          _DAT_005ddd74 = 24.0;
          DAT_005ddd68 = 433.0;
          puVar11 = &DAT_005ddd68;
          pppiVar22 = appiStackY_2f8 + 2;
          pvStack_290 = DAT_005ddd6c;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pppiVar22 = (int **)*puVar11;
            puVar11 = puVar11 + 1;
            pppiVar22 = pppiVar22 + 1;
          }
          appiStackY_2f8[1] = (int **)0x1;
          appiStackY_2f8[0] = (int **)0x1;
          local_4 = CONCAT31(local_4._1_3_,0x21);
          FUN_00466720();
          ppiStackY_2e0 = (int **)0x0;
          ppiStackY_2e4 = (int **)0x0;
          _DAT_005ddd70 = 142.0;
          _DAT_005ddd74 = 24.0;
          DAT_005ddd68 = 448.0;
          DAT_005ddd6c = pvStack_290;
          puVar11 = &DAT_005ddd68;
          pppiVar22 = appiStackY_2f8;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pppiVar22 = (int **)*puVar11;
            puVar11 = puVar11 + 1;
            pppiVar22 = pppiVar22 + 1;
          }
          FUN_00466a10();
          piVar7 = local_2ac;
          ppiStackY_2e0 = (int **)0xff;
          ppiStackY_2e4 = (int **)0xff;
          ppiStackY_2e8 = (int **)0x0;
          iStackY_2ec = (int)local_2ac;
          appiStackY_2f8[2] = (int **)0x455b94;
          FUN_00460720();
          iStackY_2ec = 0x455b9b;
          iStackY_2ec = FUN_004606f0();
          appiStackY_2f8[2] = (int **)0x455ba3;
          FUN_00466340();
          ppiStackY_2e0 = (int **)0x455bb0;
          (**(code **)(*piVar16 + 0x54))();
          ppiStackY_2e0 = (int **)0x455bbc;
          FUN_00467950();
          ppiStackY_2e0 = (int **)0x455bc8;
          FUN_00469170();
          ppiStackY_2e0 = (int **)0x455bcf;
          FUN_00469760();
          local_2ac = (int *)((int)piVar7 + 1);
          local_2b4 = local_2b4 + 0x18;
          piVar7 = local_2b0 + 1;
          local_2b0 = piVar7;
          piVar16 = (int *)FUN_00460710();
        } while (piVar7 != piVar16);
        if (0 < (int)local_2ac) {
          ppiStackY_2e0 = (int **)0x455c10;
          FUN_00465f10();
          ppiStackY_2e0 = (int **)0xff;
          ppiStackY_2e4 = (int **)0x0;
          ppiStackY_2e8 = (int **)0x455c27;
          FUN_00458210();
          ppiStackY_2e8 = (int **)0x455c2e;
          FUN_004666a0();
          *(undefined4 *)(*(int *)(param_1 + 0x278) + 0x74) = 1;
        }
      }
      local_4 = CONCAT31(local_4._1_3_,0x20);
      FUN_00402890();
      local_4 = 0xffffffff;
      FUN_004f8350();
    }
    ppiStackY_2e0 = (int **)s_game_name_005c7518;
    ppiStackY_2e4 = (int **)0x455c7a;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x455c81;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x455c88;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455c8f;
    FUN_00464240();
    ppiStackY_2e0 = (int **)s_autoswitch_005c74e8;
    ppiStackY_2e4 = (int **)0x455ca8;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x455caf;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x455cb6;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455cbd;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_friendfire_005c74f4;
    ppiStackY_2e4 = (int **)0x455cd6;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x455cdd;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x455ce4;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455ceb;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_healthitem_005c74dc;
    ppiStackY_2e4 = (int **)0x455d07;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x455d0e;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x455d15;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455d1c;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_hideitem_005c7500;
    ppiStackY_2e4 = (int **)0x455d35;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x455d3c;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x455d43;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455d4a;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_specialitem_005c74c4;
    ppiStackY_2e4 = (int **)0x455d66;
    FUN_00463010();
    ppiStackY_2e4 = (int **)0x455d6d;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x455d74;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455d7b;
    FUN_00458230();
LAB_00456132:
    ppiStackY_2e0 = (int **)s_updateitem_005c74d0;
    ppiStackY_2e4 = (int **)0x45613c;
    FUN_00463010();
LAB_0045613e:
    ppiStackY_2e4 = (int **)0x456143;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x45614a;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x456151;
    FUN_00458230();
    break;
  case 0x1f:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x456f98;
    FUN_00505f60();
  case 0x49:
    FUN_004591c0();
    break;
  case 0x35:
    if (param_3 == 1) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x4571b3;
      FUN_00505f60();
    }
    ppiStackY_2e0 = (int **)0x4571c7;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4571ce;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x154) = uVar8;
    break;
  case 0x36:
    if (param_3 == 1) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x45720a;
      FUN_00505f60();
    }
    ppiStackY_2e0 = (int **)0x45721e;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x457225;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x158) = uVar8;
    break;
  case 0x37:
    if (param_3 == 1) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x457261;
      FUN_00505f60();
    }
    ppiStackY_2e0 = (int **)0x457275;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x45727c;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x160) = uVar8;
    break;
  case 0x38:
    if (param_3 == 1) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x4572b7;
      FUN_00505f60();
    }
    ppiStackY_2e0 = (int **)0x4572cb;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x4572d2;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x164) = uVar8;
    break;
  case 0x39:
    if (param_3 == 1) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x45730e;
      FUN_00505f60();
    }
    ppiStackY_2e0 = (int **)0x457322;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x457329;
    FUN_004630b0();
    FUN_005565e0();
    FUN_004697f0();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x15c) = uVar8;
    break;
  case 0x3a:
    if (param_3 == 1) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x457365;
      FUN_00505f60();
    }
    ppiStackY_2e0 = (int **)0x457379;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x457380;
    FUN_004630b0();
    FUN_005565e0();
    fVar25 = (float10)FUN_004697f0();
    *(float *)(param_1 + 0xdc) = (float)(fVar25 * (float10)_DAT_005a84c8);
    break;
  case 0x3b:
    ppiStackY_2e0 = (int **)0x456b66;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x456b6d;
    FUN_004630b0();
    FUN_005565e0();
    iVar5 = FUN_00458210();
    if (iVar5 == 0) {
      ExceptionList = local_c;
      return 0;
    }
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x456b92;
    FUN_00463010();
    ppiStackY_2e0 = (int **)0x456b99;
    FUN_00570fd0();
    *(undefined4 *)(param_1 + 0x2dc) = 10;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x456bb2;
    FUN_00463010();
    ppiStackY_2e0 = (int **)0x456bb9;
    FUN_00570fd0();
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x456bce;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x7c) = uVar8;
    ppiStackY_2e0 = (int **)0x456beb;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x78) = uVar8;
    ppiStackY_2e0 = (int **)0x456c08;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x84) = uVar8;
    ppiStackY_2e0 = (int **)0x456c28;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x74) = uVar8;
    ppiStackY_2e0 = (int **)0x456c45;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    *(undefined4 *)(param_1 + 0x8c) = uVar8;
    ppiStackY_2e0 = (int **)0x456c65;
    FUN_004630b0();
    FUN_005565e0();
    uVar8 = FUN_00458220();
    pbVar17 = (byte *)(param_1 + 0x40);
    ppiStackY_2e0 = (int **)s_game_name_005c7518;
    *(undefined4 *)(param_1 + 0x88) = uVar8;
    ppiStackY_2e4 = (int **)0x456c89;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x456c90;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x456c97;
    FUN_00464220();
    pbVar6 = (byte *)&DAT_005d5a24;
    do {
      bVar2 = *pbVar17;
      bVar24 = bVar2 < *pbVar6;
      if (bVar2 != *pbVar6) {
LAB_00456cc4:
        iVar5 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
        goto LAB_00456cc9;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar17[1];
      bVar24 = bVar2 < pbVar6[1];
      if (bVar2 != pbVar6[1]) goto LAB_00456cc4;
      pbVar17 = pbVar17 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar2 != 0);
    iVar5 = 0;
LAB_00456cc9:
    if (iVar5 == 0) {
      pcVar9 = s_unname_005c7820;
      do {
        cVar1 = *pcVar9;
        pcVar9[param_1 + -0x5c77e0] = cVar1;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
    }
    ppiStackY_2e0 = (int **)s_password_005c4218;
    ppiStackY_2e4 = (int **)0x456cf1;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x456cf8;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x456cff;
    FUN_00464220();
    ppiStackY_2e0 = (int **)0x456d10;
    FUN_004630b0();
    FUN_005565e0();
    pcVar9 = (char *)FUN_0046b260();
    iVar5 = 3;
    bVar24 = true;
    pcVar18 = &DAT_005c7458;
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar24 = *pcVar9 == *pcVar18;
      pcVar9 = pcVar9 + 1;
      pcVar18 = pcVar18 + 1;
    } while (bVar24);
    if (bVar24) {
      *(undefined2 *)(param_1 + 0x6c) = 9999;
    }
    else {
      ppiStackY_2e0 = (int **)0x456d37;
      FUN_004630b0();
      FUN_005565e0();
      FUN_0046b260();
      ppiStackY_2e0 = (int **)0x456d4b;
      uVar4 = FUN_0050915b();
      *(undefined2 *)(param_1 + 0x6c) = uVar4;
    }
    ppiStackY_2e0 = (int **)0x456d66;
    FUN_004630b0();
    FUN_005565e0();
    FUN_0046b260();
    ppiStackY_2e0 = (int **)0x456d7a;
    uVar4 = FUN_0050915b();
    *(undefined2 *)(param_1 + 0x6e) = uVar4;
    ppiStackY_2e0 = (int **)0x456d8d;
    FUN_004630b0();
    FUN_005565e0();
    FUN_0046b260();
    ppiStackY_2e0 = (int **)0x1;
    ppiStackY_2e4 = (int **)0x456da3;
    uVar4 = FUN_004601b0();
    *(undefined2 *)(param_1 + 0x68) = uVar4;
    ppiStackY_2e0 = (int **)0x456db6;
    FUN_004630b0();
    FUN_005565e0();
    FUN_0046b260();
    ppiStackY_2e0 = (int **)0x456dca;
    uVar4 = FUN_0050915b();
    *(undefined2 *)(param_1 + 0x6a) = uVar4;
    ppiStackY_2e0 = (int **)0x456ddd;
    FUN_004630b0();
    FUN_005565e0();
    FUN_0046b260();
    ppiStackY_2e0 = (int **)0x456df1;
    FUN_0050a69a();
    uVar8 = __ftol();
    *(undefined4 *)(param_1 + 0x70) = uVar8;
    ppiStackY_2e0 = (int **)0x456e08;
    FUN_004630b0();
    FUN_005565e0();
    iVar5 = FUN_00458210();
    pbVar17 = local_240;
    for (iVar15 = 0xc; iVar15 != 0; iVar15 = iVar15 + -1) {
      pbVar17[0] = 0;
      pbVar17[1] = 0;
      pbVar17[2] = 0;
      pbVar17[3] = 0;
      pbVar17 = pbVar17 + 4;
    }
    pbVar17[0] = 0;
    pbVar17[1] = 0;
    if (*(int *)(param_1 + 0x10) != 0) {
      ppiStackY_2e0 = (int **)0x456e43;
      FUN_005005b0();
      local_4 = 0x28;
      ppiStackY_2e0 = (int **)0x456e5c;
      FUN_005005b0();
      local_4._0_1_ = 0x29;
      if (iVar5 != 0) {
        ppiStackY_2e0 = (int **)local_240;
        ppiStackY_2e4 = (int **)0x456e7d;
        FUN_004663c0();
        ppiStackY_2e4 = (int **)(int)*(short *)(param_1 + 0x68);
        ppiStackY_2e0 = &local_2a8;
        ppiStackY_2e8 = (int **)0x456e8f;
        (**(code **)(param_1 + 0x10))();
        iVar5 = FUN_004606f0();
        iVar15 = FUN_00460710();
        if (iVar5 != iVar15) {
          do {
            pbVar6 = (byte *)FUN_004606f0();
            pbVar17 = local_240;
            do {
              bVar2 = *pbVar17;
              bVar24 = bVar2 < *pbVar6;
              if (bVar2 != *pbVar6) {
LAB_00456ee0:
                iVar15 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
                goto LAB_00456ee5;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar17[1];
              bVar24 = bVar2 < pbVar6[1];
              if (bVar2 != pbVar6[1]) goto LAB_00456ee0;
              pbVar17 = pbVar17 + 2;
              pbVar6 = pbVar6 + 2;
            } while (bVar2 != 0);
            iVar15 = 0;
LAB_00456ee5:
            if (iVar15 == 0) {
              ppiStackY_2e0 = (int **)0x456f06;
              puVar10 = (undefined2 *)FUN_00460700();
              *(undefined2 *)(param_1 + 0x90) = *puVar10;
              break;
            }
            iVar5 = iVar5 + 0xc;
            iVar15 = FUN_00460710();
          } while (iVar5 != iVar15);
        }
      }
      local_4 = CONCAT31(local_4._1_3_,0x28);
      FUN_00402890();
      local_4 = 0xffffffff;
      FUN_004f8350();
    }
    FUN_0045a840();
    *(int *)(param_1 + 0x2e0) = (int)*(short *)(param_1 + 0x68);
    if (*(short *)(param_1 + 0x68) != 1) goto LAB_0045695a;
    ppiStackY_2e0 = (int **)0x456f62;
    FUN_00570fc0();
LAB_00456974:
    ppiStackY_2e0 = (int **)s_selectcancel_005c7774;
    ppiStackY_2e4 = (int **)0x456984;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x45698b;
    FUN_00570fc0();
LAB_004575d4:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x4575e2;
    FUN_00505f60();
    break;
  case 0x3c:
    *(undefined4 *)(param_1 + 0x2dc) = 4;
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x45616e;
    FUN_00505f60();
    break;
  case 0x3d:
  case 0x3e:
    FUN_004618d0();
    ppiStackY_2e0 = (int **)0x4570c0;
    (**(code **)(*param_5 + 0x54))();
    ppiStackY_2e0 = (int **)0x0;
    ppiStackY_2e4 = (int **)0x4570c9;
    (**(code **)(*param_5 + 0xc))();
    FUN_00460710();
    ppiStackY_2e0 = (int **)0x4570dc;
    FUN_00461f70();
    if (((*(int *)(param_1 + 0x2dc) == 3) && (param_2 == 0x3e)) && (DAT_005e0324 != 0)) {
      ppiStackY_2e0 = (int **)param_4;
      ppiStackY_2e4 = (int **)param_3;
      ppiStackY_2e8 = (int **)0x7d;
      iStackY_2ec = 0x45710e;
      FUN_004620e0();
    }
    if (((*(int *)(param_1 + 0x2dc) == 4) && (param_2 == 0x3e)) && (DAT_005e0324 != 0)) {
      ppiStackY_2e0 = (int **)param_4;
      ppiStackY_2e4 = (int **)param_3;
      ppiStackY_2e8 = (int **)0x7b;
      iStackY_2ec = 0x457143;
      FUN_004620e0();
    }
    break;
  case 0x40:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x4575f7;
    FUN_00505f60();
    *(undefined4 *)(param_1 + 0xe4) = 2;
    break;
  case 0x41:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x457617;
    FUN_00505f60();
    *(undefined4 *)(param_1 + 0xe4) = 1;
    break;
  case 0x42:
    ppiStackY_2e0 = (int **)DAT_005e0078;
    ppiStackY_2e4 = (int **)0x457637;
    FUN_00505f60();
    iVar5 = (**(code **)(param_1 + 0x18))();
    if (iVar5 == 9) {
      iVar5 = 10;
    }
    iVar15 = (*(int *)(param_1 + 0xe0) + 1) % (iVar5 + 10);
    *(int *)(param_1 + 0xe0) = iVar15;
    if (iVar15 == 0) {
      *(int *)(param_1 + 0xe0) = iVar5 + 10;
    }
    iVar5 = 0;
    local_2c8 = (int *)0x0;
    local_2a8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    local_2a4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2a0 = (int *)0x0;
    local_2bc = 0;
    local_29c = 0;
    local_2b8 = 0;
    local_298 = 0;
    do {
      cVar1 = (&DAT_005c792c)[iVar5];
      *(char *)((int)&local_2c8 + iVar5) = cVar1;
      iVar5 = iVar5 + 1;
    } while (cVar1 != '\0');
    goto LAB_0045771a;
  case 0x43:
    ppiStackY_2e0 = (int **)DAT_005e0078;
    ppiStackY_2e4 = (int **)0x4576af;
    FUN_00505f60();
    iVar5 = (**(code **)(param_1 + 0x18))();
    if (iVar5 == 9) {
      iVar5 = 10;
    }
    iVar15 = (iVar5 + 9 + *(int *)(param_1 + 0xe0)) % (iVar5 + 10);
    *(int *)(param_1 + 0xe0) = iVar15;
    if (iVar15 == 0) {
      *(int *)(param_1 + 0xe0) = iVar5 + 10;
    }
    iVar5 = 0;
    local_2c8 = (int *)0x0;
    local_2a8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    local_2a4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2a0 = (int *)0x0;
    local_2bc = 0;
    local_29c = 0;
    local_2b8 = 0;
    local_298 = 0;
    do {
      cVar1 = (&DAT_005c792c)[iVar5];
      *(char *)((int)&local_2c8 + iVar5) = cVar1;
      iVar5 = iVar5 + 1;
    } while (cVar1 != '\0');
LAB_0045771a:
    ppiStackY_2e4 = *(int ***)(param_1 + 0xe0);
    ppiStackY_2e0 = &local_2a8;
    ppiStackY_2e8 = (int **)0x45772d;
    FUN_0050aaa9();
    uVar13 = 0xffffffff;
    ppiVar20 = &local_2a8;
    do {
      ppiVar19 = ppiVar20;
      if (uVar13 == 0) break;
      uVar13 = uVar13 - 1;
      ppiVar19 = (int **)((int)ppiVar20 + 1);
      cVar1 = *(char *)ppiVar20;
      ppiVar20 = ppiVar19;
    } while (cVar1 != '\0');
    uVar13 = ~uVar13;
    iVar5 = -1;
    ppiVar20 = &local_2c8;
    do {
      ppiVar21 = ppiVar20;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      ppiVar21 = (int **)((int)ppiVar20 + 1);
      cVar1 = *(char *)ppiVar20;
      ppiVar20 = ppiVar21;
    } while (cVar1 != '\0');
    pcVar9 = (char *)((int)ppiVar19 - uVar13);
    pcVar18 = (char *)((int)ppiVar21 + -1);
    for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
      *(undefined4 *)pcVar18 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar18 = pcVar18 + 4;
    }
    for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
      *pcVar18 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      pcVar18 = pcVar18 + 1;
    }
    ppiStackY_2e0 = (int **)0x45776d;
    FUN_00463610();
    break;
  case 0x44:
    ppiStackY_2e0 = (int **)DAT_005e0078;
    ppiStackY_2e4 = (int **)0x457780;
    FUN_00505f60();
    iVar5 = (*(int *)(param_1 + 0xe8) + 1) % 0xc;
    *(int *)(param_1 + 0xe8) = iVar5;
    if (iVar5 == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xc;
    }
    iVar5 = 0;
    local_2c8 = (int *)0x0;
    local_2a8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    local_2a4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2a0 = (int *)0x0;
    local_2bc = 0;
    local_29c = 0;
    local_2b8 = 0;
    local_298 = 0;
    do {
      cVar1 = (&DAT_005c7930)[iVar5];
      *(char *)((int)&local_2c8 + iVar5) = cVar1;
      iVar5 = iVar5 + 1;
    } while (cVar1 != '\0');
    goto LAB_0045784c;
  case 0x45:
    ppiStackY_2e0 = (int **)DAT_005e0078;
    ppiStackY_2e4 = (int **)0x4577ed;
    FUN_00505f60();
    iVar5 = (*(int *)(param_1 + 0xe8) + 0xb) % 0xc;
    *(int *)(param_1 + 0xe8) = iVar5;
    if (iVar5 == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xc;
    }
    iVar5 = 0;
    local_2c8 = (int *)0x0;
    local_2a8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    local_2a4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2a0 = (int *)0x0;
    local_2bc = 0;
    local_29c = 0;
    local_2b8 = 0;
    local_298 = 0;
    do {
      cVar1 = (&DAT_005c7930)[iVar5];
      *(char *)((int)&local_2c8 + iVar5) = cVar1;
      iVar5 = iVar5 + 1;
    } while (cVar1 != '\0');
LAB_0045784c:
    ppiStackY_2e4 = *(int ***)(param_1 + 0xe8);
    ppiStackY_2e0 = &local_2a8;
    ppiStackY_2e8 = (int **)0x45785f;
    FUN_0050aaa9();
    uVar13 = 0xffffffff;
    ppiVar20 = &local_2a8;
    do {
      ppiVar19 = ppiVar20;
      if (uVar13 == 0) break;
      uVar13 = uVar13 - 1;
      ppiVar19 = (int **)((int)ppiVar20 + 1);
      cVar1 = *(char *)ppiVar20;
      ppiVar20 = ppiVar19;
    } while (cVar1 != '\0');
    uVar13 = ~uVar13;
    iVar5 = -1;
    ppiVar20 = &local_2c8;
    do {
      ppiVar21 = ppiVar20;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      ppiVar21 = (int **)((int)ppiVar20 + 1);
      cVar1 = *(char *)ppiVar20;
      ppiVar20 = ppiVar21;
    } while (cVar1 != '\0');
    pcVar9 = (char *)((int)ppiVar19 - uVar13);
    pcVar18 = (char *)((int)ppiVar21 + -1);
    for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
      *(undefined4 *)pcVar18 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar18 = pcVar18 + 4;
    }
    for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
      *pcVar18 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      pcVar18 = pcVar18 + 1;
    }
    ppiStackY_2e0 = (int **)0x45789f;
    FUN_00463610();
    break;
  case 0x46:
  case 0x47:
  case 0x60:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x4561a3;
    FUN_00505f60();
    *(undefined4 *)(param_1 + 0x2dc) = 1;
    break;
  case 0x4a:
  case 0x4b:
    if (param_3 == 0xff00) {
      FUN_004618d0();
      ppiStackY_2e0 = (int **)0x4578dd;
      FUN_00463070();
      ppiStackY_2e0 = (int **)0x4578ef;
      FUN_00461f70();
      ppiStackY_2e0 = (int **)0x4578fc;
      (**(code **)(**(int **)(param_1 + 0x2c4) + 0x58))();
      *(int *)(param_1 + 0x2e0) = param_4;
      if (param_4 == 1) {
        ppiStackY_2e0 = (int **)0x457920;
        FUN_00570fc0();
      }
      else {
        ppiStackY_2e0 = (int **)0x45794e;
        FUN_00570fc0();
      }
      ppiStackY_2e0 = (int **)s_selectcancel_005c7774;
      ppiStackY_2e4 = (int **)0x457973;
      FUN_004630b0();
      ppiStackY_2e0 = (int **)0x45797a;
      FUN_00570fc0();
      FUN_0044f110();
      if (param_2 == 0x4a) {
        *(undefined4 *)(param_1 + 0x2dc) = 9;
        if (DAT_005e0324 != 0) {
          ppiStackY_2e0 = (int **)param_4;
          ppiStackY_2e4 = (int **)0xff00;
          ppiStackY_2e8 = (int **)0x7c;
          iStackY_2ec = 0x4579b3;
          FUN_004620e0();
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x2dc) = 8;
        if (DAT_005e0324 != 0) {
          ppiStackY_2e0 = (int **)param_4;
          ppiStackY_2e4 = (int **)0xff00;
          ppiStackY_2e8 = (int **)0x7a;
          iStackY_2ec = 0x4579e5;
          FUN_004620e0();
        }
      }
    }
    else {
      puVar11 = &local_27c;
      for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined2 *)puVar11 = 0;
      switch(param_3) {
      case 0xff01:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dca54 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 0xff02:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dca20 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 0xff03:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dccb4 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 0xff04:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dca88 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 0xff05:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dcedc + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 0xff06:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005ddf1c + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 0xff07:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005db864 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      default:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dd104 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
      }
      ppiStackY_2e0 = (int **)0x457ab8;
      FUN_0046b860();
      ppiStackY_2e0 = (int **)0x457ac5;
      FUN_0046b560();
    }
    break;
  case 0x4e:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x455251;
    FUN_00505f60();
    *(undefined4 *)(param_1 + 0xe4) = 0;
    if (*(int *)(param_1 + 0x32c) != 0) {
      *(undefined4 *)(param_1 + 0x32c) = 0;
      *(undefined4 *)(param_1 + 0x2dc) = 1;
      FUN_0044da70();
      ppiStackY_2e0 = (int **)0x455287;
      (**(code **)(**(int **)(param_1 + 0x2a0) + 0x58))();
      ppiStackY_2e0 = (int **)0x0;
      ppiStackY_2e4 = (int **)0x455296;
      (**(code **)(**(int **)(param_1 + 0x2a4) + 0x58))();
      ExceptionList = local_c;
      return 1;
    }
    if (*(int *)(param_1 + 0x2dc) == 8) {
      *(undefined4 *)(param_1 + 0x2dc) = 4;
    }
    if (*(int *)(param_1 + 0x2dc) == 9) {
      *(undefined4 *)(param_1 + 0x2dc) = 3;
    }
    if (*(int *)(param_1 + 0x2dc) == 10) {
      *(undefined4 *)(param_1 + 0x2dc) = 6;
      if ((*(int *)(param_1 + 0x278) != 0) && (FUN_00468f20(), *(int *)(param_1 + 0x10) != 0)) {
        ppiStackY_2e0 = (int **)0x455302;
        FUN_005005b0();
        local_4 = 0x1a;
        ppiStackY_2e0 = (int **)0x45531b;
        FUN_005005b0();
        ppiStackY_2e4 = (int **)(int)*(short *)(param_1 + 0x68);
        ppiStackY_2e0 = &local_2c8;
        local_4 = CONCAT31(local_4._1_3_,0x1b);
        ppiStackY_2e8 = (int **)0x455335;
        (**(code **)(param_1 + 0x10))();
        piVar16 = (int *)FUN_004606f0();
        local_2ac = (int *)0x0;
        local_2b0 = piVar16;
        piVar7 = (int *)FUN_00460710();
        if (piVar16 != piVar7) {
          local_2b4 = 0x6f;
          do {
            ppiStackY_2e0 = (int **)0x45536b;
            pvStack_290 = operator_new(0x50);
            local_4 = CONCAT31(local_4._1_3_,0x1c);
            if (pvStack_290 == (void *)0x0) {
              piVar16 = (int *)0x0;
            }
            else {
              piVar16 = (int *)FUN_00465610();
            }
            DAT_005ddd6c = (void *)(float)local_2b4;
            _DAT_005ddd70 = 172.0;
            _DAT_005ddd74 = 24.0;
            DAT_005ddd68 = 433.0;
            puVar11 = &DAT_005ddd68;
            pppiVar22 = appiStackY_2f8 + 2;
            pvStack_290 = DAT_005ddd6c;
            for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pppiVar22 = (int **)*puVar11;
              puVar11 = puVar11 + 1;
              pppiVar22 = pppiVar22 + 1;
            }
            appiStackY_2f8[1] = (int **)0x1;
            appiStackY_2f8[0] = (int **)0x1;
            local_4 = CONCAT31(local_4._1_3_,0x1b);
            FUN_00466720();
            ppiStackY_2e0 = (int **)0x0;
            ppiStackY_2e4 = (int **)0x0;
            _DAT_005ddd70 = 142.0;
            _DAT_005ddd74 = 24.0;
            DAT_005ddd68 = 448.0;
            DAT_005ddd6c = pvStack_290;
            puVar11 = &DAT_005ddd68;
            pppiVar22 = appiStackY_2f8;
            for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pppiVar22 = (int **)*puVar11;
              puVar11 = puVar11 + 1;
              pppiVar22 = pppiVar22 + 1;
            }
            FUN_00466a10();
            piVar7 = local_2ac;
            ppiStackY_2e0 = (int **)0xff;
            ppiStackY_2e4 = (int **)0xff;
            ppiStackY_2e8 = (int **)0x0;
            iStackY_2ec = (int)local_2ac;
            appiStackY_2f8[2] = (int **)0x455442;
            FUN_00460720();
            iStackY_2ec = 0x455449;
            iStackY_2ec = FUN_004606f0();
            appiStackY_2f8[2] = (int **)0x455451;
            FUN_00466340();
            ppiStackY_2e0 = (int **)0x45545f;
            (**(code **)(*piVar16 + 0x54))();
            ppiStackY_2e0 = (int **)0x45546b;
            FUN_00467950();
            ppiStackY_2e0 = (int **)0x455477;
            FUN_00469170();
            ppiStackY_2e0 = (int **)0x45547e;
            FUN_00469760();
            local_2ac = (int *)((int)piVar7 + 1);
            local_2b4 = local_2b4 + 0x18;
            piVar7 = local_2b0 + 1;
            local_2b0 = piVar7;
            piVar16 = (int *)FUN_00460710();
          } while (piVar7 != piVar16);
          if (0 < (int)local_2ac) {
            ppiStackY_2e0 = (int **)0x4554bf;
            FUN_00465f10();
            ppiStackY_2e0 = (int **)0xff;
            ppiStackY_2e4 = (int **)0x0;
            ppiStackY_2e8 = (int **)0x4554d6;
            FUN_00458210();
            ppiStackY_2e8 = (int **)0x4554dd;
            FUN_004666a0();
            *(undefined4 *)(*(int *)(param_1 + 0x278) + 0x74) = 1;
          }
        }
        local_4 = CONCAT31(local_4._1_3_,0x1a);
        FUN_00402890();
        local_4 = 0xffffffff;
        FUN_004f8350();
      }
      ppiStackY_2e0 = (int **)s_game_name_005c7518;
      ppiStackY_2e4 = (int **)0x455528;
      FUN_004630b0();
      ppiStackY_2e0 = (int **)0x45552f;
      FUN_005565e0();
      ppiStackY_2e0 = (int **)0x455536;
      FUN_00464240();
      ppiStackY_2e0 = (int **)s_autoswitch_005c74e8;
      ppiStackY_2e4 = (int **)0x455552;
      FUN_004630b0();
      ppiStackY_2e0 = (int **)0x455559;
      FUN_005565e0();
      ppiStackY_2e0 = (int **)0x455560;
      FUN_00458230();
      ppiStackY_2e0 = (int **)s_friendfire_005c74f4;
      ppiStackY_2e4 = (int **)0x45557c;
      FUN_004630b0();
      ppiStackY_2e0 = (int **)0x455583;
      FUN_005565e0();
      ppiStackY_2e0 = (int **)0x45558a;
      FUN_00458230();
      ppiStackY_2e0 = (int **)s_healthitem_005c74dc;
      ppiStackY_2e4 = (int **)0x4555a9;
      FUN_004630b0();
      ppiStackY_2e0 = (int **)0x4555b0;
      FUN_005565e0();
      ppiStackY_2e0 = (int **)0x4555b7;
      FUN_00458230();
      ppiStackY_2e0 = (int **)s_hideitem_005c7500;
      ppiStackY_2e4 = (int **)0x4555d3;
      FUN_004630b0();
      ppiStackY_2e0 = (int **)0x4555da;
      FUN_005565e0();
      ppiStackY_2e0 = (int **)0x4555e1;
      FUN_00458230();
      ppiStackY_2e0 = (int **)s_specialitem_005c74c4;
      ppiStackY_2e4 = (int **)0x455600;
      FUN_004630b0();
      ppiStackY_2e0 = (int **)0x455607;
      FUN_005565e0();
      ppiStackY_2e0 = (int **)0x45560e;
      FUN_00458230();
      ppiStackY_2e0 = (int **)s_updateitem_005c74d0;
      ppiStackY_2e4 = (int **)0x45562d;
      FUN_004630b0();
      ppiStackY_2e0 = (int **)0x455634;
      FUN_005565e0();
      ppiStackY_2e0 = (int **)0x45563b;
      FUN_00458230();
    }
    if (*(int *)(param_1 + 0x2dc) != 0xb) {
      ExceptionList = local_c;
      return 1;
    }
    *(undefined4 *)(param_1 + 0x2dc) = 7;
    if ((*(int *)(param_1 + 0x274) != 0) && (FUN_00468f20(), *(int *)(param_1 + 0x10) != 0)) {
      ppiStackY_2e0 = (int **)0x45567c;
      FUN_005005b0();
      local_4 = 0x1d;
      ppiStackY_2e0 = (int **)0x455695;
      FUN_005005b0();
      ppiStackY_2e4 = (int **)(int)*(short *)(param_1 + 0x68);
      ppiStackY_2e0 = &local_2c8;
      local_4 = CONCAT31(local_4._1_3_,0x1e);
      ppiStackY_2e8 = (int **)0x4556af;
      (**(code **)(param_1 + 0x10))();
      piVar16 = (int *)FUN_004606f0();
      local_2ac = (int *)0x0;
      local_2b0 = piVar16;
      piVar7 = (int *)FUN_00460710();
      if (piVar16 != piVar7) {
        local_2b4 = 0x6f;
        do {
          ppiStackY_2e0 = (int **)0x4556e5;
          pvStack_290 = operator_new(0x50);
          local_4 = CONCAT31(local_4._1_3_,0x1f);
          if (pvStack_290 == (void *)0x0) {
            piVar16 = (int *)0x0;
          }
          else {
            piVar16 = (int *)FUN_00465610();
          }
          DAT_005ddd6c = (void *)(float)local_2b4;
          _DAT_005ddd70 = 172.0;
          _DAT_005ddd74 = 24.0;
          DAT_005ddd68 = 433.0;
          puVar11 = &DAT_005ddd68;
          pppiVar22 = appiStackY_2f8 + 2;
          pvStack_290 = DAT_005ddd6c;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pppiVar22 = (int **)*puVar11;
            puVar11 = puVar11 + 1;
            pppiVar22 = pppiVar22 + 1;
          }
          appiStackY_2f8[1] = (int **)0x1;
          appiStackY_2f8[0] = (int **)0x1;
          local_4 = CONCAT31(local_4._1_3_,0x1e);
          FUN_00466720();
          ppiStackY_2e0 = (int **)0x0;
          ppiStackY_2e4 = (int **)0x0;
          _DAT_005ddd70 = 142.0;
          _DAT_005ddd74 = 24.0;
          DAT_005ddd68 = 448.0;
          DAT_005ddd6c = pvStack_290;
          puVar11 = &DAT_005ddd68;
          pppiVar22 = appiStackY_2f8;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pppiVar22 = (int **)*puVar11;
            puVar11 = puVar11 + 1;
            pppiVar22 = pppiVar22 + 1;
          }
          FUN_00466a10();
          piVar7 = local_2ac;
          ppiStackY_2e0 = (int **)0xff;
          ppiStackY_2e4 = (int **)0xff;
          ppiStackY_2e8 = (int **)0x0;
          iStackY_2ec = (int)local_2ac;
          appiStackY_2f8[2] = (int **)0x4557bb;
          FUN_00460720();
          iStackY_2ec = 0x4557c2;
          iStackY_2ec = FUN_004606f0();
          appiStackY_2f8[2] = (int **)0x4557ca;
          FUN_00466340();
          ppiStackY_2e0 = (int **)0x4557d7;
          (**(code **)(*piVar16 + 0x54))();
          ppiStackY_2e0 = (int **)0x4557e3;
          FUN_00467950();
          ppiStackY_2e0 = (int **)0x4557ef;
          FUN_00469170();
          ppiStackY_2e0 = (int **)0x4557f6;
          FUN_00469760();
          local_2ac = (int *)((int)piVar7 + 1);
          local_2b4 = local_2b4 + 0x18;
          piVar7 = local_2b0 + 1;
          local_2b0 = piVar7;
          piVar16 = (int *)FUN_00460710();
        } while (piVar7 != piVar16);
        if (0 < (int)local_2ac) {
          ppiStackY_2e0 = (int **)0x455837;
          FUN_00465f10();
          ppiStackY_2e0 = (int **)0xff;
          ppiStackY_2e4 = (int **)0x0;
          ppiStackY_2e8 = (int **)0x45584e;
          FUN_00458210();
          ppiStackY_2e8 = (int **)0x455855;
          FUN_004666a0();
          *(undefined4 *)(*(int *)(param_1 + 0x274) + 0x74) = 1;
        }
      }
      local_4 = CONCAT31(local_4._1_3_,0x1d);
      FUN_00402890();
      local_4 = 0xffffffff;
      FUN_004f8350();
    }
    ppiStackY_2e0 = (int **)s_game_name_005c7518;
    ppiStackY_2e4 = (int **)0x4558a0;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x4558a7;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x4558ae;
    FUN_00464240();
    ppiStackY_2e0 = (int **)s_autoswitch_005c74e8;
    ppiStackY_2e4 = (int **)0x4558ca;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x4558d1;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x4558d8;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_friendfire_005c74f4;
    ppiStackY_2e4 = (int **)0x4558f4;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x4558fb;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455902;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_healthitem_005c74dc;
    ppiStackY_2e4 = (int **)0x455921;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x455928;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x45592f;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_hideitem_005c7500;
    ppiStackY_2e4 = (int **)0x45594b;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x455952;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455959;
    FUN_00458230();
    ppiStackY_2e0 = (int **)s_specialitem_005c74c4;
    ppiStackY_2e4 = (int **)0x455978;
    FUN_004630b0();
    ppiStackY_2e0 = (int **)0x45597f;
    FUN_005565e0();
    ppiStackY_2e0 = (int **)0x455986;
    FUN_00458230();
    if (*(int *)(param_1 + 0x88) == 0) {
      ppiStackY_2e0 = (int **)s_updateitem_005c74d0;
    }
    else {
      ppiStackY_2e0 = (int **)s_updateitem_005c74d0;
    }
    goto LAB_0045613e;
  case 0x50:
    if (param_3 == 0) {
      *(undefined4 *)(param_1 + 0x2dc) = 4;
      FUN_004618d0();
      ppiStackY_2e0 = (int **)0x457c49;
      FUN_00463070();
      ppiStackY_2e0 = (int **)0x457c5b;
      FUN_00461f70();
      ppiStackY_2e0 = (int **)0x457c68;
      (**(code **)(**(int **)(param_1 + 0x2c4) + 0x58))();
      FUN_0044f110();
      FUN_004591c0();
    }
    else {
      local_27c = (int *)0x0;
      local_278 = 0;
      local_274 = 0;
      local_270 = 0;
      local_26c = 0;
      switch(param_3) {
      case 1:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dbf14 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 2:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dde18 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 3:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005dde80 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 4:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005ddee8 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 5:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005ddd34 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        break;
      case 6:
        iVar5 = 0;
        do {
          cVar1 = *(char *)((int)&DAT_005ddf50 + iVar5);
          *(char *)((int)&local_27c + iVar5) = cVar1;
          iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
      }
      ppiStackY_2e0 = (int **)0x457d1e;
      FUN_0046b860();
    }
    break;
  case 0x53:
    if ((param_3 == 1) || (param_3 == 2)) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x45515c;
      FUN_00505f60();
      puVar11 = &local_27c;
      for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined2 *)puVar11 = 0;
      FUN_005565e0();
      iVar5 = FUN_00458210();
      if (iVar5 != 0) {
        ppiStackY_2e0 = (int **)&local_27c;
        ppiStackY_2e4 = (int **)0x455199;
        FUN_005565e0();
        ppiStackY_2e4 = (int **)0x4551a0;
        FUN_00458210();
        ppiStackY_2e4 = (int **)0x4551a7;
        FUN_004663c0();
        FUN_005565e0();
        ppiStackY_2e0 = (int **)&local_27c;
        ppiStackY_2e4 = (int **)0x4551bb;
        FUN_0044fd90();
        *(undefined4 *)(param_1 + 0x2e4) = 0;
        FUN_005565e0();
        FUN_00467240();
        iVar5 = FUN_005565e0();
        *(undefined4 *)(iVar5 + 0x74) = 1;
        pbVar17 = local_240;
        for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
          pbVar17[0] = 0;
          pbVar17[1] = 0;
          pbVar17[2] = 0;
          pbVar17[3] = 0;
          pbVar17 = pbVar17 + 4;
        }
        pbVar17[0] = 0;
        pbVar17[1] = 0;
        ppiStackY_2e0 = (int **)local_240;
        ppiStackY_2e4 = (int **)0x455204;
        FUN_005565e0();
        ppiStackY_2e4 = (int **)0x45520b;
        FUN_00458210();
        ppiStackY_2e4 = (int **)0x455212;
        FUN_004663c0();
        ppiStackY_2e0 = (int **)0xff;
        ppiStackY_2e4 = (int **)0x0;
        iStackY_2ec = (int)local_240;
        ppiStackY_2e8 = (int **)0x1;
        appiStackY_2f8[2] = (int **)0x45522f;
        FUN_005565e0();
        appiStackY_2f8[2] = (int **)0x455236;
        FUN_00458210();
        appiStackY_2f8[2] = (int **)0x45523d;
        FUN_00466340();
      }
    }
    break;
  case 0x54:
    if ((*(int *)(param_1 + 0x274) != 0) && (param_3 == 1)) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x454b7f;
      FUN_00505f60();
      FUN_00468f20();
      if (*(int *)(param_1 + 0x10) != 0) {
        local_2a8 = (int *)0x0;
        local_2a4 = (int *)0x0;
        local_2a0 = (int *)0x0;
        local_4 = 0;
        local_2c8 = (int *)0x0;
        local_2c4 = (int *)0x0;
        local_2c0 = (int *)0x0;
        puVar11 = &local_27c;
        for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar11 = 0;
          puVar11 = puVar11 + 1;
        }
        local_4 = CONCAT31(local_4._1_3_,0x14);
        *(undefined2 *)puVar11 = 0;
        iVar5 = FUN_005565e0();
        if (*(int *)(*(int *)(iVar5 + 8) + 0x44) != 0) {
          FUN_005565e0();
          ppiStackY_2e0 = (int **)&local_27c;
          ppiStackY_2e4 = (int **)0x454c04;
          FUN_004663c0();
          ppiStackY_2e0 = (int **)0x1;
          ppiStackY_2e4 = (int **)0x454c10;
          sVar3 = FUN_004601b0();
          iStackY_2ec = (int)sVar3;
          ppiStackY_2e4 = &local_2c8;
          ppiStackY_2e8 = &local_2a8;
          appiStackY_2f8[2] = (int **)0x454c21;
          (**(code **)(param_1 + 0x10))();
          local_294 = local_2a8;
          local_2ac = (int *)0x0;
          if (local_2a8 != local_2a4) {
            local_2b0 = (int *)0x0;
            local_2b4 = 0x6f;
            do {
              ppiStackY_2e0 = (int **)0x454c53;
              pvStack_290 = operator_new(0x50);
              local_4 = CONCAT31(local_4._1_3_,0x15);
              if (pvStack_290 == (void *)0x0) {
                piVar16 = (int *)0x0;
              }
              else {
                piVar16 = (int *)FUN_00465610();
              }
              DAT_005ddd6c = (void *)(float)local_2b4;
              _DAT_005ddd70 = 172.0;
              _DAT_005ddd74 = 24.0;
              DAT_005ddd68 = 433.0;
              puVar11 = &DAT_005ddd68;
              pppiVar22 = appiStackY_2f8 + 2;
              pvStack_290 = DAT_005ddd6c;
              for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pppiVar22 = (int **)*puVar11;
                puVar11 = puVar11 + 1;
                pppiVar22 = pppiVar22 + 1;
              }
              appiStackY_2f8[1] = (int **)0x1;
              appiStackY_2f8[0] = (int **)0x1;
              local_4 = CONCAT31(local_4._1_3_,0x14);
              FUN_00466720();
              ppiStackY_2e0 = (int **)0x0;
              ppiStackY_2e4 = (int **)0x0;
              _DAT_005ddd70 = 142.0;
              _DAT_005ddd74 = 24.0;
              DAT_005ddd68 = 448.0;
              DAT_005ddd6c = pvStack_290;
              puVar11 = &DAT_005ddd68;
              pppiVar22 = appiStackY_2f8;
              for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pppiVar22 = (int **)*puVar11;
                puVar11 = puVar11 + 1;
                pppiVar22 = pppiVar22 + 1;
              }
              FUN_00466a10();
              piVar7 = local_2b0;
              ppiStackY_2e0 = (int **)0xff;
              iStackY_2ec = *(int *)((int)local_2b0 + (int)local_2c8);
              ppiStackY_2e4 = (int **)0xff;
              ppiStackY_2e8 = (int **)0x0;
              appiStackY_2f8[2] = (int **)0x454d2e;
              FUN_00466340();
              ppiStackY_2e0 = (int **)0x454d3b;
              (**(code **)(*piVar16 + 0x54))();
              ppiStackY_2e0 = (int **)0x454d47;
              FUN_00467950();
              ppiStackY_2e0 = (int **)0x454d53;
              FUN_00469170();
              ppiStackY_2e0 = (int **)0x454d5a;
              FUN_00469760();
              local_2ac = (int *)((int)local_2ac + 1);
              local_294 = local_294 + 1;
              local_2b4 = local_2b4 + 0x18;
              local_2b0 = piVar7 + 3;
            } while (local_294 != local_2a4);
            if (0 < (int)local_2ac) {
              ppiStackY_2e0 = (int **)0x454da1;
              FUN_00465f10();
              ppiStackY_2e0 = (int **)0xff;
              ppiStackY_2e4 = (int **)0x0;
              ppiStackY_2e8 = (int **)0x454dbb;
              FUN_004666a0();
              *(undefined4 *)(*(int *)(param_1 + 0x274) + 0x74) = 1;
            }
          }
        }
        piVar7 = local_2c4;
        local_4._0_1_ = 0x16;
        for (piVar16 = local_2c8; piVar16 != piVar7; piVar16 = piVar16 + 3) {
          FUN_004026e0();
        }
        local_4 = CONCAT31(local_4._1_3_,0x13);
        if (((int)local_2c0 - (int)local_2c8) / 0xc != 0) {
          ppiStackY_2e4 = (int **)0x454e1d;
          ppiStackY_2e0 = (int **)local_2c8;
          FUN_00402e90();
        }
        piVar16 = local_2a8;
        iVar5 = (int)local_2a0 - (int)local_2a8 >> 2;
        if (iVar5 != 0) {
          uVar13 = iVar5 * 4;
          if (uVar13 < 0x81) {
            FUN_00402330();
            *piVar16 = *(int *)(&DAT_005d59a4 + (uVar13 + 7 >> 3) * 4);
            *(int **)(&DAT_005d59a4 + (uVar13 + 7 >> 3) * 4) = piVar16;
            DAT_005d59e8 = 0;
          }
          else {
            ppiStackY_2e0 = (int **)0x454e43;
            FUN_005089fd();
          }
        }
      }
    }
    break;
  case 0x55:
    if ((*(int *)(param_1 + 0x278) != 0) && (param_3 == 1)) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x454e9c;
      FUN_00505f60();
      FUN_00468f20();
      if (*(int *)(param_1 + 0x10) != 0) {
        ppiStackY_2e0 = (int **)0x454ec3;
        FUN_005005b0();
        local_4 = 0x17;
        ppiStackY_2e0 = (int **)0x454edc;
        FUN_005005b0();
        puVar11 = &local_27c;
        for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar11 = 0;
          puVar11 = puVar11 + 1;
        }
        local_4 = CONCAT31(local_4._1_3_,0x18);
        *(undefined2 *)puVar11 = 0;
        FUN_005565e0();
        FUN_004fa640();
        iVar5 = FUN_00458210();
        if (iVar5 != 0) {
          ppiStackY_2e0 = (int **)&local_27c;
          ppiStackY_2e4 = (int **)0x454f25;
          FUN_005565e0();
          ppiStackY_2e4 = (int **)0x454f2c;
          FUN_004fa640();
          ppiStackY_2e4 = (int **)0x454f33;
          FUN_00458210();
          ppiStackY_2e4 = (int **)0x454f3a;
          FUN_004663c0();
          ppiStackY_2e0 = (int **)0x1;
          ppiStackY_2e4 = (int **)0x454f46;
          sVar3 = FUN_004601b0();
          iStackY_2ec = (int)sVar3;
          ppiStackY_2e4 = &local_2a8;
          ppiStackY_2e8 = &local_2c8;
          appiStackY_2f8[2] = (int **)0x454f57;
          (**(code **)(param_1 + 0x10))();
          piVar16 = (int *)FUN_004606f0();
          local_2ac = (int *)0x0;
          local_2b0 = piVar16;
          piVar7 = (int *)FUN_00460710();
          if (piVar16 != piVar7) {
            local_2b4 = 0x6f;
            do {
              ppiStackY_2e0 = (int **)0x454f91;
              pvStack_290 = operator_new(0x50);
              local_4 = CONCAT31(local_4._1_3_,0x19);
              if (pvStack_290 == (void *)0x0) {
                piVar16 = (int *)0x0;
              }
              else {
                piVar16 = (int *)FUN_00465610();
              }
              DAT_005ddd6c = (void *)(float)local_2b4;
              _DAT_005ddd70 = 172.0;
              _DAT_005ddd74 = 24.0;
              DAT_005ddd68 = 433.0;
              puVar11 = &DAT_005ddd68;
              pppiVar22 = appiStackY_2f8 + 2;
              pvStack_290 = DAT_005ddd6c;
              for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pppiVar22 = (int **)*puVar11;
                puVar11 = puVar11 + 1;
                pppiVar22 = pppiVar22 + 1;
              }
              appiStackY_2f8[1] = (int **)0x1;
              appiStackY_2f8[0] = (int **)0x1;
              local_4 = CONCAT31(local_4._1_3_,0x18);
              FUN_00466720();
              ppiStackY_2e0 = (int **)0x0;
              ppiStackY_2e4 = (int **)0x0;
              _DAT_005ddd70 = 142.0;
              _DAT_005ddd74 = 24.0;
              DAT_005ddd68 = 448.0;
              DAT_005ddd6c = pvStack_290;
              puVar11 = &DAT_005ddd68;
              pppiVar22 = appiStackY_2f8;
              for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pppiVar22 = (int **)*puVar11;
                puVar11 = puVar11 + 1;
                pppiVar22 = pppiVar22 + 1;
              }
              FUN_00466a10();
              piVar7 = local_2ac;
              ppiStackY_2e0 = (int **)0xff;
              ppiStackY_2e4 = (int **)0xff;
              ppiStackY_2e8 = (int **)0x0;
              iStackY_2ec = (int)local_2ac;
              appiStackY_2f8[2] = (int **)0x455068;
              FUN_00460720();
              iStackY_2ec = 0x45506f;
              iStackY_2ec = FUN_004606f0();
              appiStackY_2f8[2] = (int **)0x455077;
              FUN_00466340();
              ppiStackY_2e0 = (int **)0x455085;
              (**(code **)(*piVar16 + 0x54))();
              ppiStackY_2e0 = (int **)0x455091;
              FUN_00467950();
              ppiStackY_2e0 = (int **)0x45509d;
              FUN_00469170();
              ppiStackY_2e0 = (int **)0x4550a4;
              FUN_00469760();
              local_2ac = (int *)((int)piVar7 + 1);
              local_2b4 = local_2b4 + 0x18;
              piVar7 = local_2b0 + 1;
              local_2b0 = piVar7;
              piVar16 = (int *)FUN_00460710();
            } while (piVar7 != piVar16);
            if (0 < (int)local_2ac) {
              ppiStackY_2e0 = (int **)0x4550e5;
              FUN_00465f10();
              ppiStackY_2e0 = (int **)0xff;
              ppiStackY_2e4 = (int **)0x0;
              ppiStackY_2e8 = (int **)0x4550fc;
              FUN_00458210();
              ppiStackY_2e8 = (int **)0x455103;
              FUN_004666a0();
              *(undefined4 *)(*(int *)(param_1 + 0x278) + 0x74) = 1;
            }
          }
        }
        local_4 = CONCAT31(local_4._1_3_,0x17);
        FUN_00402890();
        local_4 = 0xffffffff;
        FUN_004f8350();
      }
    }
    break;
  case 0x56:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x454b20;
    FUN_00505f60();
    iVar5 = FUN_00463010();
    if (iVar5 != *(int *)(param_1 + 0x2a0)) {
      ppiStackY_2e0 = (int **)0x0;
      ppiStackY_2e4 = (int **)0x0;
      ppiStackY_2e8 = (int **)0x4e;
      iStackY_2ec = 0x454b4f;
      FUN_004620e0();
    }
    break;
  case 0x58:
    ppiStackY_2e4 = *(int ***)(param_1 + 0xe8);
    if ((0 < (int)ppiStackY_2e4) && ((int)ppiStackY_2e4 < 0xc)) {
      iVar5 = 0;
      local_2c8 = (int *)0x0;
      local_2a8 = (int *)0x0;
      local_2c4 = (int *)0x0;
      local_2a4 = (int *)0x0;
      local_2c0 = (int *)0x0;
      local_2a0 = (int *)0x0;
      local_2bc = 0;
      local_29c = 0;
      local_2b8 = 0;
      local_298 = 0;
      do {
        cVar1 = (&DAT_005c7930)[iVar5];
        *(char *)((int)&local_2c8 + iVar5) = cVar1;
        iVar5 = iVar5 + 1;
      } while (cVar1 != '\0');
      ppiStackY_2e0 = &local_2a8;
      ppiStackY_2e8 = (int **)0x454aad;
      FUN_0050aaa9();
      uVar13 = 0xffffffff;
      ppiVar20 = &local_2a8;
      do {
        ppiVar19 = ppiVar20;
        if (uVar13 == 0) break;
        uVar13 = uVar13 - 1;
        ppiVar19 = (int **)((int)ppiVar20 + 1);
        cVar1 = *(char *)ppiVar20;
        ppiVar20 = ppiVar19;
      } while (cVar1 != '\0');
      uVar13 = ~uVar13;
      iVar5 = -1;
      ppiVar20 = &local_2c8;
      do {
        ppiVar21 = ppiVar20;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        ppiVar21 = (int **)((int)ppiVar20 + 1);
        cVar1 = *(char *)ppiVar20;
        ppiVar20 = ppiVar21;
      } while (cVar1 != '\0');
      pcVar9 = (char *)((int)ppiVar19 - uVar13);
      pcVar18 = (char *)((int)ppiVar21 + -1);
      for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
        *(undefined4 *)pcVar18 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar18 = pcVar18 + 4;
      }
      for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
        *pcVar18 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar18 = pcVar18 + 1;
      }
      ppiStackY_2e0 = (int **)0x454aed;
      FUN_00463610();
      ppiStackY_2e0 = (int **)0x454afd;
      (**(code **)(**(int **)(param_1 + 0x2ec) + 0xc))();
    }
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x454b0a;
    FUN_00505f60();
    break;
  case 0x5b:
    if ((*(int *)(*(int *)(param_1 + 0x274) + 0x44) != 0) && (param_3 == 1)) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x4537cb;
      FUN_00505f60();
      FUN_00467240();
      puVar11 = &local_27c;
      for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined2 *)puVar11 = 0;
      ppiStackY_2e0 = (int **)&local_27c;
      ppiStackY_2e4 = (int **)0x4537fd;
      FUN_004663c0();
      ppiStackY_2e0 = (int **)0xff;
      ppiStackY_2e4 = (int **)0x0;
      iStackY_2ec = (int)&local_27c;
      ppiStackY_2e8 = (int **)0x0;
      appiStackY_2f8[2] = (int **)0x45381e;
      FUN_00466340();
    }
    break;
  case 0x5c:
    if ((*(int *)(*(int *)(param_1 + 0x278) + 0x44) != 0) && (param_3 == 1)) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x453850;
      FUN_00505f60();
      FUN_00467240();
      puVar11 = &local_27c;
      for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined2 *)puVar11 = 0;
      ppiStackY_2e0 = (int **)&local_27c;
      ppiStackY_2e4 = (int **)0x453882;
      FUN_004663c0();
      ppiStackY_2e0 = (int **)0xff;
      ppiStackY_2e4 = (int **)0x0;
      iStackY_2ec = (int)&local_27c;
      ppiStackY_2e8 = (int **)0x0;
      appiStackY_2f8[2] = (int **)0x4538a3;
      FUN_00466340();
    }
    break;
  case 0x5d:
    ppiStackY_2e0 = (int **)DAT_005e0068;
    ppiStackY_2e4 = (int **)0x4561c3;
    FUN_00505f60();
    FUN_004618d0();
    ppiStackY_2e0 = (int **)0x4561de;
    (**(code **)(**(int **)(param_1 + 0x2d0) + 0x58))();
    ppiStackY_2e0 = (int **)0x4561f0;
    FUN_00461f70();
    if (*(int *)(param_1 + 0x14) != 0) {
      local_2c8 = (int *)0x0;
      local_2c4 = (int *)0x0;
      local_2c0 = (int *)0x0;
      local_2bc = 0;
      local_2b8 = local_2b8 & 0xffff0000;
      ppiStackY_2e0 = (int **)0x45621e;
      FUN_0046c5d0();
      ppiStackY_2e0 = (int **)0x456226;
      (**(code **)(param_1 + 0x14))();
    }
    ppiStackY_2e0 = (int **)0x456239;
    FUN_0046c620();
    if ((*(int *)(param_1 + 0x2dc) == 3) && (param_4 == 0)) {
      ppiStackY_2e0 = (int **)0x456269;
      FUN_00463070();
      ppiStackY_2e0 = (int **)0x456276;
      (**(code **)(**(int **)(param_1 + 0x2c4) + 0x58))();
      ppiStackY_2e0 = (int **)0x456288;
      FUN_00461e50();
      ppiStackY_2e0 = (int **)0x45629a;
      FUN_004618c0();
      ppiStackY_2e0 = (int **)0x4562a7;
      FUN_0046bc80();
      ppiStackY_2e0 = (int **)0x4562b4;
      FUN_0046b560();
      ppiStackY_2e0 = (int **)0x4562c4;
      FUN_0046b860();
      if (DAT_005e0324 == 0) {
        ExceptionList = local_c;
        return 0;
      }
      ppiStackY_2e0 = (int **)param_4;
      ppiStackY_2e4 = (int **)param_3;
      ppiStackY_2e8 = (int **)0x4c;
      iStackY_2ec = 0x4562ea;
      FUN_004620e0();
      ExceptionList = local_c;
      return 0;
    }
    if (*(int *)(param_1 + 0x2dc) != 4) {
      ExceptionList = local_c;
      return 1;
    }
    ppiStackY_2e0 = (int **)0x45630c;
    FUN_00463070();
    ppiStackY_2e0 = (int **)0x456319;
    (**(code **)(**(int **)(param_1 + 0x2c4) + 0x58))();
    ppiStackY_2e0 = (int **)0x45632b;
    FUN_00461e50();
    ppiStackY_2e0 = (int **)0x45633d;
    FUN_004618c0();
    ppiStackY_2e0 = (int **)0x45634a;
    FUN_0046bc80();
    ppiStackY_2e0 = (int **)0x456357;
    FUN_0046b560();
    ppiStackY_2e0 = (int **)0x456367;
    FUN_0046b860();
    if (DAT_005e0324 == 0) {
      ExceptionList = local_c;
      return 0;
    }
    ppiStackY_2e0 = (int **)param_4;
    ppiStackY_2e4 = (int **)param_3;
    ppiStackY_2e8 = (int **)0x4d;
    iStackY_2ec = 0x45638d;
    FUN_004620e0();
    ExceptionList = local_c;
    return 0;
  case 0x5e:
    ppiStackY_2e0 = (int **)DAT_005e0074;
    ppiStackY_2e4 = (int **)0x4563a2;
    FUN_00505f60();
    ppiStackY_2e0 = (int **)0x4563b5;
    FUN_0046c620();
    FUN_004618d0();
    ppiStackY_2e0 = (int **)0x4563cd;
    (**(code **)(**(int **)(param_1 + 0x2d0) + 0x58))();
    ppiStackY_2e0 = (int **)0x4563df;
    FUN_00461f70();
    break;
  case 0x5f:
    puVar11 = &local_27c;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    ppiStackY_2e0 = (int **)&local_27c;
    *(undefined2 *)puVar11 = 0;
    local_2b4 = 0;
    ppiStackY_2e4 = (int **)0x4535ea;
    FUN_004663c0();
    local_2c8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    local_2a8 = (int *)0x0;
    local_2a4 = (int *)0x0;
    local_2a0 = (int *)0x0;
    local_4._0_1_ = 0x10;
    local_4._1_3_ = 0;
    if (*(code **)(param_1 + 0x10) != (code *)0x0) {
      ppiStackY_2e0 = &local_2c8;
      ppiStackY_2e4 = (int **)0x6;
      ppiStackY_2e8 = (int **)0x45362c;
      (**(code **)(param_1 + 0x10))();
    }
    piVar16 = local_2a4;
    piVar7 = local_2a8;
    if (local_2a8 != local_2a4) {
LAB_0045363d:
      pbVar6 = (byte *)*piVar7;
      pbVar17 = (byte *)&local_27c;
      do {
        bVar2 = *pbVar6;
        bVar24 = bVar2 < *pbVar17;
        if (bVar2 != *pbVar17) {
LAB_00453668:
          iVar5 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
          goto LAB_0045366d;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar6[1];
        bVar24 = bVar2 < pbVar17[1];
        if (bVar2 != pbVar17[1]) goto LAB_00453668;
        pbVar6 = pbVar6 + 2;
        pbVar17 = pbVar17 + 2;
      } while (bVar2 != 0);
      iVar5 = 0;
LAB_0045366d:
      if (iVar5 != 0) goto code_r0x00453671;
      ppiStackY_2e0 = (int **)DAT_005e0068;
      ppiStackY_2e4 = (int **)0x4536f6;
      FUN_00505f60();
      ppiStackY_2e4 = (int **)local_2c8[local_2b4];
      ppiStackY_2e0 = (int **)0x0;
      ppiStackY_2e8 = (int **)0x61;
      iStackY_2ec = 0x453716;
      FUN_004620e0();
      piVar7 = local_2a4;
      local_4._0_1_ = 0x11;
      for (piVar16 = local_2a8; piVar16 != piVar7; piVar16 = piVar16 + 3) {
        FUN_004026e0();
      }
      local_4 = CONCAT31(local_4._1_3_,0xf);
      if (((int)local_2a0 - (int)local_2a8) / 0xc != 0) {
        ppiStackY_2e4 = (int **)0x45376b;
        ppiStackY_2e0 = (int **)local_2a8;
        FUN_00402e90();
      }
      iVar5 = (int)local_2c0 - (int)local_2c8;
      goto LAB_0045377b;
    }
LAB_00453681:
    local_4._0_1_ = 0x12;
    for (piVar7 = local_2a8; piVar7 != piVar16; piVar7 = piVar7 + 3) {
      FUN_004026e0();
    }
    local_4 = CONCAT31(local_4._1_3_,0xf);
    if (((int)local_2a0 - (int)local_2a8) / 0xc != 0) {
      ppiStackY_2e4 = (int **)0x4536d2;
      ppiStackY_2e0 = (int **)local_2a8;
      FUN_00402e90();
    }
    iVar5 = (int)local_2c0 - (int)local_2c8;
LAB_0045377b:
    local_4 = 0xffffffff;
    if (iVar5 >> 2 != 0) {
      ppiStackY_2e0 = (int **)local_2c8;
      ppiStackY_2e4 = (int **)0x453796;
      FUN_00402e90();
    }
    break;
  case 0x62:
    if (param_3 == 1) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x4530f5;
      FUN_00505f60();
      puVar11 = &local_27c;
      for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      ppiStackY_2e0 = (int **)&local_27c;
      *(undefined2 *)puVar11 = 0;
      ppiStackY_2e4 = (int **)0x45311b;
      FUN_004663c0();
      local_2a8 = (int *)0x0;
      local_2a4 = (int *)0x0;
      local_2a0 = (int *)0x0;
      local_2c8 = (int *)0x0;
      local_2c4 = (int *)0x0;
      local_2c0 = (int *)0x0;
      local_4 = 9;
      if (*(code **)(param_1 + 0x10) != (code *)0x0) {
        ppiStackY_2e0 = &local_2a8;
        ppiStackY_2e4 = (int **)0x6;
        ppiStackY_2e8 = (int **)0x45315d;
        (**(code **)(param_1 + 0x10))();
      }
      local_2ac = local_2c8;
      if (local_2c8 != local_2c4) {
        local_2b4 = 0;
        do {
          pbVar17 = (byte *)&local_27c;
          pbVar6 = (byte *)*local_2ac;
          do {
            bVar2 = *pbVar6;
            bVar24 = bVar2 < *pbVar17;
            if (bVar2 != *pbVar17) {
LAB_004531a9:
              iVar5 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
              goto LAB_004531ae;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar6[1];
            bVar24 = bVar2 < pbVar17[1];
            if (bVar2 != pbVar17[1]) goto LAB_004531a9;
            pbVar6 = pbVar6 + 2;
            pbVar17 = pbVar17 + 2;
          } while (bVar2 != 0);
          iVar5 = 0;
LAB_004531ae:
          if (iVar5 == 0) {
            local_294 = (int *)(*(int **)(param_1 + 0x2f0))[2];
            if (local_294 != *(int **)(param_1 + 0x2f0)) {
              do {
                piVar16 = local_294;
                ppiStackY_2e0 = (int **)0x4531d7;
                (**(code **)(*(int *)local_294[5] + 0xc))();
                if (*(int *)(*(int *)(piVar16[5] + 4) + 8) != 2) {
                  *(undefined4 *)(*(int *)(piVar16[5] + 4) + 8) = 3;
                }
                FUN_0043c6c0();
              } while (local_294 != *(int **)(param_1 + 0x2f0));
            }
            uStack_248 = *(undefined4 *)(local_2b4 + (int)local_2a8);
            ppiStackY_2e0 = &local_2b0;
            ppiStackY_2e4 = (int **)0x453222;
            FUN_00460d90();
            if (local_2b0 != *(int **)(param_1 + 0x2f0)) {
              ppiStackY_2e0 = (int **)0x453236;
              (**(code **)(*(int *)local_2b0[5] + 0xc))();
              if (*(int *)(*(int *)(local_2b0[5] + 4) + 8) != 2) {
                *(undefined4 *)(*(int *)(local_2b0[5] + 4) + 8) = 0;
              }
            }
          }
          local_2ac = local_2ac + 3;
          local_2b4 = local_2b4 + 4;
        } while (local_2ac != local_2c4);
      }
      piVar7 = local_2c4;
      local_4._0_1_ = 10;
      for (piVar16 = local_2c8; piVar16 != piVar7; piVar16 = piVar16 + 3) {
        FUN_004026e0();
      }
      local_4 = CONCAT31(local_4._1_3_,8);
      if (((int)local_2c0 - (int)local_2c8) / 0xc != 0) {
        ppiStackY_2e4 = (int **)0x4532c1;
        ppiStackY_2e0 = (int **)local_2c8;
        FUN_00402e90();
      }
      local_4 = 0xffffffff;
      if ((int)local_2a0 - (int)local_2a8 >> 2 != 0) {
        ppiStackY_2e0 = (int **)local_2a8;
        ppiStackY_2e4 = (int **)0x4532f2;
        FUN_00402e90();
      }
    }
    break;
  case 0x6f:
  case 0x70:
  case 0x71:
  case 0x72:
    if (param_3 != 1) {
      ExceptionList = local_c;
      return 1;
    }
  case 99:
  case 100:
  case 0x65:
  case 0x66:
  case 0x67:
  case 0x68:
  case 0x69:
  case 0x6a:
  case 0x6b:
  case 0x6c:
  case 0x6d:
  case 0x6e:
  case 0x73:
  case 0x74:
  case 0x75:
  case 0x76:
  case 0x77:
  case 0x80:
    ppiStackY_2e0 = (int **)DAT_005e0078;
    ppiStackY_2e4 = (int **)0x45307a;
    FUN_00505f60();
    ExceptionList = local_c;
    return 1;
  case 0x78:
    *(undefined4 *)(param_1 + 0x304) = 0;
    *(undefined4 *)(param_1 + 0x308) = 0;
    *(undefined4 *)(param_1 + 0x30c) = 0;
    *(undefined4 *)(param_1 + 0x310) = 0;
    *(undefined4 *)(param_1 + 0x314) = 0;
    *(undefined4 *)(param_1 + 0x318) = 0;
    *(undefined4 *)(param_1 + 0x31c) = 0;
    *(undefined4 *)(param_1 + 800) = 0;
    *(undefined4 *)(param_1 + 0x324) = 0;
    *(undefined4 *)(param_1 + 0x328) = 0;
    ppiStackY_2e0 = (int **)0x452f24;
    FUN_0046cbc0();
    ppiStackY_2e0 = (int **)0x452f30;
    FUN_0046cbe0();
    ppiStackY_2e0 = (int **)0x452f4b;
    FUN_00463070();
    ppiStackY_2e0 = (int **)0x452f58;
    (**(code **)(**(int **)(param_1 + 0x300) + 0x58))();
    ppiStackY_2e0 = (int **)0x452f63;
    FUN_004618d0();
    ppiStackY_2e0 = *(int ***)(param_1 + 0x300);
    ppiStackY_2e4 = (int **)0x452f75;
    FUN_00461f70();
    ppiStackY_2e0 = (int **)DAT_005c7b60;
    ppiStackY_2e4 = (int **)0x452f87;
    FUN_00463070();
    ppiStackY_2e0 = (int **)0x1;
    ppiStackY_2e4 = (int **)0x452f94;
    (**(code **)(**(int **)(param_1 + 0x2c4) + 0x58))();
    ppiStackY_2e0 = (int **)0x452fa6;
    FUN_00461e50();
    ppiStackY_2e0 = (int **)0x452fb8;
    FUN_004618c0();
    ppiStackY_2e0 = (int **)0x452fc5;
    FUN_0046bc80();
    ppiStackY_2e0 = (int **)0x452fd2;
    FUN_0046b560();
    ppiStackY_2e0 = (int **)0x452fe2;
    FUN_0046b860();
    if (DAT_005e0324 != 0) {
      ppiStackY_2e0 = (int **)param_4;
      ppiStackY_2e4 = (int **)param_3;
      ppiStackY_2e8 = (int **)0x4f;
      iStackY_2ec = 0x45300f;
      FUN_004620e0();
    }
    break;
  case 0x79:
    ppiStackY_2e0 = (int **)0x45302f;
    FUN_00463070();
    ppiStackY_2e0 = (int **)0x45303c;
    (**(code **)(**(int **)(param_1 + 0x300) + 0x58))();
    FUN_004618d0();
    ppiStackY_2e0 = (int **)0x453059;
    FUN_00461f70();
    break;
  case 0x7e:
    if (*(int *)(param_1 + 0x20) == 0) {
      ExceptionList = local_c;
      return 1;
    }
    local_2a8 = (int *)0x0;
    local_2a4 = (int *)0x0;
    local_2a0 = (int *)0x0;
    ppiStackY_2e0 = (int **)0x452e5c;
    FUN_004608a0();
    local_4 = 4;
    FUN_00402a70();
    local_4 = 5;
    local_2c8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    ppiStackY_2e0 = (int **)0x452e92;
    FUN_004608a0();
    local_4._0_1_ = 6;
    FUN_00402a70();
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = &local_2a8;
    local_4._0_1_ = 7;
    ppiStackY_2e8 = (int **)0x452eba;
    (**(code **)(param_1 + 0x20))();
    ppiStackY_2e0 = (int **)0x452ecd;
    FUN_0046db10();
    ppiStackY_2e0 = (int **)0x452edd;
    FUN_0046db30();
    local_4 = CONCAT31(local_4._1_3_,5);
    goto LAB_00452de8;
  case 0x7f:
    if (*(int *)(param_1 + 0x20) == 0) {
      ExceptionList = local_c;
      return 1;
    }
    local_2a8 = (int *)0x0;
    local_2a4 = (int *)0x0;
    local_2a0 = (int *)0x0;
    ppiStackY_2e0 = (int **)0x452d63;
    FUN_004608a0();
    local_4 = 0;
    FUN_00402a70();
    local_4 = 1;
    local_2c8 = (int *)0x0;
    local_2c4 = (int *)0x0;
    local_2c0 = (int *)0x0;
    ppiStackY_2e0 = (int **)0x452d95;
    FUN_004608a0();
    local_4._0_1_ = 2;
    FUN_00402a70();
    ppiStackY_2e0 = &local_2c8;
    ppiStackY_2e4 = &local_2a8;
    local_4._0_1_ = 3;
    ppiStackY_2e8 = (int **)0x452dbd;
    (**(code **)(param_1 + 0x20))();
    ppiStackY_2e0 = (int **)0x452dd0;
    FUN_0046db10();
    ppiStackY_2e0 = (int **)0x452de0;
    FUN_0046db30();
    local_4 = CONCAT31(local_4._1_3_,1);
LAB_00452de8:
    if ((local_2c8 != (int *)0x0) && (local_2c0 != local_2c8)) {
      ppiStackY_2e0 = (int **)local_2c8;
      ppiStackY_2e4 = (int **)0x452e01;
      FUN_00402e90();
    }
    local_4 = 0xffffffff;
    if ((local_2a8 != (int *)0x0) && (local_2a0 != local_2a8)) {
      ppiStackY_2e0 = (int **)local_2a8;
      ppiStackY_2e4 = (int **)0x452e30;
      FUN_00402e90();
    }
    break;
  case 0x81:
    ppiStackY_2e0 = (int **)0x452cc6;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x452ccd;
    FUN_004630b0();
    iVar5 = FUN_005565e0();
    if (*(int *)(iVar5 + 0x44) == 0) {
      ExceptionList = local_c;
      return 0;
    }
    if (*(int *)(param_1 + 0x250) == *(int *)(param_1 + 0x24c)) {
      ExceptionList = local_c;
      return 0;
    }
    break;
  case 0x82:
    ppiStackY_2e0 = (int **)0x452d0b;
    FUN_00462d40();
    ppiStackY_2e0 = (int **)0x452d12;
    FUN_004630b0();
    iVar5 = FUN_005565e0();
    if (*(int *)(iVar5 + 0x44) == 0) {
      ExceptionList = local_c;
      return 0;
    }
    if (*(int *)(param_1 + 0x250) == *(int *)(param_1 + 0x24c)) {
      ExceptionList = local_c;
      return 0;
    }
    break;
  case 0x84:
    if (*(int *)(param_1 + 0x338) != 0) {
      FUN_004618d0();
      ppiStackY_2e0 = (int **)0x452c2e;
      (**(code **)(*param_5 + 0x54))();
      ppiStackY_2e0 = (int **)0x0;
      ppiStackY_2e4 = (int **)0x452c37;
      (**(code **)(*param_5 + 0xc))();
      ppiStackY_2e0 = (int **)0x452c46;
      FUN_00461f70();
      *(undefined4 *)(param_1 + 0x338) = 0;
      ExceptionList = local_c;
      return 0;
    }
    break;
  case 0x87:
    if (param_3 == 1) {
      ppiStackY_2e0 = (int **)DAT_005e0078;
      ppiStackY_2e4 = (int **)0x4538c4;
      FUN_00505f60();
      ppiStackY_2e0 = (int **)0x4538da;
      FUN_00462d40();
      ppiStackY_2e0 = (int **)0x4538e1;
      FUN_004630b0();
      iVar5 = FUN_005565e0();
      if (*(int *)(iVar5 + 0x44) != 0) {
        ppiStackY_2e0 = (int **)0x4538ff;
        FUN_00462d40();
        ppiStackY_2e0 = (int **)0x453906;
        FUN_004630b0();
        FUN_005565e0();
        ppiStackY_2e0 = (int **)local_20c;
        ppiStackY_2e4 = (int **)0x45391f;
        FUN_004663c0();
        uVar13 = 0xffffffff;
        piVar16 = (int *)(param_1 + 0x24c);
        pcVar9 = local_20c;
        do {
          if (uVar13 == 0) break;
          uVar13 = uVar13 - 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        pcVar9 = (char *)*piVar16;
        uVar13 = ~uVar13 - 1;
        uVar14 = *(int *)(param_1 + 0x250) - (int)pcVar9;
        if (uVar14 < uVar13) {
          pcVar18 = local_20c;
          for (uVar13 = uVar14 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
            *(undefined4 *)pcVar9 = *(undefined4 *)pcVar18;
            pcVar18 = pcVar18 + 4;
            pcVar9 = pcVar9 + 4;
          }
          for (uVar14 = uVar14 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
            *pcVar9 = *pcVar18;
            pcVar18 = pcVar18 + 1;
            pcVar9 = pcVar9 + 1;
          }
          ppiStackY_2e0 = (int **)(local_20c + (*(int *)(param_1 + 0x250) - *piVar16));
          ppiStackY_2e4 = (int **)0x4539a7;
          FUN_00403490();
        }
        else {
          pcVar18 = local_20c;
          for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
            *(undefined4 *)pcVar9 = *(undefined4 *)pcVar18;
            pcVar18 = pcVar18 + 4;
            pcVar9 = pcVar9 + 4;
          }
          for (uVar14 = uVar13 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
            *pcVar9 = *pcVar18;
            pcVar18 = pcVar18 + 1;
            pcVar9 = pcVar9 + 1;
          }
          ppiStackY_2e0 = (int **)(*piVar16 + uVar13);
          ppiStackY_2e4 = (int **)0x45397c;
          FUN_00402b30();
        }
      }
    }
    break;
  case 0x88:
    if (*(int *)(param_1 + 0x338) != 0) {
      ppiStackY_2e0 = (int **)0x452b64;
      FUN_0046dbb0();
      iVar5 = -1;
      pcVar9 = local_10c;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      if (iVar5 == -2) {
        ExceptionList = local_c;
        return 0;
      }
      FUN_004618d0();
      ppiStackY_2e0 = (int **)0x452ba4;
      (**(code **)(*param_5 + 0x54))();
      ppiStackY_2e0 = (int **)0x0;
      ppiStackY_2e4 = (int **)0x452bad;
      (**(code **)(*param_5 + 0xc))();
      ppiStackY_2e0 = (int **)0x452bbc;
      FUN_00461f70();
      iVar5 = -1;
      ppiStackY_2e0 = (int **)local_10c;
      pcVar9 = local_10c;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      *(undefined4 *)(param_1 + 0x338) = 0;
      ppiStackY_2e4 = (int **)0x452bf2;
      FUN_00403200();
    }
    break;
  case 0x89:
    if (*(int *)(param_1 + 0x338) != 0) {
      FUN_004618d0();
      ppiStackY_2e0 = (int **)0x452c8e;
      (**(code **)(*param_5 + 0x54))();
      ppiStackY_2e0 = (int **)0x0;
      ppiStackY_2e4 = (int **)0x452c97;
      (**(code **)(*param_5 + 0xc))();
      ppiStackY_2e0 = (int **)0x452ca6;
      FUN_00461f70();
      *(undefined4 *)(param_1 + 0x338) = 0;
    }
  }
  ExceptionList = local_c;
  return 1;
code_r0x00453671:
  piVar7 = piVar7 + 3;
  local_2b4 = local_2b4 + 1;
  if (piVar7 == local_2a4) goto LAB_00453681;
  goto LAB_0045363d;
}

