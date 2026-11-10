/* Original Meteor.exe static export @ 004ac160; original sample not executed. */
/* XREF 005a9c30 DATA */
/* XREF 005aa4f8 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004ac160(int *param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  char cVar5;
  char *pcVar6;
  bool bVar7;
  int local_580;
  char *local_57c;
  char *local_578;
  float local_574;
  int local_570;
  undefined1 local_56a;
  undefined1 local_569;
  undefined1 local_568;
  undefined1 local_567;
  undefined1 local_566;
  undefined1 local_565;
  int local_564 [3];
  int *local_558;
  undefined1 local_554 [108];
  undefined4 local_4e8;
  undefined4 local_490;
  undefined4 local_36c;
  undefined4 local_368;
  undefined4 local_364;
  undefined4 local_360;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_348;
  undefined1 local_344;
  char local_343;
  char local_342;
  char *local_340;
  int local_33c;
  undefined4 local_334 [3];
  undefined4 local_328;
  undefined4 local_324;
  undefined4 local_31c;
  undefined4 local_318;
  undefined4 local_314;
  char local_310 [4];
  char local_30c;
  char local_304 [4];
  char local_300;
  undefined4 local_2f8;
  undefined4 local_2b4 [166];
  void *pvStack_1c;
  undefined4 uStack_14;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a007a;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  local_558 = param_1;
  FUN_00493d90();
  FUN_004b36f0(&local_56a);
  local_4 = 0;
  FUN_00492690();
  local_4._0_1_ = 1;
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  FUN_005498c0();
  FUN_004024a0(&local_566);
  local_4._0_1_ = 2;
  FUN_004024a0(&local_569);
  local_4._0_1_ = 3;
  FUN_004024a0(&local_568);
  local_4._0_1_ = 4;
  FUN_004024a0(&local_565);
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
  local_342 = '\0';
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
  local_4 = 7;
  if ((char **)(param_3 + 0x10) != &local_340) {
    FUN_00403200(*(char **)(param_3 + 0x10),*(undefined4 *)(param_3 + 0x14));
  }
  local_343 = *(char *)(param_3 + 2);
  if ((undefined4 *)(param_3 + 0x1c) != local_334) {
    FUN_00403200(*(undefined4 *)(param_3 + 0x1c),*(undefined4 *)(param_3 + 0x20));
  }
  if ((char *)(param_3 + 0x28) != local_310) {
    FUN_00403200(*(undefined4 *)(param_3 + 0x28),*(undefined4 *)(param_3 + 0x2c));
  }
  if ((char *)(param_3 + 0x34) != local_304) {
    FUN_00403200(*(undefined4 *)(param_3 + 0x34),*(undefined4 *)(param_3 + 0x38));
  }
  piVar1 = param_1 + 0xea;
  FUN_004b48c0(&local_570);
  if (local_570 != *piVar1) {
    do {
      iVar4 = *(int *)(local_570 + 0x230) - (int)*(char **)(local_570 + 0x22c);
      if (iVar4 == local_33c - (int)local_340) {
        bVar7 = true;
        pcVar6 = *(char **)(local_570 + 0x22c);
        pcVar2 = local_340;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar7 = *pcVar6 == *pcVar2;
          pcVar6 = pcVar6 + 1;
          pcVar2 = pcVar2 + 1;
        } while (bVar7);
        if ((bVar7) && (*(char *)(local_570 + 0x22a) == local_342)) {
          local_342 = local_342 + '\x01';
        }
      }
      FUN_0043c6c0();
      param_1 = local_558;
    } while (local_570 != *piVar1);
  }
  local_574 = (float)param_1[0x8f] * _DAT_005a8410;
  FUN_004d4a70(local_574);
  local_318 = param_4;
  local_2b4[0] = param_2;
  FUN_0049a750(local_554);
  local_4._0_1_ = 8;
  FUN_0049d240(local_564,local_2b4);
  local_4._0_1_ = 7;
  FUN_0048ee50();
  FUN_00402b70(&local_567,8);
  local_4._0_1_ = 9;
  FUN_00402a70();
  local_4 = CONCAT31(local_4._1_3_,10);
  if (local_57c + 1 == local_578) {
    local_564[0] = (int)local_57c - local_580;
    local_574 = 1.4013e-45;
    piVar1 = (int *)FUN_0049c0d0(local_564,&local_574);
    FUN_0049be40(local_57c + (*piVar1 - local_580));
  }
  FUN_00402bc0(local_57c + 1);
  *local_57c = (char)param_2 + '\x01';
  pcVar2 = local_57c + 1;
  cVar5 = local_342 + '\x01';
  pcVar6 = local_57c + 2;
  local_57c = pcVar2;
  if (pcVar6 == local_578) {
    local_574 = (float)((int)pcVar2 - local_580);
    local_564[0] = 1;
    piVar1 = (int *)FUN_0049c0d0(&local_574,local_564);
    FUN_0049be40(local_57c + (*piVar1 - local_580));
  }
  FUN_00402bc0(local_57c + 1);
  *local_57c = cVar5;
  local_57c = local_57c + 1;
  FUN_00498c40(local_343 + '\x01');
  FUN_00498c40(((char)local_33c - (char)local_340) + '\x01');
  uVar3 = FUN_0049de10(local_564,&local_580,&local_340);
  local_4._0_1_ = 0xb;
  FUN_00473340(uVar3);
  local_4._0_1_ = 10;
  FUN_004026e0();
  FUN_00498c40((local_30c - local_310[0]) + '\x01');
  uVar3 = FUN_0049de10(local_564,&local_580,local_310);
  local_4._0_1_ = 0xc;
  FUN_00473340(uVar3);
  local_4._0_1_ = 10;
  FUN_004026e0();
  FUN_00498c40((local_300 - local_304[0]) + '\x01');
  uVar3 = FUN_0049de10(local_564,&local_580,local_304);
  local_4._0_1_ = 0xd;
  FUN_00473340(uVar3);
  local_4 = CONCAT31(local_4._1_3_,10);
  FUN_004026e0();
  (**(code **)(*local_558 + 0x40))(0,local_580,(int)local_57c - local_580,1);
  uStack_14 = CONCAT31(uStack_14._1_3_,7);
  FUN_004026e0();
  uStack_14 = 0xffffffff;
  FUN_0048ee50();
  ExceptionList = pvStack_1c;
  return;
}

