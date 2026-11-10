/* Original Meteor.exe static export @ 00538ba0; original sample not executed. */
/* XREF 00538d85 UNCONDITIONAL_CALL */
/* XREF 00538daa UNCONDITIONAL_CALL */
/* XREF 00538dcc UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00538ba0(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int *param_5,
                    int param_6,int param_7,int param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  float10 extraout_ST0;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  
  iVar1 = FUN_005387f0(param_1,param_2,&DAT_00796400);
  iVar2 = FUN_005387f0(param_1,param_2,&DAT_00773260);
  iVar3 = FUN_005387f0(param_1,param_2,&DAT_007500c0);
  iVar4 = FUN_005387f0(param_1,param_2,&DAT_007b95a0);
  fVar9 = (float10)_DAT_005a83e4;
  *param_5 = -1;
  for (; param_3 < param_4; param_3 = param_3 + 1) {
    iVar5 = FUN_00538940(param_1,param_2,param_3,&DAT_00796400);
    iVar6 = FUN_00538940(param_1,param_2,param_3,&DAT_00773260);
    iVar7 = FUN_00538940(param_1,param_2,param_3,&DAT_007500c0);
    iVar8 = FUN_00538940(param_1,param_2,param_3,&DAT_007b95a0);
    iVar8 = iVar8 + iVar4;
    fVar9 = extraout_ST0;
    if (iVar8 != 0) {
      fVar10 = (float10)(iVar7 + iVar3);
      fVar11 = (float10)(iVar6 + iVar2);
      fVar12 = (float10)(iVar5 + iVar1);
      if ((param_9 - iVar8 != 0) &&
         (fVar13 = (float10)(param_8 - (iVar7 + iVar3)),
         fVar14 = (float10)(param_7 - (iVar6 + iVar2)),
         fVar15 = (float10)(param_6 - (iVar5 + iVar1)),
         fVar10 = (fVar13 * fVar13 + fVar14 * fVar14 + fVar15 * fVar15) / (float10)(param_9 - iVar8)
                  + (fVar10 * fVar10 + fVar11 * fVar11 + fVar12 * fVar12) / (float10)iVar8,
         extraout_ST0 < fVar10)) {
        fVar9 = (float10)(float)fVar10;
        *param_5 = param_3;
      }
    }
  }
  return fVar9;
}

