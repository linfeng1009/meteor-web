/* Original Meteor.exe static export @ 004bfc00; original sample not executed. */
/* XREF 004bfb50 UNCONDITIONAL_CALL */
/* XREF 004f9d76 UNCONDITIONAL_CALL */

undefined1 FUN_004bfc00(int param_1)

{
  int *piVar1;
  char cVar2;
  void *pvVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int *unaff_EBP;
  int iVar9;
  char *pcVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  char *pcVar13;
  undefined4 *puVar14;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_50;
  char local_4c [40];
  void *pvStack_24;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a12cb;
  local_c = ExceptionList;
  if (param_1 == 0) {
    return 0;
  }
  ExceptionList = &local_c;
  local_50 = FUN_00487830();
  if (*(int *)(local_50 + 0x212c) == 0) {
    ExceptionList = local_c;
    return 0;
  }
  pvVar3 = operator_new(0x4b0);
  local_4 = 0;
  if (pvVar3 == (void *)0x0) {
    piVar4 = (int *)0x0;
  }
  else {
    piVar4 = (int *)FUN_00500840();
  }
  local_4 = 0xffffffff;
  if (piVar4 == (int *)0x0) {
    ExceptionList = local_c;
    return 0;
  }
  FUN_00508ae6(local_4c,s_Level__s_pst_005c9b50,param_1);
  cVar2 = FUN_004f8950(local_4c);
  if (cVar2 == '\0') {
    ExceptionList = local_c;
    return 0;
  }
  uVar7 = 0xffffffff;
  piVar1 = piVar4 + 0x109;
  pcVar13 = local_4c;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar2 = *pcVar13;
    pcVar13 = pcVar13 + 1;
  } while (cVar2 != '\0');
  pcVar13 = (char *)*piVar1;
  uVar5 = (int)(local_4c + (~uVar7 - 1)) - (int)local_4c;
  uVar8 = piVar4[0x10a] - (int)pcVar13;
  if (uVar8 < uVar5) {
    pcVar10 = local_4c;
    for (uVar5 = uVar8 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar13 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar13 = pcVar13 + 1;
    }
    FUN_00403490(local_4c + (piVar4[0x10a] - *piVar1),local_4c + (~uVar7 - 1));
  }
  else {
    pcVar10 = local_4c;
    for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar7 = uVar5 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar13 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar13 = pcVar13 + 1;
    }
    iVar6 = piVar4[0x10a];
    iVar9 = *piVar1 + uVar5;
    if (iVar9 != iVar6) {
      FUN_005092c0(iVar9,iVar6,1);
      piVar4[0x10a] = piVar4[0x10a] + (iVar9 - iVar6);
    }
  }
  local_58 = 1;
  local_60 = 4;
  param_1 = 0;
  local_5c = 0;
  iVar6 = FUN_00571660(&DAT_005c9b48);
  if (iVar6 != 0) {
    iVar6 = FUN_00571660(&DAT_005c9b48);
    piVar1 = piVar4 + 0x106;
    if ((int *)(iVar6 + 0xc) != piVar1) {
      iVar9 = *(int *)(iVar6 + 0x10);
      puVar11 = *(undefined4 **)(iVar6 + 0xc);
      puVar14 = (undefined4 *)*piVar1;
      uVar7 = iVar9 - (int)puVar11;
      uVar5 = piVar4[0x107] - (int)puVar14;
      if (uVar5 < uVar7) {
        puVar12 = puVar11;
        for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar14 = *puVar12;
          puVar12 = puVar12 + 1;
          puVar14 = puVar14 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar14 = *(undefined1 *)puVar12;
          puVar12 = (undefined4 *)((int)puVar12 + 1);
          puVar14 = (undefined4 *)((int)puVar14 + 1);
        }
        FUN_00403490((undefined1 *)((piVar4[0x107] - *piVar1) + (int)puVar11),iVar9);
      }
      else {
        for (uVar5 = uVar7 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar14 = *puVar11;
          puVar11 = puVar11 + 1;
          puVar14 = puVar14 + 1;
        }
        for (uVar5 = uVar7 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar14 = *(undefined1 *)puVar11;
          puVar11 = (undefined4 *)((int)puVar11 + 1);
          puVar14 = (undefined4 *)((int)puVar14 + 1);
        }
        iVar6 = piVar4[0x107];
        iVar9 = *piVar1 + uVar7;
        if (iVar9 != iVar6) {
          FUN_005092c0(iVar9,iVar6,1);
          piVar4[0x107] = piVar4[0x107] + (iVar9 - iVar6);
        }
      }
    }
  }
  iVar6 = FUN_00571660(s_Model_005c9204);
  if (iVar6 != 0) {
    iVar6 = FUN_00571660(s_Model_005c9204);
    local_58 = *(undefined4 *)(iVar6 + 8);
  }
  iVar6 = FUN_00571660(s_Weapon_005c9b40);
  if (iVar6 != 0) {
    iVar6 = FUN_00571660(s_Weapon_005c9b40);
    local_60 = *(undefined4 *)(iVar6 + 8);
  }
  iVar6 = FUN_00571660(s_Weapon2_005c9b38);
  if (iVar6 != 0) {
    iVar6 = FUN_00571660(s_Weapon2_005c9b38);
    param_1 = *(undefined4 *)(iVar6 + 8);
  }
  iVar6 = FUN_00571660(&DAT_005c9b30);
  if (iVar6 != 0) {
    iVar6 = FUN_00571660(&DAT_005c9b30);
    local_5c = *(undefined4 *)(iVar6 + 8);
  }
  FUN_005012f0();
  (**(code **)(*piVar4 + 0x16c))(local_58,local_5c,local_60,param_1,piVar4[0x106]);
  (**(code **)(*unaff_EBP + 0x244))(piVar4);
  ExceptionList = pvStack_24;
  return 1;
}

