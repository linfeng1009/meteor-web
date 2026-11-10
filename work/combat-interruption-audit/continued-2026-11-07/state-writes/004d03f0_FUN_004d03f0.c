/* Original Meteor.exe static export; sample not executed. */
/* XREF 005aa6f0 DATA */

undefined4 __thiscall
FUN_004d03f0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = (**(code **)(*param_1 + 0x130))();
  if ((iVar1 != 7) && (iVar1 != 9)) {
    iVar1 = 0;
    (**(code **)(*param_1 + 0x74))(param_2,param_4,0,param_5);
    (**(code **)(*param_1 + 300))(4);
    param_1[0xe0] = unaff_ESI;
    param_1[0xdf] = iVar1;
    FUN_00549a90(0,0);
    param_1[0xee] = param_1[0xe4];
    param_1[0x149] = 0;
    param_1[0xef] = param_1[0xe5];
    param_1[0xf0] = param_1[0xe6];
    (**(code **)(*param_1 + 0xc))(0x35,0,0);
    return 1;
  }
  return 0;
}

