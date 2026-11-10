/* Original Meteor.exe static export @ 00407760; original sample not executed. */
/* XREF 004076fa UNCONDITIONAL_CALL */
/* XREF 00407711 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407760(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_80 [2];
  undefined4 local_78;
  undefined4 local_60;
  undefined4 local_58;
  undefined1 local_40 [20];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_1c;
  undefined4 local_18;
  
  FUN_00430c40(param_1);
  FUN_00430c40(local_40);
  local_2c = 0;
  local_18 = 0;
  local_28 = 0x3f800000;
  local_1c = 0xbf800000;
  iVar3 = 0;
  do {
    fVar2 = param_2[2] * param_1[8] + param_2[1] * param_1[4] + *param_1 * *param_2;
    fVar1 = param_1[5] * param_2[1] + param_1[1] * *param_2 + param_1[9] * param_2[2];
    if (fVar2 <= _DAT_005a83e4) {
      fVar2 = -fVar2;
    }
    if (fVar2 < _DAT_005a8408) {
      if (fVar1 <= _DAT_005a83e4) {
        fVar1 = -fVar1;
      }
      if (fVar1 < _DAT_005a8408) {
        fVar1 = (param_2[1] * param_1[6] + param_2[2] * param_1[10] + param_1[2] * *param_2) -
                _DAT_005a83f4;
        if (fVar1 <= _DAT_005a83e4) {
          fVar1 = -fVar1;
        }
        if (fVar1 < _DAT_005a8408) {
          fVar1 = param_3[2] * param_1[8] + *param_1 * *param_3 + param_3[1] * param_1[4];
          fVar2 = fVar1;
          if (fVar1 <= _DAT_005a83e4) {
            fVar2 = -fVar1;
          }
          if (fVar2 < _DAT_005a8408) {
            if (_DAT_005a83e4 <=
                param_1[1] * *param_3 + param_3[1] * param_1[5] + param_3[2] * param_1[9]) {
              return;
            }
            FUN_00430c40(&local_c0);
            local_c0 = 0xbf800000;
            local_ac = 0xbf800000;
            local_bc = 0;
            local_b0 = 0;
            FUN_004312e0(param_1,param_1,&local_c0);
            return;
          }
          if (fVar1 < _DAT_005a83e4) {
            FUN_00430c40(&local_c0);
            local_bc = 0xbf800000;
            local_b0 = 0x3f800000;
          }
          else {
            FUN_00430c40(&local_c0);
            local_bc = 0x3f800000;
            local_b0 = 0xbf800000;
          }
          goto LAB_00407b2a;
        }
      }
    }
    FUN_004312e0(param_1,param_1,local_40);
    iVar3 = iVar3 + 1;
    if (3 < iVar3) {
      FUN_00430c40(param_1);
      FUN_00430c40(local_80);
      local_80[0] = 0;
      local_58 = 0;
      local_78 = 0xbf800000;
      local_60 = 0x3f800000;
      FUN_004312e0(param_1,param_1,local_80);
      if (param_2[1] * param_1[6] + param_2[2] * param_1[10] + param_1[2] * *param_2 < _DAT_005a83e4
         ) {
        FUN_00430c40(local_80);
        local_80[0] = 0xbf800000;
        local_58 = 0xbf800000;
        local_78 = 0;
        local_60 = 0;
        FUN_004312e0(param_1,param_1,local_80);
      }
      fVar1 = param_3[2] * param_1[8] + *param_1 * *param_3 + param_3[1] * param_1[4];
      fVar2 = fVar1;
      if (fVar1 <= _DAT_005a83e4) {
        fVar2 = -fVar1;
      }
      if (_DAT_005a8408 <= fVar2) {
        if (_DAT_005a83e4 <= fVar1) {
          FUN_00430c40(&local_c0);
          local_bc = 0x3f800000;
          local_b0 = 0xbf800000;
        }
        else {
          FUN_00430c40(&local_c0);
          local_bc = 0xbf800000;
          local_b0 = 0x3f800000;
        }
LAB_00407b2a:
        local_c0 = 0;
        local_ac = 0;
        FUN_004312e0(param_1,param_1,&local_c0);
      }
      else if (param_1[1] * *param_3 + param_3[1] * param_1[5] + param_3[2] * param_1[9] <
               _DAT_005a83e4) {
        FUN_00430c40(&local_c0);
        local_c0 = 0xbf800000;
        local_ac = 0xbf800000;
        local_bc = 0;
        local_b0 = 0;
        FUN_004312e0(param_1,param_1,&local_c0);
        return;
      }
      return;
    }
  } while( true );
}

