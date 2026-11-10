/* Original Meteor.exe static export @ 0055ddd0; original sample not executed. */
/* XREF 004d0897 UNCONDITIONAL_CALL */
/* XREF 004d0c1b UNCONDITIONAL_CALL */
/* XREF 004dedf5 UNCONDITIONAL_CALL */
/* XREF 004f3aea UNCONDITIONAL_CALL */

int __fastcall FUN_0055ddd0(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = FUN_0055d540();
  if (iVar1 == 0) {
    return 0;
  }
  pcVar2 = (char *)FUN_0055c4f0(*(undefined4 *)(param_1 + 0xfc));
  return *(int *)(*(int *)(param_1 + 0x638) + 0x94) + *pcVar2 * 0x68;
}

