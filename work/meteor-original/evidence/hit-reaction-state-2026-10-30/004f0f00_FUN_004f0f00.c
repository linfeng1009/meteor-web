/* Original Meteor.exe static export @ 004f0f00; original sample not executed. */
/* XREF 005aa0f8 DATA */
/* XREF 005ab580 DATA */
/* XREF 005ab9c0 DATA */
/* XREF 005ab340 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_004f0f00(int *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float *pfVar8;
  undefined4 uVar9;
  undefined1 *puVar10;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  int iStack_dc;
  float *pfStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined1 auStack_b8 [4];
  undefined1 auStack_b4 [36];
  undefined4 uStack_90;
  undefined4 uStack_8c;
  int aiStack_88 [10];
  float fStack_60;
  float fStack_5c;
  int aiStack_58 [22];
  
  iVar2 = (**(code **)(*param_1 + 0x48))();
  if (iVar2 == 0) {
    return 0;
  }
  if (param_1[0x8e] == 0) {
    return 0;
  }
  fVar7 = (float10)FUN_00549b00();
  if ((float10)_DAT_005a9500 < fVar7) {
    if ((undefined4 *)param_1[0x8e] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0x8e])(1);
    }
    param_1[0x8e] = 0;
    piVar3 = (int *)(**(code **)(*param_1 + 0x44))();
    iVar2 = (**(code **)(*piVar3 + 0x150))();
    return iVar2;
  }
  iVar2 = FUN_005499a0(0);
  if (((iVar2 != 0) &&
      (iVar2 = param_1[0x8e],
      1 < ((*(int *)(iVar2 + 0x94) - *(int *)(iVar2 + 0x8c)) / 0xc +
          (*(int *)(iVar2 + 0x9c) - *(int *)(iVar2 + 0xa0)) / 0xc +
          (*(int *)(iVar2 + 0xa8) - *(int *)(iVar2 + 0x98) >> 2) * 0x2a) - 0x2aU)) &&
     (*(int *)(iVar2 + 0x80) != 0)) {
    piVar3 = (int *)FUN_00487830();
    piVar3 = (int *)(**(code **)(*piVar3 + 300))(*(undefined4 *)(param_1[0x8e] + 0x80));
    if ((piVar3 != (int *)0x0) && (piVar3 != (int *)0x65c)) {
      (**(code **)(*piVar3 + 4))(&fStack_f0,0,0);
      piVar3 = (int *)FUN_00487830();
      iVar2 = (**(code **)(*piVar3 + 0x14c))(*(undefined4 *)(param_1[0x8e] + 0x80));
      if (iVar2 != 0) {
        fStack_f0 = *(float *)(iVar2 + 0x30) * (float)_DAT_005a8f90 + fStack_f0;
        fStack_ec = *(float *)(iVar2 + 0x34) * (float)_DAT_005a8f90 + fStack_ec;
        fStack_e8 = *(float *)(iVar2 + 0x38) * (float)_DAT_005a8f90 + fStack_e8;
      }
      FUN_004e6050(param_1[0x8e] + 0x8c);
      uVar4 = FUN_0049bd10(0);
      FUN_004e6050(uVar4);
      *pfStack_d8 = fStack_f0;
      pfStack_d8[1] = fStack_ec;
      pfStack_d8[2] = fStack_e8;
    }
  }
  FUN_0047b740();
  FUN_00477eb0(auStack_b4);
  uStack_e4 = uStack_90;
  iStack_dc = aiStack_88[0];
  uStack_e0 = uStack_8c;
  iVar2 = (**(code **)(*(int *)param_1[0x8e] + 4))(param_2);
  puVar1 = (undefined4 *)param_1[0x8e];
  if (iVar2 == 0) {
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
    }
    param_1[0x8e] = 0;
    piVar3 = (int *)(**(code **)(*param_1 + 0x44))();
  }
  else {
    if (puVar1[0x1f] != 0) {
      return iVar2;
    }
    FUN_00477eb0(aiStack_88);
    fStack_f0 = fStack_60;
    puVar10 = &stack0xffffff0c;
    pfVar8 = &fStack_e8;
    fStack_ec = fStack_5c;
    FUN_00487830(pfVar8,puVar10);
    FUN_00562dd0(pfVar8,puVar10);
    puVar10 = &stack0xffffff0c;
    pfVar8 = &fStack_e8;
    FUN_00487830(pfVar8,puVar10);
    iVar2 = FUN_00564760(pfVar8,puVar10);
    if (iVar2 == 0) {
      iVar2 = FUN_00487830();
      iVar2 = *(int *)(*(int *)(iVar2 + 0x2188) + 8);
      iVar5 = FUN_00487830();
      if (iVar2 == *(int *)(iVar5 + 0x2188)) {
        return iVar5 + 0x2188;
      }
      do {
        iVar5 = (**(code **)(*param_1 + 0x128))(*(undefined4 *)(iVar2 + 0x10));
        if (iVar5 != 0) {
          iVar5 = (**(code **)(*param_1 + 0x48))();
          fVar7 = (float10)FUN_00549b00();
          if (iVar5 == 0) {
            iVar5 = 0;
          }
          else {
            iVar5 = iVar5 + 0x65c;
          }
          iVar6 = *(int *)(iVar2 + 0x14);
          if ((iVar6 != iVar5) && ((float10)_DAT_005a8f80 < fVar7)) {
            if (iVar6 == 0) {
              iVar6 = 0;
            }
            else {
              iVar6 = iVar6 + -0x65c;
            }
            piVar3 = (int *)FUN_00487830();
            iVar5 = (**(code **)(*piVar3 + 0x1a4))(iVar6,&fStack_e8,&stack0xffffff0c,0x40266666);
            if (0 < iVar5) {
              FUN_00549a90(0,0);
              iStack_dc = *(int *)(iVar2 + 0x10);
              iVar2 = param_1[0x8e];
              pfStack_d8 = *(float **)(iVar2 + 0x54);
              uVar9 = 0x14;
              uStack_d4 = *(undefined4 *)(iVar2 + 0x58);
              uStack_d0 = *(undefined4 *)(iVar2 + 0x5c);
              uStack_cc = *(undefined4 *)(iVar2 + 0x60);
              piVar3 = &iStack_dc;
              uVar4 = 5;
              goto LAB_004f1519;
            }
          }
        }
        iVar5 = *(int *)(iVar2 + 0xc);
        if (iVar5 == 0) {
          iVar5 = *(int *)(iVar2 + 4);
          if (iVar2 == *(int *)(iVar5 + 0xc)) {
            do {
              iVar2 = iVar5;
              iVar5 = *(int *)(iVar2 + 4);
            } while (iVar2 == *(int *)(iVar5 + 0xc));
          }
          if (*(int *)(iVar2 + 0xc) != iVar5) {
            iVar2 = iVar5;
          }
        }
        else {
          for (iVar6 = *(int *)(iVar5 + 8); iVar2 = iVar5, iVar6 != 0; iVar6 = *(int *)(iVar6 + 8))
          {
            iVar5 = iVar6;
          }
        }
        iVar5 = FUN_00487830();
        if (iVar2 == *(int *)(iVar5 + 0x2188)) {
          return iVar5 + 0x2188;
        }
      } while( true );
    }
    puVar1 = (undefined4 *)param_1[0x8e];
    if ((int)(puVar1[0x25] - puVar1[0x23]) / 0xc +
        (int)(puVar1[0x27] - puVar1[0x28]) / 0xc + ((int)(puVar1[0x2a] - puVar1[0x26]) >> 2) * 0x2a
        != 0x2a) {
      puVar1[0x1c] = 0;
      *(undefined4 *)(param_1[0x8e] + 0x74) = 0;
      *(undefined4 *)(param_1[0x8e] + 0x78) = 0;
      FUN_00477e30(auStack_b8);
      iVar2 = param_1[0x8e];
      if (((*(int *)(iVar2 + 0x94) - *(int *)(iVar2 + 0x8c)) / 0xc +
          (*(int *)(iVar2 + 0x9c) - *(int *)(iVar2 + 0xa0)) / 0xc +
          (*(int *)(iVar2 + 0xa8) - *(int *)(iVar2 + 0x98) >> 2) * 0x2a) - 0x2aU < 2) {
        *(undefined4 *)(iVar2 + 0x7c) = 1;
        (**(code **)(*(int *)param_1[0x8e] + 0xc))(aiStack_58);
        aiStack_58[0] = param_1[0x95];
        piVar3 = aiStack_58;
        uVar9 = 0x54;
        uVar4 = 0xc;
      }
      else {
        if (*(int *)(iVar2 + 0x8c) == *(int *)(iVar2 + 0x94) + -0xc) {
          FUN_00402e90(*(undefined4 *)(iVar2 + 0x90),0x1f8);
          piVar3 = (int *)(*(int *)(iVar2 + 0x98) + 4);
          *(int **)(iVar2 + 0x98) = piVar3;
          iVar5 = *piVar3;
          *(int *)(iVar2 + 0x90) = iVar5;
          *(int *)(iVar2 + 0x94) = iVar5 + 0x1f8;
          iVar5 = *(int *)(iVar2 + 0x90);
        }
        else {
          iVar5 = *(int *)(iVar2 + 0x8c) + 0xc;
        }
        *(int *)(iVar2 + 0x8c) = iVar5;
        (**(code **)(*(int *)param_1[0x8e] + 0xc))(aiStack_58);
        aiStack_58[0] = param_1[0x95];
        piVar3 = aiStack_58;
        uVar9 = 0x54;
        uVar4 = 0xd;
      }
      goto LAB_004f1519;
    }
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
    }
    param_1[0x8e] = 0;
    piVar3 = (int *)(**(code **)(*param_1 + 0x44))();
  }
  (**(code **)(*piVar3 + 0x150))();
  uVar9 = 0;
  piVar3 = (int *)0x0;
  uVar4 = 0xe;
LAB_004f1519:
  iVar2 = FUN_0054a6c0(uVar4,piVar3,uVar9,0);
  return iVar2;
}

