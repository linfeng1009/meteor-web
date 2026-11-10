/* Original Meteor.exe static read-only export; sample not executed. */

undefined4 __thiscall FUN_00494c60(int *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  int *unaff_EBX;
  int iVar5;
  int *local_588;
  int local_584;
  int local_57c;
  int local_578;
  undefined1 local_571;
  undefined1 local_570;
  undefined1 local_56f;
  undefined1 local_56e;
  undefined1 local_56d;
  int local_56c;
  int aiStack_568 [3];
  undefined1 local_55c [8];
  undefined1 local_554 [108];
  undefined4 local_4e8;
  undefined4 local_490;
  int local_36c;
  int local_368;
  int local_364;
  undefined4 local_360;
  undefined4 local_35c;
  int local_358;
  int local_354;
  undefined4 local_350;
  int local_34c;
  undefined4 local_348;
  char local_344;
  char local_343;
  char local_342;
  int local_340;
  byte *local_33c;
  byte *local_338;
  undefined4 local_328;
  undefined4 local_324;
  undefined4 local_31c;
  undefined4 local_318;
  undefined4 local_314;
  int local_310;
  byte *local_30c;
  byte *local_308;
  int local_304;
  byte *local_300;
  byte *local_2fc;
  undefined4 local_2f8;
  int local_2b4 [170];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059ea69;
  local_c = ExceptionList;
  local_56c = *param_2 - 1;
  ExceptionList = &local_c;
  if (0 < local_56c) {
    do {
      FUN_00493d90();
      FUN_0049b540(&local_570,0);
      local_4 = 0;
      FUN_00492690();
      local_4._0_1_ = 1;
      FUN_005498c0();
      FUN_005498c0();
      FUN_005498c0();
      FUN_005498c0();
      FUN_004024a0(&local_56f);
      local_4._0_1_ = 2;
      FUN_004024a0(&local_56d);
      local_4._0_1_ = 3;
      FUN_004024a0(&local_56e);
      local_4._0_1_ = 4;
      FUN_004024a0(&local_571);
      local_4._0_1_ = 5;
      FUN_005519d0();
      FUN_00498ca0();
      local_4 = CONCAT31(local_4._1_3_,6);
      local_490 = 0;
      local_31c = 0;
      local_4e8 = 0;
      local_360 = 0;
      local_368 = 0;
      local_36c = 0;
      local_34c = 0;
      local_364 = 0;
      local_344 = 0;
      local_343 = 0;
      local_342 = 0;
      local_324 = 0;
      local_328 = 0;
      local_350 = 0;
      local_354 = 0;
      local_358 = 0;
      local_314 = 0;
      local_35c = 0;
      local_318 = 0x40c00000;
      local_348 = 0;
      local_2f8 = 0;
      FUN_00549a90(0,0);
      FUN_00549bd0(0,0x40240000);
      FUN_005519e0();
      iVar5 = param_2[1] - 1;
      local_368 = param_2[2] - 1;
      local_4 = 7;
      local_36c = param_2[3] - 1;
      local_343 = param_2[4] - 1;
      bVar1 = param_2[6];
      local_344 = param_2[5] - 1;
      local_364 = param_2[7] - 1;
      local_358 = param_2[8] - 1;
      local_354 = param_2[9] - 1;
      FUN_004d5220(bVar1 - 1,0);
      local_34c = (uint)param_2[10] * 0x1a5e00 + (uint)param_2[0xb] * 0x3840 +
                  (uint)param_2[0xc] * 0x78 + (param_2[0xd] - 0x1a96b9);
      local_342 = param_2[0xe] - 1;
      param_2 = param_2 + 0xf;
      iVar3 = *param_2 - 1;
      if (0 < (int)(*param_2 - 1)) {
        do {
          local_584 = iVar3;
          bVar2 = param_2[1];
          param_2 = param_2 + 1;
          local_588 = (int *)CONCAT31(local_588._1_3_,bVar2);
          if (local_33c + 1 == local_338) {
            local_578 = 1;
            local_57c = (int)local_33c - local_340;
            piVar4 = &local_578;
            if (local_57c != 0) {
              piVar4 = &local_57c;
            }
            FUN_0049be40(*piVar4 + local_57c);
          }
          FUN_00402bc0(local_33c + 1);
          *local_33c = bVar2;
          local_33c = local_33c + 1;
          local_584 = local_584 + -1;
          iVar3 = local_584;
        } while (local_584 != 0);
      }
      param_2 = param_2 + 1;
      iVar3 = *param_2 - 1;
      if (0 < (int)(*param_2 - 1)) {
        do {
          local_584 = iVar3;
          bVar2 = param_2[1];
          param_2 = param_2 + 1;
          local_588 = (int *)CONCAT31(local_588._1_3_,bVar2);
          if (local_30c + 1 == local_308) {
            local_57c = 1;
            local_578 = (int)local_30c - local_310;
            piVar4 = &local_57c;
            if (local_578 != 0) {
              piVar4 = &local_578;
            }
            FUN_0049be40(*piVar4 + local_578);
          }
          FUN_00402bc0(local_30c + 1);
          *local_30c = bVar2;
          local_30c = local_30c + 1;
          local_584 = local_584 + -1;
          iVar3 = local_584;
        } while (local_584 != 0);
      }
      param_2 = param_2 + 1;
      iVar3 = *param_2 - 1;
      if (0 < (int)(*param_2 - 1)) {
        do {
          local_584 = iVar3;
          bVar2 = param_2[1];
          param_2 = param_2 + 1;
          local_588 = (int *)CONCAT31(local_588._1_3_,bVar2);
          if (local_300 + 1 == local_2fc) {
            local_57c = 1;
            local_578 = (int)local_300 - local_304;
            piVar4 = &local_57c;
            if (local_578 != 0) {
              piVar4 = &local_578;
            }
            FUN_0049be40(*piVar4 + local_578);
          }
          FUN_00402bc0(local_300 + 1);
          *local_300 = bVar2;
          local_300 = local_300 + 1;
          local_584 = local_584 + -1;
          iVar3 = local_584;
        } while (local_584 != 0);
      }
      local_2b4[0] = iVar5;
      FUN_0049a750(local_554);
      local_4._0_1_ = 8;
      FUN_0049d240(local_55c,local_2b4);
      local_4._0_1_ = 7;
      FUN_0048ee50();
      if (local_36c != 0) {
        (**(code **)(*param_1 + 0x11c))(local_368,iVar5,local_364);
        (**(code **)(*unaff_EBX + 0x168))(iVar5,bVar1 - 1);
        aiStack_568[0] = 0;
        aiStack_568[1] = 0;
        aiStack_568[2] = 0;
        FUN_004608a0(8);
        local_4._0_1_ = 9;
        FUN_00402a70();
        local_4 = CONCAT31(local_4._1_3_,10);
        FUN_004ab200(aiStack_568);
        if (local_584 != 0) {
          (**(code **)(*param_1 + 0x280))(local_584,aiStack_568[0]);
          FUN_0055d010(0);
          (**(code **)(*local_588 + 0x270))(local_584,local_36c);
        }
        local_4._0_1_ = 7;
        if ((aiStack_568[0] != 0) && (aiStack_568[2] - aiStack_568[0] != 0)) {
          FUN_00402e90(aiStack_568[0],aiStack_568[2] - aiStack_568[0]);
        }
      }
      if (local_344 == '\x02') {
        (**(code **)(*param_1 + 0x21c))(local_364,iVar5);
      }
      local_4 = 0xffffffff;
      FUN_0048ee50();
      local_56c = local_56c + -1;
    } while (local_56c != 0);
  }
  ExceptionList = local_c;
  return 0;
}


