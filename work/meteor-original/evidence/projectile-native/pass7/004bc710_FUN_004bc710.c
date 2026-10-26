/* Original Meteor.exe static export @ 004bc710; original sample not executed. */
/* XREF 005aa05c DATA */

undefined4 FUN_004bc710(void)

{
  void *pvVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 auStack_1dc [48];
  int iStack_1ac;
  undefined4 *puStack_24;
  int iStack_1c;
  int iStack_18;
  int iStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a0f79;
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
  if (iStack_1ac != 0) {
    uVar2 = FUN_004f1960();
    uStack_4 = 3;
    if ((iStack_18 != 0) && (iStack_10 - iStack_18 != 0)) {
      FUN_00402e90(iStack_18,iStack_10 - iStack_18);
    }
    uVar3 = iStack_1c - (int)puStack_24;
    if ((puStack_24 != (undefined4 *)0x0) && (uVar3 != 0)) {
      if (uVar3 < 0x81) {
        FUN_00402330();
        *puStack_24 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puStack_24;
        FUN_00443330();
      }
      else {
        FUN_005089fd(puStack_24);
      }
    }
    ExceptionList = pvStack_c;
    return uVar2;
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

