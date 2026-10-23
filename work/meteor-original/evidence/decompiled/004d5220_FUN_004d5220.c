/* Meteor.exe original x86 @ 004d5220 */
/* Caller: 00494ecf */
/* Caller: 005a94a4 */

undefined4 __thiscall FUN_004d5220(int param_1,undefined ***param_2,int param_3)

{
  uint *puVar1;
  int *piVar2;
  undefined ***pppuVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined ***extraout_ECX;
  undefined ***local_c0;
  undefined ***local_bc;
  undefined **local_a8;
  undefined **local_a4;
  undefined1 local_9d;
  undefined **local_9c [10];
  int local_74;
  undefined **local_54 [15];
  undefined **local_18 [3];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a1e14;
  local_c = ExceptionList;
  if ((*(int *)(param_1 + 0x3c) != 0) &&
     (*(undefined ****)(*(int *)(param_1 + 0x3c) + 0x28) == param_2)) {
    return 0;
  }
  local_bc = (undefined ***)0x4d5263;
  ExceptionList = &local_c;
  FUN_00492000();
  local_bc = (undefined ***)&local_9d;
  local_4 = 0;
  local_c0 = (undefined ***)0x4d5278;
  FUN_005005b0();
  local_9c[0] = &PTR_FUN_005a9488;
  local_4 = 1;
  local_bc = (undefined ***)0x4d5290;
  FUN_004d6570();
  local_bc = local_9c;
  local_c0 = param_2;
  iVar4 = FUN_004d65c0(1);
  if (iVar4 == 0) {
    local_4 = 0xffffffff;
    local_bc = (undefined ***)0x4d5498;
    FUN_0048f240();
    ExceptionList = local_c;
    return 0;
  }
  puVar1 = (uint *)(param_1 + 0x40);
  if (param_3 == 0) {
    pppuVar3 = (undefined ***)*puVar1;
    local_bc = &local_a4;
    local_a8 = (undefined **)0x0;
    local_c0 = (undefined ***)0x4d53f5;
    puVar5 = (undefined4 *)FUN_004e8720();
    local_bc = &local_a8;
    local_c0 = pppuVar3;
    FUN_0046ef50(*puVar5);
    if (local_a8 == (undefined **)0x0) goto LAB_004d5423;
    local_c0 = (undefined ***)&local_bc;
    local_bc = extraout_ECX;
    FUN_004e8720();
  }
  else {
    piVar6 = *(int **)*puVar1;
    for (piVar2 = piVar6; piVar2 != (int *)*puVar1; piVar2 = (int *)*piVar2) {
      if (local_74 == piVar2[0xc]) {
        if (piVar6 != piVar2) {
          local_bc = (undefined ***)(piVar2 + 2);
          local_c0 = (undefined ***)0x4d532b;
          FUN_0049ab40();
          local_bc = (undefined ***)(piVar2 + 0x11);
          local_4._0_1_ = 2;
          local_c0 = (undefined ***)0x4d5343;
          FUN_0049f4c0();
          local_54[0] = &PTR_FUN_005a9488;
          local_bc = (undefined ***)(piVar6 + 2);
          local_4._0_1_ = 3;
          local_c0 = (undefined ***)0x4d535e;
          FUN_004d3cd0();
          local_bc = (undefined ***)(piVar6 + 0x11);
          local_c0 = (undefined ***)0x4d536a;
          FUN_004d3e60();
          local_bc = local_54;
          local_c0 = (undefined ***)0x4d5376;
          FUN_004d3cd0();
          local_bc = local_18;
          local_c0 = (undefined ***)0x4d5386;
          FUN_004d3e60();
          local_4._0_1_ = 4;
          local_bc = (undefined ***)0x4d539a;
          FUN_004d6940();
          local_4 = CONCAT31(local_4._1_3_,1);
          local_bc = (undefined ***)0x4d53ab;
          FUN_004920f0();
        }
        *(int **)(param_1 + 0x3c) = piVar6 + 2;
        local_4 = 5;
        goto LAB_004d53bc;
      }
    }
    local_c0 = (undefined ***)*puVar1;
    local_bc = &local_a8;
    local_a8 = (undefined **)0x0;
    FUN_0046ef50(*local_c0);
    if (local_a8 < (undefined **)0x2) goto LAB_004d5423;
    local_a8 = (undefined **)*puVar1;
    local_bc = (undefined ***)0x4d5305;
    puVar5 = (undefined4 *)FUN_004d6b10();
    local_bc = (undefined ***)*puVar5;
  }
  local_c0 = &local_a4;
  FUN_004d6ab0();
LAB_004d5423:
  local_bc = local_9c;
  FUN_004e8720(&local_c0);
  FUN_004d6ae0(&local_a4);
  local_bc = &local_a4;
  local_a8 = (undefined **)0x0;
  pppuVar3 = (undefined ***)*puVar1;
  local_c0 = (undefined ***)0x4d544f;
  puVar5 = (undefined4 *)FUN_004e8720();
  local_bc = &local_a8;
  local_c0 = pppuVar3;
  FUN_0046ef50(*puVar5);
  local_bc = &local_a4;
  local_c0 = (undefined ***)0x4d546c;
  piVar6 = (int *)FUN_004e8720();
  *(int *)(param_1 + 0x3c) = *piVar6 + 8;
  local_4 = 6;
LAB_004d53bc:
  local_bc = (undefined ***)0x4d53c5;
  FUN_004d6940();
  local_4 = 0xffffffff;
  local_bc = (undefined ***)0x4d53d9;
  FUN_004920f0();
  ExceptionList = local_c;
  return 1;
}

