/* Original Meteor.exe static export @ 004ed820; original sample not executed. */
/* XREF 005aa14c DATA */
/* XREF 005ab5d4 DATA */
/* XREF 005aba14 DATA */
/* XREF 005ab394 DATA */

undefined4 __thiscall
FUN_004ed820(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,char *param_6)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  
  *(undefined4 *)(param_1 + 0x36c) = param_3;
  *(undefined4 *)(param_1 + 0x368) = param_2;
  *(undefined4 *)(param_1 + 0x374) = param_5;
  *(undefined4 *)(param_1 + 0x370) = param_4;
  *(undefined4 *)(param_1 + 0x304) = 1;
  piVar1 = (int *)(param_1 + 0x378);
  uVar5 = 0xffffffff;
  pcVar9 = param_6;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar2 != '\0');
  pcVar9 = (char *)*piVar1;
  uVar6 = *(int *)(param_1 + 0x37c) - (int)pcVar9;
  uVar4 = (int)(param_6 + (~uVar5 - 1)) - (int)param_6;
  if (uVar6 < uVar4) {
    pcVar8 = param_6;
    for (uVar4 = uVar6 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
    FUN_00403490(param_6 + (*(int *)(param_1 + 0x37c) - *piVar1),param_6 + (~uVar5 - 1));
  }
  else {
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)param_6;
      param_6 = param_6 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar5 = uVar4 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar9 = *param_6;
      param_6 = param_6 + 1;
      pcVar9 = pcVar9 + 1;
    }
    iVar3 = *(int *)(param_1 + 0x37c);
    iVar7 = *piVar1 + uVar4;
    if (iVar7 != iVar3) {
      FUN_005092c0(iVar7,iVar3,1);
      *(int *)(param_1 + 0x37c) = *(int *)(param_1 + 0x37c) + (iVar7 - iVar3);
      return 1;
    }
  }
  return 1;
}

