/* Decompiled from user's Meteor.exe; address: 005842d0 */
/* String anchors: [%s%s.gmc, %s%s.gmb] */

/* WARNING: Removing unreachable block (ram,0x00584796) */
/* WARNING: Removing unreachable block (ram,0x0058476f) */
/* WARNING: Removing unreachable block (ram,0x0058474b) */
/* WARNING: Removing unreachable block (ram,0x005845fc) */
/* WARNING: Removing unreachable block (ram,0x00584600) */
/* WARNING: Removing unreachable block (ram,0x00584612) */
/* WARNING: Removing unreachable block (ram,0x00584607) */
/* WARNING: Removing unreachable block (ram,0x005846d9) */
/* WARNING: Removing unreachable block (ram,0x005846e1) */
/* WARNING: Removing unreachable block (ram,0x005847a8) */
/* WARNING: Removing unreachable block (ram,0x005846ec) */
/* WARNING: Removing unreachable block (ram,0x0058474f) */
/* WARNING: Removing unreachable block (ram,0x00584773) */
/* WARNING: Removing unreachable block (ram,0x0058479a) */
/* WARNING: Removing unreachable block (ram,0x00584653) */
/* WARNING: Removing unreachable block (ram,0x00584657) */
/* WARNING: Removing unreachable block (ram,0x00584669) */
/* WARNING: Removing unreachable block (ram,0x0058465e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_005842d0(int param_1,char *param_2,char *param_3)

{
  char cVar1;
  int *piVar2;
  void *pvVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined4 *puVar8;
  int iVar9;
  char *pcVar10;
  int local_ac;
  undefined4 *local_a8;
  undefined1 local_8c [128];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a69c0;
  pvStack_c = ExceptionList;
  if (*(int *)(param_1 + 0x274) == 0) {
LAB_005847a4:
    uVar4 = 0;
  }
  else {
    ExceptionList = &pvStack_c;
    FUN_00584180();
    uVar7 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x91c) = 0;
    pcVar10 = (char *)&DAT_005d5a24;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar1 != '\0');
    piVar2 = (int *)FUN_00403200(&DAT_005d5a24,~uVar7 + 0x5d5a23);
    if (piVar2 != (int *)(param_1 + 0x8e0)) {
      FUN_00403200(*piVar2,piVar2[1]);
    }
    if (param_2 != (char *)0x0) {
      uVar7 = 0xffffffff;
      pcVar10 = param_2;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      FUN_00403200(param_2,param_2 + (~uVar7 - 1));
      if (*(int *)(param_1 + 0x8e4) != *(int *)(param_1 + 0x8e0)) {
        *(int *)(param_1 + 0x91c) = *(int *)(param_1 + 0x91c) + 1;
      }
    }
    if (param_3 != (char *)0x0) {
      uVar7 = 0xffffffff;
      pcVar10 = param_3;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      FUN_00403200(param_3,param_3 + (~uVar7 - 1));
      if (*(int *)(param_1 + 0x8f0) != *(int *)(param_1 + 0x8ec)) {
        *(int *)(param_1 + 0x91c) = *(int *)(param_1 + 0x91c) + 1;
      }
    }
    iVar9 = 0;
    if (0 < *(int *)(param_1 + 0x91c)) {
      puVar8 = (undefined4 *)(param_1 + 0x278);
      do {
        pvVar3 = operator_new(0x1d0);
        local_4 = 0;
        if (pvVar3 == (void *)0x0) {
          uVar4 = 0;
        }
        else {
          uVar4 = FUN_005678a0();
        }
        *puVar8 = uVar4;
        iVar9 = iVar9 + 1;
        puVar8 = puVar8 + 1;
        local_4 = 0xffffffff;
      } while (iVar9 < *(int *)(param_1 + 0x91c));
    }
    pcVar5 = (char *)FUN_00478ea0(0);
    uVar7 = 0xffffffff;
    local_4 = 1;
    pcVar10 = pcVar5;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar1 != '\0');
    FUN_00402ac0(pcVar5,pcVar5 + (~uVar7 - 1));
    local_4._1_3_ = 0;
    local_ac = 0;
    if (0 < *(int *)(param_1 + 0x91c)) {
      local_a8 = (undefined4 *)(param_1 + 0x8e0);
      puVar8 = (undefined4 *)(param_1 + 0x278);
      do {
        local_4._0_1_ = 2;
        pcVar5 = (char *)FUN_004807d0(*local_a8);
        uVar7 = 0xffffffff;
        local_4._0_1_ = 3;
        pcVar10 = pcVar5;
        do {
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar10 + 1;
        } while (cVar1 != '\0');
        FUN_00402ac0(pcVar5,pcVar5 + (~uVar7 - 1));
        local_4._0_1_ = 4;
        pcVar5 = (char *)FUN_004807f0(*local_a8);
        uVar7 = 0xffffffff;
        local_4._0_1_ = 5;
        pcVar10 = pcVar5;
        do {
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar10 + 1;
        } while (cVar1 != '\0');
        FUN_00402ac0(pcVar5,pcVar5 + (~uVar7 - 1));
        local_4 = CONCAT31(local_4._1_3_,6);
        FUN_00508ae6(local_8c,s__s_s_gmc_005c9354,0,0);
        FUN_00478ec0(0,0);
        iVar9 = FUN_00568f80(local_8c,1);
        if (iVar9 == 0) {
          FUN_00508ae6(local_8c,s__s_s_gmb_005c9360,0,0);
          iVar9 = FUN_00568f80(local_8c,1);
          if (iVar9 != 0) goto LAB_00584565;
          piVar2 = *(int **)(param_1 + 0x278 + local_ac * 4);
          if (piVar2 != (int *)0x0) {
            (**(code **)(*piVar2 + 8))(1);
            goto LAB_00584728;
          }
LAB_0058472f:
          *(undefined4 *)(param_1 + 0x91c) = 0;
          goto LAB_005847a4;
        }
LAB_00584565:
        FUN_00508ae6(local_8c,s__s_s_des_005c9348,0,0);
        iVar9 = FUN_00569e10(local_8c);
        if (iVar9 == 0) {
          piVar2 = *(int **)(param_1 + 0x278 + local_ac * 4);
          if (piVar2 != (int *)0x0) {
            (**(code **)(*piVar2 + 8))(3);
LAB_00584728:
            *(undefined4 *)(param_1 + 0x278 + local_ac * 4) = 0;
          }
          goto LAB_0058472f;
        }
        uVar6 = FUN_005569b0(s_d_wpnR_005c92cc);
        uVar4 = FUN_005569b0(s_d_wpnL_005c93b8);
        if ((cRamffffffff != 'L') && (cRamffffffff != 'l')) {
          uVar4 = uVar6;
        }
        puVar8[5] = uVar4;
        (**(code **)(**(int **)(param_1 + 0x274) + 0x18))(puVar8[5],*puVar8);
        local_ac = local_ac + 1;
        puVar8 = puVar8 + 1;
        local_a8 = local_a8 + 3;
      } while (local_ac < *(int *)(param_1 + 0x91c));
    }
    local_4._0_1_ = 2;
    FUN_00478ec0(0,0);
    uVar4 = 1;
  }
  ExceptionList = pvStack_c;
  return uVar4;
}

