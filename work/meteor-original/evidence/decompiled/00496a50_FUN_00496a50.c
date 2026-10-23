/* Decompiled from user's Meteor.exe; address: 00496a50 */
/* String anchors: [Cmodel\FlyBar.gmc, cmodel\%sl.gmc, cmodel\%sl.gmb, cmodel\%sb.gmc, cmodel\%sb.gmb, cmodel\%sa.gmc, cmodel\%sa.gmb, cmodel\%s.gmc, cmodel\%s.gmc, cmodel\%s.gmb, cmodel\%s.gmb] */

/* WARNING: Removing unreachable block (ram,0x00496eab) */
/* WARNING: Removing unreachable block (ram,0x00496eaf) */
/* WARNING: Removing unreachable block (ram,0x004970d2) */
/* WARNING: Removing unreachable block (ram,0x004970d6) */
/* WARNING: Removing unreachable block (ram,0x004970e8) */
/* WARNING: Removing unreachable block (ram,0x004970dd) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00496a50(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  void *pvVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  bool bVar11;
  undefined1 local_1a9;
  uint local_1a8;
  undefined4 local_1a4;
  int local_1a0;
  void *local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined **local_178 [4];
  int local_168;
  int local_160;
  int local_15c;
  int local_154;
  int *local_148;
  int *local_144;
  int local_140;
  undefined4 *local_13c;
  int local_134;
  undefined1 local_130 [4];
  undefined1 local_12c [8];
  undefined1 local_124 [8];
  undefined1 local_11c [8];
  undefined1 local_114 [8];
  undefined1 local_10c [256];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059ecd1;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar5 = FUN_004d6570();
  local_1a0 = iVar5;
  FUN_004d6780();
  iVar10 = *(int *)(iVar5 + 4);
  FUN_00478ec0(s_ctexture__005c9564,0);
  if (iVar10 != *(int *)(iVar5 + 8)) {
    do {
      uVar9 = 0;
      if (*(int *)(iVar10 + 0x2c) == 1) {
        FUN_00492000();
        local_4 = 0;
        FUN_005005b0(&local_1a9);
        local_178[0] = &PTR_FUN_005a9488;
        local_4._0_1_ = 1;
        local_4._1_3_ = 0;
        iVar5 = FUN_004d65c0(1,*(undefined4 *)(iVar10 + 0x28),local_178);
        if ((iVar5 != 0) && (piVar6 = local_148, local_148 != local_144)) {
LAB_00496b14:
          if (*piVar6 != 0xb) goto code_r0x00496b19;
          if ((piVar6 != local_144) && (piVar6 != (int *)0x0)) {
            iVar5 = piVar6[1];
            if (iVar5 == 8) {
LAB_00496eb9:
              pvVar7 = operator_new(0x1d0);
              local_4._0_1_ = 6;
              if (pvVar7 == (void *)0x0) {
                uVar9 = 0;
              }
              else {
                uVar9 = FUN_005678a0();
              }
              local_4 = CONCAT31(local_4._1_3_,1);
              FUN_00508ae6(local_10c,s_cmodel__s_gmb_005c9554,*(undefined4 *)(iVar10 + 0x10));
              iVar5 = FUN_00568f80(local_10c,1);
              if (iVar5 == 0) {
                FUN_00508ae6(local_10c,s_cmodel__s_gmc_005c9544,*(undefined4 *)(iVar10 + 0x10));
                FUN_00568f80(local_10c,1);
              }
              FUN_00508ae6(local_10c,s_cmodel__s_des_005c9534,*(undefined4 *)(iVar10 + 0x10));
              FUN_00569e10(local_10c);
              local_198 = *(undefined4 *)(iVar10 + 0x28);
              local_194 = uVar9;
              FUN_0049d760(local_12c,&local_198);
              pvVar7 = operator_new(0x1d0);
              local_4._0_1_ = 7;
              if (pvVar7 == (void *)0x0) {
                uVar9 = 0;
              }
              else {
                uVar9 = FUN_005678a0();
              }
              iVar5 = *(int *)(iVar10 + 0x14);
              iVar1 = *(int *)(iVar10 + 0x10);
              local_4._0_1_ = 8;
              FUN_004608a0((iVar5 - iVar1) + 1);
              iVar5 = FUN_004da870(iVar1,iVar5,0);
              FUN_00402a70();
              local_4._0_1_ = 9;
              *(undefined1 *)(iVar5 + -1) = 0;
              FUN_00508ae6(local_10c,s_cmodel__sl_gmb_005c94c4,0);
              iVar5 = FUN_00568f80(local_10c,1);
              if (iVar5 == 0) {
                FUN_00508ae6(local_10c,s_cmodel__sl_gmc_005c94b4,0);
                FUN_00568f80(local_10c,1);
              }
              FUN_00508ae6(local_10c,s_cmodel__sl_des_005c94a4,0);
              FUN_00569e10(local_10c);
              local_190 = *(undefined4 *)(iVar10 + 0x28);
              local_18c = uVar9;
              FUN_0049d760(local_11c,&local_190);
            }
            else {
              if (iVar5 == 9) {
                local_4._0_1_ = 2;
                FUN_00402ac0(*(undefined4 *)(iVar10 + 0x10),*(undefined4 *)(iVar10 + 0x14));
                local_4._0_1_ = 3;
                uRamffffffff = 0;
                pvVar7 = operator_new(0x1d0);
                local_4._0_1_ = 4;
                if (pvVar7 == (void *)0x0) {
                  uVar9 = 0;
                }
                else {
                  uVar9 = FUN_005678a0();
                }
                local_4 = CONCAT31(local_4._1_3_,3);
                FUN_00508ae6(local_10c,s_cmodel__sa_gmb_005c9524,0);
                iVar5 = FUN_00568f80(local_10c,1);
                if (iVar5 == 0) {
                  FUN_00508ae6(local_10c,s_cmodel__sa_gmc_005c9514,0);
                  iVar5 = FUN_00568f80(local_10c,1);
                  if (iVar5 != 0) goto LAB_00496d65;
                }
                else {
LAB_00496d65:
                  FUN_00508ae6(local_10c,s_cmodel__sa_des_005c9504,0);
                  FUN_00569e10(local_10c);
                  local_188 = *(undefined4 *)(iVar10 + 0x28);
                  local_184 = uVar9;
                  FUN_0049d760(local_124,&local_188);
                }
                pvVar7 = operator_new(0x1d0);
                local_4._0_1_ = 5;
                if (pvVar7 == (void *)0x0) {
                  uVar9 = 0;
                }
                else {
                  uVar9 = FUN_005678a0();
                }
                local_4 = CONCAT31(local_4._1_3_,3);
                FUN_00508ae6(local_10c,s_cmodel__sb_gmb_005c94f4,0);
                iVar5 = FUN_00568f80(local_10c,1);
                if (iVar5 == 0) {
                  FUN_00508ae6(local_10c,s_cmodel__sb_gmc_005c94e4,0);
                  iVar5 = FUN_00568f80(local_10c,1);
                  if (iVar5 != 0) goto LAB_00496e45;
                }
                else {
LAB_00496e45:
                  FUN_00508ae6(local_10c,s_cmodel__sb_des_005c94d4,0);
                  FUN_00569e10(local_10c);
                  local_180 = *(undefined4 *)(iVar10 + 0x28);
                  local_17c = uVar9;
                  FUN_0049d760(local_114,&local_180);
                }
                local_4._0_1_ = 1;
                goto LAB_00496eb9;
              }
              if (iVar5 == 10) goto LAB_00496eb9;
              pvVar7 = operator_new(0x1d0);
              local_4._0_1_ = 10;
              if (pvVar7 != (void *)0x0) {
                uVar9 = FUN_005678a0();
              }
              local_4._0_1_ = 1;
              FUN_00508ae6(local_10c,s_cmodel__s_gmb_005c9554,*(undefined4 *)(iVar10 + 0x10));
              iVar5 = FUN_00568f80(local_10c,1);
              if (iVar5 == 0) {
                FUN_00508ae6(local_10c,s_cmodel__s_gmc_005c9544,*(undefined4 *)(iVar10 + 0x10));
                FUN_00568f80(local_10c,1);
              }
              FUN_00508ae6(local_10c,s_cmodel__s_des_005c9534,*(undefined4 *)(iVar10 + 0x10));
              FUN_00569e10(local_10c);
              local_1a8 = *(uint *)(iVar10 + 0x28);
              iVar5 = *(int *)(param_1 + 0x2194);
              bVar11 = true;
              iVar1 = iVar5;
              iVar2 = *(int *)(iVar5 + 4);
              while (iVar2 != 0) {
                bVar11 = local_1a8 < *(uint *)(iVar2 + 0x10);
                iVar1 = iVar2;
                if (bVar11) {
                  iVar2 = *(int *)(iVar2 + 8);
                }
                else {
                  iVar2 = *(int *)(iVar2 + 0xc);
                }
              }
              local_1a4 = uVar9;
              if (bVar11) {
                if (iVar1 != *(int *)(iVar5 + 8)) {
                  FUN_0044cf00();
                  goto LAB_00496c6b;
                }
                FUN_0049f0f0(&local_19c,0,iVar1,&local_1a8);
              }
              else {
LAB_00496c6b:
                if (*(uint *)(iVar1 + 0x10) < local_1a8) {
                  FUN_0049f0f0(local_130,0,iVar1,&local_1a8);
                }
              }
            }
          }
        }
LAB_00497111:
        puVar4 = local_13c;
        iVar5 = (local_134 - (int)local_13c) / 0x28;
        if (iVar5 != 0) {
          uVar8 = iVar5 * 0x28;
          if (uVar8 < 0x81) {
            FUN_00402330();
            *puVar4 = *(undefined4 *)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4);
            *(undefined4 **)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4) = puVar4;
            DAT_005d59e8 = 0;
          }
          else {
            FUN_005089fd(local_13c);
          }
        }
        piVar3 = local_144;
        local_178[0] = &PTR_FUN_005a94e4;
        local_4 = 0xb;
        for (piVar6 = local_148; piVar6 != piVar3; piVar6 = piVar6 + 3) {
          FUN_004d4a40(piVar6);
        }
        iVar5 = (local_140 - (int)local_148) / 0xc;
        local_4 = 0xffffffff;
        if (iVar5 != 0) {
          FUN_00402e90(local_148,iVar5 * 0xc);
        }
        if ((local_15c != 0) && (local_154 - local_15c != 0)) {
          FUN_00402e90(local_15c,local_154 - local_15c);
        }
        if ((local_168 != 0) && (local_160 - local_168 != 0)) {
          FUN_00402e90(local_168,local_160 - local_168);
        }
        FUN_00402bd0();
        iVar5 = local_1a0;
      }
      iVar10 = iVar10 + 0x48;
    } while (iVar10 != *(int *)(iVar5 + 8));
  }
  local_19c = operator_new(0x1d0);
  local_4 = 0xc;
  if (local_19c == (void *)0x0) {
    uVar9 = 0;
  }
  else {
    uVar9 = FUN_005678a0();
  }
  local_4 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x2964) = uVar9;
  FUN_00568f80(s_Cmodel_FlyBar_gmc_005c9490,1);
  FUN_00569e10(s_Cmodel_FlyBar_des_005c947c);
  ExceptionList = local_c;
  return;
code_r0x00496b19:
  piVar6 = piVar6 + 3;
  if (piVar6 == local_144) goto LAB_00497111;
  goto LAB_00496b14;
}

