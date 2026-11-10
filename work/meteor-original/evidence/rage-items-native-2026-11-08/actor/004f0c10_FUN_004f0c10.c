/* Original Meteor.exe static export @ 004f0c10; original sample not executed. */
/* XREF 005aa020 DATA */
/* XREF 005ab4a8 DATA */
/* XREF 005ab8e8 DATA */
/* XREF 005ab268 DATA */

undefined4 __fastcall FUN_004f0c10(int *param_1)

{
  int iVar1;
  int *piStack_4;
  
  piStack_4 = param_1;
  iVar1 = (**(code **)(*param_1 + 0x44))();
  piStack_4 = *(int **)(iVar1 + 0x524);
  if (piStack_4 != (int *)0x0) {
    FUN_0054a6c0(0x2a,&piStack_4,4,1);
    iVar1 = (**(code **)(*param_1 + 0x44))();
    *(undefined4 *)(iVar1 + 0x524) = 0;
  }
  return 0;
}

