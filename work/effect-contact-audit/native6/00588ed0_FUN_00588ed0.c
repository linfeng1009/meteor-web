/* Original Meteor.exe static export @ 00588ed0; original sample not executed. */
/* XREF 005b1328 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00588ed0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 auStack_5c [10];
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float fStack_24;
  undefined4 uStack_20;
  float fStack_10;
  
  uStack_20 = 0x588edd;
  FUN_00582000();
  fStack_10 = 0.0;
  if (*(int *)(*(int *)(param_1 + 0x1ec) + 8) == 1) {
    fStack_10 = *(float *)(param_1 + 0x270) * _DAT_005a83e8;
  }
  *(undefined4 *)(param_1 + 0x1fc) = 0;
  *(undefined4 *)(param_1 + 0x200) = 0;
  *(float *)(param_1 + 0x204) = fStack_10;
  if (*(float *)(param_1 + 0x26c) <= *(float *)(param_1 + 0x268)) {
    fVar1 = *(float *)(param_1 + 0x268);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x26c);
  }
  *(float *)(param_1 + 0x1f0) = fVar1 + fVar1;
  *(float *)(param_1 + 500) = fVar1 + fVar1;
  *(undefined4 *)(param_1 + 0x1f8) = *(undefined4 *)(param_1 + 0x270);
  fVar1 = *(float *)(param_1 + 500) * _DAT_005a83e8;
  fVar2 = *(float *)(param_1 + 0x1f8) * _DAT_005a83e8;
  *(float *)(param_1 + 0x1f0) = *(float *)(param_1 + 0x1f0) * _DAT_005a83e8;
  *(float *)(param_1 + 500) = fVar1;
  *(float *)(param_1 + 0x1f8) = fVar2;
  uStack_20 = 0x588fb3;
  FUN_00477200();
  uStack_20 = 0;
  fStack_24 = fStack_10;
  uStack_28 = 0;
  uStack_2c = 0;
  uStack_30 = 0x588fc2;
  FUN_004781d0();
  uStack_20 = *(undefined4 *)(param_1 + 0x270);
  fStack_24 = *(float *)(param_1 + 0x268);
  uStack_28 = *(undefined4 *)(param_1 + 0x26c);
  uStack_2c = *(undefined4 *)(param_1 + 0x278);
  uStack_30 = *(undefined4 *)(param_1 + 0x274);
  uStack_34 = 0x588ff6;
  FUN_0047cdb0();
  puVar4 = (undefined4 *)(param_1 + 0x158);
  puVar5 = auStack_5c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  FUN_0047de20();
  return;
}

