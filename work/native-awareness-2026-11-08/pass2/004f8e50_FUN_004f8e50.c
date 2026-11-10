/* Original Meteor.exe static export @ 004f8e50; original sample not executed. */
/* XREF 004f89dc DATA */

undefined4 FUN_004f8e50(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004c3730(*(undefined4 *)(**(int **)(param_1 + 8) + 8));
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x74) != 0)) {
    return *(undefined4 *)(*(int *)(iVar1 + 0x74) + 8);
  }
  return 0xffffffff;
}

