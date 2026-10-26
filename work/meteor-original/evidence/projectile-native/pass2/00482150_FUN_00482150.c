/* Original Meteor.exe static export @ 00482150; original sample not executed. */
/* XREF 0048200b UNCONDITIONAL_CALL */

undefined4 FUN_00482150(undefined4 param_1,undefined4 param_2,int *param_3,int param_4)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *extraout_ECX;
  int *piVar6;
  uint *puVar7;
  uint uVar8;
  uint *puVar9;
  int unaff_EBP;
  int *piVar10;
  int unaff_EDI;
  bool bVar11;
  uint unaff_retaddr;
  undefined4 in_stack_00000028;
  undefined4 in_stack_0000002c;
  undefined *in_stack_00000030;
  undefined **in_stack_00000034;
  uint uStack_28;
  uint uStack_20;
  uint uStack_1c;
  
  FUN_00509ce0();
  in_stack_00000030 = &DAT_005c828c;
  in_stack_00000034 = &PTR_LAB_00464551_1_005c8288;
  extraout_ECX[0xd9ef] = 0;
  extraout_ECX[0xd9f0] = 0;
  extraout_ECX[0xd9f1] = 0;
  extraout_ECX[0xd9f2] = 0;
  in_stack_00000028 = 1;
  in_stack_0000002c = 2;
  iVar3 = (**(code **)(*(int *)extraout_ECX[0xdb14] + 0x10))();
  uVar4 = 0;
  if (iVar3 != 0) {
    do {
      if (4 < uVar4) break;
      piVar2 = (int *)extraout_ECX[0xdb14];
      piVar1 = extraout_ECX + extraout_ECX[0xd9e5] * 0x15ca + 1;
      uStack_1c = 2;
      param_3 = piVar1;
      (**(code **)(*piVar2 + 0x14))();
      (**(code **)(*(int *)extraout_ECX[0xdb14] + 0x20))();
      uVar8 = 0;
      piVar1[0x10f] = 0;
      piVar1[0x15c9] = 0;
      uVar4 = (**(code **)(*(int *)extraout_ECX[0xdb14] + 0x18))();
      uStack_20 = 1;
      uStack_28 = 0;
      if (uVar4 != 0) {
        piVar10 = (int *)&stack0x00000c94;
        do {
          uStack_1c = uVar8;
          if (199 < uStack_28) break;
          (**(code **)(*(int *)extraout_ECX[0xdb14] + 0x1c))();
          uVar5 = 0;
          if (uVar8 != 0) {
            piVar6 = (int *)&stack0x00000c94;
            do {
              if (((piVar6[-1] == 0) && (*piVar6 == unaff_EDI)) && (piVar6[2] == unaff_EBP)) break;
              uVar5 = uVar5 + 1;
              piVar6 = piVar6 + 4;
            } while (uVar5 < uVar8);
          }
          if (uVar5 == uVar8) {
            piVar10[-1] = 0;
            uVar5 = 0;
            *piVar10 = unaff_EDI;
            piVar10[2] = unaff_EBP;
            piVar10[1] = 0;
            uVar8 = uVar8 + 1;
            piVar10 = piVar10 + 4;
            bVar11 = uStack_20 == 0;
            if (uStack_20 != 0) {
              do {
                if (unaff_EBP == *(int *)(&stack0x00000330 + uVar5 * 4)) break;
                uVar5 = uVar5 + 1;
              } while (uVar5 < uStack_20);
              bVar11 = uVar5 == uStack_20;
            }
            if (bVar11) {
              *(int *)(&stack0x00000330 + uStack_20 * 4) = unaff_EBP;
              uStack_20 = uStack_20 + 1;
            }
          }
          uStack_28 = uStack_28 + 1;
          uStack_1c = uVar8;
        } while (uStack_28 < uVar4);
      }
      FUN_0050af1e();
      uStack_28 = 0;
      do {
        piVar10 = piVar1 + piVar1[0x10f] * 0x425 + 0x110;
        *piVar10 = *(int *)(&stack0x00000000 + uStack_28);
        (**(code **)(*(int *)extraout_ECX[0xdb14] + 0x34))();
        uVar4 = 0;
        piVar10[0x36] = *(int *)((int)&param_2 + uStack_28);
        piVar10[0x38] = 0;
        piVar10[0x421] = 0;
        piVar10[0x37] = 0;
        piVar10[0x422] = 0;
        piVar10[0x424] = 0;
        piVar10[0x423] = 0;
        if (uStack_20 != 0) {
          do {
            piVar6 = (int *)extraout_ECX[0xdb14];
            *(undefined4 *)(&stack0x00000970 + uVar4 * 4) = 0;
            iVar3 = *piVar6;
            (&param_4)[uVar4] = 0;
            iVar3 = (**(code **)(iVar3 + 0x24))();
            if (-1 < iVar3) {
              if (((*piVar10 == 1) && (extraout_ECX[0xd9ef] = 1, (piVar10[4] & 0x80000U) != 0)) &&
                 (extraout_ECX[0xd9f0] = 1, uVar4 == 0)) {
                extraout_ECX[0xd9f1] = 1;
              }
              if ((piVar10[8] & 0x10000U) == 0) {
LAB_0048249e:
                if ((&param_4)[uVar4] == 0) {
                  iVar3 = *extraout_ECX;
                  *(undefined4 *)(&stack0x00000650 + uVar4 * 4) = 0x20;
                  iVar3 = (**(code **)(iVar3 + 4))();
                  if (-1 < iVar3) {
                    (&param_4)[uVar4] = 1;
                  }
                  if ((&param_4)[uVar4] == 0) goto LAB_004824fd;
                }
              }
              else {
                if ((piVar10[8] & 0x100000U) != 0) {
                  iVar3 = *extraout_ECX;
                  *(undefined4 *)(&stack0x00000650 + uVar4 * 4) = 0x50;
                  iVar3 = (**(code **)(iVar3 + 4))();
                  if (-1 < iVar3) {
                    (&param_4)[uVar4] = 1;
                  }
                }
                if ((&param_4)[uVar4] == 0) {
                  iVar3 = *extraout_ECX;
                  *(undefined4 *)(&stack0x00000650 + uVar4 * 4) = 0x40;
                  iVar3 = (**(code **)(iVar3 + 4))();
                  if (-1 < iVar3) {
                    (&param_4)[uVar4] = 1;
                  }
                  if ((&param_4)[uVar4] == 0) {
                    iVar3 = *extraout_ECX;
                    *(undefined4 *)(&stack0x00000650 + uVar4 * 4) = 0x80;
                    iVar3 = (**(code **)(iVar3 + 4))();
                    if (-1 < iVar3) {
                      (&param_4)[uVar4] = 1;
                    }
                    goto LAB_0048249e;
                  }
                }
              }
              if ((extraout_ECX[0xdb8e] != 0) && (iVar3 = FUN_00482880(), iVar3 == 0)) {
                (&param_4)[uVar4] = 0;
              }
            }
LAB_004824fd:
            uVar4 = uVar4 + 1;
          } while (uVar4 < uStack_20);
        }
        if (uStack_1c != 0) {
          iVar3 = 0;
          uVar4 = uStack_1c;
          do {
            uVar8 = 0;
            if (uStack_20 != 0) {
              do {
                if ((*(int *)(&stack0x00000c9c + iVar3) == *(int *)(&stack0x00000330 + uVar8 * 4))
                   && ((&param_4)[uVar8] == 1)) {
                  piVar10[piVar10[0x38] * 5 + 0x39] = *(int *)(&stack0x00000c90 + iVar3);
                  piVar10[piVar10[0x38] * 5 + 0x3a] = *(int *)(&stack0x00000c94 + iVar3);
                  piVar10[piVar10[0x38] * 5 + 0x3b] = *(int *)(&stack0x00000c9c + iVar3);
                  piVar10[(piVar10[0x38] + 0xc) * 5] = *(int *)(&stack0x00000650 + uVar8 * 4);
                  piVar10[piVar10[0x38] * 5 + 0x3d] = *(int *)(&stack0x00000970 + uVar8 * 4);
                  piVar10[0x38] = piVar10[0x38] + 1;
                  if (*piVar10 == 1) {
                    extraout_ECX[0xd9f2] = 1;
                  }
                }
                uVar8 = uVar8 + 1;
              } while (uVar8 < uStack_20);
            }
            iVar3 = iVar3 + 0x10;
            uVar4 = uVar4 - 1;
          } while (uVar4 != 0);
        }
        uVar4 = piVar10[0x38];
        uVar8 = 0;
        if (uVar4 != 0) {
          piVar6 = piVar10 + 0x3b;
          do {
            if ((piVar6[-2] == 0x280) && (piVar6[-1] == 0x1e0)) {
              piVar10[0x421] = uVar8;
              iVar3 = *piVar6;
              if ((iVar3 == 0x17) || ((iVar3 == 0x18 || (iVar3 == 0x19)))) break;
            }
            uVar8 = uVar8 + 1;
            piVar6 = piVar6 + 5;
          } while (uVar8 < uVar4);
        }
        if ((param_4 != 0) && ((piVar10[4] & 0x80000U) != 0)) {
          piVar10[0x37] = 1;
          piVar10[0x422] = 1;
        }
        if (uVar4 != 0) {
          piVar1[0x10f] = piVar1[0x10f] + 1;
        }
        uStack_28 = uStack_28 + 4;
      } while (uStack_28 < 8);
      if (piVar1[0x10f] != 0) {
        extraout_ECX[0xd9e5] = extraout_ECX[0xd9e5] + 1;
      }
      uVar8 = (**(code **)(*(int *)extraout_ECX[0xdb14] + 0x10))();
      uVar4 = unaff_retaddr;
    } while ((int)piVar2 + 1U < uVar8);
  }
  uVar4 = extraout_ECX[0xd9e5];
  if (uVar4 == 0) {
    return 0x82000003;
  }
  uVar8 = 0;
  if (uVar4 != 0) {
    puVar9 = (uint *)(extraout_ECX + 0x110);
    do {
      uVar5 = 0;
      if (*puVar9 != 0) {
        puVar7 = puVar9 + 0x423;
        do {
          if (*puVar7 != 0) {
            extraout_ECX[(uVar8 + 1) * 0x15ca] = uVar5;
            extraout_ECX[0xd9e6] = uVar8;
            extraout_ECX[0xd9e7] = 1;
            if (extraout_ECX[uVar5 * 0x425 + uVar8 * 0x15ca + 0x111] == 2) {
              if (extraout_ECX[0xd9ef] == 0) {
                FUN_00483330();
                return 0;
              }
              if (extraout_ECX[0xd9f2] == 0) {
                FUN_00483330();
                return 0;
              }
              if (extraout_ECX[0xd9f0] == 0) {
                FUN_00483330();
                return 0;
              }
              if (extraout_ECX[0xd9f1] == 0) {
                FUN_00483330();
                return 0;
              }
              FUN_00483330();
            }
            return 0;
          }
          uVar5 = uVar5 + 1;
          puVar7 = puVar7 + 0x425;
        } while (uVar5 < *puVar9);
      }
      uVar8 = uVar8 + 1;
      puVar9 = puVar9 + 0x15ca;
    } while (uVar8 < uVar4);
  }
  return 0x82000004;
}

