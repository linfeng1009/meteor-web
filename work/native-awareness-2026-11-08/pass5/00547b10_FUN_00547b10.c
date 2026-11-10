/* Original Meteor.exe static export @ 00547b10; original sample not executed. */
/* XREF 004a825e UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_00547b10(int param_1,int param_2,float param_3,float param_4,undefined4 param_5,int param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  void *pvVar12;
  undefined4 *puVar13;
  float *pfVar14;
  undefined4 uVar15;
  int iVar16;
  int *piVar17;
  float *pfVar18;
  int iVar19;
  undefined4 *puVar20;
  int iVar21;
  int local_90;
  int local_84;
  float *local_80;
  int *local_78;
  int local_6c;
  int local_68;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if ((1 < param_1) && (param_3 * param_4 != (float)_DAT_005a84b8)) {
    param_2 = param_2 + -1;
    iVar19 = (param_1 * 2 + -2) * param_2;
    local_c = 0x3ecccccd;
    local_8 = 0x3ecccccd;
    local_4 = 0x3ecccccd;
    local_24 = 0x3e4ccccd;
    local_20 = 0x3e4ccccd;
    local_1c = 0x3e4ccccd;
    local_18 = 0x3dcccccd;
    local_14 = 0x3dcccccd;
    local_10 = 0x3dcccccd;
    local_30 = 0x3e4ccccd;
    local_2c = 0x3e4ccccd;
    local_28 = 0x3e4ccccd;
    pvVar12 = operator_new(iVar19 * 0x18);
    puVar13 = operator_new(iVar19 * 0x60);
    puVar20 = puVar13;
    for (iVar16 = (iVar19 * 3 & 0x7ffffffU) << 3; iVar16 != 0; iVar16 = iVar16 + -1) {
      *puVar20 = 0;
      puVar20 = puVar20 + 1;
    }
    for (iVar16 = 0; iVar16 != 0; iVar16 = iVar16 + -1) {
      *(undefined1 *)puVar20 = 0;
      puVar20 = (undefined4 *)((int)puVar20 + 1);
    }
    if (param_6 == 0) {
      local_68 = FUN_0040ed80(&local_c,&local_24,&local_18,&local_30,0x42000000,param_5,0);
    }
    else {
      local_68 = FUN_00410e20(&local_c,&local_24,&local_18,&local_30,0x42000000,param_5,0x80,0x80,0,
                              0,0,0);
      FUN_00410d60(local_68);
    }
    FUN_004059e0(6);
    param_1 = param_1 + -1;
    local_6c = 0;
    if (0 < param_1) {
      local_80 = (float *)(puVar13 + 6);
      local_78 = (int *)((int)pvVar12 + 0x10);
      local_84 = 2;
      do {
        local_90 = 0;
        if (0 < param_2) {
          fVar8 = (float)local_6c;
          fVar6 = (float)param_1;
          fVar5 = fVar8 + _DAT_005a83f4;
          fVar9 = (float)(local_6c + 1) * (param_3 / (float)param_1) - param_3 * _DAT_005a83e8;
          fVar7 = (float)(local_6c + 1) / fVar6;
          fVar10 = fVar8 * (param_3 / (float)param_1) - param_3 * _DAT_005a83e8;
          fVar11 = param_4 * _DAT_005a83e8;
          fVar8 = fVar8 / fVar6;
          pfVar14 = local_80;
          piVar17 = local_78;
          iVar16 = local_84;
          do {
            fVar1 = (float)local_90;
            local_90 = local_90 + 1;
            pfVar14[0x12] = fVar9;
            pfVar14[0x18] = fVar7;
            fVar2 = fVar1 * (param_4 / (float)param_2) - fVar11;
            pfVar14[0x1a] = fVar9;
            pfVar14[-6] = fVar10;
            pfVar14[2] = fVar9;
            pfVar14[-5] = fVar2;
            pfVar14[8] = fVar5 / fVar6;
            *pfVar14 = fVar8;
            fVar1 = fVar1 / (float)param_2;
            pfVar14[10] = fVar10;
            pfVar14[1] = fVar1;
            pfVar14[3] = fVar2;
            pfVar14[9] = fVar1;
            fVar4 = (param_4 / (float)param_2) * (float)local_90 - fVar11;
            pfVar14[0xb] = fVar4;
            pfVar14[0x10] = fVar8;
            pfVar14[0x1b] = fVar4;
            fVar3 = (float)local_90 / (float)param_2;
            pfVar14[0x20] = fVar7;
            pfVar14[0x11] = fVar3;
            pfVar14[0x13] = fVar2;
            pfVar14[0x21] = fVar3;
            pfVar14[0x19] = fVar1;
            pfVar14[0x22] = fVar10;
            pfVar14[0x23] = fVar4;
            pfVar14[0x29] = fVar3;
            pfVar18 = pfVar14 + -1;
            pfVar14[0x28] = fVar8;
            iVar21 = 6;
            do {
              pfVar18[-3] = 0.2;
              *pfVar18 = 1.0;
              pfVar18 = pfVar18 + 8;
              iVar21 = iVar21 + -1;
            } while (iVar21 != 0);
            iVar21 = 2;
            do {
              piVar17[1] = iVar16;
              piVar17[-1] = iVar16 + -2;
              *piVar17 = iVar16 + -1;
              piVar17[-4] = 1;
              piVar17[-3] = local_68;
              piVar17[-2] = 0;
              iVar16 = iVar16 + 3;
              piVar17 = piVar17 + 6;
              iVar21 = iVar21 + -1;
            } while (iVar21 != 0);
            pfVar14 = pfVar14 + 0x30;
          } while (local_90 < param_2);
        }
        local_84 = local_84 + param_1 * 6;
        local_6c = local_6c + 1;
        local_78 = local_78 + param_1 * 0xc;
        local_80 = local_80 + param_1 * 0x30;
      } while (local_6c < param_1);
    }
    FUN_0040c900(0,puVar13,iVar19 * 3,pvVar12,iVar19 * 6,iVar19,0);
    uVar15 = FUN_00405df0(0);
    FUN_00507850(pvVar12);
    FUN_00507850(puVar13);
    return uVar15;
  }
  return 0;
}

