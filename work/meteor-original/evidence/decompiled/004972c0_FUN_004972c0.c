/* Decompiled from user's Meteor.exe; address: 004972c0 */
/* String anchors: [cmodel\%s.gmc, cmodel\%s.gmb] */

void FUN_004972c0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  undefined1 *puVar9;
  undefined1 local_17e;
  undefined1 local_17d;
  int local_17c;
  int local_178;
  int *local_174;
  uint local_170;
  undefined4 local_16c;
  int local_168;
  undefined1 local_15c [4];
  undefined1 local_158 [4];
  undefined **local_154 [12];
  int local_124;
  int local_120;
  int local_118;
  undefined4 local_114;
  int local_110;
  undefined1 local_10c [256];
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059ed0f;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar3 = FUN_004d6570();
  iVar6 = *(int *)(iVar3 + 4);
  local_168 = iVar3;
  FUN_00478ec0(s_ctexture__005c9564,0);
  if (iVar6 != *(int *)(iVar3 + 8)) {
    do {
      if ((*(int *)(iVar6 + 0x2c) == 2) || (*(int *)(iVar6 + 0x2c) == 4)) {
        FUN_00492000();
        local_118 = 0;
        local_114 = 0;
        local_110 = 0;
        local_154[0] = &PTR_FUN_005a9488;
        local_4 = 0;
        iVar3 = FUN_004d65c0(*(undefined4 *)(iVar6 + 0x2c),*(undefined4 *)(iVar6 + 0x28),local_154);
        if ((iVar3 != 0) && (*(int *)(iVar6 + 0x14) != *(int *)(iVar6 + 0x10))) {
          local_174 = operator_new(0x1d0);
          local_4._0_1_ = 1;
          if (local_174 == (int *)0x0) {
            uVar4 = 0;
          }
          else {
            uVar4 = FUN_005678a0();
          }
          local_4 = (uint)local_4._1_3_ << 8;
          FUN_00508ae6(local_10c,s_cmodel__s_gmb_005c9554,*(undefined4 *)(iVar6 + 0x10));
          iVar3 = FUN_00568f80(local_10c,1);
          if (iVar3 == 0) {
            FUN_00508ae6(local_10c,s_cmodel__s_gmc_005c9544,*(undefined4 *)(iVar6 + 0x10));
            FUN_00568f80(local_10c,1);
          }
          FUN_00508ae6(local_10c,s_cmodel__s_des_005c9534,*(undefined4 *)(iVar6 + 0x10));
          FUN_00569e10(local_10c);
          iVar3 = *(int *)(local_17c + 0x21c4);
          uVar7 = *(int *)(iVar6 + 0x2c) << 10 | *(uint *)(iVar6 + 0x28);
          bVar8 = true;
          iVar1 = iVar3;
          iVar2 = *(int *)(iVar3 + 4);
          while (iVar2 != 0) {
            bVar8 = uVar7 < *(uint *)(iVar2 + 0x10);
            iVar1 = iVar2;
            if (bVar8) {
              iVar2 = *(int *)(iVar2 + 8);
            }
            else {
              iVar2 = *(int *)(iVar2 + 0xc);
            }
          }
          local_178 = iVar1;
          local_170 = uVar7;
          local_16c = uVar4;
          if (bVar8) {
            if (iVar1 != *(int *)(iVar3 + 8)) {
              FUN_0044cf00();
              goto LAB_004974a1;
            }
            puVar9 = &local_17e;
            local_17e = 1;
            piVar5 = (int *)FUN_0049f0f0(local_158,0,iVar1,&local_170);
          }
          else {
LAB_004974a1:
            if (*(uint *)(local_178 + 0x10) < uVar7) {
              puVar9 = &local_17e;
              local_17e = 1;
              piVar5 = (int *)FUN_0049f0f0(local_15c,0,iVar1,&local_170);
            }
            else {
              puVar9 = &local_17d;
              local_17d = 0;
              piVar5 = &local_178;
            }
          }
          FUN_0046ef70(piVar5,puVar9);
        }
        iVar3 = (local_110 - local_118) / 0x28;
        local_4 = 2;
        if (iVar3 != 0) {
          FUN_00402e90(local_118,iVar3 * 0x28);
        }
        iVar1 = local_120;
        local_174 = &local_124;
        local_154[0] = &PTR_FUN_005a94e4;
        local_4 = 3;
        for (iVar3 = local_124; iVar3 != iVar1; iVar3 = iVar3 + 0xc) {
          FUN_004d4a40(iVar3);
        }
        local_4 = 0xffffffff;
        FUN_0049b270();
        FUN_00402bd0();
        FUN_004026e0();
        FUN_004026e0();
        iVar3 = local_168;
      }
      iVar6 = iVar6 + 0x48;
    } while (iVar6 != *(int *)(iVar3 + 8));
  }
  ExceptionList = local_c;
  return;
}

