/* Original Meteor.exe static export @ 004708e0; original sample not executed. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004708e0(int param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  void *pvVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  void **ppvVar8;
  int **ppiVar9;
  undefined **ppuVar10;
  float *pfVar11;
  float afStack_94 [5];
  undefined *puStack_80;
  int *apiStack_34 [3];
  void *local_28 [5];
  undefined4 local_14;
  undefined4 local_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059d00c;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_00429990();
  FUN_00429aa0();
  puVar1 = (undefined *)FUN_00429c30();
  *(undefined **)(param_1 + 0x84) = puVar1;
  __ftol();
  __ftol();
  afStack_94[4] = 6.523661e-39;
  puStack_80 = puVar1;
  FUN_00429d00();
  afStack_94[3] = *(float *)(param_1 + 0x84);
  afStack_94[4] = 0.0;
  afStack_94[2] = 6.523679e-39;
  FUN_00429de0();
  afStack_94[2] = 0.0;
  afStack_94[1] = 6.523688e-39;
  FUN_00429990();
  afStack_94[1] = 6.523711e-39;
  afStack_94[0] = (float)__ftol();
  afStack_94[1] = afStack_94[0];
  FUN_00429b80(1,1,1);
  uVar2 = FUN_00429c30();
  *(undefined4 *)(param_1 + 0x80) = uVar2;
  FUN_00429d80();
  __ftol();
  __ftol();
  puStack_80 = *(undefined **)(param_1 + 0x80);
  afStack_94[4] = 6.523833e-39;
  FUN_00429d00();
  afStack_94[3] = *(float *)(param_1 + 0x80);
  afStack_94[4] = 0.0;
  afStack_94[2] = 6.523851e-39;
  FUN_00429de0();
  afStack_94[2] = 0.0;
  afStack_94[1] = 6.52386e-39;
  FUN_00429990();
  afStack_94[1] = 2.8026e-43;
  afStack_94[0] = 4.2039e-43;
  FUN_00429aa0(s_sheng_005c7c3c,0);
  uVar2 = FUN_00429c30();
  *(undefined4 *)(param_1 + 0x68) = uVar2;
  FUN_00429d80();
  puStack_80 = *(undefined **)(param_1 + 0x68);
  afStack_94[4] = 6.523965e-39;
  FUN_00429dc0();
  afStack_94[3] = *(float *)(param_1 + 0x68);
  afStack_94[4] = 0.0;
  afStack_94[2] = 6.523979e-39;
  FUN_00429de0();
  afStack_94[2] = 7.00649e-45;
  afStack_94[1] = 0.0;
  afStack_94[0] = 0.0;
  FUN_00429d40(*(undefined4 *)(param_1 + 0x68));
  FUN_00429990(0);
  FUN_00429aa0();
  afStack_94[4] = (float)FUN_00429c30();
  puStack_80 = (undefined *)0x0;
  *(float *)(param_1 + 0x6c) = afStack_94[4];
  afStack_94[3] = 6.524067e-39;
  FUN_00429d80();
  afStack_94[2] = DAT_005c7b60 * _DAT_005a83e8;
  afStack_94[1] = *(float *)(param_1 + 0x6c);
  afStack_94[0] = 6.524111e-39;
  afStack_94[3] = afStack_94[2];
  FUN_00429dc0();
  afStack_94[0] = 0.0;
  FUN_00429de0(*(undefined4 *)(param_1 + 0x6c));
  FUN_00429d40(*(undefined4 *)(param_1 + 0x6c),0,0,5);
  FUN_00429990();
  FUN_00429aa0();
  afStack_94[3] = (float)FUN_00429c30();
  puStack_80 = (undefined *)0x47;
  afStack_94[4] = 6.72623e-44;
  *(float *)(param_1 + 0x70) = afStack_94[3];
  afStack_94[2] = 6.524213e-39;
  FUN_00429d80();
  afStack_94[1] = DAT_005c7b60 * _DAT_005a83e8;
  afStack_94[0] = *(float *)(param_1 + 0x70);
  afStack_94[2] = afStack_94[1];
  FUN_00429dc0();
  FUN_00429de0(*(undefined4 *)(param_1 + 0x70),0);
  FUN_00429d40();
  FUN_00429990();
  puStack_80 = &DAT_005c7c2c;
  afStack_94[4] = 6.524331e-39;
  FUN_00429aa0();
  afStack_94[4] = 0.0;
  afStack_94[3] = 6.524339e-39;
  uVar2 = FUN_00429c30();
  afStack_94[3] = 1.4013e-45;
  afStack_94[2] = 0.0;
  afStack_94[1] = 0.0;
  afStack_94[0] = 0.0;
  *(undefined4 *)(param_1 + 0x74) = uVar2;
  FUN_00429d80(uVar2);
  FUN_00429dc0(*(undefined4 *)(param_1 + 0x74),DAT_005c7b60 * _DAT_005a83e8,
               DAT_005c7b60 * _DAT_005a83e8);
  FUN_00429de0();
  FUN_00429d40();
  local_28[0] = operator_new(0x6c);
  local_4 = 0;
  if (local_28[0] == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0046b270();
  }
  local_4 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x40) = uVar2;
  local_28[0] = operator_new(0x58);
  local_4 = 1;
  if (local_28[0] == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0046b680();
  }
  local_4 = 0xffffffff;
  local_10 = 0x3f800000;
  local_28[4] = (void *)0x43828000;
  local_14 = 0x43390000;
  local_28[2] = (void *)0x43740000;
  local_28[3] = (void *)0x433e0000;
  ppvVar8 = local_28 + 2;
  puVar3 = (undefined4 *)&stack0xffffff90;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar3 = *ppvVar8;
    ppvVar8 = ppvVar8 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)(param_1 + 0x44) = uVar2;
  FUN_0046b910();
  FUN_00462e50();
  (**(code **)(**(int **)(param_1 + 0x40) + 0x58))();
  puVar3 = operator_new(0x6c);
  puStack_8 = (undefined1 *)0x2;
  apiStack_34[2] = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar3 = &PTR_FUN_005a85e0;
  }
  puStack_8 = (undefined1 *)0xffffffff;
  *(undefined4 **)(param_1 + 0x48) = puVar3;
  apiStack_34[2] = operator_new(0x3c);
  puStack_8 = (undefined1 *)0x3;
  if (apiStack_34[2] == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0046db50();
  }
  puStack_8 = (undefined1 *)0xffffffff;
  ppvVar8 = local_28;
  local_28[3] = (void *)0x43828000;
  local_28[4] = (void *)0x43390000;
  local_28[1] = (void *)0x43740000;
  local_28[2] = (void *)0x433e0000;
  puVar3 = (undefined4 *)&stack0xffffff88;
  for (iVar6 = 5; ppvVar8 = ppvVar8 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar3 = *ppvVar8;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)(param_1 + 0x4c) = uVar2;
  FUN_0046e240();
  FUN_00462e50();
  (**(code **)(**(int **)(param_1 + 0x48) + 0x58))();
  pvVar4 = operator_new(0x34);
  if (pvVar4 == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0046f490();
  }
  *(undefined4 *)(param_1 + 4) = uVar2;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  FUN_0046f880();
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 1;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  local_28[0] = (void *)0x43340000;
  local_28[1] = (void *)0x43d98000;
  local_28[2] = (void *)0x42480000;
  local_28[3] = (void *)0x41a00000;
  puVar3 = operator_new(0x34);
  apiStack_34[1] = puVar3;
  pvStack_c = (void *)0x4;
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    piVar5 = puVar3 + 9;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    pvStack_c._0_1_ = 5;
    pvStack_c._1_3_ = 0;
    *piVar5 = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    apiStack_34[0] = piVar5;
    iVar6 = FUN_00402bf0();
    *piVar5 = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    pvStack_c = (void *)CONCAT31(pvStack_c._1_3_,7);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppvVar8 = local_28;
  ppuVar10 = &puStack_80;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar10 = *ppvVar8;
    ppvVar8 = ppvVar8 + 1;
    ppuVar10 = ppuVar10 + 1;
  }
  pvStack_c = (void *)0xffffffff;
  *(undefined4 **)(param_1 + 0x58) = puVar3;
  afStack_94[4] = 6.52534e-39;
  FUN_004636d0();
  FUN_00463b30();
  (**(code **)(**(int **)(param_1 + 0x58) + 0xc))();
  piVar5 = operator_new(0x6c);
  local_10 = 8;
  if (piVar5 == (int *)0x0) {
    piVar7 = (int *)0x0;
    apiStack_34[0] = piVar5;
  }
  else {
    apiStack_34[0] = piVar5;
    FUN_00462d50();
    *piVar5 = (int)&PTR_FUN_005a8a40;
    piVar7 = piVar5;
  }
  local_10 = 0xffffffff;
  *(int **)(param_1 + 0x60) = piVar7;
  puStack_80 = (undefined *)0x470e6e;
  FUN_00462e50();
  apiStack_34[2] = (int *)0x43960000;
  local_28[0] = (void *)0x43d98000;
  local_28[1] = (void *)0x42480000;
  local_28[2] = (void *)0x41a00000;
  piVar5 = operator_new(0x34);
  apiStack_34[0] = piVar5;
  local_10 = 9;
  if (piVar5 == (int *)0x0) {
    piVar5 = (int *)0x0;
  }
  else {
    *piVar5 = (int)&PTR_LAB_005a8810;
    piVar5[1] = 0;
    piVar5[3] = 0;
    piVar5[4] = 0;
    piVar5[5] = 0;
    piVar5[6] = 0;
    piVar5[7] = 0x3f800000;
    local_10._0_1_ = 10;
    local_10._1_3_ = 0;
    piVar5[9] = 0;
    piVar5[10] = 0;
    piVar5[0xb] = 0;
    iVar6 = FUN_00402bf0();
    piVar5[9] = iVar6;
    piVar5[10] = iVar6;
    piVar5[0xb] = iVar6 + 8;
    local_10 = CONCAT31(local_10._1_3_,0xc);
    FUN_00402a70();
    *piVar5 = (int)&PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34 + 2;
  pfVar11 = afStack_94 + 4;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    ppiVar9 = ppiVar9 + 1;
    pfVar11 = pfVar11 + 1;
  }
  local_10 = 0xffffffff;
  *(int **)(param_1 + 0x5c) = piVar5;
  afStack_94[3] = 6.525761e-39;
  FUN_004636d0();
  FUN_00463b30();
  (**(code **)(**(int **)(param_1 + 0x5c) + 0xc))();
  puVar3 = operator_new(0x6c);
  local_14 = 0xd;
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar3 = &PTR_FUN_005a8a40;
  }
  local_14 = 0xffffffff;
  *(undefined4 **)(param_1 + 100) = puVar3;
  puStack_80 = (undefined *)0x0;
  afStack_94[4] = 6.525918e-39;
  FUN_00462e50();
  DAT_005e0078 = FUN_005054e0();
  FUN_00505a10();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42f40000;
  apiStack_34[1] = (int *)0x42dc0000;
  apiStack_34[2] = (int *)0x42940000;
  puStack_80 = (undefined *)0x470fd8;
  puVar3 = operator_new(0x34);
  local_14 = 0xe;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0xf;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x11);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.526218e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42be0000;
  apiStack_34[1] = (int *)0x43680000;
  apiStack_34[2] = (int *)0x42940000;
  puVar3 = operator_new(0x34);
  local_14 = 0x12;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x13;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x15);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.526507e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42740000;
  apiStack_34[1] = (int *)0x43a38000;
  apiStack_34[2] = (int *)0x42940000;
  puVar3 = operator_new(0x34);
  local_14 = 0x16;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x17;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x19);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.526796e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42cc0000;
  apiStack_34[1] = (int *)0x43c20000;
  apiStack_34[2] = (int *)0x42940000;
  puVar3 = operator_new(0x34);
  local_14 = 0x1a;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x1b;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x1d);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.527084e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42300000;
  apiStack_34[1] = (int *)0x43f50000;
  apiStack_34[2] = (int *)0x42940000;
  puVar3 = operator_new(0x34);
  local_14 = 0x1e;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x1f;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x21);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.527373e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42f40000;
  apiStack_34[1] = (int *)0x42dc0000;
  apiStack_34[2] = (int *)0x437c0000;
  puVar3 = operator_new(0x34);
  local_14 = 0x22;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x23;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x25);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.527662e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42be0000;
  apiStack_34[1] = (int *)0x43680000;
  apiStack_34[2] = (int *)0x437c0000;
  puVar3 = operator_new(0x34);
  local_14 = 0x26;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x27;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x28);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.52795e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42740000;
  apiStack_34[1] = (int *)0x43a38000;
  apiStack_34[2] = (int *)0x437c0000;
  puVar3 = operator_new(0x34);
  local_14 = 0x29;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x2a;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x2b);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.528239e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42cc0000;
  apiStack_34[1] = (int *)0x43c20000;
  apiStack_34[2] = (int *)0x437c0000;
  puVar3 = operator_new(0x34);
  local_14 = 0x2c;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x2d;
    local_14._1_3_ = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    iVar6 = FUN_00402bf0();
    puVar3[9] = iVar6;
    puVar3[10] = iVar6;
    puVar3[0xb] = iVar6 + 8;
    local_14 = CONCAT31(local_14._1_3_,0x2e);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.528528e-39;
  FUN_004636d0();
  FUN_00463b30();
  local_28[1] = (void *)0x41880000;
  local_28[0] = (void *)0x42300000;
  apiStack_34[1] = (int *)0x43f50000;
  apiStack_34[2] = (int *)0x437c0000;
  puVar3 = operator_new(0x34);
  local_14 = 0x2f;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = &PTR_LAB_005a8810;
    puVar3[1] = 0;
    apiStack_34[0] = puVar3 + 9;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x3f800000;
    local_14._0_1_ = 0x30;
    local_14._1_3_ = 0;
    *apiStack_34[0] = 0;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    FUN_004608a0();
    local_14 = CONCAT31(local_14._1_3_,0x31);
    FUN_00402a70();
    *puVar3 = &PTR_FUN_005a8700;
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 3;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  afStack_94[2] = 6.5288e-39;
  FUN_004636d0();
  FUN_00463b30();
  apiStack_34[1] = (int *)0x0;
  apiStack_34[2] = (int *)0x0;
  local_28[0] = (void *)0x0;
  local_28[1] = (void *)0x0;
  local_28[2] = (void *)0x0;
  apiStack_34[0] = operator_new(0x78);
  local_14 = 0x32;
  if (apiStack_34[0] == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00467160();
  }
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94 + 1;
  for (iVar6 = 5; ppiVar9 = ppiVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    pfVar11 = pfVar11 + 1;
  }
  local_14 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1c) = uVar2;
  afStack_94[0] = 6.528956e-39;
  FUN_00467840();
  FUN_00467c50();
  FUN_00467c50();
  FUN_00467c50();
  FUN_00467c50();
  FUN_00467c50();
  (**(code **)(**(int **)(param_1 + 0x1c) + 0xc))();
  apiStack_34[0] = (int *)0x0;
  apiStack_34[1] = (int *)0x0;
  apiStack_34[2] = (int *)0x0;
  local_28[0] = (void *)0x0;
  local_28[1] = (void *)0x0;
  pvVar4 = operator_new(0x78);
  local_28[4] = (void *)0x33;
  if (pvVar4 == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00467160();
  }
  puStack_80 = (undefined *)0x10;
  ppiVar9 = apiStack_34;
  pfVar11 = afStack_94;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar11 = (float)*ppiVar9;
    ppiVar9 = ppiVar9 + 1;
    pfVar11 = pfVar11 + 1;
  }
  local_28[4] = (void *)0xffffffff;
  *(undefined4 *)(param_1 + 0x20) = uVar2;
  FUN_00467840();
  FUN_00467c50();
  FUN_00467c50();
  FUN_00467c50();
  FUN_00467c50();
  FUN_00467c50();
  (**(code **)(**(int **)(param_1 + 0x20) + 0xc))();
  ExceptionList = local_28[1];
  return 1;
}

