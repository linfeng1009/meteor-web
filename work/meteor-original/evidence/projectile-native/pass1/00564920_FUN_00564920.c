/* Original Meteor.exe static export @ 00564920; original sample not executed. */
/* XREF 004bc6ab UNCONDITIONAL_CALL */
/* XREF 004c13e0 UNCONDITIONAL_CALL */
/* XREF 004f3e33 UNCONDITIONAL_CALL */
/* XREF 005651b8 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00564920(int param_1,float *param_2,float *param_3,undefined4 param_4)

{
  int iVar1;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (*(char *)(param_1 + 0x251) != '\0') {
    local_30 = *param_2;
    local_2c = param_2[1];
    local_18 = *param_3;
    local_28 = param_2[2];
    local_14 = param_3[1];
    local_10 = param_3[2];
    FUN_0047ec40();
    local_24 = local_18 * _DAT_005a84c8;
    local_20 = local_14 * _DAT_005a84c8;
    local_1c = local_10 * _DAT_005a84c8;
    local_3c = local_24 + *param_2;
    local_38 = local_20 + param_2[1];
    local_34 = local_1c + param_2[2];
    local_c = local_3c;
    local_8 = local_38;
    local_4 = local_34;
    iVar1 = FUN_005648b0(param_1 + 0x478,param_1 + 0x484,&local_30);
    while (iVar1 != 0) {
      FUN_00562dd0(&local_30,&local_3c);
      iVar1 = FUN_005644f0(&local_30,&local_3c,param_4,0);
      if (iVar1 != 0) {
        return 1;
      }
      local_c = local_3c + local_24;
      local_30 = local_3c;
      local_2c = local_38;
      local_28 = local_34;
      local_38 = local_38 + local_20;
      local_34 = local_34 + local_1c;
      local_3c = local_c;
      local_8 = local_38;
      local_4 = local_34;
      iVar1 = FUN_005648b0(param_1 + 0x478,param_1 + 0x484,&local_30);
    }
  }
  return 0;
}

