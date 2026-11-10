/* Original Meteor.exe static export @ 0046cc00; original sample not executed. */
/* XREF 0043561d UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall
FUN_0046cc00(int param_1,float param_2,float param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  void *pvVar4;
  undefined4 *puVar5;
  int iVar6;
  float *pfVar7;
  undefined4 *puVar8;
  float *pfVar9;
  undefined4 **ppuVar10;
  undefined4 *puStack_6c;
  float fStack_68;
  char *pcStack_64;
  undefined4 *local_40;
  undefined4 local_3c;
  undefined4 *local_38;
  undefined4 *local_34 [2];
  undefined4 *local_2c;
  undefined4 *local_28;
  float local_20 [5];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059cc9a;
  local_c = ExceptionList;
  puVar8 = (undefined4 *)(param_1 + 0x28);
  puVar5 = (undefined4 *)register0x00000010;
  ExceptionList = &local_c;
  for (iVar6 = 5; puVar5 = puVar5 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar5;
    puVar8 = puVar8 + 1;
  }
  FUN_00429990();
  __ftol();
  __ftol();
  pcStack_64 = s_passboard_005c7be0;
  fStack_68 = 6.501782e-39;
  FUN_00429aa0();
  fStack_68 = 0.0;
  *(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) * _DAT_005a8e18;
  *(float *)(param_1 + 0x34) = *(float *)(param_1 + 0x34) * _DAT_005a8e18;
  puStack_6c = (undefined4 *)0x46cc71;
  uVar3 = FUN_00429c30();
  *(undefined4 *)(param_1 + 0x3c) = uVar3;
  puStack_6c = (undefined4 *)0x46cc85;
  puStack_6c = (undefined4 *)__ftol();
  __ftol();
  FUN_00429d00();
  FUN_00429d80(*(undefined4 *)(param_1 + 0x3c),0x72,0xfd,0x51,1);
  FUN_00429de0(*(undefined4 *)(param_1 + 0x3c),0);
  param_2 = DAT_005c7b60 * (float)_DAT_005a8b18;
  FUN_00429dc0();
  local_20[0] = *(float *)(param_1 + 0x28) + _DAT_005a8ef4;
  local_20[4] = 1.0;
  local_20[2] = 90.0;
  local_20[3] = 18.0;
  local_20[1] = *(float *)(param_1 + 0x2c) + _DAT_005a8ef0;
  pcStack_64 = (char *)0x46cd15;
  pvVar4 = operator_new(0x7c);
  if (pvVar4 == (void *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_00463fb0();
  }
  pfVar7 = local_20;
  pfVar9 = (float *)&stack0xffffff8c;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar9 = *pfVar7;
    pfVar7 = pfVar7 + 1;
    pfVar9 = pfVar9 + 1;
  }
  *(undefined4 *)(param_1 + 8) = uVar3;
  FUN_004642f0();
  iVar6 = *(int *)(param_1 + 8);
  if (*(int *)(iVar6 + 0x38) != 0) {
    pcStack_64 = (char *)0x46cd70;
    FUN_00429e60();
    pcStack_64 = (char *)0x6;
    fStack_68 = param_2;
    puStack_6c = local_40;
    FUN_00429d40();
    FUN_00429d40(*(undefined4 *)(iVar6 + 0x78),local_40,(int)param_2 + -1);
    FUN_00429e60(*(undefined4 *)(iVar6 + 0x5c),&local_40,&param_2,local_34);
    pcStack_64 = (char *)0x46cdd1;
    FUN_00429d40();
  }
  local_20[1] = local_20[1] + _DAT_005a8dbc;
  pvVar4 = operator_new(0x7c);
  if (pvVar4 == (void *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_00463fb0();
  }
  pfVar7 = local_20;
  pfVar9 = (float *)&stack0xffffff8c;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar9 = *pfVar7;
    pfVar7 = pfVar7 + 1;
    pfVar9 = pfVar9 + 1;
  }
  *(undefined4 *)(param_1 + 0xc) = uVar3;
  FUN_004642f0();
  iVar6 = *(int *)(param_1 + 0xc);
  if (*(int *)(iVar6 + 0x38) != 0) {
    pcStack_64 = (char *)0x46ce44;
    FUN_00429e60();
    pcStack_64 = (char *)0x6;
    fStack_68 = param_2;
    puStack_6c = local_40;
    FUN_00429d40();
    FUN_00429d40(*(undefined4 *)(iVar6 + 0x78),local_40,(int)param_2 + -1);
    FUN_00429e60(*(undefined4 *)(iVar6 + 0x5c),&local_40,&param_2,local_34);
    pcStack_64 = (char *)0x46cea5;
    FUN_00429d40();
  }
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x74) = 1;
  puVar5 = operator_new(0x34);
  local_2c = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    local_4 = 1;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    FUN_004024a0();
    *puVar5 = &PTR_FUN_005a8700;
  }
  local_4 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x10) = puVar5;
  puVar5 = operator_new(0x34);
  local_2c = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    local_4 = 3;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    FUN_004024a0();
    *puVar5 = &PTR_FUN_005a8700;
  }
  fVar1 = *(float *)(param_1 + 0x30) * _DAT_005a83e8;
  fVar2 = *(float *)(param_1 + 0x38) * _DAT_005a8db8;
  local_4 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x14) = puVar5;
  param_6 = 0x3f800000;
  param_4 = 0x42700000;
  param_5 = 0x41a00000;
  param_2 = (fVar1 - fVar2) * _DAT_005a83e8 + *(float *)(param_1 + 0x28);
  param_3 = (*(float *)(param_1 + 0x2c) + *(float *)(param_1 + 0x34)) - _DAT_005a8dbc;
  ppuVar10 = &puStack_6c;
  puVar5 = (undefined4 *)register0x00000010;
  for (iVar6 = 5; puVar5 = puVar5 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar10 = (undefined4 *)*puVar5;
    ppuVar10 = ppuVar10 + 1;
  }
  FUN_004636d0();
  FUN_00463b30();
  param_2 = *(float *)(param_1 + 0x30) * _DAT_005a83e8 + param_2;
  ppuVar10 = &puStack_6c;
  puVar5 = (undefined4 *)register0x00000010;
  for (iVar6 = 5; puVar5 = puVar5 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar10 = (undefined4 *)*puVar5;
    ppuVar10 = ppuVar10 + 1;
  }
  FUN_004636d0();
  FUN_00463b30();
  pcStack_64 = (char *)0x46d02a;
  FUN_00429e60();
  pcStack_64 = (char *)0x5;
  fStack_68 = (float)local_3c;
  puStack_6c = local_38;
  FUN_00429d40();
  iVar6 = *(int *)(param_1 + 0x10);
  FUN_00429e60(*(undefined4 *)(iVar6 + 8),local_34,&param_2);
  FUN_00429d40(*(undefined4 *)(iVar6 + 8),local_34[0],param_2,6);
  pcStack_64 = (char *)0x46d090;
  FUN_00429e60();
  pcStack_64 = (char *)0x6;
  fStack_68 = param_2;
  puStack_6c = local_34[0];
  FUN_00429d40();
  local_20[0] = *(float *)(param_1 + 0x28) + _DAT_005a8eec;
  local_20[2] = 40.0;
  local_20[3] = 20.0;
  local_20[1] = *(float *)(param_1 + 0x2c) + _DAT_005a8ee8;
  puVar5 = operator_new(0x34);
  local_4 = 4;
  local_28 = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    local_4 = 5;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    FUN_004024a0();
    *puVar5 = &PTR_FUN_005a8700;
  }
  pfVar7 = local_20;
  ppuVar10 = &puStack_6c;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar10 = (undefined4 *)*pfVar7;
    pfVar7 = pfVar7 + 1;
    ppuVar10 = ppuVar10 + 1;
  }
  local_4 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x20) = puVar5;
  FUN_004636d0();
  FUN_00463b30();
  local_20[1] = local_20[1] - _DAT_005a8dbc;
  puVar5 = operator_new(0x34);
  local_4 = 6;
  local_28 = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    local_4 = 7;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    FUN_004024a0();
    *puVar5 = &PTR_FUN_005a8700;
  }
  pfVar7 = local_20;
  ppuVar10 = &puStack_6c;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar10 = (undefined4 *)*pfVar7;
    pfVar7 = pfVar7 + 1;
    ppuVar10 = ppuVar10 + 1;
  }
  local_4 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x24) = puVar5;
  FUN_004636d0();
  FUN_00463b30();
  pcStack_64 = (char *)0x46d206;
  FUN_00429e60();
  pcStack_64 = (char *)0x6;
  fStack_68 = param_2;
  puStack_6c = local_34[0];
  FUN_00429d40();
  iVar6 = *(int *)(param_1 + 0x24);
  FUN_00429e60(*(undefined4 *)(iVar6 + 8),local_34,&param_2);
  FUN_00429d40(*(undefined4 *)(iVar6 + 8),local_34[0],param_2,6);
  puVar5 = operator_new(0x34);
  local_28 = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    local_2c = puVar5 + 9;
    local_4._0_1_ = 9;
    local_4._1_3_ = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    FUN_00402b70();
    local_4 = CONCAT31(local_4._1_3_,10);
    FUN_00402a70();
    *puVar5 = &PTR_FUN_005a8700;
  }
  local_4 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x18) = puVar5;
  puVar5 = operator_new(0x34);
  local_4 = 0xb;
  local_28 = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    local_4 = 0xc;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    FUN_004024a0();
    *puVar5 = &PTR_FUN_005a8700;
  }
  *(undefined4 **)(param_1 + 0x1c) = puVar5;
  param_6 = 0x3f800000;
  param_4 = 0x40e00000;
  param_5 = 0x41a80000;
  param_2 = 423.0;
  param_3 = 238.0;
  ppuVar10 = &puStack_6c;
  puVar5 = (undefined4 *)register0x00000010;
  for (iVar6 = 5; puVar5 = puVar5 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar10 = (undefined4 *)*puVar5;
    ppuVar10 = ppuVar10 + 1;
  }
  FUN_004636d0();
  param_2 = 253.0;
  ppuVar10 = &puStack_6c;
  puVar5 = (undefined4 *)register0x00000010;
  for (iVar6 = 5; puVar5 = puVar5 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar10 = (undefined4 *)*puVar5;
    ppuVar10 = ppuVar10 + 1;
  }
  FUN_004636d0();
  pcStack_64 = (char *)0x46d39a;
  FUN_00429e60();
  pcStack_64 = (char *)0x5;
  fStack_68 = (float)local_3c;
  puStack_6c = local_38;
  FUN_00429d40();
  iVar6 = *(int *)(param_1 + 0x18);
  FUN_00429e60(*(undefined4 *)(iVar6 + 8),local_34,&param_2);
  FUN_00429d40(*(undefined4 *)(iVar6 + 8),local_34[0],param_2,6);
  pcStack_64 = (char *)0x46d400;
  FUN_00429e60();
  pcStack_64 = (char *)0x6;
  fStack_68 = (float)local_40;
  puStack_6c = local_2c;
  FUN_00429d40();
  ExceptionList = local_c;
  return 1;
}

