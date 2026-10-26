/* Meteor.exe original x86 @ 00566940; function boundary recovered from direct vtable/code reference */
/* Caller: 004962e0 */

void __thiscall FUN_00566940(int *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_b4;
  void *local_b0;
  undefined1 local_ac [32];
  undefined1 local_8c [128];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a586e;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar2 = FUN_00509f8f(param_2,&DAT_005ca380);
  if (iVar2 != 0) {
    if ((*(byte *)(iVar2 + 0xc) & 0x10) == 0) {
      do {
        FUN_0050b600(iVar2,&DAT_005d1138,local_ac);
        FUN_00508ae6(local_8c,&DAT_005c4538,param_1[5],local_ac);
        local_b0 = operator_new(0x144);
        local_4 = 0;
        if (local_b0 == (void *)0x0) {
          local_b4 = 0;
        }
        else {
          local_b4 = FUN_00565ee0(param_1);
        }
        local_4 = 0xffffffff;
        FUN_00566230(local_8c);
        puVar1 = (undefined4 *)param_1[2];
        if (puVar1 == (undefined4 *)param_1[3]) {
          FUN_0055e370(puVar1,&local_b4);
        }
        else {
          if (puVar1 != (undefined4 *)0x0) {
            *puVar1 = local_b4;
          }
          param_1[2] = param_1[2] + 4;
        }
        *param_1 = param_1[2] - param_1[1] >> 2;
      } while ((*(byte *)(iVar2 + 0xc) & 0x10) == 0);
    }
    FUN_00509e57(iVar2);
    *param_1 = param_1[2] - param_1[1] >> 2;
  }
  ExceptionList = local_c;
  return;
}

