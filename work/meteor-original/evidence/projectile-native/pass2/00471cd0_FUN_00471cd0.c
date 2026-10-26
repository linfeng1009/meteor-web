/* Original Meteor.exe static export @ 00471cd0; original sample not executed. */
/* XREF 004731f8 UNCONDITIONAL_CALL */

undefined4 __fastcall FUN_00471cd0(undefined4 *param_1)

{
  char cVar1;
  void *pvVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  uint uVar11;
  char *pcVar12;
  float *pfVar13;
  uint uVar14;
  undefined4 *puVar15;
  char *pcVar16;
  char *pcVar17;
  char **ppcVar18;
  char *apcStackY_4f8 [5];
  int iStackY_4e4;
  char *pcStackY_4e0;
  float local_4c0 [6];
  int local_4a8;
  int iStack_4a4;
  undefined1 local_49d;
  undefined4 local_49c;
  undefined4 local_498;
  undefined4 *local_494;
  undefined4 local_490;
  int local_48c;
  int *local_488;
  int *piStack_484;
  int iStack_480;
  char acStack_47c [52];
  char acStack_448 [52];
  undefined4 local_414;
  undefined4 local_410;
  undefined4 local_40c;
  undefined4 local_408;
  undefined4 local_404;
  undefined4 local_400;
  undefined4 local_3fc;
  undefined4 local_3f8;
  undefined4 local_3f4;
  undefined4 local_3f0;
  undefined4 local_3ec;
  undefined4 local_3e8;
  undefined4 local_3e4;
  undefined4 local_3e0;
  undefined4 local_3dc;
  undefined4 local_3d8;
  undefined4 local_3d4;
  undefined4 local_3d0;
  undefined4 local_3cc;
  undefined4 local_3c8;
  undefined4 local_3c4;
  undefined4 local_3c0;
  undefined4 local_3bc;
  undefined4 local_3ac [16];
  undefined4 local_36c;
  undefined4 local_368;
  undefined4 local_364;
  undefined4 local_360;
  undefined4 local_35c;
  undefined1 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_348;
  undefined4 local_344;
  undefined4 local_340 [54];
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 *local_25c [2];
  int iStack_254;
  undefined4 *local_250 [2];
  int iStack_248;
  char acStack_244 [52];
  char acStack_210 [504];
  undefined4 *local_18;
  undefined4 *local_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059d0c3;
  pvStack_c = ExceptionList;
  puVar4 = local_3ac;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  local_36c = 0;
  local_368 = 0;
  local_364 = 0;
  local_360 = 0;
  local_358 = 0;
  local_35c = 0;
  ExceptionList = &pvStack_c;
  FUN_00473400();
  pcStackY_4e0 = &local_49d;
  iStackY_4e4 = 0x471d5c;
  FUN_00402b70();
  local_4 = 0;
  FUN_00402a70();
  local_4 = 1;
  pcStackY_4e0 = (char *)0x471d8c;
  FUN_004024a0();
  local_414 = 0;
  local_410 = 0;
  iVar7 = 0;
  local_40c = 0;
  local_408 = 0;
  local_404 = 0;
  local_400 = 0;
  do {
    cVar1 = s_unname_005c7820[iVar7];
    *(char *)((int)&local_410 + iVar7) = cVar1;
    iVar7 = iVar7 + 1;
  } while (cVar1 != '\0');
  local_3f8 = 0x280;
  local_3f4 = 0x1e0;
  local_3f0 = 0;
  local_3ec = 0;
  local_3e8 = 0;
  local_3e4 = 1;
  local_3e0 = 1;
  local_3dc = 1;
  local_3d8 = 1;
  local_3d4 = 0;
  local_3d0 = 0;
  local_354 = 100;
  local_34c = 0x32;
  local_350 = 100;
  local_348 = 0x32;
  local_344 = 0x32;
  local_3c4 = 0;
  local_3c0 = 1;
  local_3c8 = 1;
  local_3bc._2_1_ = 1;
  local_3cc = 0x42480000;
  local_268 = 0;
  local_264 = 0;
  local_260 = 0;
  local_4._0_1_ = 2;
  local_4._1_3_ = 0;
  if (DAT_005e0328 == 0) {
    pcStackY_4e0 = (char *)0x471ea9;
    pvVar2 = operator_new(0x33c);
    local_4._0_1_ = 3;
    if (pvVar2 == (void *)0x0) {
      DAT_005e0328 = 0;
    }
    else {
      DAT_005e0328 = FUN_0044d020();
    }
  }
  local_4._0_1_ = 2;
  pcStackY_4e0 = (char *)0x471ee7;
  local_4a8 = DAT_005e0328;
  puVar3 = (undefined4 *)FUN_0045a450();
  local_414 = *puVar3;
  local_4 = CONCAT31(local_4._1_3_,4);
  puVar4 = &local_410;
  iVar7 = 0x14;
  do {
    *(undefined1 *)puVar4 = *(undefined1 *)(((int)puVar3 - (int)&local_414) + (int)puVar4);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  local_3fc = puVar3[6];
  local_3f8 = puVar3[7];
  local_3f4 = puVar3[8];
  local_3f0 = puVar3[9];
  local_3ec = puVar3[10];
  local_3e8 = puVar3[0xb];
  local_3e4 = puVar3[0xc];
  local_3e0 = puVar3[0xd];
  local_3dc = puVar3[0xe];
  local_3d8 = puVar3[0xf];
  local_3d4 = puVar3[0x10];
  local_3d0 = puVar3[0x11];
  local_3cc = puVar3[0x12];
  local_3c8 = puVar3[0x13];
  local_3c4 = puVar3[0x14];
  local_3c0 = puVar3[0x15];
  puVar4 = puVar3 + 0x16;
  puVar15 = &local_3bc;
  for (iVar7 = 0x1a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar15 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar15 = puVar15 + 1;
  }
  local_354 = puVar3[0x30];
  local_350 = puVar3[0x31];
  local_34c = puVar3[0x32];
  local_348 = puVar3[0x33];
  local_344 = puVar3[0x34];
  puVar4 = puVar3 + 0x35;
  puVar15 = local_340;
  for (iVar7 = 0x36; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar15 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar15 = puVar15 + 1;
  }
  local_268 = puVar3[0x6b];
  local_264 = puVar3[0x6c];
  local_260 = puVar3[0x6d];
  if ((undefined4 **)(puVar3 + 0x6e) != local_25c) {
    pcStackY_4e0 = (char *)puVar3[0x6e];
    iStackY_4e4 = 0x47206c;
    FUN_00403200();
  }
  if ((undefined4 **)(puVar3 + 0x71) != local_250) {
    pcStackY_4e0 = (char *)puVar3[0x71];
    iStackY_4e4 = 0x472090;
    FUN_00403200();
  }
  local_4._0_1_ = 5;
  if ((local_18 != (undefined4 *)0x0) && (local_10 != local_18)) {
    pcStackY_4e0 = (char *)local_18;
    iStackY_4e4 = 0x4720b7;
    FUN_00402e90();
  }
  local_4._0_1_ = 2;
  FUN_004026e0();
  iVar7 = FUN_004582d0();
  local_494 = (undefined4 *)0x0;
  local_490 = 0;
  local_48c = 0;
  local_4._0_1_ = 6;
  pcStackY_4e0 = (char *)0x4720fd;
  FUN_005005b0();
  local_498 = 0;
  local_49c = 0;
  local_4 = CONCAT31(local_4._1_3_,7);
  if ((code *)*param_1 != (code *)0x0) {
    pcStackY_4e0 = (char *)0x47211a;
    (*(code *)*param_1)();
  }
  local_4c0[0] = 0.0;
  local_4c0[1] = 0.0;
  local_4c0[2] = 0.0;
  local_4c0[3] = 0.0;
  local_4c0[4] = 1.0;
  FUN_00468f20();
  if (iVar7 == 1) {
    if (local_488 != piStack_484) {
      iStack_4a4 = 0x5b;
      piVar5 = local_488 + 4;
      do {
        pcStackY_4e0 = (char *)0x472854;
        pvVar2 = operator_new(0x50);
        local_4 = CONCAT31(local_4._1_3_,10);
        if (pvVar2 == (void *)0x0) {
          piVar6 = (int *)0x0;
        }
        else {
          piVar6 = (int *)FUN_00465610();
        }
        local_4c0[1] = (float)iStack_4a4;
        local_4c0[2] = 424.0;
        local_4c0[3] = 17.0;
        local_4c0[0] = 111.0;
        pfVar13 = local_4c0;
        ppcVar18 = apcStackY_4f8 + 2;
        for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
          *ppcVar18 = (char *)*pfVar13;
          pfVar13 = pfVar13 + 1;
          ppcVar18 = ppcVar18 + 1;
        }
        apcStackY_4f8[1] = (char *)0x0;
        apcStackY_4f8[0] = (char *)0x5;
        local_4 = CONCAT31(local_4._1_3_,7);
        FUN_00466720();
        pcStackY_4e0 = (char *)0x0;
        iStackY_4e4 = 0;
        local_4c0[2] = 122.0;
        local_4c0[0] = 111.0;
        pfVar13 = local_4c0;
        ppcVar18 = apcStackY_4f8;
        for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
          *ppcVar18 = (char *)*pfVar13;
          pfVar13 = pfVar13 + 1;
          ppcVar18 = ppcVar18 + 1;
        }
        FUN_00466a10();
        if (*(char *)((int)piVar5 + -2) == '\0') {
          apcStackY_4f8[3] = (char *)*piVar5;
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 0;
          apcStackY_4f8[4] = (char *)0x0;
          apcStackY_4f8[2] = (char *)0x472902;
          FUN_00466340();
        }
        if (*(char *)((int)piVar5 + -2) == '\x01') {
          apcStackY_4f8[3] = (char *)*piVar5;
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[4] = (char *)0x0;
          apcStackY_4f8[2] = (char *)0x472923;
          FUN_00466340();
        }
        if (*(char *)((int)piVar5 + -2) == '\x02') {
          apcStackY_4f8[3] = (char *)*piVar5;
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 200;
          apcStackY_4f8[4] = (char *)0x0;
          apcStackY_4f8[2] = "j";
          FUN_00466340();
        }
        pcStackY_4e0 = (char *)0x0;
        iStackY_4e4 = 1;
        local_4c0[2] = 95.0;
        local_4c0[0] = 233.0;
        pfVar13 = local_4c0;
        ppcVar18 = apcStackY_4f8;
        for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
          *ppcVar18 = (char *)*pfVar13;
          pfVar13 = pfVar13 + 1;
          ppcVar18 = ppcVar18 + 1;
        }
        FUN_00466a10();
        apcStackY_4f8[3] = (char *)piVar5[3];
        pcStackY_4e0 = (char *)0xff;
        iStackY_4e4 = 0xff;
        apcStackY_4f8[4] = (char *)0x1;
        apcStackY_4f8[2] = "j";
        FUN_00466340();
        pcStackY_4e0 = (char *)0x0;
        iStackY_4e4 = 2;
        local_4c0[2] = 61.0;
        local_4c0[0] = 327.0;
        pfVar13 = local_4c0;
        ppcVar18 = apcStackY_4f8;
        for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
          *ppcVar18 = (char *)*pfVar13;
          pfVar13 = pfVar13 + 1;
          ppcVar18 = ppcVar18 + 1;
        }
        FUN_00466a10();
        apcStackY_4f8[3] = (char *)piVar5[6];
        pcStackY_4e0 = (char *)0xff;
        iStackY_4e4 = 0xff;
        apcStackY_4f8[4] = (char *)0x2;
        apcStackY_4f8[2] = (char *)0x4729d0;
        FUN_00466340();
        pcStackY_4e0 = acStack_47c;
        pcVar10 = acStack_47c;
        for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
          pcVar10[0] = '\0';
          pcVar10[1] = '\0';
          pcVar10[2] = '\0';
          pcVar10[3] = '\0';
          pcVar10 = pcVar10 + 4;
        }
        pcVar10[0] = '\0';
        pcVar10[1] = '\0';
        iStackY_4e4 = piVar5[-4];
        local_4c0[2] = 102.0;
        local_4c0[0] = 389.0;
        apcStackY_4f8[4] = (char *)0x4729ff;
        FUN_0050aaa9();
        iStackY_4e4 = piVar5[-2];
        if (iStackY_4e4 != 0) {
          pcVar10 = acStack_244;
          for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
            pcVar10[0] = '\0';
            pcVar10[1] = '\0';
            pcVar10[2] = '\0';
            pcVar10[3] = '\0';
            pcVar10 = pcVar10 + 4;
          }
          pcVar10[0] = '\0';
          pcVar10[1] = '\0';
          iVar7 = -1;
          pcVar10 = acStack_47c;
          do {
            pcVar12 = pcVar10;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar12 = pcVar10 + 1;
            cVar1 = *pcVar10;
            pcVar10 = pcVar12;
          } while (cVar1 != '\0');
          *(undefined2 *)(pcVar12 + -1) = DAT_005c7c4c;
          pcStackY_4e0 = acStack_244;
          pcVar12[1] = DAT_005c7c4e;
          apcStackY_4f8[4] = (char *)0x472a4d;
          FUN_0050aaa9();
          uVar8 = 0xffffffff;
          pcVar10 = acStack_244;
          do {
            pcVar12 = pcVar10;
            if (uVar8 == 0) break;
            uVar8 = uVar8 - 1;
            pcVar12 = pcVar10 + 1;
            cVar1 = *pcVar10;
            pcVar10 = pcVar12;
          } while (cVar1 != '\0');
          uVar8 = ~uVar8;
          iVar7 = -1;
          pcVar10 = acStack_47c;
          do {
            pcVar17 = pcVar10;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar17 = pcVar10 + 1;
            cVar1 = *pcVar10;
            pcVar10 = pcVar17;
          } while (cVar1 != '\0');
          pcVar10 = pcVar12 + -uVar8;
          pcVar12 = pcVar17 + -1;
          for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
            *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
            pcVar10 = pcVar10 + 4;
            pcVar12 = pcVar12 + 4;
          }
          for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pcVar12 = *pcVar10;
            pcVar10 = pcVar10 + 1;
            pcVar12 = pcVar12 + 1;
          }
          iVar7 = -1;
          pcVar10 = acStack_47c;
          do {
            pcVar12 = pcVar10;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar12 = pcVar10 + 1;
            cVar1 = *pcVar10;
            pcVar10 = pcVar12;
          } while (cVar1 != '\0');
          *(undefined2 *)(pcVar12 + -1) = DAT_005c7c48;
        }
        pcStackY_4e0 = (char *)0x0;
        iStackY_4e4 = 3;
        pfVar13 = local_4c0;
        ppcVar18 = apcStackY_4f8;
        for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
          *ppcVar18 = (char *)*pfVar13;
          pfVar13 = pfVar13 + 1;
          ppcVar18 = ppcVar18 + 1;
        }
        FUN_00466a10();
        pcStackY_4e0 = (char *)0xff;
        iStackY_4e4 = 0xff;
        apcStackY_4f8[3] = acStack_47c;
        apcStackY_4f8[4] = (char *)0x3;
        apcStackY_4f8[2] = (char *)0x472ad1;
        FUN_00466340();
        pcStackY_4e0 = acStack_47c;
        pcVar10 = acStack_47c;
        for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
          pcVar10[0] = '\0';
          pcVar10[1] = '\0';
          pcVar10[2] = '\0';
          pcVar10[3] = '\0';
          pcVar10 = pcVar10 + 4;
        }
        pcVar10[0] = '\0';
        pcVar10[1] = '\0';
        iStackY_4e4 = piVar5[-3];
        local_4c0[2] = 44.0;
        local_4c0[0] = 491.0;
        apcStackY_4f8[4] = (char *)0x472b00;
        FUN_0050aaa9();
        pcStackY_4e0 = (char *)0x0;
        iStackY_4e4 = 4;
        pfVar13 = local_4c0;
        ppcVar18 = apcStackY_4f8;
        for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
          *ppcVar18 = (char *)*pfVar13;
          pfVar13 = pfVar13 + 1;
          ppcVar18 = ppcVar18 + 1;
        }
        FUN_00466a10();
        pcStackY_4e0 = (char *)0xff;
        iStackY_4e4 = 0xff;
        apcStackY_4f8[3] = acStack_47c;
        apcStackY_4f8[4] = (char *)0x4;
        apcStackY_4f8[2] = (char *)0x472b3d;
        FUN_00466340();
        pcStackY_4e0 = (char *)0x472b4b;
        (**(code **)(*piVar6 + 0x54))();
        iStack_4a4 = iStack_4a4 + 0x11;
        pcStackY_4e0 = (char *)0x472b63;
        FUN_00467950();
        piVar6 = piVar5 + 9;
        piVar5 = piVar5 + 0xd;
      } while (piVar6 != piStack_484);
    }
    pcStackY_4e0 = (char *)0x3;
    iStackY_4e4 = 0x472b85;
    FUN_00468230();
  }
  else {
    FUN_00468f20();
    if (local_488 != piStack_484) {
      iStack_4a4 = 0x10d;
      local_4a8 = 0x5b;
      pcVar10 = (char *)((int)local_488 + 0xe);
      do {
        if (pcVar10[-2] == '\x01') {
          pcStackY_4e0 = (char *)0x472192;
          pvVar2 = operator_new(0x50);
          local_4 = CONCAT31(local_4._1_3_,8);
          if (pvVar2 == (void *)0x0) {
            piVar5 = (int *)0x0;
          }
          else {
            piVar5 = (int *)FUN_00465610();
          }
          local_4c0[1] = (float)local_4a8;
          local_4c0[2] = 424.0;
          local_4c0[3] = 17.0;
          local_4c0[0] = 111.0;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8 + 2;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          apcStackY_4f8[1] = (char *)0x0;
          apcStackY_4f8[0] = (char *)0x5;
          local_4 = CONCAT31(local_4._1_3_,7);
          FUN_00466720();
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 0;
          local_4c0[2] = 122.0;
          local_4c0[0] = 111.0;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          if (*pcVar10 == '\0') {
            apcStackY_4f8[3] = *(char **)(pcVar10 + 2);
            pcStackY_4e0 = (char *)0x0;
            iStackY_4e4 = 0;
            apcStackY_4f8[4] = (char *)0x0;
            apcStackY_4f8[2] = (char *)0x472240;
            FUN_00466340();
          }
          if (*pcVar10 == '\x01') {
            apcStackY_4f8[3] = *(char **)(pcVar10 + 2);
            pcStackY_4e0 = (char *)0xff;
            iStackY_4e4 = 0xff;
            apcStackY_4f8[4] = (char *)0x0;
            apcStackY_4f8[2] = (char *)0x472262;
            FUN_00466340();
          }
          if (*pcVar10 == '\x02') {
            apcStackY_4f8[3] = *(char **)(pcVar10 + 2);
            pcStackY_4e0 = (char *)0x0;
            iStackY_4e4 = 200;
            apcStackY_4f8[4] = (char *)0x0;
            apcStackY_4f8[2] = "j";
            FUN_00466340();
          }
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 1;
          local_4c0[2] = 95.0;
          local_4c0[0] = 233.0;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          apcStackY_4f8[3] = *(char **)(pcVar10 + 0xe);
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[4] = (char *)0x1;
          apcStackY_4f8[2] = "j";
          FUN_00466340();
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 2;
          local_4c0[2] = 61.0;
          local_4c0[0] = 327.0;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          apcStackY_4f8[3] = *(char **)(pcVar10 + 0x1a);
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[4] = (char *)0x2;
          apcStackY_4f8[2] = (char *)0x472310;
          FUN_00466340();
          pcStackY_4e0 = acStack_448;
          pcVar12 = acStack_448;
          for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
            pcVar12[0] = '\0';
            pcVar12[1] = '\0';
            pcVar12[2] = '\0';
            pcVar12[3] = '\0';
            pcVar12 = pcVar12 + 4;
          }
          pcVar12[0] = '\0';
          pcVar12[1] = '\0';
          iStackY_4e4 = *(int *)(pcVar10 + -0xe);
          local_4c0[2] = 102.0;
          local_4c0[0] = 389.0;
          apcStackY_4f8[4] = (char *)0x472345;
          FUN_0050aaa9();
          iStackY_4e4 = *(int *)(pcVar10 + -6);
          if (iStackY_4e4 != 0) {
            pcVar12 = acStack_210;
            for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
              pcVar12[0] = '\0';
              pcVar12[1] = '\0';
              pcVar12[2] = '\0';
              pcVar12[3] = '\0';
              pcVar12 = pcVar12 + 4;
            }
            pcVar12[0] = '\0';
            pcVar12[1] = '\0';
            iVar7 = -1;
            pcVar12 = acStack_448;
            do {
              pcVar17 = pcVar12;
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              pcVar17 = pcVar12 + 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar17;
            } while (cVar1 != '\0');
            *(undefined2 *)(pcVar17 + -1) = DAT_005c7c4c;
            pcStackY_4e0 = acStack_210;
            pcVar17[1] = DAT_005c7c4e;
            apcStackY_4f8[4] = (char *)0x472396;
            FUN_0050aaa9();
            uVar8 = 0xffffffff;
            pcVar12 = acStack_210;
            do {
              pcVar17 = pcVar12;
              if (uVar8 == 0) break;
              uVar8 = uVar8 - 1;
              pcVar17 = pcVar12 + 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar17;
            } while (cVar1 != '\0');
            uVar8 = ~uVar8;
            iVar7 = -1;
            pcVar12 = acStack_448;
            do {
              pcVar16 = pcVar12;
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              pcVar16 = pcVar12 + 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar16;
            } while (cVar1 != '\0');
            pcVar12 = pcVar17 + -uVar8;
            pcVar17 = pcVar16 + -1;
            for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
              *(undefined4 *)pcVar17 = *(undefined4 *)pcVar12;
              pcVar12 = pcVar12 + 4;
              pcVar17 = pcVar17 + 4;
            }
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *pcVar17 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              pcVar17 = pcVar17 + 1;
            }
            iVar7 = -1;
            pcVar12 = acStack_448;
            do {
              pcVar17 = pcVar12;
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              pcVar17 = pcVar12 + 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar17;
            } while (cVar1 != '\0');
            *(undefined2 *)(pcVar17 + -1) = DAT_005c7c48;
          }
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 3;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[3] = acStack_448;
          apcStackY_4f8[4] = (char *)0x3;
          apcStackY_4f8[2] = (char *)0x472423;
          FUN_00466340();
          pcStackY_4e0 = acStack_448;
          pcVar12 = acStack_448;
          for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
            pcVar12[0] = '\0';
            pcVar12[1] = '\0';
            pcVar12[2] = '\0';
            pcVar12[3] = '\0';
            pcVar12 = pcVar12 + 4;
          }
          pcVar12[0] = '\0';
          pcVar12[1] = '\0';
          iStackY_4e4 = *(int *)(pcVar10 + -10);
          local_4c0[2] = 44.0;
          local_4c0[0] = 491.0;
          apcStackY_4f8[4] = (char *)0x472458;
          FUN_0050aaa9();
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 4;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[3] = acStack_448;
          apcStackY_4f8[4] = (char *)0x4;
          apcStackY_4f8[2] = (char *)0x472498;
          FUN_00466340();
          pcStackY_4e0 = (char *)0x4724a5;
          (**(code **)(*piVar5 + 0x54))();
          local_4a8 = local_4a8 + 0x11;
          pcStackY_4e0 = (char *)0x4724bd;
          FUN_00467950();
        }
        if (pcVar10[-2] == '\x02') {
          pcStackY_4e0 = (char *)0x4724d2;
          pvVar2 = operator_new(0x50);
          local_4 = CONCAT31(local_4._1_3_,9);
          if (pvVar2 == (void *)0x0) {
            piVar5 = (int *)0x0;
          }
          else {
            piVar5 = (int *)FUN_00465610();
          }
          local_4c0[1] = (float)iStack_4a4;
          local_4c0[2] = 424.0;
          local_4c0[3] = 17.0;
          local_4c0[0] = 111.0;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8 + 2;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          apcStackY_4f8[1] = (char *)0x0;
          apcStackY_4f8[0] = (char *)0x5;
          local_4 = CONCAT31(local_4._1_3_,7);
          FUN_00466720();
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 0;
          local_4c0[2] = 122.0;
          local_4c0[0] = 111.0;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          if (*pcVar10 == '\0') {
            apcStackY_4f8[3] = *(char **)(pcVar10 + 2);
            pcStackY_4e0 = (char *)0x0;
            iStackY_4e4 = 0;
            apcStackY_4f8[4] = (char *)0x0;
            apcStackY_4f8[2] = (char *)0x472580;
            FUN_00466340();
          }
          if (*pcVar10 == '\x01') {
            apcStackY_4f8[3] = *(char **)(pcVar10 + 2);
            pcStackY_4e0 = (char *)0xff;
            iStackY_4e4 = 0xff;
            apcStackY_4f8[4] = (char *)0x0;
            apcStackY_4f8[2] = (char *)0x4725a2;
            FUN_00466340();
          }
          if (*pcVar10 == '\x02') {
            apcStackY_4f8[3] = *(char **)(pcVar10 + 2);
            pcStackY_4e0 = (char *)0x0;
            iStackY_4e4 = 200;
            apcStackY_4f8[4] = (char *)0x0;
            apcStackY_4f8[2] = "j";
            FUN_00466340();
          }
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 1;
          local_4c0[2] = 95.0;
          local_4c0[0] = 233.0;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          apcStackY_4f8[3] = *(char **)(pcVar10 + 0xe);
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[4] = (char *)0x1;
          apcStackY_4f8[2] = "j";
          FUN_00466340();
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 2;
          local_4c0[2] = 61.0;
          local_4c0[0] = 327.0;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          apcStackY_4f8[3] = *(char **)(pcVar10 + 0x1a);
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[4] = (char *)0x2;
          apcStackY_4f8[2] = (char *)0x472650;
          FUN_00466340();
          pcStackY_4e0 = acStack_47c;
          pcVar12 = acStack_47c;
          for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
            pcVar12[0] = '\0';
            pcVar12[1] = '\0';
            pcVar12[2] = '\0';
            pcVar12[3] = '\0';
            pcVar12 = pcVar12 + 4;
          }
          pcVar12[0] = '\0';
          pcVar12[1] = '\0';
          iStackY_4e4 = *(int *)(pcVar10 + -0xe);
          local_4c0[2] = 102.0;
          local_4c0[0] = 389.0;
          apcStackY_4f8[4] = (char *)0x47267f;
          FUN_0050aaa9();
          iStackY_4e4 = *(int *)(pcVar10 + -6);
          if (iStackY_4e4 != 0) {
            pcVar12 = acStack_244;
            for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
              pcVar12[0] = '\0';
              pcVar12[1] = '\0';
              pcVar12[2] = '\0';
              pcVar12[3] = '\0';
              pcVar12 = pcVar12 + 4;
            }
            pcVar12[0] = '\0';
            pcVar12[1] = '\0';
            iVar7 = -1;
            pcVar12 = acStack_47c;
            do {
              pcVar17 = pcVar12;
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              pcVar17 = pcVar12 + 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar17;
            } while (cVar1 != '\0');
            *(undefined2 *)(pcVar17 + -1) = DAT_005c7c4c;
            pcStackY_4e0 = acStack_244;
            pcVar17[1] = DAT_005c7c4e;
            apcStackY_4f8[4] = (char *)0x4726cd;
            FUN_0050aaa9();
            uVar8 = 0xffffffff;
            pcVar12 = acStack_244;
            do {
              pcVar17 = pcVar12;
              if (uVar8 == 0) break;
              uVar8 = uVar8 - 1;
              pcVar17 = pcVar12 + 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar17;
            } while (cVar1 != '\0');
            uVar8 = ~uVar8;
            iVar7 = -1;
            pcVar12 = acStack_47c;
            do {
              pcVar16 = pcVar12;
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              pcVar16 = pcVar12 + 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar16;
            } while (cVar1 != '\0');
            pcVar12 = pcVar17 + -uVar8;
            pcVar17 = pcVar16 + -1;
            for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
              *(undefined4 *)pcVar17 = *(undefined4 *)pcVar12;
              pcVar12 = pcVar12 + 4;
              pcVar17 = pcVar17 + 4;
            }
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *pcVar17 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              pcVar17 = pcVar17 + 1;
            }
            iVar7 = -1;
            pcVar12 = acStack_47c;
            do {
              pcVar17 = pcVar12;
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              pcVar17 = pcVar12 + 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar17;
            } while (cVar1 != '\0');
            *(undefined2 *)(pcVar17 + -1) = DAT_005c7c48;
          }
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 3;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[3] = acStack_47c;
          apcStackY_4f8[4] = (char *)0x3;
          apcStackY_4f8[2] = (char *)0x472751;
          FUN_00466340();
          pcStackY_4e0 = acStack_47c;
          pcVar12 = acStack_47c;
          for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
            pcVar12[0] = '\0';
            pcVar12[1] = '\0';
            pcVar12[2] = '\0';
            pcVar12[3] = '\0';
            pcVar12 = pcVar12 + 4;
          }
          pcVar12[0] = '\0';
          pcVar12[1] = '\0';
          iStackY_4e4 = *(int *)(pcVar10 + -10);
          local_4c0[2] = 44.0;
          local_4c0[0] = 491.0;
          apcStackY_4f8[4] = (char *)0x472780;
          FUN_0050aaa9();
          pcStackY_4e0 = (char *)0x0;
          iStackY_4e4 = 4;
          pfVar13 = local_4c0;
          ppcVar18 = apcStackY_4f8;
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *ppcVar18 = (char *)*pfVar13;
            pfVar13 = pfVar13 + 1;
            ppcVar18 = ppcVar18 + 1;
          }
          FUN_00466a10();
          pcStackY_4e0 = (char *)0xff;
          iStackY_4e4 = 0xff;
          apcStackY_4f8[3] = acStack_47c;
          apcStackY_4f8[4] = (char *)0x4;
          apcStackY_4f8[2] = (char *)0x4727bd;
          FUN_00466340();
          pcStackY_4e0 = (char *)0x4727ca;
          (**(code **)(*piVar5 + 0x54))();
          iStack_4a4 = iStack_4a4 + 0x11;
          pcStackY_4e0 = (char *)0x4727e2;
          FUN_00467950();
        }
        piVar5 = (int *)(pcVar10 + 0x26);
        pcVar10 = pcVar10 + 0x34;
      } while (piVar5 != piStack_484);
    }
    pcStackY_4e0 = (char *)0x3;
    iStackY_4e4 = 0x472805;
    FUN_00468230();
    pcStackY_4e0 = (char *)0x3;
    iStackY_4e4 = 0x472810;
    FUN_00468230();
    pcStackY_4e0 = (char *)0x0;
    iStackY_4e4 = 0x47281e;
    FUN_0046f520();
    pcStackY_4e0 = (char *)0x1;
    iStackY_4e4 = 0x47282d;
    FUN_0046f520();
  }
  local_4._0_1_ = 0xc;
  piVar6 = local_488;
  for (piVar5 = local_488; piVar5 != piStack_484; piVar5 = piVar5 + 0xd) {
    pcStackY_4e0 = (char *)0x472baa;
    local_488 = piVar6;
    FUN_00473590();
    piVar6 = local_488;
  }
  local_4._0_1_ = 0xb;
  iVar7 = (iStack_480 - (int)piVar6) / 0x34;
  if (iVar7 != 0) {
    uVar8 = iVar7 * 0x34;
    if (uVar8 < 0x81) {
      pcStackY_4e0 = (char *)&DAT_005d59e8;
      iStackY_4e4 = 0x472c15;
      iVar7 = FUN_00443110();
      uVar9 = DAT_005c4248;
      if (iVar7 != 0) {
        uVar14 = 0;
        if (DAT_005c4248 != 0) {
          uVar11 = DAT_005d59ec >> 1;
          do {
            if ((uVar11 <= uVar14) && (DAT_005d59e8 == 0)) {
              pcStackY_4e0 = (char *)&DAT_005d59e8;
              iStackY_4e4 = 0x472c56;
              iVar7 = FUN_00443110();
              if (iVar7 == 0) {
                DAT_005c4248 = 1000;
                DAT_005d59ec = uVar14;
                goto LAB_00472cea;
              }
            }
            uVar14 = uVar14 + 1;
          } while (uVar14 < uVar9);
        }
        DAT_005c4248 = 0x1e;
        while( true ) {
          pcStackY_4e0 = (char *)&DAT_005d59e8;
          iStackY_4e4 = 0x472cd7;
          iVar7 = FUN_00443110();
          if (iVar7 == 0) break;
          pcStackY_4e0 = (char *)0x472ce4;
          FUN_00443130();
        }
      }
LAB_00472cea:
      *piVar6 = *(int *)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4) = piVar6;
      DAT_005d59e8 = 0;
    }
    else {
      pcStackY_4e0 = (char *)0x472bf0;
      FUN_005089fd();
    }
  }
  puVar4 = local_494;
  uVar8 = local_48c - (int)local_494;
  local_4 = CONCAT31(local_4._1_3_,2);
  if (uVar8 != 0) {
    if (uVar8 < 0x81) {
      pcStackY_4e0 = (char *)&DAT_005d59e8;
      iStackY_4e4 = 0x472d48;
      iVar7 = FUN_00443110();
      uVar9 = DAT_005c4248;
      if (iVar7 != 0) {
        uVar14 = 0;
        if (DAT_005c4248 != 0) {
          uVar11 = DAT_005d59ec >> 1;
          do {
            if ((uVar11 <= uVar14) && (DAT_005d59e8 == 0)) {
              pcStackY_4e0 = (char *)&DAT_005d59e8;
              iStackY_4e4 = 0x472d89;
              iVar7 = FUN_00443110();
              if (iVar7 == 0) {
                DAT_005c4248 = 1000;
                DAT_005d59ec = uVar14;
                goto LAB_00472e1d;
              }
            }
            uVar14 = uVar14 + 1;
          } while (uVar14 < uVar9);
        }
        DAT_005c4248 = 0x1e;
        while( true ) {
          pcStackY_4e0 = (char *)&DAT_005d59e8;
          iStackY_4e4 = 0x472e0a;
          iVar7 = FUN_00443110();
          if (iVar7 == 0) break;
          pcStackY_4e0 = (char *)0x472e17;
          FUN_00443130();
        }
      }
LAB_00472e1d:
      *puVar4 = *(undefined4 *)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4) = puVar4;
      DAT_005d59e8 = 0;
    }
    else {
      pcStackY_4e0 = (char *)0x472d23;
      FUN_005089fd();
    }
  }
  uVar8 = iStack_248 - (int)local_250[0];
  local_4 = 0xd;
  if ((local_250[0] != (undefined4 *)0x0) && (uVar8 != 0)) {
    if (uVar8 < 0x81) {
      FUN_00402330();
      *local_250[0] = *(undefined4 *)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4) = local_250[0];
      FUN_00443330();
    }
    else {
      pcStackY_4e0 = (char *)0x472e61;
      FUN_005089fd();
    }
  }
  uVar8 = iStack_254 - (int)local_25c[0];
  local_4 = 0xffffffff;
  if ((local_25c[0] != (undefined4 *)0x0) && (uVar8 != 0)) {
    if (uVar8 < 0x81) {
      FUN_00402330();
      *local_25c[0] = *(undefined4 *)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4) = local_25c[0];
      FUN_00443330();
    }
    else {
      pcStackY_4e0 = (char *)0x472ebd;
      FUN_005089fd();
    }
  }
  ExceptionList = pvStack_c;
  return 1;
}

