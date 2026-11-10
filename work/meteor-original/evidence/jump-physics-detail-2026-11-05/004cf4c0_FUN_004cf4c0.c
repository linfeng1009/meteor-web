/* Original Meteor.exe static export @ 004cf4c0; original sample not executed. */
/* XREF 005aa724 DATA */

undefined4 __fastcall FUN_004cf4c0(int param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a19db;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  if (*(int *)(param_1 + 0xe8) == 0) {
    ExceptionList = &local_c;
    pvVar1 = operator_new(0x48);
    local_4 = 0;
    if (pvVar1 == (void *)0x0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_005498c0();
    }
    *(undefined4 *)(param_1 + 0xe8) = uVar2;
  }
  local_4 = 0xffffffff;
  FUN_00549a90(0,0);
  ExceptionList = local_c;
  return 1;
}

