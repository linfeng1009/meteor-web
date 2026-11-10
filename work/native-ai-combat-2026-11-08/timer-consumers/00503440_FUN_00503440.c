/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall
FUN_00503440(int param_1,undefined4 *param_2,undefined4 *param_3,int param_4,int *param_5)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  int aiStack_30 [2];
  undefined4 *puStack_28;
  int *piStack_24;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  piVar1 = param_5;
  puStack_8 = &LAB_005a4080;
  local_c = ExceptionList;
  local_4 = 0;
  if (param_3 == param_2) {
    local_4 = 0xffffffff;
    ExceptionList = &local_c;
    *param_5 = *(int *)(param_1 + 8);
    piStack_24 = (int *)(param_4 - (int)param_2);
    if ((param_2 != (undefined4 *)0x0) && (piStack_24 != (int *)0x0)) {
      puStack_28 = param_2;
      aiStack_30[1] = 0x50349e;
      FUN_00402e90();
    }
  }
  else {
    for (puVar3 = (undefined4 *)**(undefined4 **)(param_1 + 0xc);
        puVar3 != *(undefined4 **)(param_1 + 0xc); puVar3 = (undefined4 *)*puVar3) {
      if (*(char *)(puVar3[2] + 4) == *(char *)((int)param_3 + -1)) {
        ExceptionList = &local_c;
        *(undefined1 *)((int)param_3 + -1) = 0;
        piStack_24 = param_5;
        param_3 = (undefined4 *)((int)param_3 + -1);
        param_5 = aiStack_30;
        FUN_0047a270(&param_2);
        local_4._0_1_ = 1;
        puVar3 = (undefined4 *)FUN_00503810();
        local_4 = (uint)local_4._1_3_ << 8;
        (**(code **)(*(int *)*puVar3 + 4))();
        if (*piVar1 == 99999) {
          *piVar1 = *(int *)(param_1 + 8);
        }
        uVar2 = param_4 - (int)param_2;
        local_4 = 0xffffffff;
        if (param_2 == (undefined4 *)0x0) {
          ExceptionList = local_c;
          return;
        }
        if (uVar2 == 0) {
          ExceptionList = local_c;
          return;
        }
        if (0x80 < uVar2) {
          piStack_24 = param_2;
          puStack_28 = (undefined4 *)0x503579;
          FUN_005089fd();
          ExceptionList = local_c;
          return;
        }
        goto LAB_00503580;
      }
    }
    local_4 = 0xffffffff;
    ExceptionList = &local_c;
    *param_5 = *(int *)(param_1 + 8);
    uVar2 = param_4 - (int)param_2;
    if ((param_2 != (undefined4 *)0x0) && (uVar2 != 0)) {
      if (uVar2 < 0x81) {
LAB_00503580:
        puVar3 = param_2;
        local_4 = 0xffffffff;
        piStack_24 = (int *)0x503597;
        FUN_00402330();
        *puVar3 = *(undefined4 *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = puVar3;
        DAT_005d59e8 = 0;
      }
      else {
        piStack_24 = param_2;
        puStack_28 = (undefined4 *)0x503500;
        FUN_005089fd();
      }
    }
  }
  ExceptionList = local_c;
  return;
}

