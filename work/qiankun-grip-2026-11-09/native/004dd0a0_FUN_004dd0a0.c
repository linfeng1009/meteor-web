/* Original Meteor.exe static export @ 004dd0a0; original sample not executed. */
/* XREF 005aaab0 DATA */
/* XREF 005aab38 DATA */
/* XREF 005aaba8 DATA */
/* XREF 005aac18 DATA */
/* XREF 005aacf8 DATA */
/* XREF 005aadd8 DATA */
/* XREF 005aae48 DATA */
/* XREF 005aaeb8 DATA */
/* XREF 005aafa8 DATA */
/* XREF 005ab020 DATA */
/* XREF 004dedd7 UNCONDITIONAL_CALL */
/* XREF 004e2a87 UNCONDITIONAL_CALL */
/* XREF 004e2a9d UNCONDITIONAL_CALL */

undefined4 FUN_004dd0a0(int *param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_0055de50();
  if ((cVar1 == '\0') || (param_1[0xd8] == 0)) {
    iVar2 = FUN_0055c300();
    if (iVar2 == 4) {
      (**(code **)(*param_1 + 300))(1);
      return 1;
    }
  }
  else {
    FUN_0055de20();
  }
  return 0;
}

