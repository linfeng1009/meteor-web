/* Original Meteor.exe read-only export. Sample not executed. */

/* WARNING: Removing unreachable block (ram,0x004f9443) */
/* WARNING: Removing unreachable block (ram,0x004f9455) */
/* WARNING: Removing unreachable block (ram,0x004f93a9) */
/* WARNING: Removing unreachable block (ram,0x004f93be) */
/* WARNING: Removing unreachable block (ram,0x004f9472) */
/* WARNING: Removing unreachable block (ram,0x004f93a1) */
/* WARNING: Removing unreachable block (ram,0x004f93b0) */
/* WARNING: Removing unreachable block (ram,0x004f9323) */
/* WARNING: Removing unreachable block (ram,0x004f932b) */
/* WARNING: Removing unreachable block (ram,0x004f92bf) */
/* WARNING: Removing unreachable block (ram,0x004f92b7) */
/* WARNING: Removing unreachable block (ram,0x004f940b) */
/* WARNING: Removing unreachable block (ram,0x004f9407) */
/* WARNING: Removing unreachable block (ram,0x004f943f) */
/* WARNING: Removing unreachable block (ram,0x004f944a) */
/* WARNING: Removing unreachable block (ram,0x004f913c) */
/* WARNING: Removing unreachable block (ram,0x004f9144) */

undefined4 FUN_004f8f60(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar8;
  char *pcVar9;
  char *pcVar10;
  bool bVar11;
  undefined1 *puVar12;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar4 = param_1;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a39d0;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  param_1 = FUN_004c3730(*(undefined4 *)(**(int **)(param_1 + 8) + 8));
  if (param_1 == 0) {
    ExceptionList = local_c;
    return 0;
  }
  iVar5 = *(int *)(*(int *)(iVar4 + 8) + 4);
  local_4 = 0;
  FUN_00402ac0(*(undefined4 *)(iVar5 + 0xc),*(undefined4 *)(iVar5 + 0x10));
  iVar5 = -1;
  pcVar7 = &DAT_005ca11c;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  local_4 = 1;
  if (iVar5 == -2) {
    bVar11 = true;
    iVar5 = 0;
    pcVar7 = (char *)0x0;
    pcVar9 = &DAT_005ca11c;
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar11 = *pcVar7 == *pcVar9;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar11);
    if (bVar11) {
      FUN_004fda00();
      FUN_004fd5b0(&LAB_00503970);
    }
  }
  iVar5 = param_1;
  pcVar7 = (char *)0x0;
  iVar6 = -1;
  pcVar9 = &DAT_005ca114;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (iVar6 == -2) {
    bVar11 = true;
    iVar6 = 0;
    pcVar9 = pcVar7;
    pcVar10 = &DAT_005ca114;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar11 = *pcVar9 == *pcVar10;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    } while (bVar11);
    if (bVar11) {
      FUN_004fda00();
      FUN_004fd5b0(&LAB_005039f0);
      ExceptionList = local_c;
      return 1;
    }
  }
  iVar6 = -1;
  pcVar9 = &DAT_005ca110;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (iVar6 == -2) {
    bVar11 = true;
    iVar6 = 0;
    pcVar9 = pcVar7;
    pcVar10 = &DAT_005ca110;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar11 = *pcVar9 == *pcVar10;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    } while (bVar11);
    if (bVar11) {
      FUN_004fda00();
      FUN_004fd5b0(FUN_00503d00);
      ExceptionList = local_c;
      return 1;
    }
  }
  iVar6 = -1;
  pcVar9 = s_follow_005ca108;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (iVar6 == -2) {
    bVar11 = true;
    iVar6 = 0;
    pcVar9 = pcVar7;
    pcVar10 = s_follow_005ca108;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar11 = *pcVar9 == *pcVar10;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    } while (bVar11);
    if (bVar11) {
      iVar6 = *(int *)(*(int *)(*(int *)(iVar4 + 8) + 8) + 4);
      if ((iVar6 < 7) || (8 < iVar6)) {
        iVar5 = FUN_004c36d0(*(undefined4 *)(*(int *)(*(int *)(iVar4 + 8) + 8) + 8));
        iVar4 = param_1;
        if (iVar5 == 0) {
          ExceptionList = local_c;
          return 0;
        }
        FUN_004fda00();
        *(int *)(iVar4 + 0x78) = iVar5;
      }
      else {
        FUN_004fda00();
        iVar4 = *(int *)(*(int *)(iVar4 + 8) + 8);
        puVar3 = (undefined4 *)(iVar4 + 0xc);
        if (puVar3 != (undefined4 *)(iVar5 + 0xfc)) {
          FUN_00403200(*puVar3,*(undefined4 *)(iVar4 + 0x10));
          FUN_004fd5b0(&LAB_00503b30);
          ExceptionList = local_c;
          return 1;
        }
      }
      FUN_004fd5b0(&LAB_00503b30);
      ExceptionList = local_c;
      return 1;
    }
  }
  iVar6 = -1;
  pcVar9 = s_patrol_005ca100;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (iVar6 == -2) {
    bVar11 = true;
    iVar6 = 0;
    pcVar9 = pcVar7;
    pcVar10 = s_patrol_005ca100;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar11 = *pcVar9 == *pcVar10;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    } while (bVar11);
    if (bVar11) {
      FUN_004fda00();
      iVar6 = 2;
      uVar8 = extraout_EDX;
      if (2 < *(int *)(iVar4 + 4)) {
        do {
          iVar2 = *(int *)(iVar5 + 0x10c);
          param_1 = CONCAT22((short)((uint)uVar8 >> 0x10),
                             *(undefined2 *)(*(int *)(*(int *)(iVar4 + 8) + iVar6 * 4) + 8));
          if (iVar2 == *(int *)(iVar5 + 0x110)) {
            FUN_004c4870(iVar2,&param_1);
            uVar8 = extraout_EDX_01;
          }
          else {
            FUN_004b5f30(iVar2,&param_1);
            *(int *)(iVar5 + 0x10c) = *(int *)(iVar5 + 0x10c) + 2;
            uVar8 = extraout_EDX_00;
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < *(int *)(iVar4 + 4));
      }
      FUN_004fd5b0(&LAB_00503a00);
      ExceptionList = local_c;
      return 1;
    }
  }
  iVar6 = -1;
  pcVar9 = s_attacktarget_005ca0f0;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (iVar6 == -2) {
    bVar11 = true;
    iVar6 = 0;
    pcVar9 = pcVar7;
    pcVar10 = s_attacktarget_005ca0f0;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar11 = *pcVar9 == *pcVar10;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    } while (bVar11);
    if (bVar11) {
      iVar6 = *(int *)(*(int *)(*(int *)(iVar4 + 8) + 8) + 8);
      if (iVar6 < 0) {
        ExceptionList = local_c;
        return 0;
      }
      if (iVar6 < 10) {
        FUN_004fd630(&LAB_00504a70);
        if (*(int *)(iVar4 + 4) == 4) {
          *(undefined4 *)(iVar5 + 0x88) = *(undefined4 *)(*(int *)(*(int *)(iVar4 + 8) + 0xc) + 8);
        }
        else {
          *(undefined4 *)(iVar5 + 0x88) = 0;
        }
        *(undefined4 *)(iVar5 + 0xd4) = *(undefined4 *)(&DAT_00666858 + iVar6 * 0xc);
        *(undefined4 *)(iVar5 + 0xd8) = *(undefined4 *)(&DAT_0066685c + iVar6 * 0xc);
        *(undefined4 *)(iVar5 + 0xdc) = *(undefined4 *)(&DAT_00666860 + iVar6 * 0xc);
        ExceptionList = local_c;
        return 1;
      }
      ExceptionList = local_c;
      return 0;
    }
  }
  iVar5 = -1;
  pcVar9 = &DAT_005c9858;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (iVar5 == -2) {
    bVar11 = true;
    iVar5 = 0;
    pcVar9 = pcVar7;
    pcVar10 = &DAT_005c9858;
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar11 = *pcVar9 == *pcVar10;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    } while (bVar11);
    if (bVar11) {
      iVar4 = FUN_004c36d0(*(undefined4 *)(*(int *)(*(int *)(iVar4 + 8) + 8) + 8));
      if (iVar4 == 0) {
        ExceptionList = local_c;
        return 0;
      }
      puVar12 = &LAB_00504670;
      goto LAB_004f93e3;
    }
  }
  iVar5 = -1;
  pcVar9 = s_dodge_005ca0e8;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (iVar5 != -2) {
    ExceptionList = local_c;
    return 0;
  }
  bVar11 = true;
  iVar5 = 0;
  pcVar9 = s_dodge_005ca0e8;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    bVar11 = *pcVar7 == *pcVar9;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  } while (bVar11);
  if (!bVar11) {
    ExceptionList = local_c;
    return 0;
  }
  iVar4 = FUN_004c36d0(*(undefined4 *)(*(int *)(*(int *)(iVar4 + 8) + 8) + 8));
  if (iVar4 == 0) {
    ExceptionList = local_c;
    return 0;
  }
  puVar12 = &LAB_00504560;
LAB_004f93e3:
  iVar5 = param_1;
  FUN_004fd630(puVar12);
  *(int *)(iVar5 + 0x74) = iVar4;
  ExceptionList = local_c;
  return 1;
}

