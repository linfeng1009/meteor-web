/* Original Meteor.exe static export @ 00408b70; original sample not executed. */
/* XREF 004083f6 UNCONDITIONAL_CALL */
/* XREF 004087ed UNCONDITIONAL_CALL */
/* XREF 0040ac53 UNCONDITIONAL_CALL */
/* XREF 0040ae08 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_00408b70(undefined4 param_1,int param_2,uint *param_3,float *param_4,float *param_5,
            undefined4 param_6,int param_7,undefined4 param_8)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float10 fVar7;
  int local_78;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60 [24];
  
  FUN_00406ed0(*param_3 | 0x2000000,0,local_60,0);
  if (param_7 == 2) {
    local_70 = -*param_5;
    local_6c = -param_5[1];
  }
  else if (param_7 == 3) {
    local_70 = param_5[1];
    local_6c = -*param_5;
  }
  else if (param_7 == 4) {
    local_6c = *param_5;
    local_70 = -param_5[1];
  }
  else {
    local_70 = *param_5;
    local_6c = param_5[1];
  }
  pfVar6 = local_60;
  local_78 = 0;
  do {
    local_68 = *pfVar6 - *param_4;
    local_64 = pfVar6[1] - param_4[1];
    fVar7 = (float10)FUN_00430e60(&local_70,&local_68);
    if ((((float10)_DAT_005a83e4 < fVar7) || (param_7 == 5)) &&
       (iVar2 = FUN_00410000(param_1,param_2 + 0xc + param_3[0x52] * DAT_005c4314 * 4,pfVar6,param_8
                            ), iVar2 == 0)) {
      iVar5 = 0;
      iVar2 = *(int *)(*(int *)(param_3[0x51] + 0x14) + param_3[0x52] * 4);
      iVar4 = *(int *)(param_3[0x51] + 0x1c);
      iVar1 = *(int *)(iVar4 + iVar2 * 4);
      if (0 < iVar1) {
        do {
          iVar3 = FUN_00410000(param_1,param_2 + 0xc +
                                       *(int *)(iVar4 + iVar2 * 4 + 4 + iVar5 * 4) * DAT_005c4314 *
                                       4,pfVar6,param_8);
          if (iVar3 != 0) goto LAB_00408d69;
          iVar5 = iVar5 + 1;
        } while (iVar5 < iVar1);
      }
      iVar2 = 0;
      while( true ) {
        if (*(int *)(*(int *)(*(int *)(param_3[0x51] + 4) + 0x9c) + 0x34) <= iVar2) {
          return 0;
        }
        iVar4 = FUN_00410000(param_1,param_2 + 0xc + DAT_005c4314 * iVar2 * 4,pfVar6,param_8);
        if ((iVar4 != 0) &&
           (iVar4 = FUN_0040ff40(param_1,param_2 + 0xc + DAT_005c4314 * iVar2 * 4,pfVar6,param_8,
                                 param_6), iVar4 != 0)) break;
        iVar2 = iVar2 + 1;
      }
    }
LAB_00408d69:
    pfVar6 = pfVar6 + 3;
    local_78 = local_78 + 1;
    if (7 < local_78) {
      return 1;
    }
  } while( true );
}

