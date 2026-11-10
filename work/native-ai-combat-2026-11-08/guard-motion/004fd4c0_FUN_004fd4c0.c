/* Original Meteor.exe static export @ 004fd4c0; original sample not executed. */
/* XREF 004fd166 UNCONDITIONAL_CALL */
/* XREF 004fd1df UNCONDITIONAL_CALL */
/* XREF 004fd257 UNCONDITIONAL_CALL */
/* XREF 004fd567 UNCONDITIONAL_CALL */
/* XREF 00504a92 UNCONDITIONAL_CALL */
/* XREF 00504b33 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004fd4c0(int param_1,undefined4 param_2)

{
  undefined4 local_c;
  undefined4 local_8;
  float local_4;
  
  local_c = *(undefined4 *)(param_1 + 0x18);
  local_8 = *(undefined4 *)(param_1 + 0x1c);
  local_4 = _DAT_005a8dbc;
  if (-1 < *(int *)(param_1 + 0x58)) {
    local_4 = *(float *)(&DAT_00666a08 + *(int *)(param_1 + 0x58) * 0x38);
  }
  local_4 = *(float *)(param_1 + 0x20) + local_4;
  FUN_00501670(&local_c,param_2,param_1 + 0xe0,param_1 + 0x40);
  return;
}

