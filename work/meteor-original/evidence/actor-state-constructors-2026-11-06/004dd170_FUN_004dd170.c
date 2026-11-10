/* Original Meteor.exe static export @ 004dd170; original sample not executed. */
/* XREF 004dd33b UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004dd170(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a2828;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_004dc9a0();
  local_4 = 0;
  *param_1 = &PTR_FUN_005aab00;
  FUN_004dd370();
  ExceptionList = local_c;
  return param_1;
}

