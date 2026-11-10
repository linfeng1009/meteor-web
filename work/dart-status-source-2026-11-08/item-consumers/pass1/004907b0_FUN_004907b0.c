/* Original Meteor.exe static read-only export; sample not executed. */

void __fastcall FUN_004907b0(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1[0x8bb] + 8);
  if (iVar3 != param_1[0x8bb]) {
    do {
      iVar2 = (**(code **)(*param_1 + 300))(*(undefined4 *)(iVar3 + 0x10));
      if ((iVar2 != 0) && (iVar2 != 0x65c)) {
        FUN_0055e050();
      }
      *(undefined4 *)(iVar3 + 0x200) = 1;
      *(undefined4 *)(iVar3 + 0x210) = 1;
      (**(code **)(*(int *)(iVar3 + 0x88) + 0xc))(1,0x3f800000);
      FUN_00549a90(0,0);
      iVar2 = *(int *)(iVar3 + 0xc);
      if (iVar2 == 0) {
        iVar2 = *(int *)(iVar3 + 4);
        if (iVar3 == *(int *)(iVar2 + 0xc)) {
          do {
            iVar3 = iVar2;
            iVar2 = *(int *)(iVar3 + 4);
          } while (iVar3 == *(int *)(iVar2 + 0xc));
        }
        if (*(int *)(iVar3 + 0xc) != iVar2) {
          iVar3 = iVar2;
        }
      }
      else {
        for (iVar1 = *(int *)(iVar2 + 8); iVar3 = iVar2, iVar1 != 0; iVar1 = *(int *)(iVar1 + 8)) {
          iVar2 = iVar1;
        }
      }
    } while (iVar3 != param_1[0x8bb]);
  }
  return;
}

