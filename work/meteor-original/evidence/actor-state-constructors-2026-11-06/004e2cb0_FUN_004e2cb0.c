/* Original Meteor.exe static export @ 004e2cb0; original sample not executed. */
/* XREF 004e2e7b UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004e2cb0(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a2ca8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004dc9a0();
  local_4 = 0;
  *param_1 = &PTR_FUN_005aaf70;
  FUN_004e2eb0();
  ExceptionList = local_c;
  return param_1;
}

