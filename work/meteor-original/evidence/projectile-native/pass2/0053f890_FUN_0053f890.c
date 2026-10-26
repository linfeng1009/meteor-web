/* Original Meteor.exe static export @ 0053f890; original sample not executed. */
/* XREF 0053fb8e UNCONDITIONAL_CALL */

void FUN_0053f890(int *param_1)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  
  piVar3 = param_1;
  if (param_1[5] != 0xca) {
    *(undefined4 *)(*param_1 + 0x14) = 0x14;
    *(int *)(*param_1 + 0x18) = param_1[5];
    (**(code **)*param_1)(param_1);
  }
  iVar5 = param_1[0xc];
  uVar2 = param_1[0xd];
  if ((uint)(iVar5 * 8) < uVar2 || iVar5 * 8 - uVar2 == 0) {
    iVar5 = FUN_0053e5b0(param_1[7],8);
    param_1[0x17] = iVar5;
    iVar5 = FUN_0053e5b0(param_1[8],8);
    param_1[0x46] = 1;
  }
  else if ((uint)(iVar5 * 4) < uVar2 || iVar5 * 4 - uVar2 == 0) {
    iVar5 = FUN_0053e5b0(param_1[7],4);
    param_1[0x17] = iVar5;
    iVar5 = FUN_0053e5b0(param_1[8],4);
    param_1[0x46] = 2;
  }
  else if (uVar2 < (uint)(iVar5 * 2)) {
    iVar5 = param_1[8];
    param_1[0x17] = param_1[7];
    param_1[0x46] = 8;
  }
  else {
    iVar5 = FUN_0053e5b0(param_1[7],2);
    param_1[0x17] = iVar5;
    iVar5 = FUN_0053e5b0(param_1[8],2);
    param_1[0x46] = 4;
  }
  piVar1 = param_1 + 0x31;
  param_1[0x18] = iVar5;
  piVar7 = param_1 + 9;
  param_1 = (int *)0x0;
  if (0 < *piVar7) {
    piVar7 = (int *)(*piVar1 + 0xc);
    do {
      iVar5 = piVar3[0x46];
      iVar6 = iVar5;
      if (iVar5 < 8) {
        do {
          if ((piVar3[0x44] * iVar5 < piVar7[-1] * iVar6 * 2) ||
             (piVar3[0x45] * iVar5 < *piVar7 * iVar6 * 2)) break;
          iVar6 = iVar6 * 2;
        } while (iVar6 < 8);
      }
      piVar7[6] = iVar6;
      param_1 = (int *)((int)param_1 + 1);
      piVar7 = piVar7 + 0x15;
    } while ((int)param_1 < piVar3[9]);
  }
  iVar5 = 0;
  if (0 < piVar3[9]) {
    piVar7 = (int *)(piVar3[0x31] + 0x24);
    do {
      iVar6 = FUN_0053e5b0(piVar7[-7] * *piVar7 * piVar3[7],piVar3[0x44] << 3);
      piVar7[1] = iVar6;
      iVar6 = FUN_0053e5b0(piVar7[-6] * piVar3[8] * *piVar7,piVar3[0x45] << 3);
      piVar7[2] = iVar6;
      iVar5 = iVar5 + 1;
      piVar7 = piVar7 + 0x15;
    } while (iVar5 < piVar3[9]);
  }
  switch(piVar3[0xb]) {
  case 1:
    piVar3[0x19] = 1;
    break;
  case 2:
  case 3:
    piVar3[0x19] = 3;
    break;
  case 4:
  case 5:
    piVar3[0x19] = 4;
    break;
  default:
    piVar3[0x19] = piVar3[9];
  }
  iVar5 = 1;
  if (*(char *)((int)piVar3 + 0x4a) == '\0') {
    iVar5 = piVar3[0x19];
  }
  piVar3[0x1a] = iVar5;
  cVar4 = FUN_0053fab0(piVar3);
  if (cVar4 == '\0') {
    piVar3[0x1b] = 1;
    return;
  }
  piVar3[0x1b] = piVar3[0x45];
  return;
}

