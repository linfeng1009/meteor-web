/* Original Meteor.exe read-only motion producer export; sample not executed. */

undefined4 __thiscall FUN_005570e0(int *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_00477200();
  if ((*(int *)(param_2 + 0xc) == param_1[7]) && (*(int *)(param_2 + 0x10) == param_1[8])) {
    iVar1 = 0;
    iVar3 = *(int *)(param_2 + 4);
    if (param_3 == 0) {
      param_1[10] = iVar3;
      param_1[0x4b] = 0;
      param_1[0x4c] = iVar3 + -1;
      param_1[0xe] = *(int *)(param_2 + 8);
    }
    else {
      param_1[0xb] = iVar3;
    }
    if (0 < param_1[7]) {
      iVar3 = 0;
      do {
        uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x14) + iVar1 * 4);
        if (param_3 == 0) {
          *(undefined4 *)(iVar3 + 0x304 + param_1[0xd4]) = uVar2;
        }
        else {
          *(undefined4 *)(iVar3 + 0x308 + param_1[0xd4]) = uVar2;
        }
        iVar1 = iVar1 + 1;
        iVar3 = iVar3 + 0x334;
      } while (iVar1 < param_1[7]);
    }
    iVar3 = 0;
    if (0 < param_1[8]) {
      iVar1 = 0;
      do {
        uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x18) + iVar3 * 4);
        if (param_3 == 0) {
          *(undefined4 *)(iVar1 + 0x7c + param_1[0xd5]) = uVar2;
        }
        else {
          *(undefined4 *)(iVar1 + 0x80 + param_1[0xd5]) = uVar2;
        }
        iVar3 = iVar3 + 1;
        iVar1 = iVar1 + 0x2f0;
      } while (iVar3 < param_1[8]);
    }
    if (param_3 == 0) {
      uVar2 = 0;
      param_1[0x12] = 1;
    }
    else {
      uVar2 = 50000;
      param_1[0x13] = 1;
    }
    (**(code **)(*param_1 + 0x14))(uVar2);
    if ((param_1[0x11] != 0) && (param_1[0x10] != 0)) {
      FUN_00558600();
    }
    return 1;
  }
  return 0;
}


