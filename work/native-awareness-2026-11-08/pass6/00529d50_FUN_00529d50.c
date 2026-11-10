/* Original Meteor.exe static export @ 00529d50; original sample not executed. */
/* XREF 0052a5cc UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00529d50(float *param_1,int param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  float10 fVar5;
  float local_d0;
  float local_cc;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  double local_94;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  int local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
  undefined1 local_48 [12];
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  float local_4;
  
  cVar4 = FUN_00528e40(param_1);
  if (cVar4 == '\0') {
    return;
  }
  FUN_0052aae0(0xc000,&local_80);
  FUN_0052ab80(0xd000,&local_70);
  fVar1 = param_1[0xd9];
  local_b0 = param_1[0xe];
  local_d0 = param_1[0x3f];
  local_c4 = param_1[0x15];
  local_98 = param_1[0xee];
  local_a4 = param_1[0x23];
  local_c0 = param_1[0x16];
  local_94 = (double)CONCAT44(local_94._4_4_,param_1[0xe0]);
  local_bc = param_1[0x17];
  local_60 = param_1[0x1c];
  local_a0 = param_1[0x24];
  local_9c = param_1[0x25];
  local_b4 = param_1[0xe7];
  local_5c = param_1[0x1d];
  local_58 = param_1[0x1e];
  cVar4 = *(char *)((int)param_1 + 0xe03);
  local_a8 = *param_1;
  local_b8 = param_1[7];
  FUN_00529ac0(0x100a,&local_ac);
  FUN_00529b20(0x1004,&local_3c);
  FUN_00529b20(0x1006,&local_30);
  FUN_00529b20(0x100f,&local_54);
  if (*(char *)(param_1 + 0x39a) == '\0') {
    *param_5 = local_b0;
    fVar1 = local_ac * local_d0 * SQRT((float)_DAT_005a8460);
    param_3[1] = fVar1;
    *param_3 = fVar1;
LAB_00529eb2:
    param_4[1] = 0.0;
    *param_4 = 0.0;
    return;
  }
  if (cVar4 == '\0') {
    local_c4 = local_c4 - local_3c;
    local_c0 = local_c0 - local_38;
    local_bc = local_bc - local_34;
  }
  local_4c = -local_4c;
  FUN_00529c40(local_48,&local_54,&local_6c);
  FUN_00529ca0(&local_6c);
  FUN_00529c40(&local_54,&local_6c,&local_8c);
  FUN_00529ca0(&local_8c);
  local_7c = local_54;
  local_78 = local_50;
  local_74 = local_4c;
  FUN_00529ca0(&local_7c);
  local_24 = local_6c;
  local_20 = local_8c;
  local_18 = local_68;
  local_14 = local_88;
  local_1c = local_7c;
  local_c = local_64;
  local_8 = local_84;
  local_10 = local_78;
  local_4 = local_74;
  FUN_00529ce0(&local_24,&local_c4);
  fVar5 = (float10)FUN_00529c80(&local_c4,&local_c4);
  local_cc = (float)SQRT(fVar5);
  if (local_70 == 0) {
    local_d0 = local_ac * local_d0;
  }
  else {
    if (local_98 <= local_cc) {
      *param_5 = local_b0;
      param_4[1] = 0.0;
      *param_4 = 0.0;
      param_4 = param_3;
      goto LAB_00529eb2;
    }
    if (local_70 == 0xd002) {
      if (local_cc < fVar1) {
        local_cc = fVar1;
      }
      if (local_98 < local_cc) {
        local_cc = local_98;
      }
    }
    local_d0 = (local_ac * fVar1 * local_d0) / ((local_cc - fVar1) * local_94._0_4_ + fVar1);
  }
  local_8c = -local_c4;
  local_88 = -local_c0;
  local_84 = -local_bc;
  FUN_00529ca0(&local_60);
  FUN_00529ca0(&local_8c);
  FUN_00529c80(&local_60,&local_8c);
  fVar5 = (float10)FUN_00509d10();
  fVar5 = fVar5 * (float10)_DAT_005ad378;
  if ((fVar5 < (float10)local_a8) || (fVar5 < (float10)local_b8 == (fVar5 == (float10)local_b8))) {
    if (fVar5 <= (float10)local_b8) goto LAB_0052a17a;
    fVar5 = (float10)local_b4 - (float10)_DAT_005a83f4;
  }
  else {
    fVar5 = (((float10)local_b4 - (float10)_DAT_005a83f4) * (fVar5 - (float10)local_a8)) /
            ((float10)local_b8 - (float10)local_a8);
  }
  local_d0 = (float)((fVar5 + (float10)_DAT_005a83f4) * (float10)local_d0);
LAB_0052a17a:
  local_a4 = local_a4 - local_30;
  local_a0 = local_a0 - local_2c;
  local_9c = local_9c - local_28;
  FUN_00529ce0(&local_24,&local_a4);
  if ((local_80 == _DAT_005a83e4) || (local_cc == _DAT_005a83e4)) {
    local_94 = (double)local_b0;
    fVar5 = (float10)FUN_00529c80(&local_a4,&local_c4);
    fVar5 = (float10)local_94 / (fVar5 * (float10)_DAT_005ad370 + (float10)_DAT_005a8418);
  }
  else {
    local_94 = (double)(local_b0 * local_80);
    fVar5 = (float10)FUN_00529c80(&local_a4,&local_c4);
    fVar5 = (float10)local_94 /
            (fVar5 / ((float10)local_cc * (float10)_DAT_005ad374) + (float10)_DAT_005a8418);
  }
  *param_5 = (float)fVar5;
  if (local_cc == _DAT_005a83e4) {
    local_cc = 0.5;
    fVar1 = _DAT_005a83e8;
  }
  else {
    FUN_00529ca0(&local_c4);
    if (_DAT_005a83e4 <= local_c4) {
      fVar1 = SQRT(local_c4) * (float)_DAT_005a8f80 + (float)_DAT_005a8460;
    }
    else {
      fVar1 = (float)_DAT_005a8460 - SQRT(-local_c4) * (float)_DAT_005a8f80;
    }
    if (_DAT_005a83e4 <= local_bc) {
      local_cc = SQRT(local_bc) * (float)_DAT_005a8f80 + (float)_DAT_005a8460;
    }
    else {
      local_cc = (float)_DAT_005a8460 - SQRT(-local_bc) * (float)_DAT_005a8f80;
    }
  }
  if (param_2 == 1) {
    *param_3 = local_d0;
    *param_4 = local_d0 * _DAT_005a83e4;
    FUN_00525570();
    return;
  }
  if (param_2 == 3) {
    fVar2 = SQRT(_DAT_005a83f4 - fVar1) * local_d0;
    *param_3 = fVar2;
    param_3[1] = SQRT(fVar1) * local_d0;
    param_3[2] = SQRT(local_cc) * local_d0;
    *param_4 = fVar2 * _DAT_005a83e4;
    param_4[1] = SQRT(fVar1) * local_d0 * _DAT_005a83e4;
    param_4[2] = SQRT(local_cc) * local_d0 * _DAT_005a83e4;
    FUN_00525570();
    return;
  }
  if (param_2 == 4) {
    fVar3 = _DAT_005a83f4 - local_cc;
    fVar2 = _DAT_005a83f4 - fVar1;
    local_b4 = SQRT(fVar3 * fVar2) * local_d0;
    *param_3 = local_b4;
    fVar3 = SQRT(fVar3 * fVar1) * local_d0;
    local_94 = (double)CONCAT44(local_94._4_4_,fVar3);
    param_3[1] = fVar3;
    local_b8 = SQRT(fVar2 * local_cc) * local_d0;
    param_3[2] = local_b8;
    local_d0 = SQRT(fVar1 * local_cc) * local_d0;
    param_3[3] = local_d0;
    *param_4 = local_b4 * _DAT_005a83e4;
    param_4[1] = fVar3 * _DAT_005a83e4;
    param_4[2] = local_b8 * _DAT_005a83e4;
    param_4[3] = local_d0 * _DAT_005a83e4;
    FUN_00525570();
    return;
  }
  fVar2 = SQRT(_DAT_005a83f4 - fVar1) * local_d0;
  *param_3 = fVar2;
  param_3[1] = SQRT(fVar1) * local_d0;
  *param_4 = fVar2 * _DAT_005a83e4;
  param_4[1] = SQRT(fVar1) * local_d0 * _DAT_005a83e4;
  FUN_00525570();
  return;
}

