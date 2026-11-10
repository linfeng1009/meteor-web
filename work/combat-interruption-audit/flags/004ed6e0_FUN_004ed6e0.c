/* Original Meteor.exe static export @ 004ed6e0; original sample not executed. */

undefined4 __fastcall FUN_004ed6e0(int *param_1)

{
  if (param_1[0xc1] != 0) {
    (**(code **)(*param_1 + 0x8c))(param_1[0xda],param_1[0xdb]);
    (**(code **)(*param_1 + 0xa8))(param_1[0xdc],1);
    (**(code **)(*param_1 + 0xb0))(param_1[0xdd]);
    (**(code **)(*param_1 + 0x130))(param_1[0xdb],0xffffffff);
    param_1[0xc1] = 0;
    return 1;
  }
  return 0;
}

