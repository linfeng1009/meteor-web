/* Original Meteor.exe static export @ 00548c90; original sample not executed. */
/* XREF 004a673c UNCONDITIONAL_CALL */
/* XREF 004a68aa UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00548c90(int param_1,undefined4 param_2,float param_3,int *param_4,float *param_5)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  LONG LVar12;
  int *piVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  float local_78;
  float local_74;
  float local_70;
  float local_68;
  int local_64;
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined4 *local_54;
  int local_50;
  int local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined1 local_18 [12];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a43a8;
  local_c = ExceptionList;
  if (DAT_005d5a00 == 0) {
    return 0;
  }
  ExceptionList = &local_c;
  FUN_00407c10(param_1,&local_3c,0,0);
  iVar8 = FUN_00410a70(param_1);
  if (iVar8 == 0) {
    ExceptionList = local_c;
    return 0;
  }
  if (*(int *)(iVar8 + 0x144) == 0) {
    ExceptionList = local_c;
    return 0;
  }
  if (*(int *)(*(int *)(iVar8 + 0x144) + 4) == 0) {
    ExceptionList = local_c;
    return 0;
  }
  if (*(int *)(iVar8 + 0x148) == -1) {
    ExceptionList = local_c;
    return 0;
  }
  local_68 = 0.0;
  local_78 = 1.0;
  local_70 = 1.0;
  local_74 = 0.0;
  if (param_4 != (int *)0x0) {
    FUN_00407c10(param_4,&local_30,local_18,0);
    local_48 = local_3c - local_30;
    local_44 = local_38 - local_2c;
    fVar2 = SQRT(local_48 * local_48 + local_44 * local_44);
    if ((_DAT_005a842c < fVar2) && (_DAT_005a842c < -(local_34 - local_28))) {
      fVar3 = -(local_34 - local_28) - _DAT_005aa938;
      if (fVar3 < _DAT_005a83f4) {
        fVar3 = _DAT_005a83f4;
      }
      local_68 = -0.25;
      local_70 = local_44 * (_DAT_005a83f4 / fVar2);
      local_74 = -((_DAT_005a83f4 / fVar2) * local_48);
      local_78 = fVar2 / fVar3 + _DAT_005a83f4;
    }
  }
  iVar8 = FUN_0040bb20(param_2,local_58,local_5c,local_60);
  iVar9 = FUN_0040bad0(param_2,&local_64);
  local_54 = (undefined4 *)0x0;
  local_50 = 0;
  local_4c = 0;
  local_4 = 0;
  FUN_005484c0(param_1,&local_54);
  param_1 = 0;
  if (0 < local_64) {
    iVar14 = 0;
    param_4 = (int *)(iVar9 + 0xc);
    do {
      iVar9 = 0;
      piVar13 = param_4;
      do {
        iVar5 = *piVar13;
        if (param_1 < (int)((uint)(local_50 - (int)local_54 >> 2) / 9)) {
          iVar1 = iVar9 + iVar14;
          fVar2 = (float)local_54[iVar1 * 3];
          fVar3 = (float)local_54[iVar1 * 3 + 1];
          fVar4 = (float)local_54[iVar1 * 3 + 2];
          *(float *)(iVar8 + iVar5 * 0x20) = fVar2;
          *(float *)(iVar8 + 4 + iVar5 * 0x20) = fVar3;
          *(float *)(iVar8 + 8 + iVar5 * 0x20) = fVar4 + _DAT_005a9b34;
          fVar4 = _DAT_005a83f4 / param_3;
          *(float *)(iVar8 + 0x18 + iVar5 * 0x20) =
               (_DAT_005a83e8 -
               (fVar4 / local_78) * ((local_3c - fVar2) * local_74 - (local_38 - fVar3) * local_70))
               - local_68;
          *(float *)(iVar8 + 0x1c + iVar5 * 0x20) =
               _DAT_005a83e8 -
               ((local_3c - fVar2) * local_70 + (local_38 - fVar3) * local_74) * fVar4;
        }
        else {
          *(undefined4 *)(iVar8 + 0x18 + iVar5 * 0x20) = 0;
          *(undefined4 *)(iVar8 + 0x1c + iVar5 * 0x20) = 0;
        }
        iVar9 = iVar9 + 1;
        piVar13 = piVar13 + 1;
      } while (iVar9 < 3);
      param_1 = param_1 + 1;
      param_4 = param_4 + 6;
      iVar14 = iVar14 + 3;
    } while (param_1 < local_64);
  }
  if (param_5 != (float *)0x0) {
    local_40 = _DAT_005a83f4 / (local_78 * local_78 + local_78 * local_78);
    local_48 = local_40 * *param_5;
    local_44 = local_40 * param_5[1];
    local_40 = local_40 * param_5[2];
    local_24 = local_48;
    local_20 = local_44;
    local_1c = local_40;
    uVar10 = FUN_0040ed10(param_2,0);
    FUN_0040eb20(uVar10,&local_24,&local_48,0,param_5);
  }
  puVar7 = local_54;
  iVar8 = local_4c - (int)local_54 >> 2;
  if (iVar8 != 0) {
    uVar11 = iVar8 * 4;
    if (uVar11 < 0x81) {
      LVar12 = InterlockedExchange(&DAT_005d59e8,1);
      uVar6 = DAT_005c4248;
      if (LVar12 != 0) {
        uVar15 = 0;
        if (DAT_005c4248 != 0) {
          uVar16 = DAT_005d59ec >> 1;
          do {
            if (((uVar16 <= uVar15) && (DAT_005d59e8 == 0)) &&
               (LVar12 = InterlockedExchange(&DAT_005d59e8,1), LVar12 == 0)) {
              DAT_005c4248 = 1000;
              DAT_005d59ec = uVar15;
              goto LAB_005491a4;
            }
            uVar15 = uVar15 + 1;
          } while (uVar15 < uVar6);
        }
        DAT_005c4248 = 0x1e;
        iVar8 = 6;
        while( true ) {
          iVar9 = iVar8;
          if (0x1b < iVar8) {
            iVar9 = 0x1b;
          }
          LVar12 = InterlockedExchange(&DAT_005d59e8,1);
          if (LVar12 == 0) break;
          if (iVar9 < 0x15) {
            Sleep(0);
            iVar8 = iVar8 + 1;
          }
          else {
            Sleep(1 << ((char)iVar9 - 0x14U & 0x1f));
            iVar8 = iVar8 + 1;
          }
        }
      }
LAB_005491a4:
      *puVar7 = *(undefined4 *)(&DAT_005d59a4 + (uVar11 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar11 + 7 >> 3) * 4) = puVar7;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(local_54);
    }
  }
  ExceptionList = local_c;
  return 1;
}

