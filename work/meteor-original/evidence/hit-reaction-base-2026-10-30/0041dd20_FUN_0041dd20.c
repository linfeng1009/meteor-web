/* Original Meteor.exe static export @ 0041dd20; original sample not executed. */
/* XREF 0042adb5 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void * FUN_0041dd20(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5)

{
  byte *pbVar1;
  undefined1 *puVar2;
  char cVar3;
  short *psVar4;
  byte bVar5;
  byte bVar6;
  int iVar7;
  void *pvVar8;
  undefined4 uVar9;
  undefined2 *puVar10;
  undefined4 uVar11;
  int iVar12;
  void *pvVar13;
  undefined1 uVar14;
  byte bVar15;
  int iVar17;
  uint uVar18;
  int iVar19;
  ushort *puVar20;
  undefined4 extraout_EDX;
  size_t _Size;
  short *psVar21;
  undefined2 *puVar22;
  int iVar23;
  undefined4 *puVar24;
  char *pcVar25;
  int local_694;
  short *local_690;
  byte local_68c;
  int local_688;
  byte local_684;
  byte local_680;
  int local_67c;
  undefined1 local_675;
  undefined4 local_674;
  byte local_670 [4];
  int local_66c;
  byte local_668 [4];
  byte local_664 [4];
  undefined4 local_660;
  uint local_65c;
  uint local_658;
  char local_654 [16];
  undefined4 local_644;
  undefined4 local_640;
  undefined4 local_63c;
  undefined4 local_638;
  undefined1 local_634 [4];
  undefined4 local_630;
  undefined4 local_62c;
  undefined1 local_628 [2];
  ushort local_626;
  undefined1 auStack_624 [4];
  undefined1 local_620 [4];
  undefined1 local_61c [4];
  undefined1 local_618 [4];
  int local_614;
  undefined1 local_610 [4];
  undefined1 local_60c [4];
  undefined1 local_608 [4];
  undefined1 local_604 [2];
  undefined1 local_602 [2];
  undefined1 local_600 [4];
  undefined1 local_5fc [4];
  undefined4 local_5f8;
  undefined4 local_5f4;
  int local_5f0;
  undefined4 local_5ec;
  undefined4 local_5e8;
  undefined2 local_5e4;
  undefined1 local_5ac [20];
  int local_598;
  int local_594;
  undefined1 local_590 [10];
  int local_586;
  char local_580;
  char local_57f;
  undefined1 local_57e;
  char acStack_503 [3];
  undefined4 local_500 [32];
  undefined4 local_480 [32];
  int local_400 [256];
  byte bVar16;
  
  local_644 = 0;
  local_640 = 0;
  local_63c = 0;
  puVar24 = local_480;
  for (iVar17 = 0x20; iVar17 != 0; iVar17 = iVar17 + -1) {
    *puVar24 = 0;
    puVar24 = puVar24 + 1;
  }
  puVar24 = local_500;
  for (iVar17 = 0x20; iVar17 != 0; iVar17 = iVar17 + -1) {
    *puVar24 = 0;
    puVar24 = puVar24 + 1;
  }
  local_654[0] = '\0';
  local_654[1] = '\0';
  local_654[2] = '\0';
  local_654[3] = '\0';
  local_638 = 0;
  local_654[4] = '\0';
  local_654[5] = '\0';
  local_654[6] = '\0';
  local_654[7] = '\0';
  local_654[8] = '\0';
  local_654[9] = '\0';
  local_654[10] = '\0';
  local_654[0xb] = '\0';
  local_654[0xc] = '\0';
  local_654[0xd] = '\0';
  local_654[0xe] = '\0';
  local_654[0xf] = '\0';
  pcVar25 = &local_580;
  for (iVar17 = 0x20; iVar17 != 0; iVar17 = iVar17 + -1) {
    pcVar25[0] = '\0';
    pcVar25[1] = '\0';
    pcVar25[2] = '\0';
    pcVar25[3] = '\0';
    pcVar25 = pcVar25 + 4;
  }
  local_660 = 0;
  local_658 = 0;
  FUN_0042b080(param_1,&local_644,local_480,local_500,local_654);
  iVar17 = FUN_0042b280(local_654,&DAT_005c4914,1);
  if (iVar17 == 0) {
    local_660 = 0;
    iVar17 = FUN_00509f8f(param_1,&DAT_005c4580);
    local_66c = iVar17;
  }
  else {
    uVar18 = 0xffffffff;
    pcVar25 = (char *)local_500;
    do {
      if (uVar18 == 0) break;
      uVar18 = uVar18 - 1;
      cVar3 = *pcVar25;
      pcVar25 = pcVar25 + 1;
    } while (cVar3 != '\0');
    uVar18 = ~uVar18;
    if ((int)(uVar18 - 1) < 2) {
      return (void *)0x0;
    }
    local_57f = acStack_503[uVar18 + 1];
    local_57e = 0;
    local_580 = acStack_503[uVar18];
    iVar7 = FUN_0050915b(&local_580);
    acStack_503[uVar18] = '\0';
    FUN_0042b190(&local_580,&local_644,local_480,local_500,local_654);
    iVar17 = FUN_00509f8f(&local_580,&DAT_005c4580);
    local_66c = iVar17;
    FUN_0050a2d3(iVar17,4,0);
    FUN_0050a118(&local_658,4,1,iVar17);
    if (local_658 < iVar7 + 1U) {
      if (iVar17 == 0) {
        return (void *)0x0;
      }
      FUN_00509e57(iVar17);
      return (void *)0x0;
    }
    FUN_0050a2d3(iVar17,iVar7 * 4 + 8,0);
    FUN_0050a118(&local_660,4,1,iVar17);
  }
  iVar7 = FUN_0042b280(local_654,&DAT_005c4914,1);
  if (iVar7 == 0) {
    iVar7 = 0;
    do {
      pcVar25 = local_654 + iVar7;
      *(char *)((int)&local_5ec + iVar7) = *pcVar25;
      iVar7 = iVar7 + 1;
    } while (*pcVar25 != '\0');
  }
  else {
    local_5ec = 0;
    local_5e8 = 0;
    local_5e4 = 0;
    FUN_0050a2d3(iVar17,local_660,0);
    FUN_0050a118(&local_5ec,1,4,iVar17);
    if ((((char)local_5ec != 'B') ||
        (uVar9 = DAT_005c490c, uVar14 = DAT_005c4910, local_5ec._1_1_ != 'M')) &&
       (iVar7 = FUN_0042b280(&DAT_005c4908,&local_5ec,1), uVar9 = DAT_005c4900,
       uVar14 = DAT_005c4904, iVar7 == 0)) {
      return (void *)0x0;
    }
    local_5e8 = CONCAT31(local_5e8._1_3_,uVar14);
    local_5ec = uVar9;
    FUN_0050a2d3(iVar17,local_660,0);
  }
  iVar7 = FUN_0042b280(&local_5ec,&DAT_005c4530,1);
  if (iVar7 == 0) {
    iVar7 = FUN_0042b280(&local_5ec,&DAT_005c4924,1);
    if (iVar7 == 0) {
      iVar7 = FUN_0042b280(&local_5ec,&DAT_005c48f4,1);
      if (iVar7 == 0) {
        return (void *)0x0;
      }
      FUN_0050a118(local_5ac,0x1c,1,iVar17);
      pvVar13 = _malloc(local_598 * 8);
      FUN_0050a118(pvVar13,4,local_598 * 2,iVar17);
      FUN_0050a118(local_590,0xe,1,iVar17);
      _Size = local_586 - 0xe;
      if (local_594 != 0) {
        _Size = local_586 - 0x40e;
      }
      pvVar8 = _malloc(_Size);
      FUN_0050a118(pvVar8,1,_Size,iVar17);
      local_690 = _malloc(0x68);
      *(undefined4 *)((int)local_690 + 0x20) = *(undefined4 *)((int)pvVar8 + 4);
      *(undefined4 *)((int)local_690 + 0x24) = *(undefined4 *)((int)pvVar8 + 8);
      if (*(short *)((int)pvVar8 + 0xe) == 8) {
        *(undefined4 *)((int)local_690 + 0x28) = 0x100;
      }
      else {
        *(undefined4 *)((int)local_690 + 0x28) = 0;
      }
      FUN_005089fd(pvVar13);
      FUN_005089fd(pvVar8);
    }
    else {
      FUN_0050a118(local_5fc,0x10,1,iVar17);
      local_690 = _malloc(0x68);
      *(undefined4 *)((int)local_690 + 0x20) = local_5f8;
      *(undefined4 *)((int)local_690 + 0x24) = local_5f4;
      if (local_5f0 == 0x18) {
        *(undefined4 *)((int)local_690 + 0x28) = 0;
      }
      else {
        *(undefined4 *)((int)local_690 + 0x28) = 0x100;
      }
    }
  }
  else {
    FUN_0050a118(local_60c,2,1,iVar17);
    FUN_0050a118(local_608,4,1,iVar17);
    FUN_0050a118(local_604,2,1,iVar17);
    FUN_0050a118(local_602,2,1,iVar17);
    FUN_0050a118(local_600,4,1,iVar17);
    FUN_0050a118(local_634,4,1,iVar17);
    FUN_0050a118(&local_630,4,1,iVar17);
    FUN_0050a118(&local_62c,4,1,iVar17);
    FUN_0050a118(local_628,2,1,iVar17);
    FUN_0050a118(&local_626,2,1,iVar17);
    FUN_0050a118(auStack_624,4,1,iVar17);
    FUN_0050a118(local_620,4,1,iVar17);
    FUN_0050a118(local_61c,4,1,iVar17);
    FUN_0050a118(local_618,4,1,iVar17);
    FUN_0050a118(&local_614,4,1,iVar17);
    FUN_0050a118(local_610,4,1,iVar17);
    local_690 = _malloc(0x68);
    *(undefined4 *)((int)local_690 + 0x20) = local_630;
    *(undefined4 *)((int)local_690 + 0x24) = local_62c;
    if (local_626 < 9) {
      if (local_614 == 0) {
        *(int *)((int)local_690 + 0x28) = 1 << ((byte)local_626 & 0x1f);
      }
      else {
        *(int *)((int)local_690 + 0x28) = local_614;
      }
    }
    else {
      *(undefined4 *)((int)local_690 + 0x28) = 0;
    }
  }
  psVar4 = local_690;
  if (*(int *)((int)local_690 + 0x28) == 0) {
    FUN_005089fd(local_690);
    FUN_00509e57(iVar17);
    return (void *)0x0;
  }
  if (param_2 == 0) {
    *(undefined4 *)((int)local_690 + 0x2c) = 0xffffffff;
  }
  else {
    *(undefined4 *)((int)local_690 + 0x2c) = 1;
    *(char *)((int)local_690 + 0x30) = (char)param_3;
    *(char *)((int)local_690 + 0x31) = (char)param_4;
    *(char *)((int)local_690 + 0x32) = (char)param_5;
    local_65c = FUN_0040e550(param_3,param_4,param_5);
  }
  local_688 = *(int *)((int)local_690 + 0x20);
  *(undefined4 *)((int)local_690 + 100) = 0;
  if (local_688 < 0x100) {
    log2((float10)(int)(0x100 / (longlong)local_688));
    log2((float10)_DAT_005a8468);
    iVar7 = __ftol();
    *(int *)((int)local_690 + 0x48) = iVar7 + 8;
  }
  else {
    *(undefined4 *)((int)local_690 + 0x48) = 8;
  }
  if (*(int *)((int)local_690 + 0x24) < 0x100) {
    log2((float10)(int)(0x100 / (longlong)*(int *)((int)local_690 + 0x24)));
    log2((float10)_DAT_005a8468);
    iVar7 = __ftol();
    *(int *)((int)local_690 + 0x4c) = iVar7 + 0x18;
  }
  else {
    *(undefined4 *)((int)local_690 + 0x4c) = 0x18;
  }
  log2((float10)local_688);
  log2((float10)_DAT_005a8468);
  uVar9 = __ftol();
  *(undefined4 *)((int)local_690 + 0x50) = uVar9;
  *(undefined4 *)((int)local_690 + 0x5c) = 0;
  *(undefined4 *)((int)local_690 + 0x60) = 0;
  if (DAT_007f18e4 == 1) {
    uVar18 = 0xb;
    local_688 = 0;
LAB_0041e3da:
    local_68c = 2;
  }
  else {
    if (DAT_007f18e4 == 2) {
      local_688 = 0xb;
      uVar18 = 0;
      goto LAB_0041e3da;
    }
    if (DAT_007f18e4 == 3) {
      uVar18 = 10;
      local_688 = 0;
      local_68c = 3;
    }
    else {
      if (DAT_007f18e4 != 4) {
        uVar18 = local_65c;
        if (DAT_007f18e4 == 5) {
          local_680 = 4;
          local_688 = 0;
          local_684 = 4;
          local_68c = 4;
          local_674 = 4;
          uVar18 = 8;
        }
        goto LAB_0041e456;
      }
      local_688 = 10;
      uVar18 = 0;
      local_68c = 3;
    }
  }
  local_680 = 5;
  local_684 = 3;
  local_674 = 3;
LAB_0041e456:
  puVar10 = _malloc(*(int *)((int)local_690 + 0x28) << 5);
  *(undefined2 **)((int)local_690 + 0x54) = puVar10;
  local_694 = 0;
  bVar15 = (byte)uVar18;
  bVar16 = (byte)local_688;
  if (DAT_007f18e4 == 5) {
    if (0 < *(int *)((int)local_690 + 0x28)) {
      do {
        FUN_0050a118(local_670,1,1,iVar17);
        FUN_0050a118(local_668,1,1,iVar17);
        FUN_0050a118(local_664,1,1,iVar17);
        FUN_0050a118(&local_675,1,1,iVar17);
        local_67c = 0;
        psVar21 = local_690;
        do {
          puVar22 = puVar10;
          bVar5 = __ftol();
          uVar9 = __ftol();
          uVar11 = __ftol();
          psVar21 = (short *)((CONCAT22((short)((uint)psVar21 >> 0x10),
                                        (ushort)(bVar5 >> (local_684 & 0x1f))) << (bVar15 & 0x1f)) +
                              (CONCAT22((short)((uint)uVar9 >> 0x10),
                                        (ushort)(byte)((byte)uVar9 >> (local_68c & 0x1f))) <<
                              (local_680 & 0x1f)) +
                             (CONCAT22((short)((uint)uVar11 >> 0x10),
                                       (ushort)(byte)((byte)uVar11 >> ((byte)local_674 & 0x1f))) <<
                             (bVar16 & 0x1f)));
          *puVar22 = (short)psVar21;
          local_67c = local_67c + 1;
          puVar10 = puVar22 + 1;
        } while (local_67c < 0xf);
        puVar10 = puVar22 + 2;
        puVar22[1] = ((ushort)(local_664[0] >> (local_684 & 0x1f)) << (bVar15 & 0x1f)) +
                     ((ushort)(local_668[0] >> (local_68c & 0x1f)) << (local_680 & 0x1f)) +
                     ((ushort)(local_670[0] >> ((byte)local_674 & 0x1f)) << (bVar16 & 0x1f));
        local_694 = local_694 + 1;
        iVar17 = local_66c;
      } while (local_694 < *(int *)((int)local_690 + 0x28));
    }
  }
  else if (0 < *(int *)((int)local_690 + 0x28)) {
    do {
      FUN_0050a118(local_670,1,1,iVar17);
      FUN_0050a118(local_668,1,1,iVar17);
      FUN_0050a118(local_664,1,1,iVar17);
      FUN_0050a118(&local_675,1,1,iVar17);
      local_67c = 0;
      psVar21 = local_690;
      do {
        puVar22 = puVar10;
        bVar5 = __ftol();
        bVar6 = __ftol();
        uVar9 = __ftol();
        psVar21 = (short *)((CONCAT22((short)((uint)psVar21 >> 0x10),
                                      (ushort)(bVar5 >> (local_684 & 0x1f))) << (bVar15 & 0x1f)) +
                            ((CONCAT31((int3)((uint)extraout_EDX >> 8),bVar6 >> (local_68c & 0x1f))
                             & 0xffff00ff) << (local_680 & 0x1f)) +
                           (CONCAT22((short)((uint)uVar9 >> 0x10),
                                     (ushort)(byte)((byte)uVar9 >> ((byte)local_674 & 0x1f))) <<
                           (bVar16 & 0x1f)));
        *puVar22 = (short)psVar21;
        local_67c = local_67c + 1;
        puVar10 = puVar22 + 1;
      } while (local_67c < 0xf);
      puVar10 = puVar22 + 2;
      puVar22[1] = ((ushort)(local_664[0] >> (local_684 & 0x1f)) << (bVar15 & 0x1f)) +
                   ((ushort)(local_668[0] >> (local_68c & 0x1f)) << (local_680 & 0x1f)) +
                   ((ushort)(local_670[0] >> ((byte)local_674 & 0x1f)) << (bVar16 & 0x1f));
      local_694 = local_694 + 1;
      iVar17 = local_66c;
    } while (local_694 < *(int *)((int)local_690 + 0x28));
  }
  iVar7 = *(int *)((int)local_690 + 0x54);
  iVar23 = *(int *)((int)local_690 + 0x28);
  iVar12 = 1;
  local_400[0] = 0;
  local_690 = (short *)(iVar7 + 0x3e);
  if (1 < iVar23) {
    do {
      iVar19 = 0;
      if (0 < iVar12) {
        psVar21 = (short *)(iVar7 + 0x1e);
        do {
          if (*psVar21 == *local_690) break;
          psVar21 = psVar21 + 0x10;
          iVar19 = iVar19 + 1;
        } while (iVar19 < iVar12);
      }
      if (iVar19 == iVar12) {
        local_400[iVar12] = iVar12;
      }
      else {
        local_400[iVar12] = iVar19;
      }
      local_690 = local_690 + 0x10;
      iVar12 = iVar12 + 1;
    } while (iVar12 < iVar23);
  }
  if (param_2 != 0) {
    iVar7 = 0;
    puVar20 = (ushort *)(*(int *)((int)psVar4 + 0x54) + 0x1e);
    if (0 < iVar23) {
      do {
        if (*puVar20 == local_65c) {
          *(int *)((int)psVar4 + 0x2c) = iVar7;
          break;
        }
        puVar20 = puVar20 + 0x10;
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar23);
    }
  }
  pvVar13 = _malloc(*(int *)((int)psVar4 + 0x24) * *(int *)((int)psVar4 + 0x20));
  *(void **)((int)psVar4 + 0x58) = pvVar13;
  FUN_0050a118(pvVar13,*(undefined4 *)((int)psVar4 + 0x20),*(undefined4 *)((int)psVar4 + 0x24),
               iVar17);
  iVar7 = *(int *)((int)psVar4 + 0x24) * *(int *)((int)psVar4 + 0x20);
  iVar23 = 0;
  if (0 < iVar7) {
    do {
      pbVar1 = (byte *)(*(int *)((int)psVar4 + 0x58) + iVar23);
      puVar2 = (undefined1 *)(*(int *)((int)psVar4 + 0x58) + iVar23);
      iVar23 = iVar23 + 1;
      *puVar2 = (char)local_400[*pbVar1];
    } while (iVar23 < iVar7);
  }
  FUN_00509e57(iVar17);
  return psVar4;
}

