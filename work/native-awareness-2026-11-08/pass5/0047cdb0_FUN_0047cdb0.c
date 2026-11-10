/* Original Meteor.exe static export @ 0047cdb0; original sample not executed. */
/* XREF 00588ff1 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0047cdb0(float param_1,float param_2,float param_3,float param_4,float param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float10 fVar10;
  float local_14;
  
  iVar6 = FUN_0047c1e0(DAT_005c8128 * 2 + 2,DAT_005c8128 * 2,DAT_005c8128 * 6);
  if (iVar6 != 0) {
    fVar3 = (param_2 - param_1) * _DAT_005a8fec;
    iVar6 = 0;
    fVar4 = (float)DAT_005c8128;
    local_14 = param_1 * _DAT_005a8fec;
    FUN_00481b30();
    param_2 = 0.0;
    if (-1 < DAT_005c8128) {
      fVar5 = param_5 * _DAT_005a8ff0;
      param_5 = param_5 * _DAT_005a83e8;
      do {
        fVar10 = (float10)fsin((float10)local_14);
        fVar1 = (float)fVar10;
        fVar10 = (float10)fcos((float10)local_14);
        fVar2 = (float)fVar10;
        FUN_00481c20(iVar6,fVar2 * param_3,fVar1 * param_3,fVar5);
        FUN_00481cb0(iVar6,fVar2,fVar1,0);
        FUN_00481d00(iVar6,0xffffffff);
        FUN_00481d40(iVar6,(float)(int)param_2 / (float)DAT_005c8128,0,0xffffffff);
        iVar8 = iVar6 + 1;
        FUN_00481c20(iVar8,fVar2 * param_4,fVar1 * param_4,param_5);
        FUN_00481cb0(iVar8,fVar2,fVar1,0);
        FUN_00481d40(iVar8,(float)(int)param_2 / (float)DAT_005c8128,0x3f800000,0xffffffff);
        local_14 = local_14 + fVar3 / fVar4;
        iVar6 = iVar6 + 2;
        param_2 = (float)((int)param_2 + 1);
      } while ((int)param_2 <= DAT_005c8128);
    }
    FUN_00481b90();
    iVar6 = 0;
    iVar8 = 0;
    FUN_00481b30();
    param_2 = 0.0;
    if (0 < DAT_005c8128) {
      param_1 = 2.8026e-45;
      iVar7 = 1;
      do {
        FUN_00481ee0(iVar8,iVar6);
        FUN_00481ee0(iVar8 + 1,param_1);
        FUN_00481ee0(iVar8 + 2,iVar7);
        FUN_00481ee0(iVar8 + 3,iVar6 + 1);
        iVar9 = iVar8 + 5;
        FUN_00481ee0(iVar8 + 4,iVar7 + 1);
        iVar8 = iVar8 + 6;
        FUN_00481ee0(iVar9,(int)param_1 + 1);
        iVar6 = iVar6 + 2;
        iVar7 = iVar7 + 2;
        param_1 = (float)((int)param_1 + 2);
        param_2 = (float)((int)param_2 + 1);
      } while ((int)param_2 < DAT_005c8128);
    }
    FUN_00481b90();
    return 1;
  }
  return 0;
}

