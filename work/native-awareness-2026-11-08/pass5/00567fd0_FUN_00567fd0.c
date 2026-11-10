/* Original Meteor.exe static export @ 00567fd0; original sample not executed. */
/* XREF 00568ccd UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00567fd0(int param_1,int param_2,undefined4 *param_3,char param_4)

{
  int *piVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float fVar7;
  undefined4 uVar8;
  int iVar9;
  float fVar10;
  undefined4 *puVar11;
  int iVar12;
  int *piVar13;
  float *pfVar14;
  undefined4 *puVar15;
  undefined4 *local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  undefined1 local_58;
  undefined1 uStack_57;
  undefined1 uStack_56;
  byte bStack_55;
  undefined1 local_54;
  undefined1 uStack_53;
  undefined1 uStack_52;
  undefined1 uStack_51;
  float local_50;
  float local_44;
  undefined1 local_40 [64];
  
  iVar9 = (int)param_3;
  uVar8 = param_2;
  pfVar2 = (float *)((int)param_3 + 0x220);
  *(undefined4 *)((int)param_3 + 0x228) = 0x501502f9;
  *(undefined4 *)((int)param_3 + 0x224) = 0x501502f9;
  *pfVar2 = 1e+10;
  *(undefined4 *)((int)param_3 + 0x234) = 0xd01502f9;
  *(undefined4 *)((int)param_3 + 0x230) = 0xd01502f9;
  *(undefined4 *)((int)param_3 + 0x22c) = 0xd01502f9;
  pfVar14 = (float *)(*(int *)(*(int *)(param_1 + 0x120) + 0xd8) +
                     *(int *)((int)param_3 + 0x20c) * 0x24);
  puVar11 = (undefined4 *)
            (*(int *)(*(int *)(param_1 + 0x120) + 0xd4) + *(int *)((int)param_3 + 0x210) * 0x54);
  if (param_4 == '\0') {
    FUN_0050b600(param_2,s__s__s_005d12a8,local_40,(int)param_3 + 8);
    FUN_00480830(param_2,1);
    FUN_0050b600(param_2,s__s__d__s__d_005d12d0,local_40,(int)param_3 + 0x208,local_40,
                 (int)param_3 + 0x204);
  }
  else {
    FUN_00567c80(param_2,(int)param_3 + 8);
    FUN_0050a118((int)param_3 + 0x208,4,1,param_2);
    FUN_0050a118((int)param_3 + 0x204,4,1,param_2);
  }
  param_2 = 0;
  if (0 < *(int *)((int)param_3 + 0x208)) {
    do {
      if (param_4 == '\0') {
        FUN_0050b600(uVar8,s__s__f__f__f__s__f__f__f__s__d__d_005d16ec,local_40,pfVar14,pfVar14 + 1,
                     pfVar14 + 2,local_40,pfVar14 + 3,pfVar14 + 4,pfVar14 + 5,local_40,&local_68,
                     &local_64,&local_5c,&local_60,local_40,pfVar14 + 7,pfVar14 + 8);
      }
      else {
        FUN_0050a118(pfVar14,4,3,uVar8);
        FUN_0050a118(pfVar14 + 3,4,3,uVar8);
        FUN_0050a118(&local_58,1,4,uVar8);
        FUN_0050a118(pfVar14 + 7,4,2,uVar8);
        local_5c = CONCAT11(bStack_55,uStack_56) & 0xff;
        local_60 = (uint)bStack_55;
        local_68 = (undefined4 *)(CONCAT12(uStack_56,CONCAT11(uStack_57,local_58)) & 0xff);
        local_64 = CONCAT12(bStack_55,CONCAT11(uStack_56,uStack_57)) & 0xff;
      }
      fVar10 = (float)FUN_00475c50(local_68,local_64,local_5c,local_60);
      pfVar14[6] = fVar10;
      if (*pfVar14 < *pfVar2) {
        *pfVar2 = *pfVar14;
      }
      if (pfVar14[1] < *(float *)((int)param_3 + 0x224)) {
        *(float *)((int)param_3 + 0x224) = pfVar14[1];
      }
      if (pfVar14[2] < *(float *)((int)param_3 + 0x228)) {
        *(float *)((int)param_3 + 0x228) = pfVar14[2];
      }
      if (*(float *)((int)param_3 + 0x22c) < *pfVar14) {
        *(float *)((int)param_3 + 0x22c) = *pfVar14;
      }
      if (*(float *)((int)param_3 + 0x230) < pfVar14[1]) {
        *(float *)((int)param_3 + 0x230) = pfVar14[1];
      }
      if (*(float *)((int)param_3 + 0x234) < pfVar14[2]) {
        *(float *)((int)param_3 + 0x234) = pfVar14[2];
      }
      param_2 = param_2 + 1;
      pfVar14 = pfVar14 + 9;
    } while (param_2 < *(int *)((int)param_3 + 0x208));
  }
  local_44 = *(float *)((int)param_3 + 0x228) + *(float *)((int)param_3 + 0x234);
  pfVar14 = (float *)((int)param_3 + 0x238);
  fVar10 = (*(float *)((int)param_3 + 0x224) + *(float *)((int)param_3 + 0x230)) * _DAT_005a83e8;
  *(float *)((int)param_3 + 0x244) = (*pfVar2 + *(float *)((int)param_3 + 0x22c)) * _DAT_005a83e8;
  fVar7 = local_44 * _DAT_005a83e8;
  *(float *)((int)param_3 + 0x248) = fVar10;
  *(float *)((int)param_3 + 0x24c) = fVar7;
  *pfVar14 = *(float *)((int)param_3 + 0x22c) - *pfVar2;
  *(float *)((int)param_3 + 0x23c) =
       *(float *)((int)param_3 + 0x230) - *(float *)((int)param_3 + 0x224);
  *(float *)((int)param_3 + 0x240) =
       *(float *)((int)param_3 + 0x234) - *(float *)((int)param_3 + 0x228);
  fVar10 = *pfVar14 * _DAT_005a83e8;
  local_58 = SUB41(fVar10,0);
  uStack_57 = (undefined1)((uint)fVar10 >> 8);
  uStack_56 = (undefined1)((uint)fVar10 >> 0x10);
  bStack_55 = (byte)((uint)fVar10 >> 0x18);
  fVar7 = *(float *)((int)param_3 + 0x23c) * _DAT_005a83e8;
  local_54 = SUB41(fVar7,0);
  uStack_53 = (undefined1)((uint)fVar7 >> 8);
  uStack_52 = (undefined1)((uint)fVar7 >> 0x10);
  uStack_51 = (undefined1)((uint)fVar7 >> 0x18);
  local_50 = *(float *)((int)param_3 + 0x240) * _DAT_005a83e8;
  *(float *)((int)param_3 + 0x198) = fVar10;
  *(float *)((int)param_3 + 0x19c) = fVar7;
  *(float *)((int)param_3 + 0x1a0) = local_50;
  FUN_00477200();
  FUN_00477b90(3,(int)param_3 + 0x244);
  local_44 = *(float *)((int)param_3 + 0x240);
  pfVar3 = (float *)((int)param_3 + 0x250);
  *pfVar3 = *pfVar2;
  *(undefined4 *)((int)param_3 + 0x254) = *(undefined4 *)((int)param_3 + 0x224);
  *(undefined4 *)((int)param_3 + 600) = *(undefined4 *)((int)param_3 + 0x228);
  pfVar4 = (float *)((int)param_3 + 0x25c);
  *pfVar4 = *pfVar14 + *pfVar2;
  *(undefined4 *)((int)param_3 + 0x260) = *(undefined4 *)((int)param_3 + 0x224);
  *(undefined4 *)((int)param_3 + 0x264) = *(undefined4 *)((int)param_3 + 0x228);
  *(float *)((int)param_3 + 0x268) = *pfVar4;
  *(float *)((int)param_3 + 0x26c) =
       *(float *)((int)param_3 + 0x23c) + *(float *)((int)param_3 + 0x260);
  *(undefined4 *)((int)param_3 + 0x270) = *(undefined4 *)((int)param_3 + 0x264);
  *(float *)((int)param_3 + 0x274) = *pfVar3;
  *(float *)((int)param_3 + 0x278) =
       *(float *)((int)param_3 + 0x23c) + *(float *)((int)param_3 + 0x254);
  *(undefined4 *)((int)param_3 + 0x27c) = *(undefined4 *)((int)param_3 + 600);
  *(float *)((int)param_3 + 0x280) = *pfVar3;
  *(undefined4 *)((int)param_3 + 0x284) = *(undefined4 *)((int)param_3 + 0x254);
  *(float *)((int)param_3 + 0x288) = local_44 + *(float *)((int)param_3 + 600);
  *(float *)((int)param_3 + 0x28c) = *pfVar4;
  *(undefined4 *)((int)param_3 + 0x290) = *(undefined4 *)((int)param_3 + 0x260);
  *(float *)((int)param_3 + 0x294) = local_44 + *(float *)((int)param_3 + 0x264);
  *(undefined4 *)((int)param_3 + 0x298) = *(undefined4 *)((int)param_3 + 0x268);
  *(undefined4 *)((int)param_3 + 0x29c) = *(undefined4 *)((int)param_3 + 0x26c);
  *(float *)((int)param_3 + 0x2a0) = local_44 + *(float *)((int)param_3 + 0x270);
  uVar5 = *(undefined4 *)((int)param_3 + 0x274);
  uVar6 = *(undefined4 *)((int)param_3 + 0x278);
  local_58 = (undefined1)uVar5;
  uStack_57 = (undefined1)((uint)uVar5 >> 8);
  uStack_56 = (undefined1)((uint)uVar5 >> 0x10);
  bStack_55 = (byte)((uint)uVar5 >> 0x18);
  local_50 = local_44 + *(float *)((int)param_3 + 0x27c);
  local_54 = (undefined1)uVar6;
  uStack_53 = (undefined1)((uint)uVar6 >> 8);
  uStack_52 = (undefined1)((uint)uVar6 >> 0x10);
  uStack_51 = (undefined1)((uint)uVar6 >> 0x18);
  *(undefined4 *)((int)param_3 + 0x2a4) = uVar5;
  *(undefined4 *)((int)param_3 + 0x2a8) = uVar6;
  *(float *)((int)param_3 + 0x2ac) = local_50;
  if (*pfVar2 < *(float *)(*(int *)(param_1 + 0x120) + 0x4c)) {
    *(float *)(*(int *)(param_1 + 0x120) + 0x4c) = *pfVar2;
  }
  if (*(float *)((int)param_3 + 0x224) < *(float *)(*(int *)(param_1 + 0x120) + 0x50)) {
    *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x50) = *(undefined4 *)((int)param_3 + 0x224);
  }
  if (*(float *)((int)param_3 + 0x228) < *(float *)(*(int *)(param_1 + 0x120) + 0x54)) {
    *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x54) = *(undefined4 *)((int)param_3 + 0x228);
  }
  if (*(float *)(*(int *)(param_1 + 0x120) + 0x58) < *(float *)((int)param_3 + 0x22c)) {
    *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x58) = *(undefined4 *)((int)param_3 + 0x22c);
  }
  if (*(float *)(*(int *)(param_1 + 0x120) + 0x5c) < *(float *)((int)param_3 + 0x230)) {
    *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x5c) = *(undefined4 *)((int)param_3 + 0x230);
  }
  if (*(float *)(*(int *)(param_1 + 0x120) + 0x60) < *(float *)((int)param_3 + 0x234)) {
    *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x60) = *(undefined4 *)((int)param_3 + 0x234);
  }
  param_2 = 0;
  if (0 < *(int *)((int)param_3 + 0x204)) {
    puVar15 = puVar11 + 0x10;
    param_3 = puVar11;
    do {
      piVar1 = puVar15 + -0xe;
      if (param_4 == '\0') {
        FUN_0050b600(uVar8,s__s__d__d__d__d__f__f__f_005d16d0,local_40,piVar1,&local_5c,&local_60,
                     &local_64,puVar15,puVar15 + 1,puVar15 + 2);
      }
      else {
        FUN_0050a118(piVar1,4,1,uVar8);
        FUN_0050a118(&local_5c,4,1,uVar8);
        FUN_0050a118(&local_60,4,1,uVar8);
        FUN_0050a118(&local_64,4,1,uVar8);
        FUN_0050a118(puVar15,4,3,uVar8);
      }
      uVar5 = *(undefined4 *)(iVar9 + 4);
      puVar15[-0xf] = iVar9;
      local_58 = 3;
      uStack_57 = 0;
      uStack_56 = 0;
      bStack_55 = 0;
      *param_3 = uVar5;
      piVar13 = puVar15 + -0xc;
      puVar15[-0xd] = *(int *)(*(int *)(param_1 + 0x120) + 0x104) + *piVar1 * 0x28;
      *piVar13 = *(int *)(iVar9 + 0x20c) + local_5c;
      local_68 = puVar15 + -9;
      puVar15[-0xb] = *(int *)(iVar9 + 0x20c) + local_60;
      puVar15[-10] = *(int *)(iVar9 + 0x20c) + local_64;
      do {
        puVar11 = (undefined4 *)FUN_0056af20(*piVar13);
        piVar13 = piVar13 + 1;
        *local_68 = *puVar11;
        local_68[1] = puVar11[1];
        local_68[2] = puVar11[2];
        local_68 = local_68 + 3;
        iVar12 = CONCAT13(bStack_55,CONCAT12(uStack_56,CONCAT11(uStack_57,local_58))) + -1;
        local_58 = (undefined1)iVar12;
        uStack_57 = (undefined1)((uint)iVar12 >> 8);
        uStack_56 = (undefined1)((uint)iVar12 >> 0x10);
        bStack_55 = (byte)((uint)iVar12 >> 0x18);
      } while (iVar12 != 0);
      param_2 = param_2 + 1;
      param_3 = param_3 + 0x15;
      puVar15 = puVar15 + 0x15;
    } while (param_2 < *(int *)(iVar9 + 0x204));
  }
  if (param_4 == '\0') {
    FUN_00480830(uVar8,1);
  }
  return 1;
}

