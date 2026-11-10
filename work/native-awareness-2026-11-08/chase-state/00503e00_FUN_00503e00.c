/* Original Meteor.exe static export @ 00503e00; original sample not executed. */
/* XREF 004fd7c1 DATA */
/* XREF 00503bf3 DATA */
/* XREF 005046b2 DATA */
/* XREF 004fdf13 DATA */
/* XREF 004fb99d DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

DWORD __fastcall FUN_00503e00(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  float fVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  DWORD DVar7;
  int iVar8;
  uint uVar9;
  DWORD DVar10;
  bool bVar11;
  float10 fVar12;
  float fStack_20;
  
  *(undefined4 *)(param_1 + 0x80) = 0x3e4ccccd;
  if ((*(int *)(param_1 + 0x74) != 0) && (iVar6 = _rand(), iVar6 % 0x1e != 0)) {
    if ((*(int *)(param_1 + 0xc4) == -1) &&
       ((fVar12 = (float10)FUN_0047ed20(), (float10)_DAT_005a94fc < fVar12 &&
        (cVar4 = FUN_004fc980(*(undefined4 *)(param_1 + 0x74)), cVar4 == '\0')))) {
      FUN_004fd870();
      DVar7 = FUN_004fd630(&LAB_005049d0);
      return DVar7;
    }
    if ((*(int *)(param_1 + 0x78) == 0) ||
       ((fVar12 = (float10)FUN_0047ed20(), fVar12 <= (float10)_DAT_005abb10 &&
        (ABS(*(float *)(param_1 + 0x20) - *(float *)(*(int *)(param_1 + 0x78) + 0x20)) <=
         (float)_DAT_005abb28)))) {
      cVar4 = FUN_004fcbd0();
      if (cVar4 != '\0') {
        _rand();
      }
      iVar8 = _rand();
      iVar6 = *(short *)(*(int *)(param_1 + 0x10) + 8) * 3;
      if ((iVar8 % 100 < (int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2) &&
         (cVar4 = FUN_004fcde0(0x66), cVar4 != '\0')) {
        iVar6 = _rand();
        *(float *)(param_1 + 0x80) =
             (float)(iVar6 % 10) * (float)_DAT_005abb20 + (float)_DAT_005abb18;
        return iVar6 / 10;
      }
      cVar4 = FUN_00501070();
      if (cVar4 != '\0') {
        uVar9 = _rand();
        uVar9 = uVar9 & 0x80000003;
        bVar11 = uVar9 == 0;
        if ((int)uVar9 < 0) {
          bVar11 = (uVar9 - 1 | 0xfffffffc) == 0xffffffff;
        }
        if (bVar11) {
          *(undefined4 *)(param_1 + 0xbc) = 0;
        }
      }
      DVar7 = FUN_004fdf90(0x43480000);
      if ((char)DVar7 != '\0') {
        return DVar7;
      }
      cVar4 = FUN_004fc9f0(*(undefined4 *)(param_1 + 0x74));
      if (cVar4 == '\0') {
        iVar6 = *(int *)(param_1 + 0x5c);
        if (-1 < iVar6) {
          uVar2 = *(undefined4 *)(param_1 + 0x58);
          *(int *)(param_1 + 0x58) = iVar6;
          *(undefined4 *)(param_1 + 0x5c) = uVar2;
          DVar7 = timeGetTime();
          if (((20000 < DVar7 - *(int *)(param_1 + 0x120)) &&
              (cVar4 = FUN_004fc9f0(*(undefined4 *)(param_1 + 0x74)), cVar4 != '\0')) &&
             (cVar4 = FUN_00501030(), cVar4 != '\0')) {
            DVar10 = FUN_00501240();
            *(undefined4 *)(param_1 + 0x80) = 0x3f19999a;
            *(DWORD *)(param_1 + 0x120) = DVar7;
            return DVar10;
          }
          *(undefined4 *)(param_1 + 0x58) = uVar2;
          *(int *)(param_1 + 0x5c) = iVar6;
        }
        FUN_00500c60(0);
        FUN_00500fa0();
        if (*(int *)(param_1 + 0xc4) != -1) {
          iVar6 = _rand();
          if (iVar6 % 0x1e != 0) {
            return iVar6 / 0x1e;
          }
        }
        fVar12 = (float10)FUN_0047ecf0();
        if (fVar12 <= (float10)_DAT_005aa638) {
          uVar9 = _rand();
          uVar9 = uVar9 & 0x80000001;
          bVar11 = uVar9 == 0;
          if ((int)uVar9 < 0) {
            bVar11 = (uVar9 - 1 | 0xfffffffe) == 0xffffffff;
          }
          if (!bVar11) {
            DVar7 = FUN_004fd530(*(undefined4 *)(param_1 + 0x74));
            return DVar7;
          }
        }
        FUN_004fd580();
        DVar7 = FUN_00501030();
        if ((char)DVar7 == '\0') {
          return DVar7;
        }
        DVar7 = FUN_004fbcc0(*(undefined4 *)(param_1 + 0x74));
        if ((char)DVar7 != '\0') {
          return DVar7;
        }
        uVar9 = _rand();
        uVar9 = uVar9 & 0x80000003;
        bVar11 = uVar9 == 0;
        if ((int)uVar9 < 0) {
          bVar11 = (uVar9 - 1 | 0xfffffffc) == 0xffffffff;
        }
        if (!bVar11) {
          iVar6 = _rand();
          if (iVar6 % 100 < (int)*(short *)(*(int *)(param_1 + 0x10) + 10)) {
            iVar6 = _rand();
            *(float *)(param_1 + 0xe0) = (float)(iVar6 % 0x168);
          }
          DVar7 = FUN_004fd870();
          *(undefined4 *)(param_1 + 0x80) = 0x3ecccccd;
          return DVar7;
        }
        FUN_004fd530(*(undefined4 *)(param_1 + 0x74));
        DVar7 = FUN_004fced0(0x40a00000);
        if ((char)DVar7 != '\0') {
          DVar7 = FUN_005012d0();
        }
        *(undefined4 *)(param_1 + 0x80) = 0x3f4ccccd;
        return DVar7;
      }
      cVar4 = FUN_004fcb40(*(undefined4 *)(param_1 + 0x74));
      if (cVar4 == '\0') {
        cVar4 = FUN_004fcf70();
        if (((cVar4 != '\0') && (0 < *(int *)(param_1 + 0x5c))) &&
           (iVar6 = _rand(), iVar6 % 0x14 == 0)) {
LAB_0050430f:
          FUN_00501240();
          *(undefined4 *)(param_1 + 0x80) = 0x3f19999a;
          DVar7 = timeGetTime();
          *(DWORD *)(param_1 + 0x120) = DVar7;
          return DVar7;
        }
      }
      else {
        if ((*(int *)(param_1 + 0x78) == 0) &&
           (iVar6 = _rand(), iVar6 % 100 < (int)*(short *)(*(int *)(param_1 + 0x10) + 6))) {
          DVar7 = FUN_004fd630(&LAB_00504560);
          return DVar7;
        }
        iVar6 = *(int *)(param_1 + 0x5c);
        if (-1 < iVar6) {
          uVar2 = *(undefined4 *)(param_1 + 0x58);
          *(int *)(param_1 + 0x58) = iVar6;
          *(undefined4 *)(param_1 + 0x5c) = uVar2;
          cVar4 = FUN_004fcb40(*(undefined4 *)(param_1 + 0x74));
          if (((cVar4 == '\0') &&
              (cVar4 = FUN_004fc9f0(*(undefined4 *)(param_1 + 0x74)), cVar4 != '\0')) &&
             (cVar4 = FUN_00501030(), cVar4 != '\0')) goto LAB_0050430f;
          *(undefined4 *)(param_1 + 0x58) = uVar2;
          *(int *)(param_1 + 0x5c) = iVar6;
        }
      }
      iVar6 = _rand();
      iVar8 = (int)*(short *)(*(int *)(param_1 + 0x10) + 8);
      if ((iVar6 % 100 < (int)(iVar8 + (iVar8 >> 0x1f & 3U)) >> 2) &&
         (DVar7 = FUN_004fcde0(0x62), (char)DVar7 != '\0')) {
        return DVar7;
      }
      iVar6 = _rand();
      if (iVar6 % 100 < (int)*(short *)(*(int *)(param_1 + 0x10) + 0xc)) {
        iVar6 = _rand();
        cVar4 = "fbbllrr"[iVar6 % 7];
        cVar5 = FUN_004fcc10(cVar4,0x428c0000);
        if (cVar5 != '\0') {
          DVar7 = FUN_00500ff0(cVar4);
          *(undefined4 *)(param_1 + 0x80) = 0x3f000000;
          return DVar7;
        }
      }
      if (*(int *)(param_1 + 0x84) % 3 == 0) {
        iVar6 = _rand();
        if (iVar6 % 10 == 0) {
          cVar4 = FUN_004fcc10(0x72,0x42480000);
          if (cVar4 != '\0') {
            *(undefined4 *)(param_1 + 0xc0) = 1;
            goto LAB_005043a1;
          }
        }
        else if ((iVar6 % 10 == 1) && (cVar4 = FUN_004fcc10(0x6c,0x42480000), cVar4 != '\0')) {
          *(undefined4 *)(param_1 + 0xc0) = 0xffffffff;
          goto LAB_005043a1;
        }
        *(undefined4 *)(param_1 + 0xc0) = 0;
      }
LAB_005043a1:
      *(undefined4 *)(param_1 + 0xbc) = 0;
      *(undefined4 *)(param_1 + 0xc4) = 0xffffffff;
      cVar4 = FUN_004fcf70();
      if (cVar4 == '\0') {
        FUN_00500f70(*(undefined4 *)(param_1 + 0x74));
      }
      FUN_004fd530(*(undefined4 *)(param_1 + 0x74));
      iVar6 = _rand();
      if (iVar6 % 100 < (int)*(short *)(*(int *)(param_1 + 0x10) + 4)) {
        iVar6 = _rand();
        if (iVar6 % 5 != 0) {
          DVar7 = FUN_00500c60(1);
          *(undefined4 *)(param_1 + 0x80) = 0x3ecccccd;
          return DVar7;
        }
        DVar7 = FUN_005012a0(1);
        *(undefined4 *)(param_1 + 0x80) = 0x3ecccccd;
        return DVar7;
      }
      FUN_00500c60(0);
      FUN_005012a0(0);
      iVar8 = *(int *)(param_1 + 0x10);
      if ((int)*(short *)(iVar8 + 0x16) + (int)*(short *)(iVar8 + 0x14) +
          (int)*(short *)(iVar8 + 0x12) + (int)*(short *)(iVar8 + 4) <= iVar6 % 100) {
        return (int)*(short *)(iVar8 + 4);
      }
      DVar7 = FUN_004fcb00(*(undefined4 *)(param_1 + 0x74));
      if ((char)DVar7 == '\0') {
        return DVar7;
      }
      fStack_20 = 0.0;
      sVar1 = *(short *)(*(int *)(param_1 + 0x10) + 0xe);
      fVar3 = _DAT_005a83e4;
      if (sVar1 < 100) {
        iVar8 = 100 - sVar1;
        iVar6 = _rand();
        fStack_20 = (float)(iVar8 / 2 - iVar6 % iVar8) * _DAT_005a83ec;
        iVar6 = _rand();
        fVar3 = (float)(iVar8 / 2 - iVar6 % iVar8) * _DAT_005ab868;
      }
      FUN_005011c0(fStack_20 + *(float *)(param_1 + 0x3c),fVar3 + *(float *)(param_1 + 0x40));
      iVar6 = _rand();
      iVar8 = (int)*(short *)(*(int *)(param_1 + 0x10) + 0x12);
      if (iVar8 <= iVar6 % 100) {
        DVar7 = FUN_00500c90(*(undefined4 *)(param_1 + 0x58),
                             (*(short *)(*(int *)(param_1 + 0x10) + 0x14) + iVar8 <= iVar6 % 100) +
                             '\x01');
        return DVar7;
      }
      DVar7 = FUN_00500c90(*(undefined4 *)(param_1 + 0x58),0);
      return DVar7;
    }
  }
  DVar7 = FUN_004fd870();
  return DVar7;
}

