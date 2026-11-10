/* Original Meteor.exe static export @ 004a9010; original sample not executed. */
/* XREF 004b31e2 UNCONDITIONAL_CALL */
/* XREF 004ed202 UNCONDITIONAL_CALL */
/* XREF 00485862 UNCONDITIONAL_CALL */
/* XREF 004a8fb3 UNCONDITIONAL_CALL */
/* XREF 004abac2 UNCONDITIONAL_CALL */
/* XREF 004beed1 UNCONDITIONAL_CALL */
/* XREF 004e7e21 UNCONDITIONAL_CALL */
/* XREF 004a02a2 UNCONDITIONAL_CALL */
/* XREF 00502d9d UNCONDITIONAL_CALL */
/* XREF 004f590d UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004a9010(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int local_14;
  undefined4 *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059fc96;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_10 = param_1;
  FUN_00402330();
  local_4 = 0;
  if (DAT_005d59ac == (undefined4 *)0x0) {
    local_14 = 0x14;
    puVar2 = (undefined4 *)FUN_004036c0(0x10,&local_14);
    if (local_14 != 1) {
      puVar3 = puVar2 + 4;
      iVar4 = 1;
      puVar1 = puVar3;
      DAT_005d59ac = puVar3;
      if (local_14 != 2) {
        do {
          puVar3 = puVar1 + 4;
          *puVar1 = puVar3;
          iVar4 = iVar4 + 1;
          puVar1 = puVar3;
        } while (local_14 + -1 != iVar4);
      }
      *puVar3 = 0;
    }
  }
  else {
    puVar2 = DAT_005d59ac;
    DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
  }
  DAT_005d59e8 = 0;
  param_1[1] = puVar2;
  *puVar2 = puVar2;
  *(undefined4 *)(param_1[1] + 4) = param_1[1];
  iVar4 = 1;
  local_4 = 1;
  FUN_00402330();
  local_4._0_1_ = 2;
  if (DAT_005d59ac == (undefined4 *)0x0) {
    local_14 = 0x14;
    puVar2 = (undefined4 *)FUN_004036c0(0x10,&local_14);
    if (local_14 != 1) {
      puVar3 = puVar2 + 4;
      puVar1 = puVar3;
      DAT_005d59ac = puVar3;
      if (local_14 != 2) {
        do {
          puVar3 = puVar1 + 4;
          *puVar1 = puVar3;
          iVar4 = iVar4 + 1;
          puVar1 = puVar3;
        } while (local_14 + -1 != iVar4);
      }
      *puVar3 = 0;
    }
  }
  else {
    puVar2 = DAT_005d59ac;
    DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
  }
  DAT_005d59e8 = 0;
  param_1[2] = puVar2;
  *puVar2 = puVar2;
  *(undefined4 *)(param_1[2] + 4) = param_1[2];
  local_4 = CONCAT31(local_4._1_3_,3);
  *param_1 = &PTR_FUN_005a9b74;
  FUN_004a92c0();
  ExceptionList = local_c;
  return param_1;
}

