/* Decompiled from user's Meteor.exe; address: 00587b90 */
/* String anchors: [%s\%s.gmb, %s\%s.gmc] */

/* WARNING: Removing unreachable block (ram,0x00587e26) */
/* WARNING: Removing unreachable block (ram,0x00587df1) */
/* WARNING: Removing unreachable block (ram,0x00587d50) */
/* WARNING: Removing unreachable block (ram,0x00587d4c) */
/* WARNING: Removing unreachable block (ram,0x00587d9c) */
/* WARNING: Removing unreachable block (ram,0x00587da4) */
/* WARNING: Removing unreachable block (ram,0x00587db6) */
/* WARNING: Removing unreachable block (ram,0x00587dab) */
/* WARNING: Removing unreachable block (ram,0x00587df5) */
/* WARNING: Removing unreachable block (ram,0x00587e2a) */

void __fastcall FUN_00587b90(int param_1)

{
  char cVar1;
  char *pcVar2;
  void *pvVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  undefined1 auStack_8c [128];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a6aea;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_00582000();
  pcVar2 = (char *)FUN_00478ea0(0);
  uVar5 = 0xffffffff;
  local_4 = 0;
  pcVar7 = pcVar2;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  FUN_00402ac0(pcVar2,pcVar2 + (~uVar5 - 1));
  iVar6 = -1;
  pcVar7 = (char *)(param_1 + 0x268);
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  local_4 = 1;
  if (iVar6 == -2) {
LAB_00587dff:
    FUN_00478ec0(0,0);
  }
  else {
    pcVar2 = (char *)FUN_004807d0((char *)(param_1 + 0x268));
    uVar5 = 0xffffffff;
    local_4._0_1_ = 2;
    pcVar7 = pcVar2;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    FUN_00402ac0(pcVar2,pcVar2 + (~uVar5 - 1));
    local_4._0_1_ = 3;
    if (*(int **)(param_1 + 0x2e8) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0x2e8) + 8))(1);
      *(undefined4 *)(param_1 + 0x2e8) = 0;
    }
    pvVar3 = operator_new(0x1d0);
    local_4._0_1_ = 4;
    if (pvVar3 == (void *)0x0) {
      uVar4 = 0;
    }
    else {
      uVar4 = FUN_005678a0();
    }
    local_4 = CONCAT31(local_4._1_3_,3);
    *(undefined4 *)(param_1 + 0x2e8) = uVar4;
    FUN_00508ae6(auStack_8c,s__s__s_gmc_005d2f4c,&DAT_0072b6b0,0);
    iVar6 = FUN_00568f80(auStack_8c,1);
    if (iVar6 == 0) {
      FUN_00508ae6(auStack_8c,s__s__s_gmb_005d2f40,&DAT_0072b6b0,0);
      iVar6 = FUN_00568f80(auStack_8c,1);
      if (iVar6 != 0) goto LAB_00587d02;
    }
    else {
LAB_00587d02:
      FUN_00508ae6(auStack_8c,s__s__s_des_005d2f34,&DAT_0072b6b0,0);
      iVar6 = FUN_00569e10(auStack_8c);
      if (iVar6 != 0) {
        local_4 = CONCAT31(local_4._1_3_,1);
        goto LAB_00587dff;
      }
    }
    local_4 = CONCAT31(local_4._1_3_,1);
    FUN_00478ec0(0,0);
    if (*(int **)(param_1 + 0x2e8) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0x2e8) + 8))(1);
      *(undefined4 *)(param_1 + 0x2e8) = 0;
    }
  }
  ExceptionList = pvStack_c;
  return;
}

