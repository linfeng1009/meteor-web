/* Original Meteor.exe static read-only export; sample not executed. */

void __fastcall FUN_004c0020(int param_1)

{
  float *pfVar1;
  float *pfVar2;
  int *piVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int *piVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  undefined1 auStack_10 [4];
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar5 = FUN_00487830();
  iVar15 = 0;
  *(undefined4 *)(param_1 + 0x58c) = 0;
  iVar12 = *(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518);
  uVar14 = 0;
  iVar7 = iVar12 >> 0x1f;
  if (iVar12 / 0x124 + iVar7 != iVar7) {
    do {
      uVar14 = uVar14 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x518) + 4 + iVar15) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0x518) + 8 + iVar15) = 0xffffffff;
      *(undefined4 *)(*(int *)(param_1 + 0x518) + 0xc + iVar15) = 0;
      iVar15 = iVar15 + 0x124;
    } while (uVar14 < (uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124));
  }
  iVar7 = *(int *)(*(int *)(iVar5 + 0x2188) + 8);
  iVar12 = *(int *)(iVar5 + 0x2188);
  while (iVar7 != iVar12) {
    uVar14 = *(uint *)(iVar7 + 0x10);
    if ((((-1 < (int)uVar14) &&
         (uVar14 < (uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124))) &&
        (iVar12 = *(int *)(iVar7 + 0x14), iVar12 != 0)) && (iVar12 != 0x65c)) {
      iVar15 = *(int *)(param_1 + 0x518) + uVar14 * 0x124;
      *(uint *)(iVar15 + 8) = uVar14;
      *(undefined4 *)(iVar15 + 0xc) = 0;
      *(undefined4 *)(iVar15 + 0x10) = 0;
      *(undefined4 *)(iVar15 + 0x44) = *(undefined4 *)(iVar12 + 500);
      uVar6 = (**(code **)(*(int *)(iVar5 + 0x2488) + 0x4c))();
      if (uVar14 == uVar6) {
        *(undefined4 *)(iVar15 + 4) = 1;
        *(int *)(param_1 + 0x58c) = iVar15;
        if (*(char *)(param_1 + 0x594) != '\0') {
          FUN_004c0580(uVar14,*(undefined4 *)(param_1 + 0x588));
          *(undefined1 *)(param_1 + 0x594) = 0;
        }
      }
      else {
        *(undefined4 *)(iVar15 + 4) = 2;
      }
      FUN_00477d30(3,iVar15 + 0x18);
      pfVar1 = (float *)(iVar15 + 0x24);
      FUN_00477d30(1,pfVar1);
      pfVar2 = (float *)(iVar15 + 0x30);
      FUN_00477d30(0,pfVar2);
      *pfVar1 = -*pfVar1;
      *(float *)(iVar15 + 0x28) = -*(float *)(iVar15 + 0x28);
      *(float *)(iVar15 + 0x2c) = -*(float *)(iVar15 + 0x2c);
      *pfVar2 = -*pfVar2;
      *(float *)(iVar15 + 0x34) = -*(float *)(iVar15 + 0x34);
      *(float *)(iVar15 + 0x38) = -*(float *)(iVar15 + 0x38);
      uStack_c = 0;
      uStack_8 = 0;
      uStack_4 = 0;
      FUN_00501670(&uStack_c,pfVar1,iVar15 + 0x3c,auStack_10);
    }
    FUN_0043c6c0();
    iVar12 = *(int *)(iVar5 + 0x2188);
  }
  if ((*(int **)(iVar5 + 0x212c) != (int *)0x0) &&
     (iVar7 = (**(code **)(**(int **)(iVar5 + 0x212c) + 0x3c))(), iVar7 != 0)) {
    iVar12 = *(int *)(*(int *)(iVar7 + 4) + 8);
    iVar15 = *(int *)(iVar7 + 4);
    while (iVar12 != iVar15) {
      uVar14 = *(uint *)(iVar12 + 0x10);
      if ((-1 < (int)uVar14) &&
         (uVar14 < (uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124))) {
        iVar15 = *(int *)(param_1 + 0x518) + uVar14 * 0x124;
        uVar8 = (**(code **)(*(int *)(iVar12 + 0x88) + 0x34))(2,0);
        *(undefined4 *)(iVar15 + 0x48) = uVar8;
        if (*(int *)(iVar12 + 0x200) == 2) {
          *(undefined4 *)(iVar15 + 0x48) = 0;
        }
        uVar8 = (**(code **)(*(int *)(iVar12 + 0x88) + 0x34))(6,0);
        *(undefined4 *)(iVar15 + 0x11c) = uVar8;
        *(undefined4 *)(iVar15 + 0x4c) = *(undefined4 *)(iVar12 + 0x208);
        iVar9 = (**(code **)(*(int *)(iVar12 + 0x88) + 0x34))(10,0);
        *(bool *)(iVar15 + 0x62) = iVar9 != 0;
        *(bool *)(iVar15 + 0x60) = *(char *)(iVar12 + 0x228) == '\x02';
        iVar13 = *(int *)(iVar12 + 0xd0) - *(int *)(iVar12 + 0xcc);
        iVar9 = iVar13 >> 0x1f;
        *(bool *)(iVar15 + 0x61) = iVar13 / 0x48 + iVar9 != iVar9;
      }
      FUN_0043c6c0();
      iVar15 = *(int *)(iVar7 + 4);
    }
    iVar12 = *(int *)(*(int *)(iVar5 + 0x22ec) + 8);
    iVar7 = *(int *)(iVar5 + 0x22ec);
    while (iVar12 != iVar7) {
      uVar14 = *(uint *)(iVar12 + 0x10);
      if ((-1 < (int)uVar14) &&
         (uVar14 < (uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124))) {
        iVar7 = *(int *)(param_1 + 0x518) + uVar14 * 0x124;
        *(undefined4 *)(iVar7 + 0x54) = 0xffffffff;
        *(undefined4 *)(iVar7 + 0x50) = 0xffffffff;
        *(undefined4 *)(iVar7 + 0x5c) = 0xffffffff;
        *(undefined4 *)(iVar7 + 0x58) = 0xffffffff;
        if (*(int *)(iVar12 + 0xc4) != 0) {
          *(undefined4 *)(iVar7 + 0x50) = *(undefined4 *)(*(int *)(iVar12 + 0xc4) + 0x28);
          piVar10 = *(int **)(*(int *)(iVar12 + 0xc4) + 0x30);
          piVar11 = *(int **)(*(int *)(iVar12 + 0xc4) + 0x34);
          if (piVar10 != piVar11) {
            do {
              if (*piVar10 == 0xb) break;
              piVar10 = piVar10 + 3;
            } while (piVar10 != piVar11);
            if ((piVar10 != piVar11) && (piVar10 != (int *)0x0)) {
              *(int *)(iVar7 + 0x58) = piVar10[1];
            }
          }
        }
        piVar10 = (int *)**(int **)(iVar12 + 200);
        if (piVar10 != *(int **)(iVar12 + 200)) {
          do {
            if (piVar10[0xc] != *(int *)(iVar7 + 0x50)) {
              *(int *)(iVar7 + 0x54) = piVar10[0xc];
              piVar11 = (int *)piVar10[0xe];
              piVar3 = (int *)piVar10[0xf];
              if (piVar11 != piVar3) {
                do {
                  if (*piVar11 == 0xb) break;
                  piVar11 = piVar11 + 3;
                } while (piVar11 != piVar3);
                if ((piVar11 != piVar3) && (piVar11 != (int *)0x0)) {
                  *(int *)(iVar7 + 0x5c) = piVar11[1];
                }
              }
            }
            piVar10 = (int *)*piVar10;
          } while (piVar10 != (int *)*(int *)(iVar12 + 200));
        }
      }
      FUN_0043c6c0();
      iVar7 = *(int *)(iVar5 + 0x22ec);
    }
    piVar10 = (int *)**(int **)(iVar5 + 0x2960);
    if (piVar10 != *(int **)(iVar5 + 0x2960)) {
      do {
        piVar11 = (int *)piVar10[2];
        if ((((piVar11 != (int *)0x0) && (piVar11[0x102] == -1)) &&
            (uVar14 = (**(code **)(*piVar11 + 0x4c))(), -1 < (int)uVar14)) &&
           ((uVar14 < (uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124) &&
            (iVar7 = *(int *)(param_1 + 0x518) + uVar14 * 0x124,
            -1 < *(int *)(*(int *)(param_1 + 0x518) + 8 + uVar14 * 0x124))))) {
          *(undefined4 *)(iVar7 + 4) = 3;
          *(int **)(iVar7 + 0xc) = piVar11;
          *(int **)(iVar7 + 0x10) = piVar11 + 0x10c;
          uVar4 = FUN_00501090();
          *(undefined1 *)(iVar7 + 0x14) = uVar4;
        }
        piVar10 = (int *)*piVar10;
      } while (piVar10 != (int *)*(int *)(iVar5 + 0x2960));
    }
    iVar5 = *(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518);
    uVar14 = 0;
    iVar7 = iVar5 >> 0x1f;
    if (iVar5 / 0x124 + iVar7 != iVar7) {
      iVar7 = 0;
      do {
        iVar5 = *(int *)(param_1 + 0x518) + iVar7;
        if ((*(int *)(iVar5 + 4) == 3) && (0 < *(int *)(iVar5 + 0x48))) {
          FUN_004fb770(DAT_00666240);
        }
        uVar14 = uVar14 + 1;
        iVar7 = iVar7 + 0x124;
      } while (uVar14 < (uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124));
    }
    FUN_004fa210();
  }
  return;
}


