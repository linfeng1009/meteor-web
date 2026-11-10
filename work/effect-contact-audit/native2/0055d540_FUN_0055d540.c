/* Original Meteor.exe static export @ 0055d540; original sample not executed. */
/* XREF 0055ddd3 UNCONDITIONAL_CALL */
/* XREF 004f33b7 UNCONDITIONAL_CALL */
/* XREF 0056553f UNCONDITIONAL_CALL */
/* XREF 0055dc29 UNCONDITIONAL_CALL */
/* XREF 0055da59 UNCONDITIONAL_CALL */

bool __fastcall FUN_0055d540(int param_1)

{
  char *pcVar1;
  
  pcVar1 = (char *)FUN_0055c4f0(*(undefined4 *)(param_1 + 0xfc));
  if (pcVar1 == (char *)0x0) {
    return false;
  }
  return *pcVar1 != -1;
}

