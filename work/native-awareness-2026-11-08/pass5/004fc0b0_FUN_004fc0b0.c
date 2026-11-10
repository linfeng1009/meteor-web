/* Original Meteor.exe static export @ 004fc0b0; original sample not executed. */
/* XREF 004fc0a9 UNCONDITIONAL_CALL */
/* XREF 00503bd9 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004fc0b0(int param_1,undefined4 param_2,float param_3)

{
  int iVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  float10 fVar9;
  
  uVar7 = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  iVar4 = FUN_004c38d0();
  if (1 < iVar4) {
    return 0;
  }
  if (-1 < *(int *)(param_1 + 0x58)) {
    param_3 = *(float *)(&DAT_00666a04 + *(int *)(param_1 + 0x58) * 0x38) * _DAT_005a83e8 + param_3;
  }
  fVar2 = param_3 * param_3;
  piVar5 = (int *)FUN_004c33d0();
  iVar4 = *piVar5;
  iVar1 = piVar5[1] - iVar4 >> 0x1f;
  if ((piVar5[1] - iVar4) / 0x124 + iVar1 == iVar1) {
LAB_004fc25a:
    return *(undefined4 *)(param_1 + 0x74);
  }
  param_3 = 0.0;
  do {
    iVar4 = iVar4 + (int)param_3;
    if ((((-1 < *(int *)(iVar4 + 8)) && (iVar4 != param_1)) &&
        ((*(int *)(iVar4 + 0x4c) < 1 || (*(int *)(iVar4 + 0x4c) != *(int *)(param_1 + 0x4c))))) &&
       (0 < *(int *)(iVar4 + 0x48))) {
      fVar9 = (float10)FUN_0047ed20();
      if ((((fVar9 <= (float10)_DAT_005ab850) || (cVar3 = FUN_004fc610(iVar4 + 0x18), cVar3 != '\0')
           ) && ((float)fVar9 <= fVar2)) && (cVar3 = FUN_004fc980(iVar4), cVar3 != '\0')) {
        *(int *)(param_1 + 0x74) = iVar4;
        uVar6 = _rand();
        uVar6 = uVar6 & 0x80000001;
        bVar8 = uVar6 == 0;
        if ((int)uVar6 < 0) {
          bVar8 = (uVar6 - 1 | 0xfffffffe) == 0xffffffff;
        }
        if (bVar8) goto LAB_004fc25a;
      }
    }
    param_3 = (float)((int)param_3 + 0x124);
    iVar4 = *piVar5;
    uVar7 = uVar7 + 1;
    if ((uint)((piVar5[1] - iVar4) / 0x124) <= uVar7) {
      return *(undefined4 *)(param_1 + 0x74);
    }
  } while( true );
}

