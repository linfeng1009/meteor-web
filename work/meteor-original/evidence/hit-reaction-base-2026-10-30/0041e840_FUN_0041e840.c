/* Original Meteor.exe static export @ 0041e840; original sample not executed. */
/* XREF 0042ad2a UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void * FUN_0041e840(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
                   ,undefined4 param_6)

{
  byte *pbVar1;
  undefined1 *puVar2;
  short *psVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  void *pvVar7;
  undefined4 uVar8;
  undefined2 *puVar9;
  int iVar10;
  void *pvVar11;
  byte bVar12;
  int iVar13;
  ushort *puVar14;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  short *psVar15;
  size_t _Size;
  undefined2 *puVar16;
  int iVar17;
  byte bVar18;
  int local_4a8;
  byte local_4a4;
  int local_4a0;
  byte local_49c;
  byte local_498;
  short *local_494;
  int local_490;
  undefined1 local_489;
  undefined4 local_488;
  byte local_484 [4];
  byte local_480 [4];
  byte local_47c [4];
  uint local_478;
  undefined1 local_474 [4];
  undefined4 local_470;
  undefined4 local_46c;
  undefined1 local_468 [2];
  ushort local_466;
  undefined1 auStack_464 [4];
  undefined1 local_460 [4];
  undefined1 local_45c [4];
  undefined1 local_458 [4];
  int local_454;
  undefined1 local_450 [4];
  undefined1 local_44c [4];
  undefined1 local_448 [4];
  undefined1 local_444 [2];
  undefined1 local_442 [2];
  undefined1 local_440 [4];
  undefined1 local_43c [4];
  undefined4 local_438;
  undefined4 local_434;
  int local_430;
  undefined1 local_42c [20];
  int local_418;
  int local_414;
  undefined1 local_410 [10];
  int local_406;
  int local_400 [256];
  
  iVar6 = FUN_0042b280(param_2,&DAT_005c4530,1);
  if (iVar6 == 0) {
    iVar6 = FUN_0042b280(param_2,&DAT_005c4924,1);
    if (iVar6 == 0) {
      iVar6 = FUN_0042b280(param_2,&DAT_005c48f4,1);
      if (iVar6 == 0) {
        return (void *)0x0;
      }
      FUN_0050a118(local_42c,0x1c,1,param_1);
      pvVar11 = _malloc(local_418 * 8);
      FUN_0050a118(pvVar11,4,local_418 * 2,param_1);
      FUN_0050a118(local_410,0xe,1,param_1);
      _Size = local_406 - 0xe;
      if (local_414 != 0) {
        _Size = local_406 - 0x40e;
      }
      pvVar7 = _malloc(_Size);
      FUN_0050a118(pvVar7,1,_Size,param_1);
      local_494 = _malloc(0x68);
      *(undefined4 *)((int)local_494 + 0x20) = *(undefined4 *)((int)pvVar7 + 4);
      *(undefined4 *)((int)local_494 + 0x24) = *(undefined4 *)((int)pvVar7 + 8);
      if (*(short *)((int)pvVar7 + 0xe) == 8) {
        *(undefined4 *)((int)local_494 + 0x28) = 0x100;
      }
      else {
        *(undefined4 *)((int)local_494 + 0x28) = 0;
      }
      FUN_005089fd(pvVar11);
      FUN_005089fd(pvVar7);
    }
    else {
      FUN_0050a118(local_43c,0x10,1,param_1);
      local_494 = _malloc(0x68);
      *(undefined4 *)((int)local_494 + 0x20) = local_438;
      *(undefined4 *)((int)local_494 + 0x24) = local_434;
      if (local_430 == 0x18) {
        *(undefined4 *)((int)local_494 + 0x28) = 0;
      }
      else {
        *(undefined4 *)((int)local_494 + 0x28) = 0x100;
      }
    }
  }
  else {
    FUN_0050a118(local_44c,2,1,param_1);
    FUN_0050a118(local_448,4,1,param_1);
    FUN_0050a118(local_444,2,1,param_1);
    FUN_0050a118(local_442,2,1,param_1);
    FUN_0050a118(local_440,4,1,param_1);
    FUN_0050a118(local_474,4,1,param_1);
    FUN_0050a118(&local_470,4,1,param_1);
    FUN_0050a118(&local_46c,4,1,param_1);
    FUN_0050a118(local_468,2,1,param_1);
    FUN_0050a118(&local_466,2,1,param_1);
    FUN_0050a118(auStack_464,4,1,param_1);
    FUN_0050a118(local_460,4,1,param_1);
    FUN_0050a118(local_45c,4,1,param_1);
    FUN_0050a118(local_458,4,1,param_1);
    FUN_0050a118(&local_454,4,1,param_1);
    FUN_0050a118(local_450,4,1,param_1);
    local_494 = _malloc(0x68);
    *(undefined4 *)((int)local_494 + 0x20) = local_470;
    *(undefined4 *)((int)local_494 + 0x24) = local_46c;
    if (local_466 < 9) {
      if (local_454 == 0) {
        *(int *)((int)local_494 + 0x28) = 1 << ((byte)local_466 & 0x1f);
      }
      else {
        *(int *)((int)local_494 + 0x28) = local_454;
      }
    }
    else {
      *(undefined4 *)((int)local_494 + 0x28) = 0;
    }
  }
  psVar3 = local_494;
  if (*(int *)((int)local_494 + 0x28) == 0) {
    FUN_005089fd(local_494);
    return (void *)0x0;
  }
  if (param_3 == 0) {
    *(undefined4 *)((int)local_494 + 0x2c) = 0xffffffff;
  }
  else {
    *(undefined4 *)((int)local_494 + 0x2c) = 1;
    *(char *)((int)local_494 + 0x30) = (char)param_4;
    *(char *)((int)local_494 + 0x31) = (char)param_5;
    *(char *)((int)local_494 + 0x32) = (char)param_6;
    local_478 = FUN_0040e550(param_4,param_5,param_6);
  }
  local_4a0 = *(int *)((int)local_494 + 0x20);
  *(undefined4 *)((int)local_494 + 100) = 0;
  if (local_4a0 < 0x100) {
    log2((float10)(int)(0x100 / (longlong)local_4a0));
    log2((float10)_DAT_005a8468);
    iVar6 = __ftol();
    *(int *)((int)local_494 + 0x48) = iVar6 + 8;
  }
  else {
    *(undefined4 *)((int)local_494 + 0x48) = 8;
  }
  if (*(int *)((int)local_494 + 0x24) < 0x100) {
    log2((float10)(int)(0x100 / (longlong)*(int *)((int)local_494 + 0x24)));
    log2((float10)_DAT_005a8468);
    iVar6 = __ftol();
    *(int *)((int)local_494 + 0x4c) = iVar6 + 0x18;
  }
  else {
    *(undefined4 *)((int)local_494 + 0x4c) = 0x18;
  }
  log2((float10)local_4a0);
  log2((float10)_DAT_005a8468);
  uVar8 = __ftol();
  *(undefined4 *)((int)local_494 + 0x50) = uVar8;
  *(undefined4 *)((int)local_494 + 0x5c) = 0;
  *(undefined4 *)((int)local_494 + 0x60) = 0;
  if (DAT_007f18e4 == 1) {
    bVar18 = 0xb;
    local_4a0 = 0;
LAB_0041ec61:
    local_49c = 2;
  }
  else {
    if (DAT_007f18e4 == 2) {
      local_4a0 = 0xb;
      bVar18 = 0;
      goto LAB_0041ec61;
    }
    if (DAT_007f18e4 == 3) {
      bVar18 = 10;
      local_4a0 = 0;
      local_49c = 3;
    }
    else {
      if (DAT_007f18e4 != 4) {
        if (DAT_007f18e4 == 5) {
          bVar18 = 8;
          local_4a4 = 4;
          local_4a0 = 0;
          local_498 = 4;
          local_49c = 4;
          local_488 = 4;
        }
        else {
          bVar18 = (byte)local_478;
        }
        goto LAB_0041ecdd;
      }
      local_4a0 = 10;
      bVar18 = 0;
      local_49c = 3;
    }
  }
  local_4a4 = 5;
  local_498 = 3;
  local_488 = 3;
LAB_0041ecdd:
  puVar9 = _malloc(*(int *)((int)local_494 + 0x28) << 5);
  *(undefined2 **)((int)local_494 + 0x54) = puVar9;
  local_4a8 = 0;
  bVar12 = (byte)local_4a0;
  if (DAT_007f18e4 == 5) {
    if (0 < *(int *)((int)local_494 + 0x28)) {
      do {
        FUN_0050a118(local_484,1,1,param_1);
        FUN_0050a118(local_480,1,1,param_1);
        FUN_0050a118(local_47c,1,1,param_1);
        FUN_0050a118(&local_489,1,1,param_1);
        local_490 = 0;
        iVar6 = param_1;
        do {
          puVar16 = puVar9;
          bVar4 = __ftol();
          bVar5 = __ftol();
          uVar8 = __ftol();
          iVar6 = (CONCAT22((short)((uint)iVar6 >> 0x10),(ushort)(bVar4 >> (local_498 & 0x1f))) <<
                  (bVar18 & 0x1f)) +
                  ((CONCAT31((int3)((uint)extraout_EDX >> 8),bVar5 >> (local_49c & 0x1f)) &
                   0xffff00ff) << (local_4a4 & 0x1f)) +
                  (CONCAT22((short)((uint)uVar8 >> 0x10),
                            (ushort)(byte)((byte)uVar8 >> ((byte)local_488 & 0x1f))) <<
                  (bVar12 & 0x1f));
          *puVar16 = (short)iVar6;
          local_490 = local_490 + 1;
          puVar9 = puVar16 + 1;
        } while (local_490 < 0xf);
        puVar9 = puVar16 + 2;
        puVar16[1] = ((ushort)(local_47c[0] >> (local_498 & 0x1f)) << (bVar18 & 0x1f)) +
                     ((ushort)(local_480[0] >> (local_49c & 0x1f)) << (local_4a4 & 0x1f)) +
                     ((ushort)(local_484[0] >> ((byte)local_488 & 0x1f)) << (bVar12 & 0x1f));
        local_4a8 = local_4a8 + 1;
      } while (local_4a8 < *(int *)((int)local_494 + 0x28));
    }
  }
  else if (0 < *(int *)((int)local_494 + 0x28)) {
    do {
      FUN_0050a118(local_484,1,1,param_1);
      FUN_0050a118(local_480,1,1,param_1);
      FUN_0050a118(local_47c,1,1,param_1);
      FUN_0050a118(&local_489,1,1,param_1);
      local_490 = 0;
      iVar6 = param_1;
      do {
        puVar16 = puVar9;
        bVar4 = __ftol();
        bVar5 = __ftol();
        uVar8 = __ftol();
        iVar6 = (CONCAT22((short)((uint)iVar6 >> 0x10),(ushort)(bVar4 >> (local_498 & 0x1f))) <<
                (bVar18 & 0x1f)) +
                ((CONCAT31((int3)((uint)extraout_EDX_00 >> 8),bVar5 >> (local_49c & 0x1f)) &
                 0xffff00ff) << (local_4a4 & 0x1f)) +
                (CONCAT22((short)((uint)uVar8 >> 0x10),
                          (ushort)(byte)((byte)uVar8 >> ((byte)local_488 & 0x1f))) <<
                (bVar12 & 0x1f));
        *puVar16 = (short)iVar6;
        local_490 = local_490 + 1;
        puVar9 = puVar16 + 1;
      } while (local_490 < 0xf);
      puVar9 = puVar16 + 2;
      puVar16[1] = ((ushort)(local_47c[0] >> (local_498 & 0x1f)) << (bVar18 & 0x1f)) +
                   ((ushort)(local_480[0] >> (local_49c & 0x1f)) << (local_4a4 & 0x1f)) +
                   ((ushort)(local_484[0] >> ((byte)local_488 & 0x1f)) << (bVar12 & 0x1f));
      local_4a8 = local_4a8 + 1;
    } while (local_4a8 < *(int *)((int)local_494 + 0x28));
  }
  iVar6 = *(int *)((int)local_494 + 0x54);
  iVar17 = *(int *)((int)local_494 + 0x28);
  iVar10 = 1;
  local_400[0] = 0;
  local_494 = (short *)(iVar6 + 0x3e);
  if (1 < iVar17) {
    do {
      iVar13 = 0;
      if (0 < iVar10) {
        psVar15 = (short *)(iVar6 + 0x1e);
        do {
          if (*psVar15 == *local_494) break;
          psVar15 = psVar15 + 0x10;
          iVar13 = iVar13 + 1;
        } while (iVar13 < iVar10);
      }
      if (iVar13 == iVar10) {
        local_400[iVar10] = iVar10;
      }
      else {
        local_400[iVar10] = iVar13;
      }
      local_494 = local_494 + 0x10;
      iVar10 = iVar10 + 1;
    } while (iVar10 < iVar17);
  }
  if (param_3 != 0) {
    iVar6 = 0;
    puVar14 = (ushort *)(*(int *)((int)psVar3 + 0x54) + 0x1e);
    if (0 < iVar17) {
      do {
        if (*puVar14 == local_478) {
          *(int *)((int)psVar3 + 0x2c) = iVar6;
          break;
        }
        puVar14 = puVar14 + 0x10;
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar17);
    }
  }
  pvVar11 = _malloc(*(int *)((int)psVar3 + 0x24) * *(int *)((int)psVar3 + 0x20));
  *(void **)((int)psVar3 + 0x58) = pvVar11;
  FUN_0050a118(pvVar11,*(undefined4 *)((int)psVar3 + 0x20),*(undefined4 *)((int)psVar3 + 0x24),
               param_1);
  iVar6 = *(int *)((int)psVar3 + 0x24) * *(int *)((int)psVar3 + 0x20);
  iVar17 = 0;
  if (0 < iVar6) {
    do {
      pbVar1 = (byte *)(*(int *)((int)psVar3 + 0x58) + iVar17);
      puVar2 = (undefined1 *)(*(int *)((int)psVar3 + 0x58) + iVar17);
      iVar17 = iVar17 + 1;
      *puVar2 = (char)local_400[*pbVar1];
    } while (iVar17 < iVar6);
  }
  return psVar3;
}

