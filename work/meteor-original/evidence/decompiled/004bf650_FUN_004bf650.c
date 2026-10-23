/* Meteor.exe original x86 @ 004bf650 */
/* Caller: 004bfbcc */
/* Caller: 00488c89 */

undefined4 __thiscall FUN_004bf650(int param_1,char *param_2)

{
  int *piVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  undefined1 local_40 [64];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar5 = 0xffffffff;
  piVar1 = (int *)(param_1 + 0x50c);
  pcVar9 = param_2;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar2 != '\0');
  pcVar9 = (char *)*piVar1;
  uVar6 = *(int *)(param_1 + 0x510) - (int)pcVar9;
  uVar3 = (int)(param_2 + (~uVar5 - 1)) - (int)param_2;
  if (uVar6 < uVar3) {
    pcVar8 = param_2;
    for (uVar3 = uVar6 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
    FUN_00403490(param_2 + (*(int *)(param_1 + 0x510) - *piVar1),param_2 + (~uVar5 - 1));
  }
  else {
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)param_2;
      param_2 = param_2 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar5 = uVar3 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar9 = *param_2;
      param_2 = param_2 + 1;
      pcVar9 = pcVar9 + 1;
    }
    iVar4 = *(int *)(param_1 + 0x510);
    iVar7 = *piVar1 + uVar3;
    if (iVar7 != iVar4) {
      FUN_005092c0(iVar7,iVar4,1);
      *(int *)(param_1 + 0x510) = *(int *)(param_1 + 0x510) + (iVar7 - iVar4);
    }
  }
  *(undefined4 *)(param_1 + 0x598) = 0;
  *(undefined1 *)(param_1 + 0x594) = 1;
  cVar2 = FUN_004c2de0();
  if (cVar2 == '\0') {
    FUN_00553800(s_Load__s_wp_error_005c9afc,*piVar1);
    return 0;
  }
  FUN_00508ae6(local_40,s_Level__s__pst_005c9aec,*piVar1);
  cVar2 = FUN_004f8950(local_40);
  if (cVar2 == '\0') {
    FUN_00553800(s_Load__s__pst_error_005c9ad8,*piVar1);
    return 0;
  }
  *(undefined4 *)(param_1 + 0x578) = 5;
  iVar4 = FUN_00571660(&DAT_005c9ad0);
  if (iVar4 != 0) {
    iVar4 = FUN_00571660(&DAT_005c9ad0);
    *(undefined4 *)(param_1 + 0x578) = *(undefined4 *)(iVar4 + 8);
  }
  *(undefined4 *)(param_1 + 0x57c) = 0xf;
  iVar4 = FUN_00571660(s_RoundTime_005c9ac4);
  if (iVar4 != 0) {
    iVar4 = FUN_00571660(s_RoundTime_005c9ac4);
    *(undefined4 *)(param_1 + 0x57c) = *(undefined4 *)(iVar4 + 8);
  }
  *(undefined4 *)(param_1 + 0x570) = 0;
  iVar4 = FUN_00571660(s_PlayerSpawn_005c9ab8);
  if (iVar4 != 0) {
    iVar4 = FUN_00571660(s_PlayerSpawn_005c9ab8);
    *(undefined4 *)(param_1 + 0x570) = *(undefined4 *)(iVar4 + 8);
  }
  *(undefined4 *)(param_1 + 0x574) = 0;
  iVar4 = FUN_00571660(s_PlayerSpawnDir_005c9aa8);
  if (iVar4 != 0) {
    iVar4 = FUN_00571660(s_PlayerSpawnDir_005c9aa8);
    *(undefined4 *)(param_1 + 0x574) = *(undefined4 *)(iVar4 + 8);
  }
  *(undefined4 *)(param_1 + 0x580) = 5;
  iVar4 = FUN_00571660(s_PlayerWeapon_005c9a98);
  if (iVar4 != 0) {
    iVar4 = FUN_00571660(s_PlayerWeapon_005c9a98);
    *(undefined4 *)(param_1 + 0x580) = *(undefined4 *)(iVar4 + 8);
  }
  *(undefined4 *)(param_1 + 0x584) = 0;
  iVar4 = FUN_00571660(s_PlayerWeapon2_005c9a88);
  if (iVar4 != 0) {
    iVar4 = FUN_00571660(s_PlayerWeapon2_005c9a88);
    *(undefined4 *)(param_1 + 0x584) = *(undefined4 *)(iVar4 + 8);
  }
  *(undefined4 *)(param_1 + 0x588) = 1000;
  iVar4 = FUN_00571660(s_PlayerHP_005c9a7c);
  if (iVar4 != 0) {
    iVar4 = FUN_00571660(s_PlayerHP_005c9a7c);
    *(undefined4 *)(param_1 + 0x588) = *(undefined4 *)(iVar4 + 8);
  }
  *(undefined4 *)(param_1 + 0x590) = 0;
  iVar4 = FUN_00571660(s_Peace_005c9a74);
  if (iVar4 != 0) {
    iVar4 = FUN_00571660(s_Peace_005c9a74);
    *(undefined4 *)(param_1 + 0x590) = *(undefined4 *)(iVar4 + 8);
  }
  return 1;
}

