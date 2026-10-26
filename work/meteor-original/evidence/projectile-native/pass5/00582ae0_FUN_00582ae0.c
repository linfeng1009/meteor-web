/* Original Meteor.exe static export @ 00582ae0; original sample not executed. */
/* XREF 005b0e1c DATA */
/* XREF 005b0ea4 DATA */
/* XREF 005b0f2c DATA */
/* XREF 005b0fb4 DATA */
/* XREF 005b103c DATA */
/* XREF 005b10c4 DATA */
/* XREF 005b114c DATA */
/* XREF 005b11d4 DATA */
/* XREF 005b125c DATA */
/* XREF 005b12e4 DATA */
/* XREF 005b136c DATA */
/* XREF 005b13f4 DATA */
/* XREF 005b147c DATA */

undefined4 __thiscall FUN_00582ae0(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  FUN_00509fa2(*(int *)(param_1 + 0x1ec) + 0xe4,4,1,param_2);
  iVar1 = *(int *)(param_1 + 0x1ec);
  iVar2 = 0;
  if (0 < *(int *)(iVar1 + 0xe4)) {
    do {
      iVar1 = (**(code **)(**(int **)(*(int *)(iVar1 + 0xe8) + iVar2 * 4) + 4))(param_2);
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = *(int *)(param_1 + 0x1ec);
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(iVar1 + 0xe4));
  }
  return 1;
}

