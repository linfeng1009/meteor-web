/* Original Meteor.exe static export @ 0046b910; original sample not executed. */
/* XREF 00435477 UNCONDITIONAL_CALL */
/* XREF 00470c0c UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0046b910(int param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  float *pfVar7;
  undefined4 *puVar8;
  undefined4 **ppuVar9;
  undefined4 *puStack_60;
  int iStack_5c;
  char *pcStack_58;
  undefined4 uStack_54;
  undefined4 **ppuStack_50;
  int *piStack_4c;
  int local_34;
  undefined4 *local_30;
  undefined1 local_2c [4];
  undefined4 *local_28;
  undefined4 *local_24;
  float local_20 [5];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059cb96;
  local_c = ExceptionList;
  puVar8 = (undefined4 *)(param_1 + 0x10);
  puVar5 = (undefined4 *)register0x00000010;
  ExceptionList = &local_c;
  for (iVar6 = 5; puVar5 = puVar5 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar5;
    puVar8 = puVar8 + 1;
  }
  *(undefined4 *)(param_1 + 0x54) = 3;
  *(undefined4 *)(param_1 + 0x50) = 0;
  piStack_4c = (int *)0x46b94e;
  FUN_00429990();
  piStack_4c = (int *)0x46b956;
  piStack_4c = (int *)__ftol();
  ppuStack_50 = (undefined4 **)0x46b95f;
  ppuStack_50 = (undefined4 **)__ftol();
  uStack_54 = 0;
  pcStack_58 = s_gialog_bmp_005c7bcc;
  iStack_5c = 0x46b96b;
  FUN_00429aa0();
  iStack_5c = 0;
  puStack_60 = (undefined4 *)0x46b971;
  uVar3 = FUN_00429c30();
  *(undefined4 *)(param_1 + 0x4c) = uVar3;
  puStack_60 = (undefined4 *)0x46b97e;
  puStack_60 = (undefined4 *)__ftol();
  uVar4 = __ftol();
  FUN_00429d00(uVar3,uVar4);
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x18) * _DAT_005a8e18;
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x1c) * _DAT_005a8e18;
  FUN_00429dc0(*(undefined4 *)(param_1 + 0x4c),0x3f200000,0x3f200000);
  FUN_00429990(0);
  uVar3 = __ftol();
  uVar3 = __ftol(uVar3);
  FUN_00429b80(1,1,1,uVar3);
  piStack_4c = (int *)0x46b9e5;
  uVar3 = FUN_00429c30();
  *(undefined4 *)(param_1 + 0x24) = uVar3;
  piStack_4c = (int *)0x46b9f2;
  piStack_4c = (int *)__ftol();
  ppuStack_50 = (undefined4 **)0x46b9fb;
  ppuStack_50 = (undefined4 **)__ftol();
  pcStack_58 = (char *)0x46ba02;
  uStack_54 = uVar3;
  FUN_00429d00();
  pcStack_58 = (char *)0x1;
  iStack_5c = 0;
  puStack_60 = (undefined4 *)0x0;
  FUN_00429d80(*(undefined4 *)(param_1 + 0x24),0);
  puVar5 = operator_new(0x34);
  local_28 = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    local_24 = puVar5 + 9;
    piStack_4c = &param_2;
    local_4._0_1_ = 1;
    local_4._1_3_ = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    ppuStack_50 = (undefined4 **)0x46ba5e;
    FUN_00402b70();
    local_4 = CONCAT31(local_4._1_3_,2);
    FUN_00402a70();
    *puVar5 = &PTR_FUN_005a8700;
  }
  local_4 = 0xffffffff;
  *(undefined4 **)(param_1 + 8) = puVar5;
  piStack_4c = (int *)0x46ba86;
  puVar5 = operator_new(0x34);
  local_24 = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    local_28 = puVar5 + 9;
    piStack_4c = &param_2;
    local_4._0_1_ = 4;
    local_4._1_3_ = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    ppuStack_50 = (undefined4 **)0x46bad1;
    FUN_00402b70();
    local_4 = CONCAT31(local_4._1_3_,5);
    FUN_00402a70();
    *puVar5 = &PTR_FUN_005a8700;
  }
  fVar1 = *(float *)(param_1 + 0x18) * _DAT_005a83e8;
  fVar2 = *(float *)(param_1 + 0x20) * _DAT_005a8db8;
  piStack_4c = (int *)0x0;
  *(undefined4 **)(param_1 + 0xc) = puVar5;
  local_20[4] = 1.0;
  local_20[2] = 60.0;
  local_20[3] = 20.0;
  local_4 = 0xffffffff;
  local_20[0] = (fVar1 - fVar2) * _DAT_005a83e8 + *(float *)(param_1 + 0x10);
  local_20[1] = (*(float *)(param_1 + 0x1c) + *(float *)(param_1 + 0x14)) - _DAT_005a8dbc;
  pfVar7 = local_20;
  ppuVar9 = &puStack_60;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar9 = (undefined4 *)*pfVar7;
    pfVar7 = pfVar7 + 1;
    ppuVar9 = ppuVar9 + 1;
  }
  FUN_004636d0();
  piStack_4c = (int *)0x46bb62;
  FUN_00463b30();
  piStack_4c = (int *)0x0;
  local_20[0] = *(float *)(param_1 + 0x18) * _DAT_005a83e8 + local_20[0];
  pfVar7 = local_20;
  ppuVar9 = &puStack_60;
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppuVar9 = (undefined4 *)*pfVar7;
    pfVar7 = pfVar7 + 1;
    ppuVar9 = ppuVar9 + 1;
  }
  FUN_004636d0();
  piStack_4c = (int *)0x46bb9a;
  FUN_00463b30();
  piStack_4c = &local_34;
  uStack_54 = *(undefined4 *)(param_1 + 0x24);
  ppuStack_50 = &local_30;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  pcStack_58 = (char *)0x46bbb5;
  FUN_00429e60();
  pcStack_58 = (char *)0x5;
  iStack_5c = local_34;
  puStack_60 = local_30;
  FUN_00429d40(*(undefined4 *)(param_1 + 0x24));
  FUN_00429e60(*(undefined4 *)(param_1 + 0x4c),&local_30,&local_34,local_2c);
  FUN_00429d40(*(undefined4 *)(param_1 + 0x4c),local_30,local_34 + -1,5);
  iVar6 = *(int *)(param_1 + 8);
  piStack_4c = &param_2;
  uStack_54 = *(undefined4 *)(iVar6 + 8);
  ppuStack_50 = &local_28;
  pcStack_58 = (char *)0x46bc16;
  FUN_00429e60();
  pcStack_58 = (char *)0x6;
  iStack_5c = param_2;
  puStack_60 = local_28;
  FUN_00429d40(*(undefined4 *)(iVar6 + 8));
  iVar6 = *(int *)(param_1 + 0xc);
  FUN_00429e60(*(undefined4 *)(iVar6 + 8),&local_28,&param_2,&local_24);
  FUN_00429d40(*(undefined4 *)(iVar6 + 8),local_28,param_2,6);
  ExceptionList = local_c;
  return 1;
}

