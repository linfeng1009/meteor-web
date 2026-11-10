/* Original Meteor.exe static export @ 004ecc00; original sample not executed. */
/* XREF 005a3ef3 UNCONDITIONAL_CALL */
/* XREF 005a3f53 UNCONDITIONAL_CALL */
/* XREF 004ecbe3 UNCONDITIONAL_CALL */
/* XREF 00500bbc UNCONDITIONAL_CALL */

void __fastcall FUN_004ecc00(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005a31b8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005ab228;
  param_1[4] = &PTR_LAB_005ab1f8;
  local_4 = 0;
  FUN_004ecdd0();
  local_4 = 0xffffffff;
  FUN_004ed450();
  ExceptionList = local_c;
  return;
}

