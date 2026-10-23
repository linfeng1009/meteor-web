/* Meteor.exe original x86 @ 004d4180 */
/* Caller: 004d4749 */
/* Caller: 004d66a2 */
/* Caller: 004d3eb6 */
/* Caller: 004d3a2e */

void * FUN_004d4180(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint _Size;
  int iVar5;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a1d38;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffd8;
  piVar3 = (void *)0x0;
  ExceptionList = &local_10;
  puVar2 = &stack0xffffffd8;
  if (param_1 != 0) {
    _Size = param_1 * 0x28;
    if (_Size < 0x81) {
      ExceptionList = &local_10;
      FUN_00402330();
      piVar3 = *(int **)(&DAT_005d59a4 + (_Size + 7 >> 3) * 4);
      local_8 = 0;
      if (piVar3 == (int *)0x0) {
        local_18 = 0x14;
        piVar3 = (int *)FUN_004036c0(_Size,&local_18);
        if (local_18 != 1) {
          puVar4 = (undefined4 *)((int)piVar3 + _Size);
          iVar5 = 1;
          *(undefined4 **)(&DAT_005d59a4 + (_Size + 7 >> 3) * 4) = puVar4;
          puVar1 = puVar4;
          if (local_18 != 2) {
            do {
              puVar4 = puVar1 + param_1 * 10;
              *puVar1 = puVar4;
              iVar5 = iVar5 + 1;
              puVar1 = puVar4;
            } while (local_18 + -1 != iVar5);
          }
          *puVar4 = 0;
        }
      }
      else {
        *(int *)(&DAT_005d59a4 + (_Size + 7 >> 3) * 4) = *piVar3;
      }
      DAT_005d59e8 = 0;
      puVar2 = local_14;
    }
    else {
      ExceptionList = &local_10;
      local_14 = &stack0xffffffd8;
      piVar3 = _malloc(_Size);
      puVar2 = local_14;
      if (piVar3 == (void *)0x0) {
        piVar3 = (int *)FUN_00403440(_Size);
        puVar2 = local_14;
      }
    }
  }
  local_14 = puVar2;
  local_8 = 1;
  FUN_0049fe20(param_2,param_3,piVar3,param_1);
  ExceptionList = local_10;
  return piVar3;
}

