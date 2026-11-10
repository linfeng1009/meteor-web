/* Original Meteor.exe static export @ 0041b6b0; original sample not executed. */
/* XREF 0041b2bf UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041b6b0(int param_1,uint param_2,uint param_3,uint param_4,uint param_5,float param_6)

{
  ushort uVar1;
  longlong lVar2;
  uint *puVar3;
  ushort uVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint *puVar10;
  uint *puVar11;
  undefined4 *puVar12;
  int *piVar13;
  undefined4 local_128 [4];
  int local_118;
  int local_104;
  undefined4 local_ac [4];
  int local_9c;
  int local_94 [25];
  int local_30;
  uint local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  uint *local_c;
  int local_8;
  
  iVar7 = param_2 + param_4;
  if (param_2 != (param_2 & 0xfffffffe)) {
    param_2 = param_2 + 1;
  }
  param_6 = param_6 - _DAT_005a83f4;
  if (param_6 <= _DAT_005a83e4) {
    param_6 = -param_6;
  }
  if ((param_6 < _DAT_005a8408 != (param_6 == _DAT_005a8408)) || (DAT_007eabe0 == 8)) {
    local_30 = param_1;
    local_28 = param_1 + param_3;
    piVar13 = local_94;
    for (iVar5 = 0x19; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar13 = 0;
      piVar13 = piVar13 + 1;
    }
    local_94[0] = 100;
    local_94[2] = 0xcc0020;
    if (param_5 == 0) {
      for (; (int)param_2 < iVar7; param_2 = param_2 + 2) {
        local_24 = param_2 + 1;
        local_2c = param_2;
        (**(code **)(**(int **)(DAT_005d5a0c + 0x6f4) + 0x14))
                  (*(int **)(DAT_005d5a0c + 0x6f4),&local_30,*(undefined4 *)(DAT_005d5a0c + 0x6f8),
                   &local_30,0x20000,local_94);
      }
    }
    else if ((int)param_2 < iVar7) {
      do {
        local_24 = param_2 + 1;
        local_2c = param_2;
        (**(code **)(**(int **)(DAT_005d5a0c + 0x6f4) + 0x14))
                  (*(int **)(DAT_005d5a0c + 0x6f4),&local_30,*(undefined4 *)(DAT_005d5a0c + 0x6f8),
                   &local_30,0x28000,local_94);
        param_2 = param_2 + 2;
      } while ((int)param_2 < iVar7);
      return;
    }
    return;
  }
  puVar12 = local_ac;
  for (iVar5 = 0x1f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_ac[0] = 0x7c;
  (**(code **)(**(int **)(DAT_005d5a0c + 0x6f8) + 100))
            (*(int **)(DAT_005d5a0c + 0x6f8),0,local_ac,0,0);
  DAT_007e2768 = -0x7789fde4;
  puVar12 = local_128;
  for (iVar5 = 0x1f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_128[0] = 0x7c;
  do {
    DAT_007e2768 = (**(code **)(**(int **)(DAT_005d5a0c + 0x6f4) + 100))
                             (*(int **)(DAT_005d5a0c + 0x6f4),0,local_128,0,0);
    if (DAT_007e2768 == 0) break;
  } while (DAT_007e2768 == -0x7789fde4);
  if (DAT_007eabe0 == 0x10) {
    local_18 = __ftol();
    local_18 = local_18 & 0xffff;
    local_14 = __ftol();
    local_14 = local_14 & 0xffff;
    local_10 = local_9c * 2;
    puVar6 = (uint *)(local_9c * param_2 + param_1 * 2 + local_94[3]);
    puVar10 = (uint *)(local_118 * param_2 + param_1 * 2 + local_104);
    local_1c = local_118 * 2;
    if (param_5 == 0) {
      if ((DAT_007f18e4 == 1) || (DAT_007f18e4 == 2)) {
        param_4 = 0xf81f07e0;
        param_5 = 0x7e0f81f;
      }
      else {
        param_4 = 0x7c1f03e0;
        param_5 = 0x3e07c1f;
      }
      local_8 = (int)param_3 / 2;
      if ((int)param_2 < iVar7) {
        param_3 = ((iVar7 - param_2) - 1 >> 1) + 1;
        iVar7 = local_8;
        puVar11 = puVar10;
        puVar3 = puVar6;
        do {
          do {
            local_c = puVar3;
            lVar2 = (ulonglong)(*puVar6 & param_4) * (ulonglong)local_18;
            uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
            uVar8 = ((*puVar6 & param_5) * local_18 >> 4 & param_5) +
                    ((uint)lVar2 >> 4 & param_4) + (uVar8 >> 4 | uVar8 << 0x1c);
            lVar2 = (ulonglong)(uVar8 & param_4) * (ulonglong)local_14;
            uVar9 = (uint)((ulonglong)lVar2 >> 0x20);
            *puVar10 = ((*puVar10 & param_5) * local_14 >> 4 & param_5) +
                       ((uint)lVar2 >> 4 & param_4) + (uVar9 >> 4 | uVar9 << 0x1c) + uVar8;
            puVar6 = puVar6 + 1;
            puVar10 = puVar10 + 1;
            iVar7 = iVar7 + -1;
            puVar3 = local_c;
          } while (iVar7 != 0);
          puVar6 = (uint *)((int)local_c + local_10);
          puVar10 = (uint *)((int)puVar11 + local_1c);
          param_3 = param_3 + -1;
          iVar7 = local_8;
          puVar11 = puVar10;
          puVar3 = puVar6;
        } while (param_3 != 0);
      }
    }
    else {
      uVar1 = *(ushort *)(DAT_005d5a0c + 0x704);
      local_8 = CONCAT22((short)(param_5 >> 0x10),uVar1);
      if ((DAT_007f18e4 == 1) || (DAT_007f18e4 == 2)) {
        param_4 = 0x7e0;
        param_5 = 0xf81f;
      }
      else {
        param_4 = 0x3e0;
        param_5 = 0xfc1f;
      }
      if ((int)param_2 < iVar7) {
        local_20 = ((iVar7 - param_2) - 1 >> 1) + 1;
        uVar8 = param_3;
        puVar11 = puVar10;
        puVar3 = puVar6;
        do {
          do {
            local_c = puVar3;
            uVar4 = (ushort)*puVar6;
            if (uVar4 != uVar1) {
              *(ushort *)puVar10 =
                   ((ushort)(((ushort)*puVar10 & param_4) * local_14 >> 4) & 0xfff & (ushort)param_4
                   ) + ((ushort)(((ushort)*puVar10 & param_5) * local_14 >> 4) & (ushort)param_5) +
                   ((ushort)((uVar4 & param_5) * local_18 >> 4) & (ushort)param_5) +
                   ((ushort)((uVar4 & param_4) * local_18 >> 4) & 0xfff & (ushort)param_4);
            }
            puVar6 = (uint *)((int)puVar6 + 2);
            puVar10 = (uint *)((int)puVar10 + 2);
            uVar4 = (short)uVar8 - 1;
            uVar8 = (uint)uVar4;
            puVar3 = local_c;
          } while (uVar4 != 0);
          puVar6 = (uint *)((int)local_c + local_10);
          puVar10 = (uint *)((int)puVar11 + local_1c);
          local_20 = local_20 + -1;
          uVar8 = param_3;
          puVar11 = puVar10;
          puVar3 = puVar6;
        } while (local_20 != 0);
        local_20 = 0;
      }
    }
  }
  (**(code **)(**(int **)(DAT_005d5a0c + 0x6f8) + 0x80))(*(int **)(DAT_005d5a0c + 0x6f8),0);
  (**(code **)(**(int **)(DAT_005d5a0c + 0x6f4) + 0x80))(*(int **)(DAT_005d5a0c + 0x6f4),0);
  return;
}

