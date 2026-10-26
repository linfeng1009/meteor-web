/* Original Meteor.exe static export @ 004accf0; original sample not executed. */
/* XREF 005a9c40 DATA */

undefined4 __fastcall FUN_004accf0(int *param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  uint unaff_EBX;
  uint unaff_EBP;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  undefined1 auStack_10 [4];
  undefined1 auStack_c [8];
  byte *pbStack_4;
  
  (**(code **)(*param_1 + 0xac))(auStack_10,auStack_c);
  if ((*pbStack_4 != unaff_EBP) || (pbStack_4[1] != unaff_EBX)) {
    return 0xff01;
  }
  pcVar4 = (char *)param_1[0x81];
  if ((char *)param_1[0x82] != pcVar4) {
    iVar3 = param_1[0x82] - (int)pcVar4;
    if (iVar3 == *(int *)(pbStack_4 + 8) - (int)*(char **)(pbStack_4 + 4)) {
      bVar6 = true;
      pcVar5 = *(char **)(pbStack_4 + 4);
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar6 = *pcVar4 == *pcVar5;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      } while (bVar6);
      if (bVar6) goto LAB_004acd6e;
    }
    return 0xff04;
  }
LAB_004acd6e:
  if (param_1[0x86] <= param_1[0xeb]) {
    return 0xff03;
  }
  iVar3 = (**(code **)(*param_1 + 0xbc))(pbStack_4 + 0x1c);
  if (iVar3 == 0) {
    return 0xff02;
  }
  piVar2 = (int *)FUN_00487830();
  (**(code **)(*piVar2 + 0x2c4))(&stack0xffffffec);
  if (*(uint *)(pbStack_4 + 0x44) != unaff_EBX) {
    return 0xff06;
  }
  iVar3 = (**(code **)(*param_1 + 0x114))(0,*(undefined4 *)(pbStack_4 + 0x10));
  if (iVar3 != 0) {
    return 0xff07;
  }
  FUN_004b3420();
  cVar1 = FUN_00550c20();
  if (cVar1 == '\0') {
    iVar3 = (**(code **)(param_1[0xe9] + 0x2c))(pbStack_4 + 0x1c);
    if (iVar3 != 0) {
      return 0xff05;
    }
  }
  return 0;
}

