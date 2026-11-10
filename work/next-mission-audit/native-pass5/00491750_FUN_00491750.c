/* Original Meteor.exe static export @ 00491750; original sample not executed. */
/* XREF 005a9284 DATA */

undefined4 __thiscall FUN_00491750(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int unaff_EBX;
  char *pcVar4;
  
  iVar1 = (**(code **)(*param_1 + 300))(param_3);
  if ((iVar1 == 0) || (iVar1 + -0x65c == 0)) {
    return 0;
  }
  iVar2 = (**(code **)(*param_1 + 0x14c))(param_3);
  if (iVar2 != 0) {
    *(undefined1 *)(iVar2 + 0x210) = 2;
  }
  if (unaff_EBX == 1) {
    piVar3 = (int *)FUN_004db420();
    pcVar4 = s_VipBlue_005c92bc;
  }
  else {
    if (unaff_EBX != 2) {
      return 0;
    }
    piVar3 = (int *)FUN_004db420();
    pcVar4 = s_VipRed_005c92c4;
  }
  iVar1 = (**(code **)(*piVar3 + 4))(pcVar4,iVar1 + -0x65c);
  if (iVar1 == 0) {
    return 0;
  }
  FUN_00566200(1);
  return 1;
}

