/* Original Meteor.exe static export @ 004bc8b0; original sample not executed. */
/* XREF 005aa198 DATA */

undefined4 __fastcall FUN_004bc8b0(int *param_1)

{
  void *pvVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 auStack_1dc [56];
  int iStack_1a4;
  undefined4 *puStack_24;
  int iStack_1c;
  int iStack_18;
  int iStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a0fb9;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  if (DAT_005e0328 == 0) {
    ExceptionList = &pvStack_c;
    pvVar1 = operator_new(0x33c);
    uStack_4 = 0;
    if (pvVar1 == (void *)0x0) {
      DAT_005e0328 = 0;
    }
    else {
      DAT_005e0328 = FUN_0044d020();
    }
  }
  uStack_4 = 0xffffffff;
  FUN_0045a450(auStack_1dc);
  uStack_4 = 1;
  if (iStack_1a4 != 0) {
    piVar2 = (int *)(**(code **)(*param_1 + 0x44))();
    uVar3 = (**(code **)(*piVar2 + 0x1b8))();
    uStack_4 = 3;
    if ((iStack_18 != 0) && (iStack_10 - iStack_18 != 0)) {
      FUN_00402e90(iStack_18,iStack_10 - iStack_18);
    }
    uVar4 = iStack_1c - (int)puStack_24;
    if ((puStack_24 != (undefined4 *)0x0) && (uVar4 != 0)) {
      if (uVar4 < 0x81) {
        FUN_00402330();
        *puStack_24 = *(undefined4 *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = puStack_24;
        FUN_00443330();
      }
      else {
        FUN_005089fd(puStack_24);
      }
    }
    ExceptionList = pvStack_c;
    return uVar3;
  }
  uStack_4 = 2;
  if ((iStack_18 != 0) && (iStack_10 - iStack_18 != 0)) {
    FUN_00402e90(iStack_18,iStack_10 - iStack_18);
  }
  uStack_4 = 0xffffffff;
  if ((puStack_24 != (undefined4 *)0x0) && (iStack_1c - (int)puStack_24 != 0)) {
    FUN_00402e90(puStack_24,iStack_1c - (int)puStack_24);
  }
  ExceptionList = pvStack_c;
  return 0;
}

