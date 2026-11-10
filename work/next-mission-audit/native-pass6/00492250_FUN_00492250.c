/* Original Meteor.exe static export @ 00492250; original sample not executed. */
/* XREF 005a9200 DATA */

void __thiscall FUN_00492250(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int unaff_EBX;
  int iVar5;
  int iStack_114;
  undefined4 uStack_104;
  undefined4 uStack_100;
  void **appvStack_fc [2];
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  void **ppvStack_ec;
  int iStack_e4;
  void *local_c0;
  int *piStack_bc;
  undefined4 uStack_b8;
  undefined1 *puStack_b4;
  int iStack_b0;
  int iStack_ac;
  undefined4 *puStack_9c;
  void *pvStack_98;
  int iStack_94;
  undefined4 uStack_90;
  undefined1 *puStack_8c;
  void *pvStack_88;
  char cStack_84;
  char cStack_74;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined1 auStack_44 [52];
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059e80d;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  local_c0 = operator_new(0x1d0);
  iVar5 = 0;
  local_4 = 0;
  if (local_c0 == (void *)0x0) {
    local_c0 = (void *)0x0;
  }
  else {
    local_c0 = (void *)FUN_005678a0();
  }
  local_4 = 0xffffffff;
  iVar1 = (**(code **)(*param_1 + 300))();
  if ((iVar1 != 0) && ((int *)(iVar1 + -0x65c) != (int *)0x0)) {
    iVar1 = (**(code **)(*(int *)(iVar1 + -0x65c) + 0x44))();
    if (iVar1 != 0) {
      FUN_0056b230();
      FUN_0047b310();
      iStack_e4 = 0x4922ff;
      pvStack_88 = operator_new(0xb0);
      puStack_8 = (undefined1 *)0x1;
      if (pvStack_88 == (void *)0x0) {
        piVar2 = (int *)0x0;
      }
      else {
        iStack_e4 = 0x49231e;
        piVar2 = (int *)FUN_004e5340();
      }
      puStack_8 = (undefined1 *)0xffffffff;
      piVar2[0x1c] = *(int *)(param_2 + 0x14);
      piVar2[0x1d] = *(int *)(param_2 + 0x18);
      piVar2[0x1e] = *(int *)(param_2 + 0x1c);
      iVar1 = *piVar2;
      FUN_0047ecf0();
      (**(code **)(iVar1 + 0x10))();
      piVar2[0x20] = *(int *)(param_2 + 4);
      FUN_0047b740();
      iStack_e4 = 0x492375;
      FUN_00477eb0();
      uStack_50 = *(undefined4 *)(param_2 + 8);
      uStack_4c = *(undefined4 *)(param_2 + 0xc);
      uStack_48 = *(undefined4 *)(param_2 + 0x10);
      iStack_e4 = 0x49239f;
      FUN_00477e30();
      puStack_b4 = (undefined1 *)0x0;
      iStack_b0 = 0;
      FUN_00502330();
      FUN_00502330();
      iStack_e4 = 0x4923c3;
      FUN_0049cae0();
      pvStack_c = (void *)0x2;
      if (0 < *(short *)(param_2 + 0x20)) {
        puVar3 = (undefined4 *)(param_2 + 0x2c);
        do {
          local_c0 = (void *)puVar3[-1];
          piStack_bc = (int *)*puVar3;
          if (puStack_9c == (undefined4 *)(iStack_94 + -0xc)) {
            iStack_e4 = 0x49242e;
            FUN_0049cc80();
          }
          else {
            if (puStack_9c != (undefined4 *)0x0) {
              *puStack_9c = puVar3[-2];
              puStack_9c[1] = local_c0;
              puStack_9c[2] = piStack_bc;
            }
            puStack_9c = puStack_9c + 3;
          }
          iVar5 = iVar5 + 1;
          puVar3 = puVar3 + 3;
        } while (iVar5 < *(short *)(param_2 + 0x20));
      }
      puStack_8c = (undefined1 *)&uStack_104;
      FUN_0049b1e0();
      uStack_104 = 0;
      uStack_100 = 0;
      FUN_00502330();
      FUN_00502330();
      FUN_0049cae0();
      pvStack_c._0_1_ = 3;
      puVar3 = (undefined4 *)FUN_0049b180();
      puVar4 = (undefined4 *)FUN_0049b160();
      FUN_004e6050(appvStack_fc);
      FUN_0049dfb0(auStack_44,*puVar4,puVar4[1],puVar4[2],puVar4[3],*puVar3,puVar3[1],puVar3[2],
                   puVar3[3]);
      pvStack_c = (void *)CONCAT31(pvStack_c._1_3_,2);
      (**(code **)(*piVar2 + 8))();
      iStack_e4 = 0x49253f;
      piStack_bc = piVar2;
      FUN_0049d520();
      if (cStack_74 == '\0') {
        iStack_e4 = 0x49255f;
        FUN_0049d3c0();
        if (*(undefined4 **)(unaff_EBX + 0x14) != (undefined4 *)0x0) {
          (**(code **)**(undefined4 **)(unaff_EBX + 0x14))();
        }
        iStack_e4 = *(int *)(unaff_EBX + 0x2110) + 4;
        ppvStack_ec = (void **)0x492588;
        uStack_f0 = FUN_0048ea60();
        ppvStack_ec = (void **)0x18;
        uStack_f4 = 0x492590;
        FUN_00402e90();
        *(int *)(unaff_EBX + 0x2114) = *(int *)(unaff_EBX + 0x2114) + -1;
        iStack_e4 = 0x4925ba;
        piStack_bc = piVar2;
        FUN_0049d520();
        if ((cStack_84 == '\0') && (&stack0x00000000 != (undefined1 *)0x114)) {
          (**(code **)(iStack_114 + 8))();
        }
      }
      piStack_bc = (int *)iStack_94;
      local_c0 = pvStack_98;
      puStack_8 = (undefined1 *)0x4;
      uStack_b8 = uStack_90;
      puStack_b4 = puStack_8c;
      FUN_004e6050();
      ppvStack_ec = &local_c0;
      uStack_f0 = 0x492619;
      FUN_004e6050();
      appvStack_fc[0] = &pvStack_88;
      uStack_100 = 0x492628;
      FUN_004e6050();
      appvStack_fc[0] = (void **)0x49262d;
      FUN_0049f320();
      puStack_8 = (undefined1 *)0xffffffff;
      if (iStack_b0 != 0) {
        iStack_e4 = 0x492659;
        FUN_0049ead0();
        if (iStack_ac != 0) {
          iStack_e4 = 0x49266f;
          FUN_00402e90();
        }
      }
    }
  }
  ExceptionList = pvStack_10;
  return;
}

