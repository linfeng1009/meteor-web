/* Original Meteor.exe static export @ 005615e0; original sample not executed. */
/* XREF 004935f3 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_005615e0(int param_1,char *param_2)

{
  float *pfVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  void *pvVar12;
  uint uVar13;
  int iVar14;
  char *pcVar15;
  float *pfVar16;
  char *pcVar17;
  float fVar18;
  bool bVar19;
  undefined *puVar20;
  float local_90;
  int local_8c;
  int *local_88;
  float local_84;
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
  float local_50;
  char local_4c [64];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a564e;
  local_c = ExceptionList;
  uVar13 = 0xffffffff;
  ExceptionList = &local_c;
  *(undefined1 *)(param_1 + 0x251) = 0;
  pcVar15 = param_2;
  do {
    if (uVar13 == 0) break;
    uVar13 = uVar13 - 1;
    cVar2 = *pcVar15;
    pcVar15 = pcVar15 + 1;
  } while (cVar2 != '\0');
  if ((param_2[~uVar13 - 2] == 'b') || (param_2[~uVar13 - 2] == 'B')) {
    bVar19 = true;
    puVar20 = &DAT_005c4580;
  }
  else {
    bVar19 = false;
    puVar20 = &DAT_005ca380;
  }
  iVar4 = FUN_00509f8f(param_2,puVar20);
  uVar9 = 0;
  if (iVar4 != 0) {
    if (bVar19) {
      FUN_0050a118(local_4c,10,1,iVar4);
      iVar14 = 9;
      bVar19 = true;
      pcVar15 = local_4c;
      pcVar17 = s_COL_V1_0_005d1530;
      do {
        if (iVar14 == 0) break;
        iVar14 = iVar14 + -1;
        bVar19 = *pcVar15 == *pcVar17;
        pcVar15 = pcVar15 + 1;
        pcVar17 = pcVar17 + 1;
      } while (bVar19);
      if (!bVar19) {
        FUN_0050ac20(s_Invalid_COL_file_005d151c);
        FUN_00509e57(iVar4);
        ExceptionList = local_c;
        return 0;
      }
      FUN_0050a118(param_1 + 0x4a0,4,1,iVar4);
      FUN_0050a118(param_1 + 0x4a4,4,1,iVar4);
      FUN_0050a118(param_1 + 0x4a8,4,1,iVar4);
      FUN_0050a118(param_1 + 0x49c,4,1,iVar4);
      FUN_0050a118(param_1 + 0x490,4,3,iVar4);
      FUN_0050a118(param_1 + 0x478,4,3,iVar4);
      FUN_0050a118(param_1 + 0x484,4,3,iVar4);
    }
    else {
      FUN_0050b600(iVar4,s__s__d__d__d__d_005d1338,local_4c,param_1 + 0x4a0,param_1 + 0x4a4,
                   param_1 + 0x4a8,param_1 + 0x49c);
      FUN_0050b600(iVar4,s__s__f__f__f_005d1298,local_4c,param_1 + 0x490,param_1 + 0x494,
                   param_1 + 0x498);
      FUN_0050b600(iVar4,s__s__f__f__f__f__f__f_005d1504,local_4c,param_1 + 0x478,param_1 + 0x47c,
                   param_1 + 0x480,param_1 + 0x484,param_1 + 0x488,param_1 + 0x48c);
    }
    *(int *)(param_1 + 0x4ac) = *(int *)(param_1 + 0x4a0) * *(int *)(param_1 + 0x4a4);
    iVar5 = FUN_0050a38c(iVar4);
    FUN_0050a2d3(iVar4,0,2);
    iVar6 = FUN_0050a38c(iVar4);
    FUN_0050a2d3(iVar4,iVar5,0);
    iVar14 = *(int *)(param_1 + 0x49c);
    piVar7 = operator_new(iVar14 * 0x58 + 4);
    local_4 = 0;
    if (piVar7 == (int *)0x0) {
      piVar8 = (int *)0x0;
    }
    else {
      piVar8 = piVar7 + 1;
      *piVar7 = iVar14;
      FUN_0050ac61(piVar8,0x58,iVar14,&LAB_0057e040,&LAB_00560fc0);
    }
    local_4 = 0xffffffff;
    *(int **)(param_1 + 0x2ec) = piVar8;
    if (piVar8 == (int *)0x0) {
      FUN_00509e57(iVar4);
      uVar9 = 0;
    }
    else {
      iVar14 = *(int *)(param_1 + 0x2a4);
      uVar13 = *(uint *)(param_1 + 0x49c);
      local_84 = 0.0;
      uVar10 = iVar14 - *(int *)(param_1 + 0x2a0) >> 2;
      if (uVar13 < uVar10) {
        local_80 = (float)(*(int *)(param_1 + 0x2a0) + uVar13 * 4);
        iVar11 = FUN_0049f3d0(iVar14,iVar14,local_80,piVar7,0);
        iVar3 = *(int *)(param_1 + 0x2a4);
        for (; iVar11 != iVar3; iVar11 = iVar11 + 4) {
          FUN_004d4a40(iVar11);
        }
        *(int *)(param_1 + 0x2a4) = *(int *)(param_1 + 0x2a4) + (iVar14 - (int)local_80 >> 2) * -4;
      }
      else {
        FUN_00565b30(iVar14,uVar13 - uVar10,&local_84);
      }
      pvVar12 = operator_new(((int)((iVar6 - iVar5) + (iVar6 - iVar5 >> 0x1f & 3U)) >> 2) * 4);
      local_88 = *(int **)(param_1 + 0x2ec);
      *(void **)(param_1 + 0x2f0) = pvVar12;
      uVar9 = FUN_0056b1f0();
      *(undefined4 *)(param_1 + 0x290) = uVar9;
      fVar18 = 0.0;
      *(undefined4 *)(param_1 + 0x28c) = 0;
      local_8c = 0;
      local_90 = 0.0;
      local_84 = 0.0;
      local_80 = 0.0;
      if (0 < *(int *)(param_1 + 0x49c)) {
        pfVar16 = (float *)(local_88 + 5);
        do {
          FUN_0057e060(iVar4,*(int *)(param_1 + 0x2f0) + local_8c * 4);
          pfVar16[10] = fVar18;
          pfVar16[0xc] = local_84;
          pfVar16[-3] = local_80;
          pfVar16[0xb] = local_90;
          pfVar1 = pfVar16 + 1;
          fVar18 = (float)((int)fVar18 + 1);
          pfVar16[-2] = (float)(int)pfVar16[10] * *(float *)(param_1 + 0x490) +
                        *(float *)(param_1 + 0x478);
          pfVar16[-1] = (float)(int)local_90 * *(float *)(param_1 + 0x494) +
                        *(float *)(param_1 + 0x47c);
          *pfVar16 = (float)(int)local_84 * *(float *)(param_1 + 0x498) +
                     *(float *)(param_1 + 0x480);
          local_64 = *(float *)(param_1 + 0x490) + pfVar16[-2];
          local_60 = pfVar16[-1] + *(float *)(param_1 + 0x494);
          local_5c = *pfVar16 + *(float *)(param_1 + 0x498);
          *pfVar1 = local_64;
          pfVar16[2] = local_60;
          pfVar16[3] = local_5c;
          local_50 = *pfVar16 + pfVar16[3];
          local_7c = (pfVar16[-2] + *pfVar1) * _DAT_005a83e8;
          local_78 = (pfVar16[-1] + pfVar16[2]) * _DAT_005a83e8;
          pfVar16[4] = local_7c;
          local_74 = local_50 * _DAT_005a83e8;
          pfVar16[5] = local_78;
          pfVar16[6] = local_74;
          local_70 = *pfVar1 - pfVar16[4];
          local_6c = pfVar16[2] - pfVar16[5];
          local_68 = pfVar16[3] - pfVar16[6];
          pfVar16[7] = local_70;
          pfVar16[8] = local_6c;
          pfVar16[9] = local_68;
          if (*(int *)(param_1 + 0x4a0) <= (int)fVar18) {
            fVar18 = 0.0;
            local_90 = (float)((int)local_90 + 1);
          }
          if (*(int *)(param_1 + 0x4a4) <= (int)local_90) {
            fVar18 = 0.0;
            local_84 = (float)((int)local_84 + 1);
            local_90 = 0.0;
          }
          if (*local_88 < *(int *)(param_1 + 0x290)) {
            *(int *)(param_1 + 0x290) = *local_88;
          }
          if (*(int *)(param_1 + 0x28c) < *local_88) {
            *(int *)(param_1 + 0x28c) = *local_88;
          }
          local_8c = local_8c + *local_88;
          local_88 = local_88 + 0x16;
          local_80 = (float)((int)local_80 + 1);
          pfVar16 = pfVar16 + 0x16;
        } while ((int)local_80 < *(int *)(param_1 + 0x49c));
      }
      local_8c = local_8c / *(int *)(param_1 + 0x49c);
      *(int *)(param_1 + 0x294) = local_8c;
      FUN_0050ac20(s_InSection_min__d__max__d__averag_005d14dc,*(undefined4 *)(param_1 + 0x290),
                   *(undefined4 *)(param_1 + 0x28c),local_8c);
      FUN_00509e57(iVar4);
      *(undefined1 *)(param_1 + 0x251) = 1;
      uVar9 = 1;
    }
  }
  ExceptionList = local_c;
  return uVar9;
}

