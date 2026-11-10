/* Original Meteor.exe static export @ 00589a40; original sample not executed. */
/* XREF 005b1438 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00589a40(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 auStack_a0 [11];
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  float fStack_68;
  undefined1 *puStack_64;
  float fStack_50;
  undefined1 auStack_40 [64];
  
  puStack_64 = (undefined1 *)0x589a4e;
  FUN_00582000();
  fStack_50 = 0.0;
  if (*(int *)(*(int *)(param_1 + 0x1ec) + 8) == 1) {
    fStack_50 = *(float *)(param_1 + 0x26c) * _DAT_005a83e8;
  }
  *(undefined4 *)(param_1 + 0x1fc) = 0;
  *(undefined4 *)(param_1 + 0x200) = 0;
  *(float *)(param_1 + 0x204) = fStack_50;
  *(undefined4 *)(param_1 + 0x1f0) = *(undefined4 *)(param_1 + 0x268);
  *(undefined4 *)(param_1 + 500) = *(undefined4 *)(param_1 + 0x26c);
  *(undefined4 *)(param_1 + 0x1f8) = *(undefined4 *)(param_1 + 0x270);
  fVar1 = *(float *)(param_1 + 500) * _DAT_005a83e8;
  fVar2 = *(float *)(param_1 + 0x1f8) * _DAT_005a83e8;
  *(float *)(param_1 + 0x1f0) = *(float *)(param_1 + 0x1f0) * _DAT_005a83e8;
  *(float *)(param_1 + 500) = fVar1;
  *(float *)(param_1 + 0x1f8) = fVar2;
  puStack_64 = (undefined1 *)0x589b09;
  FUN_00477200();
  puStack_64 = (undefined1 *)0x0;
  fStack_68 = fStack_50;
  uStack_6c = 0;
  uStack_70 = 0;
  uStack_74 = 0x589b18;
  FUN_004781d0();
  puStack_64 = (undefined1 *)0x3fc90fdb;
  fStack_68 = 8.137178e-39;
  FUN_00477f40();
  puStack_64 = auStack_40;
  fStack_68 = 8.137194e-39;
  puVar3 = (undefined4 *)FUN_00477ad0();
  fStack_68 = *(float *)(param_1 + 0x26c);
  uStack_6c = *(undefined4 *)(param_1 + 0x268);
  puVar5 = (undefined4 *)(param_1 + 0x198);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  puStack_64 = *(undefined1 **)(param_1 + 0x270);
  uStack_70 = 0x589b65;
  FUN_0047c570();
  puVar3 = (undefined4 *)(param_1 + 0x158);
  puVar5 = auStack_a0;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  FUN_0047de20();
  return;
}

