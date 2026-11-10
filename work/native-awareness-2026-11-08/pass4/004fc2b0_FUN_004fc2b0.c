/* Original Meteor.exe static export @ 004fc2b0; original sample not executed. */
/* XREF 004fdfd5 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004fc2b0(int param_1,float param_2)

{
  float fVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  float10 fVar7;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_4;
  
  iVar3 = FUN_004c3830();
  if (iVar3 != 0) {
    fVar1 = (float)(int)**(short **)(param_1 + 0x10) * _DAT_005a83e8;
    if (param_2 < fVar1) {
      fVar1 = param_2;
    }
    iVar6 = 0;
    fStack_3c = *(float *)(param_1 + 0x18);
    fStack_38 = *(float *)(param_1 + 0x1c);
    fStack_34 = _DAT_005ab844 + *(float *)(param_1 + 0x20);
    if (0 < iVar3) {
      do {
        piVar4 = (int *)FUN_004c3840(iVar6);
        if ((((piVar4 != (int *)0x0) && ((char)piVar4[2] != '\0')) && (*piVar4 == 0xf)) &&
           ((piVar4[0xb] != 0 && (iVar6 != *(int *)(param_1 + 0xe4))))) {
          fStack_4 = (float)piVar4[0x14] + (float)piVar4[0x17];
          fStack_48 = ((float)piVar4[0x12] + (float)piVar4[0x15]) * _DAT_005a83e8;
          fStack_44 = ((float)piVar4[0x13] + (float)piVar4[0x16]) * _DAT_005a83e8;
          fStack_28 = fStack_4 * _DAT_005a83e8;
          fStack_40 = _DAT_005ab844 * _DAT_005a83e8 + fStack_28;
          fStack_24 = fStack_3c - fStack_48;
          fStack_20 = fStack_38 - fStack_44;
          fStack_1c = fStack_34 - fStack_40;
          fStack_30 = fStack_48;
          fStack_2c = fStack_44;
          fStack_18 = fStack_24;
          fStack_14 = fStack_20;
          fStack_10 = fStack_1c;
          fVar7 = (float10)FUN_0047ed20();
          if ((fVar7 <= (float10)(fVar1 * fVar1)) &&
             (cVar2 = FUN_004c1360(&fStack_3c,&fStack_48,0,0), cVar2 == '\0')) {
            *(float *)(param_1 + 0xe8) = fStack_48;
            *(float *)(param_1 + 0xec) = fStack_44;
            *(float *)(param_1 + 0xf0) = fStack_40;
            uVar5 = FUN_005679d0(0);
            *(undefined4 *)(param_1 + 0xf4) = uVar5;
            uVar5 = FUN_005679d0(1);
            *(int *)(param_1 + 0xe4) = iVar6;
            *(undefined4 *)(param_1 + 0xf8) = uVar5;
            return 1;
          }
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar3);
    }
  }
  return 0;
}

