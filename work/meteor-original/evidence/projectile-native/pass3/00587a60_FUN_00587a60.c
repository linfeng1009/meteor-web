/* Original Meteor.exe static export @ 00587a60; original sample not executed. */
/* XREF 0056e6c8 UNCONDITIONAL_CALL */
/* XREF 0056f094 UNCONDITIONAL_CALL */

undefined4 * __thiscall FUN_00587a60(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a6a78;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_005811c0(param_2,param_3);
  local_4 = 0;
  *param_1 = &PTR_FUN_005b1148;
  param_1[1] = 8;
  param_1[3] = 0x2f4;
  pcVar2 = (char *)FUN_0058a6d0(8);
  pcVar3 = (char *)(param_1 + 5);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  param_1[0xba] = 0;
  FUN_00581aa0(s_Model_005c9204);
  *(undefined1 *)(param_1 + 0x9a) = 0;
  param_1[0xbc] = 0;
  ExceptionList = local_c;
  return param_1;
}

