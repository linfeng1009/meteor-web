/* Original Meteor.exe static export @ 004cc840; original sample not executed. */
/* XREF 005aa728 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004cc840(int *param_1)

{
  float *pfVar1;
  int *piVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float fStack_f8;
  float fStack_f4;
  float fStack_f0;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  int iStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined1 auStack_74 [8];
  float fStack_6c;
  float fStack_60;
  undefined1 auStack_50 [32];
  undefined1 auStack_30 [16];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  int iStack_10;
  
  piVar2 = (int *)param_1[4];
  if (piVar2 != (int *)0x0) {
    (**(code **)(piVar2[-0x197] + 0x6c))(auStack_30,2);
    (**(code **)(*piVar2 + 4))(auStack_50,auStack_74,&fStack_80);
    pfVar1 = (float *)(param_1 + 0xe4);
    uStack_98 = uStack_8c;
    uStack_94 = uStack_88;
    fStack_a4 = *pfVar1;
    uStack_90 = uStack_84;
    iStack_a0 = param_1[0xe5];
    uStack_9c = 0;
    FUN_0047ec40();
    fStack_b4 = fStack_18;
    fStack_bc = fStack_20;
    fStack_b8 = fStack_1c;
    FUN_0047ec40();
    FUN_00529c40(&stack0xfffffefc,&uStack_98,&fStack_c8);
    FUN_0047ec40();
    iVar6 = 0;
    do {
      if (iVar6 == 0) {
        fStack_f8 = fStack_80;
        fStack_f4 = fStack_7c;
        fStack_f0 = fStack_78;
      }
      else if (iVar6 == 1) {
        fStack_f8 = fStack_c8 + fStack_80;
        fStack_f4 = fStack_7c + fStack_c4;
        fStack_f0 = fStack_78 + fStack_c0;
        fStack_b0 = fStack_f8;
        fStack_ac = fStack_f4;
        fStack_a8 = fStack_f0;
        FUN_0047ec40();
      }
      else if (iVar6 == 2) {
        fStack_6c = fStack_c0 * _DAT_005a8430;
        fStack_f8 = fStack_c8 * _DAT_005a8430 + fStack_80;
        fStack_f4 = fStack_7c + fStack_c4 * _DAT_005a8430;
        fStack_f0 = fStack_78 + fStack_6c;
        FUN_0047ec40();
      }
      fStack_60 = fStack_f0 * _DAT_005a8b08;
      fStack_e0 = fStack_f8 * _DAT_005a8b08 + fStack_bc;
      fStack_dc = fStack_b8 + fStack_f4 * _DAT_005a8b08;
      fStack_d8 = fStack_b4 + fStack_60;
      iVar5 = FUN_005644f0(&fStack_bc,&fStack_e0,auStack_50,&fStack_d4);
      if (iVar5 != 0) {
        fVar3 = fStack_d4 * *pfVar1 +
                fStack_d0 * (float)param_1[0xe5] + fStack_cc * (float)param_1[0xe6];
        fStack_dc = fStack_d0 * fVar3;
        fStack_d8 = fStack_cc * fVar3;
        *pfVar1 = *pfVar1 - fStack_d4 * fVar3;
        param_1[0xe5] = (int)((float)param_1[0xe5] - fStack_dc);
        fVar3 = fStack_cc + _DAT_005a83f4;
        param_1[0xe6] = (int)((float)param_1[0xe6] - fStack_d8);
        FUN_0047ec40();
        fVar4 = _DAT_005a84c0;
        if (iStack_10 != 0) {
          fVar4 = _DAT_005aa8c0;
        }
        fStack_dc = fStack_d0 * fVar4;
        fStack_d8 = fVar3 * fVar4;
        *pfVar1 = fStack_d4 * fVar4 + *pfVar1;
        param_1[0xe5] = (int)(fStack_dc + (float)param_1[0xe5]);
        param_1[0xe6] = (int)(fStack_d8 + (float)param_1[0xe6]);
        if (iVar6 == 0) {
          (**(code **)(*param_1 + 0x74))(0x9d,0,0,0xbf800000);
        }
        else {
          if (iVar6 == 1) {
            (**(code **)(*param_1 + 0x74))(0x9f,0,0,0xbf800000);
            return 1;
          }
          if (iVar6 == 2) {
            (**(code **)(*param_1 + 0x74))(0xa0,0,0,0xbf800000);
            return 1;
          }
        }
        return 1;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 3);
  }
  return 0;
}

