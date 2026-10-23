/* Meteor.exe original x86 @ 005637d0 */
/* Caller: 004936c7 */

undefined4 __fastcall FUN_005637d0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  void **ppvVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 **ppuVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  int *piVar13;
  int iVar14;
  undefined4 **ppuVar15;
  char *pcVar16;
  bool bVar17;
  float10 fVar18;
  int local_a8;
  int iStack_a4;
  undefined4 *puStack_a0;
  int iStack_9c;
  int iStack_98;
  undefined4 **ppuStack_94;
  undefined **ppuStack_90;
  undefined4 uStack_8c;
  int iStack_88;
  undefined4 *puStack_84;
  undefined4 *puStack_80;
  undefined4 *puStack_7c;
  undefined1 auStack_78 [20];
  undefined1 auStack_64 [64];
  undefined1 auStack_24 [12];
  undefined1 auStack_18 [12];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a56b7;
  pvStack_c = ExceptionList;
  iVar14 = 0;
  local_a8 = 0;
  ExceptionList = &pvStack_c;
  ppvVar3 = &pvStack_c;
  if (0 < *(int *)(*(int *)(param_1 + 0x120) + 0x38)) {
    do {
      iVar5 = FUN_0056ae80(iVar14);
      iVar6 = FUN_00563300(iVar5);
      if (((2 < iVar6) && (iVar6 < 8)) &&
         (uVar7 = (*(code *)PTR_FUN_005d186c)(5,0,0), (*(uint *)(iVar5 + 0x218) & uVar7) != 0)) {
        local_a8 = local_a8 + 1;
      }
      iVar14 = iVar14 + 1;
      ppvVar3 = ExceptionList;
    } while (iVar14 < *(int *)(*(int *)(param_1 + 0x120) + 0x38));
  }
  ExceptionList = ppvVar3;
  iVar14 = 0;
  if (0 < *(int *)(*(int *)(param_1 + 0x120) + 0x40)) {
    do {
      iVar5 = FUN_0056ae40(iVar14);
      iVar6 = FUN_00563300(iVar5);
      if ((iVar6 < 10) || (0xf < iVar6)) {
        if ((*(char *)(iVar5 + 0x48) == '\0') &&
           (uVar7 = (*(code *)PTR_FUN_005d186c)(5,0,0), (*(uint *)(iVar5 + 0x218) & uVar7) != 0)) {
          iVar6 = -1;
          pcVar16 = (char *)(iVar5 + 0x68);
          do {
            if (iVar6 == 0) break;
            iVar6 = iVar6 + -1;
            cVar1 = *pcVar16;
            pcVar16 = pcVar16 + 1;
          } while (cVar1 != '\0');
          bVar17 = iVar6 == -2;
          goto LAB_005638d2;
        }
      }
      else {
        iVar6 = (*(code *)PTR_FUN_005d186c)(4,iVar5 + 0x48,0);
        if (iVar6 != 0) {
          uVar7 = (*(code *)PTR_FUN_005d186c)(5,0,0);
          bVar17 = (*(uint *)(iVar5 + 0x218) & uVar7) == 0;
LAB_005638d2:
          if (!bVar17) {
            local_a8 = local_a8 + 1;
          }
        }
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < *(int *)(*(int *)(param_1 + 0x120) + 0x40));
  }
  if (*(int *)(param_1 + 0x4b4) != 0) {
    FUN_00507850(*(int *)(param_1 + 0x4b4));
    *(undefined4 *)(param_1 + 0x4b4) = 0;
  }
  *(int *)(param_1 + 0x4b0) = local_a8;
  puStack_a0 = operator_new(local_a8 * 0xac);
  uStack_4 = 0;
  if (puStack_a0 == (undefined4 *)0x0) {
    puVar12 = (undefined4 *)0x0;
  }
  else {
    puVar12 = puStack_a0;
    if (-1 < local_a8 + -1) {
      puVar9 = puStack_a0 + 0x13;
      do {
        puVar9[-0x12] = 2;
        *(undefined1 *)(puVar9 + -0x10) = 1;
        *(undefined2 *)((int)puVar9 + -0x3e) = 0;
        *(undefined2 *)(puVar9 + -0xf) = 0;
        puVar9[-0x13] = 0;
        *(undefined1 *)(puVar9 + -0x11) = 1;
        *(undefined1 *)((int)puVar9 + -0x43) = 1;
        *(undefined1 *)((int)puVar9 + -0x42) = 0;
        *(undefined1 *)((int)puVar9 + -0x41) = 0;
        puVar9[-0xe] = 0;
        puVar9[-0xd] = 0;
        puVar9[-0xc] = 0x40a00000;
        puVar9[-9] = 0;
        puVar9[-8] = 0;
        puVar9[-7] = 0;
        puVar9[-6] = 0;
        puVar9[-4] = 0;
        puVar9[-5] = 0;
        puVar9[-3] = 0;
        puVar9[-2] = 0;
        puVar9[1] = 0;
        *puVar9 = 0;
        puVar9[-1] = 0;
        puVar9[4] = 0;
        puVar9[3] = 0;
        puVar9[2] = 0;
        puVar9[7] = 0;
        puVar9[6] = 0;
        puVar9[5] = 0;
        FUN_00477200();
        puVar9 = puVar9 + 0x2b;
        local_a8 = local_a8 + -1;
        puVar12 = puStack_a0;
      } while (local_a8 != 0);
    }
  }
  *(undefined4 **)(param_1 + 0x4b4) = puVar12;
  iVar14 = 0;
  uStack_4 = 0xffffffff;
  if (0 < *(int *)(param_1 + 0x4b0)) {
    iVar5 = 0;
    do {
      *(int *)(iVar5 + 0x20 + *(int *)(param_1 + 0x4b4)) = iVar14;
      iVar14 = iVar14 + 1;
      iVar5 = iVar5 + 0xac;
    } while (iVar14 < *(int *)(param_1 + 0x4b0));
  }
  local_a8 = 0;
  iStack_98 = 0;
  if (0 < *(int *)(*(int *)(param_1 + 0x120) + 0x38)) {
    iStack_a4 = 0;
    do {
      iVar14 = iStack_98;
      ppuVar8 = (undefined4 **)FUN_0056ae80(iStack_98);
      ppuStack_94 = ppuVar8;
      puStack_a0 = (undefined4 *)FUN_00563300(ppuVar8);
      puVar12 = (undefined4 *)(*(int *)(param_1 + 0x4b4) + iStack_a4);
      if (((2 < (int)puStack_a0) && ((int)puStack_a0 < 8)) &&
         (uVar7 = (*(code *)PTR_FUN_005d186c)(5,0,0), ((uint)ppuVar8[0x86] & uVar7) != 0)) {
        *puVar12 = puStack_a0;
        iVar14 = -1;
        puVar12[10] = ppuVar8;
        ppuVar15 = ppuVar8 + 0x1a;
        do {
          if (iVar14 == 0) break;
          iVar14 = iVar14 + -1;
          cVar1 = *(char *)ppuVar15;
          ppuVar15 = (undefined4 **)((int)ppuVar15 + 1);
        } while (cVar1 != '\0');
        if ((iVar14 != -2) && (iStack_9c = FUN_00567230(ppuVar8 + 0x1a,0), iStack_9c != 0)) {
          puVar9 = (undefined4 *)FUN_0047b740();
          ppuVar8 = ppuVar8 + 0x26;
          for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
            *puVar9 = *ppuVar8;
            ppuVar8 = ppuVar8 + 1;
            puVar9 = puVar9 + 1;
          }
          FUN_00566200(1);
          ppuVar8 = ppuStack_94;
        }
        puVar9 = (undefined4 *)FUN_0057e520(auStack_24);
        puVar12[0x12] = *puVar9;
        puVar12[0x13] = puVar9[1];
        puVar12[0x14] = puVar9[2];
        puVar9 = (undefined4 *)FUN_0057e4f0(auStack_18);
        puVar12[0x15] = *puVar9;
        puVar12[0x16] = puVar9[1];
        puVar12[0x17] = puVar9[2];
        if (puStack_a0 == (undefined4 *)0x3) {
          fVar18 = (float10)FUN_0050a69a((int)ppuVar8 + 0x2e);
          puVar12[6] = (float)fVar18;
        }
        FUN_005603f0();
        FUN_00564480(puVar12);
        *(undefined1 *)(puVar12 + 3) = 1;
        FUN_005644a0(puVar12);
        local_a8 = local_a8 + 1;
        iStack_a4 = iStack_a4 + 0xac;
        iVar14 = iStack_98;
      }
      iStack_98 = iVar14 + 1;
    } while (iStack_98 < *(int *)(*(int *)(param_1 + 0x120) + 0x38));
  }
  *(undefined4 *)(param_1 + 0x220) = 0;
  iStack_98 = 0;
  if (0 < *(int *)(*(int *)(param_1 + 0x120) + 0x40)) {
    iStack_a4 = local_a8 * 0xac;
    do {
      iVar14 = FUN_0056ae40(iStack_98);
      iStack_9c = iVar14;
      ppuStack_94 = (undefined4 **)FUN_00563300(iVar14);
      piVar13 = (int *)(*(int *)(param_1 + 0x4b4) + iStack_a4);
      piVar13[10] = iVar14;
      if (((((int)ppuStack_94 < 10) || (0xf < (int)ppuStack_94)) ||
          (uVar7 = (*(code *)PTR_FUN_005d186c)(5,0,0), (*(uint *)(iVar14 + 0x218) & uVar7) == 0)) ||
         (iVar5 = (*(code *)PTR_FUN_005d186c)(4,iVar14 + 0x48,0), iVar5 == 0)) {
        if ((*(char *)(iVar14 + 0x48) == '\0') &&
           (uVar7 = (*(code *)PTR_FUN_005d186c)(5,0,0), (*(uint *)(iVar14 + 0x218) & uVar7) != 0)) {
          iVar5 = -1;
          pcVar16 = (char *)(iVar14 + 0x68);
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            cVar1 = *pcVar16;
            pcVar16 = pcVar16 + 1;
          } while (cVar1 != '\0');
          if (iVar5 != -2) {
            iVar14 = FUN_00567230((char *)(iVar14 + 0x68),0);
            if (iVar14 != 0) {
              puVar9 = (undefined4 *)FUN_0047b740();
              puVar12 = (undefined4 *)(iStack_9c + 0x98);
              for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
                *puVar9 = *puVar12;
                puVar12 = puVar12 + 1;
                puVar9 = puVar9 + 1;
              }
              FUN_00566200(1);
            }
            goto LAB_00563dd4;
          }
        }
      }
      else {
        *piVar13 = (int)ppuStack_94;
        iVar5 = -1;
        pcVar16 = (char *)(iVar14 + 0x68);
        do {
          if (iVar5 == 0) break;
          iVar5 = iVar5 + -1;
          cVar1 = *pcVar16;
          pcVar16 = pcVar16 + 1;
        } while (cVar1 != '\0');
        if ((iVar5 != -2) &&
           (puStack_a0 = (undefined4 *)FUN_00567230((char *)(iVar14 + 0x68),0),
           puStack_a0 != (undefined4 *)0x0)) {
          puVar9 = (undefined4 *)FUN_0047b740();
          puVar12 = (undefined4 *)(iVar14 + 0x98);
          for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar9 = *puVar12;
            puVar12 = puVar12 + 1;
            puVar9 = puVar9 + 1;
          }
          FUN_00566200(1);
          iVar14 = iStack_9c;
        }
        iVar5 = _strncmp((char *)(iVar14 + 0x28),s_damage_005d1590,6);
        if (iVar5 == 0) {
          fVar18 = (float10)FUN_0050a69a(iVar14 + 0x2e);
          piVar13[6] = (int)(float)fVar18;
        }
        puStack_a0 = (undefined4 *)FUN_00563540(iVar14,local_a8);
        if (puStack_a0 == (undefined4 *)0x0) {
          piVar13[0x14] = 0;
          piVar13[0x13] = 0;
          piVar13[0x12] = 0;
          piVar13[0x17] = 0;
          piVar13[0x16] = 0;
          piVar13[0x15] = 0;
          piVar13[0xb] = 0;
          *(undefined1 *)(piVar13 + 2) = 0;
          piVar13[10] = iVar14;
        }
        else {
          if (ppuStack_94 == (undefined4 **)0xf) {
            ppuStack_94 = (undefined4 **)(*(code *)PTR_FUN_005d186c)(3,iVar14 + 0x48,0);
            piVar13[7] = (int)(float)(int)ppuStack_94;
          }
          puVar10 = (undefined4 *)FUN_0047b740();
          puVar12 = puStack_a0;
          puVar9 = (undefined4 *)(iStack_9c + 0x98);
          for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
            *puVar10 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar10 = puVar10 + 1;
          }
          FUN_0047b750();
          FUN_005604a0(puVar12);
          piVar13[10] = iStack_9c;
          uVar4 = FUN_00569560();
          *(undefined2 *)((int)piVar13 + 0xe) = uVar4;
          uVar4 = FUN_00569570();
          *(undefined2 *)(piVar13 + 4) = uVar4;
          iVar14 = FUN_0056ad10();
          piVar13[1] = iVar14;
          iVar14 = FUN_0056b1f0();
          *(int *)(param_1 + 0x220) = *(int *)(param_1 + 0x220) + iVar14;
        }
        FUN_005603f0();
        FUN_00564480(piVar13);
        *(undefined1 *)(piVar13 + 3) = 1;
        FUN_005644a0(piVar13);
LAB_00563dd4:
        local_a8 = local_a8 + 1;
        iStack_a4 = iStack_a4 + 0xac;
      }
      iStack_98 = iStack_98 + 1;
    } while (iStack_98 < *(int *)(*(int *)(param_1 + 0x120) + 0x40));
  }
  piVar13 = (int *)FUN_005715d0(s_Scene_OnLoad_005d164c);
  *(int **)(param_1 + 0x6c4) = piVar13;
  if (piVar13 != (int *)0x0) {
    (**(code **)(*piVar13 + 4))();
  }
  uVar11 = FUN_005715d0(s_Scene_OnClose_005d163c);
  *(undefined4 *)(param_1 + 0x6c8) = uVar11;
  uVar11 = FUN_005715d0(s_Scene_OnInit_005d162c);
  *(undefined4 *)(param_1 + 0x6cc) = uVar11;
  uVar11 = FUN_005715d0(s_Scene_OnIdle_005d161c);
  *(undefined4 *)(param_1 + 0x6d0) = uVar11;
  uVar11 = FUN_005715d0(s_Scene_OnCharacterEvent_005d1604);
  *(undefined4 *)(param_1 + 0x6d4) = uVar11;
  iStack_98 = 0;
  if (0 < *(int *)(param_1 + 0x4b0)) {
    ppuStack_94 = &puStack_84;
    puVar12 = (undefined4 *)(*(int *)(param_1 + 0x4b4) + 0x34);
    do {
      iVar14 = puVar12[-3] + 8;
      FUN_00508ae6(auStack_64,s__s_OnLoad_005d15f8,iVar14);
      uVar11 = FUN_005715d0(auStack_64);
      puVar12[-1] = uVar11;
      FUN_00508ae6(auStack_64,s__s_OnInit_005d15ec,iVar14);
      uVar11 = FUN_005715d0(auStack_64);
      *puVar12 = uVar11;
      FUN_00508ae6(auStack_64,s__s_OnAttack_005d15e0,iVar14);
      uVar11 = FUN_005715d0(auStack_64);
      puVar12[2] = uVar11;
      FUN_00508ae6(auStack_64,s__s_OnTouch_005d15d4,iVar14);
      uVar11 = FUN_005715d0(auStack_64);
      puVar12[1] = uVar11;
      FUN_00508ae6(auStack_64,s__s_OnPickUp_005d15c8,iVar14);
      uVar11 = FUN_005715d0(auStack_64);
      puVar12[3] = uVar11;
      FUN_00508ae6(auStack_64,s__s_OnIdle_005d15bc,iVar14);
      uVar11 = FUN_005715d0(auStack_64);
      puVar12[4] = uVar11;
      FUN_005783a0();
      uStack_4 = 1;
      puStack_84 = (undefined4 *)0x0;
      puStack_80 = (undefined4 *)0x0;
      puStack_7c = (undefined4 *)0x0;
      FUN_00402330();
      uStack_4._0_1_ = 2;
      if (DAT_005d59a8 == (undefined4 *)0x0) {
        iStack_a4 = 0x14;
        puVar9 = (undefined4 *)FUN_004036c0(8,&iStack_a4);
        if (iStack_a4 != 1) {
          iVar14 = FUN_00460900(8);
          puVar10 = puVar9 + 2;
          (&DAT_005d59a8)[iVar14] = puVar10;
          iStack_9c = 1;
          puVar2 = puVar10;
          if (iStack_a4 != 2) {
            do {
              puVar10 = puVar2 + 2;
              *puVar2 = puVar10;
              iStack_9c = iStack_9c + 1;
              puVar2 = puVar10;
            } while (iStack_a4 + -1 != iStack_9c);
          }
          *puVar10 = 0;
        }
      }
      else {
        puVar9 = DAT_005d59a8;
        DAT_005d59a8 = (undefined4 *)*DAT_005d59a8;
      }
      FUN_00443330();
      puStack_7c = puVar9 + 2;
      uStack_4._0_1_ = 6;
      puStack_84 = puVar9;
      puStack_80 = puVar9;
      FUN_00402a70();
      uStack_8c = 0;
      ppuStack_90 = &PTR_LAB_005ab82c;
      uStack_4 = CONCAT31(uStack_4._1_3_,7);
      iStack_88 = iStack_98;
      FUN_005785c0(&ppuStack_90);
      if (puVar12[-1] != 0) {
        FUN_00570fc0(auStack_78);
        (**(code **)(*(int *)puVar12[-1] + 4))();
      }
      uVar7 = (int)puStack_7c - (int)puStack_84;
      ppuStack_90 = &PTR_LAB_005ab82c;
      if ((puStack_84 != (undefined4 *)0x0) && (uVar7 != 0)) {
        if (uVar7 < 0x81) {
          puStack_a0 = puStack_84;
          FUN_00402330();
          *puStack_a0 = *(undefined4 *)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4);
          *(undefined4 **)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4) = puStack_a0;
          FUN_00443330();
        }
        else {
          FUN_005089fd(puStack_84);
        }
      }
      uStack_4 = 0xffffffff;
      FUN_005783c0();
      iStack_98 = iStack_98 + 1;
      puVar12 = puVar12 + 0x2b;
    } while (iStack_98 < *(int *)(param_1 + 0x4b0));
  }
  FUN_00564140();
  ExceptionList = pvStack_c;
  return 1;
}

