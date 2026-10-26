/* Original Meteor.exe static export @ 00581c40; original sample not executed. */
/* XREF 005b0e18 DATA */
/* XREF 005b0ea0 DATA */
/* XREF 005b0f28 DATA */
/* XREF 005b0fb0 DATA */
/* XREF 005b1038 DATA */
/* XREF 005b10c0 DATA */
/* XREF 005b1148 DATA */
/* XREF 005b11d0 DATA */
/* XREF 005b12e0 DATA */
/* XREF 005b1368 DATA */
/* XREF 005b13f0 DATA */
/* XREF 005b1478 DATA */
/* XREF 0058881f UNCONDITIONAL_CALL */

void __thiscall FUN_00581c40(int param_1,int param_2)

{
  int *piVar1;
  void *pvVar2;
  undefined4 uVar3;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a67d6;
  pvStack_c = ExceptionList;
  piVar1 = *(int **)(*(int *)(param_1 + 0x1ec) + 0x10);
  ExceptionList = &pvStack_c;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &pvStack_c;
    (**(code **)(*piVar1 + 0x14))(1);
    *(undefined4 *)(*(int *)(param_1 + 0x1ec) + 0x10) = 0;
  }
  if (param_2 == 0) {
    pvVar2 = operator_new(0x8c);
    uStack_4 = 0;
    if (pvVar2 != (void *)0x0) {
      uVar3 = FUN_0058eba0(param_1);
      goto LAB_00581cd5;
    }
  }
  else {
    if (param_2 != 1) {
      ExceptionList = pvStack_c;
      return;
    }
    pvVar2 = operator_new(0xb4);
    uStack_4 = 1;
    if (pvVar2 != (void *)0x0) {
      uVar3 = FUN_0058f5f0(param_1);
      goto LAB_00581cd5;
    }
  }
  uVar3 = 0;
LAB_00581cd5:
  uStack_4 = 0xffffffff;
  FUN_00581d00(uVar3);
  ExceptionList = pvStack_c;
  return;
}

