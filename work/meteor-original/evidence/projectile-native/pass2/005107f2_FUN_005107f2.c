/* Original Meteor.exe static export @ 005107f2; original sample not executed. */
/* XREF 0050b797 UNCONDITIONAL_CALL */
/* XREF 0050b95b UNCONDITIONAL_CALL */
/* XREF 0050bc80 UNCONDITIONAL_CALL */
/* XREF 0050baab UNCONDITIONAL_CALL */
/* XREF 0050c06e UNCONDITIONAL_CALL */
/* XREF 0050b368 UNCONDITIONAL_CALL */

void FUN_005107f2(uint param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = (uint *)FUN_0051086e();
  iVar3 = 0;
  *puVar1 = param_1;
  puVar1 = &DAT_005cce30;
  do {
    if (param_1 == *puVar1) {
      puVar2 = (undefined4 *)FUN_00510865();
      *puVar2 = *(undefined4 *)(iVar3 * 8 + 0x5cce34);
      return;
    }
    puVar1 = puVar1 + 2;
    iVar3 = iVar3 + 1;
  } while ((int)puVar1 < 0x5ccf98);
  if ((0x12 < param_1) && (param_1 < 0x25)) {
    puVar2 = (undefined4 *)FUN_00510865();
    *puVar2 = 0xd;
    return;
  }
  if ((0xbb < param_1) && (param_1 < 0xcb)) {
    puVar2 = (undefined4 *)FUN_00510865();
    *puVar2 = 8;
    return;
  }
  puVar2 = (undefined4 *)FUN_00510865();
  *puVar2 = 0x16;
  return;
}

