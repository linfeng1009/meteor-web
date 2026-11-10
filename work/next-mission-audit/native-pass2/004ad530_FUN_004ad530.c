/* Original Meteor.exe static export @ 004ad530; original sample not executed. */
/* XREF 005a9c54 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall
FUN_004ad530(int *param_1,undefined **param_2,uint param_3,uint *param_4,uint param_5)

{
  undefined *puVar1;
  undefined **ppuVar2;
  undefined **ppuVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  undefined ***pppuVar8;
  undefined **ppuVar9;
  int iVar10;
  undefined4 uVar11;
  uint *puVar12;
  int iVar13;
  char *pcVar14;
  char cVar15;
  float *pfVar16;
  undefined **ppuVar17;
  float *pfVar18;
  float afStack_18c [9];
  char *pcStack_168;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  char *pcStack_144;
  uint uStack_140;
  undefined ***pppuStack_13c;
  undefined *puStack_138;
  undefined ***pppuStack_134;
  undefined ***pppuStack_130;
  undefined ***pppuStack_12c;
  char *pcStack_118;
  char *pcStack_114;
  char *pcStack_110;
  undefined **ppuStack_10c;
  undefined **ppuStack_108;
  undefined **ppuStack_104;
  uint uStack_100;
  undefined **ppuStack_fc;
  undefined **ppuStack_f8;
  undefined **ppuStack_f4;
  undefined4 uStack_f0;
  undefined **ppuStack_ec;
  uint uStack_e8;
  uint uStack_e4;
  undefined **appuStack_e0 [2];
  uint uStack_d8;
  undefined **ppuStack_d4;
  float fStack_d0;
  float fStack_cc;
  undefined **ppuStack_c0;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined **ppuStack_8c;
  undefined **ppuStack_88;
  undefined **ppuStack_84;
  undefined **ppuStack_80;
  undefined **ppuStack_7c;
  undefined **ppuStack_78;
  undefined **ppuStack_74;
  undefined **ppuStack_70;
  float afStack_6c [3];
  uint uStack_60;
  uint uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined **ppuStack_4;
  
  puVar12 = param_4;
  ppuStack_4 = (undefined **)0xffffffff;
  puStack_8 = &LAB_005a01ed;
  pvStack_c = ExceptionList;
  switch(param_3 & 0xffff) {
  case 1:
    pppuStack_12c = (undefined ***)param_5;
    pppuStack_130 = (undefined ***)param_4;
    pppuStack_134 = (undefined ***)param_2;
    puStack_138 = (undefined *)0x4ad58d;
    ExceptionList = &pvStack_c;
    (**(code **)(*param_1 + 0x60))();
    break;
  case 3:
    appuStack_e0[0] = (undefined **)CONCAT31(appuStack_e0[0]._1_3_,(char)param_2);
    appuStack_e0[1] = (undefined **)(*param_4 & 0xff);
    pppuStack_12c = (undefined ***)0x0;
    ppuStack_f4 = (undefined **)(param_4[1] >> 8);
    uStack_f0 = 0;
    pppuStack_134 = appuStack_e0;
    pppuStack_130 = (undefined ***)0x18;
    puStack_138 = (undefined *)0x7;
    fStack_d0 = (float)(param_4[1] & 0xff) * _DAT_005a8410 - _DAT_005a8b80;
    uStack_d8 = *param_4 >> 8;
    pppuStack_13c = (undefined ***)param_2;
    fStack_cc = (float)ppuStack_f4 * _DAT_005a9d2c;
    uStack_140 = 0x4ad60c;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 4:
    puVar1 = (undefined *)*param_4;
    pcVar14 = (char *)param_4[2];
    pppuStack_12c = (undefined ***)0x4adb16;
    ExceptionList = &pvStack_c;
    piVar7 = (int *)FUN_00487830();
    pppuStack_12c = (undefined ***)&pcStack_118;
    pppuStack_134 = (undefined ***)0x4adb26;
    pppuStack_130 = (undefined ***)puVar1;
    (**(code **)(*piVar7 + 0x2c8))();
    if (pcStack_114 != pcVar14) {
      pppuStack_130 = (undefined ***)0x44;
LAB_004adb36:
      pppuStack_134 = (undefined ***)0x4adb41;
      pppuStack_12c = (undefined ***)param_2;
      (**(code **)(*param_1 + 0x11c))();
      pppuStack_12c = (undefined ***)0x80;
      pppuStack_130 = (undefined ***)param_2;
      pppuStack_134 = (undefined ***)0x4adb56;
      FUN_0054ea00();
      ExceptionList = pvStack_c;
      return 0;
    }
    pppuStack_12c = &ppuStack_7c;
    pppuStack_130 = &ppuStack_10c;
    ppuStack_7c = param_2;
    pppuStack_134 = (undefined ***)0x4adb85;
    FUN_0049d3c0();
    if (ppuStack_10c != (undefined **)param_1[0xea]) {
      ppuStack_10c[0x80] = (undefined *)0x1;
      appuStack_e0[0] = param_2;
      if (ppuStack_10c[0x31] == (undefined *)0x0) {
        uStack_d8 = 0;
      }
      else {
        uStack_d8 = *(uint *)(ppuStack_10c[0x31] + 0x28);
      }
      pppuStack_130 = (undefined ***)puVar12[1];
      ppuStack_fc = (undefined **)pppuStack_130;
      appuStack_e0[1] = (undefined **)puVar1;
      if (pppuStack_130 != (undefined ***)0x0) {
        ppuStack_ec = (undefined **)0x0;
        uStack_e8 = 0;
        uStack_e4 = 0;
        pppuStack_12c = &ppuStack_ec;
        ppuStack_4 = (undefined **)0x0;
        pppuStack_134 = (undefined ***)0x4adc00;
        (**(code **)(param_1[0xe9] + 0x20))();
        if (7 < (uint)((int)(uStack_e8 - (int)ppuStack_ec) >> 2)) {
          pppuStack_12c = (undefined ***)0x1;
          pppuStack_134 = &ppuStack_fc;
          ppuStack_fc = (undefined **)(2 - (ppuStack_fc != (undefined **)0x1));
          pppuStack_130 = (undefined ***)0x4;
          puStack_138 = (undefined *)0x29;
          pppuStack_13c = (undefined ***)param_2;
          uStack_140 = 0x4adc3c;
          FUN_004acae0();
        }
        ppuStack_4 = (undefined **)0xffffffff;
        iVar10 = (int)(uStack_e4 - (int)ppuStack_ec) >> 2;
        if (iVar10 != 0) {
          pppuStack_12c = (undefined ***)(iVar10 * 4);
          pppuStack_130 = (undefined ***)ppuStack_ec;
          pppuStack_134 = (undefined ***)0x4adc64;
          FUN_00402e90();
        }
      }
      pppuStack_12c = (undefined ***)0x1;
      pppuStack_130 = (undefined ***)0x10;
      ppuStack_10c[0x82] = (undefined *)ppuStack_fc;
      ppuStack_d4 = ppuStack_fc;
      ppuStack_10c[0x81] = (undefined *)appuStack_e0[1];
      pppuStack_134 = appuStack_e0;
      puStack_138 = (undefined *)0x9;
      pppuStack_13c = (undefined ***)0x4adc9e;
      (**(code **)(*param_1 + 0x40))();
      pppuStack_13c = (undefined ***)&pcStack_114;
      uStack_140 = 0x4adcb2;
      uVar11 = (**(code **)(param_1[0xe9] + 0x28))();
      if (pcStack_118 != (char *)0x0) {
        uStack_140 = 1;
        pcStack_144 = pcStack_118;
        uStack_14c = 0x2f;
        uStack_150 = uStack_10;
        uStack_154 = 0x4adcd1;
        uStack_148 = uVar11;
        FUN_004acae0();
        pcStack_144 = (char *)0x4adcd7;
        uStack_140 = uVar11;
        FUN_00507850();
      }
      uStack_140 = uStack_10;
      pcStack_144 = (char *)0x4adced;
      (**(code **)(*param_1 + 0x128))();
    }
    break;
  case 5:
    pppuStack_12c = (undefined ***)param_5;
    pppuStack_130 = (undefined ***)param_4;
    pppuStack_134 = (undefined ***)param_2;
    puStack_138 = (undefined *)0x4add3a;
    ExceptionList = &pvStack_c;
    (**(code **)(*param_1 + 100))();
    break;
  case 6:
    pppuStack_12c = &ppuStack_f8;
    pppuStack_130 = &ppuStack_104;
    ppuStack_f8 = param_2;
    pppuStack_134 = (undefined ***)0x4adee0;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    pppuStack_12c = (undefined ***)0x1;
    ppuVar2 = (undefined **)*param_4;
    pppuStack_134 = (undefined ***)0x4adeff;
    pppuStack_130 = (undefined ***)ppuVar2;
    (**(code **)(ppuStack_104[0x22] + 0x14))();
    pppuStack_12c = (undefined ***)0x1;
    pppuStack_134 = &ppuStack_10c;
    pppuStack_130 = (undefined ***)0x8;
    puStack_138 = (undefined *)0xc;
    pppuStack_13c = (undefined ***)param_2;
    ppuStack_108 = param_2;
    uStack_140 = 0x4adf21;
    ppuStack_10c = ppuVar2;
    FUN_004acb00();
    break;
  case 7:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_130 = (undefined ***)0x18;
    appuStack_e0[1] = (undefined **)*param_4;
    ppuStack_d4 = (undefined **)param_4[1];
    pppuStack_134 = appuStack_e0;
    puStack_138 = (undefined *)0xd;
    pppuStack_13c = (undefined ***)param_2;
    appuStack_e0[0] = (undefined **)CONCAT31(appuStack_e0[0]._1_3_,(char)param_2);
    uStack_140 = 0x4ad92f;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 8:
    pppuStack_12c = &ppuStack_78;
    pppuStack_130 = &ppuStack_10c;
    ppuStack_78 = param_2;
    pppuStack_134 = (undefined ***)0x4ad7bf;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    if (*param_4 == 0) {
      ppuStack_10c[0x83] = (undefined *)0x0;
    }
    else {
      ppuStack_10c[0x83] = (undefined *)0x1;
    }
    break;
  case 9:
    uVar6 = param_5 / 0x1c;
    ExceptionList = &pvStack_c;
    if (uVar6 != 0) {
      ExceptionList = &pvStack_c;
      do {
        *puVar12 = *puVar12 | (int)param_2 << 0xc;
        puVar12 = puVar12 + 7;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_130 = (undefined ***)param_5;
    pppuStack_134 = (undefined ***)param_4;
    puStack_138 = (undefined *)0xf;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ad97a;
    FUN_004acb00();
    break;
  case 10:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = &ppuStack_10c;
    pppuStack_130 = (undefined ***)0x4;
    ppuStack_10c = (undefined **)*param_4;
    puStack_138 = (undefined *)0x10;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ad9a6;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0xb:
    pppuVar8 = appuStack_e0;
    for (iVar10 = 0x15; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppuVar8 = (undefined **)*puVar12;
      puVar12 = puVar12 + 1;
      pppuVar8 = pppuVar8 + 1;
    }
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = appuStack_e0;
    pppuStack_130 = (undefined ***)0x54;
    puStack_138 = (undefined *)0x11;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ad9d7;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0xc:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = appuStack_e0;
    pppuStack_130 = (undefined ***)0x54;
    pppuVar8 = appuStack_e0;
    for (iVar10 = 0x15; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppuVar8 = (undefined **)*puVar12;
      puVar12 = puVar12 + 1;
      pppuVar8 = pppuVar8 + 1;
    }
    puStack_138 = (undefined *)0x12;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ada2b;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0xd:
    pppuVar8 = appuStack_e0;
    for (iVar10 = 0x15; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppuVar8 = (undefined **)*puVar12;
      puVar12 = puVar12 + 1;
      pppuVar8 = pppuVar8 + 1;
    }
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = appuStack_e0;
    pppuStack_130 = (undefined ***)0x54;
    puStack_138 = (undefined *)0x13;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ada5c;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0xe:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = &ppuStack_10c;
    pppuStack_130 = (undefined ***)0x4;
    puStack_138 = (undefined *)0x14;
    pppuStack_13c = (undefined ***)param_2;
    ppuStack_10c = param_2;
    uStack_140 = 0x4ad9fa;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0xf:
    pppuStack_12c = (undefined ***)0x8;
    pcStack_118 = (char *)0x0;
    pcStack_114 = (char *)0x0;
    pcStack_110 = (char *)0x0;
    pppuStack_130 = (undefined ***)0x4ae0ab;
    ExceptionList = &pvStack_c;
    FUN_004608a0();
    ppuStack_4 = (undefined **)0x3;
    pppuStack_12c = (undefined ***)0x4ae0bf;
    FUN_00402a70();
    cVar15 = (char)param_2 + '\x01';
    ppuStack_4 = (undefined **)0x4;
    if (pcStack_114 + 1 == pcStack_110) {
      ppuStack_104 = (undefined **)0x1;
      ppuStack_10c = (undefined **)(pcStack_114 + -(int)pcStack_118);
      pppuVar8 = &ppuStack_104;
      if (ppuStack_10c != (undefined **)0x0) {
        pppuVar8 = &ppuStack_10c;
      }
      pppuStack_12c = (undefined ***)((int)*pppuVar8 + (int)ppuStack_10c);
      pppuStack_130 = (undefined ***)0x4ae10f;
      FUN_0049be40();
    }
    pppuStack_12c = (undefined ***)(pcStack_114 + 1);
    pppuStack_130 = (undefined ***)0x4ae11e;
    FUN_00402bc0();
    *pcStack_114 = cVar15;
    pcStack_114 = pcStack_114 + 1;
    puVar12 = param_4;
    uVar6 = param_5;
    if (0 < (int)param_5) {
      do {
        uVar5 = *puVar12;
        if (pcStack_114 + 1 == pcStack_110) {
          ppuStack_104 = (undefined **)0x1;
          ppuStack_10c = (undefined **)(pcStack_114 + -(int)pcStack_118);
          pppuVar8 = &ppuStack_104;
          if (ppuStack_10c != (undefined **)0x0) {
            pppuVar8 = &ppuStack_10c;
          }
          pppuStack_12c = (undefined ***)((int)*pppuVar8 + (int)ppuStack_10c);
          pppuStack_130 = (undefined ***)0x4ae17b;
          FUN_0049be40();
        }
        pppuStack_12c = (undefined ***)(pcStack_114 + 1);
        pppuStack_130 = (undefined ***)0x4ae18a;
        FUN_00402bc0();
        *pcStack_114 = (char)uVar5;
        pcStack_114 = pcStack_114 + 1;
        uVar6 = uVar6 - 1;
        puVar12 = (uint *)((int)puVar12 + 1);
      } while (uVar6 != 0);
    }
    pppuStack_130 = (undefined ***)((int)pcStack_114 - (int)pcStack_118);
    pppuStack_12c = (undefined ***)0x1;
    pppuStack_134 = (undefined ***)pcStack_118;
    puStack_138 = (undefined *)0x15;
    pppuStack_13c = (undefined ***)0x4ae1b3;
    (**(code **)(*param_1 + 0x40))();
    pcVar14 = pcStack_118;
    uVar6 = (int)pcStack_110 - (int)pcStack_118;
    if ((pcStack_118 != (char *)0x0) && (uVar6 != 0)) {
      if (uVar6 < 0x81) {
        pppuStack_12c = (undefined ***)0x4ae1fb;
        FUN_00402330();
        *(undefined4 *)pcVar14 = *(undefined4 *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
        *(char **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = pcVar14;
        DAT_005d59e8 = 0;
      }
      else {
        pppuStack_12c = (undefined ***)pcStack_118;
        pppuStack_130 = (undefined ***)0x4ae1da;
        FUN_005089fd();
      }
    }
    break;
  case 0x10:
    pppuStack_12c = &ppuStack_f4;
    pppuStack_130 = &ppuStack_10c;
    ppuStack_f4 = param_2;
    pppuStack_134 = (undefined ***)0x4ae232;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    if (ppuStack_10c == (undefined **)param_1[0xea]) {
      ExceptionList = pvStack_c;
      return 0;
    }
    pppuStack_12c = (undefined ***)0x8;
    pcStack_118 = (char *)0x0;
    pcStack_114 = (char *)0x0;
    pcStack_110 = (char *)0x0;
    pppuStack_130 = (undefined ***)0x4ae258;
    pcStack_118 = (char *)FUN_00402bf0();
    pcStack_110 = pcStack_118 + 8;
    ppuStack_4 = (undefined **)0x5;
    pppuStack_12c = (undefined ***)0x4ae27e;
    pcStack_114 = pcStack_118;
    FUN_00402a70();
    cVar15 = (char)param_2 + '\x01';
    ppuStack_4 = (undefined **)0x6;
    if (pcStack_114 + 1 == pcStack_110) {
      ppuStack_104 = (undefined **)0x1;
      ppuStack_fc = (undefined **)(pcStack_114 + -(int)pcStack_118);
      pppuVar8 = &ppuStack_104;
      if (ppuStack_fc != (undefined **)0x0) {
        pppuVar8 = &ppuStack_fc;
      }
      pppuStack_12c = (undefined ***)((int)*pppuVar8 + (int)ppuStack_fc);
      pppuStack_130 = (undefined ***)0x4ae2ce;
      FUN_0049be40();
    }
    pppuStack_12c = (undefined ***)(pcStack_114 + 1);
    pppuStack_130 = (undefined ***)0x4ae2dd;
    FUN_00402bc0();
    *pcStack_114 = cVar15;
    pcVar14 = pcStack_114 + 1;
    puVar12 = param_4;
    uVar6 = param_5;
    if (0 < (int)param_5) {
      do {
        uVar5 = *puVar12;
        pcStack_114 = pcVar14;
        if (pcVar14 + 1 == pcStack_110) {
          ppuStack_fc = (undefined **)(pcVar14 + -(int)pcStack_118);
          ppuStack_104 = (undefined **)0x1;
          pppuVar8 = &ppuStack_104;
          if (ppuStack_fc != (undefined **)0x0) {
            pppuVar8 = &ppuStack_fc;
          }
          pppuStack_12c = (undefined ***)((int)*pppuVar8 + (int)ppuStack_fc);
          pppuStack_130 = (undefined ***)0x4ae33c;
          FUN_0049be40();
        }
        pppuStack_12c = (undefined ***)(pcStack_114 + 1);
        pppuStack_130 = (undefined ***)0x4ae34b;
        FUN_00402bc0();
        *pcStack_114 = (char)uVar5;
        pcVar14 = pcStack_114 + 1;
        uVar6 = uVar6 - 1;
        puVar12 = (uint *)((int)puVar12 + 1);
      } while (uVar6 != 0);
    }
    iVar10 = *(int *)(param_1[0xea] + 8);
    pcStack_114 = pcVar14;
    if (iVar10 != param_1[0xea]) {
      do {
        if (((uint)ppuStack_10c[0x82] & *(uint *)(iVar10 + 0x208)) != 0) {
          pppuStack_12c = (undefined ***)0x1;
          pppuStack_130 = (undefined ***)((int)pcVar14 - (int)pcStack_118);
          pppuStack_134 = (undefined ***)pcStack_118;
          pppuStack_13c = *(undefined ****)(iVar10 + 0x10);
          puStack_138 = (undefined *)0x16;
          uStack_140 = 0x4ae394;
          FUN_004acae0();
          pcVar14 = pcStack_114;
        }
        iVar13 = *(int *)(iVar10 + 0xc);
        if (iVar13 == 0) {
          iVar13 = *(int *)(iVar10 + 4);
          if (iVar10 == *(int *)(iVar13 + 0xc)) {
            do {
              iVar10 = iVar13;
              iVar13 = *(int *)(iVar10 + 4);
            } while (iVar10 == *(int *)(iVar13 + 0xc));
          }
          if (*(int *)(iVar10 + 0xc) != iVar13) {
            iVar10 = iVar13;
          }
        }
        else {
          for (iVar4 = *(int *)(iVar13 + 8); iVar10 = iVar13, iVar4 != 0;
              iVar4 = *(int *)(iVar4 + 8)) {
            iVar13 = iVar4;
          }
        }
      } while (iVar10 != param_1[0xea]);
    }
    pcVar14 = pcStack_118;
    uVar6 = (int)pcStack_110 - (int)pcStack_118;
    if ((pcStack_118 != (char *)0x0) && (uVar6 != 0)) {
      if (uVar6 < 0x81) {
        pppuStack_12c = (undefined ***)0x4ae41c;
        FUN_00402330();
        *(undefined4 *)pcVar14 = *(undefined4 *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
        *(char **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = pcVar14;
        DAT_005d59e8 = 0;
      }
      else {
        pppuStack_12c = (undefined ***)pcStack_118;
        pppuStack_130 = (undefined ***)0x4ae3fb;
        FUN_005089fd();
      }
    }
    break;
  case 0x12:
    pppuStack_12c = &ppuStack_74;
    pppuStack_130 = &ppuStack_10c;
    ppuStack_74 = param_2;
    pppuStack_134 = (undefined ***)0x4ad819;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    if (ppuStack_10c != (undefined **)param_1[0xea]) {
      pppuStack_12c = (undefined ***)0x0;
      pppuStack_130 = (undefined ***)0x6;
      pppuStack_134 = (undefined ***)0x4ad836;
      uVar6 = (**(code **)(ppuStack_10c[0x22] + 0x34))();
      if (uVar6 < 100) {
        pppuStack_134 = (undefined ***)ppuStack_4;
        puStack_138 = (undefined *)0x4a;
        pppuStack_13c = (undefined ***)0x4ad850;
        (**(code **)(*param_1 + 0x11c))();
      }
      pppuStack_134 = (undefined ***)0x0;
      puStack_138 = (undefined *)0x6;
      pppuStack_13c = (undefined ***)0x4ad863;
      (**(code **)(*(int *)(pcStack_114 + 0x88) + 0x28))();
    }
    break;
  case 0x13:
    pppuStack_12c = (undefined ***)0x4ae025;
    ExceptionList = &pvStack_c;
    FUN_005498c0();
    uStack_60 = *param_4;
    uStack_5c = param_4[1];
    puVar12 = param_4;
    pppuVar8 = appuStack_e0;
    for (iVar10 = 8; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppuVar8 = (undefined **)*puVar12;
      puVar12 = puVar12 + 1;
      pppuVar8 = pppuVar8 + 1;
    }
    pppuStack_12c = (undefined ***)afStack_6c;
    ppuStack_c0 = param_2;
    pppuStack_130 = (undefined ***)param_2;
    uStack_58 = 0;
    pppuStack_134 = (undefined ***)0x4ae073;
    (**(code **)(*param_1 + 0x78))();
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = appuStack_e0;
    pppuStack_130 = (undefined ***)0x24;
    puStack_138 = (undefined *)0x1e;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ae08d;
    FUN_004acb00();
    break;
  case 0x14:
    pppuStack_12c = (undefined ***)0x4adf32;
    ExceptionList = &pvStack_c;
    FUN_005498c0();
    puVar12 = param_4;
    uStack_58 = 0;
    uStack_5c = param_4[1];
    pppuStack_12c = &ppuStack_104;
    uStack_60 = *param_4;
    iVar10 = *param_1;
    afStack_6c[0] = (float)(int)param_4[2] * _DAT_005a83ec;
    afStack_6c[1] = (float)(int)param_4[3] * _DAT_005a83ec;
    afStack_6c[2] = (float)(int)param_4[4] * _DAT_005a83ec;
    pfVar16 = afStack_6c;
    pfVar18 = afStack_18c;
    for (iVar13 = 0x18; iVar13 != 0; iVar13 = iVar13 + -1) {
      *pfVar18 = *pfVar16;
      pfVar16 = pfVar16 + 1;
      pfVar18 = pfVar18 + 1;
    }
    (**(code **)(iVar10 + 0x74))();
    pppuStack_13c = (undefined ***)puVar12[1];
    uStack_140 = *puVar12;
    pppuStack_130 = (undefined ***)puVar12[4];
    pppuStack_134 = (undefined ***)puVar12[3];
    pcStack_144 = pcStack_168;
    puStack_138 = (undefined *)puVar12[2];
    (**(code **)(*param_1 + 0x40))(0x1f,&pcStack_144,0x18,1);
    break;
  case 0x15:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_130 = (undefined ***)0x10;
    appuStack_e0[1] = (undefined **)*param_4;
    appuStack_e0[0] = param_2;
    uStack_d8 = param_4[1];
    ppuStack_d4 = (undefined **)param_4[2];
    pppuStack_134 = appuStack_e0;
    puStack_138 = (undefined *)0x27;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ad711;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0x16:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_130 = (undefined ***)0xc;
    uStack_e8 = *param_4;
    uStack_e4 = param_4[1];
    pppuStack_134 = &ppuStack_ec;
    puStack_138 = (undefined *)0x2a;
    pppuStack_13c = (undefined ***)param_2;
    ppuStack_ec = param_2;
    uStack_140 = 0x4ad748;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0x17:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_130 = (undefined ***)0x18;
    appuStack_e0[1] = (undefined **)*param_4;
    appuStack_e0[0] = param_2;
    uStack_d8 = param_4[1];
    ppuStack_d4 = (undefined **)param_4[2];
    fStack_d0 = (float)param_4[3];
    fStack_cc = (float)param_4[4];
    pppuStack_134 = appuStack_e0;
    puStack_138 = (undefined *)0x2b;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ad794;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0x18:
    pppuStack_12c = (undefined ***)0x1;
    pppuStack_130 = (undefined ***)0x8;
    uStack_100 = *param_4;
    pppuStack_134 = &ppuStack_104;
    puStack_138 = (undefined *)0x31;
    pppuStack_13c = (undefined ***)param_2;
    ppuStack_104 = param_2;
    uStack_140 = 0x4ae56c;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0x19:
  case 0x1a:
    pcStack_118 = (char *)CONCAT22((short)*param_4,(short)param_2);
    pcStack_114 = *(char **)((int)param_4 + 2);
    pcStack_110 = (char *)CONCAT22(pcStack_110._2_2_,*(undefined2 *)((int)param_4 + 6));
    puStack_138 = (undefined *)0x32;
    if ((param_3 & 0xffff) == 0x1a) {
      puStack_138 = (undefined *)0x33;
    }
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = (undefined ***)&pcStack_118;
    pppuStack_130 = (undefined ***)0xa;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4ad6d3;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0x1b:
    pppuStack_12c = (undefined ***)0x1;
    pppuStack_134 = &param_2;
    pppuStack_130 = (undefined ***)0x4;
    puStack_138 = (undefined *)0x34;
    pppuStack_13c = (undefined ***)0x4ad627;
    ExceptionList = &pvStack_c;
    (**(code **)(*param_1 + 0x40))();
    break;
  case 0x1c:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = &param_2;
    pppuStack_130 = (undefined ***)0x4;
    puStack_138 = (undefined *)0x37;
    pppuStack_13c = (undefined ***)param_2;
    uStack_140 = 0x4add5c;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0x1d:
    pppuStack_12c = (undefined ***)(param_5 >> 2);
    pppuStack_130 = (undefined ***)param_4;
    pppuStack_134 = (undefined ***)param_2;
    puStack_138 = (undefined *)0x4add15;
    ExceptionList = &pvStack_c;
    (**(code **)(*param_1 + 0x68))();
    break;
  case 0x1e:
    ppuVar2 = (undefined **)param_1[0xea];
    ppuStack_f4 = ppuVar2;
    ppuVar9 = (undefined **)ppuVar2[1];
    while (ppuVar9 != (undefined **)0x0) {
      if (ppuVar9[4] < param_2) {
        ppuVar9 = (undefined **)ppuVar9[3];
      }
      else {
        ppuStack_f4 = ppuVar9;
        ppuVar9 = (undefined **)ppuVar9[2];
      }
    }
    if ((ppuStack_f4 == ppuVar2) || (param_2 < ppuStack_f4[4])) {
      ppuStack_f8 = ppuVar2;
      pppuVar8 = &ppuStack_f8;
    }
    else {
      pppuVar8 = &ppuStack_f4;
    }
    ppuVar2 = *pppuVar8;
    ExceptionList = &pvStack_c;
    if (ppuVar2 != (undefined **)param_1[0xea]) {
      ExceptionList = &pvStack_c;
      ppuVar2[0x91] = (undefined *)*param_4;
      ppuVar2[0x93] = (undefined *)param_4[1];
      ppuVar2[0x88] = (undefined *)param_4[2];
    }
    if (param_1[0xe8] == 0) {
      pppuStack_130 = (undefined ***)ppuVar2[0x91];
      pppuStack_12c = (undefined ***)0x0;
      pppuStack_134 = (undefined ***)0x4ae66c;
      iVar10 = (**(code **)(*param_1 + 0x114))();
      if (iVar10 == 0) {
        pppuStack_134 = (undefined ***)ppuVar2[0x93];
        puStack_138 = ppuVar2[0x91];
        pppuStack_13c = (undefined ***)0x4ae69b;
        FUN_004b3420();
        pppuStack_13c = (undefined ***)0x4ae6a2;
        FUN_0054d940();
        ppuStack_108 = (undefined **)puVar12[2];
        ppuStack_10c = ppuStack_4;
        pppuStack_134 = (undefined ***)0x1;
        pppuStack_13c = &ppuStack_10c;
        puStack_138 = (undefined *)0x8;
        uStack_140 = 0x48;
        pcStack_144 = (char *)0x4ae6c7;
        (**(code **)(*param_1 + 0x40))();
      }
      else {
        pppuStack_134 = (undefined ***)ppuStack_4;
        puStack_138 = (undefined *)0x4ae683;
        (**(code **)(*param_1 + 0xd8))();
      }
    }
    break;
  case 0x1f:
    if (param_5 != 0) {
      pppuStack_12c = (undefined ***)param_5;
      pppuStack_130 = (undefined ***)param_4;
      pppuStack_134 = (undefined ***)0x4add84;
      ExceptionList = &pvStack_c;
      (**(code **)(*param_1 + 0xc4))();
    }
    break;
  case 0x21:
    ppuStack_f8 = (undefined **)param_1[0xea];
    ppuStack_f4 = ppuStack_f8;
    ppuVar2 = (undefined **)ppuStack_f8[1];
    while (ppuVar2 != (undefined **)0x0) {
      if (ppuVar2[4] < param_2) {
        ppuVar2 = (undefined **)ppuVar2[3];
      }
      else {
        ppuStack_f4 = ppuVar2;
        ppuVar2 = (undefined **)ppuVar2[2];
      }
    }
    if ((ppuStack_f4 == ppuStack_f8) || (param_2 < ppuStack_f4[4])) {
      pppuVar8 = &ppuStack_f8;
    }
    else {
      pppuVar8 = &ppuStack_f4;
    }
    if (*pppuVar8 != (undefined **)param_1[0xea]) {
      (*pppuVar8)[0x95] = (undefined *)*param_4;
    }
    break;
  case 0x22:
    iVar10 = param_1[0x7b];
    uVar6 = *param_4;
    pppuStack_12c = (undefined ***)0x4ada75;
    ExceptionList = &pvStack_c;
    piVar7 = (int *)FUN_00487830();
    pppuStack_12c = &ppuStack_104;
    pppuStack_134 = (undefined ***)0x4ada85;
    pppuStack_130 = (undefined ***)iVar10;
    (**(code **)(*piVar7 + 0x2cc))();
    if (uStack_100 != uVar6) {
      pppuStack_130 = (undefined ***)0x45;
      goto LAB_004adb36;
    }
    break;
  case 0x23:
    pppuStack_12c = &ppuStack_8c;
    pppuStack_130 = &ppuStack_104;
    ppuStack_8c = param_2;
    pppuStack_134 = (undefined ***)0x4addaf;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    pppuStack_12c = (undefined ***)0x0;
    ppuVar2 = (undefined **)*param_4;
    pppuStack_134 = (undefined ***)0x4addce;
    pppuStack_130 = (undefined ***)ppuVar2;
    (**(code **)(ppuStack_104[0x22] + 0x14))();
    pppuStack_12c = (undefined ***)0x1;
    pppuStack_134 = &ppuStack_10c;
    pppuStack_130 = (undefined ***)0x8;
    puStack_138 = (undefined *)0x47;
    pppuStack_13c = (undefined ***)param_2;
    ppuStack_108 = param_2;
    uStack_140 = 0x4addf0;
    ppuStack_10c = ppuVar2;
    FUN_004acb00();
    break;
  case 0x24:
    pppuStack_12c = &ppuStack_84;
    pppuStack_130 = &ppuStack_10c;
    ppuStack_84 = param_2;
    pppuStack_134 = (undefined ***)0x4ad654;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    if (ppuStack_10c != (undefined **)param_1[0xea]) {
      pppuStack_12c = (undefined ***)0x0;
      pppuStack_130 = (undefined ***)0xffffffc4;
      pppuStack_134 = (undefined ***)0x6;
      puStack_138 = (undefined *)0x4ad677;
      (**(code **)(ppuStack_10c[0x22] + 0x2c))();
    }
    break;
  case 0x25:
    pppuStack_12c = &ppuStack_80;
    pppuStack_130 = &ppuStack_10c;
    ppuStack_80 = param_2;
    pppuStack_134 = (undefined ***)0x4ade1d;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    if (ppuStack_10c == (undefined **)param_1[0xea]) {
      ExceptionList = pvStack_c;
      return 0;
    }
    uVar6 = *param_4;
    pppuStack_12c = (undefined ***)0x4ade3d;
    FUN_00492000();
    appuStack_e0[0] = &PTR_FUN_005a9488;
    uStack_a4 = 0;
    uStack_a0 = 0;
    uStack_9c = 0;
    pppuStack_12c = appuStack_e0;
    ppuStack_4 = (undefined **)0x1;
    pppuStack_134 = (undefined ***)0x1;
    puStack_138 = (undefined *)0x4ade74;
    pppuStack_130 = (undefined ***)uVar6;
    FUN_004d6570();
    puStack_138 = (undefined *)0x4ade7b;
    FUN_004d65c0();
    pppuStack_130 = appuStack_e0;
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_134 = (undefined ***)0x4ade90;
    (**(code **)(ppuStack_10c[0x22] + 0x24))();
    ppuStack_4 = (undefined **)0x2;
    pppuStack_12c = (undefined ***)0x4adea7;
    FUN_0049b240();
    ppuStack_4 = (undefined **)0xffffffff;
    pppuStack_12c = (undefined ***)0x4adebb;
    FUN_004920f0();
    break;
  case 0x26:
    ppuStack_ec = param_2;
    uStack_e8 = *param_4;
    uStack_e4 = param_4[1];
    if (0x23 < uStack_e8) {
      if (uStack_e8 < 0x27) {
        ppuVar2 = (undefined **)param_1[0xea];
        ppuStack_f4 = ppuVar2;
        ppuVar9 = (undefined **)ppuVar2[1];
        while (ppuVar9 != (undefined **)0x0) {
          if (ppuVar9[4] < param_2) {
            ppuVar9 = (undefined **)ppuVar9[3];
          }
          else {
            ppuStack_f4 = ppuVar9;
            ppuVar9 = (undefined **)ppuVar9[2];
          }
        }
        if ((ppuStack_f4 == ppuVar2) || (param_2 < ppuStack_f4[4])) {
          ppuStack_f8 = ppuVar2;
          pppuVar8 = &ppuStack_f8;
        }
        else {
          pppuVar8 = &ppuStack_f4;
        }
        ppuVar2 = *pppuVar8;
        ppuVar9 = (undefined **)param_1[0xea];
        if (ppuVar2 == ppuVar9) {
          return 0;
        }
        ppuVar17 = (undefined **)ppuVar9[2];
        ExceptionList = &pvStack_c;
        if (ppuVar17 != ppuVar9) {
          do {
            if (((uint)ppuVar2[0x82] & (uint)ppuVar17[0x82]) != 0) {
              pppuStack_13c = (undefined ***)ppuVar17[4];
              pppuStack_12c = (undefined ***)0x0;
              pppuStack_134 = &ppuStack_ec;
              pppuStack_130 = (undefined ***)0xc;
              puStack_138 = (undefined *)0x49;
              uStack_140 = 0x4ae500;
              FUN_004acae0();
            }
            ppuVar9 = (undefined **)ppuVar17[3];
            if (ppuVar9 == (undefined **)0x0) {
              ppuVar9 = (undefined **)ppuVar17[1];
              if (ppuVar17 == (undefined **)ppuVar9[3]) {
                do {
                  ppuVar17 = ppuVar9;
                  ppuVar9 = (undefined **)ppuVar17[1];
                } while (ppuVar17 == (undefined **)ppuVar9[3]);
              }
              if ((undefined **)ppuVar17[3] != ppuVar9) {
                ppuVar17 = ppuVar9;
              }
            }
            else {
              for (ppuVar3 = (undefined **)ppuVar9[2]; ppuVar17 = ppuVar9,
                  ppuVar3 != (undefined **)0x0; ppuVar3 = (undefined **)ppuVar3[2]) {
                ppuVar9 = ppuVar3;
              }
            }
          } while (ppuVar17 != (undefined **)param_1[0xea]);
        }
      }
      else if (uStack_e8 == 0x27) {
        pppuStack_12c = (undefined ***)0x0;
        pppuStack_134 = &ppuStack_ec;
        pppuStack_130 = (undefined ***)0xc;
        puStack_138 = (undefined *)0x49;
        pppuStack_13c = (undefined ***)0x4ae47a;
        ExceptionList = &pvStack_c;
        (**(code **)(*param_1 + 0x40))();
      }
    }
    break;
  case 0x27:
    pppuStack_12c = (undefined ***)*param_4;
    pppuStack_130 = (undefined ***)param_2;
    pppuStack_134 = (undefined ***)0x4adabb;
    ExceptionList = &pvStack_c;
    (**(code **)(*param_1 + 0x110))();
    break;
  case 0x28:
    pppuStack_12c = (undefined ***)0x0;
    pppuStack_130 = (undefined ***)0x8;
    uStack_100 = *param_4;
    pppuStack_134 = &ppuStack_104;
    puStack_138 = (undefined *)0x4c;
    pppuStack_13c = (undefined ***)param_2;
    ppuStack_104 = param_2;
    uStack_140 = 0x4ae014;
    ExceptionList = &pvStack_c;
    FUN_004acb00();
    break;
  case 0x29:
    pppuStack_12c = &ppuStack_70;
    pppuStack_130 = &ppuStack_10c;
    ppuStack_70 = param_2;
    pppuStack_134 = (undefined ***)0x4ad890;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    if (ppuStack_10c != (undefined **)param_1[0xea]) {
      pppuStack_12c = (undefined ***)0x0;
      uVar6 = *param_4;
      pppuStack_130 = (undefined ***)0x6;
      pppuStack_134 = (undefined ***)0x4ad8ba;
      (**(code **)(ppuStack_10c[0x22] + 0x34))();
      pppuStack_134 = (undefined ***)0x0;
      puStack_138 = (undefined *)-uVar6;
      pppuStack_13c = (undefined ***)0x6;
      uStack_140 = 0x4ad8d4;
      (**(code **)(*(int *)(pcStack_114 + 0x88) + 0x2c))();
    }
    break;
  case 0x2a:
    pppuStack_12c = (undefined ***)*param_4;
    pppuStack_130 = (undefined ***)0x2;
    pppuStack_134 = (undefined ***)param_2;
    puStack_138 = (undefined *)0x4ad8f8;
    ExceptionList = &pvStack_c;
    (**(code **)(*param_1 + 0xfc))();
    break;
  case 0x2b:
    pppuStack_12c = &ppuStack_88;
    pppuStack_130 = &ppuStack_10c;
    ppuStack_88 = param_2;
    pppuStack_134 = (undefined ***)0x4adae8;
    ExceptionList = &pvStack_c;
    FUN_0049d3c0();
    if (ppuStack_10c != (undefined **)param_1[0xea]) {
      ppuStack_10c[0x96] = (undefined *)0x1;
    }
    break;
  case 0x2d:
    if (param_1[0xe8] != 2) {
      pppuStack_12c = (undefined ***)*param_4;
      pppuStack_130 = (undefined ***)param_2;
      pppuStack_134 = (undefined ***)0x4ae750;
      ExceptionList = &pvStack_c;
      uVar11 = (**(code **)(*param_1 + 0x118))();
      ExceptionList = pvStack_c;
      return uVar11;
    }
    break;
  case 0x2e:
    if (param_1[0xe8] != 2) {
      pppuStack_12c = (undefined ***)*param_4;
      pppuStack_130 = (undefined ***)param_2;
      pppuStack_134 = (undefined ***)0x4ae725;
      ExceptionList = &pvStack_c;
      uVar11 = (**(code **)(*param_1 + 0xdc))();
      ExceptionList = pvStack_c;
      return uVar11;
    }
    break;
  case 0x2f:
    if (param_1[0xe8] != 2) {
      pppuStack_12c = (undefined ***)*param_4;
      pppuStack_130 = (undefined ***)param_2;
      pppuStack_134 = (undefined ***)0x4ae6f6;
      ExceptionList = &pvStack_c;
      uVar11 = (**(code **)(*param_1 + 0xe4))();
      ExceptionList = pvStack_c;
      return uVar11;
    }
    break;
  case 0x32:
    ppuStack_f8 = (undefined **)param_1[0xea];
    ppuStack_f4 = ppuStack_f8;
    ppuVar2 = (undefined **)ppuStack_f8[1];
    while (ppuVar2 != (undefined **)0x0) {
      if (ppuVar2[4] < param_2) {
        ppuVar2 = (undefined **)ppuVar2[3];
      }
      else {
        ppuStack_f4 = ppuVar2;
        ppuVar2 = (undefined **)ppuVar2[2];
      }
    }
    if ((ppuStack_f4 == ppuStack_f8) || (param_2 < ppuStack_f4[4])) {
      pppuVar8 = &ppuStack_f8;
    }
    else {
      pppuVar8 = &ppuStack_f4;
    }
    if (*pppuVar8 != (undefined **)param_1[0xea]) {
      (*pppuVar8)[0x92] = (undefined *)*param_4;
    }
  }
  ExceptionList = pvStack_c;
  return 1;
}

