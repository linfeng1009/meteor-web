/* Original Meteor.exe static export @ 004f1560; original sample not executed. */
/* XREF 005aa050 DATA */
/* XREF 005ab4d8 DATA */
/* XREF 005ab918 DATA */
/* XREF 005ab298 DATA */

undefined4 __fastcall FUN_004f1560(int *param_1)

{
  int iVar1;
  undefined4 *unaff_EBX;
  uint uVar2;
  int iVar3;
  int local_30;
  int local_2c;
  undefined4 *local_28;
  int iStack_24;
  int iStack_20;
  undefined1 auStack_1c [12];
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005a36c8;
  pvStack_c = ExceptionList;
  uVar2 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = (undefined4 *)0x0;
  local_4 = 0;
  ExceptionList = &pvStack_c;
  (**(code **)(*param_1 + 0x74))(&local_30);
  iVar3 = local_30 - (int)unaff_EBX >> 0x1f;
  iVar1 = (local_30 - (int)unaff_EBX) / 0xc + iVar3;
  if (iVar1 == iVar3) {
    iVar3 = (local_2c - (int)unaff_EBX) / 0xc;
    if (iVar3 != 0) {
      uVar2 = iVar3 * 0xc;
      if (uVar2 < 0x81) {
        FUN_00402330();
        *unaff_EBX = *(undefined4 *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = unaff_EBX;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(unaff_EBX);
      }
    }
    ExceptionList = pvStack_10;
    return 0;
  }
  if (iVar1 != iVar3) {
    iVar3 = 0;
    do {
      (**(code **)(*(int *)(*(int *)((int)unaff_EBX + iVar3) + 0x65c) + 4))(auStack_1c,0,0);
      unaff_EBX = local_28;
      local_2c = iStack_20;
      local_30 = iStack_24;
      (**(code **)(*param_1 + 0x140))(s_ReBorn_005c9f88,local_28,iStack_24,iStack_20,0);
      uVar2 = uVar2 + 1;
      iVar3 = iVar3 + 0xc;
    } while (uVar2 < (uint)((local_30 - (int)unaff_EBX) / 0xc));
  }
  iVar3 = (local_2c - (int)unaff_EBX) / 0xc;
  if (iVar3 != 0) {
    uVar2 = iVar3 * 0xc;
    if (0x80 < uVar2) {
      FUN_005089fd(unaff_EBX);
      ExceptionList = pvStack_10;
      return 1;
    }
    FUN_00402330();
    *unaff_EBX = *(undefined4 *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
    *(undefined4 **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = unaff_EBX;
    DAT_005d59e8 = 0;
  }
  ExceptionList = pvStack_10;
  return 1;
}

