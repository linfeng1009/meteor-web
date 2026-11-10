/* Original Meteor.exe static export @ 004deda0; original sample not executed. */
/* XREF 005aac64 DATA */

undefined4 FUN_004deda0(int param_1,undefined4 param_2)

{
  int extraout_EDX;
  
  FUN_004dd130(param_1,param_2);
  if ((extraout_EDX != 0x3a) && (extraout_EDX != 0x92)) {
    *(undefined4 *)(param_1 + 0x370) = 1;
  }
  return 0;
}

