/* Original Meteor.exe static export @ 0056c400; original sample not executed. */
/* XREF 00560a21 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0056c400(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  
  iVar7 = *(int *)(param_1 + 4);
  if (iVar7 < 2) {
    return 0;
  }
  piVar2 = *(int **)(param_1 + 8);
  uVar5 = 0xffffffff;
  iVar3 = *piVar2;
  iVar4 = piVar2[1];
  pcVar8 = &DAT_005d1834;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  iVar6 = ~uVar5 - 1;
  if (*(int *)(iVar3 + 0x10) - (int)*(char **)(iVar3 + 0xc) == iVar6) {
    bVar10 = true;
    pcVar8 = *(char **)(iVar3 + 0xc);
    pcVar9 = &DAT_005d1834;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      FUN_00561b60(CONCAT31((int3)((uint)*(int *)(iVar4 + 8) >> 8),*(int *)(iVar4 + 8) != 0));
      return 1;
    }
  }
  uVar5 = 0xffffffff;
  pcVar8 = s_winddir_005d182c;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  iVar6 = ~uVar5 - 1;
  if (*(int *)(iVar3 + 0x10) - (int)*(char **)(iVar3 + 0xc) == iVar6) {
    bVar10 = true;
    pcVar8 = *(char **)(iVar3 + 0xc);
    pcVar9 = s_winddir_005d182c;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      if (iVar7 < 4) {
        return 0;
      }
      FUN_0057d930((float)*(int *)(iVar4 + 8) * _DAT_005a8410,
                   (float)*(int *)(piVar2[2] + 8) * _DAT_005a8410,
                   (float)*(int *)(piVar2[3] + 8) * _DAT_005a8410);
      return 1;
    }
  }
  uVar5 = 0xffffffff;
  pcVar8 = s_snowspeed_005d1820;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  iVar6 = ~uVar5 - 1;
  if (*(int *)(iVar3 + 0x10) - (int)*(char **)(iVar3 + 0xc) == iVar6) {
    bVar10 = true;
    pcVar8 = *(char **)(iVar3 + 0xc);
    pcVar9 = s_snowspeed_005d1820;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      if (iVar7 < 3) {
        return 0;
      }
      FUN_0057d970((float)*(int *)(iVar4 + 8),(float)*(int *)(piVar2[2] + 8));
      return 1;
    }
  }
  uVar5 = 0xffffffff;
  pcVar8 = s_snowsize_005d1814;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  iVar6 = ~uVar5 - 1;
  if (*(int *)(iVar3 + 0x10) - (int)*(char **)(iVar3 + 0xc) == iVar6) {
    bVar10 = true;
    pcVar8 = *(char **)(iVar3 + 0xc);
    pcVar9 = s_snowsize_005d1814;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      if (iVar7 < 3) {
        return 0;
      }
      FUN_0057d950((float)*(int *)(iVar4 + 8),(float)*(int *)(piVar2[2] + 8));
      return 1;
    }
  }
  uVar5 = 0xffffffff;
  pcVar8 = s_snowdensity_005d1808;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  iVar7 = ~uVar5 - 1;
  if (*(int *)(iVar3 + 0x10) - (int)*(char **)(iVar3 + 0xc) == iVar7) {
    bVar10 = true;
    pcVar8 = *(char **)(iVar3 + 0xc);
    pcVar9 = s_snowdensity_005d1808;
    do {
      if (iVar7 == 0) break;
      iVar7 = iVar7 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      FUN_0057d990(*(undefined4 *)(iVar4 + 8));
    }
  }
  return 1;
}

