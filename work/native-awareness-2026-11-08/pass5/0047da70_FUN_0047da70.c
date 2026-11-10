/* Original Meteor.exe static export @ 0047da70; original sample not executed. */
/* XREF 00588b15 UNCONDITIONAL_CALL */
/* XREF 00572d37 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0047da70(int param_1,float param_2,float param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 local_1c;
  undefined4 local_14;
  undefined4 uStack_8;
  
  uStack_8 = param_1;
  local_14 = 0.0;
  fVar1 = _DAT_005a83f4 / (float)param_1;
  fVar2 = param_2 * fVar1;
  fVar3 = param_3 * _DAT_005a83e8;
  local_1c = param_2 * _DAT_005a8ff0;
  iVar4 = FUN_0047c1e0(param_1 << 2,param_1 * 2,param_1 * 6);
  if (iVar4 == 0) {
    return 0;
  }
  iVar5 = 0;
  iVar4 = 0;
  FUN_00481b30();
  FUN_00481b30();
  if (0 < param_1) {
    param_1 = 2;
    param_3 = fVar1;
    do {
      param_2 = local_1c + fVar2;
      FUN_00481c20(iVar5,local_1c,-fVar3,0);
      FUN_00481cb0(iVar5,0,0,0x3f800000);
      FUN_00481d00(iVar5,0xffffffff);
      FUN_00481d40(iVar5,local_14,0,0xffffffff);
      iVar6 = iVar5 + 1;
      FUN_00481c20(iVar6,param_2,-fVar3,0);
      FUN_00481cb0(iVar6,0,0,0x3f800000);
      FUN_00481d00(iVar6,0xffffffff);
      FUN_00481d40(iVar6,param_3,0,0xffffffff);
      iVar6 = iVar5 + 2;
      FUN_00481c20(iVar6,param_2,fVar3,0);
      FUN_00481cb0(iVar6,0,0,0x3f800000);
      FUN_00481d00(iVar6,0xffffffff);
      FUN_00481d40(iVar6,param_3,0x3f800000,0xffffffff);
      iVar6 = iVar5 + 3;
      FUN_00481c20(iVar6,local_1c,fVar3,0);
      FUN_00481cb0(iVar6,0,0,0x3f800000);
      FUN_00481d00(iVar6,0xffffffff);
      FUN_00481d40(iVar6,local_14,0x3f800000,0xffffffff);
      local_1c = param_2;
      iVar5 = iVar5 + 4;
      local_14 = param_3;
      FUN_00481ee0(iVar4,param_1 + -2);
      FUN_00481ee0(iVar4 + 1,param_1 + -1);
      FUN_00481ee0(iVar4 + 2,param_1);
      FUN_00481ee0(iVar4 + 3,param_1 + -2);
      iVar6 = iVar4 + 5;
      FUN_00481ee0(iVar4 + 4,param_1);
      iVar4 = iVar4 + 6;
      FUN_00481ee0(iVar6,param_1 + 1);
      param_1 = param_1 + 4;
      uStack_8 = uStack_8 + -1;
      param_3 = param_3 + fVar1;
    } while (uStack_8 != 0);
  }
  FUN_00481b90();
  FUN_00481b90();
  return 1;
}

