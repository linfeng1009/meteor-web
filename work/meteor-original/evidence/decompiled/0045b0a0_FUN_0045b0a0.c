/* Meteor.exe original x86 @ 0045b0a0 */
/* Caller: 0045a7ef */

undefined4 __thiscall FUN_0045b0a0(int param_1,char *param_2,char *param_3)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  bool bVar8;
  
  iVar4 = 0xb;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_player_num_005c7478;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar2 = FUN_0050915b(param_3);
    *(undefined2 *)(param_1 + 0x6a) = uVar2;
  }
  iVar4 = 9;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_game_num_005c744c;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar2 = FUN_0050915b(param_3);
    *(undefined2 *)(param_1 + 0x6c) = uVar2;
  }
  iVar4 = 10;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_game_time_005c7440;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar2 = FUN_0050915b(param_3);
    *(undefined2 *)(param_1 + 0x6e) = uVar2;
  }
  iVar4 = 0xc;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_life_adjust_005c7410;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar5 = 0xffffffff;
    pcVar6 = param_3;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    param_3[~uVar5 - 2] = '\0';
    uVar3 = FUN_0050915b(param_3);
    *(undefined4 *)(param_1 + 0x70) = uVar3;
  }
  iVar4 = 9;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_hideitem_005c7500;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar3 = FUN_0050915b(param_3);
    *(undefined4 *)(param_1 + 0x74) = uVar3;
  }
  iVar4 = 0xb;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_friendfire_005c74f4;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar3 = FUN_0050915b(param_3);
    *(undefined4 *)(param_1 + 0x78) = uVar3;
  }
  iVar4 = 0xb;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_autoswitch_005c74e8;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar3 = FUN_0050915b(param_3);
    *(undefined4 *)(param_1 + 0x7c) = uVar3;
  }
  iVar4 = 10;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_walknoise_005c7958;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar3 = FUN_0050915b(param_3);
    *(undefined4 *)(param_1 + 0x80) = uVar3;
  }
  iVar4 = 0xb;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_healthitem_005c74dc;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar3 = FUN_0050915b(param_3);
    *(undefined4 *)(param_1 + 0x84) = uVar3;
  }
  iVar4 = 0xb;
  bVar8 = true;
  pcVar6 = param_2;
  pcVar7 = s_updateitem_005c74d0;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *pcVar6 == *pcVar7;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar3 = FUN_0050915b(param_3);
    *(undefined4 *)(param_1 + 0x88) = uVar3;
  }
  iVar4 = 0xc;
  bVar8 = true;
  pcVar6 = s_specialitem_005c74c4;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *param_2 == *pcVar6;
    param_2 = param_2 + 1;
    pcVar6 = pcVar6 + 1;
  } while (bVar8);
  if (bVar8) {
    uVar3 = FUN_0050915b(param_3);
    *(undefined4 *)(param_1 + 0x8c) = uVar3;
  }
  return 1;
}

