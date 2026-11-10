/* Original Meteor.exe static export @ 00490350; original sample not executed. */
/* XREF 005a9170 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00490350(int *param_1)

{
  int *piVar1;
  float fVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  uint uVar12;
  int **ppiVar13;
  float10 fVar14;
  undefined4 local_a0;
  undefined4 uStack_9c;
  float fStack_94;
  int *piStack_90;
  float fStack_8c;
  float fStack_88;
  int *piStack_84;
  float fStack_80;
  float fStack_7c;
  int *piStack_78;
  float fStack_74;
  int *local_70;
  float fStack_6c;
  undefined1 auStack_68 [40];
  undefined4 auStack_40 [15];
  
  local_70 = param_1;
  FUN_005499a0(&local_a0);
  (**(code **)(*param_1 + 0x234))();
  iVar10 = *(int *)(param_1[0x8bb] + 8);
  if (iVar10 != param_1[0x8bb]) {
    do {
      uVar4 = *(undefined4 *)(iVar10 + 0x10);
      iVar6 = (**(code **)(*param_1 + 0x238))(uVar4);
      if ((((iVar6 == 0) && (*(int *)(iVar10 + 0x200) != 0)) &&
          (piVar7 = (int *)(**(code **)(*param_1 + 300))(uVar4), piVar7 != (int *)0x0)) &&
         (piVar1 = piVar7 + -0x197, piVar1 != (int *)0x0)) {
        fVar14 = (float10)FUN_00549b00();
        fVar2 = (float)fVar14;
        if (fVar14 <= (float10)_DAT_005a8460) {
          fStack_6c = fVar2 + fVar2;
          (**(code **)(*param_1 + 500))(piVar7,iVar10 + 0x18,local_a0,uStack_9c,fStack_6c);
        }
        else {
          (**(code **)(*param_1 + 0x1f0))(piVar7,iVar10 + 0x18,local_a0,uStack_9c);
        }
        if (*(int *)(iVar10 + 0xdc) == 1) {
          *(undefined4 *)(iVar10 + 0xdc) = 0;
          FUN_00549a90(0,0);
          FUN_0055c4d0();
          uVar5 = *(uint *)(iVar10 + 0x54);
          uVar12 = uVar5 & 0x7ff;
          if ((uVar5 & 0x800) == 0) {
            if ((int)(uint)*(ushort *)((int)piVar7 + 0x24e) < *(int *)(iVar10 + 0x58)) {
              FUN_00559720(0x3dcccccd);
              (**(code **)(*param_1 + 0x210))(piVar1,uVar12,(int)uVar5 >> 0xd,1,0xc0a00000);
              uVar3 = *(undefined2 *)(iVar10 + 0x58);
              piVar7[0x7c] = 0;
              *(undefined2 *)((int)piVar7 + 0x24e) = uVar3;
              *(undefined2 *)(piVar7 + -0x12) = uVar3;
            }
          }
          else {
            uVar8 = FUN_0055c4e0();
            if (uVar12 == uVar8) {
              *(undefined2 *)((int)piVar7 + 0x24e) = *(undefined2 *)(iVar10 + 0x58);
            }
            else if ((int)(short)piVar7[-0x12] < *(int *)(iVar10 + 0x58)) {
              FUN_00559720(0x3dcccccd);
              (**(code **)(*param_1 + 0x210))(piVar1,uVar12,(int)uVar5 >> 0xd,1,0xc0a00000);
              *(undefined2 *)(piVar7 + -0x12) = *(undefined2 *)(iVar10 + 0x58);
              *(undefined2 *)((int)piVar7 + 0x24e) = *(undefined2 *)(iVar10 + 0x58);
              piVar7[0x7c] = 1;
            }
          }
        }
        else {
          fVar14 = (float10)FUN_00549b00();
          if (fVar14 < (float10)_DAT_005a8460 != (fVar14 == (float10)_DAT_005a8460)) {
            if (_DAT_005a9518 <= fVar2) {
              fVar14 = (float10)FUN_00549b00();
              if ((fVar14 <= (float10)_DAT_005a8f90) ||
                 (*(float *)(iVar10 + 0x50) * *(float *)(iVar10 + 0x50) +
                  *(float *)(iVar10 + 0x4c) * *(float *)(iVar10 + 0x4c) +
                  *(float *)(iVar10 + 0x48) * *(float *)(iVar10 + 0x48) <= _DAT_005a84c8)) {
                fStack_88 = *(float *)(iVar10 + 0x48) * (float)(double)CONCAT44(uStack_9c,local_a0);
                piStack_84 = (int *)(*(float *)(iVar10 + 0x4c) *
                                    (float)(double)CONCAT44(uStack_9c,local_a0));
                fStack_80 = *(float *)(iVar10 + 0x50) * (float)(double)CONCAT44(uStack_9c,local_a0);
                *(float *)(iVar10 + 0x18) = *(float *)(iVar10 + 0x18) + fStack_88;
                *(float *)(iVar10 + 0x1c) =
                     *(float *)(iVar10 + 0x4c) * (float)(double)CONCAT44(uStack_9c,local_a0) +
                     *(float *)(iVar10 + 0x1c);
                *(float *)(iVar10 + 0x20) =
                     *(float *)(iVar10 + 0x50) * (float)(double)CONCAT44(uStack_9c,local_a0) +
                     *(float *)(iVar10 + 0x20);
              }
              else {
                fStack_80 = 0.0;
                piStack_84 = (int *)0x0;
                fStack_88 = 0.0;
              }
            }
            else {
              (**(code **)(*piVar1 + 0x6c))(auStack_68,2);
              iVar6 = FUN_005569b0(s_d_base_005c928c);
              if (iVar6 != -1) {
                FUN_00557ef0(iVar6,auStack_40);
                iVar6 = *piVar1;
                puVar11 = auStack_40;
                ppiVar13 = &local_70;
                for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1) {
                  *ppiVar13 = (int *)*puVar11;
                  puVar11 = puVar11 + 1;
                  ppiVar13 = ppiVar13 + 1;
                }
                (**(code **)(iVar6 + 0x70))(&local_70,0);
                param_1 = piStack_78;
              }
              (**(code **)(*piVar1 + 0x20))(&piStack_84);
              fStack_8c = *(float *)(iVar10 + 0x274);
              fStack_94 = fStack_7c * fStack_8c;
              piStack_90 = (int *)(fStack_8c * (float)piStack_78);
              fStack_8c = fStack_8c * fStack_74;
              *(float *)(iVar10 + 0x18) = fStack_94 + *(float *)(iVar10 + 0x18);
              *(float *)(iVar10 + 0x1c) = (float)piStack_90 + *(float *)(iVar10 + 0x1c);
              *(float *)(iVar10 + 0x20) = fStack_8c + *(float *)(iVar10 + 0x20);
              *(undefined4 *)(iVar10 + 0x50) = 0;
              *(undefined4 *)(iVar10 + 0x4c) = 0;
              *(undefined4 *)(iVar10 + 0x48) = 0;
              fStack_88 = fStack_94;
              piStack_84 = piStack_90;
              fStack_80 = fStack_8c;
              fStack_7c = fStack_94;
              piStack_78 = piStack_90;
              fStack_74 = fStack_8c;
            }
            (**(code **)(*piVar7 + 0x84))(&fStack_88);
          }
          iVar6 = FUN_0055c300();
          if ((iVar6 == 4) && (piVar7[0x7c] != 0)) {
            piVar7[0x7c] = 0;
            iVar6 = FUN_0055c4e0();
            if ((iVar6 != 0x70) && (iVar6 != 0x71)) {
              FUN_00559720(0x3f800000);
              (**(code **)(*param_1 + 0x210))(piVar1,0,1,1,0xc0a00000);
            }
          }
        }
      }
      iVar6 = *(int *)(iVar10 + 0xc);
      if (iVar6 == 0) {
        iVar6 = *(int *)(iVar10 + 4);
        if (iVar10 == *(int *)(iVar6 + 0xc)) {
          do {
            iVar10 = iVar6;
            iVar6 = *(int *)(iVar10 + 4);
          } while (iVar10 == *(int *)(iVar6 + 0xc));
        }
        if (*(int *)(iVar10 + 0xc) != iVar6) {
          iVar10 = iVar6;
        }
      }
      else {
        for (iVar9 = *(int *)(iVar6 + 8); iVar10 = iVar6, iVar9 != 0; iVar9 = *(int *)(iVar9 + 8)) {
          iVar6 = iVar9;
        }
      }
    } while (iVar10 != param_1[0x8bb]);
  }
  return;
}

