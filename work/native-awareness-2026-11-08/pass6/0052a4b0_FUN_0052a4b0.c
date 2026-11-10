/* Original Meteor.exe static export @ 0052a4b0; original sample not executed. */
/* XREF 00527be1 UNCONDITIONAL_CALL */
/* XREF 00527bfc UNCONDITIONAL_CALL */
/* XREF 00527e5e UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0052a4b0(int param_1,int param_2,uint param_3,int param_4)

{
  float fVar1;
  char cVar2;
  undefined2 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  uint uVar7;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  uint extraout_EDX_02;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint local_6c;
  uint local_68;
  float local_64;
  int local_60;
  uint local_5c;
  uint local_58;
  int local_54;
  int local_50;
  int local_4c;
  uint local_48;
  int local_44;
  int *local_40;
  uint local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  uint local_28;
  undefined4 uStack_24;
  int local_20;
  undefined4 local_1c;
  uint local_18;
  undefined4 uStack_14;
  uint local_10;
  undefined4 uStack_c;
  int local_8;
  undefined4 uStack_4;
  
  if (param_1 != 0) {
    FUN_00525610(param_1);
    if ((param_2 != 0) && (param_3 != 0)) {
      if (param_4 == 0x1100) {
        local_68 = 1;
        local_6c = local_68;
      }
      else if (param_4 == 0x1101) {
        local_68 = 2;
        local_6c = local_68;
      }
      else if (param_4 == 0x1102) {
        local_68 = 2;
        local_6c = 1;
      }
      else {
        local_68 = 4;
        local_6c = 2;
      }
      local_68 = param_3 / local_68;
      local_54 = *(int *)(param_1 + 0x38);
      if (47999 < local_68) {
        local_68 = 48000;
      }
      local_48 = 0;
      puVar5 = &DAT_006c5660;
      for (iVar6 = (local_68 & 0x1fffffff) << 1; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
        *(undefined1 *)puVar5 = 0;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
      puVar5 = &DAT_00667a60;
      for (iVar6 = (local_68 & 0x1fffffff) << 1; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
        *(undefined1 *)puVar5 = 0;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
      uVar4 = local_5c;
      if (*(int *)(param_1 + 0x3c) != 0) {
        do {
          iVar6 = *(int *)(local_54 + 0xe08);
          uVar11 = 0;
          iVar10 = local_54;
          while (((iVar6 == 0x1012 && (uVar11 < local_68)) &&
                 ((FUN_00529d50(iVar10,2,&local_38,&local_30,&local_64), local_38 != _DAT_005a83e4
                  || (local_34 != _DAT_005a83e4))))) {
            local_40 = *(int **)(iVar10 + 0xe0);
            if (local_40 != (int *)0x0) {
              local_4c = local_40[1];
              iVar6 = *local_40;
              if ((iVar6 == 0x1100) || (iVar8 = 0x10, iVar6 == 0x1102)) {
                iVar8 = 8;
              }
              if ((iVar6 == 0x1100) || (local_60 = 2, iVar6 == 0x1101)) {
                local_60 = 1;
              }
              local_28 = local_40[3];
              uStack_24 = 0;
              local_20 = *(int *)(param_1 + 0x48);
              local_1c = 0;
              uVar9 = *(uint *)(iVar10 + 0xe10);
              local_64 = ((float)local_28 * local_64) / (float)local_20;
              local_3c = (uint)local_40[2] / ((uint)(local_60 * iVar8) >> 3);
              iVar6 = *(int *)(iVar10 + 0xe0c);
              uStack_14 = 0;
              uStack_c = 0;
              uStack_4 = 0;
              local_5c = uVar9;
              local_58 = iVar6;
              local_18 = local_3c;
              local_10 = uVar9;
              local_8 = iVar6;
              __ftol();
              iVar6 = local_4c + iVar6 * local_60 * 2;
              local_4c = FUN_00529be0(local_64 * _DAT_005ad380);
              iVar8 = extraout_ECX;
              while (iVar8 != 0) {
                uVar4 = uVar9 >> 0xe;
                uVar7 = uVar9 & 0x3fff;
                if (local_60 == 1) {
                  local_44 = (int)(short)((int)*(short *)(iVar6 + uVar4 * 2) * (0x4000 - uVar7) +
                                          (int)*(short *)(iVar6 + 2 + uVar4 * 2) * uVar7 >> 0xe);
                  fVar1 = (float)local_44;
                  (&DAT_006c5660)[uVar11 * 2] =
                       local_38 * fVar1 + (float)(&DAT_006c5660)[uVar11 * 2];
                  *(float *)(&DAT_006c5664 + uVar11 * 8) =
                       local_34 * fVar1 + *(float *)(&DAT_006c5664 + uVar11 * 8);
                  (&DAT_00667a60)[uVar11 * 2] =
                       local_30 * fVar1 + (float)(&DAT_00667a60)[uVar11 * 2];
LAB_0052a825:
                  *(float *)(&DAT_00667a64 + uVar11 * 8) =
                       fVar1 * local_2c + *(float *)(&DAT_00667a64 + uVar11 * 8);
                  iVar10 = local_54;
                }
                else if (local_60 == 2) {
                  fVar1 = (float)(int)(short)((int)*(short *)(iVar6 + 4 + uVar4 * 4) * uVar7 +
                                              (int)*(short *)(iVar6 + uVar4 * 4) * (0x4000 - uVar7)
                                             >> 0xe);
                  (&DAT_006c5660)[uVar11 * 2] =
                       local_38 * fVar1 + (float)(&DAT_006c5660)[uVar11 * 2];
                  (&DAT_00667a60)[uVar11 * 2] =
                       fVar1 * local_30 + (float)(&DAT_00667a60)[uVar11 * 2];
                  local_44 = (int)(short)((int)*(short *)(iVar6 + 6 + uVar4 * 4) * uVar7 +
                                          (int)*(short *)(iVar6 + 2 + uVar4 * 4) * (0x4000 - uVar7)
                                         >> 0xe);
                  fVar1 = (float)local_44;
                  *(float *)(&DAT_006c5664 + uVar11 * 8) =
                       local_34 * fVar1 + *(float *)(&DAT_006c5664 + uVar11 * 8);
                  uVar9 = local_5c;
                  goto LAB_0052a825;
                }
                uVar9 = uVar9 + local_4c;
                uVar11 = uVar11 + 1;
                iVar8 = iVar8 + -1;
                local_5c = uVar9;
                local_50 = iVar8;
              }
              uVar4 = uVar9 & 0x3fff;
              local_58 = local_58 + (uVar9 >> 0xe);
              *(uint *)(iVar10 + 0xe10) = uVar4;
              *(uint *)(iVar10 + 0xe0c) = local_58;
            }
            uVar9 = uVar4 + local_4c;
            uVar4 = uVar9 & 0x3fff;
            local_58 = local_58 + (uVar9 >> 0xe);
            if ((local_40 == (int *)0x0) || (local_3c <= local_58)) {
              puVar5 = *(undefined4 **)(iVar10 + 0xe14);
              if ((puVar5 == (undefined4 *)0x0) ||
                 (iVar6 = *(int *)(iVar10 + 0xa8),
                 *(int *)(iVar10 + 0xe18) - 1U <= *(uint *)(iVar10 + 0xe2c))) {
                FUN_005297f0(iVar10);
                if (*(int *)(iVar10 + 0xa8) != 0) {
                  FUN_005298a0(iVar10);
                  FUN_00529730(iVar10);
                }
              }
              else {
                uVar9 = 0;
                do {
                  if (puVar5 != (undefined4 *)0x0) {
                    if (iVar6 == 0) {
                      puVar5[1] = 2;
                    }
                    puVar5 = (undefined4 *)puVar5[3];
                  }
                  uVar9 = uVar9 + 1;
                } while (uVar9 <= *(uint *)(iVar10 + 0xe2c));
                if (iVar6 == 0) {
                  *(int *)(iVar10 + 0xe1c) = *(int *)(iVar10 + 0xe1c) + 1;
                }
                if (puVar5 != (undefined4 *)0x0) {
                  *(undefined4 *)(iVar10 + 0xe0) = *puVar5;
                }
                *(undefined4 *)(iVar10 + 0xe0c) = 0;
                *(undefined4 *)(iVar10 + 0xe10) = 0;
                *(int *)(iVar10 + 0xe2c) = *(int *)(iVar10 + 0xe2c) + 1;
              }
            }
            iVar6 = *(int *)(iVar10 + 0xe08);
          }
          local_54 = *(int *)(iVar10 + 0xe64);
          local_48 = local_48 + 1;
        } while (local_48 < *(uint *)(param_1 + 0x3c));
      }
      uVar4 = 0;
      if (param_4 == 0x1100) {
        if (param_3 / local_6c != 0) {
          do {
            cVar2 = FUN_00529c00(*(float *)(&DAT_00667a64 + uVar4 * 8) +
                                 *(float *)(&DAT_006c5664 + uVar4 * 8) +
                                 (float)(&DAT_00667a60)[uVar4 * 2] +
                                 (float)(&DAT_006c5660)[uVar4 * 2]);
            *(char *)(extraout_ECX_03 + param_2) = cVar2 + -0x80;
            uVar4 = extraout_ECX_03 + 1;
          } while (uVar4 < extraout_EDX_02);
        }
      }
      else if (param_4 == 0x1101) {
        if (param_3 / local_6c != 0) {
          do {
            uVar3 = FUN_00529c00(*(float *)(&DAT_00667a64 + uVar4 * 8) +
                                 *(float *)(&DAT_006c5664 + uVar4 * 8) +
                                 (float)(&DAT_00667a60)[uVar4 * 2] +
                                 (float)(&DAT_006c5660)[uVar4 * 2]);
            *(undefined2 *)(param_2 + extraout_ECX_02 * 2) = uVar3;
            uVar4 = extraout_ECX_02 + 1;
          } while (uVar4 < extraout_EDX_01);
        }
      }
      else if (param_4 == 0x1102) {
        if (param_3 / local_6c != 0) {
          do {
            iVar6 = (uVar4 & 1) + (uVar4 & 0xfffffffe);
            cVar2 = FUN_00529c00((float)(&DAT_00667a60)[iVar6] + (float)(&DAT_006c5660)[iVar6]);
            *(char *)(extraout_ECX_01 + param_2) = cVar2 + -0x80;
            uVar4 = extraout_ECX_01 + 1;
          } while (uVar4 < extraout_EDX_00);
        }
      }
      else if (param_3 / local_6c != 0) {
        do {
          iVar6 = (uVar4 & 1) + (uVar4 & 0xfffffffe);
          uVar3 = FUN_00529c00((float)(&DAT_00667a60)[iVar6] + (float)(&DAT_006c5660)[iVar6]);
          *(undefined2 *)(param_2 + extraout_ECX_00 * 2) = uVar3;
          uVar4 = extraout_ECX_00 + 1;
        } while (uVar4 < extraout_EDX);
      }
    }
    FUN_00525570();
    FUN_00525620(param_1);
  }
  return;
}

