/* Original Meteor.exe static export @ 00502050; original sample not executed. */
/* XREF 004c0d9e UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00502050(float param_1)

{
  int *piVar1;
  undefined *puVar2;
  float local_60 [4];
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
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
  
  local_60[0] = param_1 * _DAT_005a8ff0;
  piVar1 = &DAT_005ca36c;
  puVar2 = &DAT_005ca30c;
  local_4c = param_1 * _DAT_005a83e8;
  local_60[1] = local_60[0];
  local_60[2] = local_60[0];
  local_60[3] = local_60[0];
  local_50 = local_60[0];
  local_48 = local_60[0];
  local_44 = local_4c;
  local_40 = local_4c;
  local_3c = local_60[0];
  local_38 = local_4c;
  local_34 = local_60[0];
  local_30 = local_4c;
  local_2c = local_60[0];
  local_28 = local_60[0];
  local_24 = local_4c;
  local_20 = local_60[0];
  local_1c = local_4c;
  local_18 = local_4c;
  local_14 = local_4c;
  local_10 = local_4c;
  local_c = local_4c;
  local_8 = local_4c;
  local_4 = local_60[0];
  do {
    FUN_005019e0(6);
    FUN_00501cf0(puVar2);
    FUN_00501c20(local_60 + piVar1[-1] * 3);
    FUN_00501c20(local_60 + *piVar1 * 3);
    FUN_00501c20(local_60 + piVar1[1] * 3);
    FUN_00501c20(local_60 + piVar1[2] * 3);
    FUN_00501a20();
    puVar2 = puVar2 + -0xc;
    piVar1 = piVar1 + -4;
  } while (0x5ca2cf < (int)puVar2);
  return;
}

