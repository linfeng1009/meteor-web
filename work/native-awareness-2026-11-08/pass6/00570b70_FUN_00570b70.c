/* Original Meteor.exe static export @ 00570b70; original sample not executed. */
/* XREF 0055da97 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00570b70(float *param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  ushort uVar6;
  float local_20;
  float local_1c;
  
  fVar1 = *param_2 - *param_4;
  local_20 = param_2[1] - param_4[1];
  local_1c = param_2[2] - param_4[2];
  fVar2 = *param_1 + *param_3;
  fVar3 = param_1[1] + param_3[1];
  fVar4 = param_1[2] + param_3[2];
  if (fVar1 < _DAT_005a83e4) {
    fVar1 = -fVar1;
  }
  if (local_20 < _DAT_005a83e4) {
    local_20 = -local_20;
  }
  if (local_1c < _DAT_005a83e4) {
    local_1c = -local_1c;
  }
  uVar5 = (uint)(ushort)((ushort)(fVar1 < fVar2) << 8 | (ushort)(NAN(fVar1) || NAN(fVar2)) << 10 |
                        (ushort)(fVar1 == fVar2) << 0xe);
  if ((fVar1 < fVar2 != (fVar1 == fVar2)) &&
     (uVar5 = (uint)(ushort)((ushort)(local_20 < fVar3) << 8 |
                             (ushort)(NAN(local_20) || NAN(fVar3)) << 10 |
                            (ushort)(local_20 == fVar3) << 0xe),
     local_20 < fVar3 != (local_20 == fVar3))) {
    uVar6 = (ushort)(local_1c < fVar4) << 8 | (ushort)(NAN(local_1c) || NAN(fVar4)) << 10 |
            (ushort)(local_1c == fVar4) << 0xe;
    uVar5 = (uint)uVar6;
    if (local_1c < fVar4 != (local_1c == fVar4)) {
      return CONCAT31((uint3)(byte)(uVar6 >> 8),1);
    }
  }
  return uVar5;
}

