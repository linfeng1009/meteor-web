/* Original Meteor.exe static export @ 00565a40; original sample not executed. */
/* XREF 00577eea DATA */
/* XREF 00560534 DATA */
/* XREF 00560644 DATA */
/* XREF 00560734 DATA */

undefined4 * __fastcall FUN_00565a40(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int local_14;
  undefined4 *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a5750;
  local_c = ExceptionList;
  puVar1 = param_1 + 3;
  ExceptionList = &local_c;
  *puVar1 = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  local_10 = puVar1;
  FUN_00402330();
  local_4 = 0;
  if (DAT_005d59a8 == (undefined4 *)0x0) {
    local_14 = 0x14;
    puVar3 = (undefined4 *)FUN_004036c0(8,&local_14);
    if (local_14 != 1) {
      puVar4 = puVar3 + 2;
      iVar5 = 1;
      puVar2 = puVar4;
      DAT_005d59a8 = puVar4;
      if (local_14 != 2) {
        do {
          puVar4 = puVar2 + 2;
          *puVar2 = puVar4;
          iVar5 = iVar5 + 1;
          puVar2 = puVar4;
        } while (local_14 + -1 != iVar5);
      }
      *puVar4 = 0;
    }
  }
  else {
    puVar3 = DAT_005d59a8;
    DAT_005d59a8 = (undefined4 *)*DAT_005d59a8;
  }
  DAT_005d59e8 = 0;
  *puVar1 = puVar3;
  param_1[4] = puVar3;
  param_1[5] = puVar3 + 2;
  local_4 = 3;
  FUN_00402a70();
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = &PTR_LAB_005ab82c;
  ExceptionList = local_c;
  return param_1;
}

