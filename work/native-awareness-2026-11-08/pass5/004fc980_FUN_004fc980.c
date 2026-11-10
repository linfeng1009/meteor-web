/* Original Meteor.exe static export @ 004fc980; original sample not executed. */
/* XREF 004fc1f1 UNCONDITIONAL_CALL */
/* XREF 00504609 UNCONDITIONAL_CALL */
/* XREF 005046a9 UNCONDITIONAL_CALL */
/* XREF 00503e95 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004fc980(int param_1)

{
  uint3 uVar2;
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  float local_4;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar2 = (uint3)((uint)param_1 >> 8);
  if (*(int *)(param_1 + 0x48) < 1) {
    return (uint)uVar2 << 8;
  }
  if (*(char *)(param_1 + 0x62) != '\0') {
    return (uint)uVar2 << 8;
  }
  local_c = *(undefined4 *)(param_1 + 0x18);
  local_8 = *(undefined4 *)(param_1 + 0x1c);
  local_4 = _DAT_005ab844 * _DAT_005a83e8 + *(float *)(param_1 + 0x20);
  iVar1 = FUN_004fc8a0(&local_c);
  return iVar1;
}

