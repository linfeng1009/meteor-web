/* Original Meteor.exe static export @ 00573d50; original sample not executed. */
/* XREF 00558b1e UNCONDITIONAL_CALL */
/* XREF 00573fe0 UNCONDITIONAL_CALL */

void __fastcall FUN_00573d50(int param_1)

{
  float fVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  float local_80;
  float local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 local_50 [16];
  undefined1 local_40 [64];
  
  puVar4 = (undefined4 *)(param_1 + 0x184);
  iVar5 = 0x10;
  if (*(int *)(param_1 + 0x20) == 0) {
    puVar2 = (undefined4 *)(*(int *)(param_1 + 0x28) + 0x16c);
    puVar3 = puVar4;
    for (; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  else {
    uVar7 = *(undefined4 *)(param_1 + 0x3c);
    uVar8 = *(undefined4 *)(param_1 + 0x44);
    puVar2 = (undefined4 *)(*(int *)(param_1 + 0x20) + 0x184);
    puVar3 = puVar4;
    for (; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    FUN_004781d0(uVar7,*(undefined4 *)(param_1 + 0x40),uVar8,0);
  }
  iVar5 = *(int *)(param_1 + 0x28);
  if (*(int *)(param_1 + 0x30) == 0) {
    puVar2 = (undefined4 *)FUN_00573920(*(undefined4 *)(iVar5 + 0x110),1);
    puVar3 = (undefined4 *)FUN_00573920(*(undefined4 *)(iVar5 + 0x114),1);
    fVar1 = *(float *)(iVar5 + 0x118);
    local_80 = ((float)puVar3[4] - (float)puVar2[4]) * fVar1 + (float)puVar2[4];
    local_7c = (float)puVar2[5] + ((float)puVar3[5] - (float)puVar2[5]) * fVar1;
    local_78 = (float)puVar2[6] + ((float)puVar3[6] - (float)puVar2[6]) * fVar1;
    local_64 = *puVar2;
    local_68 = puVar2[3];
    local_6c = puVar2[2];
    local_70 = puVar2[1];
    local_84 = *puVar3;
    local_88 = puVar3[3];
    local_8c = puVar3[2];
    local_90 = puVar3[1];
    puVar2 = (undefined4 *)FUN_0047ee00(local_50,&local_70,&local_90,*(undefined4 *)(iVar5 + 0x118))
    ;
    local_58 = puVar2[2];
    uVar7 = *puVar2;
    uVar8 = puVar2[1];
    local_54 = puVar2[3];
    FUN_004781d0(local_80,local_7c,local_78,0);
    uVar9 = local_58;
    uVar10 = local_54;
  }
  else {
    puVar2 = (undefined4 *)FUN_00573920(*(undefined4 *)(iVar5 + 0x110),0);
    puVar3 = (undefined4 *)FUN_00573920(*(undefined4 *)(iVar5 + 0x114),0);
    local_74 = *puVar2;
    local_78 = (float)puVar2[3];
    local_7c = (float)puVar2[2];
    local_80 = (float)puVar2[1];
    local_84 = *puVar3;
    local_88 = puVar3[3];
    local_8c = puVar3[2];
    local_90 = puVar3[1];
    puVar2 = (undefined4 *)FUN_0047ee00(local_50,&local_80,&local_90,*(undefined4 *)(iVar5 + 0x118))
    ;
    uVar7 = *puVar2;
    uVar8 = puVar2[1];
    uVar9 = puVar2[2];
    uVar10 = puVar2[3];
  }
  FUN_00478670(uVar7,uVar8,uVar9,uVar10);
  puVar2 = (undefined4 *)FUN_00476f00(local_40,param_1 + 0x2c4,puVar4);
  puVar3 = puVar4;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar4 = (undefined4 *)FUN_00476f00(local_40,param_1 + 0x204,puVar4);
  iVar5 = *(int *)(param_1 + 0x28);
  puVar2 = puVar4;
  puVar3 = (undefined4 *)(param_1 + 0x244);
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  if (*(int *)(iVar5 + 0x58) != 0) {
    puVar2 = (undefined4 *)(param_1 + 0x284);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar2 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar2 = puVar2 + 1;
    }
    *(undefined4 *)(param_1 + 700) = 0;
    *(undefined4 *)(param_1 + 0x2b8) = 0;
    *(undefined4 *)(param_1 + 0x2b4) = 0;
  }
  FUN_005739d0();
  iVar5 = 0;
  if (0 < *(int *)(param_1 + 0x34)) {
    do {
      FUN_00573d50();
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(param_1 + 0x34));
  }
  return;
}

