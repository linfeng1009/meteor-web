/* Original Meteor.exe static export @ 004b14c0; original sample not executed. */
/* XREF 005a9cd8 DATA */
/* XREF 005aa448 DATA */
/* XREF 005aa5a0 DATA */

undefined4 __fastcall FUN_004b14c0(int *param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  uint uVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined1 *puVar8;
  undefined1 local_36;
  undefined1 local_35;
  int local_34;
  int local_30;
  int *local_2c;
  int *local_28;
  undefined1 local_24 [4];
  void *local_20 [2];
  undefined4 *local_18;
  undefined4 local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a0410;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_2c = param_1;
  FUN_0049d3c0(&local_34,&stack0x00000004);
  if (local_34 == param_1[0xea]) {
    ExceptionList = local_c;
    return 0;
  }
  iVar7 = *(int *)(local_34 + 0x22c);
  if (*(int *)(local_34 + 0x230) != iVar7) {
    local_18 = (undefined4 *)0x0;
    local_14 = 0;
    local_10 = 0;
    iVar6 = *(int *)(local_34 + 0x230);
    local_4 = 0;
    FUN_004608a0((iVar6 - iVar7) + 1);
    local_14 = FUN_004da870(iVar7,iVar6,local_18);
    FUN_00402a70();
    local_4 = 1;
    FUN_004b4cc0(local_20,&local_18);
    puVar2 = local_18;
    uVar3 = local_10 - (int)local_18;
    local_4 = 0xffffffff;
    if ((local_18 != (undefined4 *)0x0) && (uVar3 != 0)) {
      if (uVar3 < 0x81) {
        FUN_00402330();
        *puVar2 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puVar2;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(local_18);
      }
    }
  }
  local_28 = (int *)(local_34 + 0x244);
  if (*local_28 == 0) goto LAB_004b16a5;
  iVar7 = param_1[0xe5];
  bVar1 = true;
  if (*(int *)(iVar7 + 4) != 0) {
    iVar6 = *(int *)(iVar7 + 4);
    do {
      iVar7 = iVar6;
      bVar1 = *local_28 < *(int *)(iVar7 + 0x10);
      if (bVar1) {
        iVar6 = *(int *)(iVar7 + 8);
      }
      else {
        iVar6 = *(int *)(iVar7 + 0xc);
      }
    } while (iVar6 != 0);
  }
  local_30 = iVar7;
  if (bVar1) {
    piVar4 = (int *)FUN_004b48c0(local_24);
    if (local_30 != *piVar4) {
      FUN_0044cf00();
      goto LAB_004b1662;
    }
    puVar8 = &local_36;
    local_36 = 1;
    piVar4 = (int *)FUN_0049ed70(local_24,0,iVar7,local_28);
  }
  else {
LAB_004b1662:
    if (*(int *)(local_30 + 0x10) < *local_28) {
      puVar8 = &local_36;
      local_36 = 1;
      piVar4 = (int *)FUN_0049ed70(local_24,0,iVar7,local_28);
    }
    else {
      puVar8 = &local_35;
      local_35 = 0;
      piVar4 = &local_30;
    }
  }
  FUN_0046ef70(piVar4,puVar8);
  param_1 = local_2c;
LAB_004b16a5:
  (**(code **)(*param_1 + 0x40))(0x4f,&stack0x00000004,4,1);
  uVar5 = (**(code **)(*param_1 + 0xd8))(local_c);
  ExceptionList = local_20[0];
  return uVar5;
}

