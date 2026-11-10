/* Original Meteor.exe static export @ 004f1ae0; original sample not executed. */
/* XREF 005ab4f8 DATA */
/* XREF 005ab938 DATA */
/* XREF 004bc56f UNCONDITIONAL_CALL */
/* XREF 005ab2b8 DATA */

int __thiscall FUN_004f1ae0(int *param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  void *unaff_EDI;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a370b;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  piVar1 = (int *)FUN_00487830();
  iVar2 = (**(code **)(*piVar1 + 0x118))(param_2,param_3,param_4);
  if (iVar2 != 0) {
    param_1[0x95] = param_3;
    if (param_1[0x69] == 0) {
      pvVar3 = operator_new(0x528);
      if (pvVar3 == (void *)0x0) {
        iVar4 = 0;
      }
      else {
        iVar4 = FUN_004cabd0();
      }
      param_1[0x69] = iVar4;
    }
    iVar4 = *(int *)param_1[0x69];
    iVar5 = FUN_00487830();
    (**(code **)(iVar4 + 0x38))(iVar2,iVar5 + 0x20);
    (**(code **)(*param_1 + 0x10))(param_1[0x69]);
    iVar4 = FUN_00487830();
    iVar4 = **(int **)(iVar4 + 0x2180);
    iVar5 = FUN_00487830();
    (**(code **)(iVar4 + 0x3c))(iVar2,iVar5 + 0x20);
  }
  ExceptionList = unaff_EDI;
  return iVar2;
}

