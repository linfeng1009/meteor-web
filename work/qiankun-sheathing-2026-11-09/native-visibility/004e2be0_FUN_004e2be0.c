/* Original Meteor.exe static export @ 004e2be0; original sample not executed. */
/* XREF 005aaf68 DATA */

undefined4 FUN_004e2be0(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  void *pvVar3;
  void *unaff_EBX;
  undefined4 uVar4;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a2c8b;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  iVar1 = (**(code **)(*param_1 + 0x58))(param_2);
  if (iVar1 == 0) {
    if (param_2 == 1) {
      piVar2 = (int *)FUN_00487830();
      iVar1 = (**(code **)(*piVar2 + 0x140))(1);
LAB_004e2c43:
      uVar4 = 0;
      if (iVar1 != 0) {
        pvVar3 = operator_new(0x1d0);
        puStack_8 = (undefined1 *)0x0;
        if (pvVar3 != (void *)0x0) {
          uVar4 = FUN_005678a0();
        }
        puStack_8 = (undefined1 *)0xffffffff;
        FUN_0056b230(uVar4);
        (**(code **)(*param_1 + 0x5c))(param_2,uVar4);
        goto LAB_004e2c86;
      }
    }
    else if (param_2 == 2) {
      piVar2 = (int *)FUN_00487830();
      iVar1 = (**(code **)(*piVar2 + 0x144))(2);
      goto LAB_004e2c43;
    }
    uVar4 = 0;
  }
  else {
LAB_004e2c86:
    uVar4 = 1;
  }
  ExceptionList = unaff_EBX;
  return uVar4;
}

