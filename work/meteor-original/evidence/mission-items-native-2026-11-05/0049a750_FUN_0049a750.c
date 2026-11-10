/* Original Meteor.exe static export @ 0049a750; original sample not executed. */
/* XREF 00495126 UNCONDITIONAL_CALL */
/* XREF 0049f63f UNCONDITIONAL_CALL */
/* XREF 004ac49c UNCONDITIONAL_CALL */
/* XREF 004bd79a UNCONDITIONAL_CALL */
/* XREF 004aa2e4 UNCONDITIONAL_CALL */
/* XREF 0048bde8 UNCONDITIONAL_CALL */

undefined4 * __thiscall FUN_0049a750(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 local_6c;
  undefined4 local_68;
  int local_64;
  undefined4 *local_60;
  undefined1 local_3c [16];
  undefined1 local_2c [16];
  undefined1 local_1c [16];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puVar5 = param_2;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059f0cc;
  local_c = ExceptionList;
  local_60 = param_2 + 0x13;
  puVar2 = param_2;
  puVar3 = param_1;
  ExceptionList = &local_c;
  for (iVar4 = 0x11; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  local_64 = 0x49a794;
  uVar1 = FUN_0049bdc0();
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  local_60 = (undefined4 *)0x49a7af;
  FUN_00502330();
  local_60 = (undefined4 *)0x49a7b7;
  FUN_00502330();
  local_64 = 0x49a7c3;
  local_60 = (undefined4 *)uVar1;
  FUN_0049d070();
  local_6c = param_1[0x13];
  param_2 = &local_6c;
  local_4 = 0;
  local_68 = param_1[0x14];
  local_64 = param_1[0x15];
  local_60 = (undefined4 *)param_1[0x16];
  puVar2 = (undefined4 *)FUN_0049b180(local_3c);
  puVar3 = (undefined4 *)FUN_0049b160(local_2c);
  FUN_0049e0e0(local_1c,*puVar3,puVar3[1],puVar3[2],puVar3[3],*puVar2,puVar2[1],puVar2[2],puVar2[3])
  ;
  local_4 = 1;
  param_1[0x1b] = puVar5[0x1b];
  local_60 = puVar5 + 0x1c;
  local_64 = 0x49a86a;
  FUN_0049ab40();
  local_60 = puVar5 + 0x2c;
  local_4._0_1_ = 2;
  param_1[0x2b] = puVar5[0x2b];
  local_64 = 0x49a881;
  FUN_0049b2a0();
  local_60 = &param_2;
  local_64 = (int)(puVar5[0x2e] - puVar5[0x2d]) / 0x48;
  local_4._0_1_ = 3;
  local_68 = 0x49a8bb;
  FUN_0049bb50();
  local_68 = puVar5[0x2e];
  local_6c = puVar5[0x2d];
  local_4._0_1_ = 4;
  local_64 = param_1[0x2d];
  local_60 = param_2;
  uVar1 = FUN_0049fa30();
  param_1[0x2e] = uVar1;
  local_60 = puVar5 + 0x30;
  local_4._0_1_ = 5;
  local_64 = 0x49a8fc;
  FUN_0049b2a0();
  param_1[0x1c] = &PTR_FUN_005a9490;
  param_1[0x31] = puVar5[0x31];
  puVar2 = puVar5 + 0x32;
  puVar3 = param_1 + 0x32;
  for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = puVar5 + 0x44;
  puVar3 = param_1 + 0x44;
  for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = puVar5 + 0x56;
  puVar3 = param_1 + 0x56;
  for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = puVar5 + 0x68;
  puVar3 = param_1 + 0x68;
  for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  param_1[0x7a] = puVar5[0x7a];
  param_1[0x7b] = puVar5[0x7b];
  param_1[0x7c] = puVar5[0x7c];
  param_1[0x7d] = puVar5[0x7d];
  param_1[0x7e] = puVar5[0x7e];
  param_1[0x7f] = puVar5[0x7f];
  param_1[0x80] = puVar5[0x80];
  param_1[0x81] = puVar5[0x81];
  param_1[0x82] = puVar5[0x82];
  param_1[0x83] = puVar5[0x83];
  *(undefined1 *)(param_1 + 0x84) = *(undefined1 *)(puVar5 + 0x84);
  *(undefined1 *)((int)param_1 + 0x211) = *(undefined1 *)((int)puVar5 + 0x211);
  param_2 = param_1 + 0x85;
  *(undefined1 *)((int)param_1 + 0x212) = *(undefined1 *)((int)puVar5 + 0x212);
  *param_2 = 0;
  param_1[0x86] = 0;
  param_1[0x87] = 0;
  local_60 = (undefined4 *)puVar5[0x86];
  local_64 = puVar5[0x85];
  local_4._0_1_ = 7;
  local_68 = 0x49aa22;
  FUN_00402ac0();
  param_2 = param_1 + 0x88;
  *param_2 = 0;
  param_1[0x89] = 0;
  param_1[0x8a] = 0;
  local_60 = (undefined4 *)puVar5[0x89];
  local_64 = puVar5[0x88];
  local_4._0_1_ = 9;
  local_68 = 0x49aa4c;
  FUN_00402ac0();
  param_1[0x8b] = puVar5[0x8b];
  param_1[0x8c] = puVar5[0x8c];
  param_1[0x8d] = puVar5[0x8d];
  param_1[0x8e] = puVar5[0x8e];
  param_1[0x8f] = puVar5[0x8f];
  param_2 = param_1 + 0x91;
  param_1[0x90] = puVar5[0x90];
  *param_2 = 0;
  param_1[0x92] = 0;
  param_1[0x93] = 0;
  local_60 = (undefined4 *)puVar5[0x92];
  local_64 = puVar5[0x91];
  local_4._0_1_ = 0xb;
  local_68 = 0x49aabe;
  FUN_00402ac0();
  param_2 = param_1 + 0x94;
  *param_2 = 0;
  param_1[0x95] = 0;
  param_1[0x96] = 0;
  local_60 = (undefined4 *)puVar5[0x95];
  local_4._0_1_ = 0xd;
  local_64 = puVar5[0x94];
  local_68 = 0x49aae8;
  FUN_00402ac0();
  param_1[0x97] = puVar5[0x97];
  local_60 = puVar5 + 0xa5;
  puVar5 = puVar5 + 0x98;
  puVar2 = param_1 + 0x98;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar2 = puVar2 + 1;
  }
  local_4 = CONCAT31(local_4._1_3_,0xe);
  local_64 = 0x49ab1e;
  FUN_0049ba80();
  ExceptionList = local_c;
  return param_1;
}

