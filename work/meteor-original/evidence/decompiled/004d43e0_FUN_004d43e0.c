/* Meteor.exe original x86 @ 004d43e0 */
/* Caller: 004d404e */

void * FUN_004d43e0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a1d58;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffd8;
  piVar3 = (void *)0x0;
  ExceptionList = &local_10;
  puVar2 = &stack0xffffffd8;
  if (param_1 != 0) {
    uVar5 = param_1 * 0xc;
    if (uVar5 < 0x81) {
      ExceptionList = &local_10;
      FUN_00402330();
      piVar3 = *(int **)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4);
      local_8 = 0;
      if (piVar3 == (int *)0x0) {
        uVar5 = uVar5 + 7 & 0xfffffff8;
        local_18 = 0x14;
        piVar3 = (int *)FUN_004036c0(uVar5,&local_18);
        if (local_18 != 1) {
          puVar4 = (undefined4 *)((int)piVar3 + uVar5);
          iVar6 = 1;
          *(undefined4 **)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4) = puVar4;
          puVar1 = puVar4;
          if (local_18 != 2) {
            do {
              puVar4 = (undefined4 *)((int)puVar1 + uVar5);
              *puVar1 = puVar4;
              iVar6 = iVar6 + 1;
              puVar1 = puVar4;
            } while (local_18 + -1 != iVar6);
          }
          *puVar4 = 0;
        }
      }
      else {
        *(int *)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4) = *piVar3;
      }
      DAT_005d59e8 = 0;
      puVar2 = local_14;
    }
    else {
      ExceptionList = &local_10;
      local_14 = &stack0xffffffd8;
      piVar3 = _malloc(uVar5);
      puVar2 = local_14;
      if (piVar3 == (void *)0x0) {
        piVar3 = (int *)FUN_00403440(uVar5);
        puVar2 = local_14;
      }
    }
  }
  local_14 = puVar2;
  local_8 = 1;
  FUN_004f4800(param_2,param_3,piVar3,param_1);
  ExceptionList = local_10;
  return piVar3;
}

