/* Original Meteor.exe static export @ 004ee9a0; original sample not executed. */
/* XREF 005aa128 DATA */
/* XREF 005ab5b0 DATA */
/* XREF 005ab9f0 DATA */
/* XREF 005ab370 DATA */

undefined4
FUN_004ee9a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5
            )

{
  int *piVar1;
  int iVar2;
  undefined4 unaff_retaddr;
  undefined4 uStack_14;
  int iStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_14 = param_1;
  iStack_10 = param_5;
  uStack_c = __ftol();
  uStack_8 = __ftol();
  uStack_4 = __ftol();
  FUN_0054a6c0(0x17,&uStack_14,0x14,0);
  piVar1 = (int *)FUN_004db420();
  iVar2 = (**(code **)(*piVar1 + 8))(param_1,0);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_5 != 0) {
    FUN_00566200(1);
  }
  FUN_0047b7d0(unaff_retaddr,param_1,param_2,1);
  return 1;
}

