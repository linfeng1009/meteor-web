/* Original Meteor.exe static export @ 005724f0; original sample not executed. */
/* XREF 00573602 UNCONDITIONAL_CALL */
/* XREF 0057312e UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_005724f0(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  float10 fVar8;
  int *piStack_c8;
  int *piStack_c4;
  int local_b0;
  int local_ac;
  int *local_a8;
  int local_a4;
  undefined1 local_a0 [12];
  int *local_94;
  int local_90;
  int local_8c;
  int local_88;
  float local_84;
  undefined4 local_80 [16];
  undefined1 local_40 [64];
  
  local_a4 = param_1;
  fVar8 = (float10)FUN_004748c0();
  iVar5 = *(int *)(param_1 + 0xa8);
  local_a8 = (int *)(float)fVar8;
  piStack_c4 = (int *)0x572517;
  iVar3 = FUN_0056ae40();
  if (iVar3 != 0) {
    iVar5 = iVar5 + 0x54;
    piStack_c8 = (int *)(iVar3 + 0x98);
    piStack_c4 = (int *)iVar5;
    FUN_00476f00(local_80);
    piStack_c4 = (int *)local_a0;
    piStack_c8 = (int *)0x3;
    FUN_00477d30();
    piStack_c4 = (int *)local_a0;
    piVar1 = (int *)(param_1 + 0xac);
    local_94 = local_a8;
    FUN_004e8720(&piStack_c8);
    FUN_00574810(&local_b0);
    piStack_c4 = (int *)0x1;
    piStack_c8 = (int *)0x572578;
    iVar3 = FUN_0056ae40();
    piStack_c8 = (int *)(iVar3 + 0x98);
    piStack_c4 = (int *)iVar5;
    puVar4 = (undefined4 *)FUN_00476f00(local_40);
    piStack_c4 = (int *)local_a0;
    puVar7 = local_80;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar7 = puVar7 + 1;
    }
    piStack_c8 = (int *)0x3;
    FUN_00477d30();
    piStack_c4 = (int *)local_a0;
    local_94 = local_a8;
    piStack_c8 = local_a8;
    FUN_004e8720(&piStack_c8);
    FUN_00574810(&local_b0);
    piStack_c8 = (int *)*piVar1;
    piStack_c4 = &local_ac;
    local_ac = 0;
    FUN_0046ef50(*piStack_c8);
    iVar5 = local_ac;
    iVar3 = 0;
    local_ac = 0;
    local_b0 = iVar5;
    FUN_0046ef50(*(undefined4 *)*piVar1,(undefined4 *)*piVar1,&local_ac);
    piVar2 = (int *)*piVar1;
    piVar6 = (int *)*piVar2;
    if (piVar6 != piVar2) {
      local_a8 = (int *)((float)local_a8 - _DAT_005a83e8);
      do {
        local_90 = piVar6[2];
        local_8c = piVar6[3];
        local_88 = piVar6[4];
        local_84 = (float)piVar6[5];
        iVar5 = iVar3;
        if (local_84 < (float)local_a8) break;
        piVar6 = (int *)*piVar6;
        iVar3 = iVar3 + 1;
        iVar5 = local_b0;
      } while (piVar6 != piVar2);
    }
    if ((iVar5 < local_ac) && (iVar5 = local_ac - iVar5, 0 < iVar5)) {
      do {
        local_b0 = *piVar1;
        piStack_c4 = (int *)0x57267f;
        piStack_c8 = (int *)FUN_004d6b10();
        piStack_c8 = (int *)*piStack_c8;
        piStack_c4 = (int *)0x18;
        piVar2 = (int *)piStack_c8[1];
        iVar3 = *piStack_c8;
        *piVar2 = iVar3;
        *(int **)(iVar3 + 4) = piVar2;
        FUN_00402e90();
        local_b0 = *(int *)(param_1 + 0xb0);
        piStack_c4 = (int *)0x5726a5;
        puVar4 = (undefined4 *)FUN_004d6b10();
        piStack_c8 = (int *)*puVar4;
        piStack_c4 = (int *)0x18;
        piVar2 = (int *)piStack_c8[1];
        iVar3 = *piStack_c8;
        *piVar2 = iVar3;
        *(int **)(iVar3 + 4) = piVar2;
        FUN_00402e90();
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    for (puVar4 = *(undefined4 **)*piVar1; puVar4 != (undefined4 *)*piVar1;
        puVar4 = (undefined4 *)*puVar4) {
    }
    iVar5 = *(int *)(*(int *)(local_a4 + 0x20) + 0x63c);
    if (((iVar5 != 0) && (*(char *)(iVar5 + 1) != -1)) &&
       (*(int *)(*(int *)(*(int *)(local_a4 + 0x20) + 0x638) + 100) != 0)) {
      FUN_00572710();
    }
  }
  return;
}

