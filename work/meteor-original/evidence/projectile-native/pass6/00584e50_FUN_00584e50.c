/* Original Meteor.exe static export @ 00584e50; original sample not executed. */
/* XREF 005b0f70 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00584e50(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 auStack_98 [11];
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined1 *puStack_5c;
  undefined1 auStack_40 [64];
  
  puStack_5c = (undefined1 *)0x584e5d;
  FUN_00582000();
  *(undefined4 *)(param_1 + 0x1fc) = 0;
  *(undefined4 *)(param_1 + 0x200) = 0;
  *(undefined4 *)(param_1 + 0x204) = 0;
  fVar1 = *(float *)(param_1 + 0x268) + *(float *)(param_1 + 0x268);
  *(float *)(param_1 + 0x1f0) = fVar1;
  *(float *)(param_1 + 500) = fVar1;
  *(float *)(param_1 + 0x1f8) = fVar1;
  fVar1 = *(float *)(param_1 + 500) * _DAT_005a83e8;
  fVar2 = *(float *)(param_1 + 0x1f8) * _DAT_005a83e8;
  *(float *)(param_1 + 0x1f0) = *(float *)(param_1 + 0x1f0) * _DAT_005a83e8;
  *(float *)(param_1 + 500) = fVar1;
  *(float *)(param_1 + 0x1f8) = fVar2;
  puStack_5c = (undefined1 *)0x584ef8;
  FUN_00477200();
  puStack_5c = (undefined1 *)0x0;
  uStack_60 = 0;
  uStack_64 = 0;
  uStack_68 = 0;
  uStack_6c = 0x584f07;
  FUN_004781d0();
  puStack_5c = auStack_40;
  uStack_60 = 0x584f13;
  puVar3 = (undefined4 *)FUN_00477ad0();
  puVar5 = (undefined4 *)(param_1 + 0x198);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  if (DAT_0072baec == 0) {
    puStack_5c = (undefined1 *)0x4;
    uStack_60 = 0x584f37;
    FUN_0047c140();
    puStack_5c = (undefined1 *)0x3f800000;
    uStack_60 = 0x584f46;
    FUN_0047d2c0();
    puVar3 = (undefined4 *)(param_1 + 0x158);
    puVar5 = auStack_98;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    FUN_0047de20();
  }
  return;
}

