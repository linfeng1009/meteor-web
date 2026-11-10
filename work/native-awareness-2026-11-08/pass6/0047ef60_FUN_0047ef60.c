/* Original Meteor.exe static export @ 0047ef60; original sample not executed. */
/* XREF 0058233a UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0047ef60(float *param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float local_c;
  float local_8;
  float local_4;
  
  fVar1 = ABS(param_2);
  fVar2 = ABS(param_3);
  if ((fVar1 <= fVar2) || (fVar1 <= ABS(param_4))) {
    if ((fVar2 <= fVar1) || (fVar2 <= ABS(param_4))) {
      local_4 = 0.0;
      if (param_3 != _DAT_005a83e4) {
        local_c = 1.0;
        if (param_2 <= _DAT_005a83e4) {
          local_c = -1.0;
        }
        local_8 = -((param_2 / param_3) * local_c);
        goto LAB_0047f15f;
      }
      local_8 = 1.0;
      if (param_3 <= _DAT_005a83e4) {
        local_8 = -1.0;
      }
      local_c = (param_3 / param_2) * local_8;
    }
    else {
      local_8 = 0.0;
      if (param_4 != _DAT_005a83e4) {
        local_c = 1.0;
        if (param_2 <= _DAT_005a83e4) {
          local_c = -1.0;
        }
        local_4 = -((param_2 / param_4) * local_c);
        goto LAB_0047f15f;
      }
      local_4 = 1.0;
      if (param_4 <= _DAT_005a83e4) {
        local_4 = -1.0;
      }
      local_c = (param_4 / param_2) * local_4;
    }
    local_c = -local_c;
  }
  else {
    local_c = 0.0;
    if (param_4 == _DAT_005a83e4) {
      local_4 = 1.0;
      if (param_4 <= _DAT_005a83e4) {
        local_4 = -1.0;
      }
      local_8 = -((param_4 / param_3) * local_4);
    }
    else {
      local_8 = 1.0;
      if (param_3 <= _DAT_005a83e4) {
        local_8 = -1.0;
      }
      local_4 = -((param_3 / param_4) * local_8);
    }
  }
LAB_0047f15f:
  FUN_0047ec40();
  *param_1 = local_c;
  param_1[1] = local_8;
  param_1[2] = local_4;
  return;
}

