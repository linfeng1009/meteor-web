/* Meteor.exe original x86 @ 00563300 */
/* Caller: 00563815 */
/* Caller: 0056386d */
/* Caller: 00563a33 */
/* Caller: 00563bbc */

byte FUN_00563300(int param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  char local_20 [32];
  
  pcVar2 = (char *)(param_1 + 0x88);
  iVar3 = -(int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2[(int)(local_20 + iVar3)] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_00593634(local_20);
  pcVar2 = (char *)(param_1 + 0x28);
  iVar3 = 10;
  bVar6 = true;
  pcVar4 = pcVar2;
  pcVar5 = s_animation_005d1598;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *pcVar4 == *pcVar5;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    return 10;
  }
  iVar3 = _strncmp(pcVar2,s_damage_005d1590,6);
  if (iVar3 != 0) {
    iVar3 = 5;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = &DAT_005d1588;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 4;
    }
    iVar3 = 6;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = &DAT_005d1580;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 5;
    }
    iVar3 = 6;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = &DAT_005d1578;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 6;
    }
    iVar3 = 5;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = &DAT_005c9c1c;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 7;
    }
    iVar3 = 5;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = &DAT_005c9c14;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 0xb;
    }
    iVar3 = 8;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = s_machine_005d1570;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 0xc;
    }
    iVar3 = 7;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = s_normal_005d1568;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 0;
    }
    iVar3 = _strncmp(pcVar2,&DAT_005d1560,4);
    if (iVar3 == 0) {
      return 1;
    }
    iVar3 = _strncmp(pcVar2,&DAT_005d1558,4);
    if (iVar3 == 0) {
      return 1;
    }
    iVar3 = 8;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = s_targeta_005d1550;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 0xd;
    }
    iVar3 = 8;
    bVar6 = true;
    pcVar4 = pcVar2;
    pcVar5 = s_targetb_005d1548;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return 0xe;
    }
    iVar3 = 9;
    bVar6 = true;
    pcVar4 = s_treasure_005d153c;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pcVar2 == *pcVar4;
      pcVar2 = pcVar2 + 1;
      pcVar4 = pcVar4 + 1;
    } while (bVar6);
    if (bVar6) {
      return 0xf;
    }
    iVar3 = -1;
    pcVar2 = (char *)(param_1 + 0x48);
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    return -(iVar3 != -2) & 0xf;
  }
  iVar3 = -1;
  pcVar2 = (char *)(param_1 + 0x48);
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return (-(iVar3 != -2) & 9U) + 3;
}

