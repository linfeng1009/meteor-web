/* Meteor.exe original x86 @ 004f3380 */
/* Caller: 005aa0cc */
/* Caller: 005ab554 */
/* Caller: 005ab994 */
/* Caller: 005ab314 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004f3380(int *param_1,uint param_2,int param_3)

{
  double dVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  void *pvVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  undefined4 uVar11;
  LONG LVar12;
  uint uVar13;
  uint uVar14;
  int unaff_EDI;
  uint uVar15;
  float10 fVar16;
  undefined4 **ppuVar17;
  undefined4 *puStack_94;
  float fStack_90;
  float fStack_8c;
  int *piStack_88;
  int *piStack_84;
  int iStack_80;
  undefined1 auStack_7c [4];
  uint uStack_78;
  uint uStack_74;
  int *piStack_70;
  float fStack_6c;
  float fStack_68;
  uint uStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  float fStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined1 auStack_24 [24];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a38a6;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  piVar3 = (int *)(**(code **)(*param_1 + 0x48))();
  if (piVar3 != (int *)0x0) {
    iVar4 = FUN_0055d540();
    if (iVar4 != 0) {
      piVar5 = (int *)(**(code **)(*param_1 + 0x44))();
      (**(code **)(*piVar5 + 0x160))();
    }
    puStack_94 = (undefined4 *)0x0;
    fStack_90 = 0.0;
    fStack_8c = 0.0;
    ppuVar17 = &puStack_94;
    uStack_4 = 0;
    piVar5 = piVar3;
    FUN_00487830(piVar3,ppuVar17);
    iVar4 = FUN_00565520(piVar5,ppuVar17);
    if ((iVar4 != 0) && (fVar16 = (float10)FUN_00549b00(), (float10)_DAT_005a8f90 < fVar16)) {
      FUN_00549a90(0,0);
      pvVar6 = operator_new(((int)fStack_90 - (int)puStack_94 >> 2) << 2);
      uVar7 = 0;
      if ((int)fStack_90 - (int)puStack_94 >> 2 != 0) {
        do {
          *(uint *)((int)pvVar6 + uVar7 * 4) = puStack_94[uVar7] | param_2 << 0x10;
          uVar7 = uVar7 + 1;
        } while (uVar7 < (uint)((int)fStack_90 - (int)puStack_94 >> 2));
      }
      FUN_0054a6c0(0x1d,pvVar6,((int)fStack_90 - (int)puStack_94 >> 2) << 2,0);
      FUN_00507850(pvVar6);
    }
    piStack_88 = (int *)0x0;
    piStack_84 = (int *)0x0;
    iStack_80 = 0;
    uStack_4 = CONCAT31(uStack_4._1_3_,1);
    if (param_3 == 0) {
      (**(code **)(*param_1 + 0x11c))(&piStack_88);
    }
    else {
      (**(code **)(*param_1 + 0x124))(&piStack_88);
    }
    piVar5 = piStack_88;
    if (piStack_88 != piStack_84) {
      do {
        iVar4 = (**(code **)(*param_1 + 0x128))(piVar5[1]);
        if (iVar4 != 0) {
          iVar4 = *piVar5;
          fVar16 = (float10)FUN_00549b00();
          if (((float10)_DAT_005a8f90 < fVar16) &&
             (iVar8 = (**(code **)(*piVar3 + 0x3c))(iVar4,param_3), iVar8 != 0)) {
            fStack_68 = (float)piVar5[1];
            uStack_64 = *(int *)(iVar8 + 0x30) << 10 | param_2;
            piVar9 = (int *)(**(code **)(*param_1 + 0x44))();
            iVar10 = (**(code **)(*piVar9 + 0x1a8))();
            uStack_64 = uStack_64 | iVar10 << 0x10;
            (**(code **)(*(int *)(iVar4 + 0x65c) + 4))(auStack_7c,auStack_24,0);
            (**(code **)(*(int *)(unaff_EDI + 0x65c) + 4))(&uStack_54,0,0);
            fStack_6c = fStack_60 - (float)puStack_94;
            uStack_64 = 0;
            fStack_68 = fStack_5c - fStack_90;
            FUN_0047ec40();
            fStack_30 = fStack_6c;
            fStack_2c = fStack_68;
            uStack_28 = uStack_64;
            uStack_54 = uStack_3c;
            uStack_50 = uStack_38;
            uStack_4c = uStack_34;
            FUN_00548270(&uStack_54,&fStack_30,&piStack_88,1);
            dVar1 = (double)CONCAT44(piStack_84,piStack_88);
            if (dVar1 <= _DAT_005a84b8) {
              if (dVar1 <= _DAT_005ab628) {
                if (dVar1 <= _DAT_005ab620) goto LAB_004f36ba;
                uStack_78 = *(uint *)(iVar8 + 0x58) | 0x1000;
              }
              else {
                uStack_78 = *(uint *)(iVar8 + 0x4c);
              }
            }
            else if (_DAT_005ab638 <= dVar1) {
              if (_DAT_005ab630 <= dVar1) {
LAB_004f36ba:
                uStack_78 = *(uint *)(iVar8 + 0x50) | 0x3000;
              }
              else {
                uStack_78 = *(uint *)(iVar8 + 0x54) | 0x2000;
              }
            }
            else {
              uStack_78 = *(uint *)(iVar8 + 0x4c);
            }
            iVar4 = __ftol();
            uStack_74 = __ftol();
            uStack_74 = iVar4 << 0x10 | uStack_74;
            iVar4 = __ftol();
            uVar7 = __ftol();
            piStack_70 = (int *)(iVar4 << 0x10 | uVar7);
            FUN_00549a90(0,0);
            FUN_0054a6c0(5,&iStack_80,0x14,0);
            iVar4 = (**(code **)(*param_1 + 0x7c))();
            if ((iVar4 != 0) && (iVar4 = (**(code **)(*param_1 + 0x170))(piVar5[1]), iVar4 != 0)) {
              piVar9 = (int *)FUN_00487830();
              iVar4 = (**(code **)(*piVar9 + 0x278))(piVar5[1]);
              if (iVar4 != 0) {
                (**(code **)(*param_1 + 0xcc))(*piVar5);
              }
            }
            fStack_48 = (fStack_60 - (float)puStack_94) * (float)_DAT_005ab618 + (float)puStack_94;
            fStack_44 = (fStack_5c - fStack_90) * (float)_DAT_005ab618 + fStack_90;
            fStack_40 = (fStack_58 - fStack_8c) * (float)_DAT_005ab618 + fStack_8c +
                        (float)_DAT_005a9d48;
            piVar9 = (int *)FUN_00487830();
            iVar4 = *piVar9;
            uVar11 = (**(code **)(*param_1 + 0x4c))(s_FrontHit_005c9f90,&fStack_48,0,0);
            (**(code **)(iVar4 + 0x200))(uVar11);
          }
        }
        piVar5 = piVar5 + 3;
      } while (piVar5 != piStack_84);
    }
    iVar4 = (iStack_80 - (int)piStack_88) / 0xc;
    if (iVar4 != 0) {
      uVar7 = iVar4 * 0xc;
      if (uVar7 < 0x81) {
        piStack_70 = piStack_88;
        LVar12 = InterlockedExchange(&DAT_005d59e8,1);
        uVar15 = DAT_005c4248;
        if (LVar12 != 0) {
          uVar14 = 0;
          if (DAT_005c4248 != 0) {
            uVar13 = DAT_005d59ec >> 1;
            do {
              if (((uVar13 <= uVar14) && (DAT_005d59e8 == 0)) &&
                 (LVar12 = InterlockedExchange(&DAT_005d59e8,1), LVar12 == 0)) {
                DAT_005c4248 = 1000;
                DAT_005d59ec = uVar14;
                goto LAB_004f3957;
              }
              uVar14 = uVar14 + 1;
            } while (uVar14 < uVar15);
          }
          DAT_005c4248 = 0x1e;
          iVar4 = 6;
          while( true ) {
            iVar8 = iVar4;
            if (0x1b < iVar4) {
              iVar8 = 0x1b;
            }
            LVar12 = InterlockedExchange(&DAT_005d59e8,1);
            if (LVar12 == 0) break;
            if (iVar8 < 0x15) {
              Sleep(0);
              iVar4 = iVar4 + 1;
            }
            else {
              Sleep(1 << ((char)iVar8 - 0x14U & 0x1f));
              iVar4 = iVar4 + 1;
            }
          }
        }
LAB_004f3957:
        *piStack_70 = *(int *)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4);
        *(int **)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4) = piStack_70;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(piStack_88);
      }
    }
    puVar2 = puStack_94;
    iVar4 = (int)fStack_8c - (int)puStack_94 >> 2;
    if (iVar4 != 0) {
      uVar7 = iVar4 * 4;
      if (uVar7 < 0x81) {
        piStack_70 = (int *)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4);
        LVar12 = InterlockedExchange(&DAT_005d59e8,1);
        uVar7 = DAT_005c4248;
        if (LVar12 != 0) {
          uVar15 = 0;
          if (DAT_005c4248 != 0) {
            uVar14 = DAT_005d59ec >> 1;
            do {
              if (((uVar14 <= uVar15) && (DAT_005d59e8 == 0)) &&
                 (LVar12 = InterlockedExchange(&DAT_005d59e8,1), LVar12 == 0)) {
                DAT_005c4248 = 1000;
                DAT_005d59ec = uVar15;
                goto LAB_004f3a99;
              }
              uVar15 = uVar15 + 1;
            } while (uVar15 < uVar7);
          }
          DAT_005c4248 = 0x1e;
          iVar4 = 6;
          while( true ) {
            iVar8 = iVar4;
            if (0x1b < iVar4) {
              iVar8 = 0x1b;
            }
            LVar12 = InterlockedExchange(&DAT_005d59e8,1);
            if (LVar12 == 0) break;
            if (iVar8 < 0x15) {
              Sleep(0);
              iVar4 = iVar4 + 1;
            }
            else {
              Sleep(1 << ((char)iVar8 - 0x14U & 0x1f));
              iVar4 = iVar4 + 1;
            }
          }
        }
LAB_004f3a99:
        *puVar2 = *piStack_70;
        *piStack_70 = (int)puVar2;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(puStack_94);
      }
    }
  }
  ExceptionList = pvStack_c;
  return 0xffffffff;
}

