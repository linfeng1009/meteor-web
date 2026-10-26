/* Original Meteor.exe static export @ 00565520; original sample not executed. */
/* XREF 004f33f5 UNCONDITIONAL_CALL */

int __thiscall FUN_00565520(int param_1,int param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int local_54;
  undefined1 local_4c [12];
  undefined1 local_40 [64];
  
  piVar3 = param_3;
  if (param_2 == 0) {
    return 0;
  }
  iVar4 = FUN_0055d540();
  if (iVar4 != 0) {
    FUN_00562dd0(param_2 + 0x288,param_2 + 0x294);
    iVar4 = *param_3;
    iVar7 = param_3[1];
    FUN_004a8b00(iVar7,iVar7,iVar4);
    param_3[1] = param_3[1] + (iVar7 - iVar4 >> 2) * -4;
    iVar4 = 0;
    if (0 < *(int *)(param_1 + 0x29c)) {
      do {
        iVar7 = *(int *)(*(int *)(param_1 + 0x2a0) + iVar4 * 4);
        if ((iVar7 != 0) && (uVar6 = 0, *(int *)(iVar7 + 0x50) - *(int *)(iVar7 + 0x4c) >> 2 != 0))
        {
          do {
            iVar5 = *(int *)(*(int *)(iVar7 + 0x4c) + uVar6 * 4);
            if (iVar5 != 0) {
              *(undefined4 *)(iVar5 + 0x24) = 0;
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 < (uint)(*(int *)(iVar7 + 0x50) - *(int *)(iVar7 + 0x4c) >> 2));
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(param_1 + 0x29c));
    }
    local_54 = 0;
    if (0 < *(int *)(param_1 + 0x29c)) {
      do {
        iVar4 = *(int *)(*(int *)(param_1 + 0x2a0) + local_54 * 4);
        if (iVar4 != 0) {
          iVar7 = *(int *)(iVar4 + 0x50) - *(int *)(iVar4 + 0x4c) >> 2;
          param_3 = (int *)0x0;
          if (0 < iVar7) {
            do {
              piVar1 = *(int **)(*(int *)(iVar4 + 0x4c) + (int)param_3 * 4);
              if (((((piVar1 != (int *)0x0) && (piVar1[0xf] != 0)) && ((char)piVar1[2] != '\0')) &&
                  (((char)piVar1[3] != '\0' && ((int *)piVar1[0xb] != (int *)0x0)))) &&
                 ((piVar1[9] != 1 && ((0xb < *piVar1 && (*piVar1 < 0xf)))))) {
                (**(code **)(*(int *)piVar1[0xb] + 4))(local_40,local_4c,0);
                iVar5 = FUN_0055dc20(local_4c,local_40);
                if (iVar5 != 0) {
                  piVar2 = (int *)piVar3[1];
                  if (piVar2 == (int *)piVar3[2]) {
                    FUN_0046ecb0(piVar2,piVar1 + 8);
                  }
                  else {
                    if (piVar2 != (int *)0x0) {
                      *piVar2 = piVar1[8];
                    }
                    piVar3[1] = piVar3[1] + 4;
                  }
                  piVar1[9] = 1;
                }
              }
              param_3 = (int *)((int)param_3 + 1);
            } while ((int)param_3 < iVar7);
          }
        }
        local_54 = local_54 + 1;
      } while (local_54 < *(int *)(param_1 + 0x29c));
    }
    return piVar3[1] - *piVar3 >> 2;
  }
  return 0;
}

