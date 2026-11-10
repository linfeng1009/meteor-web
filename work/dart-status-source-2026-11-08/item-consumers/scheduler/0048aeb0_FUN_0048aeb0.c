/* Original Meteor.exe static read-only source export; not executed. */

void __fastcall FUN_0048aeb0(int *param_1)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  int *piVar8;
  int *piVar9;
  undefined1 local_2c [4];
  undefined1 auStack_28 [4];
  int *local_24;
  int *local_20;
  int local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059dfc0;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar4 = FUN_005499a0(local_2c);
  if ((iVar4 != 0) && (iVar4 = *(int *)(param_1[0x8bb] + 8), iVar4 != param_1[0x8bb])) {
    do {
      local_24 = (int *)0x0;
      local_20 = (int *)0x0;
      local_1c = 0;
      local_4 = 0;
      piVar8 = (int *)0x0;
      iVar5 = (**(code **)(*param_1 + 0x238))(*(undefined4 *)(iVar4 + 0x10));
      if (iVar5 != 0) {
        local_1c = 0;
        uStack_18 = 0;
        uStack_14 = 0;
        piVar8 = &local_1c;
      }
      (**(code **)(*(int *)(iVar4 + 0x88) + 4))(0x3e4ccccd,auStack_28,piVar8);
      if (piVar8 != (int *)0x0) {
        piVar9 = (int *)piVar8[1];
        piVar8 = (int *)*piVar8;
        iVar5 = (int)piVar9 - (int)piVar8 >> 0x1f;
        if ((((int)piVar9 - (int)piVar8) / 0xc + iVar5 != iVar5) &&
           (bVar2 = false, piVar8 != piVar9)) {
          do {
            if ((*piVar8 == 2) && (piVar8[1] < 0)) {
              bVar2 = true;
            }
            piVar8 = piVar8 + 3;
          } while (piVar8 != piVar9);
          if (bVar2) {
            piVar8 = (int *)(**(code **)(*param_1 + 0x23c))(*(undefined4 *)(iVar4 + 0x10));
            piVar8 = (int *)(**(code **)(*piVar8 + 0x44))();
            (**(code **)(*piVar8 + 0x48))(0x5a,0x3f800000,0,0xbf800000);
          }
        }
      }
      iVar5 = (**(code **)(*param_1 + 300))(*(undefined4 *)(iVar4 + 0x10));
      if (iVar5 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = iVar5 + -0x65c;
      }
      piVar8 = local_24;
      if (local_24 != local_20) {
        piVar9 = local_24 + 0xd;
        do {
          piVar6 = (int *)piVar9[-1];
          piVar1 = (int *)*piVar9;
          if (piVar6 != piVar1) {
            do {
              if (*piVar6 == 0xf) break;
              piVar6 = piVar6 + 3;
            } while (piVar6 != piVar1);
            if ((((piVar6 != piVar1) && (piVar6 != (int *)0x0)) && (piVar6[2] != 0)) && (iVar5 != 0)
               ) {
              FUN_0055dfc0(piVar6[2]);
              piVar8 = local_24;
            }
          }
          piVar6 = piVar9 + 5;
          piVar9 = piVar9 + 0x12;
        } while (piVar6 != local_20);
      }
      if (iVar5 != 0) {
        iVar5 = (**(code **)(*(int *)(iVar4 + 0x88) + 0x34))(10,0);
        FUN_005591b0(iVar5 != 0);
        piVar8 = local_24;
      }
      piVar9 = local_20;
      iVar5 = *(int *)(iVar4 + 0xc);
      if (iVar5 == 0) {
        iVar5 = *(int *)(iVar4 + 4);
        if (iVar4 == *(int *)(iVar5 + 0xc)) {
          do {
            iVar4 = iVar5;
            iVar5 = *(int *)(iVar4 + 4);
          } while (iVar4 == *(int *)(iVar5 + 0xc));
        }
        if (*(int *)(iVar4 + 0xc) != iVar5) {
          iVar4 = iVar5;
        }
      }
      else {
        for (iVar3 = *(int *)(iVar5 + 8); iVar4 = iVar5, iVar3 != 0; iVar3 = *(int *)(iVar3 + 8)) {
          iVar5 = iVar3;
        }
      }
      local_4 = 1;
      piVar6 = piVar8;
      for (; piVar8 != piVar9; piVar8 = piVar8 + 0x12) {
        (**(code **)*piVar8)(0);
        piVar6 = local_24;
      }
      local_4 = 0xffffffff;
      iVar5 = (local_1c - (int)piVar6) / 0x48;
      if (iVar5 != 0) {
        uVar7 = iVar5 * 0x48;
        if (uVar7 < 0x81) {
          FUN_00402330();
          *piVar6 = *(int *)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4);
          *(int **)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4) = piVar6;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(piVar6);
        }
      }
    } while (iVar4 != param_1[0x8bb]);
  }
  ExceptionList = local_c;
  return;
}

