/* Original Meteor.exe static export @ 005813c0; original sample not executed. */
/* XREF 005a6853 UNCONDITIONAL_CALL */
/* XREF 005a68a3 UNCONDITIONAL_CALL */
/* XREF 005a69d3 UNCONDITIONAL_CALL */
/* XREF 005a69f3 UNCONDITIONAL_CALL */
/* XREF 005a6a13 UNCONDITIONAL_CALL */
/* XREF 005a6a33 UNCONDITIONAL_CALL */
/* XREF 005a6a53 UNCONDITIONAL_CALL */
/* XREF 005a6a73 UNCONDITIONAL_CALL */
/* XREF 005a6a93 UNCONDITIONAL_CALL */
/* XREF 005a6b23 UNCONDITIONAL_CALL */
/* XREF 005a6b43 UNCONDITIONAL_CALL */
/* XREF 005a6ba3 UNCONDITIONAL_CALL */
/* XREF 005a6bc3 UNCONDITIONAL_CALL */
/* XREF 005a6be3 UNCONDITIONAL_CALL */
/* XREF 005a6c03 UNCONDITIONAL_CALL */
/* XREF 005a6c23 UNCONDITIONAL_CALL */
/* XREF 005813a3 UNCONDITIONAL_CALL */
/* XREF 00583bd6 UNCONDITIONAL_CALL */
/* XREF 00585d3a UNCONDITIONAL_CALL */
/* XREF 00587b5a UNCONDITIONAL_CALL */
/* XREF 005893d0 UNCONDITIONAL_JUMP */
/* XREF 0058a2fa UNCONDITIONAL_CALL */

void __fastcall FUN_005813c0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005a678c;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005b0e18;
  local_4 = 1;
  FUN_005820a0();
  iVar2 = FUN_00580c30();
  if (iVar2 != 0) {
    param_1[0x7b] = 0;
  }
  piVar4 = *(int **)param_1[0x99];
  if (piVar4 != (undefined4 *)param_1[0x99]) {
    do {
      piVar3 = piVar4;
      piVar4 = (int *)*piVar3;
      FUN_00402330();
      *piVar3 = (int)DAT_005d59ac;
      DAT_005d59e8 = 0;
      DAT_005d59ac = piVar3;
    } while (piVar4 != (int *)param_1[0x99]);
  }
  *(undefined4 *)param_1[0x99] = param_1[0x99];
  *(undefined4 *)(param_1[0x99] + 4) = param_1[0x99];
  piVar4 = (int *)param_1[0x99];
  FUN_00402330();
  *piVar4 = (int)DAT_005d59ac;
  piVar3 = *(int **)param_1[0x98];
  DAT_005d59ac = piVar4;
  if (piVar3 != (int *)param_1[0x98]) {
    do {
      piVar4 = piVar3;
      DAT_005d59e8 = 0;
      piVar3 = (int *)*piVar4;
      FUN_00402330();
      *piVar4 = (int)DAT_005d59ac;
      DAT_005d59ac = piVar4;
    } while (piVar3 != (int *)param_1[0x98]);
  }
  DAT_005d59e8 = 0;
  *(undefined4 *)param_1[0x98] = param_1[0x98];
  *(undefined4 *)(param_1[0x98] + 4) = param_1[0x98];
  puVar1 = (undefined4 *)param_1[0x98];
  FUN_00402330();
  *puVar1 = DAT_005d59ac;
  DAT_005d59ac = puVar1;
  DAT_005d59e8 = 0;
  ExceptionList = local_c;
  return;
}

