/* Original Meteor.exe static export @ 00582b50; original sample not executed. */
/* XREF 005b0e20 DATA */
/* XREF 005b0ea8 DATA */
/* XREF 005b0f30 DATA */
/* XREF 005b0fb8 DATA */
/* XREF 005b1040 DATA */
/* XREF 005b10c8 DATA */
/* XREF 005b1150 DATA */
/* XREF 005b11d8 DATA */
/* XREF 005b1260 DATA */
/* XREF 005b12e8 DATA */
/* XREF 005b1370 DATA */
/* XREF 005b13f8 DATA */
/* XREF 005b1480 DATA */

undefined4 __thiscall FUN_00582b50(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a680b;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  (**(code **)(*param_1 + 0x68))();
  piVar2 = param_2;
  FUN_0050a118(param_1[0x7b] + 0xe4,4,1,param_2);
  iVar5 = 0;
  if (0 < *(int *)(param_1[0x7b] + 0xe4)) {
    do {
      pvVar3 = operator_new(0x68);
      uStack_4 = 0;
      if (pvVar3 == (void *)0x0) {
        param_2 = (int *)0x0;
      }
      else {
        param_2 = (int *)FUN_0058e150(param_1);
      }
      uStack_4 = 0xffffffff;
      iVar4 = (**(code **)(*param_2 + 8))(piVar2);
      if (iVar4 == 0) {
        ExceptionList = pvStack_c;
        return 0;
      }
      iVar4 = param_1[0x7b];
      puVar1 = *(undefined4 **)(iVar4 + 0xec);
      if (puVar1 == *(undefined4 **)(iVar4 + 0xf0)) {
        FUN_00583630(puVar1,&param_2);
      }
      else {
        if (puVar1 != (undefined4 *)0x0) {
          *puVar1 = param_2;
        }
        *(int *)(iVar4 + 0xec) = *(int *)(iVar4 + 0xec) + 4;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(param_1[0x7b] + 0xe4));
  }
  (**(code **)(*param_1 + 0x38))();
  ExceptionList = pvStack_c;
  return 1;
}

