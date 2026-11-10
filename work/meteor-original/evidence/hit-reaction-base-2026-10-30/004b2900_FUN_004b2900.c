/* Original Meteor.exe static export @ 004b2900; original sample not executed. */
/* XREF 004ed212 UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004b2900(undefined4 *param_1)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a0504;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_0054a170();
  local_4 = 0;
  param_1[0x57] = 0;
  param_1[0x58] = 0;
  param_1[0x59] = 0;
  param_1[0x5a] = 0;
  param_1[0x5b] = 0;
  param_1[0x5c] = 0;
  param_1[0x5d] = 0;
  param_1[0x5e] = 0;
  param_1[0x5f] = 0;
  param_1[0x60] = 0;
  FUN_0049d070(0);
  param_1[0x61] = 0;
  param_1[0x62] = 0;
  param_1[99] = 0;
  local_4 = CONCAT31(local_4._1_3_,2);
  *param_1 = &PTR_FUN_005a9d58;
  FUN_004b29b0();
  ExceptionList = local_c;
  return param_1;
}

