/* Original Meteor.exe static export @ 00566230; original sample not executed. */
/* XREF 005669f3 UNCONDITIONAL_CALL */

void __thiscall FUN_00566230(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  char *pcVar11;
  char *pcVar12;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a57cb;
  local_c = ExceptionList;
  iVar2 = *(int *)(param_1 + 300);
  ExceptionList = &local_c;
  if (iVar2 != 0) {
    ExceptionList = &local_c;
    FUN_0056dc50();
    FUN_00507850(iVar2);
    *(undefined4 *)(param_1 + 300) = 0;
  }
  pvVar3 = operator_new(0x130);
  local_4 = 0;
  if (pvVar3 == (void *)0x0) {
    uVar4 = 0;
  }
  else {
    uVar4 = FUN_0056db90();
  }
  *(undefined4 *)(param_1 + 300) = uVar4;
  local_4 = 0xffffffff;
  uVar4 = FUN_004807d0(param_2);
  pcVar5 = (char *)FUN_00593634(uVar4);
  uVar7 = 0xffffffff;
  piVar9 = (int *)(param_1 + 0x120);
  pcVar12 = pcVar5;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar12;
    pcVar12 = pcVar12 + 1;
  } while (cVar1 != '\0');
  pcVar12 = (char *)*piVar9;
  uVar8 = *(int *)(param_1 + 0x124) - (int)pcVar12;
  uVar6 = (int)(pcVar5 + (~uVar7 - 1)) - (int)pcVar5;
  if (uVar8 < uVar6) {
    pcVar11 = pcVar5;
    for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar12 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar12 = pcVar12 + 1;
    }
    FUN_00403490(pcVar5 + (*(int *)(param_1 + 0x124) - *piVar9),pcVar5 + (~uVar7 - 1));
  }
  else {
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar7 = uVar6 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar12 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar12 = pcVar12 + 1;
    }
    iVar2 = *(int *)(param_1 + 0x124);
    iVar10 = *piVar9 + uVar6;
    if (iVar10 != iVar2) {
      FUN_005092c0(iVar10,iVar2,1);
      *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) + (iVar10 - iVar2);
    }
  }
  FUN_0056e490(param_2);
  ExceptionList = local_c;
  return;
}

