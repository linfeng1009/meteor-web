/* Original Meteor.exe static export @ 0053fb80; original sample not executed. */
/* XREF 0053fb67 UNCONDITIONAL_CALL */

void FUN_0053fb80(int *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined1 uVar4;
  int iVar5;
  
  piVar3 = param_1;
  iVar2 = param_1[0x60];
  FUN_0053f890(param_1);
  FUN_0053fd60(param_1);
  *(undefined4 *)(iVar2 + 0xc) = 0;
  uVar4 = FUN_0053fab0(param_1);
  *(undefined1 *)(iVar2 + 0x10) = uVar4;
  *(undefined4 *)(iVar2 + 0x14) = 0;
  *(undefined4 *)(iVar2 + 0x18) = 0;
  if ((*(char *)((int)param_1 + 0x4a) == '\0') || ((char)param_1[0x10] == '\0')) {
    *(undefined1 *)(param_1 + 0x16) = 0;
    *(undefined1 *)((int)param_1 + 0x59) = 0;
    *(undefined1 *)((int)param_1 + 0x5a) = 0;
  }
  if (*(char *)((int)param_1 + 0x4a) == '\0') goto LAB_0053fc25;
  if (*(char *)((int)param_1 + 0x41) != '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 0x2f;
    (**(code **)*param_1)(param_1);
  }
  if (param_1[0x19] == 3) {
    if (param_1[0x1d] == 0) {
      if ((char)param_1[0x14] == '\0') goto LAB_0053fbee;
      *(undefined1 *)((int)param_1 + 0x5a) = 1;
    }
    else {
      *(undefined1 *)((int)param_1 + 0x59) = 1;
    }
  }
  else {
    *(undefined1 *)((int)param_1 + 0x59) = 0;
    *(undefined1 *)((int)param_1 + 0x5a) = 0;
    param_1[0x1d] = 0;
LAB_0053fbee:
    *(undefined1 *)(param_1 + 0x16) = 1;
  }
  if ((char)param_1[0x16] != '\0') {
    FUN_00545a70(param_1);
    *(int *)(iVar2 + 0x14) = param_1[0x6a];
  }
  if ((*(char *)((int)param_1 + 0x5a) != '\0') || (*(char *)((int)param_1 + 0x59) != '\0')) {
    FUN_00544720(param_1);
    *(int *)(iVar2 + 0x18) = param_1[0x6a];
  }
LAB_0053fc25:
  if (*(char *)((int)param_1 + 0x41) == '\0') {
    if (*(char *)(iVar2 + 0x10) == '\0') {
      FUN_00543ad0(param_1);
      FUN_005433c0(param_1);
    }
    else {
      FUN_00544130();
    }
    FUN_00543050(param_1,*(undefined1 *)((int)param_1 + 0x5a));
  }
  FUN_00542db0(param_1);
  if (*(char *)((int)param_1 + 0xc9) == '\0') {
    if ((char)param_1[0x32] == '\0') {
      FUN_00541a80(param_1);
    }
    else {
      FUN_005420d0();
    }
  }
  else {
    *(undefined4 *)(*param_1 + 0x14) = 1;
    (**(code **)*param_1)();
  }
  if ((*(char *)(param_1[100] + 0x10) != '\0') ||
     (piVar1 = param_1 + 0x10, param_1 = (int *)0x0, (char)*piVar1 != '\0')) {
    param_1 = (int *)0x1;
  }
  FUN_00540670(piVar3,param_1);
  if (*(char *)((int)piVar3 + 0x41) == '\0') {
    FUN_0053ffc0(piVar3,0);
  }
  (**(code **)(piVar3[1] + 0x18))(piVar3);
  (**(code **)(piVar3[100] + 8))(piVar3);
  if (((piVar3[2] != 0) && ((char)piVar3[0x10] == '\0')) && (*(char *)(piVar3[100] + 0x10) != '\0'))
  {
    iVar5 = piVar3[9];
    if ((char)piVar3[0x32] != '\0') {
      iVar5 = iVar5 * 3 + 2;
    }
    *(undefined4 *)(piVar3[2] + 4) = 0;
    *(int *)(piVar3[2] + 8) = piVar3[0x47] * iVar5;
    *(undefined4 *)(piVar3[2] + 0xc) = 0;
    *(uint *)(piVar3[2] + 0x10) = (*(char *)((int)piVar3 + 0x5a) != '\0') + 2;
    *(int *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc) + 1;
  }
  return;
}

