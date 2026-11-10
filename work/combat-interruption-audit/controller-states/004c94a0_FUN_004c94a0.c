/* Original Meteor.exe static export @ 004c94a0; original sample not executed. */
/* XREF 005aa69c DATA */

undefined4 __thiscall FUN_004c94a0(int *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  undefined4 uStack_b4;
  void *pvStack_b0;
  uint uStack_ac;
  undefined4 uStack_a8;
  int iStack_a4;
  int iStack_a0;
  uint local_9c;
  uint local_98;
  int iStack_94;
  int local_90;
  int aiStack_88 [21];
  int local_34 [2];
  uint uStack_2c;
  uint uStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a186b;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_00507979(param_2,0x80,DAT_005ac35c,1);
  local_4 = 0;
  if (*(int *)((int)aiStack_88 + *(int *)(local_90 + 4)) == 0) {
    local_34[0] = 0x1e0d;
    FUN_00507fb7(local_34,0x28);
    if (local_34[0] == 0x1e0d) {
      piVar2 = (int *)FUN_00487830();
      (**(code **)(*piVar2 + 0x214))(&local_9c,&local_98);
      if ((uStack_2c <= local_9c) && (uStack_28 <= local_98)) {
        iStack_a0 = iStack_18;
        iStack_c0 = iStack_1c;
        iStack_94 = iStack_14;
        FUN_00507fb7(param_1 + 0x41,0x14);
        FUN_00507fb7(param_1 + 0x31,4);
        FUN_00507fb7(param_1 + 0x32,4);
        FUN_00507fb7(param_1 + 0x37,4);
        FUN_00507fb7(param_1 + 0x3d,4);
        FUN_00507fb7(param_1 + 0x39,4);
        FUN_00507fb7(param_1 + 0x3a,4);
        FUN_00507fb7(param_1 + 0x38,4);
        FUN_00507fb7(param_1 + 0x3b,4);
        iVar3 = iStack_1c;
        if (0 < iStack_24) {
          iStack_a4 = iStack_24;
          do {
            pvStack_b0 = (void *)0x0;
            uStack_ac = 0;
            FUN_00507fb7(&uStack_b4,4);
            FUN_00507fb7(&uStack_a8,4);
            FUN_00507fb7(&uStack_ac,4);
            if (uStack_ac != 0) {
              pvStack_b0 = operator_new(uStack_ac);
              FUN_00507fb7(pvStack_b0,uStack_ac);
            }
            puVar1 = (undefined4 *)param_1[3];
            if (puVar1 == (undefined4 *)param_1[4]) {
              FUN_004c9b80(puVar1,&uStack_b4);
            }
            else {
              if (puVar1 != (undefined4 *)0x0) {
                *puVar1 = uStack_b4;
                puVar1[1] = pvStack_b0;
                puVar1[2] = uStack_ac;
                puVar1[3] = uStack_a8;
              }
              param_1[3] = param_1[3] + 0x10;
            }
            iStack_a4 = iStack_a4 + -1;
          } while (iStack_a4 != 0);
          iStack_a4 = 0;
          iVar3 = iStack_c0;
        }
        iVar4 = iStack_20;
        if (0 < iStack_20) {
          do {
            FUN_00507fb7(&iStack_c0,0xc);
            piVar2 = (int *)param_1[7];
            if (piVar2 == (int *)param_1[8]) {
              FUN_004c9eb0(piVar2,&iStack_c0);
            }
            else {
              if (piVar2 != (int *)0x0) {
                *piVar2 = iStack_c0;
                piVar2[1] = iStack_bc;
                piVar2[2] = iStack_b8;
              }
              param_1[7] = param_1[7] + 0xc;
            }
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
        if (0 < iVar3) {
          do {
            FUN_00507fb7(&iStack_c0,8);
            piVar2 = (int *)param_1[0xb];
            if (piVar2 == (int *)param_1[0xc]) {
              FUN_004ca1f0(piVar2,&iStack_c0);
            }
            else {
              if (piVar2 != (int *)0x0) {
                *piVar2 = iStack_c0;
                piVar2[1] = iStack_bc;
              }
              param_1[0xb] = param_1[0xb] + 8;
            }
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
        }
        iVar3 = iStack_a0;
        if (0 < iStack_a0) {
          do {
            uStack_b4 = 0;
            pvStack_b0 = (void *)0x0;
            uStack_ac = 0;
            FUN_00507fb7(&uStack_b4,0x10);
            puVar1 = (undefined4 *)param_1[0xf];
            if (puVar1 == (undefined4 *)param_1[0x10]) {
              FUN_004ca4c0(puVar1,&uStack_b4);
            }
            else {
              if (puVar1 != (undefined4 *)0x0) {
                *puVar1 = uStack_b4;
                puVar1[1] = pvStack_b0;
                puVar1[2] = uStack_ac;
                puVar1[3] = uStack_a8;
              }
              param_1[0xf] = param_1[0xf] + 0x10;
            }
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
        }
        iVar3 = iStack_94;
        if (0 < iStack_94) {
          do {
            iStack_c0 = 0;
            iStack_bc = 0;
            FUN_00507fb7(&iStack_c0,0xc);
            piVar2 = (int *)param_1[0x13];
            if (piVar2 == (int *)param_1[0x14]) {
              FUN_004ca7f0(piVar2,&iStack_c0);
            }
            else {
              if (piVar2 != (int *)0x0) {
                *piVar2 = iStack_c0;
                piVar2[1] = iStack_bc;
                piVar2[2] = iStack_b8;
              }
              param_1[0x13] = param_1[0x13] + 0xc;
            }
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
        }
        FUN_00507a71();
        (**(code **)(*param_1 + 0xc))();
        local_4 = 0xffffffff;
        FUN_00507a30();
        FUN_005078d5();
        ExceptionList = pvStack_c;
        return 1;
      }
    }
  }
  local_4 = 0xffffffff;
  FUN_00507a30();
  FUN_005078d5();
  ExceptionList = pvStack_c;
  return 0;
}

