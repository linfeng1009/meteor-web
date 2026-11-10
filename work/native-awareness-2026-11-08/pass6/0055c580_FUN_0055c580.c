/* Original Meteor.exe static export @ 0055c580; original sample not executed. */
/* XREF 004dbea5 UNCONDITIONAL_CALL */
/* XREF 00583fef UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __thiscall FUN_0055c580(int param_1,uint param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  uint uVar8;
  undefined1 *puVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  bool bVar13;
  float10 extraout_ST0;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_28;
  int *local_24;
  int *local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a5310;
  local_c = ExceptionList;
  if (*(int *)(param_1 + 0x48) == 0) {
    bVar13 = false;
  }
  else {
    iVar10 = *(int *)(param_1 + 0x64c);
    iVar11 = *(int *)(param_1 + 0x650);
    ExceptionList = &local_c;
    iVar4 = FUN_0055e8b0(iVar11,iVar11,iVar10);
    iVar7 = *(int *)(param_1 + 0x650);
    for (; iVar4 != iVar7; iVar4 = iVar4 + 0xc) {
      FUN_0047a7e0(0);
    }
    iVar10 = (int)((ulonglong)((longlong)(iVar11 - iVar10) * -0x2aaaaaab) >> 0x20);
    *(int *)(param_1 + 0x650) = *(int *)(param_1 + 0x650) + ((iVar10 >> 1) - (iVar10 >> 0x1f)) * 0xc
    ;
    iVar10 = FUN_00509f8f(param_2,&DAT_005ca380);
    bVar13 = false;
    if (iVar10 != 0) {
      iVar11 = *(int *)(param_1 + 0x62c);
      iVar7 = *(int *)(param_1 + 0x630);
      iVar5 = FUN_0055e980(iVar7,iVar7,iVar11);
      iVar4 = *(int *)(param_1 + 0x630);
      for (; iVar5 != iVar4; iVar5 = iVar5 + 0xac) {
        FUN_00560150(0);
      }
      iVar11 = (int)((ulonglong)((longlong)(iVar7 - iVar11) * -0x2fa0be83) >> 0x20);
      *(int *)(param_1 + 0x630) =
           *(int *)(param_1 + 0x630) + ((iVar11 >> 5) - (iVar11 >> 0x1f)) * 0xac;
      FUN_0057a9d0(iVar10,param_1);
      FUN_0057aaf0();
      FUN_00509e57(iVar10);
      iVar10 = FUN_0057aa00();
      if (iVar10 != 0) {
        FUN_0050ac20(s_Read__s_fail_005d1428,param_2);
      }
      *(int *)(param_1 + 0x5dc) = (*(int *)(param_1 + 0x630) - *(int *)(param_1 + 0x62c)) / 0xac;
      if (*(int *)(param_1 + 0x618) != 0) {
        FUN_00507850(*(int *)(param_1 + 0x618));
        *(undefined4 *)(param_1 + 0x618) = 0;
      }
      if (*(int *)(param_1 + 0x61c) != 0) {
        FUN_00507850(*(int *)(param_1 + 0x61c));
        *(undefined4 *)(param_1 + 0x61c) = 0;
      }
      iVar10 = *(int *)(param_1 + 0x28);
      pvVar6 = operator_new(iVar10 << 4);
      if (pvVar6 == (void *)0x0) {
        pvVar6 = (void *)0x0;
      }
      else if (-1 < iVar10 + -1) {
        puVar9 = (undefined1 *)((int)pvVar6 + 1);
        do {
          *(undefined2 *)(puVar9 + 1) = 0xffff;
          puVar9[-1] = 0xff;
          *puVar9 = 0xff;
          puVar9[3] = 1;
          *(undefined4 *)(puVar9 + 7) = 0x3f800000;
          *(undefined4 *)(puVar9 + 0xb) = 0;
          puVar9 = puVar9 + 0x10;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
      }
      iVar10 = *(int *)(param_1 + 0x2c);
      *(void **)(param_1 + 0x618) = pvVar6;
      pvVar6 = operator_new(iVar10 << 4);
      if (pvVar6 == (void *)0x0) {
        pvVar6 = (void *)0x0;
      }
      else if (-1 < iVar10 + -1) {
        puVar9 = (undefined1 *)((int)pvVar6 + 1);
        do {
          *(undefined2 *)(puVar9 + 1) = 0xffff;
          puVar9[-1] = 0xff;
          *puVar9 = 0xff;
          puVar9[3] = 1;
          *(undefined4 *)(puVar9 + 7) = 0x3f800000;
          *(undefined4 *)(puVar9 + 0xb) = 0;
          puVar9 = puVar9 + 0x10;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
      }
      iVar10 = *(int *)(param_1 + 0x62c);
      *(void **)(param_1 + 0x61c) = pvVar6;
      local_3c = 0;
      if (0 < *(int *)(param_1 + 0x5dc)) {
        do {
          if (*(int *)(iVar10 + 0x10) == 1) {
            *(int *)(iVar10 + 0x14) = *(int *)(iVar10 + 0x14) + 50000;
            *(int *)(iVar10 + 0x18) = *(int *)(iVar10 + 0x18) + 50000;
            if (*(int *)(iVar10 + 0x1c) != -1) {
              *(int *)(iVar10 + 0x1c) = *(int *)(iVar10 + 0x1c) + 50000;
            }
            if (*(int *)(iVar10 + 0x20) != -1) {
              *(int *)(iVar10 + 0x20) = *(int *)(iVar10 + 0x20) + 50000;
            }
            *(int *)(iVar10 + 0x48) = *(int *)(iVar10 + 0x48) + 50000;
            *(int *)(iVar10 + 0x4c) = *(int *)(iVar10 + 0x4c) + 50000;
          }
          iVar7 = *(int *)(iVar10 + 0x80) - *(int *)(iVar10 + 0x7c);
          iVar4 = 0;
          iVar11 = iVar7 >> 0x1f;
          param_2 = 0;
          if (iVar7 / 0xc + iVar11 != iVar11) {
            do {
              iVar11 = *(int *)(iVar10 + 0x7c);
              if (*(int *)(iVar10 + 0x10) == 1) {
                *(int *)(iVar4 + iVar11) = *(int *)(iVar4 + iVar11) + 50000;
                *(int *)(iVar4 + 4 + iVar11) = *(int *)(iVar4 + 4 + iVar11) + 50000;
              }
              if (*(int *)(iVar4 + iVar11) < *(int *)(iVar10 + 0x14)) {
                *(int *)(iVar4 + iVar11) = *(int *)(iVar10 + 0x14);
              }
              if (*(int *)(iVar10 + 0x18) < *(int *)(iVar4 + 4 + iVar11)) {
                *(int *)(iVar4 + 4 + iVar11) = *(int *)(iVar10 + 0x18);
              }
              iVar7 = *(int *)(iVar4 + iVar11);
              if (iVar7 <= *(int *)(iVar4 + 4 + iVar11)) {
                do {
                  iVar5 = FUN_0055c4f0(iVar7);
                  if (iVar5 != 0) {
                    *(undefined1 *)(iVar5 + 4) = 1;
                    *(undefined4 *)(iVar5 + 8) = *(undefined4 *)(iVar4 + 8 + iVar11);
                  }
                  iVar7 = iVar7 + 1;
                } while (iVar7 <= *(int *)(iVar4 + 4 + iVar11));
              }
              param_2 = param_2 + 1;
              iVar4 = iVar4 + 0xc;
            } while (param_2 < (uint)((*(int *)(iVar10 + 0x80) - *(int *)(iVar10 + 0x7c)) / 0xc));
          }
          iVar7 = *(int *)(iVar10 + 0x8c) - *(int *)(iVar10 + 0x88);
          param_2 = 0;
          iVar11 = iVar7 >> 0x1f;
          if (iVar7 / 0xc + iVar11 != iVar11) {
            iVar11 = 0;
            do {
              iVar7 = *(int *)(iVar10 + 0x88);
              if (*(int *)(iVar10 + 0x10) == 1) {
                *(int *)(iVar11 + iVar7) = *(int *)(iVar11 + iVar7) + 50000;
                *(int *)(iVar11 + 4 + iVar7) = *(int *)(iVar11 + 4 + iVar7) + 50000;
              }
              if (*(int *)(iVar11 + iVar7) < *(int *)(iVar10 + 0x14)) {
                *(int *)(iVar11 + iVar7) = *(int *)(iVar10 + 0x14);
              }
              if (*(int *)(iVar10 + 0x18) < *(int *)(iVar11 + 4 + iVar7)) {
                *(int *)(iVar11 + 4 + iVar7) = *(int *)(iVar10 + 0x18);
              }
              iVar4 = *(int *)(iVar11 + iVar7);
              if (iVar4 <= *(int *)(iVar11 + 4 + iVar7)) {
                do {
                  iVar5 = FUN_0055c4f0(iVar4);
                  if (iVar5 != 0) {
                    *(undefined1 *)(iVar5 + 4) = 0;
                    *(undefined4 *)(iVar5 + 8) = *(undefined4 *)(iVar11 + 8 + iVar7);
                  }
                  iVar4 = iVar4 + 1;
                } while (iVar4 <= *(int *)(iVar11 + 4 + iVar7));
              }
              param_2 = param_2 + 1;
              iVar11 = iVar11 + 0xc;
            } while (param_2 < (uint)((*(int *)(iVar10 + 0x8c) - *(int *)(iVar10 + 0x88)) / 0xc));
          }
          iVar7 = *(int *)(iVar10 + 0x98) - *(int *)(iVar10 + 0x94);
          param_2 = 0;
          iVar11 = iVar7 >> 0x1f;
          if (iVar7 / 0x68 + iVar11 != iVar11) {
            local_44 = 0;
            do {
              iVar11 = *(int *)(iVar10 + 0x94);
              local_38 = (*(int *)(local_44 + 0x14 + iVar11) - *(int *)(local_44 + 0x10 + iVar11)) /
                         0xc;
              if (*(int *)(iVar10 + 0x10) == 1) {
                *(int *)(local_44 + iVar11) = *(int *)(local_44 + iVar11) + 50000;
                *(int *)(local_44 + 4 + iVar11) = *(int *)(local_44 + 4 + iVar11) + 50000;
              }
              if (*(int *)(local_44 + iVar11) < *(int *)(iVar10 + 0x14)) {
                *(int *)(local_44 + iVar11) = *(int *)(iVar10 + 0x14);
              }
              local_20 = (int *)(local_44 + 4 + iVar11);
              if (*(int *)(iVar10 + 0x18) < *(int *)(local_44 + 4 + iVar11)) {
                *local_20 = *(int *)(iVar10 + 0x18);
              }
              local_24 = (int *)(local_44 + 0x28 + iVar11);
              piVar12 = (int *)(local_44 + 0x1c + iVar11);
              *local_24 = 0;
              iVar7 = *piVar12;
              iVar4 = piVar12[1];
              FUN_0049f3d0(iVar4,iVar4,iVar7,param_2,0);
              piVar12[1] = piVar12[1] + (iVar4 - iVar7 >> 2) * -4;
              if (0 < local_38) {
                local_40 = 0;
                do {
                  local_18 = (undefined4 *)0x0;
                  local_14 = (undefined4 *)0x0;
                  iVar7 = *(int *)(local_44 + 0x10 + iVar11);
                  local_10 = 0;
                  local_4 = 0;
                  iVar4 = *(int *)(local_40 + 4 + iVar7);
                  iVar5 = *(int *)(local_40 + iVar7);
                  iVar7 = (iVar4 - iVar5) + 1;
                  if (iVar7 == -1) {
                    FUN_004030f0();
                  }
                  else if (iVar7 == 0) {
                    local_18 = (undefined4 *)0x0;
                    local_14 = (undefined4 *)0x0;
                    local_10 = 0;
                  }
                  else {
                    local_18 = (undefined4 *)FUN_00402bf0(iVar7);
                    local_10 = iVar7 + (int)local_18;
                    local_14 = local_18;
                  }
                  local_14 = (undefined4 *)FUN_004da870(iVar5,iVar4,local_18);
                  FUN_00402a70();
                  local_4 = 1;
                  local_28 = FUN_00556910(local_18);
                  if (local_28 != -1) {
                    piVar1 = (int *)piVar12[1];
                    if (piVar1 == (int *)piVar12[2]) {
                      FUN_0046ecb0(piVar1,&local_28);
                    }
                    else {
                      if (piVar1 != (int *)0x0) {
                        *piVar1 = local_28;
                      }
                      piVar12[1] = piVar12[1] + 4;
                    }
                  }
                  puVar2 = local_18;
                  uVar8 = local_10 - (int)local_18;
                  local_4 = 0xffffffff;
                  if ((local_18 != (undefined4 *)0x0) && (uVar8 != 0)) {
                    if (uVar8 < 0x81) {
                      FUN_00402330();
                      *puVar2 = *(undefined4 *)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4);
                      *(undefined4 **)(&DAT_005d59a4 + (uVar8 + 7 >> 3) * 4) = puVar2;
                      DAT_005d59e8 = 0;
                    }
                    else {
                      FUN_005089fd(local_18);
                    }
                  }
                  local_40 = local_40 + 0xc;
                  local_38 = local_38 + -1;
                } while (local_38 != 0);
              }
              piVar1 = local_20;
              *local_24 = piVar12[1] - *piVar12 >> 2;
              iVar11 = *(int *)(local_44 + iVar11);
              if (iVar11 <= *local_20) {
                do {
                  puVar9 = (undefined1 *)FUN_0055c4f0(iVar11);
                  if (puVar9 != (undefined1 *)0x0) {
                    *puVar9 = (undefined1)param_2;
                  }
                  iVar11 = iVar11 + 1;
                } while (iVar11 <= *piVar1);
              }
              local_44 = local_44 + 0x68;
              param_2 = param_2 + 1;
            } while (param_2 < (uint)((*(int *)(iVar10 + 0x98) - *(int *)(iVar10 + 0x94)) / 0x68));
          }
          iVar7 = *(int *)(iVar10 + 0xa4) - *(int *)(iVar10 + 0xa0);
          iVar11 = iVar7 >> 0x1f;
          uVar8 = 0;
          if (iVar7 / 0x18 + iVar11 != iVar11) {
            param_2 = 0;
            do {
              piVar12 = (int *)(*(int *)(iVar10 + 0xa0) + param_2);
              iVar11 = *piVar12;
              if (iVar11 <= piVar12[1]) {
                do {
                  iVar7 = FUN_0055c4f0(iVar11);
                  if (iVar7 != 0) {
                    *(char *)(iVar7 + 1) = (char)uVar8;
                  }
                  iVar11 = iVar11 + 1;
                } while (iVar11 <= piVar12[1]);
              }
              param_2 = param_2 + 0x18;
              uVar8 = uVar8 + 1;
            } while (uVar8 < (uint)((*(int *)(iVar10 + 0xa4) - *(int *)(iVar10 + 0xa0)) / 0x18));
          }
          iVar11 = *(int *)(iVar10 + 0x14);
          fVar3 = _DAT_005a83f4 / *(float *)(param_1 + 0x38);
          *(undefined4 *)(iVar10 + 0x54) = 0;
          if (iVar11 <= *(int *)(iVar10 + 0x18)) {
            do {
              iVar7 = FUN_0055c4f0(iVar11);
              if (iVar7 != 0) {
                *(float *)(iVar7 + 0xc) = (float)extraout_ST0;
                *(short *)(iVar7 + 2) = (short)local_3c;
                *(float *)(iVar10 + 0x54) =
                     fVar3 / *(float *)(iVar7 + 8) + *(float *)(iVar10 + 0x54);
              }
              iVar11 = iVar11 + 1;
            } while (iVar11 <= *(int *)(iVar10 + 0x18));
          }
          iVar11 = FUN_00567220();
          if ((iVar11 != 0) &&
             (iVar7 = *(int *)(iVar10 + 0x38) - *(int *)(iVar10 + 0x34), iVar11 = iVar7 >> 0x1f,
             uVar8 = 0, iVar7 / 0xc + iVar11 != iVar11)) {
            iVar11 = 0;
            do {
              local_1c = FUN_00566d40(*(undefined4 *)(iVar11 + *(int *)(iVar10 + 0x34)));
              puVar2 = *(undefined4 **)(iVar10 + 0x2c);
              if (puVar2 == *(undefined4 **)(iVar10 + 0x30)) {
                FUN_0046ecb0(puVar2,&local_1c);
              }
              else {
                if (puVar2 != (undefined4 *)0x0) {
                  *puVar2 = local_1c;
                }
                *(int *)(iVar10 + 0x2c) = *(int *)(iVar10 + 0x2c) + 4;
              }
              uVar8 = uVar8 + 1;
              iVar11 = iVar11 + 0xc;
            } while (uVar8 < (uint)((*(int *)(iVar10 + 0x38) - *(int *)(iVar10 + 0x34)) / 0xc));
          }
          local_3c = local_3c + 1;
          iVar10 = iVar10 + 0xac;
        } while (local_3c < *(int *)(param_1 + 0x5dc));
      }
      *(undefined4 *)(param_1 + 0x628) = 1;
      *(undefined4 *)(param_1 + 0x638) = *(undefined4 *)(param_1 + 0x62c);
      iVar10 = FUN_0057aa00();
      bVar13 = iVar10 == 0;
    }
  }
  ExceptionList = local_c;
  return bVar13;
}

