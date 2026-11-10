/* Original Meteor.exe static export @ 004e0cd0; original sample not executed. */
/* XREF 004e0e9b UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004e0cd0(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a2b28;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004dc9a0();
  local_4 = 0;
  *param_1 = &PTR_FUN_005aae80;
  FUN_004e0ed0();
  ExceptionList = local_c;
  return param_1;
}

