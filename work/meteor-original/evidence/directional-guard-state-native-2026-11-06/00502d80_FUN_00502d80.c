/* Original Meteor.exe static export @ 00502d80; original sample not executed. */
/* XREF 004cabf2 UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_00502d80(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a4020;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004a9010();
  local_4 = 0;
  FUN_005498c0();
  param_1[4] = 0;
  local_4 = 1;
  *param_1 = &PTR_FUN_005aba58;
  FUN_00502e10();
  ExceptionList = local_c;
  return param_1;
}

