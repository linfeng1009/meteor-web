/* Original Meteor.exe read-only export. Sample not executed. */

void FUN_004d7fc0(int param_1,int *param_2,int *param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined ***pppuVar11;
  undefined1 local_e3;
  undefined1 local_e2;
  undefined1 local_e1;
  int local_e0;
  int local_dc;
  int local_d8;
  undefined1 local_cf;
  undefined1 local_ce;
  undefined1 local_cd;
  int local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc [12];
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  int local_60;
  undefined **local_54;
  undefined1 local_50 [44];
  int *local_24;
  int *local_20;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a2183;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_e0 = FUN_00487830();
  FUN_004024a0(&local_cd);
  local_4 = 0;
  FUN_004024a0(&local_cf);
  local_4._0_1_ = 1;
  FUN_004024a0(&local_ce);
  local_4 = CONCAT31(local_4._1_3_,2);
  FUN_00499700();
  local_80 = 0;
  local_64 = 0;
  local_6c = 0;
  local_70 = 0;
  local_74 = 0;
  local_78 = 0;
  local_7c = 0;
  local_68 = 100;
  local_8c = 2;
  local_88 = 300;
  local_84 = 3;
  local_4 = 3;
  FUN_004aad20();
  FUN_0049d3c0(local_bc,&param_1);
  FUN_005005b0(&local_e2);
  piVar2 = param_3;
  local_4._0_1_ = 4;
  if (local_bc[0] != local_60) {
    local_e3 = local_e2;
    FUN_004da940(*(int *)(local_bc[0] + 0x18) - *(int *)(local_bc[0] + 0x14) >> 2,&local_e3);
    local_4._0_1_ = 5;
    local_d8 = FUN_0049e5e0(*(undefined4 *)(local_bc[0] + 0x14),*(undefined4 *)(local_bc[0] + 0x18),
                            local_dc);
    uVar7 = 0;
    local_4._0_1_ = 6;
    if (local_d8 - local_dc >> 2 != 0) {
      do {
        FUN_00492000();
        local_4._0_1_ = 7;
        FUN_005005b0(&local_e1);
        local_54 = &PTR_FUN_005a9488;
        pppuVar11 = &local_54;
        local_4._0_1_ = 8;
        uVar10 = *(undefined4 *)(local_dc + uVar7 * 4);
        uVar9 = 5;
        FUN_004d6570(5,uVar10,pppuVar11);
        iVar3 = FUN_004d65c0(uVar9,uVar10,pppuVar11);
        if (iVar3 != 0) {
          piVar4 = local_24;
          if (param_1 == 6) {
            for (; piVar4 != local_20; piVar4 = piVar4 + 3) {
              if (*piVar4 == 1) {
                if (piVar4 != local_20) {
                  if ((piVar4 == (int *)0x0) ||
                     ((uint)piVar4[1] <=
                      (uint)(*(int *)(local_e0 + 0x22e0) - *(int *)(local_e0 + 0x22dc) >> 2)))
                  goto LAB_004d81c8;
                  local_4._0_1_ = 9;
                  goto LAB_004d8293;
                }
                break;
              }
            }
            piVar4 = (int *)0x0;
LAB_004d81c8:
            if (local_c8 == local_c4) {
              FUN_0049c640(local_c8,piVar4 + 1);
            }
            else {
              FUN_004a8e30();
              local_c8 = local_c8 + 4;
            }
          }
          iVar3 = piVar2[1];
          if (iVar3 == piVar2[2]) {
            FUN_0047a010(iVar3,local_50);
          }
          else {
            FUN_0047a400(iVar3,local_50);
            piVar2[1] = piVar2[1] + 0xc;
          }
          piVar4 = param_2;
          if (param_2[1] == param_2[2]) {
            FUN_0049c640(param_2[1],local_dc + uVar7 * 4);
          }
          else {
            FUN_004a8e30();
            piVar4[1] = piVar4[1] + 4;
          }
        }
        local_4._0_1_ = 10;
LAB_004d8293:
        FUN_004d6940();
        local_4._0_1_ = 6;
        FUN_004920f0();
        uVar7 = uVar7 + 1;
      } while (uVar7 < (uint)(local_d8 - local_dc >> 2));
    }
    local_4._0_1_ = 4;
    FUN_004fe380();
  }
  if ((param_1 == 6) &&
     (iVar5 = (local_c8 - local_cc >> 2) + -1, iVar3 = local_cc, iVar8 = iVar5, 0 < iVar5)) {
    do {
      local_e0 = iVar8;
      iVar8 = 0;
      if (0 < iVar5) {
        iVar6 = 0;
        local_c0 = iVar5;
        do {
          uVar7 = *(uint *)(iVar3 + iVar8 * 4);
          if (*(uint *)(iVar3 + 4 + iVar8 * 4) < uVar7) {
            *(undefined4 *)(iVar3 + iVar8 * 4) = *(undefined4 *)(iVar3 + 4 + iVar8 * 4);
            *(uint *)(local_cc + 4 + iVar8 * 4) = uVar7;
            iVar3 = *piVar2;
            local_e3 = local_e1;
            FUN_005005b0(&local_e3);
            local_4._0_1_ = 0xb;
            FUN_00402ac0(*(undefined4 *)(iVar6 + iVar3),*(undefined4 *)(iVar6 + 4 + iVar3));
            local_4 = CONCAT31(local_4._1_3_,0xc);
            puVar1 = (undefined4 *)(*piVar2 + 0xc + iVar6);
            if (puVar1 != (undefined4 *)(*piVar2 + iVar6)) {
              FUN_00403200(*puVar1,puVar1[1]);
            }
            if (&local_dc != (int *)(*piVar2 + 0xc + iVar6)) {
              FUN_00403200(local_dc,local_d8);
            }
            local_4._0_1_ = 4;
            iVar3 = *param_2;
            uVar10 = *(undefined4 *)(iVar3 + iVar8 * 4);
            *(undefined4 *)(iVar3 + iVar8 * 4) = *(undefined4 *)(iVar3 + 4 + iVar8 * 4);
            *(undefined4 *)(*param_2 + 4 + iVar8 * 4) = uVar10;
            FUN_00402bd0();
            iVar3 = local_cc;
            iVar5 = local_c0;
          }
          iVar8 = iVar8 + 1;
          iVar6 = iVar6 + 0xc;
        } while (iVar8 < iVar5);
      }
      iVar5 = iVar5 + -1;
      local_e0 = local_e0 + -1;
      iVar8 = local_e0;
      local_c0 = iVar5;
    } while (local_e0 != 0);
  }
  local_4 = CONCAT31(local_4._1_3_,3);
  FUN_004fe380();
  local_4 = 0xffffffff;
  FUN_004872c0();
  ExceptionList = local_c;
  return;
}

