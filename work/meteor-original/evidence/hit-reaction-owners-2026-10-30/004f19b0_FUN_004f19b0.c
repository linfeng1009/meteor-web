/* Original Meteor.exe static export @ 004f19b0; original sample not executed. */
/* XREF 005ab534 DATA */
/* XREF 005ab974 DATA */
/* XREF 004bc239 UNCONDITIONAL_CALL */
/* XREF 005ab2f4 DATA */

undefined4 __thiscall FUN_004f19b0(int param_1,int param_2)

{
  int iVar1;
  
  if (*(int **)(param_1 + 0x1a4) != (int *)0x0) {
    iVar1 = **(int **)(param_1 + 0x1a4);
    if (param_2 != 0) {
      (**(code **)(iVar1 + 0x4c))(*(undefined4 *)(param_2 + 0x850));
      return 0;
    }
    (**(code **)(iVar1 + 0x4c))(0);
  }
  return 0;
}

