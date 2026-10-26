/* Original Meteor.exe static export @ 0053e360; original sample not executed. */
/* XREF 0053b796 UNCONDITIONAL_CALL */

undefined4 FUN_0053e360(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1[5] == 0xca) {
    FUN_0053fb40(param_1);
    if ((char)param_1[0x10] != '\0') {
      param_1[5] = 0xcf;
      return 1;
    }
    param_1[5] = 0xcb;
  }
  if (param_1[5] == 0xcb) {
    if (*(char *)(param_1[100] + 0x10) != '\0') {
      while( true ) {
        if ((undefined4 *)param_1[2] != (undefined4 *)0x0) {
          (**(code **)param_1[2])(param_1);
        }
        iVar2 = (**(code **)param_1[100])(param_1);
        if (iVar2 == 0) {
          return 0;
        }
        if (iVar2 == 2) break;
        iVar1 = param_1[2];
        if ((iVar1 != 0) && ((iVar2 == 3 || (iVar2 == 1)))) {
          *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + 1;
          iVar2 = param_1[2];
          if (*(int *)(iVar2 + 8) <= *(int *)(iVar2 + 4)) {
            *(int *)(iVar2 + 8) = param_1[0x47] + *(int *)(iVar2 + 8);
          }
        }
      }
    }
    param_1[0x21] = param_1[0x1f];
    uVar3 = FUN_0053e440(param_1);
    return uVar3;
  }
  if (param_1[5] != 0xcc) {
    *(undefined4 *)(*param_1 + 0x14) = 0x14;
    *(int *)(*param_1 + 0x18) = param_1[5];
    (**(code **)*param_1)(param_1);
  }
  uVar3 = FUN_0053e440(param_1);
  return uVar3;
}

