/* Original Meteor.exe read-only export. Sample not executed. */

undefined4 __fastcall FUN_004d0250(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x130))();
  if ((((iVar1 == 1) || (iVar1 == 4)) || (iVar1 == 3)) || (iVar1 == 0xb)) {
    iVar1 = (**(code **)(*param_1 + 0xc))(0x22,0,0);
    if (iVar1 != 0) {
      iVar1 = (**(code **)(*param_1 + 0xa4))(0x55,4);
      if (iVar1 != 3) {
        param_1[0xd6] = 1;
        (**(code **)(*param_1 + 300))(3);
        (**(code **)(*(int *)param_1[0xd2] + 0x14))(param_1,0x55);
        (**(code **)(*param_1 + 0xc))(0x21,0,0);
      }
    }
  }
  return 0;
}

