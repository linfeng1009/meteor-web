/* Original Meteor.exe static export @ 00547f80; original sample not executed. */
/* XREF 00466908 UNCONDITIONAL_CALL */
/* XREF 004662d0 UNCONDITIONAL_CALL */
/* XREF 004658b2 UNCONDITIONAL_CALL */

undefined4
FUN_00547f80(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,undefined4 param_6,
            undefined4 *param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,
            int param_11,int param_12)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  float local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 local_30 [4];
  undefined4 local_2c [11];
  
  local_70 = (float)param_1;
  local_64 = 0x3c23d70a;
  local_68 = param_5;
  local_54 = 0x3c23d70a;
  local_6c = (float)param_2;
  local_a4 = (float)param_3;
  local_48 = param_5;
  local_58 = param_5;
  local_5c = (float)param_4 + local_6c;
  local_44 = 0x3c23d70a;
  local_38 = param_5;
  local_34 = 0x3c23d70a;
  local_50 = local_a4 + local_70;
  if (param_11 == 0) {
    local_c4 = 0;
    local_bc = 0;
    local_b4 = 0x3f800000;
    local_ac = 0x3f800000;
  }
  else {
    local_c4 = 0x3f800000;
    local_bc = 0x3f800000;
    local_b4 = 0;
    local_ac = 0;
  }
  if (param_12 == 0) {
    local_c0 = 0x3f800000;
    local_b8 = 0;
    local_b0 = 0;
    local_a8 = 0x3f800000;
  }
  else {
    local_c0 = 0;
    local_b8 = 0x3f800000;
    local_b0 = 0x3f800000;
    local_a8 = 0;
  }
  local_7c = 0x3f800000;
  local_78 = 0x3f800000;
  local_74 = 0x3f800000;
  local_a0 = 0x3f800000;
  local_9c = 0x3f800000;
  local_98 = 0x3f800000;
  local_94 = 0x3f800000;
  local_90 = 0x3f800000;
  local_8c = 0x3f800000;
  local_88 = 0x3f800000;
  local_84 = 0x3f800000;
  local_80 = 0x3f800000;
  local_60 = local_70;
  local_4c = local_5c;
  local_40 = local_50;
  local_3c = local_6c;
  uVar1 = FUN_0040ed80(&local_7c,&local_a0,&local_94,&local_88,0x42000000,param_6,0,1,param_8,
                       param_9,param_10);
  FUN_004059e0(6);
  FUN_00406520(0,0x10);
  if (param_7 == (undefined4 *)0x0) {
    FUN_0040cc10(0,&local_70,0,&local_c4,4,uVar1,0);
  }
  else {
    puVar2 = local_2c;
    iVar3 = 4;
    do {
      puVar2[-1] = *param_7;
      *puVar2 = param_7[1];
      puVar2[1] = param_7[2];
      puVar2 = puVar2 + 3;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    FUN_0040cc10(0,&local_70,local_30,&local_c4,4,uVar1,0);
  }
  uVar1 = FUN_00405df0(0);
  FUN_004054e0(uVar1,4,0);
  return uVar1;
}

