/* Original Meteor.exe static export @ 005542f0; original sample not executed. */
/* XREF 00553e03 UNCONDITIONAL_CALL */
/* XREF 0054ecb5 UNCONDITIONAL_CALL */
/* XREF 0055410e UNCONDITIONAL_CALL */
/* XREF 0054ab6b UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __thiscall FUN_005542f0(int param_1,uint param_2)

{
  float fVar1;
  DWORD DVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_c;
  uint local_8;
  
  uVar3 = *(uint *)(param_1 + 0x3c);
  if (uVar3 != *(uint *)(param_1 + 0x2c)) {
    DVar2 = timeGetTime();
    uVar3 = DVar2 - *(int *)(param_1 + 0x18);
    if (500 < uVar3) {
      local_c = 0;
      for (local_8 = 0; fVar1 = _DAT_005a83e4,
          iVar6 = *(int *)(param_1 + 0x3c) - *(int *)(param_1 + 0x40), uVar3 = iVar6 * 0x2aaaaaab,
          local_8 < (iVar6 / 0x18 +
                    (*(int *)(param_1 + 0x34) - *(int *)(param_1 + 0x2c)) / 0x18 +
                    (*(int *)(param_1 + 0x48) - *(int *)(param_1 + 0x38) >> 2) * 0x15) - 0x15U;
          local_8 = local_8 + 1) {
        iVar6 = (*(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x30)) / 0x18 + local_8;
        if ((iVar6 < 0) || (0x14 < iVar6)) {
          if (iVar6 < 1) {
            iVar4 = -1 - (-iVar6 - 1U) / 0x15;
          }
          else {
            iVar4 = iVar6 / 0x15;
          }
          iVar6 = *(int *)(*(int *)(param_1 + 0x38) + iVar4 * 4) + (iVar6 + iVar4 * -0x15) * 0x18;
        }
        else {
          iVar6 = *(int *)(param_1 + 0x2c) + local_c;
        }
        if (DVar2 - *(int *)(iVar6 + 0xc) < param_2) {
          return param_2;
        }
        *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + 1;
        *(uint *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + (uint)*(ushort *)(iVar6 + 0x10);
        if (*(float *)(param_1 + 0x20) <= fVar1) {
LAB_0055445a:
          uVar3 = FUN_005547a0(*(undefined4 *)(iVar6 + 0x14),*(undefined2 *)(iVar6 + 0x10),iVar6 + 4
                              );
          if ((int)uVar3 < 1) {
            return uVar3;
          }
          *(DWORD *)(param_1 + 0x18) = DVar2;
        }
        else {
          iVar4 = _rand();
          iVar5 = __ftol();
          if (iVar5 <= iVar4 % 1000) goto LAB_0055445a;
        }
        local_c = local_c + 0x18;
      }
    }
  }
  return uVar3;
}

