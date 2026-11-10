/* Original Meteor.exe static export @ 004ce850; original sample not executed. */
/* XREF 005aa770 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __fastcall FUN_004ce850(int *param_1)

{
  float *pfVar1;
  float *pfVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  float10 extraout_ST0;
  float10 fVar11;
  undefined4 *puStack_b8;
  float fStack_b4;
  char *pcStack_b0;
  undefined1 *puStack_ac;
  float fStack_a8;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  float fStack_80;
  float fStack_7c;
  undefined1 auStack_74 [8];
  undefined4 auStack_6c [3];
  undefined1 auStack_60 [36];
  undefined4 uStack_3c;
  undefined1 auStack_38 [12];
  float fStack_2c;
  float fStack_10;
  int iStack_c;
  float fStack_8;
  
  if (param_1[4] == 0) {
    piVar8 = (int *)0x0;
  }
  else {
    piVar8 = (int *)(param_1[4] + -0x65c);
  }
  puStack_ac = auStack_60;
  fStack_a8 = 2.8026e-45;
  pcStack_b0 = (char *)0x4ce87c;
  (**(code **)(*piVar8 + 0x6c))();
  pcStack_b0 = s_d_base_005c928c;
  fStack_b4 = 7.062914e-39;
  fStack_b4 = (float)FUN_005569b0();
  if (fStack_b4 != -NAN) {
    pcStack_b0 = auStack_38;
    puStack_b8 = (undefined4 *)0x4ce89e;
    FUN_00557ef0();
    pcStack_b0 = auStack_74;
    fStack_b4 = 7.062963e-39;
    (**(code **)(*piVar8 + 0x20))();
    puStack_b8 = auStack_6c;
    puVar9 = &uStack_3c;
    puVar10 = auStack_6c;
    for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar10 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar10 = puVar10 + 1;
    }
    fStack_b4 = 0.0;
    (**(code **)(*piVar8 + 0x70))();
    fVar5 = _DAT_005a83f4 / fStack_10;
    fVar4 = _DAT_005a9b30;
    if (param_1[0xd7] != 0) {
      fVar4 = _DAT_005aa928;
    }
    pfVar1 = (float *)(param_1 + 0xee);
    fVar4 = _DAT_005a83f4 - fVar4 * fStack_10;
    fStack_a8 = fVar4 * *pfVar1;
    *pfVar1 = fStack_a8;
    param_1[0xef] = (int)(fVar4 * (float)param_1[0xef]);
    param_1[0xf0] = (int)(fVar4 * (float)param_1[0xf0]);
    uVar6 = __ftol();
    if (_DAT_005a83ec <= (float)(int)((uVar6 ^ (int)uVar6 >> 0x1f) - ((int)uVar6 >> 0x1f))) {
      param_1[0xe6] = (int)(float)extraout_ST0;
      param_1[0xf0] = (int)(float)extraout_ST0;
    }
    else {
      fVar4 = fStack_10 * *(float *)(iStack_c + 8);
      param_1[0xf0] = (int)fVar4;
      param_1[0xe6] = (int)(fVar4 + (float)param_1[0xe6]);
    }
    pfVar2 = (float *)(param_1 + 0xe4);
    uStack_8c = 0;
    uStack_88 = 0;
    uStack_84 = 0x41200000;
    *pfVar2 = fStack_80 * fVar5 * fStack_8 + *pfVar1;
    param_1[0xe5] = (int)(fStack_7c * fVar5 * fStack_8 + (float)param_1[0xef]);
    fStack_a8 = *pfVar2 + (float)param_1[0x2e];
    *pfVar2 = fStack_a8;
    param_1[0xe5] = (int)((float)param_1[0xe5] + (float)param_1[0x2f]);
    param_1[0xe6] = (int)((float)param_1[0xe6] + (float)param_1[0x30]);
    if ((param_1[0x2a] != 0) && (param_1[0xea] != 0)) {
      iVar7 = (**(code **)(*param_1 + 0xfc))(pfVar2,pfVar2,(double)fStack_10,&uStack_8c,0,0);
      bVar3 = *pfVar2 == _DAT_005a83e4;
      param_1[0xda] = iVar7;
      if (bVar3) {
        *pfVar1 = 0.0;
      }
      if ((float)param_1[0xe5] == _DAT_005a83e4) {
        param_1[0xef] = 0;
      }
      if ((float)param_1[0xe6] == _DAT_005a83e4) {
        param_1[0xf0] = 0;
      }
      puStack_b8 = (undefined4 *)(fStack_2c * (float)param_1[0xeb]);
      fStack_b4 = fStack_2c * (float)param_1[0xec];
      pcStack_b0 = (char *)(fStack_2c * (float)param_1[0xed]);
      fVar11 = (float10)FUN_0047ecf0();
      if ((float10)_DAT_005a8f74 < fVar11) {
        (**(code **)(*param_1 + 0xfc))(&puStack_b8,&puStack_b8,(double)fStack_2c,&fStack_a8,0,0);
      }
      return param_1[0xda];
    }
  }
  return 0;
}

