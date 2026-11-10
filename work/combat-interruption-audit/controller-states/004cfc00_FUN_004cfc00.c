/* Original Meteor.exe static export @ 004cfc00; original sample not executed. */
/* XREF 005aa700 DATA */

void __thiscall
FUN_004cfc00(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 *param_5)

{
  undefined4 uStack_4;
  
  uStack_4 = 0x3df5c28f;
  if (param_2 == 0) {
    uStack_4 = 0x3df5c28f;
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x348) + 0x30))(param_1,param_2,&uStack_4);
  }
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = uStack_4;
  }
  FUN_00559720(uStack_4);
  FUN_004dbf80(param_2,param_3,1,param_4);
  return;
}

