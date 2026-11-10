/* Original Meteor.exe static export @ 0058a560; original sample not executed. */
/* XREF 00582dc3 UNCONDITIONAL_CALL */
/* XREF 00582dd5 UNCONDITIONAL_CALL */

void FUN_0058a560(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char local_80 [128];
  
  FUN_0058a620(local_80,param_2);
  uVar4 = 0xffffffff;
  pcVar8 = local_80;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  pcVar8 = (char *)*param_1;
  uVar3 = (int)(local_80 + (~uVar4 - 1)) - (int)local_80;
  uVar5 = param_1[1] - (int)pcVar8;
  if (uVar5 < uVar3) {
    pcVar7 = local_80;
    for (uVar3 = uVar5 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    FUN_00403490(local_80 + (param_1[1] - *param_1),local_80 + (~uVar4 - 1));
  }
  else {
    pcVar7 = local_80;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    iVar2 = param_1[1];
    iVar6 = *param_1 + uVar3;
    if (iVar6 != iVar2) {
      FUN_005092c0(iVar6,iVar2,1);
      param_1[1] = param_1[1] + (iVar6 - iVar2);
      return;
    }
  }
  return;
}

