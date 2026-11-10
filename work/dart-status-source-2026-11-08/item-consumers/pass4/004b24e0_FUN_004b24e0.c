/* Original Meteor.exe static read-only export; sample not executed. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004b24e0(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  
  iVar3 = *(int *)(param_1[0xea] + 8);
  if (iVar3 != param_1[0xea]) {
    do {
      (**(code **)(*(int *)(iVar3 + 0x88) + 4))(param_2,0,0);
      if (((*(int *)(iVar3 + 0x200) == 2) && (iVar2 = (**(code **)(*param_1 + 0xf0))(), iVar2 != 0))
         && (fVar4 = (float10)FUN_00549b00(), (float10)_DAT_005a9bd0 < fVar4)) {
        (**(code **)(*param_1 + 0xec))(*(undefined4 *)(iVar3 + 0x10));
      }
      (**(code **)(*param_1 + 200))(iVar3 + 0x18,*(undefined4 *)(iVar3 + 0x10));
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
    } while (iVar3 != param_1[0xea]);
  }
  return;
}

