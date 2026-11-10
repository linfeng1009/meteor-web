/* Original Meteor.exe static export @ 004eca2d; original sample not executed. */

void __fastcall FUN_004eca2d(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int unaff_EBX;
  uint unaff_EBP;
  int unaff_ESI;
  int in_stack_00000018;
  int in_stack_00000028;
  
  do {
    (**(code **)(param_2 + 0xd8))();
    if (in_stack_00000018 == 6) {
      if (*(int *)(unaff_ESI + 0x208) == 1) {
        *(uint *)(unaff_EBX + 0x58) = *(uint *)(unaff_EBX + 0x58) | 4;
        goto LAB_004eca90;
      }
    }
    else if (in_stack_00000018 == 7) {
      if (*(uint *)(unaff_ESI + 0x208) == unaff_EBP) {
        *(uint *)(unaff_EBX + 0x58) = *(uint *)(unaff_EBX + 0x58) | unaff_EBP;
        goto LAB_004eca90;
      }
    }
    else if (in_stack_00000018 == 8) {
      if (*(int *)(unaff_ESI + 0x208) == 1) {
        *(uint *)(unaff_EBX + 0x58) = *(uint *)(unaff_EBX + 0x58) | 4;
      }
      if (*(uint *)(unaff_ESI + 0x208) == unaff_EBP) {
        *(uint *)(unaff_EBX + 0x58) = *(uint *)(unaff_EBX + 0x58) | unaff_EBP;
      }
LAB_004eca90:
      FUN_005603b0();
    }
    do {
      do {
        iVar2 = *(int *)(unaff_ESI + 0xc);
        if (iVar2 == 0) {
          iVar2 = *(int *)(unaff_ESI + 4);
          if (unaff_ESI == *(int *)(iVar2 + 0xc)) {
            do {
              unaff_ESI = iVar2;
              iVar2 = *(int *)(unaff_ESI + 4);
            } while (unaff_ESI == *(int *)(iVar2 + 0xc));
          }
          if (*(int *)(unaff_ESI + 0xc) != iVar2) {
            unaff_ESI = iVar2;
          }
        }
        else {
          for (iVar3 = *(int *)(iVar2 + 8); unaff_ESI = iVar2, iVar3 != 0;
              iVar3 = *(int *)(iVar3 + 8)) {
            iVar2 = iVar3;
          }
        }
        if (unaff_ESI == *(int *)(in_stack_00000028 + 0x3a8)) {
          return;
        }
      } while ((*(int *)(unaff_ESI + 0x200) != 1) ||
              (iVar3 = *(int *)(unaff_ESI + 0xd0) - *(int *)(unaff_ESI + 0xcc),
              iVar2 = iVar3 >> 0x1f, iVar3 / 0x48 + iVar2 == iVar2));
      piVar1 = (int *)FUN_00487830();
      iVar2 = (**(code **)(*piVar1 + 300))();
    } while ((iVar2 == 0) || (iVar2 == 0x65c));
    piVar1 = (int *)FUN_00487830();
    param_2 = *piVar1;
  } while( true );
}

