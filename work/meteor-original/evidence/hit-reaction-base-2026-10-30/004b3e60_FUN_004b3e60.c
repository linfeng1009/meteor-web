/* Original Meteor.exe static export @ 004b3e60; original sample not executed. */
/* XREF 004a9d99 UNCONDITIONAL_CALL */
/* XREF 004a9b2e UNCONDITIONAL_CALL */

void FUN_004b3e60(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000010;
  undefined2 in_stack_00000014;
  undefined4 in_stack_00000018;
  undefined4 uVar3;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a0728;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_00549d20(0,0);
  local_4 = 0;
  FUN_00549da0(in_stack_00000018,0xc);
  uVar1 = __ftol();
  uVar1 = uVar1 & ((int)uVar1 < 0) - 1;
  if (0x80 < (int)uVar1) {
    uVar1 = 0x80;
  }
  thunk_FUN_00549df0(uVar1,7);
  uVar1 = __ftol();
  uVar1 = uVar1 & ((int)uVar1 < 0) - 1;
  if (0x80 < (int)uVar1) {
    uVar1 = 0x80;
  }
  thunk_FUN_00549df0(uVar1,7);
  uVar1 = __ftol();
  uVar1 = uVar1 & ((int)uVar1 < 0) - 1;
  if (0x80 < (int)uVar1) {
    uVar1 = 0x80;
  }
  thunk_FUN_00549df0(uVar1,7);
  uVar3 = 7;
  uVar2 = __ftol(7);
  thunk_FUN_00549df0(uVar2,uVar3);
  uVar1 = __ftol();
  uVar1 = uVar1 & ((int)uVar1 < 0) - 1;
  if (0x1000 < (int)uVar1) {
    uVar1 = 0x1000;
  }
  thunk_FUN_00549df0(uVar1,0xc);
  uVar1 = __ftol();
  uVar1 = uVar1 & ((int)uVar1 < 0) - 1;
  if (0x1000 < (int)uVar1) {
    uVar1 = 0x1000;
  }
  thunk_FUN_00549df0(uVar1,0xc);
  uVar1 = __ftol();
  uVar1 = uVar1 & ((int)uVar1 < 0) - 1;
  if (0x1000 < (int)uVar1) {
    uVar1 = 0x1000;
  }
  thunk_FUN_00549df0(uVar1,0xc);
  thunk_FUN_00549df0(in_stack_00000010,0x10);
  thunk_FUN_00549df0(in_stack_00000014,0x10);
  local_4 = 0xffffffff;
  FUN_00549d80();
  ExceptionList = local_c;
  return;
}

