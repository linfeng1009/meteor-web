/* Original Meteor.exe static export @ 0040d3b0; original sample not executed. */
/* XREF 0040ccd0 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040d3b0(int param_1,float param_2,int param_3,undefined4 *param_4,int param_5,int param_6,
                 uint param_7,undefined4 param_8,int param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  int local_20;
  undefined4 *local_1c;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  fVar5 = param_2;
  iVar6 = DAT_007eac64;
  if (param_9 != 0) {
    fVar1 = (float)*(int *)((int)param_2 + 0x18);
    pfVar9 = *(float **)(param_1 + 0xa0);
    local_30 = 1e+20;
    param_2 = 1e+20;
    local_2c = -1e+20;
    local_18 = fVar1 * *pfVar9;
    local_34 = -1e+20;
    local_28 = 1e+20;
    local_24 = -1e+20;
    local_14 = fVar1 * pfVar9[1];
    local_10 = fVar1 * pfVar9[2];
  }
  local_20 = 0;
  if (0 < param_6) {
    local_1c = param_4;
    pfVar9 = (float *)(param_3 + 8);
    pfVar10 = pfVar9;
    do {
      *(float *)(*(int *)((int)fVar5 + 0x1c) + *(int *)((int)fVar5 + 0x18) * iVar6 * 4) =
           pfVar10[-2];
      *(float *)(*(int *)((int)fVar5 + 0x1c) + 4 + *(int *)((int)fVar5 + 0x18) * iVar6 * 4) =
           pfVar10[-1];
      *(float *)(*(int *)((int)fVar5 + 0x1c) + 8 + *(int *)((int)fVar5 + 0x18) * iVar6 * 4) =
           *pfVar10;
      *(float *)(*(int *)((int)fVar5 + 0x1c) + 0xc + *(int *)((int)fVar5 + 0x18) * iVar6 * 4) =
           pfVar10[1];
      puVar7 = local_1c;
      if (param_4 == (undefined4 *)0x0) {
        local_c = 0x3f800000;
        local_8 = 0x3f800000;
        local_4 = 0x3f800000;
        puVar7 = &local_c;
      }
      FUN_00419ce0(*(int *)((int)fVar5 + 0x1c) + *(int *)((int)fVar5 + 0x18) * iVar6 * 4,puVar7,
                   *(undefined4 *)(param_1 + 0x114),1,iVar6);
      iVar8 = *(int *)((int)fVar5 + 0x18) * iVar6;
      if (param_5 == 0) {
        *(undefined4 *)(*(int *)((int)fVar5 + 0x1c) + 0x18 + iVar8 * 4) = 0;
        *(undefined4 *)
         (*(int *)((int)fVar5 + 0x1c) + 0x1c + *(int *)((int)fVar5 + 0x18) * iVar6 * 4) = 0;
      }
      else {
        *(undefined4 *)(*(int *)((int)fVar5 + 0x1c) + 0x18 + iVar8 * 4) =
             *(undefined4 *)(param_5 + local_20 * 8);
        *(undefined4 *)
         (*(int *)((int)fVar5 + 0x1c) + 0x1c + *(int *)((int)fVar5 + 0x18) * iVar6 * 4) =
             *(undefined4 *)(param_5 + 4 + local_20 * 8);
      }
      if (param_9 != 0) {
        if (pfVar9[-2] < param_2) {
          param_2 = pfVar9[-2];
        }
        if (local_34 <= pfVar9[-2]) {
          local_34 = pfVar9[-2];
        }
        if (pfVar9[-1] < local_30) {
          local_30 = pfVar9[-1];
        }
        if (local_2c <= pfVar9[-1]) {
          local_2c = pfVar9[-1];
        }
        if (*pfVar9 < local_28) {
          local_28 = *pfVar9;
        }
        if (local_24 <= *pfVar9) {
          local_24 = *pfVar9;
        }
        local_18 = local_18 + pfVar9[-2];
        local_14 = local_14 + pfVar9[-1];
        local_10 = local_10 + *pfVar9;
      }
      local_1c = local_1c + 3;
      local_20 = local_20 + 1;
      pfVar10 = pfVar10 + 4;
      pfVar9 = pfVar9 + 3;
      *(int *)((int)fVar5 + 0x18) = *(int *)((int)fVar5 + 0x18) + 1;
    } while (local_20 < param_6);
  }
  if (param_9 != 0) {
    iVar6 = *(int *)(param_1 + 0xa0);
    if (*(float *)(iVar6 + 0x10) < param_2) {
      param_2 = *(float *)(iVar6 + 0x10);
    }
    *(float *)(iVar6 + 0x10) = param_2;
    iVar6 = *(int *)(param_1 + 0xa0);
    if (local_34 <= *(float *)(iVar6 + 0x14)) {
      local_34 = *(float *)(iVar6 + 0x14);
    }
    *(float *)(iVar6 + 0x14) = local_34;
    iVar6 = *(int *)(param_1 + 0xa0);
    if (*(float *)(iVar6 + 0x18) < local_30) {
      local_30 = *(float *)(iVar6 + 0x18);
    }
    *(float *)(iVar6 + 0x18) = local_30;
    iVar6 = *(int *)(param_1 + 0xa0);
    if (local_2c <= *(float *)(iVar6 + 0x1c)) {
      local_2c = *(float *)(iVar6 + 0x1c);
    }
    *(float *)(iVar6 + 0x1c) = local_2c;
    iVar6 = *(int *)(param_1 + 0xa0);
    if (*(float *)(iVar6 + 0x20) < local_28) {
      local_28 = *(float *)(iVar6 + 0x20);
    }
    *(float *)(iVar6 + 0x20) = local_28;
    iVar6 = *(int *)(param_1 + 0xa0);
    if (local_24 <= *(float *)(iVar6 + 0x24)) {
      local_24 = *(float *)(iVar6 + 0x24);
    }
    *(float *)(iVar6 + 0x24) = local_24;
    **(float **)(param_1 + 0xa0) = local_18 / (float)*(int *)((int)fVar5 + 0x18);
    *(float *)(*(int *)(param_1 + 0xa0) + 4) = local_14 / (float)*(int *)((int)fVar5 + 0x18);
    *(float *)(*(int *)(param_1 + 0xa0) + 8) = local_10 / (float)*(int *)((int)fVar5 + 0x18);
    iVar6 = *(int *)(param_1 + 0xa0);
    fVar1 = *(float *)(iVar6 + 0x1c) - *(float *)(iVar6 + 0x18);
    fVar4 = *(float *)(iVar6 + 0x24) - *(float *)(iVar6 + 0x20);
    fVar3 = fVar4;
    if (fVar4 < fVar1) {
      fVar3 = fVar1;
    }
    fVar2 = *(float *)(iVar6 + 0x14) - *(float *)(iVar6 + 0x10);
    if ((fVar2 <= fVar3) && (fVar2 = fVar1, fVar1 <= fVar4)) {
      fVar2 = fVar4;
    }
    *(float *)(iVar6 + 0xc) = fVar2;
    *(float *)(*(int *)(param_1 + 0xa0) + 0xc) =
         *(float *)(*(int *)(param_1 + 0xa0) + 0xc) * _DAT_005a83e8;
    fVar1 = *(float *)(*(int *)(param_1 + 0xa0) + 0xc);
    *(float *)(*(int *)(param_1 + 0xa0) + 0xc) = fVar1 * fVar1;
  }
  iVar6 = 0;
  if (0 < param_6 + -2) {
    do {
      *(undefined4 *)(*(int *)((int)fVar5 + 0x40) + *(int *)((int)fVar5 + 0x3c) * 4) = 1;
      iVar8 = *(int *)((int)fVar5 + 0x3c) + 1;
      *(int *)((int)fVar5 + 0x3c) = iVar8;
      if ((param_7 == 0xffffffff) || (param_7 == 0)) {
        *(undefined4 *)(*(int *)((int)fVar5 + 0x40) + iVar8 * 4) = 0xffffffff;
      }
      else {
        *(uint *)(*(int *)((int)fVar5 + 0x40) + iVar8 * 4) = param_7 & 0xffffff;
      }
      iVar8 = *(int *)((int)fVar5 + 0x3c) + 1;
      *(int *)((int)fVar5 + 0x3c) = iVar8;
      *(undefined4 *)(*(int *)((int)fVar5 + 0x40) + iVar8 * 4) = param_8;
      iVar8 = *(int *)((int)fVar5 + 0x3c) + 1;
      *(int *)((int)fVar5 + 0x3c) = iVar8;
      *(int *)(*(int *)((int)fVar5 + 0x40) + iVar8 * 4) = *(int *)((int)fVar5 + 0x18) - param_6;
      iVar8 = *(int *)((int)fVar5 + 0x3c) + 1;
      *(int *)((int)fVar5 + 0x3c) = iVar8;
      *(int *)(*(int *)((int)fVar5 + 0x40) + iVar8 * 4) =
           (iVar6 - param_6) + 1 + *(int *)((int)fVar5 + 0x18);
      iVar8 = *(int *)((int)fVar5 + 0x3c) + 1;
      *(int *)((int)fVar5 + 0x3c) = iVar8;
      *(int *)(*(int *)((int)fVar5 + 0x40) + iVar8 * 4) =
           (iVar6 - param_6) + 2 + *(int *)((int)fVar5 + 0x18);
      iVar6 = iVar6 + 1;
      *(int *)((int)fVar5 + 0x3c) = *(int *)((int)fVar5 + 0x3c) + 1;
      *(int *)((int)fVar5 + 0x34) = *(int *)((int)fVar5 + 0x34) + 1;
    } while (iVar6 < param_6 + -2);
  }
  *(undefined4 *)((int)fVar5 + 0x38) = *(undefined4 *)((int)fVar5 + 0x34);
  if (*(int *)((int)fVar5 + 8) != -1) {
    if (*(int *)((int)fVar5 + 8) == 1) {
      *(undefined4 *)((int)fVar5 + 8) = 2;
    }
    return;
  }
  *(undefined4 *)((int)fVar5 + 8) = 0;
  return;
}

