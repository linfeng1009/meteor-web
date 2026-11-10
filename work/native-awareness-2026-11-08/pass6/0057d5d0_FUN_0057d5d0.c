/* Original Meteor.exe static export @ 0057d5d0; original sample not executed. */
/* XREF 005609fc UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_0057d5d0(undefined4 *param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  float10 fVar5;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a660b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_0047bfd0();
  fVar5 = (float10)fcos((float10)_DAT_005afd10);
  param_1[0x4f] = 0;
  param_1[0x50] = 0;
  param_1[0x51] = 0;
  param_1[0x52] = 0;
  *(undefined1 *)(param_1 + 0x53) = 0;
  *(undefined1 *)((int)param_1 + 0x14d) = 0;
  *(undefined1 *)((int)param_1 + 0x14e) = 0;
  param_1[0x54] = 1;
  param_1[0x55] = 0;
  param_1[0x56] = 0x3f800000;
  param_1[0x57] = 0;
  param_1[0x58] = 0xb;
  param_1[0x5f] = 0x42700000;
  param_1[0x68] = 0x42700000;
  param_1[0x5b] = 0;
  param_1[0x5d] = 0;
  param_1[0x5c] = 0;
  *param_1 = 0;
  param_1[0x5e] = 0x41f00000;
  param_1[0x69] = 0x42a00000;
  local_4 = 0;
  param_1[0x6a] = (float)fVar5;
  param_1[10] = 0x447a0000;
  param_1[0xb] = 0x447a0000;
  param_1[0xc] = 0x43480000;
  param_1[0x5a] = 0;
  pfVar1 = (float *)(param_1 + 0xd);
  param_1[0x59] = param_1[0xc];
  fVar2 = (float)param_1[0xc] * _DAT_005a83e8;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = fVar2;
  fVar2 = (float)param_1[0xb] * _DAT_005a83e8;
  fVar3 = (float)param_1[0xc] * _DAT_005a83e8;
  *pfVar1 = (float)param_1[10] * _DAT_005a83e8;
  param_1[0xe] = fVar2;
  param_1[0xf] = fVar3;
  param_1[4] = (float)param_1[1] - *pfVar1;
  param_1[5] = (float)param_1[2] - (float)param_1[0xe];
  param_1[6] = (float)param_1[3] - (float)param_1[0xf];
  param_1[7] = (float)param_1[1] + *pfVar1;
  param_1[8] = (float)param_1[2] + (float)param_1[0xe];
  param_1[9] = (float)param_1[3] + (float)param_1[0xf];
  param_1[99] = 0x41000000;
  param_1[0x62] = 0x41000000;
  param_1[0x10] = 0x3f800000;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  fVar2 = (float)param_1[0x11] * _DAT_005a83e4;
  fVar3 = (float)param_1[0x12] * _DAT_005a83e4;
  param_1[0x10] = (float)param_1[0x10] * _DAT_005a83e4;
  param_1[0x11] = fVar2;
  param_1[0x12] = fVar3;
  param_1[0x78] = 0;
  param_1[0x79] = 0x3f800000;
  param_1[0x7a] = 0;
  param_1[0x7e] = 0x3f800000;
  param_1[0x7f] = 0;
  param_1[0x80] = 0;
  param_1[0x7b] = 0;
  param_1[0x7c] = 0;
  param_1[0x7d] = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x1b1) = 0;
  param_1[100] = 0x3f000000;
  param_1[0x60] = 0x3d4ccccd;
  param_1[0x61] = 0x3e4ccccd;
  param_1[0x65] = 0xbf800000;
  param_1[0x66] = 0xbf800000;
  *(undefined1 *)(param_1 + 0x6c) = 1;
  *(undefined1 *)(param_1 + 0x53) = 1;
  uVar4 = FUN_00475c00(0x3f800000,0x3f800000,0x3f800000,0x3f800000);
  param_1[0x6b] = uVar4;
  FUN_0047c140(4);
  ExceptionList = local_c;
  return param_1;
}

