/* Original Meteor.exe static export @ 004e3530; original sample not executed. */
/* XREF 004e373b UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004e3530(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a2d13;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004dc9a0();
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  local_4 = 1;
  *param_1 = &PTR_FUN_005aafe8;
  FUN_004e3770();
  ExceptionList = local_c;
  return param_1;
}

