/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall FUN_004fe6e0(undefined4 *param_1,uint param_2)

{
  uint _Size;
  int *piVar1;
  undefined1 *puVar2;
  int **ppiVar3;
  int *piVar4;
  int iVar5;
  int *local_1c;
  int *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a3e08;
  local_10 = ExceptionList;
  iVar5 = (param_2 >> 7) + 1;
  local_14 = &stack0xffffffd4;
  local_18 = (int *)((param_2 >> 7) + 3);
  local_1c = (int *)0x8;
  ppiVar3 = &local_18;
  if (local_18 < (int *)0x9) {
    ppiVar3 = &local_1c;
  }
  piVar1 = *ppiVar3;
  ExceptionList = &local_10;
  param_1[1] = piVar1;
  piVar4 = (void *)0x0;
  puVar2 = &stack0xffffffd4;
  if (piVar1 != (int *)0x0) {
    _Size = (int)piVar1 * 4;
    if (_Size < 0x81) {
      local_1c = (int *)(&DAT_005d59a4 + (_Size + 7 >> 3) * 4);
      FUN_00402330();
      local_8 = 0;
      piVar4 = (int *)*local_1c;
      if (piVar4 == (int *)0x0) {
        piVar4 = (int *)FUN_00403290(_Size + 7 & 0xfffffff8);
      }
      else {
        *local_1c = *piVar4;
      }
      DAT_005d59e8 = 0;
      puVar2 = local_14;
    }
    else {
      local_14 = &stack0xffffffd4;
      piVar4 = _malloc(_Size);
      puVar2 = local_14;
      if (piVar4 == (void *)0x0) {
        piVar4 = (int *)FUN_00403440(_Size);
        puVar2 = local_14;
      }
    }
  }
  local_14 = puVar2;
  *param_1 = piVar4;
  local_8 = 1;
  piVar4 = (int *)((int)piVar4 + ((uint)(param_1[1] - iVar5) >> 1) * 4);
  piVar1 = piVar4 + iVar5;
  FUN_004fec40(piVar4,piVar1);
  param_1[5] = piVar4;
  iVar5 = *piVar4;
  param_1[3] = iVar5;
  param_1[4] = iVar5 + 0x200;
  param_1[9] = piVar1 + -1;
  iVar5 = piVar1[-1];
  param_1[7] = iVar5;
  param_1[8] = iVar5 + 0x200;
  param_1[2] = param_1[3];
  param_1[6] = param_1[7] + (param_2 & 0x7f) * 4;
  ExceptionList = local_10;
  return;
}

