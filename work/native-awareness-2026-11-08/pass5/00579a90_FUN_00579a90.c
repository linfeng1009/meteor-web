/* Original Meteor.exe static export @ 00579a90; original sample not executed. */
/* XREF 005593d1 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00579a90(int *param_1)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  ushort *puVar11;
  float10 fVar12;
  float fVar13;
  int *piStack_48;
  uint uStack_3c;
  
  FUN_00475590(0,1);
  FUN_00475590(0x14,1);
  FUN_00475590(0x15,1);
  FUN_00475590(1,1);
  FUN_00475950(&DAT_005c7df8,&DAT_005c7df0);
  FUN_00476090(2);
  FUN_00476090(3);
  FUN_0047ec40();
  fVar12 = (float10)FUN_0047ecf0();
  fVar2 = (float)(fVar12 * (float10)(float)param_1[0x54]);
  fVar3 = (float)(fVar12 * (float10)(float)param_1[0x55]);
  FUN_00476090(3);
  piVar6 = (int *)FUN_00476070(0);
  piVar1 = param_1 + 1;
  piVar10 = piVar1;
  for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
    *piVar10 = *piVar6;
    piVar6 = piVar6 + 1;
    piVar10 = piVar10 + 1;
  }
  FUN_00477b90(3,param_1 + 0x11);
  FUN_00474410();
  if (*param_1 == 1) {
    uVar9 = 0xffffffff;
    piVar6 = param_1 + 0x14;
    do {
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      iVar8 = *piVar6;
      piVar6 = (int *)((int)piVar6 + 1);
    } while ((char)iVar8 != '\0');
    uStack_3c = ~uVar9 - 1;
  }
  else {
    uStack_3c = FUN_0050b0ec(param_1 + 0x1c);
  }
  fVar13 = _DAT_005a8fac;
  if ((param_1[0x4f] == 1) || (fVar13 = _DAT_005a83e8, param_1[0x4f] == 3)) {
    FUN_00478150((_DAT_005a83e8 - (float)uStack_3c * fVar13) * fVar2);
  }
  fVar13 = fVar3 * _DAT_005a83e8;
  FUN_00478190(fVar13);
  if (param_1[0x50] != 4) {
    if (param_1[0x50] != 5) goto LAB_00579ca0;
    fVar13 = fVar3 * _DAT_005a8ff0;
  }
  FUN_00478190(fVar13);
LAB_00579ca0:
  iVar8 = 0;
  if (*param_1 == 1) {
    piStack_48 = param_1 + 0x14;
    if (0 < param_1[0x4e]) {
      fVar13 = _DAT_005a83f4 / fVar3;
      piVar6 = param_1 + 0x2c;
      do {
        iVar4 = *piVar6;
        iVar7 = FUN_00593d6d(piStack_48);
        piStack_48 = (int *)((int)piStack_48 + iVar4);
        fVar5 = (float)iVar7 * _DAT_005a83e8 * fVar2;
        FUN_00477db0(fVar5,fVar3,0x3f800000);
        FUN_00474410();
        thunk_FUN_004e8500(piVar1);
        FUN_00479f80(*(undefined4 *)(param_1[0x51] + iVar8 * 4));
        FUN_0047c2e0(0);
        FUN_00474470();
        FUN_004781d0(0x3f800000,0,0,0);
        FUN_00477db0(_DAT_005a83f4 / fVar5,fVar13,0x3f800000);
        iVar8 = iVar8 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar8 < param_1[0x4e]);
    }
  }
  else if (0 < param_1[0x4e]) {
    fVar13 = _DAT_005a83f4 / fVar3;
    puVar11 = (ushort *)(param_1 + 0x1c);
    do {
      fVar5 = (float)(int)(2 - (uint)(*puVar11 < 0x80)) * _DAT_005a83e8 * fVar2;
      FUN_00477db0(fVar5,fVar3,0x3f800000);
      FUN_00474410();
      thunk_FUN_004e8500(piVar1);
      FUN_00479f80(*(undefined4 *)(param_1[0x51] + iVar8 * 4));
      FUN_0047c2e0(0);
      FUN_00474470();
      FUN_004781d0(0x3f800000,0,0,0);
      FUN_00477db0(_DAT_005a83f4 / fVar5,fVar13,0x3f800000);
      iVar8 = iVar8 + 1;
      puVar11 = puVar11 + 1;
    } while (iVar8 < param_1[0x4e]);
  }
  FUN_00474470();
  FUN_00475590(0x14,2);
  FUN_00475590(0x15,2);
  FUN_00475590(0,0);
  FUN_00475590(1,0);
  return;
}

