/* Original Meteor.exe static export @ 004fcc10; original sample not executed. */
/* XREF 004fe0ed UNCONDITIONAL_CALL */
/* XREF 004fe118 UNCONDITIONAL_CALL */
/* XREF 004fe13f UNCONDITIONAL_CALL */
/* XREF 004fe166 UNCONDITIONAL_CALL */
/* XREF 005042bd UNCONDITIONAL_CALL */
/* XREF 0050435f UNCONDITIONAL_CALL */
/* XREF 00504382 UNCONDITIONAL_CALL */
/* XREF 004fce5e UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004fcc10(int param_1,undefined1 param_2,float param_3)

{
  float fVar1;
  float fVar2;
  char cVar3;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_4;
  
  cVar3 = FUN_00501030();
  if (cVar3 == '\0') {
    return;
  }
  local_30 = *(float *)(param_1 + 0x18);
  local_2c = *(float *)(param_1 + 0x1c);
  local_28 = *(float *)(param_1 + 0x20);
  switch(param_2) {
  case 0x62:
    local_4 = param_3 * *(float *)(param_1 + 0x2c);
    local_24 = local_30 - param_3 * *(float *)(param_1 + 0x24);
    local_20 = local_2c - param_3 * *(float *)(param_1 + 0x28);
    local_28 = local_28 - local_4;
    break;
  default:
    goto switchD_004fcc5d_caseD_63;
  case 0x66:
    fVar1 = *(float *)(param_1 + 0x24);
    fVar2 = *(float *)(param_1 + 0x28);
    local_4 = *(float *)(param_1 + 0x2c);
    goto LAB_004fcd3b;
  case 0x6c:
    local_4 = param_3 * *(float *)(param_1 + 0x38);
    local_24 = local_30 - param_3 * *(float *)(param_1 + 0x30);
    local_20 = local_2c - param_3 * *(float *)(param_1 + 0x34);
    local_28 = local_28 - local_4;
    break;
  case 0x72:
    fVar1 = *(float *)(param_1 + 0x30);
    fVar2 = *(float *)(param_1 + 0x34);
    local_4 = *(float *)(param_1 + 0x38);
LAB_004fcd3b:
    local_4 = param_3 * local_4;
    local_20 = local_2c + param_3 * fVar2;
    local_24 = param_3 * fVar1 + local_30;
    local_28 = local_4 + local_28;
  }
  local_30 = local_24;
  local_2c = local_20;
  local_1c = local_28;
switchD_004fcc5d_caseD_63:
  local_10 = local_28 - _DAT_005a8b08;
  local_28 = local_28 + _DAT_005a8e78;
  local_18 = local_30;
  local_14 = local_2c;
  FUN_004c1360(&local_30,&local_18,0,0);
  return;
}

