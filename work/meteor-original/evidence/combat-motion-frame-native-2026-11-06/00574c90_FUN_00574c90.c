/* Original Meteor.exe static export @ 00574c90; original sample not executed. */
/* XREF 00574c6a UNCONDITIONAL_CALL */
/* XREF 0057b519 UNCONDITIONAL_CALL */
/* XREF 0057b73f UNCONDITIONAL_CALL */

/* WARNING: Removing unreachable block (ram,0x00574cde) */
/* WARNING: Removing unreachable block (ram,0x00574cee) */
/* WARNING: Removing unreachable block (ram,0x00574cf9) */
/* WARNING: Removing unreachable block (ram,0x00574d5f) */
/* WARNING: Removing unreachable block (ram,0x00574d64) */
/* WARNING: Removing unreachable block (ram,0x00574d66) */
/* WARNING: Removing unreachable block (ram,0x00574d6b) */
/* WARNING: Removing unreachable block (ram,0x00574d6d) */
/* WARNING: Removing unreachable block (ram,0x00574d12) */
/* WARNING: Removing unreachable block (ram,0x00574d19) */
/* WARNING: Removing unreachable block (ram,0x00574d1b) */
/* WARNING: Removing unreachable block (ram,0x00574d20) */
/* WARNING: Removing unreachable block (ram,0x00574d22) */
/* WARNING: Removing unreachable block (ram,0x00574d34) */
/* WARNING: Removing unreachable block (ram,0x00574d84) */
/* WARNING: Removing unreachable block (ram,0x00574d96) */
/* WARNING: Removing unreachable block (ram,0x00574cea) */

void __fastcall FUN_00574c90(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0x3f800000;
  param_1[0xb] = 1;
  iVar3 = param_1[5];
  iVar2 = param_1[5];
  iVar1 = param_1[4];
  for (iVar4 = iVar1; iVar4 != iVar2; iVar4 = iVar4 + 0xc) {
    FUN_0047a7e0(0);
  }
  iVar3 = (int)((ulonglong)((longlong)(iVar3 - iVar1) * -0x2aaaaaab) >> 0x20);
  param_1[5] = param_1[5] + ((iVar3 >> 1) - (iVar3 >> 0x1f)) * 0xc;
  param_1[0xd] = 0xffffffff;
  param_1[0xc] = 0xffffffff;
  param_1[0x10] = 0x3f800000;
  param_1[0xf] = 0x3f800000;
  param_1[0xe] = 0xffffffff;
  param_1[0x11] = 0xffffffff;
  param_1[0x16] = 0xffffffff;
  param_1[0x15] = 0xffffffff;
  param_1[0x14] = 0xffffffff;
  param_1[0x13] = 0xffffffff;
  param_1[0x12] = 0xffffffff;
  param_1[0x18] = 0x3f800000;
  param_1[0x17] = 0x3f800000;
  param_1[0x19] = 0xbf800000;
  return;
}

