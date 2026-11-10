/* Original Meteor.exe static export @ 004dd070; original sample not executed. */
/* XREF 005aaaa8 DATA */
/* XREF 005aab30 DATA */
/* XREF 005aaba0 DATA */
/* XREF 005aac10 DATA */
/* XREF 005aac80 DATA */
/* XREF 005aacf0 DATA */
/* XREF 005aad60 DATA */
/* XREF 005aadd0 DATA */
/* XREF 005aae40 DATA */
/* XREF 005aaeb0 DATA */
/* XREF 005aaf20 DATA */
/* XREF 005aafa0 DATA */
/* XREF 005ab018 DATA */

undefined4 __thiscall FUN_004dd070(int param_1,undefined4 param_2,int param_3,undefined4 *param_4)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x1c);
  while( true ) {
    if (piVar1 == *(int **)(param_1 + 0x20)) {
      return 0;
    }
    if (*piVar1 == param_3) break;
    piVar1 = piVar1 + 1;
  }
  *param_4 = 0x3c23d70a;
  return 1;
}

