/* Original Meteor.exe static read-only export; sample not executed. */

undefined4 __thiscall FUN_004d4e30(int param_1,undefined4 param_2,int param_3,int param_4)

{
  uint *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  uint uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_c;
  int iStack_8;
  undefined4 uStack_4;
  
  iVar5 = param_3;
  iVar8 = 0;
  iVar7 = *(int *)(param_3 + 0x40) - *(int *)(param_3 + 0x3c);
  iVar2 = iVar7 >> 0x1f;
  uStack_28 = 0;
  uStack_2c = 0;
  if (iVar7 / 0x28 + iVar2 != iVar2) {
    do {
      iVar2 = *(int *)(iVar5 + 0x3c);
      if (((-1 < *(int *)(iVar8 + 0x10 + iVar2)) || (*(int *)(iVar8 + 0xc + iVar2) != 0)) &&
         ((*(byte *)(iVar8 + iVar2) & 2) != 0)) {
        puVar1 = (uint *)(iVar8 + 0x24 + iVar2);
        if (*puVar1 < (uint)(*(int *)(iVar8 + 0xc + iVar2) * 10)) {
          uVar6 = __ftol();
          *puVar1 = uVar6;
        }
        else {
          piVar9 = *(int **)(param_1 + 0x30);
          piVar3 = *(int **)(param_1 + 0x34);
          if (piVar9 == piVar3) {
            return 0xffffffff;
          }
          do {
            if (*piVar9 == *(int *)(iVar8 + 8 + iVar2)) break;
            piVar9 = piVar9 + 3;
          } while (piVar9 != piVar3);
          if (piVar9 == piVar3) {
            return 0xffffffff;
          }
          if (piVar9 == (int *)0x0) {
            return 0xffffffff;
          }
          iVar7 = *(int *)(iVar8 + 0x14 + iVar2);
          if (iVar7 == 0) {
            param_3 = *(int *)(iVar8 + 0x18 + iVar2);
          }
          else {
            if (iVar7 != 1) {
              return 0xffffffff;
            }
            param_3 = __ftol();
          }
          FUN_004d4d30(*(undefined4 *)(iVar8 + 8 + iVar2),param_3,&param_3);
          piVar9[1] = piVar9[1] + param_3;
          *(undefined4 *)(iVar8 + 0x24 + *(int *)(iVar5 + 0x3c)) = 0;
          if (param_4 != 0) {
            uStack_4 = 0;
            uStack_c = *(undefined4 *)(iVar8 + 8 + *(int *)(iVar5 + 0x3c));
            iStack_8 = param_3;
            puVar4 = *(undefined4 **)(param_4 + 4);
            if (puVar4 != *(undefined4 **)(param_4 + 8)) {
              if (puVar4 != (undefined4 *)0x0) {
                *puVar4 = uStack_c;
                puVar4[1] = param_3;
                puVar4[2] = 0;
              }
              uStack_28 = 1;
              *(int *)(param_4 + 4) = *(int *)(param_4 + 4) + 0xc;
              goto LAB_004d4fd3;
            }
            FUN_004d6b20(puVar4,&uStack_c);
          }
          uStack_28 = 1;
        }
      }
LAB_004d4fd3:
      iVar8 = iVar8 + 0x28;
      uStack_2c = uStack_2c + 1;
    } while (uStack_2c < (uint)((*(int *)(iVar5 + 0x40) - *(int *)(iVar5 + 0x3c)) / 0x28));
  }
  return uStack_28;
}

