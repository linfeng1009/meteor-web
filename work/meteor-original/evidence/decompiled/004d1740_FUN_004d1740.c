/* Meteor.exe original x86 @ 004d1740 */
/* Caller: 005aa8ac */

undefined4 __thiscall FUN_004d1740(int param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  char *pcVar11;
  char *pcVar12;
  char *pcVar13;
  bool bVar14;
  undefined1 local_4d;
  int local_4c;
  uint uStack_48;
  int local_44;
  uint uStack_40;
  int local_3c;
  int local_38;
  undefined1 auStack_34 [8];
  undefined1 auStack_2c [8];
  undefined4 *local_24;
  undefined4 *local_20;
  int local_1c;
  undefined4 *local_18;
  undefined1 *local_14;
  undefined1 *local_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a1b58;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  local_3c = param_1;
  iVar4 = FUN_00509f8f(param_2,&DAT_005c67d0);
  if (iVar4 == 0) {
LAB_004d1c8a:
    uVar7 = 0;
  }
  else {
    local_38 = iVar4;
    FUN_00402b70(&local_4d,8);
    local_4 = 0;
    FUN_00402a70();
    bVar1 = *(byte *)(iVar4 + 0xc);
    local_4 = 1;
    while ((bVar1 & 0x10) == 0) {
      FUN_0050a118(&param_2,1,1,iVar4);
      if ((*(byte *)(iVar4 + 0xc) & 0x20) != 0) {
        FUN_0050b19a(s_Read_error_005c9150);
        break;
      }
      uVar2 = (undefined1)param_2;
      if (local_14 + 1 == local_10) {
        local_44 = (int)local_14 - (int)local_18;
        local_4c = 1;
        piVar5 = (int *)FUN_0049c0d0(&local_44,&local_4c);
        FUN_0049be40(local_14 + (*piVar5 - (int)local_18));
      }
      FUN_00402bc0(local_14 + 1);
      *local_14 = uVar2;
      local_14 = local_14 + 1;
      bVar1 = *(byte *)(iVar4 + 0xc);
    }
    local_24 = (undefined4 *)0x0;
    local_20 = (undefined4 *)0x0;
    local_1c = 0;
    local_4 = CONCAT31(local_4._1_3_,2);
    piVar5 = (int *)FUN_004a1ab0();
    (**(code **)(*piVar5 + 4))(&local_18,&local_24);
    param_2 = param_1 + 4;
    FUN_0049aff0();
    puVar8 = local_24;
    if (local_24 != local_20) {
      do {
        puVar3 = local_20;
        pcVar12 = (char *)*puVar8;
        iVar10 = 0;
        iVar4 = 7;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_Attack_005c91fc;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x1000;
        }
        iVar4 = 6;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_Guard_005c9cdc;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x20;
        }
        iVar4 = 5;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = &DAT_005c9cd4;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x1200;
        }
        iVar4 = 0xd;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_SwitchWeapon_005c9cc4;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x45;
        }
        iVar4 = 7;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_Unlock_005c9cbc;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x51;
        }
        iVar4 = 0xb;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_DropWeapon_005c9cb0;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x47;
        }
        iVar4 = 5;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = &DAT_005c9ca8;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x59;
        }
        iVar4 = 10;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_RightTurn_005c9c9c;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x27;
        }
        iVar4 = 9;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_LeftTurn_005c9c90;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x25;
        }
        iVar4 = 9;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_DropItem_005c9c84;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x48;
        }
        iVar4 = 5;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = &DAT_005c9c7c;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x54;
        }
        iVar4 = 7;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_Crouch_005c9c74;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x43;
        }
        iVar4 = 0xe;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_InitialCamera_005c9c64;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x4c;
        }
        iVar4 = 5;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = &DAT_005c9c5c;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x52;
        }
        iVar4 = 6;
        bVar14 = true;
        pcVar11 = pcVar12;
        pcVar13 = s_Score_005c9c54;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar11 == *pcVar13;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 9;
        }
        iVar4 = 10;
        bVar14 = true;
        pcVar11 = s_HitAttack_005c9c48;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar12 == *pcVar11;
          pcVar12 = pcVar12 + 1;
          pcVar11 = pcVar11 + 1;
        } while (bVar14);
        if (bVar14) {
          iVar10 = 0x46;
        }
        if (puVar8 + 3 == local_20) {
          local_4._0_1_ = 5;
          for (puVar8 = local_24; puVar8 != puVar3; puVar8 = puVar8 + 3) {
            FUN_004026e0();
          }
LAB_004d1c10:
          local_4 = CONCAT31(local_4._1_3_,1);
          iVar4 = (local_1c - (int)local_24) / 0xc;
          if (iVar4 != 0) {
            FUN_00402e90(local_24,iVar4 * 0xc);
          }
          uVar6 = (int)local_10 - (int)local_18;
          if ((local_18 != (undefined4 *)0x0) && (uVar6 != 0)) {
            puVar8 = local_18;
            if (0x80 < uVar6) {
              FUN_005089fd(local_18);
              ExceptionList = pvStack_c;
              return 0;
            }
LAB_004d1c63:
            FUN_00402330();
            *puVar8 = *(undefined4 *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
            *(undefined4 **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = puVar8;
            DAT_005d59e8 = 0;
          }
          goto LAB_004d1c8a;
        }
        uVar6 = FUN_0050915b(puVar8[3]);
        if (uVar6 < 0x100) {
          local_44 = iVar10;
          uStack_40 = uVar6;
          FUN_0049c330(auStack_34,&local_44);
        }
        puVar3 = local_20;
        puVar9 = puVar8 + 6;
        if (puVar9 == local_20) {
          local_4._0_1_ = 4;
          for (puVar8 = local_24; puVar8 != puVar3; puVar8 = puVar8 + 3) {
            FUN_004026e0();
          }
          local_4 = CONCAT31(local_4._1_3_,1);
          iVar4 = (local_1c - (int)local_24) / 0xc;
          if (iVar4 != 0) {
            FUN_00402e90(local_24,iVar4 * 0xc);
          }
          uVar6 = (int)local_10 - (int)local_18;
          if ((local_18 != (undefined4 *)0x0) && (uVar6 != 0)) {
            puVar8 = local_18;
            if (0x80 < uVar6) {
              FUN_005089fd(local_18);
              ExceptionList = pvStack_c;
              return 0;
            }
            goto LAB_004d1c63;
          }
          goto LAB_004d1c8a;
        }
        iVar4 = 2;
        bVar14 = true;
        pcVar12 = (char *)*puVar9;
        pcVar11 = &DAT_005c9c44;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar14 = *pcVar12 == *pcVar11;
          pcVar12 = pcVar12 + 1;
          pcVar11 = pcVar11 + 1;
        } while (bVar14);
        if (bVar14) {
          if (puVar8 + 9 == local_20) {
            local_4._0_1_ = 3;
            for (puVar8 = local_24; puVar8 != puVar3; puVar8 = puVar8 + 3) {
              FUN_004026e0();
            }
            goto LAB_004d1c10;
          }
          uVar6 = FUN_0050915b(puVar8[9]);
          if (uVar6 < 0x100) {
            local_4c = iVar10;
            uStack_48 = uVar6;
            FUN_0049c330(auStack_2c,&local_4c);
          }
          puVar9 = puVar8 + 0xc;
        }
        puVar8 = puVar9;
        iVar4 = local_38;
      } while (puVar9 != local_20);
    }
    FUN_00509e57(iVar4);
    puVar3 = local_20;
    local_4._0_1_ = 6;
    for (puVar8 = local_24; puVar8 != puVar3; puVar8 = puVar8 + 3) {
      FUN_004026e0();
    }
    local_4 = CONCAT31(local_4._1_3_,1);
    iVar4 = (local_1c - (int)local_24) / 0xc;
    if (iVar4 != 0) {
      FUN_00402e90(local_24,iVar4 * 0xc);
    }
    uVar6 = (int)local_10 - (int)local_18;
    if ((local_18 != (undefined4 *)0x0) && (uVar6 != 0)) {
      if (uVar6 < 0x81) {
        FUN_00402330();
        *local_18 = *(undefined4 *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = local_18;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(local_18);
      }
    }
    uVar7 = 1;
  }
  ExceptionList = pvStack_c;
  return uVar7;
}

