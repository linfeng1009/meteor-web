/* Meteor.exe original x86 @ 004efb20; function boundary recovered from direct vtable/code reference */
/* Caller: 005ab488 */
/* Caller: 005ab8c8 */
/* Caller: 005ab248 */

uint __thiscall FUN_004efb20(int *param_1,int param_2,uint *param_3,uint param_4)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint *puStack_28;
  undefined1 auStack_10 [16];
  
  switch(param_2) {
  case 4:
  case 9:
    break;
  case 5:
    puStack_28 = (uint *)param_3[1];
    (**(code **)(*param_1 + 0xec))(*param_3);
    return 0;
  case 6:
    puStack_28 = (uint *)0x0;
    uVar2 = (**(code **)(*param_1 + 0xcc))();
    return uVar2;
  default:
    return 0xffffffff;
  case 8:
    puStack_28 = (uint *)0x0;
    FUN_0054a6c0(0x19,param_3,param_4);
    return 0;
  case 10:
    puStack_28 = (uint *)*param_3;
    (**(code **)(*param_1 + 0xf0))();
    return 0;
  case 0xc:
    puStack_28 = param_3;
    (**(code **)(*param_1 + 0xc4))();
    return 0;
  case 0xd:
    puStack_28 = param_3;
    (**(code **)(*param_1 + 200))();
    return 0;
  case 0xf:
    if (param_1[0xd7] == 1) {
      puStack_28 = (uint *)0x4efb56;
      (**(code **)(*param_1 + 300))();
      puStack_28 = (uint *)0x4efb5b;
      piVar4 = (int *)FUN_00487830();
      iVar5 = *piVar4;
      puStack_28 = (uint *)0x4efb66;
      puStack_28 = (uint *)(**(code **)(*param_1 + 0x4c))();
      (**(code **)(iVar5 + 0x174))();
      piVar4 = (int *)(**(code **)(*param_1 + 0x44))();
      iVar5 = (**(code **)(*piVar4 + 0x94))();
      (**(code **)(*(int *)(iVar5 + 0x65c) + 4))(&stack0xffffffe4,auStack_10,0);
      FUN_0054a6c0(0x11,&puStack_28,0x18,1);
      iVar5 = (**(code **)(*param_1 + 0x134))();
      if (iVar5 != 0) {
        *(undefined4 *)(iVar5 + 0xc4) = 0;
      }
      return 1;
    }
    break;
  case 0x10:
    uVar2 = param_1[0x95];
    puStack_28 = (uint *)0x4eff07;
    iVar5 = FUN_00487830();
    iVar5 = *(int *)(iVar5 + 0x22ec);
    param_3 = (uint *)iVar5;
    iVar6 = *(int *)(iVar5 + 4);
    while (iVar6 != 0) {
      if (*(uint *)(iVar6 + 0x10) < uVar2) {
        iVar6 = *(int *)(iVar6 + 0xc);
      }
      else {
        param_3 = (uint *)iVar6;
        iVar6 = *(int *)(iVar6 + 8);
      }
    }
    if ((param_3 == (uint *)iVar5) || (uVar2 < *(uint *)((int)param_3 + 0x10))) {
      param_2 = iVar5;
      piVar4 = &param_2;
    }
    else {
      piVar4 = (int *)&param_3;
    }
    iVar5 = *piVar4;
    puStack_28 = (uint *)0x4eff50;
    iVar6 = FUN_00487830();
    if (iVar5 != *(int *)(iVar6 + 0x22ec)) {
      puStack_28 = (uint *)0x0;
      uVar2 = (**(code **)(*(int *)(iVar5 + 0x88) + 0x34))(6);
      if ((99 < uVar2) && (param_1[0xc2] == 1)) {
        return 1;
      }
    }
    break;
  case 0x11:
    puStack_28 = (uint *)0x1;
    param_1[0xc2] = 0;
    FUN_0054a6c0(0x12,0,0);
    return 0;
  case 0x13:
    puStack_28 = (uint *)0x4efd72;
    (**(code **)(*param_1 + 0xa4))();
    return 0;
  case 0x14:
    puStack_28 = (uint *)0x4efd87;
    (**(code **)(*param_1 + 0xb8))();
    return 0;
  case 0x15:
    puStack_28 = (uint *)0x4efd11;
    iVar5 = FUN_00487830();
    puVar1 = *(uint **)(iVar5 + 0x2260);
    puStack_28 = (uint *)0x4efd1c;
    piVar4 = (int *)FUN_00487830();
    puStack_28 = puVar1;
    iVar5 = (**(code **)(*piVar4 + 0x2b4))();
    return (uint)(iVar5 == 0);
  case 0x16:
    puStack_28 = (uint *)0x0;
    (**(code **)(*param_1 + 0x150))();
    return 0;
  case 0x17:
    puStack_28 = (uint *)*param_3;
    (**(code **)(*param_1 + 0x15c))();
    return 0;
  case 0x19:
    puStack_28 = param_3;
    uVar2 = (**(code **)(*param_1 + 0x168))();
    return uVar2;
  case 0x1a:
    puStack_28 = (uint *)0x4efff1;
    iVar5 = (**(code **)(*param_1 + 0x134))();
    if (iVar5 != 0) {
      puStack_28 = (uint *)0x0;
      uVar2 = (**(code **)(*(int *)(iVar5 + 0x70) + 0x34))(5);
      return uVar2;
    }
    break;
  case 0x1b:
    puStack_28 = (uint *)0x0;
    FUN_0054a6c0(0x1a,param_3,param_4);
    return 0;
  case 0x1c:
    puStack_28 = (uint *)0x4efd9c;
    (**(code **)(*param_1 + 0xc0))();
    return 0;
  case 0x1e:
    puStack_28 = (uint *)0x4f0011;
    iVar5 = (**(code **)(*param_1 + 0x68))();
    if (iVar5 != 0) {
      puStack_28 = (uint *)0x4f001c;
      (**(code **)(*param_1 + 0x6c))();
      return 0;
    }
    break;
  case 0x1f:
    puStack_28 = (uint *)0x4f002e;
    uVar2 = (**(code **)(*param_1 + 0x68))();
    return uVar2;
  case 0x20:
    puStack_28 = (uint *)0x4f003e;
    (**(code **)(*param_1 + 0x70))();
    return 0;
  case 0x21:
    puStack_28 = (uint *)0x1;
    FUN_0054a6c0(0x24,0,0);
    return 0;
  case 0x22:
    uVar2 = param_1[0x95];
    puStack_28 = (uint *)0x4efc73;
    iVar5 = FUN_00487830();
    iVar5 = *(int *)(iVar5 + 0x22ec);
    param_3 = (uint *)iVar5;
    iVar6 = *(int *)(iVar5 + 4);
    while (iVar6 != 0) {
      if (*(uint *)(iVar6 + 0x10) < uVar2) {
        iVar6 = *(int *)(iVar6 + 0xc);
      }
      else {
        param_3 = (uint *)iVar6;
        iVar6 = *(int *)(iVar6 + 8);
      }
    }
    if ((param_3 == (uint *)iVar5) || (uVar2 < *(uint *)((int)param_3 + 0x10))) {
      param_2 = iVar5;
      piVar4 = &param_2;
    }
    else {
      piVar4 = (int *)&param_3;
    }
    iVar5 = *piVar4;
    puStack_28 = (uint *)0x4efcbc;
    iVar6 = FUN_00487830();
    if (iVar5 != *(int *)(iVar6 + 0x22ec)) {
      puStack_28 = (uint *)0x0;
      uVar2 = (**(code **)(*(int *)(iVar5 + 0x88) + 0x34))(6);
      return (uint)(0x3b < uVar2);
    }
    break;
  case 0x2a:
    uVar7 = 0x28;
    goto LAB_004f0054;
  case 0x2b:
    param_4 = param_1[0x95];
    puStack_28 = (uint *)0x4efc0f;
    FUN_00487830();
    puStack_28 = &param_4;
    FUN_0049d3c0(&param_2);
    uVar2 = *param_3;
    puStack_28 = (uint *)0x4efc30;
    iVar5 = FUN_00487830();
    if (param_2 != *(int *)(iVar5 + 0x22ec)) {
      puStack_28 = (uint *)0x0;
      uVar3 = (**(code **)(*(int *)(param_2 + 0x88) + 0x34))(6);
      return (uint)(uVar2 <= uVar3);
    }
    break;
  case 0x2c:
    puStack_28 = (uint *)0x4efbd7;
    uVar2 = (**(code **)(*param_1 + 0x38))();
    return uVar2;
  case 0x2d:
    puStack_28 = (uint *)0x4efbe7;
    uVar2 = (**(code **)(*param_1 + 0x3c))();
    return uVar2;
  case 0x2e:
    uVar2 = param_1[0x95];
    uVar3 = *param_3;
    puStack_28 = (uint *)0x4efe7f;
    iVar5 = FUN_00487830();
    iVar5 = *(int *)(iVar5 + 0x22ec);
    param_3 = (uint *)iVar5;
    iVar6 = *(int *)(iVar5 + 4);
    while (iVar6 != 0) {
      if (*(uint *)(iVar6 + 0x10) < uVar2) {
        iVar6 = *(int *)(iVar6 + 0xc);
      }
      else {
        param_3 = (uint *)iVar6;
        iVar6 = *(int *)(iVar6 + 8);
      }
    }
    if ((param_3 == (uint *)iVar5) || (uVar2 < *(uint *)((int)param_3 + 0x10))) {
      param_2 = iVar5;
      piVar4 = &param_2;
    }
    else {
      piVar4 = (int *)&param_3;
    }
    iVar5 = *piVar4;
    puStack_28 = (uint *)0x4efec8;
    iVar6 = FUN_00487830();
    if (iVar5 != *(int *)(iVar6 + 0x22ec)) {
      puStack_28 = (uint *)0x0;
      uVar2 = (**(code **)(*(int *)(iVar5 + 0x88) + 0x34))(6);
      return (uint)(uVar3 <= uVar2);
    }
    break;
  case 0x2f:
    uVar7 = 0x29;
LAB_004f0054:
    puStack_28 = (uint *)0x1;
    param_3 = (uint *)*param_3;
    FUN_0054a6c0(uVar7,&param_3,4);
    break;
  case 0x30:
    puStack_28 = (uint *)0x4efbf7;
    uVar2 = (**(code **)(*param_1 + 0x40))();
    return uVar2;
  }
  return 0;
}

