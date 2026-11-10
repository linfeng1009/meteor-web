/* Original Meteor.exe static export @ 004cfca0; original sample not executed. */
/* XREF 005aa6e8 DATA */

void __thiscall FUN_004cfca0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(int **)(param_1 + 0x10) != (int *)0x0) {
    *(undefined4 *)(param_1 + 0x390) = 0;
    *(undefined4 *)(param_1 + 0x394) = 0;
    *(undefined4 *)(param_1 + 0x398) = 0;
    (**(code **)(**(int **)(param_1 + 0x10) + 0x80))(param_2,param_3,param_4,0);
  }
  return;
}

