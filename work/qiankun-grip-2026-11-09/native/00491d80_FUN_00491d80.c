/* Original Meteor.exe static export @ 00491d80; original sample not executed. */
/* XREF 005a91fc DATA */

void __thiscall FUN_00491d80(int *param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  undefined4 uVar5;
  void *pvVar6;
  undefined4 *puVar7;
  int *unaff_EBX;
  int iVar8;
  bool bVar9;
  int local_40;
  void *local_3c;
  int iStack_38;
  uint uStack_34;
  int iStack_30;
  undefined1 auStack_2c [4];
  char cStack_28;
  char cStack_20;
  uint uStack_1c;
  uint uStack_18;
  uint uStack_14;
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059e786;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  local_3c = operator_new(0x1d0);
  iVar8 = 0;
  local_4 = 0;
  if (local_3c == (void *)0x0) {
    local_40 = 0;
  }
  else {
    local_40 = FUN_005678a0();
  }
  iVar1 = local_40;
  local_4 = 0xffffffff;
  iVar4 = (**(code **)(*param_1 + 300))(param_2);
  if (iVar4 == 0) {
    ExceptionList = pvStack_10;
    return;
  }
  if (iVar4 == 0x65c) {
    ExceptionList = pvStack_10;
    return;
  }
  uVar5 = FUN_005569b0(s_d_wpnR_005c92cc);
  iVar4 = FUN_005598c0(uVar5);
  if (iVar4 == 0) {
    ExceptionList = pvStack_10;
    return;
  }
  FUN_0056b230(iVar1);
  FUN_0047b310(iVar1);
  pvVar6 = operator_new(0x78);
  puVar3 = param_2;
  puStack_8 = (undefined1 *)0x1;
  if (pvVar6 != (void *)0x0) {
    iVar8 = FUN_004e4f70(iVar1,*param_2 >> 0xc,0);
  }
  *(uint *)(iVar8 + 0x6c) = puVar3[4];
  *(uint *)(iVar8 + 0x70) = puVar3[5];
  puStack_8 = (undefined1 *)0xffffffff;
  *(uint *)(iVar8 + 0x74) = puVar3[6];
  FUN_00549a90(0,0);
  FUN_0047b740();
  uStack_18 = puVar3[5];
  uStack_14 = puVar3[6];
  uStack_1c = puVar3[4];
  FUN_0047ec40();
  FUN_00477200();
  FUN_00478960(&uStack_1c);
  FUN_00477c10(3,puVar3 + 1);
  uStack_34 = *puVar3;
  iStack_30 = iVar8;
  FUN_0049c910(auStack_2c,&uStack_34);
  if (cStack_28 != '\0') {
    ExceptionList = pvStack_10;
    return;
  }
  FUN_0049d3c0(&local_40,puVar3);
  if (*(undefined4 **)(local_40 + 0x14) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(local_40 + 0x14))(1);
  }
  iVar1 = param_1[0x847];
  puVar7 = (undefined4 *)FUN_0048ea60(local_40,iVar1 + 4,iVar1 + 8,iVar1 + 0xc);
  FUN_00402330();
  *puVar7 = DAT_005d59b0;
  DAT_005d59e8 = 0;
  bVar9 = true;
  DAT_005d59b0 = puVar7;
  param_1[0x848] = param_1[0x848] + -1;
  pvVar6 = (void *)*puVar3;
  iVar1 = param_1[0x847];
  iVar4 = iVar1;
  iVar2 = *(int *)(iVar1 + 4);
  while (iVar2 != 0) {
    bVar9 = pvVar6 < *(void **)(iVar2 + 0x10);
    iVar4 = iVar2;
    if (bVar9) {
      iVar2 = *(int *)(iVar2 + 8);
    }
    else {
      iVar2 = *(int *)(iVar2 + 0xc);
    }
  }
  param_2 = (uint *)iVar4;
  local_3c = pvVar6;
  iStack_38 = iVar8;
  if (bVar9) {
    if (iVar4 == *(int *)(iVar1 + 8)) goto LAB_00491fa3;
    FUN_0044cf00();
  }
  if (pvVar6 <= *(void **)((int)param_2 + 0x10)) {
    FUN_0046ef70(&param_2,&stack0x00000000);
    if (cStack_20 != '\0') {
      ExceptionList = pvStack_10;
      return;
    }
    if (unaff_EBX == (int *)0x0) {
      ExceptionList = pvStack_10;
      return;
    }
    (**(code **)(*unaff_EBX + 8))(1);
    ExceptionList = pvStack_10;
    return;
  }
LAB_00491fa3:
  FUN_0049e870(&stack0xffffffbc,0,iVar4,&local_3c);
  ExceptionList = pvStack_10;
  return;
}

