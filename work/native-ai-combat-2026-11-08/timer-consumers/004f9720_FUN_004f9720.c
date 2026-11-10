/* Original Meteor.exe read-only export. Sample not executed. */

undefined4 FUN_004f9720(int param_1)

{
  char cVar1;
  int iVar2;
  char **ppcVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  char *pcVar9;
  undefined4 *puVar10;
  char *pcVar11;
  bool bVar12;
  undefined1 local_2e;
  undefined1 local_2d;
  int local_2c;
  char *local_28;
  int local_24;
  int local_20;
  undefined4 *local_1c;
  int local_18;
  int local_14;
  int local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a3a09;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_00402b70(&local_2e,8);
  local_4 = 0;
  FUN_00402a70();
  local_4 = 1;
  FUN_004024a0(&local_2d);
  local_4 = 2;
  ppcVar3 = (char **)(**(int **)(param_1 + 8) + 0xc);
  if (ppcVar3 != &local_28) {
    FUN_00403200(*ppcVar3,*(undefined4 *)(**(int **)(param_1 + 8) + 0x10));
  }
  iVar2 = *(int *)(*(int *)(param_1 + 8) + 4);
  if ((*(int *)(iVar2 + 4) < 7) || (8 < *(int *)(iVar2 + 4))) {
    local_10 = *(int *)(iVar2 + 8);
  }
  else if ((undefined4 **)(iVar2 + 0xc) != &local_1c) {
    iVar6 = *(int *)(iVar2 + 0x10);
    puVar7 = *(undefined4 **)(iVar2 + 0xc);
    uVar5 = local_18 - (int)local_1c;
    uVar4 = iVar6 - (int)puVar7;
    if (uVar5 < uVar4) {
      puVar8 = puVar7;
      puVar10 = local_1c;
      for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar10 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar10 = puVar10 + 1;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined1 *)puVar10 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      }
      FUN_00403490((undefined1 *)((local_18 - (int)local_1c) + (int)puVar7),iVar6);
    }
    else {
      puVar8 = local_1c;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar5 = uVar4 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      FUN_00402b30((undefined1 *)(uVar4 + (int)local_1c),local_18);
    }
  }
  iVar2 = DAT_0066629c;
  uVar4 = 0xffffffff;
  pcVar9 = s_pause_005c9b74;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  iVar6 = ~uVar4 - 1;
  if (local_24 - (int)local_28 == iVar6) {
    bVar12 = true;
    pcVar9 = local_28;
    pcVar11 = s_pause_005c9b74;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar12 = *pcVar9 == *pcVar11;
      pcVar9 = pcVar9 + 1;
      pcVar11 = pcVar11 + 1;
    } while (bVar12);
    if (bVar12) {
      local_10 = local_10 * 2;
    }
  }
  iVar6 = *(int *)(DAT_0066629c + 0x14);
  if (iVar6 == *(int *)(DAT_0066629c + 0x18)) {
    FUN_004fa240(iVar6,&local_28);
  }
  else {
    local_4 = CONCAT31(local_4._1_3_,3);
    local_2c = iVar6;
    if (iVar6 != 0) {
      FUN_004fa650(&local_28);
    }
    *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 0x1c;
  }
  uVar4 = local_14 - (int)local_1c;
  local_4 = 0xffffffff;
  if ((local_1c != (undefined4 *)0x0) && (uVar4 != 0)) {
    if (uVar4 < 0x81) {
      FUN_00402330();
      *local_1c = *(undefined4 *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = local_1c;
      FUN_00443330();
    }
    else {
      FUN_005089fd(local_1c);
    }
  }
  if ((local_28 != (char *)0x0) && (local_20 - (int)local_28 != 0)) {
    FUN_00402e90(local_28,local_20 - (int)local_28);
  }
  ExceptionList = local_c;
  return 1;
}

