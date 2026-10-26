/* Original Meteor.exe static export @ 004aa370; original sample not executed. */
/* XREF 005a9458 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004aa370(int param_1,int param_2,short *param_3)

{
  short sVar1;
  float fVar2;
  int local_4;
  
  local_4 = param_2;
  FUN_0049d3c0(&param_2,&local_4);
  if (param_2 != *(int *)(param_1 + 4)) {
    if (*(int *)(param_2 + 0xdc) != 1) {
      *(undefined4 *)(param_2 + 0x30) = *(undefined4 *)(param_2 + 0x18);
      *(undefined4 *)(param_2 + 0x34) = *(undefined4 *)(param_2 + 0x1c);
      *(undefined4 *)(param_2 + 0x38) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)(param_2 + 0xdc) = 1;
    }
    fVar2 = (float)(int)*param_3 * _DAT_005a83ec;
    *(float *)(param_2 + 0x18) = fVar2;
    *(float *)(param_2 + 0x3c) = fVar2;
    fVar2 = (float)(int)param_3[1] * _DAT_005a83ec;
    *(float *)(param_2 + 0x1c) = fVar2;
    *(float *)(param_2 + 0x40) = fVar2;
    fVar2 = (float)(int)param_3[2] * _DAT_005a83ec;
    *(float *)(param_2 + 0x20) = fVar2;
    *(float *)(param_2 + 0x44) = fVar2;
    *(float *)(param_2 + 0x24) = (float)(int)param_3[3] * _DAT_005a8414;
    sVar1 = param_3[4];
    *(undefined4 *)(param_2 + 0x2c) = 0;
    *(float *)(param_2 + 0x28) = (float)(int)sVar1 * _DAT_005a8414;
    *(float *)(param_2 + 0x48) = (float)(int)param_3[5] * _DAT_005a9bcc;
    *(float *)(param_2 + 0x4c) = (float)(int)param_3[6] * _DAT_005a9bcc;
    *(float *)(param_2 + 0x50) = (float)(int)param_3[7] * _DAT_005a9bcc;
    *(int *)(param_2 + 0x54) = (int)param_3[8];
    *(uint *)(param_2 + 0x58) = (uint)(ushort)param_3[9];
    *(int *)(param_2 + 0x250) = *(int *)(param_2 + 0x250) + 1;
    if (*(int *)(param_2 + 0x200) == 1) {
      *(undefined4 *)(param_2 + 0x210) = 0;
    }
    if ((*(uint *)(param_2 + 0x54) & 0x1000) != 0) {
      *(undefined4 *)(param_2 + 0x20c) = 1;
      return;
    }
    *(undefined4 *)(param_2 + 0x20c) = 0;
  }
  return;
}

