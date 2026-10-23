/* Meteor.exe original x86 @ 004d2900 */
/* Caller: 004d289e */

void __thiscall FUN_004d2900(int *param_1,undefined4 param_2)

{
  char *pcVar1;
  char cVar2;
  void *pvVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  undefined4 *puVar11;
  undefined4 *local_b0;
  undefined4 *local_ac;
  undefined1 uStack_a5;
  undefined4 local_a4;
  int local_a0;
  int *local_9c;
  undefined4 **ppuStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined **local_88 [10];
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 *puStack_58;
  undefined4 *puStack_54;
  undefined4 *puStack_4c;
  int iStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined1 local_18 [4];
  short sStack_14;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a1c4e;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  local_9c = param_1;
  pvVar3 = _malloc(0x2800);
  uVar4 = FUN_0050be91(param_2,0x8000);
  local_a4 = uVar4;
  FUN_0050b997(uVar4,pvVar3,0x30);
  FUN_0050b997(uVar4,local_18,*(short *)((int)pvVar3 + 0x2e) * 0xc);
  FUN_0050b997(uVar4,pvVar3,0x2800);
  iVar8 = *param_1;
  local_a0 = *(int *)(iVar8 + 4);
  iVar6 = *(int *)(iVar8 + 8);
  local_b0 = (undefined4 *)FUN_004d3930(iVar6,iVar6,local_a0);
  local_ac = *(undefined4 **)(iVar8 + 8);
  if (local_b0 != local_ac) {
    do {
      (**(code **)*local_b0)(0);
      local_b0 = local_b0 + 0x12;
    } while (local_b0 != local_ac);
  }
  iVar6 = (int)((ulonglong)((longlong)(iVar6 - local_a0) * -0x38e38e39) >> 0x20);
  *(int *)(iVar8 + 8) = *(int *)(iVar8 + 8) + ((iVar6 >> 4) - (iVar6 >> 0x1f)) * 0x48;
  FUN_00492000();
  uStack_4 = 0;
  FUN_005005b0(&uStack_a5);
  local_88[0] = &PTR_FUN_005a9488;
  uStack_4 = 1;
  local_ac = (undefined4 *)0x0;
  puVar7 = (undefined4 *)0x0;
  if (0 < sStack_14) {
    do {
      uStack_5c = *(undefined4 *)((int)pvVar3 + (int)puVar7);
      uStack_60 = *(undefined4 *)((int)pvVar3 + (int)(puVar7 + 1));
      uVar5 = 0xffffffff;
      iVar8 = *(int *)((int)pvVar3 + (int)(puVar7 + 2));
      pcVar1 = (char *)((int)pvVar3 + (int)(puVar7 + 3));
      pcVar10 = pcVar1;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar2 != '\0');
      FUN_00403200(pcVar1,pcVar1 + (~uVar5 - 1));
      iVar8 = (int)(puVar7 + 3) + iVar8;
      uVar5 = 0xffffffff;
      iVar6 = *(int *)((int)pvVar3 + iVar8);
      iVar8 = iVar8 + 4;
      pcVar1 = (char *)((int)pvVar3 + iVar8);
      pcVar10 = pcVar1;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar2 != '\0');
      FUN_00403200(pcVar1,pcVar1 + (~uVar5 - 1));
      iVar8 = iVar8 + iVar6;
      uVar5 = 0xffffffff;
      iVar6 = *(int *)((int)pvVar3 + iVar8);
      iVar8 = iVar8 + 4;
      pcVar1 = (char *)((int)pvVar3 + iVar8);
      pcVar10 = pcVar1;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar2 != '\0');
      FUN_00403200(pcVar1,pcVar1 + (~uVar5 - 1));
      iVar8 = iVar8 + iVar6;
      iVar6 = *(int *)((int)pvVar3 + iVar8);
      iVar8 = iVar8 + 4;
      uStack_94 = 0;
      uStack_90 = 0;
      uStack_8c = 0;
      FUN_004d2dd0(iVar6,&uStack_94);
      iVar9 = iVar8 + iVar6 * 0xc;
      puVar7 = (undefined4 *)((int)pvVar3 + iVar8);
      puVar11 = puStack_58;
      for (uVar5 = iVar6 * 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar11 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar11 = puVar11 + 1;
      }
      iVar6 = iVar9 + 4;
      for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined1 *)puVar11 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar11 = (undefined4 *)((int)puVar11 + 1);
      }
      iVar8 = *(int *)((int)pvVar3 + iVar9);
      uStack_40 = 0;
      uStack_3c = 0;
      uStack_38 = 0;
      uStack_34 = 0;
      uStack_30 = 0;
      uStack_2c = 0;
      uStack_28 = 0;
      uStack_24 = 0;
      uStack_20 = 0;
      uStack_1c = 0;
      FUN_004d2d20(iVar8,&uStack_40);
      local_b0 = (undefined4 *)(iVar6 + iVar8 * 0x28);
      puVar7 = (undefined4 *)((int)pvVar3 + iVar6);
      puVar11 = puStack_4c;
      for (iVar8 = (iVar8 * 5 & 0x1fffffffU) << 1; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar11 = puVar11 + 1;
      }
      for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined1 *)puVar11 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar11 = (undefined4 *)((int)puVar11 + 1);
      }
      iVar8 = *local_9c;
      iVar6 = *(int *)(iVar8 + 8);
      if (iVar6 == *(int *)(iVar8 + 0xc)) {
        FUN_004d3690(iVar6,local_88);
      }
      else {
        uStack_4._0_1_ = 2;
        local_a0 = iVar6;
        ppuStack_98 = (undefined4 **)iVar6;
        if (iVar6 != 0) {
          FUN_004d3b70(local_88);
        }
        uStack_4 = CONCAT31(uStack_4._1_3_,1);
        *(int *)(iVar8 + 8) = *(int *)(iVar8 + 8) + 0x48;
      }
      FUN_004d28b0(local_a4,&local_b0,pvVar3);
      local_ac = (undefined4 *)((int)local_ac + 1);
      puVar7 = local_b0;
    } while ((int)local_ac < (int)sStack_14);
  }
  FUN_0050b6c7(local_a4);
  FUN_005089fd(pvVar3);
  iVar8 = (iStack_44 - (int)puStack_4c) / 0x28;
  uStack_4 = 3;
  if (iVar8 != 0) {
    uVar5 = iVar8 * 0x28;
    if (uVar5 < 0x81) {
      FUN_00402330();
      *puStack_4c = *(undefined4 *)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4) = puStack_4c;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(puStack_4c);
    }
  }
  local_88[0] = &PTR_FUN_005a94e4;
  ppuStack_98 = &puStack_58;
  uStack_4._0_1_ = 7;
  uStack_4._1_3_ = 0;
  for (puVar7 = puStack_58; puVar7 != puStack_54; puVar7 = puVar7 + 3) {
    FUN_004d4a40(puVar7);
  }
  uStack_4._0_1_ = 6;
  FUN_0049b270();
  uStack_4._0_1_ = 5;
  FUN_00402bd0();
  uStack_4 = CONCAT31(uStack_4._1_3_,4);
  FUN_004026e0();
  uStack_4 = 0xffffffff;
  FUN_004026e0();
  ExceptionList = pvStack_c;
  return;
}

