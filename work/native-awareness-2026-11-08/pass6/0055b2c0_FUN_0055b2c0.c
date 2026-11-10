/* Original Meteor.exe static export @ 0055b2c0; original sample not executed. */
/* XREF 004b8ab4 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0055b2c0(undefined4 *param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  char *pcVar6;
  int *piVar7;
  float10 fVar8;
  float10 fVar9;
  char acStack_50 [16];
  undefined1 auStack_40 [64];
  
  DAT_0072684c = DAT_0072684c + 1;
  fVar8 = (float10)FUN_004748b0();
  fVar9 = (float10)_DAT_00726850;
  _DAT_00726850 = (float)(fVar8 + fVar9);
  if ((float10)_DAT_005a83f4 < fVar8 + fVar9) {
    param_1[0x12] = (float)DAT_0072684c / _DAT_00726850;
    _DAT_00726850 = 0.0;
    DAT_0072684c = 0;
  }
  FUN_0055b260();
  FUN_00475800(&DAT_005c7dd4);
  FUN_00475590(0,1);
  FUN_004756e0(&DAT_005c7dcc,0);
  FUN_00475950(&DAT_005c7df8,&DAT_005c7474);
  FUN_00477200();
  if (*(char *)(param_1 + 0x18) == '\0') {
    return;
  }
  iVar3 = FUN_00474600();
  if (iVar3 == 1) {
    FUN_00474570(1);
    FUN_004745d0(auStack_40);
  }
  fVar2 = (float)param_1[0x10] * _DAT_005a83e8;
  FUN_00474570(3);
  FUN_00474410();
  FUN_004745d0(param_1 + 0x19);
  FUN_00474570(0);
  FUN_00474410();
  if (*(char *)(param_1 + 0x17) != '\0') {
    uVar4 = __ftol();
    FUN_00477200();
    FUN_004781d0((float)param_1[0x10] - _DAT_005a8f50,(float)param_1[0x11] - _DAT_005a84ac,
                 0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_00475590(1,1);
    FUN_0055aac0(uVar4,0,param_1 + 0x33d,auStack_40,param_1[6]);
    FUN_00475590(1,0);
  }
  if (*(char *)(param_1 + 0x16) != '\0') {
    FUN_00477200();
    FUN_004781d0(fVar2 - ((float)param_1[6] + (float)param_1[6]),
                 (float)param_1[0x11] - (float)param_1[7] * (float)_DAT_005aa910,0xbf800000,0);
    FUN_00475590(1,1);
    FUN_0055aac0(param_1[1],2,param_1 + 0x33d,auStack_40,param_1[6]);
    FUN_004745d0(auStack_40);
    FUN_00479f80(param_1[0x33c]);
    FUN_0047c2e0(0);
    FUN_004745d0(auStack_40);
    FUN_00478150(param_1[6]);
    FUN_0055aac0(*param_1,2,param_1 + 0x33d,auStack_40,param_1[6]);
    FUN_00475590(1,0);
  }
  if (*(char *)((int)param_1 + 0x5f) == '\0') goto LAB_0055bb62;
  if (*(char *)((int)param_1 + 0x59) != '\0') {
    FUN_00475590(1,1);
    FUN_00477200();
    FUN_004781d0((float)param_1[0x10] * _DAT_005a83e8,(float)param_1[0x11] * _DAT_005a83e8,
                 0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_00479f80(param_1[0x4e3]);
    FUN_0047c2e0(0);
    FUN_00475590(1,0);
  }
  FUN_00477200();
  FUN_004781d0(0x41c80000,0x41f00000,0xbf800000,0);
  FUN_004745d0(auStack_40);
  FUN_00479f80(param_1[0x2b3]);
  FUN_0047c2e0(0);
  if ((float)param_1[0x599] < _DAT_005a9b30 != ((float)param_1[0x599] == _DAT_005a9b30)) {
    FUN_0055ab70();
  }
  if (_DAT_005a83f4 <= (float)param_1[0x59a]) {
    FUN_0055ac30();
  }
  FUN_00477200();
  FUN_004781d0(0x43898000,0x41f00000,0xbf800000,0);
  FUN_004745d0(auStack_40);
  FUN_00479f80(param_1[0x2b4]);
  FUN_0047c2e0(0);
  if (*(char *)((int)param_1 + 0x5a) != '\0') {
    FUN_00477200();
    FUN_004781d0((float)param_1[10] * _DAT_005a83e8 + _DAT_005a8b10,0x41f00000,0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_00479f80(0);
    FUN_0047c2e0(0);
    FUN_00477200();
    FUN_004781d0((float)param_1[10] * _DAT_005a83e8 + _DAT_005a8b10,0x41f00000,0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_0047c2e0(0);
    FUN_00477200();
    FUN_004781d0((float)param_1[0x599] * (float)param_1[10] * _DAT_005a83e8 + _DAT_005a8b10,
                 0x41f00000,0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_0047c2e0(0);
    FUN_00508ae6(acStack_50,&DAT_005c9b80,param_1[2]);
    uVar5 = 0xffffffff;
    pcVar6 = acStack_50;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    FUN_00477200();
    FUN_004781d0((float)(int)(3 - (~uVar5 - 1)) * (float)param_1[0xc] + (float)param_1[10] +
                 _DAT_005ae1ac,0x424c0000,0xbf800000,0);
    FUN_00475590(1,1);
    FUN_0055aac0(param_1[2],0,param_1 + 0x3b6,auStack_40,param_1[0xc]);
    FUN_004745d0(auStack_40);
    FUN_00479f80(param_1[0x33b]);
    FUN_0047c2e0(0);
    FUN_00478150(param_1[0xc]);
    FUN_0055aac0(param_1[4],0,param_1 + 0x3b6,auStack_40,param_1[0xc]);
    FUN_00475590(1,0);
  }
  if (*(char *)((int)param_1 + 0x5b) != '\0') {
    FUN_00477200();
    FUN_004781d0((float)param_1[10] * _DAT_005a83e8 + _DAT_005a8f50,0x41500000,0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_00479f80(0);
    FUN_0047c2e0(0);
    FUN_00477200();
    FUN_004781d0((float)param_1[10] * _DAT_005a83e8 + _DAT_005a8f50,0x41500000,0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_0047c2e0(0);
    FUN_00477200();
    FUN_004781d0((float)param_1[0x59a] * (float)param_1[10] * _DAT_005a83e8 + _DAT_005a8f50,
                 0x41500000,0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_0047c2e0(0);
    FUN_00475590(0,1);
  }
  FUN_00477200();
  FUN_004781d0(0x42500000,0x42540000,0xbf800000,0);
  piVar7 = param_1 + 0x48;
  iVar3 = 2;
  do {
    if (*piVar7 != 0) {
      FUN_004745d0(auStack_40);
      if (param_1[0x47] == *piVar7) {
        FUN_00479f80(0);
        FUN_0047c2e0(0);
      }
      FUN_00479f80(param_1[*piVar7 + 0x38]);
      FUN_0047c2e0(0);
    }
    FUN_004781d0((float)param_1[8] + _DAT_005a8b80,0,0,0);
    piVar7 = piVar7 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (param_1[0x4a] != 0) {
    FUN_004745d0(auStack_40);
    FUN_0047c2e0(0);
    FUN_00479f80(param_1[0x2b2]);
    FUN_0047c2e0(0);
  }
  FUN_00475950(&DAT_005c7df8,&DAT_005c7df0);
  if (*(char *)((int)param_1 + 0x5e) != '\0') {
    fVar9 = (float10)FUN_004748b0();
    param_1[0x15] = (float)(fVar9 + (float10)(float)param_1[0x15]);
    FUN_00477200();
    FUN_004781d0(((float)param_1[10] + _DAT_005a8f70) - (float)param_1[8],0x42540000,0xbf800000,0);
    FUN_004745d0(auStack_40);
    FUN_00479f80(param_1[0x46]);
    FUN_0047c2e0(0);
    if (_DAT_005a9b30 <= (float)param_1[0x14]) {
      FUN_00475590(1,1);
      uVar4 = param_1[0x45];
    }
    else {
      iVar3 = __ftol();
      fVar2 = (float)param_1[0x15] - (float)iVar3;
      if (((fVar2 <= _DAT_005a83e4) || (_DAT_005a83f0 <= fVar2)) &&
         ((fVar2 <= _DAT_005a83e8 || (_DAT_005a9b34 <= fVar2)))) goto LAB_0055bb38;
      FUN_00475590(1,1);
      uVar4 = param_1[0x45];
    }
    FUN_00479f80(uVar4);
    FUN_0047c2e0(0);
    FUN_00475590(1,0);
  }
LAB_0055bb38:
  if (*(char *)((int)param_1 + 0x5d) != '\0') {
    FUN_0055b1c0();
  }
  FUN_004781d0((float)param_1[8] + _DAT_005a8b80,0,0,0);
LAB_0055bb62:
  FUN_00474470();
  FUN_00474570(3);
  FUN_00474470();
  FUN_00474570(0);
  FUN_00475590(0x14,2);
  FUN_00475590(0x15,2);
  FUN_00475800(&DAT_005c7ddc);
  return;
}

