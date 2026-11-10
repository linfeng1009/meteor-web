/* Original Meteor.exe static export @ 004080a0; original sample not executed. */
/* XREF 00408573 UNCONDITIONAL_CALL */
/* XREF 00408966 UNCONDITIONAL_CALL */
/* XREF 0040ace6 UNCONDITIONAL_CALL */
/* XREF 0040ae91 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004080a0(int param_1,int param_2,float *param_3,float *param_4,int *param_5)

{
  float fVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_20 [4];
  int local_10 [4];
  
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x9c);
  fVar1 = *param_4;
  if (*param_4 <= _DAT_005a83e4) {
    fVar1 = -fVar1;
  }
  if (fVar1 < _DAT_005a8408) {
    fVar1 = param_4[1];
    if (param_4[1] <= _DAT_005a83e4) {
      fVar1 = -fVar1;
    }
    if (fVar1 < _DAT_005a8408) {
      return 0;
    }
  }
  piVar2 = *(int **)(iVar3 + 0x40);
  iVar4 = 0;
  iVar5 = param_2;
  if (0 < param_2) {
    do {
      iVar4 = DAT_005c4314;
      if (*piVar2 != 1) {
        iVar4 = piVar2[2] * 2 + 3;
      }
      piVar2 = piVar2 + iVar4;
      iVar5 = iVar5 + -1;
      iVar4 = param_2;
    } while (iVar5 != 0);
  }
  if (*(int *)(iVar3 + 0x34) <= iVar4) {
    return 0;
  }
  local_20[3] = piVar2[3];
  iVar3 = *(int *)(iVar3 + 0x1c);
  local_20[0] = local_20[3];
  local_20[1] = piVar2[4];
  local_20[2] = piVar2[5];
  local_10[0] = iVar3 + DAT_007eac64 * local_20[3] * 4;
  local_10[1] = iVar3 + DAT_007eac64 * piVar2[4] * 4;
  local_10[2] = iVar3 + DAT_007eac64 * piVar2[5] * 4;
  local_10[3] = iVar3 + DAT_007eac64 * local_20[3] * 4;
  iVar3 = 0;
  while (fVar1 = ((*(float *)local_20[iVar3 + 4] - *param_3) * param_4[1] +
                 (param_3[1] - ((float *)local_20[iVar3 + 4])[1]) * *param_4) *
                 ((*(float *)local_20[iVar3 + 5] - *param_3) * param_4[1] +
                 (param_3[1] - ((float *)local_20[iVar3 + 5])[1]) * *param_4),
        fVar1 < _DAT_005a83e4 == (fVar1 == _DAT_005a83e4)) {
    iVar3 = iVar3 + 1;
    if (2 < iVar3) {
      return 0;
    }
  }
  if (2 < iVar3) {
    return 0;
  }
  iVar5 = 0;
  piVar2 = *(int **)(param_1 + 0x24);
  iVar4 = *(int *)(param_1 + 0x20) / 3;
  if (0 < iVar4) {
    do {
      if (((*piVar2 == local_20[iVar3]) && (piVar2[1] == local_20[iVar3 + 1])) ||
         ((piVar2[1] == local_20[iVar3] && (*piVar2 == local_20[iVar3 + 1])))) break;
      piVar2 = piVar2 + 3;
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar4);
  }
  if (iVar4 <= iVar5) {
    return 0;
  }
  if (param_5 != (int *)0x0) {
    *param_5 = iVar5 / 3;
  }
  return piVar2[2];
}

