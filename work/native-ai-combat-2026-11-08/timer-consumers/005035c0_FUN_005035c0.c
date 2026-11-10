/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall
FUN_005035c0(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
            undefined1 *param_5)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined1 auStack_38 [4];
  undefined4 uStack_34;
  undefined4 *puStack_30;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a40ab;
  local_c = ExceptionList;
  local_4 = 0;
  if (param_3 == param_2) {
    local_4 = 0xffffffff;
    ExceptionList = &local_c;
    *(undefined1 **)(param_1 + 8) = param_5;
    if ((param_2 != (undefined4 *)0x0) && (param_4 != param_2)) {
      puStack_30 = param_2;
      uStack_34 = 0x50361b;
      FUN_00402e90();
      ExceptionList = local_c;
      return;
    }
  }
  else {
    for (puVar3 = (undefined4 *)**(undefined4 **)(param_1 + 0xc);
        puVar3 != *(undefined4 **)(param_1 + 0xc); puVar3 = (undefined4 *)*puVar3) {
      if (*(char *)(puVar3[2] + 4) == *(char *)((int)param_3 + -1)) {
        ExceptionList = &local_c;
        *(undefined1 *)((int)param_3 + -1) = 0;
        param_3 = (undefined4 *)((int)param_3 + -1);
        param_5 = auStack_38;
        FUN_0047a270(&param_2);
        local_4._0_1_ = 1;
        puVar3 = (undefined4 *)FUN_00503810();
        local_4 = (uint)local_4._1_3_ << 8;
        (**(code **)(*(int *)*puVar3 + 8))();
        local_4 = 0xffffffff;
        if (param_2 == (undefined4 *)0x0) {
          ExceptionList = local_c;
          return;
        }
        if (param_4 == param_2) {
          ExceptionList = local_c;
          return;
        }
        puStack_30 = param_2;
        uStack_34 = 0x5036f8;
        FUN_00402e90();
        ExceptionList = local_c;
        return;
      }
    }
    puStack_30 = (undefined4 *)0x50365e;
    ExceptionList = &local_c;
    piVar1 = operator_new(0x10);
    local_4._0_1_ = 2;
    if (piVar1 == (int *)0x0) {
      piVar2 = (int *)0x0;
    }
    else {
      puStack_30 = (undefined4 *)0x503681;
      FUN_004a84d0();
      *piVar1 = (int)&PTR_FUN_005aaae8;
      piVar1[2] = 99999;
      piVar2 = piVar1;
    }
    local_4 = (uint)local_4._1_3_ << 8;
    *(undefined1 *)(piVar2 + 1) = *(undefined1 *)((int)param_3 + -1);
    puStack_30 = (undefined4 *)0x50372f;
    FUN_004db820();
    puStack_30 = (undefined4 *)0x50373b;
    puVar3 = (undefined4 *)FUN_00503820();
    *puVar3 = piVar1;
    puVar3[1] = piVar1[1];
    *(undefined4 **)piVar1[1] = puVar3;
    piVar1[1] = (int)puVar3;
    *(undefined1 *)((int)param_3 + -1) = 0;
    param_3 = (undefined4 *)((int)param_3 + -1);
    param_5 = auStack_38;
    FUN_0047a270(&param_2);
    (**(code **)(*piVar2 + 8))();
    puVar3 = param_2;
    uVar4 = (int)param_4 - (int)param_2;
    local_4 = 0xffffffff;
    if ((param_2 != (undefined4 *)0x0) && (uVar4 != 0)) {
      if (0x80 < uVar4) {
        puStack_30 = (undefined4 *)0x5037b3;
        FUN_005089fd();
        ExceptionList = local_c;
        return;
      }
      FUN_00402330();
      *puVar3 = *(undefined4 *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = puVar3;
      DAT_005d59e8 = 0;
    }
  }
  ExceptionList = local_c;
  return;
}

