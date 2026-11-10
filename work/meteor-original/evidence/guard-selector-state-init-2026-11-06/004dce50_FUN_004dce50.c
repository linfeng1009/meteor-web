/* Original Meteor.exe static export @ 004dce50; original sample not executed. */
/* XREF 005aaae0 DATA */
/* XREF 005aab68 DATA */
/* XREF 005aabd8 DATA */
/* XREF 005aac48 DATA */
/* XREF 005aacb8 DATA */
/* XREF 005aad28 DATA */
/* XREF 005aad98 DATA */
/* XREF 005aae08 DATA */
/* XREF 005aae78 DATA */
/* XREF 005aaee8 DATA */
/* XREF 005aafd8 DATA */
/* XREF 005ab050 DATA */
/* XREF 004e2ba0 UNCONDITIONAL_CALL */

undefined4 __thiscall
FUN_004dce50(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  
  if (0x1b < (int)(*(int *)(param_1 + 0x20) - *(int *)(param_1 + 0x1c) & 0xfffffffcU)) {
    switch(param_3) {
    case 0:
      _rand();
      iVar1 = __ftol();
      *param_4 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + iVar1 * 4);
      return 1;
    case 1:
      *param_4 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x10);
      return 1;
    case 2:
      *param_4 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x14);
      return 1;
    case 3:
      *param_4 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x18);
      return 1;
    default:
      *param_4 = 0;
      return 1;
    }
  }
  return 0;
}

