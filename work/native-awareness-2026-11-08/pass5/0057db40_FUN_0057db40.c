/* Original Meteor.exe static export @ 0057db40; original sample not executed. */
/* XREF 005615bf UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0057db40(int param_1,float param_2)

{
  float fVar1;
  
  fVar1 = param_2 - *(float *)(param_1 + 0x168);
  *(float *)(param_1 + 0x30) = fVar1;
  fVar1 = fVar1 * _DAT_005a83e8;
  *(float *)(param_1 + 0x24) = param_2;
  *(float *)(param_1 + 0x164) = param_2;
  *(float *)(param_1 + 0x3c) = fVar1;
  *(float *)(param_1 + 0xc) = fVar1 + *(float *)(param_1 + 0x18);
  return;
}

