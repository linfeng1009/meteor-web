/* Original Meteor.exe static export @ 0052dce0; original sample not executed. */
/* XREF 0052dc75 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0052dce0(int param_1,int param_2,uint param_3)

{
  char cVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined2 *puVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined4 *puVar12;
  undefined2 *puVar13;
  uint uVar14;
  int iVar15;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  uint local_48;
  int local_44;
  uint local_40;
  undefined4 *local_34;
  undefined2 *local_30;
  
  if (param_1 == 0) {
    FUN_00530d00(0x506);
    return 0;
  }
  iVar8 = *(int *)(param_1 + 0x14);
  iVar9 = *(int *)(param_2 + 0x14);
  if (DAT_005cfe18 == 0x2601) {
    cVar1 = *(char *)(param_1 + 0xd);
    if (cVar1 == '\x01') {
      local_48 = 0;
      if (param_3 != 0) {
        uVar11 = (uint)*(byte *)(param_2 + 0xc);
        do {
          iVar8 = uVar11 * local_48;
          iVar9 = __ftol();
          bVar2 = *(byte *)(param_1 + 0xc);
          uVar14 = 0;
          if (uVar11 != 0) {
            do {
              iVar5 = *(int *)(param_1 + 0x14) + uVar14;
              iVar15 = *(int *)(param_2 + 0x14) + uVar14;
              uVar14 = uVar14 + 1;
              *(undefined1 *)(iVar15 + iVar8) = *(undefined1 *)(iVar5 + iVar9 * (uint)bVar2);
              uVar11 = (uint)*(byte *)(param_2 + 0xc);
            } while (uVar14 < uVar11);
          }
          local_48 = local_48 + 1;
        } while (local_48 < param_3);
        return param_2;
      }
    }
    else if (cVar1 == '\x02') {
      local_48 = 0;
      if (param_3 != 0) {
        uVar11 = (uint)*(byte *)(param_2 + 0xc);
        do {
          iVar5 = __ftol();
          uVar14 = 0;
          if (uVar11 != 0) {
            puVar13 = (undefined2 *)(iVar9 + uVar11 * local_48 * 2);
            puVar7 = (undefined2 *)(iVar8 + iVar5 * (uint)*(byte *)(param_1 + 0xc) * 2);
            do {
              uVar14 = uVar14 + 1;
              *puVar13 = *puVar7;
              uVar11 = (uint)*(byte *)(param_2 + 0xc);
              puVar7 = puVar7 + 1;
              puVar13 = puVar13 + 1;
            } while (uVar14 < uVar11);
          }
          local_48 = local_48 + 1;
        } while (local_48 < param_3);
        return param_2;
      }
    }
    else if ((cVar1 == '\x04') && (local_48 = 0, param_3 != 0)) {
      uVar11 = (uint)*(byte *)(param_2 + 0xc);
      do {
        iVar5 = __ftol();
        uVar14 = 0;
        if (uVar11 != 0) {
          puVar12 = (undefined4 *)(iVar9 + uVar11 * local_48 * 4);
          puVar6 = (undefined4 *)(iVar8 + iVar5 * (uint)*(byte *)(param_1 + 0xc) * 4);
          do {
            uVar14 = uVar14 + 1;
            *puVar12 = *puVar6;
            uVar11 = (uint)*(byte *)(param_2 + 0xc);
            puVar6 = puVar6 + 1;
            puVar12 = puVar12 + 1;
          } while (uVar14 < uVar11);
        }
        local_48 = local_48 + 1;
      } while (local_48 < param_3);
      return param_2;
    }
  }
  else {
    cVar1 = *(char *)(param_1 + 0xd);
    if (cVar1 == '\x01') {
      local_44 = 0;
      local_48 = 0;
      if (param_3 != 0) {
        local_30 = (undefined2 *)(uint)*(byte *)(param_2 + 0xc);
        do {
          uVar11 = __ftol();
          fcos((extraout_ST0_01 - (float10)uVar11) * (float10)_DAT_005cfe98);
          __ftol();
          uVar11 = 0;
          if (local_30 != (undefined2 *)0x0) {
            do {
              uVar3 = __ftol();
              *(undefined1 *)(*(int *)(param_2 + 0x14) + local_44 + uVar11) = uVar3;
              uVar11 = uVar11 + 1;
            } while (uVar11 < *(byte *)(param_2 + 0xc));
          }
          local_30 = (undefined2 *)(uint)*(byte *)(param_2 + 0xc);
          local_44 = local_44 + (int)local_30;
          local_48 = local_48 + 1;
        } while (local_48 < param_3);
      }
    }
    else if (cVar1 == '\x02') {
      local_44 = 0;
      local_48 = 0;
      if (param_3 != 0) {
        uVar11 = (uint)*(byte *)(param_2 + 0xc);
        do {
          uVar14 = __ftol();
          fcos((extraout_ST0_00 - (float10)uVar14) * (float10)_DAT_005cfe98);
          __ftol();
          local_40 = 0;
          if (uVar11 != 0) {
            local_30 = (undefined2 *)(iVar9 + local_44 * 2);
            do {
              uVar4 = __ftol();
              *local_30 = uVar4;
              local_30 = local_30 + 1;
              local_40 = local_40 + 1;
            } while (local_40 < *(byte *)(param_2 + 0xc));
          }
          uVar11 = (uint)*(byte *)(param_2 + 0xc);
          local_44 = local_44 + uVar11;
          local_48 = local_48 + 1;
        } while (local_48 < param_3);
        return param_2;
      }
    }
    else if (cVar1 == '\x04') {
      local_44 = 0;
      local_48 = 0;
      if (param_3 != 0) {
        uVar11 = (uint)*(byte *)(param_2 + 0xc);
        do {
          uVar14 = __ftol();
          fcos((extraout_ST0 - (float10)uVar14) * (float10)_DAT_005cfe98);
          __ftol();
          local_40 = 0;
          if (uVar11 != 0) {
            local_34 = (undefined4 *)(iVar9 + local_44 * 4);
            do {
              uVar10 = __ftol();
              *local_34 = uVar10;
              local_34 = local_34 + 1;
              local_40 = local_40 + 1;
            } while (local_40 < *(byte *)(param_2 + 0xc));
          }
          uVar11 = (uint)*(byte *)(param_2 + 0xc);
          local_44 = local_44 + uVar11;
          local_48 = local_48 + 1;
        } while (local_48 < param_3);
        return param_2;
      }
    }
  }
  return param_2;
}

