/* Original Meteor.exe static read-only export; sample not executed. */

undefined4 __thiscall FUN_004d59d0(int param_1,uint param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int *piStack_2c;
  undefined4 *puStack_28;
  
  iVar2 = param_2;
  iVar3 = *(int *)(param_2 + 0x2c);
  if (iVar3 == 1) {
    piStack_2c = *(int **)(param_1 + 0x40);
    piVar4 = (int *)(param_1 + 0x40);
    puStack_28 = &param_2;
    param_2 = 0;
    FUN_0046ef50(*piStack_2c);
    if (1 < param_2) {
      return 0;
    }
    piStack_2c = (int *)*piVar4;
    piVar6 = (int *)*piStack_2c;
    if (piVar6 != piStack_2c) {
      do {
        if (*(int *)(iVar2 + 0x28) == piVar6[0xc]) {
          return 0;
        }
        piVar6 = (int *)*piVar6;
      } while (piVar6 != piStack_2c);
    }
    puStack_28 = (undefined4 *)iVar2;
    FUN_004db820(&piStack_2c);
    FUN_004d6ae0(&param_2);
    piStack_2c = (int *)*piVar4;
    puStack_28 = &param_2;
    param_2 = 0;
    FUN_0046ef50(*piStack_2c);
    if (param_3 != (int *)0x0) {
      *param_3 = *(int *)(*piVar4 + 4) + 8;
    }
  }
  else if (iVar3 == 2) {
    piVar4 = *(int **)(param_1 + 0x50);
    piVar6 = (int *)*piVar4;
    if (piVar6 != piVar4) {
      do {
        if ((piVar6[0xc] == *(int *)(param_2 + 0x28)) && (piVar6[0xd] == 2)) {
          piVar4 = (int *)piVar6[0xe];
          piVar5 = (int *)piVar6[0xf];
          if (piVar4 == piVar5) {
            return 0;
          }
          goto LAB_004d5b05;
        }
        piVar6 = (int *)*piVar6;
      } while (piVar6 != piVar4);
    }
    piVar4 = *(int **)(param_2 + 0x30);
    piVar6 = *(int **)(param_2 + 0x34);
    if (piVar4 != piVar6) {
      do {
        if (*piVar4 == 1) break;
        piVar4 = piVar4 + 3;
      } while (piVar4 != piVar6);
      if (((piVar4 != piVar6) && (piVar4 != (int *)0x0)) && ((int *)piVar4[1] != (int *)0x0)) {
        puStack_28 = (undefined4 *)param_2;
        piStack_2c = (int *)piVar4[1];
        FUN_004db820(&piStack_2c);
        FUN_004d6ae0(&param_2);
        if (param_3 == (int *)0x0) {
          return 1;
        }
        *param_3 = *(int *)(*(int *)(param_1 + 0x50) + 4) + 8;
        return 1;
      }
    }
    iVar7 = *(int *)(param_2 + 0x40) - *(int *)(param_2 + 0x3c);
    iVar3 = iVar7 >> 0x1f;
    iVar8 = 0;
    param_2 = 0;
    if (iVar7 / 0x28 + iVar3 != iVar3) {
      do {
        iVar3 = *(int *)(iVar2 + 0x3c);
        if ((-1 < *(int *)(iVar8 + 0x10 + iVar3)) && ((*(byte *)(iVar8 + iVar3) & 2) != 0)) {
          piVar4 = *(int **)(param_1 + 0x30);
          piVar6 = *(int **)(param_1 + 0x34);
          if (piVar4 == piVar6) {
            return 0xffffffff;
          }
          do {
            if (*piVar4 == *(int *)(iVar8 + 8 + iVar3)) break;
            piVar4 = piVar4 + 3;
          } while (piVar4 != piVar6);
          if (piVar4 == piVar6) {
            return 0xffffffff;
          }
          if (piVar4 == (int *)0x0) {
            return 0xffffffff;
          }
          iVar7 = *(int *)(iVar8 + 0x14 + iVar3);
          if (iVar7 == 0) {
            param_3 = *(int **)(iVar8 + 0x18 + iVar3);
          }
          else {
            if (iVar7 != 1) {
              return 0xffffffff;
            }
            puStack_28 = (undefined4 *)0x4d5c20;
            param_3 = (int *)__ftol();
          }
          puStack_28 = &param_3;
          piStack_2c = param_3;
          FUN_004d4d30(*(undefined4 *)(iVar8 + 8 + iVar3));
          piVar4[1] = piVar4[1] + (int)param_3;
        }
        iVar8 = iVar8 + 0x28;
        param_2 = param_2 + 1;
        if ((uint)((*(int *)(iVar2 + 0x40) - *(int *)(iVar2 + 0x3c)) / 0x28) <= param_2) {
          return 1;
        }
      } while( true );
    }
  }
  else {
    if (iVar3 != 4) {
      return 0;
    }
    iVar3 = *(int *)(param_1 + 0x44);
    if (iVar3 != *(int *)(param_1 + 0x48)) {
      do {
        if (*(int *)(param_2 + 0x28) == *(int *)(iVar3 + 0x28)) {
          return 0;
        }
        iVar3 = iVar3 + 0x48;
      } while (iVar3 != *(int *)(param_1 + 0x48));
    }
    piStack_2c = *(int **)(param_1 + 0x48);
    puStack_28 = (undefined4 *)param_2;
    if (piStack_2c == *(int **)(param_1 + 0x4c)) {
      FUN_004d3690();
    }
    else {
      FUN_004d6e60();
      *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 0x48;
    }
    if (param_3 != (int *)0x0) {
      *param_3 = *(int *)(param_1 + 0x48) + -0x48;
      return 1;
    }
  }
  return 1;
  while (piVar4 = piVar4 + 3, piVar4 != piVar5) {
LAB_004d5b05:
    if (*piVar4 == 2) break;
  }
  if ((piVar4 != piVar5) && (piVar4 != (int *)0x0)) {
    piVar5 = *(int **)(param_2 + 0x30);
    piVar1 = *(int **)(param_2 + 0x34);
    if (piVar5 != piVar1) {
      do {
        if (*piVar5 == 2) break;
        piVar5 = piVar5 + 3;
      } while (piVar5 != piVar1);
      if ((piVar5 != piVar1) && (piVar5 != (int *)0x0)) {
        piVar4[1] = piVar5[1];
        piVar4[2] = piVar5[2];
        if (param_3 != (int *)0x0) {
          *param_3 = (int)(piVar6 + 2);
        }
        return 2;
      }
    }
  }
  return 0;
}

