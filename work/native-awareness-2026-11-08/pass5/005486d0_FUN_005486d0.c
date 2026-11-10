/* Original Meteor.exe static export @ 005486d0; original sample not executed. */
/* XREF 004a66e1 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_005486d0(undefined4 param_1,undefined4 param_2,int param_3,float *param_4,float param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  LONG LVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  float10 fVar19;
  int local_b4;
  int local_ac;
  int *local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  int *local_98;
  undefined4 *local_90;
  int local_8c;
  int local_88;
  int local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  float local_3c;
  float local_38;
  float local_34;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [16];
  void *local_14;
  undefined1 *puStack_10;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_005a438b;
  local_14 = ExceptionList;
  if (DAT_005d5a00 == 0) {
    return 0;
  }
  ExceptionList = &local_14;
  FUN_00407c10(param_1,&local_7c,0,0);
  iVar7 = FUN_00410a70(param_1);
  if (iVar7 == 0) {
    ExceptionList = local_14;
    return 0;
  }
  if (*(int *)(iVar7 + 0x144) == 0) {
    ExceptionList = local_14;
    return 0;
  }
  if (*(int *)(*(int *)(iVar7 + 0x144) + 4) == 0) {
    ExceptionList = local_14;
    return 0;
  }
  if (*(int *)(iVar7 + 0x148) == -1) {
    ExceptionList = local_14;
    return 0;
  }
  local_a0 = 1.0;
  local_a4 = 0.0;
  local_9c = 0.0;
  local_70 = 60.0;
  if (param_3 != 0) {
    FUN_00407c10(param_3,&local_3c,local_24,0);
    fVar16 = (float10)local_7c - (float10)local_3c;
    fVar17 = (float10)local_78 - (float10)local_38;
    local_4c = local_74 - local_34;
    fVar19 = fVar16 * fVar16 + fVar17 * fVar17;
    fVar18 = (float10)fptan((float10)param_5 * (float10)_DAT_005a83e8);
    fVar18 = fVar18 * SQRT((float10)local_4c * (float10)local_4c + fVar19);
    local_70 = (float)(fVar18 + fVar18);
    local_9c = (float)SQRT(fVar19);
    local_a0 = (float)(((float10)_DAT_005a83f4 / (float10)local_9c) * fVar17);
    local_a4 = (float)-((float10)(float)((float10)_DAT_005a83f4 / (float10)local_9c) * fVar16);
  }
  iVar8 = FUN_0040bb20(param_2,local_28,local_2c,local_30);
  iVar9 = FUN_0040bad0(param_2,&local_84);
  local_90 = (undefined4 *)0x0;
  local_8c = 0;
  local_88 = 0;
  local_c = 0;
  FUN_005484c0(param_1,&local_90);
  iVar13 = local_8c - (int)local_90;
  iVar7 = 0;
  local_ac = 0;
  if (0 < local_84) {
    local_b4 = 0;
    local_a8 = (int *)(iVar9 + 0xc);
    iVar9 = 0;
    local_98 = local_a8;
    while( true ) {
      do {
        iVar4 = *local_98;
        if (iVar7 < (int)((uint)(iVar13 >> 2) / 9)) {
          iVar7 = local_b4 + iVar9;
          local_64 = 0.0;
          local_58 = 0.0;
          local_48 = 0;
          uStack_44 = 0;
          fVar1 = (float)local_90[iVar7 * 3];
          fVar2 = (float)local_90[iVar7 * 3 + 1];
          fVar3 = (float)local_90[iVar7 * 3 + 2];
          *(float *)(iVar8 + iVar4 * 0x20) = fVar1;
          local_5c = local_a0;
          *(float *)(iVar8 + 4 + iVar4 * 0x20) = fVar2;
          *(float *)(iVar8 + 8 + iVar4 * 0x20) = fVar3 + _DAT_005a9b34;
          fVar3 = local_7c - fVar1;
          local_80 = SQRT((local_78 - fVar2) * (local_78 - fVar2) + fVar3 * fVar3);
          local_6c = (fVar1 - local_7c) * (_DAT_005a83f4 / local_80);
          local_68 = (fVar2 - local_78) * (_DAT_005a83f4 / local_80);
          local_60 = -local_a4;
          FUN_00548270(&local_60,&local_6c,&local_48,0);
          fVar16 = (float10)fcos((float10)(double)CONCAT44(uStack_44,local_48));
          fVar17 = (float10)local_9c + fVar16 * (float10)local_80;
          fVar18 = (float10)fcos((float10)param_5 * (float10)_DAT_005a83e8);
          fVar17 = ((float10)_DAT_005a8418 -
                   (-(float10)local_4c /
                   SQRT((float10)local_4c * (float10)local_4c + fVar17 * fVar17)) / fVar18) *
                   fVar16 * (float10)local_80;
          fVar16 = (float10)_DAT_005a83f4;
          *(float *)(iVar8 + 0x18 + iVar4 * 0x20) =
               (float)(((float10)fVar3 - fVar17 * (float10)local_a4) * (fVar16 / (float10)local_70)
                      + (float10)_DAT_005a83e8);
          *(float *)(iVar8 + 0x1c + iVar4 * 0x20) =
               (float)((((float10)fVar2 - (float10)local_78) - fVar17 * (float10)local_a0) *
                       (fVar16 / (float10)local_70) + (float10)_DAT_005a83e8);
          iVar7 = local_ac;
        }
        else {
          *(undefined4 *)(iVar8 + 0x18 + iVar4 * 0x20) = 0;
          *(undefined4 *)(iVar8 + 0x1c + iVar4 * 0x20) = 0;
        }
        iVar9 = iVar9 + 1;
        local_98 = local_98 + 1;
      } while (iVar9 < 3);
      iVar7 = iVar7 + 1;
      local_a8 = local_a8 + 6;
      local_b4 = local_b4 + 3;
      if (local_84 <= iVar7) break;
      iVar9 = 0;
      local_ac = iVar7;
      local_98 = local_a8;
    }
  }
  if (param_4 != (float *)0x0) {
    local_6c = *param_4 * _DAT_005a83e8;
    local_68 = param_4[1] * _DAT_005a83e8;
    local_64 = param_4[2] * _DAT_005a83e8;
    local_60 = local_6c;
    local_5c = local_68;
    local_58 = local_64;
    uVar10 = FUN_0040ed10(param_2,0);
    FUN_0040eb20(uVar10,&local_6c,&local_60,0,param_4);
  }
  puVar6 = local_90;
  iVar7 = local_88 - (int)local_90 >> 2;
  if (iVar7 != 0) {
    uVar11 = iVar7 * 4;
    if (uVar11 < 0x81) {
      LVar12 = InterlockedExchange(&DAT_005d59e8,1);
      uVar5 = DAT_005c4248;
      if (LVar12 != 0) {
        uVar15 = 0;
        if (DAT_005c4248 != 0) {
          uVar14 = DAT_005d59ec >> 1;
          do {
            if (((uVar14 <= uVar15) && (DAT_005d59e8 == 0)) &&
               (LVar12 = InterlockedExchange(&DAT_005d59e8,1), LVar12 == 0)) {
              DAT_005c4248 = 1000;
              DAT_005d59ec = uVar15;
              goto LAB_00548c57;
            }
            uVar15 = uVar15 + 1;
          } while (uVar15 < uVar5);
        }
        DAT_005c4248 = 0x1e;
        iVar7 = 6;
        while( true ) {
          iVar8 = iVar7;
          if (0x1b < iVar7) {
            iVar8 = 0x1b;
          }
          LVar12 = InterlockedExchange(&DAT_005d59e8,1);
          if (LVar12 == 0) break;
          if (iVar8 < 0x15) {
            Sleep(0);
            iVar7 = iVar7 + 1;
          }
          else {
            Sleep(1 << ((char)iVar8 - 0x14U & 0x1f));
            iVar7 = iVar7 + 1;
          }
        }
      }
LAB_00548c57:
      *puVar6 = *(undefined4 *)(&DAT_005d59a4 + (uVar11 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar11 + 7 >> 3) * 4) = puVar6;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(local_90);
    }
  }
  ExceptionList = local_14;
  return 1;
}

