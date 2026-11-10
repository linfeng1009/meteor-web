/* Original Meteor.exe static export @ 004b4250; original sample not executed. */
/* XREF 004aa2c8 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004b4250(float *param_1,undefined4 param_2)

{
  float fVar1;
  float10 fVar2;
  float10 fVar3;
  float local_24 [6];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a0768;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_00549d20(0,0);
  local_4 = 0;
  FUN_00549da0(param_2,0xe);
  thunk_FUN_00549ee0(local_24,0xe);
  fVar1 = ((float)(int)local_24[0] - _DAT_005a9bbc) * _DAT_005a83e8;
  *param_1 = fVar1;
  param_1[9] = fVar1;
  thunk_FUN_00549ee0(local_24,0xe);
  fVar1 = ((float)(int)local_24[0] - _DAT_005a9bbc) * _DAT_005a83e8;
  param_1[1] = fVar1;
  param_1[10] = fVar1;
  thunk_FUN_00549ee0(local_24,0xc);
  fVar1 = ((float)(int)local_24[0] - _DAT_005a9bb8) * _DAT_005a83e8;
  param_1[2] = fVar1;
  param_1[0xb] = fVar1;
  thunk_FUN_00549ee0(local_24,6);
  fVar3 = (float10)_DAT_005a83ec;
  param_1[5] = 0.0;
  fVar2 = (float10)fcos((float10)(int)local_24[0] * fVar3);
  param_1[3] = (float)fVar2;
  fVar3 = (float10)fsin((float10)(int)local_24[0] * fVar3);
  param_1[4] = (float)fVar3;
  thunk_FUN_00549ee0(local_24,0xb);
  param_1[0xc] = ((float)(int)local_24[0] - _DAT_005a9bb4) * _DAT_005a9bb0;
  thunk_FUN_00549ee0(local_24,0xb);
  param_1[0xd] = ((float)(int)local_24[0] - _DAT_005a9bb4) * _DAT_005a9bb0;
  thunk_FUN_00549ee0(local_24,0xb);
  param_1[0xe] = ((float)(int)local_24[0] - _DAT_005a9bb4) * _DAT_005a9bb0;
  thunk_FUN_00549ee0(local_24,0x10);
  param_1[0xf] = local_24[0];
  thunk_FUN_00549ee0(local_24,0x10);
  param_1[0x10] = local_24[0];
  local_4 = 0xffffffff;
  FUN_00549d80();
  ExceptionList = local_c;
  return;
}

