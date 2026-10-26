/* Original Meteor.exe static export @ 0053dd90; original sample not executed. */
/* XREF 0053b727 UNCONDITIONAL_CALL */

int FUN_0053dd90(int *param_1,char param_2)

{
  int iVar1;
  
  if ((param_1[5] != 200) && (param_1[5] != 0xc9)) {
    *(undefined4 *)(*param_1 + 0x14) = 0x14;
    *(int *)(*param_1 + 0x18) = param_1[5];
    (**(code **)*param_1)(param_1);
  }
  iVar1 = FUN_0053de00(param_1);
  if (iVar1 == 1) {
    iVar1 = 1;
  }
  else if (iVar1 == 2) {
    if (param_2 != '\0') {
      *(undefined4 *)(*param_1 + 0x14) = 0x33;
      (**(code **)*param_1)(param_1);
    }
    FUN_0053e2c0(param_1);
    return 2;
  }
  return iVar1;
}

