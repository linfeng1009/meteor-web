/* Original Meteor.exe static export @ 004a9770; original sample not executed. */
/* XREF 005a9034 DATA */
/* XREF 005a9074 DATA */
/* XREF 005a97cc DATA */
/* XREF 005a959c DATA */
/* XREF 005a981c DATA */
/* XREF 005a986c DATA */
/* XREF 005a98b4 DATA */
/* XREF 005a9b44 DATA */
/* XREF 005a9b80 DATA */
/* XREF 005a9c04 DATA */
/* XREF 005a9d94 DATA */
/* XREF 005a9ee4 DATA */
/* XREF 005a9f54 DATA */
/* XREF 005a9fec DATA */
/* XREF 005aa374 DATA */
/* XREF 005aa4cc DATA */
/* XREF 005aa600 DATA */
/* XREF 005aa6b4 DATA */
/* XREF 005a953c DATA */
/* XREF 005ab114 DATA */
/* XREF 005ab0b4 DATA */
/* XREF 005ab474 DATA */
/* XREF 005ab67c DATA */
/* XREF 005ab6cc DATA */
/* XREF 005ab71c DATA */
/* XREF 005ab7b4 DATA */
/* XREF 005ab8b4 DATA */
/* XREF 005aba64 DATA */
/* XREF 005ababc DATA */
/* XREF 005a9604 DATA */
/* XREF 005ab234 DATA */

undefined4 __fastcall FUN_004a9770(int param_1)

{
  undefined4 uVar1;
  
  if (*(int **)(param_1 + 0xc) != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x004a9779. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x20))();
    return uVar1;
  }
  return 0xffffffff;
}

