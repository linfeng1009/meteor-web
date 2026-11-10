/* Original Meteor.exe static export @ 004fc8a0; original sample not executed. */
/* XREF 004fc9e1 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __thiscall FUN_004fc8a0(int param_1,float *param_2)

{
  float fVar1;
  char cVar2;
  undefined2 extraout_var;
  float10 fVar3;
  float10 fVar4;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_24 = *(float *)(param_1 + 0x18);
  local_20 = *(float *)(param_1 + 0x1c);
  local_1c = _DAT_005a8dbc;
  if (-1 < *(int *)(param_1 + 0x58)) {
    local_1c = *(float *)(&DAT_00666a08 + *(int *)(param_1 + 0x58) * 0x38);
  }
  local_1c = *(float *)(param_1 + 0x20) + local_1c;
  fVar1 = (float)(int)**(short **)(param_1 + 0x10) * *(float *)(param_1 + 0x114);
  local_18 = *param_2 - local_24;
  local_14 = param_2[1] - local_20;
  local_10 = param_2[2] - local_1c;
  local_c = local_18;
  local_8 = local_14;
  local_4 = local_10;
  fVar3 = (float10)FUN_0047ed20();
  fVar4 = (float10)fVar1 * (float10)fVar1;
  if (fVar4 >= fVar3) {
    cVar2 = FUN_004c1360(&local_24,param_2,0,0);
    return (uint)(cVar2 == '\0');
  }
  return CONCAT22(extraout_var,
                  (ushort)(fVar4 < fVar3) << 8 | (ushort)(NAN(fVar4) || NAN(fVar3)) << 10 |
                  (ushort)(fVar4 == fVar3) << 0xe);
}

