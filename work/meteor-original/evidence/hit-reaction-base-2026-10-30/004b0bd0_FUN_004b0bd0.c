/* Original Meteor.exe static export @ 004b0bd0; original sample not executed. */
/* XREF 005a9c84 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004b0bd0(int *param_1)

{
  float fVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  LONG LVar11;
  int iVar12;
  undefined4 *puVar13;
  uint uVar14;
  int *piVar15;
  int iVar16;
  int *piStack_4c;
  uint local_2c;
  int *piStack_28;
  int *piStack_24;
  int iStack_20;
  int *piStack_1c;
  int *piStack_18;
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a03e8;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  param_1[0xe0] = 0;
  FUN_004b48d0();
  fVar1 = (float)param_1[0x8f] * _DAT_005a8410;
  FUN_00487830();
  FUN_00549a90(0,0);
  uVar2 = FUN_0056d800(0);
  local_2c = uVar2;
  puVar3 = (undefined4 *)FUN_0056d800(1);
  uVar4 = FUN_0056d800(2);
  puVar5 = operator_new(uVar2 * 4);
  puVar13 = puVar5;
  for (uVar2 = uVar2 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  for (iVar12 = 0; iVar12 != 0; iVar12 = iVar12 + -1) {
    *(undefined1 *)puVar13 = 0;
    puVar13 = (undefined4 *)((int)puVar13 + 1);
  }
  puVar6 = operator_new((int)puVar3 * 4);
  puVar13 = puVar6;
  for (uVar2 = (uint)puVar3 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  for (iVar12 = 0; iVar12 != 0; iVar12 = iVar12 + -1) {
    *(undefined1 *)puVar13 = 0;
    puVar13 = (undefined4 *)((int)puVar13 + 1);
  }
  piVar7 = operator_new(uVar4 * 4);
  piVar15 = piVar7;
  for (uVar4 = uVar4 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
    *piVar15 = 0;
    piVar15 = piVar15 + 1;
  }
  for (iVar12 = 0; iVar12 != 0; iVar12 = iVar12 + -1) {
    *(undefined1 *)piVar15 = 0;
    piVar15 = (int *)((int)piVar15 + 1);
  }
  iVar12 = *(int *)(param_1[0xea] + 8);
  if (iVar12 != param_1[0xea]) {
    do {
      (**(code **)(*(int *)(iVar12 + 0x88) + 0xc))(1,fVar1);
      *(undefined4 *)(iVar12 + 0x21c) = *(undefined4 *)(iVar12 + 0x214);
      *(undefined1 *)(iVar12 + 0x228) = 0;
      puVar13 = puVar3;
      piVar15 = param_1;
      if ((*(int *)(iVar12 + 0x208) != 1) &&
         (puVar13 = puVar5, piVar15 = piVar7, *(int *)(iVar12 + 0x208) == 2)) {
        piVar15 = piStack_4c;
      }
      piVar8 = (int *)0x0;
      iStack_20 = 0;
      piStack_1c = (int *)0x0;
      piStack_18 = (int *)0x0;
      pvStack_c = (void *)0x0;
      iVar16 = 0;
      if (0 < (int)piVar15) {
        do {
          if (puVar13[iVar16] == 0) {
            if (piVar8 == piStack_18) {
              FUN_0046ecb0(piVar8,&stack0xffffffac);
              piVar8 = piStack_1c;
            }
            else {
              piVar9 = (int *)0x0;
              if (piVar8 != (int *)0x0) {
                *piVar8 = iVar16;
                piVar9 = piStack_1c;
              }
              piStack_1c = piVar9 + 1;
              piVar8 = piStack_1c;
            }
          }
          iVar16 = iVar16 + 1;
        } while (iVar16 < (int)piVar15);
      }
      (**(code **)(*param_1 + 0x104))(*(undefined4 *)(iVar12 + 0x10));
      iVar16 = iStack_20;
      if ((iStack_20 - (int)piStack_24 & 0xfffffffcU) == 0) {
        FUN_004acae0(*(undefined4 *)(iVar12 + 0x10),0x1c,0,0,1);
      }
      else {
        iVar10 = _rand();
        piStack_28 = (int *)piStack_24[(uint)(iVar10 * (iVar16 - (int)piStack_24 >> 2)) / 0x7fff];
        puVar13[(int)piStack_28] = 1;
        local_2c = *(uint *)(iVar12 + 0x208);
        FUN_004acae0(*(undefined4 *)(iVar12 + 0x10),0x1c,&local_2c,8,1);
      }
      if (*(int *)(iVar12 + 0x200) != 0) {
        *(undefined4 *)(iVar12 + 0x200) = 1;
      }
      iVar16 = *(int *)(iVar12 + 0xc);
      if (iVar16 == 0) {
        iVar16 = *(int *)(iVar12 + 4);
        if (iVar12 == *(int *)(iVar16 + 0xc)) {
          do {
            iVar12 = iVar16;
            iVar16 = *(int *)(iVar12 + 4);
          } while (iVar12 == *(int *)(iVar16 + 0xc));
        }
        if (*(int *)(iVar12 + 0xc) != iVar16) {
          iVar12 = iVar16;
        }
      }
      else {
        for (iVar10 = *(int *)(iVar16 + 8); iVar12 = iVar16, iVar10 != 0;
            iVar10 = *(int *)(iVar10 + 8)) {
          iVar16 = iVar10;
        }
      }
      uStack_4 = 0xffffffff;
      iVar16 = (int)pvStack_10 - (int)piStack_18 >> 2;
      if (iVar16 != 0) {
        uVar2 = iVar16 * 4;
        if (uVar2 < 0x81) {
          piStack_24 = piStack_18;
          piStack_28 = (int *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
          LVar11 = InterlockedExchange(&DAT_005d59e8,1);
          uVar2 = DAT_005c4248;
          if (LVar11 != 0) {
            uVar4 = 0;
            if (DAT_005c4248 != 0) {
              uVar14 = DAT_005d59ec >> 1;
              do {
                if (((uVar14 <= uVar4) && (DAT_005d59e8 == 0)) &&
                   (LVar11 = InterlockedExchange(&DAT_005d59e8,1), LVar11 == 0)) {
                  DAT_005c4248 = 1000;
                  DAT_005d59ec = uVar4;
                  goto LAB_004b0fb2;
                }
                uVar4 = uVar4 + 1;
              } while (uVar4 < uVar2);
            }
            DAT_005c4248 = 0x1e;
            iVar16 = 6;
            while( true ) {
              iVar10 = iVar16;
              if (0x1b < iVar16) {
                iVar10 = 0x1b;
              }
              LVar11 = InterlockedExchange(&DAT_005d59e8,1);
              if (LVar11 == 0) break;
              if (iVar10 < 0x15) {
                Sleep(0);
                iVar16 = iVar16 + 1;
              }
              else {
                Sleep(1 << ((char)iVar10 - 0x14U & 0x1f));
                iVar16 = iVar16 + 1;
              }
            }
          }
LAB_004b0fb2:
          *piStack_24 = *piStack_28;
          *piStack_28 = (int)piStack_24;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(piStack_18);
        }
      }
    } while (iVar12 != param_1[0xea]);
  }
  FUN_00507850(puVar5);
  FUN_00507850(puVar6);
  FUN_00507850(piVar7);
  (**(code **)(*(int *)param_1[0x94] + 0xc))(param_1);
  ExceptionList = pvStack_10;
  return;
}

