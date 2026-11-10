/* Original Meteor.exe static export @ 004fd3b0; original sample not executed. */
/* XREF 004fb78b UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004fd3b0(int param_1,float param_2)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  
  cVar4 = FUN_00500fd0();
  if (cVar4 == '\0') {
    pfVar2 = (float *)(param_1 + 0xe0);
    FUN_00501730(pfVar2);
    pfVar1 = (float *)(param_1 + 0x3c);
    uVar5 = __ftol();
    iVar6 = (uVar5 ^ (int)uVar5 >> 0x1f) - ((int)uVar5 >> 0x1f);
    fVar3 = (float)iVar6;
    if (_DAT_005a83e8 <= (float)iVar6) {
      if (_DAT_005a84c0 < fVar3) {
        if (*pfVar2 <= _DAT_005a84c0) {
          *pfVar1 = *pfVar1 - _DAT_005a84a8;
        }
        else {
          *pfVar2 = *pfVar2 - _DAT_005a84a8;
        }
      }
      if (_DAT_005a8e84 <= fVar3) {
        param_2 = param_2 * _DAT_005ab84c;
        if (fVar3 < param_2) {
          param_2 = fVar3;
        }
        if (*pfVar2 <= *pfVar1) {
          param_2 = -param_2;
        }
      }
      else {
        param_2 = *pfVar2 - *pfVar1;
      }
      FUN_00500c00(param_2);
      FUN_00501730(pfVar2);
      FUN_00501730(pfVar1);
    }
  }
  return;
}

