/* Original Meteor.exe static export @ 0041b2d0; original sample not executed. */
/* XREF 0041b2ba UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041b2d0(int param_1,uint param_2,uint param_3,int param_4,uint param_5,float param_6)

{
  ushort uVar1;
  longlong lVar2;
  uint *puVar3;
  ushort uVar4;
  int iVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  uint *puVar10;
  undefined4 *puVar11;
  int *piVar12;
  undefined4 local_120 [4];
  int local_110;
  int local_fc;
  undefined4 local_a4 [4];
  int local_94;
  int local_8c [25];
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  undefined4 local_14;
  uint local_10;
  uint *local_c;
  int local_8;
  
  param_6 = param_6 - _DAT_005a83f4;
  if (param_6 <= _DAT_005a83e4) {
    param_6 = -param_6;
  }
  if ((param_6 < _DAT_005a8408 != (param_6 == _DAT_005a8408)) || (DAT_007eabe0 == 8)) {
    local_28 = param_1;
    local_20 = param_1 + param_3;
    local_24 = param_2;
    local_1c = param_2 + param_4;
    piVar12 = local_8c;
    for (iVar5 = 0x19; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar12 = 0;
      piVar12 = piVar12 + 1;
    }
    local_8c[0] = 100;
    local_8c[2] = 0xcc0020;
    piVar12 = *(int **)(DAT_005d5a0c + 0x6f4);
    if (param_5 == 0) {
      (**(code **)(*piVar12 + 0x14))
                (piVar12,&local_28,*(undefined4 *)(DAT_005d5a0c + 0x6f8),&local_28,0x20000,local_8c)
      ;
      return;
    }
    (**(code **)(*piVar12 + 0x14))
              (piVar12,&local_28,*(undefined4 *)(DAT_005d5a0c + 0x6f8),&local_28,0x28000);
    return;
  }
  puVar11 = local_a4;
  for (iVar5 = 0x1f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  local_a4[0] = 0x7c;
  (**(code **)(**(int **)(DAT_005d5a0c + 0x6f8) + 100))
            (*(int **)(DAT_005d5a0c + 0x6f8),0,local_a4,0,0);
  DAT_007e2768 = -0x7789fde4;
  puVar11 = local_120;
  for (iVar5 = 0x1f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  local_120[0] = 0x7c;
  do {
    DAT_007e2768 = (**(code **)(**(int **)(DAT_005d5a0c + 0x6f4) + 100))
                             (*(int **)(DAT_005d5a0c + 0x6f4),0,local_120,0,0);
    if (DAT_007e2768 == 0) break;
  } while (DAT_007e2768 == -0x7789fde4);
  if (DAT_007eabe0 == 0x10) {
    local_10 = __ftol();
    local_10 = local_10 & 0xffff;
    local_18 = __ftol();
    local_18 = local_18 & 0xffff;
    puVar6 = (uint *)(local_94 * param_2 + param_1 * 2 + local_8c[3]);
    puVar9 = (uint *)(local_110 * param_2 + param_1 * 2 + local_fc);
    if (param_5 == 0) {
      if ((DAT_007f18e4 == 1) || (DAT_007f18e4 == 2)) {
        param_5 = 0xf81f07e0;
        param_2 = 0x7e0f81f;
      }
      else {
        param_5 = 0x7c1f03e0;
        param_2 = 0x3e07c1f;
      }
      local_8 = (int)param_3 / 2;
      if (0 < param_4) {
        param_3 = param_4;
        iVar5 = local_8;
        puVar10 = puVar9;
        puVar3 = puVar6;
        do {
          do {
            local_c = puVar3;
            lVar2 = (ulonglong)(*puVar6 & param_5) * (ulonglong)local_10;
            uVar7 = (uint)((ulonglong)lVar2 >> 0x20);
            uVar7 = ((*puVar6 & param_2) * local_10 >> 4 & param_2) +
                    ((uint)lVar2 >> 4 & param_5) + (uVar7 >> 4 | uVar7 << 0x1c);
            lVar2 = (ulonglong)(uVar7 & param_5) * (ulonglong)local_18;
            uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
            *puVar9 = ((*puVar9 & param_2) * local_18 >> 4 & param_2) +
                      ((uint)lVar2 >> 4 & param_5) + (uVar8 >> 4 | uVar8 << 0x1c) + uVar7;
            puVar6 = puVar6 + 1;
            puVar9 = puVar9 + 1;
            iVar5 = iVar5 + -1;
            puVar3 = local_c;
          } while (iVar5 != 0);
          puVar6 = (uint *)((int)local_c + local_94);
          puVar9 = (uint *)((int)puVar10 + local_110);
          param_3 = param_3 + -1;
          iVar5 = local_8;
          puVar10 = puVar9;
          puVar3 = puVar6;
        } while (param_3 != 0);
      }
    }
    else {
      uVar1 = *(ushort *)(DAT_005d5a0c + 0x704);
      local_8 = CONCAT22((short)(param_5 >> 0x10),uVar1);
      if ((DAT_007f18e4 == 1) || (DAT_007f18e4 == 2)) {
        param_5 = 0x7e0;
        param_2 = 0xf81f;
      }
      else {
        param_5 = 0x3e0;
        param_2 = 0xfc1f;
      }
      uVar7 = param_3;
      puVar10 = puVar9;
      puVar3 = puVar6;
      if (0 < param_4) {
        do {
          do {
            local_c = puVar3;
            uVar4 = (ushort)*puVar6;
            if (uVar4 != uVar1) {
              *(ushort *)puVar9 =
                   ((ushort)(((ushort)*puVar9 & param_5) * local_18 >> 4) & 0xfff & (ushort)param_5)
                   + ((ushort)(((ushort)*puVar9 & param_2) * local_18 >> 4) & (ushort)param_2) +
                   ((ushort)((uVar4 & param_2) * local_10 >> 4) & (ushort)param_2) +
                   ((ushort)((uVar4 & param_5) * local_10 >> 4) & 0xfff & (ushort)param_5);
            }
            puVar6 = (uint *)((int)puVar6 + 2);
            puVar9 = (uint *)((int)puVar9 + 2);
            uVar4 = (short)uVar7 - 1;
            uVar7 = (uint)uVar4;
            puVar3 = local_c;
          } while (uVar4 != 0);
          puVar6 = (uint *)((int)local_c + local_94);
          puVar9 = (uint *)((int)puVar10 + local_110);
          param_4 = param_4 + -1;
          uVar7 = param_3;
          puVar10 = puVar9;
          puVar3 = puVar6;
        } while (param_4 != 0);
        local_14 = 0;
      }
    }
  }
  (**(code **)(**(int **)(DAT_005d5a0c + 0x6f8) + 0x80))(*(int **)(DAT_005d5a0c + 0x6f8),0);
  (**(code **)(**(int **)(DAT_005d5a0c + 0x6f4) + 0x80))(*(int **)(DAT_005d5a0c + 0x6f4),0);
  return;
}

