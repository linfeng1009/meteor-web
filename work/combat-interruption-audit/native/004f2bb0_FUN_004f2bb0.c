/* Original Meteor.exe static export @ 004f2bb0; original sample not executed. */
/* XREF 005aa138 DATA */
/* XREF 005ab5c0 DATA */
/* XREF 005aba00 DATA */
/* XREF 005ab380 DATA */

int __fastcall FUN_004f2bb0(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_EDI;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_c = 0;
  uStack_8 = 0;
  uStack_4 = 0;
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  iVar3 = *param_1;
  uVar2 = (**(code **)(*piVar1 + 0xf4))();
  iVar3 = (**(code **)(iVar3 + 0x154))(&uStack_c,uVar2);
  if (iVar3 != 0) {
    (**(code **)(*param_1 + 0xd8))(unaff_EDI);
    return iVar3;
  }
  (**(code **)(*param_1 + 0xd8))(0);
  return 0;
}

