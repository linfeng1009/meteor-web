/* Original Meteor.exe static export @ 00431680; original sample not executed. */
/* XREF 00431606 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00431680(float *param_1,int param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  float local_60;
  int local_5c;
  float *local_58;
  float *local_54;
  int local_50;
  int local_4c;
  float local_44 [17];
  
  iVar3 = (int)param_4;
  iVar9 = 0;
  *param_3 = 1.0;
  pfVar5 = param_1;
  if (0 < (int)param_4) {
    do {
      local_60 = 0.0;
      pfVar7 = pfVar5;
      iVar8 = (int)param_4;
      do {
        fVar1 = *pfVar7;
        if (fVar1 <= _DAT_005a83e4) {
          fVar1 = -fVar1;
        }
        if (local_60 < fVar1) {
          local_60 = fVar1;
        }
        pfVar7 = pfVar7 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      iVar9 = iVar9 + 1;
      local_44[iVar9] = _DAT_005a83f4 / local_60;
      pfVar5 = pfVar5 + (int)param_4;
    } while (iVar9 < (int)param_4);
  }
  local_5c = 0;
  if (0 < (int)param_4) {
    local_50 = (int)param_4;
    param_4 = param_1;
    local_54 = param_1;
    local_58 = param_1;
    do {
      iVar9 = 0;
      pfVar5 = param_1;
      pfVar7 = param_4;
      if (0 < local_5c) {
        do {
          fVar1 = *pfVar7;
          pfVar4 = pfVar5;
          pfVar6 = param_4;
          iVar8 = iVar9;
          if (0 < iVar9) {
            do {
              iVar8 = iVar8 + -1;
              fVar1 = fVar1 - *pfVar6 * *pfVar4;
              pfVar4 = pfVar4 + 1;
              pfVar6 = pfVar6 + iVar3;
            } while (iVar8 != 0);
          }
          iVar9 = iVar9 + 1;
          *pfVar7 = fVar1;
          pfVar5 = pfVar5 + iVar3;
          pfVar7 = pfVar7 + iVar3;
        } while (iVar9 < local_5c);
      }
      local_60 = 0.0;
      fVar1 = _DAT_005a83e4;
      pfVar5 = local_58;
      pfVar7 = local_54;
      for (iVar9 = local_5c; _DAT_005a83e4 = fVar1, iVar9 < iVar3; iVar9 = iVar9 + 1) {
        fVar2 = *pfVar7;
        pfVar4 = pfVar5;
        pfVar6 = param_4;
        iVar8 = local_5c;
        if (0 < local_5c) {
          do {
            iVar8 = iVar8 + -1;
            fVar2 = fVar2 - *pfVar4 * *pfVar6;
            pfVar4 = pfVar4 + 1;
            pfVar6 = pfVar6 + iVar3;
          } while (iVar8 != 0);
        }
        *pfVar7 = fVar2;
        if (fVar2 <= fVar1) {
          fVar2 = -fVar2;
        }
        if (local_60 <= fVar2 * local_44[iVar9 + 1]) {
          local_60 = fVar2 * local_44[iVar9 + 1];
          local_4c = iVar9;
        }
        pfVar5 = pfVar5 + iVar3;
        pfVar7 = pfVar7 + iVar3;
        fVar1 = _DAT_005a83e4;
      }
      if (local_5c != local_4c) {
        pfVar5 = param_1 + local_4c * iVar3;
        pfVar7 = local_58;
        iVar9 = iVar3;
        do {
          fVar1 = *pfVar5;
          *pfVar5 = *pfVar7;
          pfVar5 = pfVar5 + 1;
          *pfVar7 = fVar1;
          iVar9 = iVar9 + -1;
          pfVar7 = pfVar7 + 1;
        } while (iVar9 != 0);
        *param_3 = -*param_3;
        local_44[local_4c + 1] = *(float *)((int)local_44 + (4 - (int)param_1) + (int)param_4);
      }
      *(int *)((param_2 - (int)param_1) + (int)param_4) = local_4c;
      if (*local_54 == _DAT_005a83e4) {
        *local_54 = 1e-07;
      }
      if (local_5c != iVar3 + -1) {
        fVar1 = _DAT_005a83f4 / *local_54;
        if (local_5c + 1 < iVar3) {
          pfVar5 = param_1 + local_50 + local_5c;
          iVar9 = iVar3 - (local_5c + 1);
          do {
            *pfVar5 = fVar1 * *pfVar5;
            pfVar5 = pfVar5 + iVar3;
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
        }
      }
      local_58 = local_58 + iVar3;
      local_5c = local_5c + 1;
      param_4 = param_4 + 1;
      local_54 = local_54 + iVar3 + 1;
      local_50 = local_50 + iVar3;
    } while (local_5c < iVar3);
  }
  return;
}

