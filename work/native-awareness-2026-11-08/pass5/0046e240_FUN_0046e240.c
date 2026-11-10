/* Original Meteor.exe static export @ 0046e240; original sample not executed. */
/* XREF 004356f2 UNCONDITIONAL_CALL */
/* XREF 00470cd1 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0046e240(int param_1,undefined4 *param_2)

{
  float fVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  void *pvVar5;
  int iVar6;
  float *pfVar7;
  undefined4 *puVar8;
  int **ppiVar9;
  int in_stack_00000018;
  int *apiStack_68 [2];
  int *apiStack_60 [2];
  char *pcStack_58;
  int iStack_54;
  int **ppiStack_50;
  int *piStack_4c;
  float local_34;
  int local_30;
  float local_2c;
  int *local_28;
  int local_24;
  float local_20 [5];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059cd3c;
  local_c = ExceptionList;
  puVar8 = (undefined4 *)(param_1 + 0x18);
  puVar4 = (undefined4 *)register0x00000010;
  ExceptionList = &local_c;
  for (iVar6 = 5; puVar4 = puVar4 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar4;
    puVar8 = puVar8 + 1;
  }
  *(int *)(param_1 + 0x38) = in_stack_00000018;
  *(undefined4 *)(param_1 + 0x34) = 0;
  piStack_4c = (int *)0x46e27e;
  FUN_00429990();
  piStack_4c = (int *)0x46e286;
  piStack_4c = (int *)__ftol();
  ppiStack_50 = (int **)0x46e28f;
  ppiStack_50 = (int **)__ftol();
  iStack_54 = 0;
  pcStack_58 = s_gialog_bmp_005c7bcc;
  apiStack_60[1] = (int *)0x46e29b;
  FUN_00429aa0();
  apiStack_60[1] = (int *)0x0;
  apiStack_60[0] = (int *)0x46e2a1;
  piVar2 = (int *)FUN_00429c30();
  *(int **)(param_1 + 0x2c) = piVar2;
  apiStack_60[0] = (int *)0x46e2ae;
  apiStack_60[0] = (int *)__ftol();
  apiStack_68[1] = (int *)0x46e2b7;
  apiStack_68[1] = (int *)__ftol();
  apiStack_68[0] = piVar2;
  FUN_00429d00();
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) * _DAT_005a8e18;
  *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) * _DAT_005a8e18;
  FUN_00429dc0(*(undefined4 *)(param_1 + 0x2c),0x3f200000,0x3f200000);
  FUN_00429990(0);
  uVar3 = __ftol();
  uVar3 = __ftol(uVar3);
  FUN_00429b80(1,1,1,uVar3);
  piStack_4c = (int *)0x46e321;
  uVar3 = FUN_00429c30();
  *(undefined4 *)(param_1 + 0x30) = uVar3;
  piStack_4c = (int *)0x46e32e;
  piStack_4c = (int *)__ftol();
  ppiStack_50 = (int **)0x46e337;
  ppiStack_50 = (int **)__ftol();
  pcStack_58 = (char *)0x46e33e;
  iStack_54 = uVar3;
  FUN_00429d00();
  apiStack_68[0] = *(int **)(param_1 + 0x30);
  pcStack_58 = (char *)0x0;
  apiStack_60[1] = (undefined4 *)0x0;
  apiStack_60[0] = (int *)0x0;
  apiStack_68[1] = (int *)0x0;
  FUN_00429e90();
  FUN_00429d80(*(undefined4 *)(param_1 + 0x30),0,0,0,1);
  uVar3 = __ftol(7);
  uVar3 = __ftol(uVar3);
  FUN_00429d40(*(undefined4 *)(param_1 + 0x30),uVar3);
  piStack_4c = (int *)0x46e380;
  puVar4 = operator_new(0x34);
  param_2 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    puVar4 = (undefined4 *)0x0;
  }
  else {
    *puVar4 = &PTR_LAB_005a8810;
    puVar4[1] = 0;
    local_28 = puVar4 + 9;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0x3f800000;
    local_4._0_1_ = 1;
    local_4._1_3_ = 0;
    *local_28 = 0;
    puVar4[10] = 0;
    puVar4[0xb] = 0;
    piStack_4c = (int *)0x46e3ca;
    FUN_004608a0();
    local_4 = CONCAT31(local_4._1_3_,2);
    FUN_00402a70();
    *puVar4 = &PTR_FUN_005a8700;
  }
  local_4 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x10) = puVar4;
  if (in_stack_00000018 == 0) {
    piStack_4c = (int *)0x46e3fa;
    puVar4 = operator_new(0x34);
    param_2 = puVar4;
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      *puVar4 = &PTR_LAB_005a8810;
      puVar4[1] = 0;
      local_28 = puVar4 + 9;
      puVar4[3] = 0;
      puVar4[4] = 0;
      puVar4[5] = 0;
      puVar4[6] = 0;
      puVar4[7] = 0x3f800000;
      local_4._0_1_ = 4;
      local_4._1_3_ = 0;
      *local_28 = 0;
      puVar4[10] = 0;
      puVar4[0xb] = 0;
      piStack_4c = (int *)0x46e448;
      FUN_004608a0();
      local_4 = CONCAT31(local_4._1_3_,5);
      FUN_00402a70();
      *puVar4 = &PTR_FUN_005a8700;
    }
    local_4 = 0xffffffff;
    *(undefined4 **)(param_1 + 0xc) = puVar4;
  }
  local_4 = 0xffffffff;
  fVar1 = *(float *)(param_1 + 0x20) * _DAT_005a83e8;
  piStack_4c = (int *)0x0;
  local_20[4] = 1.0;
  iVar6 = 5;
  local_20[3] = 20.0;
  local_20[2] = 60.0;
  if (in_stack_00000018 == 0) {
    local_20[0] = ((fVar1 - *(float *)(param_1 + 0x28) * _DAT_005a8db8) * _DAT_005a83e8 +
                  *(float *)(param_1 + 0x18)) - _DAT_005a84ac;
    local_20[1] = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x1c)) - _DAT_005a8dbc;
    pfVar7 = local_20;
    ppiVar9 = apiStack_68 + 2;
    for (; iVar6 != 0; iVar6 = iVar6 + -1) {
      *ppiVar9 = (int *)*pfVar7;
      pfVar7 = pfVar7 + 1;
      ppiVar9 = ppiVar9 + 1;
    }
    apiStack_68[1] = (int *)0x46e4de;
    FUN_004636d0();
    piStack_4c = (int *)0x46e4eb;
    FUN_00463b30();
    piStack_4c = (int *)0x0;
    local_20[0] = *(float *)(param_1 + 0x20) * _DAT_005a83e8 + local_20[0];
    pfVar7 = local_20;
    ppiVar9 = apiStack_68 + 2;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *ppiVar9 = (int *)*pfVar7;
      pfVar7 = pfVar7 + 1;
      ppiVar9 = ppiVar9 + 1;
    }
    apiStack_68[1] = (int *)0x46e516;
    FUN_004636d0();
    piStack_4c = (int *)0x46e523;
    FUN_00463b30();
    piStack_4c = (int *)0x46e52a;
    puVar4 = operator_new(0x34);
    param_2 = puVar4;
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      *puVar4 = &PTR_LAB_005a8810;
      puVar4[1] = 0;
      local_28 = puVar4 + 9;
      puVar4[3] = 0;
      puVar4[4] = 0;
      puVar4[5] = 0;
      puVar4[6] = 0;
      puVar4[7] = 0x3f800000;
      local_4._0_1_ = 7;
      local_4._1_3_ = 0;
      *local_28 = 0;
      puVar4[10] = 0;
      puVar4[0xb] = 0;
      piStack_4c = (int *)0x46e578;
      FUN_004608a0();
      local_4 = CONCAT31(local_4._1_3_,8);
      FUN_00402a70();
      *puVar4 = &PTR_FUN_005a8700;
    }
    piStack_4c = (int *)0x0;
    local_20[0] = *(float *)(param_1 + 0x18) + _DAT_005a8f54;
    local_20[1] = *(float *)(param_1 + 0x1c) + _DAT_005a8f50;
    local_20[2] = 60.0;
    local_20[3] = 20.0;
    local_4 = 0xffffffff;
    *(undefined4 **)(param_1 + 0x14) = puVar4;
    pfVar7 = local_20;
    ppiVar9 = apiStack_68 + 2;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *ppiVar9 = (int *)*pfVar7;
      pfVar7 = pfVar7 + 1;
      ppiVar9 = ppiVar9 + 1;
    }
    apiStack_68[1] = (int *)0x46e5de;
    FUN_004636d0();
    piStack_4c = (int *)0x46e5eb;
    FUN_00463b30();
    piStack_4c = (int *)0x46e5f2;
    pvVar5 = operator_new(0x7c);
    if (pvVar5 == (void *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00463fb0();
    }
    piStack_4c = (int *)0xff;
    ppiStack_50 = (int **)0xff;
    iStack_54 = 0;
    local_20[0] = *(float *)(param_1 + 0x18) + _DAT_005a8b08;
    local_20[1] = *(float *)(param_1 + 0x1c) + _DAT_005a8f50;
    local_20[2] = 80.0;
    local_20[3] = 20.0;
    *(undefined4 *)(param_1 + 8) = uVar3;
    pfVar7 = local_20;
    ppiVar9 = apiStack_68;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *ppiVar9 = (int *)*pfVar7;
      pfVar7 = pfVar7 + 1;
      ppiVar9 = ppiVar9 + 1;
    }
    FUN_004642f0();
    iVar6 = *(int *)(param_1 + 8);
    if (*(int *)(iVar6 + 0x38) == 0) goto LAB_0046e8d1;
    piStack_4c = (int *)&param_2;
    ppiStack_50 = (int **)&local_34;
    pcStack_58 = (char *)0x46e67b;
    iStack_54 = *(int *)(iVar6 + 0x38);
    FUN_00429e60();
    apiStack_68[1] = *(int **)(iVar6 + 0x38);
    pcStack_58 = (char *)0x6;
    apiStack_60[1] = param_2;
    apiStack_60[0] = (int *)local_34;
    apiStack_68[0] = (int *)0x46e690;
    FUN_00429d40();
    apiStack_68[0] = (int *)0x6;
    FUN_00429d40(*(undefined4 *)(iVar6 + 0x78),local_34,(int)param_2 + -1);
    FUN_00429e60(*(undefined4 *)(iVar6 + 0x5c),&local_34,&param_2,&local_28);
    iStack_54 = *(undefined4 *)(iVar6 + 0x5c);
    ppiStack_50 = (int **)local_34;
  }
  else {
    local_20[0] = fVar1 + *(float *)(param_1 + 0x18) + _DAT_005a8dbc;
    local_20[1] = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x1c)) - _DAT_005a8dbc;
    pfVar7 = local_20;
    ppiVar9 = apiStack_68 + 2;
    for (; iVar6 != 0; iVar6 = iVar6 + -1) {
      *ppiVar9 = (int *)*pfVar7;
      pfVar7 = pfVar7 + 1;
      ppiVar9 = ppiVar9 + 1;
    }
    apiStack_68[1] = (int *)0x46e700;
    FUN_004636d0();
    piStack_4c = (int *)0x46e70d;
    FUN_00463b30();
    piStack_4c = (int *)0x46e714;
    puVar4 = operator_new(0x34);
    param_2 = puVar4;
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      *puVar4 = &PTR_LAB_005a8810;
      puVar4[1] = 0;
      piVar2 = puVar4 + 9;
      puVar4[3] = 0;
      puVar4[4] = 0;
      puVar4[5] = 0;
      puVar4[6] = 0;
      puVar4[7] = 0x3f800000;
      local_4._0_1_ = 10;
      local_4._1_3_ = 0;
      *piVar2 = 0;
      puVar4[10] = 0;
      puVar4[0xb] = 0;
      piStack_4c = (int *)0x46e760;
      local_28 = piVar2;
      iVar6 = FUN_00402bf0();
      *piVar2 = iVar6;
      puVar4[10] = iVar6;
      puVar4[0xb] = iVar6 + 8;
      local_4 = CONCAT31(local_4._1_3_,0xb);
      FUN_00402a70();
      *puVar4 = &PTR_FUN_005a8700;
    }
    piStack_4c = (int *)0x0;
    local_20[0] = *(float *)(param_1 + 0x18) + _DAT_005a8dbc;
    local_20[2] = 60.0;
    local_20[3] = 20.0;
    local_4 = 0xffffffff;
    *(undefined4 **)(param_1 + 0x14) = puVar4;
    local_20[1] = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x1c)) - _DAT_005a8dbc;
    pfVar7 = local_20;
    ppiVar9 = apiStack_68 + 2;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *ppiVar9 = (int *)*pfVar7;
      pfVar7 = pfVar7 + 1;
      ppiVar9 = ppiVar9 + 1;
    }
    apiStack_68[1] = (int *)0x46e7d7;
    FUN_004636d0();
    piStack_4c = (int *)0x46e7e4;
    FUN_00463b30();
    piStack_4c = (int *)0x46e7eb;
    pvVar5 = operator_new(0x7c);
    if (pvVar5 == (void *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00463fb0();
    }
    piStack_4c = (int *)0xff;
    ppiStack_50 = (int **)0xff;
    iStack_54 = 0;
    local_20[0] = *(float *)(param_1 + 0x18) + _DAT_005a8e7c;
    local_20[1] = *(float *)(param_1 + 0x1c) + _DAT_005a8f50;
    local_20[2] = 80.0;
    local_20[3] = 20.0;
    *(undefined4 *)(param_1 + 8) = uVar3;
    pfVar7 = local_20;
    ppiVar9 = apiStack_68;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *ppiVar9 = (int *)*pfVar7;
      pfVar7 = pfVar7 + 1;
      ppiVar9 = ppiVar9 + 1;
    }
    FUN_004642f0();
    iVar6 = *(int *)(param_1 + 8);
    if (*(int *)(iVar6 + 0x38) == 0) goto LAB_0046e8d1;
    piStack_4c = (int *)&param_2;
    ppiStack_50 = (int **)&local_34;
    pcStack_58 = (char *)0x46e870;
    iStack_54 = *(int *)(iVar6 + 0x38);
    FUN_00429e60();
    apiStack_68[1] = *(int **)(iVar6 + 0x38);
    pcStack_58 = (char *)0x6;
    apiStack_60[1] = param_2;
    apiStack_60[0] = (int *)local_34;
    apiStack_68[0] = (int *)0x46e885;
    FUN_00429d40();
    apiStack_68[0] = (int *)0x6;
    FUN_00429d40(*(undefined4 *)(iVar6 + 0x78),local_34,(int)param_2 + -1);
    FUN_00429e60(*(undefined4 *)(iVar6 + 0x5c),&local_34,&param_2,&local_28);
    iStack_54 = *(undefined4 *)(iVar6 + 0x5c);
    ppiStack_50 = (int **)local_34;
  }
  pcStack_58 = (char *)0x46e8ce;
  piStack_4c = param_2;
  FUN_00429d40();
LAB_0046e8d1:
  piStack_4c = (int *)0x46e8de;
  FUN_00464240();
  piStack_4c = &local_30;
  iStack_54 = *(undefined4 *)(param_1 + 0x2c);
  ppiStack_50 = (int **)&local_2c;
  pcStack_58 = (char *)0x46e8f6;
  FUN_00429e60();
  apiStack_68[1] = *(int **)(param_1 + 0x2c);
  pcStack_58 = (char *)0x5;
  apiStack_60[1] = (int *)local_30;
  apiStack_60[0] = (int *)local_2c;
  apiStack_68[0] = (int *)0x46e90b;
  FUN_00429d40();
  apiStack_68[0] = &local_24;
  FUN_00429e60(*(undefined4 *)(param_1 + 0x30),&local_2c,&local_30);
  FUN_00429d40(*(undefined4 *)(param_1 + 0x30),local_2c,local_30 + -1,5);
  iVar6 = *(int *)(param_1 + 0x10);
  piStack_4c = (int *)&param_2;
  iStack_54 = *(undefined4 *)(iVar6 + 8);
  ppiStack_50 = &local_28;
  pcStack_58 = (char *)0x46e957;
  FUN_00429e60();
  apiStack_68[1] = *(int **)(iVar6 + 8);
  pcStack_58 = (char *)0x6;
  apiStack_60[1] = param_2;
  apiStack_60[0] = local_28;
  apiStack_68[0] = (int *)0x46e96c;
  FUN_00429d40();
  if (in_stack_00000018 == 0) {
    iVar6 = *(int *)(param_1 + 0xc);
    piStack_4c = &stack0x00000018;
    iStack_54 = *(undefined4 *)(iVar6 + 8);
    ppiStack_50 = &param_2;
    pcStack_58 = (char *)0x46e992;
    FUN_00429e60();
    apiStack_68[1] = *(int **)(iVar6 + 8);
    pcStack_58 = (char *)0x6;
    apiStack_60[1] = (int *)in_stack_00000018;
    apiStack_60[0] = param_2;
    apiStack_68[0] = (int *)0x46e9a7;
    FUN_00429d40();
  }
  ExceptionList = local_c;
  return 1;
}

