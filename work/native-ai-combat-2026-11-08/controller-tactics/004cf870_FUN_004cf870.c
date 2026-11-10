/* Original Meteor.exe static export @ 004cf870; original sample not executed. */
/* XREF 005aa7b8 DATA */

int __fastcall FUN_004cf870(int param_1)

{
  int iVar1;
  
  if (*(int **)(param_1 + 0x348) != (int *)0x0) {
    iVar1 = (**(code **)(**(int **)(param_1 + 0x348) + 0x5c))(param_1);
    if (iVar1 != 0) {
      return iVar1;
    }
    if (((*(int *)(param_1 + 0x10) != 0) && (*(int *)(param_1 + 0x10) != 0x65c)) &&
       ((iVar1 = FUN_0055c4e0(), iVar1 == 0x70 || ((iVar1 == 0x71 || (iVar1 == 0x75)))))) {
      return 1;
    }
  }
  return 0;
}

