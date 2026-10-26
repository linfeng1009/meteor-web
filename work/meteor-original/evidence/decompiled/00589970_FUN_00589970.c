/* Meteor.exe original x86 @ 00589970; function boundary recovered from direct vtable/code reference */
/* Caller: 0056e600 */
/* Caller: 0056efd8 */

undefined4 * __thiscall FUN_00589970(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a6be8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_005811c0(param_2,param_3);
  *param_1 = &PTR_FUN_005b13f0;
  DAT_0072bcf0 = DAT_0072bcf0 + 1;
  local_4 = 0;
  param_1[1] = 3;
  param_1[3] = 0x274;
  pcVar2 = (char *)FUN_0058a6d0(3);
  pcVar3 = (char *)(param_1 + 5);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  param_1[0x9c] = 0x41200000;
  param_1[0x9b] = 0x41200000;
  param_1[0x9a] = 0x41200000;
  FUN_00581aa0(&PTR_DAT_005d2f7c);
  ExceptionList = local_c;
  return param_1;
}

