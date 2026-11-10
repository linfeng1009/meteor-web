/* Original Meteor.exe static export @ 00431900; original sample not executed. */
/* XREF 0043164a UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00431900(float *param_1,int param_2,float *param_3,int param_4)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int local_4;
  
  iVar5 = param_4;
  iVar4 = (int)param_1;
  iVar10 = -1;
  local_4 = 0;
  if (0 < param_4) {
    param_4 = 0;
    pfVar7 = param_3;
    do {
      iVar6 = *(int *)((param_2 - (int)param_3) + (int)pfVar7);
      fVar2 = param_3[iVar6];
      param_3[iVar6] = *pfVar7;
      if (iVar10 == -1) {
        if (fVar2 != _DAT_005a83e4) {
          iVar10 = local_4;
        }
      }
      else if (iVar10 <= local_4 + -1) {
        pfVar8 = (float *)((int)param_1 + (param_4 + iVar10) * 4);
        iVar6 = iVar10;
        do {
          pfVar1 = param_3 + iVar6;
          fVar3 = *pfVar8;
          iVar6 = iVar6 + 1;
          pfVar8 = pfVar8 + 1;
          fVar2 = fVar2 - *pfVar1 * fVar3;
        } while (iVar6 <= local_4 + -1);
      }
      local_4 = local_4 + 1;
      *pfVar7 = fVar2;
      param_4 = param_4 + iVar5;
      pfVar7 = pfVar7 + 1;
    } while (local_4 < iVar5);
  }
  iVar10 = iVar5 + -1;
  if (-1 < iVar10) {
    iVar6 = iVar10 * iVar5;
    param_1 = (float *)((int)param_1 + (iVar5 + 1) * iVar10 * 4);
    do {
      fVar2 = param_3[iVar10];
      iVar9 = iVar10 + 1;
      if (iVar9 < iVar5) {
        pfVar7 = (float *)(iVar4 + 4 + (iVar6 + iVar10) * 4);
        do {
          pfVar8 = param_3 + iVar9;
          fVar3 = *pfVar7;
          iVar9 = iVar9 + 1;
          pfVar7 = pfVar7 + 1;
          fVar2 = fVar2 - *pfVar8 * fVar3;
        } while (iVar9 < iVar5);
      }
      iVar6 = iVar6 - iVar5;
      iVar9 = iVar10 + -1;
      fVar3 = *param_1;
      param_1 = param_1 + (-1 - iVar5);
      param_3[iVar10] = fVar2 / fVar3;
      iVar10 = iVar9;
    } while (-1 < iVar9);
  }
  return;
}

