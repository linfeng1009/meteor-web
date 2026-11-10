/* Original Meteor.exe static export @ 004f1d90; original sample not executed. */
/* XREF 005aa024 DATA */
/* XREF 005ab4ac DATA */
/* XREF 005ab8ec DATA */
/* XREF 005ab26c DATA */

int __fastcall FUN_004f1d90(int *param_1)

{
  void *pvVar1;
  int iVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a372b;
  local_c = ExceptionList;
  if (param_1[0x69] == 0) {
    ExceptionList = &local_c;
    pvVar1 = operator_new(0x528);
    local_4 = 0;
    if (pvVar1 == (void *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_004cabd0();
    }
    local_4 = 0xffffffff;
    param_1[0x69] = iVar2;
    (**(code **)(*param_1 + 0x10))(iVar2);
  }
  ExceptionList = local_c;
  return param_1[0x69];
}

