/* Original Meteor.exe static export @ 0040cd10; original sample not executed. */
/* XREF 0040ccf9 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040cd10(int param_1,int param_2,float *param_3,undefined4 *param_4,int param_5,int param_6
                 ,uint param_7,undefined4 param_8,int param_9)

{
  float fVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  float *pfVar10;
  float *pfVar11;
  float local_458;
  float local_454;
  float local_450;
  float local_44c;
  int local_448;
  float local_444;
  float local_440;
  int local_43c;
  undefined4 *local_438;
  float local_434;
  float local_430;
  float local_42c;
  float local_424;
  float local_420;
  float local_41c;
  float local_418;
  float local_414;
  float local_410;
  undefined4 local_40c;
  undefined4 local_408;
  undefined4 local_404;
  int aiStack_400 [256];
  
  iVar8 = 0;
  local_43c = 0;
  bVar2 = true;
  if (0 < param_6) {
    do {
      if (iVar8 == 0) {
        pfVar6 = param_3 + param_6 * 3 + -3;
        pfVar10 = param_3;
        pfVar11 = param_3 + 3;
      }
      else if (iVar8 == param_6 + -1) {
        pfVar10 = param_3 + param_6 * 3 + -3;
        pfVar6 = param_3 + param_6 * 3 + -6;
        pfVar11 = param_3;
      }
      else {
        pfVar10 = param_3 + iVar8 * 3;
        pfVar11 = param_3 + iVar8 * 3 + 3;
        pfVar6 = pfVar10 + -3;
      }
      fVar9 = (float10)FUN_00431ed0(pfVar6,pfVar10,pfVar11);
      if (fVar9 <= (float10)_DAT_005a83e4) {
        fVar9 = -fVar9;
      }
      if (fVar9 <= (float10)_DAT_005a842c) {
        aiStack_400[iVar8] = 0;
      }
      else {
        if (bVar2) {
          if (iVar8 == 0) {
            local_424 = param_3[param_6 * 3 + -3] - *param_3;
            local_420 = param_3[param_6 * 3 + -2] - param_3[1];
            local_41c = param_3[param_6 * 3 + -1] - param_3[2];
          }
          else {
            local_424 = param_3[iVar8 * 3 + -3] - param_3[iVar8 * 3];
            local_420 = param_3[iVar8 * 3 + -2] - param_3[iVar8 * 3 + 1];
            local_41c = param_3[iVar8 * 3 + -1] - param_3[iVar8 * 3 + 2];
          }
          if (iVar8 == param_6 + -1) {
            local_418 = *param_3 - param_3[iVar8 * 3];
            pfVar6 = param_3 + iVar8 * 3;
            local_414 = param_3[1] - pfVar6[1];
            local_410 = param_3[2];
          }
          else {
            local_418 = param_3[iVar8 * 3 + 3] - param_3[iVar8 * 3];
            pfVar6 = param_3 + iVar8 * 3;
            local_414 = pfVar6[4] - pfVar6[1];
            local_410 = pfVar6[5];
          }
          local_410 = local_410 - pfVar6[2];
          FUN_00430e80(&local_40c,&local_418,&local_424);
          bVar2 = false;
        }
        aiStack_400[iVar8] = 1;
        local_43c = local_43c + 1;
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < param_6);
  }
  iVar8 = DAT_007eac64;
  if (param_9 != 0) {
    local_44c = 1e+20;
    fVar1 = (float)*(int *)(param_2 + 0x18);
    pfVar6 = *(float **)(param_1 + 0xa0);
    local_454 = 1e+20;
    local_444 = 1e+20;
    local_458 = -1e+20;
    local_434 = fVar1 * *pfVar6;
    local_450 = -1e+20;
    local_440 = -1e+20;
    local_430 = fVar1 * pfVar6[1];
    local_42c = fVar1 * pfVar6[2];
  }
  local_448 = 0;
  if (0 < param_6) {
    pfVar6 = param_3 + 2;
    local_438 = param_4;
    do {
      if (aiStack_400[local_448] != 0) {
        *(float *)(*(int *)(param_2 + 0x1c) + *(int *)(param_2 + 0x18) * iVar8 * 4) = pfVar6[-2];
        *(float *)(*(int *)(param_2 + 0x1c) + 4 + *(int *)(param_2 + 0x18) * iVar8 * 4) = pfVar6[-1]
        ;
        *(float *)(*(int *)(param_2 + 0x1c) + 8 + *(int *)(param_2 + 0x18) * iVar8 * 4) = *pfVar6;
        if (param_4 == (undefined4 *)0x0) {
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0xc + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               local_40c;
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x10 + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               local_408;
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x14 + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               local_404;
        }
        else {
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0xc + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               *local_438;
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x10 + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               *(undefined4 *)((int)pfVar6 + ((int)param_4 - (int)param_3) + -4);
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x14 + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               *(undefined4 *)((int)pfVar6 + ((int)param_4 - (int)param_3));
          if ((*(byte *)(param_2 + 4) & 1) != 0) {
            FUN_00419c30(*(int *)(param_2 + 0x1c) + *(int *)(param_2 + 0x18) * iVar8 * 4,
                         *(undefined4 *)(param_1 + 0x114),1,iVar8);
          }
        }
        if (param_5 == 0) {
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x18 + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               0;
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x1c + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               0;
        }
        else {
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x18 + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               *(undefined4 *)(param_5 + local_448 * 8);
          *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x1c + *(int *)(param_2 + 0x18) * iVar8 * 4) =
               *(undefined4 *)(param_5 + 4 + local_448 * 8);
        }
        if (param_9 != 0) {
          if (pfVar6[-2] < local_444) {
            local_444 = pfVar6[-2];
          }
          if (local_440 <= pfVar6[-2]) {
            local_440 = pfVar6[-2];
          }
          if (pfVar6[-1] < local_454) {
            local_454 = pfVar6[-1];
          }
          if (local_450 <= pfVar6[-1]) {
            local_450 = pfVar6[-1];
          }
          if (*pfVar6 < local_44c) {
            local_44c = *pfVar6;
          }
          if (local_458 <= *pfVar6) {
            local_458 = *pfVar6;
          }
          local_434 = local_434 + pfVar6[-2];
          local_430 = local_430 + pfVar6[-1];
          local_42c = local_42c + *pfVar6;
        }
        *(int *)(param_2 + 0x18) = *(int *)(param_2 + 0x18) + 1;
      }
      local_448 = local_448 + 1;
      local_438 = local_438 + 3;
      pfVar6 = pfVar6 + 3;
    } while (local_448 < param_6);
  }
  if (param_9 != 0) {
    iVar8 = *(int *)(param_1 + 0xa0);
    if (*(float *)(iVar8 + 0x10) < local_444) {
      local_444 = *(float *)(iVar8 + 0x10);
    }
    *(float *)(iVar8 + 0x10) = local_444;
    iVar8 = *(int *)(param_1 + 0xa0);
    if (local_440 <= *(float *)(iVar8 + 0x14)) {
      local_440 = *(float *)(iVar8 + 0x14);
    }
    *(float *)(iVar8 + 0x14) = local_440;
    iVar8 = *(int *)(param_1 + 0xa0);
    if (*(float *)(iVar8 + 0x18) < local_454) {
      local_454 = *(float *)(iVar8 + 0x18);
    }
    *(float *)(iVar8 + 0x18) = local_454;
    iVar8 = *(int *)(param_1 + 0xa0);
    if (local_450 <= *(float *)(iVar8 + 0x1c)) {
      local_450 = *(float *)(iVar8 + 0x1c);
    }
    *(float *)(iVar8 + 0x1c) = local_450;
    iVar8 = *(int *)(param_1 + 0xa0);
    if (*(float *)(iVar8 + 0x20) < local_44c) {
      local_44c = *(float *)(iVar8 + 0x20);
    }
    *(float *)(iVar8 + 0x20) = local_44c;
    iVar8 = *(int *)(param_1 + 0xa0);
    if (local_458 <= *(float *)(iVar8 + 0x24)) {
      local_458 = *(float *)(iVar8 + 0x24);
    }
    *(float *)(iVar8 + 0x24) = local_458;
    **(float **)(param_1 + 0xa0) = local_434 / (float)*(int *)(param_2 + 0x18);
    *(float *)(*(int *)(param_1 + 0xa0) + 4) = local_430 / (float)*(int *)(param_2 + 0x18);
    *(float *)(*(int *)(param_1 + 0xa0) + 8) = local_42c / (float)*(int *)(param_2 + 0x18);
    iVar8 = *(int *)(param_1 + 0xa0);
    fVar1 = *(float *)(iVar8 + 0x1c) - *(float *)(iVar8 + 0x18);
    fVar5 = *(float *)(iVar8 + 0x24) - *(float *)(iVar8 + 0x20);
    fVar4 = fVar5;
    if (fVar5 < fVar1) {
      fVar4 = fVar1;
    }
    fVar3 = *(float *)(iVar8 + 0x14) - *(float *)(iVar8 + 0x10);
    if ((fVar3 <= fVar4) && (fVar3 = fVar1, fVar1 <= fVar5)) {
      fVar3 = fVar5;
    }
    *(float *)(iVar8 + 0xc) = fVar3;
    *(float *)(*(int *)(param_1 + 0xa0) + 0xc) =
         *(float *)(*(int *)(param_1 + 0xa0) + 0xc) * _DAT_005a83e8;
    fVar1 = *(float *)(*(int *)(param_1 + 0xa0) + 0xc);
    *(float *)(*(int *)(param_1 + 0xa0) + 0xc) = fVar1 * fVar1;
  }
  iVar8 = 0;
  if (0 < local_43c + -2) {
    do {
      *(undefined4 *)(*(int *)(param_2 + 0x40) + *(int *)(param_2 + 0x3c) * 4) = 1;
      iVar7 = *(int *)(param_2 + 0x3c) + 1;
      *(int *)(param_2 + 0x3c) = iVar7;
      if ((param_7 == 0xffffffff) || (param_7 == 0)) {
        *(undefined4 *)(*(int *)(param_2 + 0x40) + iVar7 * 4) = 0xffffffff;
      }
      else {
        *(uint *)(*(int *)(param_2 + 0x40) + iVar7 * 4) = param_7 & 0xffffff;
      }
      iVar7 = *(int *)(param_2 + 0x3c) + 1;
      *(int *)(param_2 + 0x3c) = iVar7;
      *(undefined4 *)(*(int *)(param_2 + 0x40) + iVar7 * 4) = param_8;
      iVar7 = *(int *)(param_2 + 0x3c) + 1;
      *(int *)(param_2 + 0x3c) = iVar7;
      *(int *)(*(int *)(param_2 + 0x40) + iVar7 * 4) = *(int *)(param_2 + 0x18) - local_43c;
      iVar7 = *(int *)(param_2 + 0x3c) + 1;
      *(int *)(param_2 + 0x3c) = iVar7;
      *(int *)(*(int *)(param_2 + 0x40) + iVar7 * 4) =
           (*(int *)(param_2 + 0x18) - local_43c) + 1 + iVar8;
      iVar7 = *(int *)(param_2 + 0x3c) + 1;
      *(int *)(param_2 + 0x3c) = iVar7;
      *(int *)(*(int *)(param_2 + 0x40) + iVar7 * 4) =
           (*(int *)(param_2 + 0x18) - local_43c) + 2 + iVar8;
      iVar8 = iVar8 + 1;
      *(int *)(param_2 + 0x3c) = *(int *)(param_2 + 0x3c) + 1;
      *(int *)(param_2 + 0x34) = *(int *)(param_2 + 0x34) + 1;
    } while (iVar8 < local_43c + -2);
  }
  *(undefined4 *)(param_2 + 0x38) = *(undefined4 *)(param_2 + 0x34);
  if (*(int *)(param_2 + 8) != -1) {
    if (*(int *)(param_2 + 8) == 1) {
      *(undefined4 *)(param_2 + 8) = 2;
    }
    return;
  }
  *(undefined4 *)(param_2 + 8) = 0;
  return;
}

