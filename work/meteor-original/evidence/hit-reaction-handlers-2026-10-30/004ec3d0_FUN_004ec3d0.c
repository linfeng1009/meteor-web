/* Original Meteor.exe static export @ 004ec3d0; original sample not executed. */
/* XREF 005ab1dc DATA */

/* WARNING: Type propagation algorithm not settling */

void __thiscall FUN_004ec3d0(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iStack_3c;
  int iStack_38;
  int aiStack_34 [3];
  undefined4 *puStack_28;
  int iStack_24;
  int iStack_20;
  undefined4 *puStack_1c;
  int iStack_18;
  int iStack_14;
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a3180;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  param_1[0x14] = 0;
  (**(code **)(*param_1 + 8))(param_2);
  FUN_005005b0(&stack0x00000000);
  puStack_8 = (undefined1 *)0x0;
  FUN_005005b0(&stack0xffffffc3);
  puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,1);
  FUN_004b48c0(&iStack_3c);
  if (iStack_3c != param_2[0xea]) {
    do {
      if ((*(int *)(iStack_3c + 0x208) == 1) && (*(int *)(iStack_3c + 0x200) == 1)) {
        if (iStack_18 == iStack_14) {
          FUN_0049c640(iStack_18,iStack_3c + 0x10);
        }
        else {
          FUN_004a8e30();
          iStack_18 = iStack_18 + 4;
        }
      }
      if ((*(int *)(iStack_3c + 0x208) == 2) && (*(int *)(iStack_3c + 0x200) == 1)) {
        if (iStack_24 == iStack_20) {
          FUN_0049c640(iStack_24,iStack_3c + 0x10);
        }
        else {
          FUN_004a8e30();
          iStack_24 = iStack_24 + 4;
        }
      }
      FUN_0043c6c0();
    } while (iStack_3c != param_2[0xea]);
  }
  iVar2 = iStack_18;
  if ((iStack_18 - (int)puStack_1c & 0xfffffffcU) != 0) {
    iVar1 = _rand();
    iStack_38 = puStack_1c[(uint)(iVar1 * (iVar2 - (int)puStack_1c >> 2)) / 0x7fff];
    param_1[0x16] = iStack_38;
    FUN_0049d3c0(aiStack_34,&iStack_38);
    *(undefined1 *)(aiStack_34[0] + 0x228) = 2;
    aiStack_34[2] = param_1[0x16];
    aiStack_34[1] = 1;
    (**(code **)(*param_2 + 0x40))(0x23,aiStack_34 + 1,8,1);
  }
  iVar2 = iStack_24;
  if ((iStack_24 - (int)puStack_28 & 0xfffffffcU) != 0) {
    iVar1 = _rand();
    aiStack_34[0] = puStack_28[(uint)(iVar1 * (iVar2 - (int)puStack_28 >> 2)) / 0x7fff];
    param_1[0x17] = aiStack_34[0];
    FUN_0049d3c0(&iStack_38,aiStack_34);
    *(undefined1 *)(iStack_38 + 0x228) = 2;
    aiStack_34[2] = param_1[0x17];
    aiStack_34[1] = 2;
    (**(code **)(*param_2 + 0x40))(0x23,aiStack_34 + 1,8,1);
  }
  puStack_8 = (undefined1 *)((uint)puStack_8 & 0xffffff00);
  iVar2 = iStack_20 - (int)puStack_28 >> 2;
  if (iVar2 != 0) {
    uVar3 = iVar2 * 4;
    if (uVar3 < 0x81) {
      FUN_00402330();
      *puStack_28 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puStack_28;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(puStack_28);
    }
  }
  puStack_8 = (undefined1 *)0xffffffff;
  iVar2 = iStack_14 - (int)puStack_1c >> 2;
  if (iVar2 != 0) {
    uVar3 = iVar2 * 4;
    if (uVar3 < 0x81) {
      FUN_00402330();
      *puStack_1c = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puStack_1c;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(puStack_1c);
    }
  }
  ExceptionList = pvStack_10;
  return;
}

