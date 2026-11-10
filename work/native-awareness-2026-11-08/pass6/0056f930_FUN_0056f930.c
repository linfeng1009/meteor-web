/* Original Meteor.exe static export @ 0056f930; original sample not executed. */
/* XREF 0057023e UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0056f930(float *param_1,float param_2,float *param_3)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float local_18 [6];
  
  iVar3 = (int)local_18 - (int)param_3;
  iVar5 = (int)local_18 + (0xc - (int)param_3);
  iVar4 = 3;
  do {
    pfVar1 = (float *)(iVar3 + (int)param_3);
    if (*(float *)((int)pfVar1 + ((int)param_1 - (int)local_18)) <= _DAT_005a83e4) {
      fVar2 = *param_3;
      *(float *)(iVar5 + (int)param_3) = -*param_3;
      *pfVar1 = fVar2;
    }
    else {
      *pfVar1 = -*param_3;
      *(float *)(iVar5 + (int)param_3) = *param_3;
    }
    param_3 = param_3 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if ((local_18[1] * param_1[1] + local_18[2] * param_1[2] + local_18[0] * *param_1 + param_2 <=
       (float)_DAT_005a84b8) &&
     ((float)_DAT_005a84b8 <=
      local_18[4] * param_1[1] + local_18[5] * param_1[2] + local_18[3] * *param_1 + param_2)) {
    return 1;
  }
  return 0;
}

