/* Original Meteor.exe static export @ 005811c0; original sample not executed. */
/* XREF 0058391b UNCONDITIONAL_CALL */
/* XREF 00584da9 UNCONDITIONAL_CALL */
/* XREF 00585389 UNCONDITIONAL_CALL */
/* XREF 005856e9 UNCONDITIONAL_CALL */
/* XREF 0058596c UNCONDITIONAL_CALL */
/* XREF 00587a8a UNCONDITIONAL_CALL */
/* XREF 005880f9 UNCONDITIONAL_CALL */
/* XREF 0058874a UNCONDITIONAL_CALL */
/* XREF 00588e39 UNCONDITIONAL_CALL */
/* XREF 00589359 UNCONDITIONAL_CALL */
/* XREF 00589999 UNCONDITIONAL_CALL */
/* XREF 0058a21a UNCONDITIONAL_CALL */

undefined4 * __thiscall FUN_005811c0(undefined4 *param_1,undefined4 param_2,char param_3)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  void *pvVar4;
  int *piVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a6757;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  FUN_00402330();
  local_4 = 0;
  if (DAT_005d59ac == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_00403290(0x10);
  }
  else {
    puVar2 = DAT_005d59ac;
    DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
  }
  DAT_005d59e8 = 0;
  param_1[0x98] = puVar2;
  *puVar2 = puVar2;
  *(undefined4 *)(param_1[0x98] + 4) = param_1[0x98];
  local_4 = 1;
  FUN_00402330();
  local_4._0_1_ = 2;
  if (DAT_005d59ac == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_00403290(0x10);
  }
  else {
    puVar2 = DAT_005d59ac;
    DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
  }
  DAT_005d59e8 = 0;
  param_1[0x99] = puVar2;
  *puVar2 = puVar2;
  *(undefined4 *)(param_1[0x99] + 4) = param_1[0x99];
  *param_1 = &PTR_FUN_005b0e18;
  DAT_0072badc = DAT_0072badc + 1;
  param_1[2] = param_2;
  param_1[1] = 0;
  param_1[3] = 0x268;
  param_1[5] = 0;
  local_4._0_1_ = 3;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  pcVar3 = &DAT_005d2e58;
  do {
    cVar1 = *pcVar3;
    *(char *)((int)(param_1 + -0x174b91) + (int)pcVar3) = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  param_1[4] = 0;
  *(char *)(param_1 + 0xe) = param_3;
  if (param_3 == '\0') {
    param_1[0x7b] = 0;
  }
  else {
    pvVar4 = operator_new(0x208);
    local_4._0_1_ = 4;
    if (pvVar4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_00580970(param_1);
    }
    param_1[0x7b] = piVar5;
    *piVar5 = *piVar5 + 1;
    *(undefined4 **)(param_1[0x7b] + 0x74) = param_1;
  }
  local_4._0_1_ = 3;
  param_1[0x76] = 0;
  param_1[0x7a] = 0;
  param_1[0x79] = 0;
  param_1[0x78] = param_1[2] + 0x5c;
  param_1[0x77] = param_1[2] + 0x5c;
  param_1[0x7e] = 0;
  param_1[0x7d] = 0;
  param_1[0x7c] = 0;
  FUN_00477200();
  FUN_00477200();
  FUN_00477200();
  FUN_00477200();
  FUN_00477200();
  FUN_00581a70(s_Channel_005d2e50);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

